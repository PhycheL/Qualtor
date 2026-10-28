"""Docker 模式的接线测试（不需要 Docker）：
- 用假的 docker 命令检查 DockerExecutor 的隔离参数、挂载核对和结果读取；
- 用脚本化执行器检查流水线在 Docker 模式下生成的任务和挂载：容器内路径、只读属性、
  隐藏材料只在替换版本的构建阶段出现、Mull 配置只在 Clang 阶段出现。
"""
import json
from pathlib import Path
import shutil
import tempfile
import unittest

from support import ASSESSMENT
import common
import docker_runner
import judge
import pipeline

REFERENCE_PRODUCT = common.CALIBRATION / "gildedrose-update-quality" / "CAL-15" / "final"


class FakeAudit:
    """模拟 docker 命令行：记录命令，并按需返回 inspect 结果、写出 step.json。"""

    def __init__(self, tamper_rw=False, reject_short_images=False):
        self.commands, self.created, self.tamper_rw = [], {}, tamper_rw
        self.reject_short_images = reject_short_images

    def run(self, stage, command, cwd=None, timeout=180, input_text=None, echo=False):
        self.commands.append(command)
        out = {"returncode": 0, "timed_out": False, "stdout": "", "stderr": "", "stderr_log": "x", "stdout_log": "x"}
        args = command[command.index("--host") + 2:] if "--host" in command else command[1:]
        if command[:3] == ["docker", "context", "inspect"]:
            out["stdout"] = "unix:///fake.sock\n"
        elif args[:2] == ["image", "inspect"]:
            if self.reject_short_images and not args[2].startswith("docker.io/library/"):
                return {**out, "returncode": 1, "stderr": f"No such image: {args[2]}"}
            out["stdout"] = json.dumps([{"Id": "sha256:" + args[2][:10], "Os": "linux", "Architecture": "arm64"}])
        elif args[:1] == ["create"]:
            name = args[args.index("--name") + 1]
            mounts = []
            for i, token in enumerate(args):
                if token == "--mount":
                    fields = dict(f.split("=", 1) if "=" in f else (f, True) for f in args[i + 1].split(","))
                    mounts.append({"Destination": fields["target"], "Source": fields["source"],
                                   "RW": "readonly" not in fields})
            if self.tamper_rw:
                mounts[0]["RW"] = not mounts[0]["RW"]
            self.created[name] = {"Mounts": mounts, "HostConfig": {"NetworkMode": "none", "ReadonlyRootfs": True},
                                  "State": {"Running": False, "ExitCode": 0}, "args": args}
        elif args[:1] == ["inspect"]:
            out["stdout"] = json.dumps([self.created[args[1]]])
        elif args[:2] == ["start", "--attach"]:
            record = self.created[args[2]]
            out_dir = next(m["Source"] for m in record["Mounts"] if m["Destination"] == "/out")
            Path(out_dir, "step.json").write_text(json.dumps({"status": "built"}))
        return out


class DockerExecutorTest(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def test_short_name_lookup_failure_does_not_block_startup(self):
        # 本机捕获的故障：短名称返回 No such image，完整名称仍解析到原镜像。
        audit = FakeAudit(reject_short_images=True)
        ex = docker_runner.DockerExecutor(audit, self.tmp / "evidence", "image-reference")
        self.assertEqual(set(ex.images), {"gcc", "clang"})
        ex.run_phase("gcc-build", "gcc", {}, {}, {}, self.tmp / "out", 60, audit)
        create = next(c for c in audit.commands if "create" in c)
        self.assertIn(ex.images["gcc"]["id"], create)
        self.assertNotIn(ex.images["gcc"]["tag"], create)

    def test_isolation_flags_and_mounts(self):
        audit = FakeAudit()
        ex = docker_runner.DockerExecutor(audit, self.tmp / "evidence", "Unit-Test")
        self.assertEqual(set(ex.images), {"gcc", "clang"})
        step = ex.run_phase("gcc-build", "gcc", {"repo": (self.tmp, True), "build": (self.tmp / "b", False)},
                            {"MULL_CONFIG": "/config/mull.yml"}, {"phase": "build"}, self.tmp / "out", 60, audit)
        self.assertEqual(step["status"], "built")
        create = next(c for c in audit.commands if "create" in c)
        for flag in ("--network", "none", "--read-only", "--cap-drop", "ALL", "no-new-privileges", "--pids-limit"):
            self.assertIn(flag, create)
        self.assertIn("MULL_CONFIG=/config/mull.yml", create)
        mounts = [create[i + 1] for i, t in enumerate(create) if t == "--mount"]
        self.assertIn(f"type=bind,source={self.tmp},target=/repo,readonly", mounts)
        self.assertIn(f"type=bind,source={self.tmp / 'b'},target=/build", mounts)
        self.assertIn(f"type=bind,source={ASSESSMENT},target=/assessment,readonly", mounts)
        self.assertTrue(any(c[-2:] == ["--force", c[-1]] and "rm" in c for c in audit.commands))
        self.assertEqual(json.loads((self.tmp / "out" / "job.json").read_text()), {"phase": "build"})

    def test_mount_mismatch_aborts_and_removes_container(self):
        audit = FakeAudit(tamper_rw=True)
        ex = docker_runner.DockerExecutor(audit, self.tmp / "evidence", "unit")
        with self.assertRaises(docker_runner.DockerError):
            ex.run_phase("gcc-run", "gcc", {"build": (self.tmp, True)}, {}, {}, self.tmp / "out", 60, audit)
        self.assertTrue(any("rm" in c for c in audit.commands))
        self.assertFalse(any("start" in c for c in audit.commands))


class ScriptedExecutor:
    """Docker 模式的路径规则，按阶段返回预先写好的结果，并记录每个阶段的任务与挂载。"""
    mode = "docker"
    capabilities = {"coverage": True, "mull": True}
    images = {"gcc": {"id": "g"}, "clang": {"id": "c"}}

    def __init__(self, tests, failing_on=None):
        self.tests, self.failing_on, self.calls = tests, failing_on or {}, []

    @staticmethod
    def at(name, host_path):
        return "/" + name

    def tools(self, toolchain):
        return {}

    def run_phase(self, label, toolchain, mounts, env, job, out_host, timeout, audit):
        self.calls.append({"label": label, "toolchain": toolchain, "mounts": mounts, "env": env, "job": dict(job)})
        if job["phase"] == "build":
            return {"status": "built"}
        if job["phase"] == "mull":
            return {"status": "ok", "mutants": [{"id": "cxx_add_to_sub:/repo/cpp/src/GildedRose.cc:1:1:1:2",
                                                 "mutator": "cxx_add_to_sub", "status": "Killed", "location": {}}]}
        if job.get("mode") == "variant":
            failing = self.failing_on.get(label, [])
            return {"status": "ok", "record": {"variant_outcomes": {n: {"outcome": "failed" if n in failing else "passed"}
                                                                    for n in job["tests"]}}}
        discovered = [{"name": n} for n in self.tests]
        full = {"returncode": 0, "timed_out": False, "json": True,
                "outcomes": {n: {"outcome": "passed", "failures": []} for n in self.tests}}
        step3, problem = judge.step3_statuses(discovered, full, {})
        stability = {n: {"repeat_failures": 0, "shuffle_failures": 0, "isolation_outcome": "passed"} for n in self.tests}
        record = {"discovery": {"ok": True, "tests": discovered}, "full_run": full, "isolation": {}, "step3": step3,
                  "step3_problem": problem, "stability": stability,
                  "final_statuses": judge.final_test_statuses(step3, stability),
                  "coverage": {"status": "ok", "data": {
                      "files": {"/repo/cpp/src/GildedRose.cc": {"line": {"covered": 29, "total": 29},
                                                                "branch_all": {"covered": 38, "total": 38},
                                                                "function": {"covered": 2, "total": 2},
                                                                "uncovered_functions": []}},
                      "total": {"lines": {"covered": 29, "total": 29}, "branches": {"covered": 38, "total": 38},
                                "functions": {"covered": 2, "total": 2}}}}}
        return {"status": "ok", "record": record}


class PipelineWiringTest(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        self.task = common.load_task("gildedrose-update-quality")

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def score(self, executor):
        from audit import Audit
        return pipeline.assess_product(executor, self.task, REFERENCE_PRODUCT, self.tmp / "out", {"unit": True},
                                      Audit(self.tmp / "audit"), prep=True)

    def test_jobs_and_mounts(self):
        ex = ScriptedExecutor(["S.A", "S.B"], failing_on={"v02-run": ["S.A"]})
        result = self.score(ex)
        self.assertEqual(result["status"], "scored", result.get("infra_detail"))
        calls = {c["label"]: c for c in ex.calls}
        self.assertEqual(list(calls), ["gcc-build", "gcc-run", "clang-build", "mull", "v01-build", "v01-run",
                                       "v02-build", "v02-run"])
        build = calls["gcc-build"]["job"]
        self.assertEqual(build["mode"], "coverage")
        self.assertEqual(build["target_sources"], ["/repo/cpp/src/GildedRose.cc"])
        self.assertEqual(build["test_sources"], ["/product/tests/reference_tests.cc"])
        self.assertEqual(build["include_dirs"], ["/repo/cpp/src", "/product/tests"])
        self.assertEqual((build["build_dir"], build["template_dir"], build["out_dir"]), ("/build", "/assessment/cmake", "/out"))
        self.assertEqual(calls["clang-build"]["job"]["mode"], "mull")
        self.assertEqual(calls["clang-build"]["env"], {"MULL_CONFIG": "/config/mull.yml"})
        self.assertEqual(calls["mull"]["job"]["tests"], ["S.A", "S.B"])
        self.assertEqual(calls["v01-build"]["job"]["target_sources"], ["/variant/cpp/src/GildedRose.cc"])
        self.assertEqual(calls["v01-build"]["job"]["mode"], "plain")
        hidden = str(self.task["_dir"] / "hidden")
        for label, call in calls.items():
            readonly = {name: ro for name, (_, ro) in call["mounts"].items()}
            hosts = [str(host) for host, _ in call["mounts"].values()]
            if label.endswith("-run") or label == "mull":
                self.assertTrue(all(readonly.values()), f"{label} 的输入挂载应全部只读")
                self.assertFalse(any(h.startswith(hidden) for h in hosts), f"{label} 不应挂载隐藏材料")
                self.assertNotIn("product", call["mounts"])
            if label in ("gcc-build", "gcc-run", "clang-build", "mull"):
                self.assertNotIn("variant", call["mounts"])
            if label.endswith("-build") and label.startswith("v"):
                self.assertTrue(call["mounts"]["variant"][1])
                self.assertTrue(str(call["mounts"]["variant"][0]).startswith(hidden))
            if "config" in call["mounts"]:
                self.assertIn(label, ("clang-build", "mull"))
        self.assertEqual({v["id"]: v["outcome"] for v in result["variants"]}, {"eq-02": "clean", "hw-01": "detected"})
        self.assertEqual(result["counts"]["coverage"]["files"]["cpp/src/GildedRose.cc"]["lines"]["covered"], 29)
        self.assertEqual(result["raw_mutants"][0]["status"], "Killed")
        self.assertTrue((self.tmp / "out" / "clang-build" / "config" / "mull.yml").is_file())

    def test_record_mismatch_is_infra_error(self):
        class Tampered(ScriptedExecutor):
            def run_phase(self, label, *args):
                step = super().run_phase(label, *args)
                if label == "gcc-run":
                    step["record"]["final_statuses"]["S.A"] = "flaky"
                return step

        result = self.score(Tampered(["S.A", "S.B"]))
        self.assertEqual(result["status"], "infra_error")
        self.assertIn("judge_mismatch", result["infra_detail"])

    def test_invalid_results_keep_generation_cost(self):
        from audit import Audit
        import aggregate

        class BuildFailure(ScriptedExecutor):
            def run_phase(self, label, *args):
                return {"status": "build_failed", "reason": "compile_or_link_error"}

        cost = {"tokens": {"input": 120, "output": 40}, "seconds": 12,
                "model_calls": 2, "repair_rounds": 1}
        cost_path = self.tmp / "cost.json"
        common.write_json(cost_path, cost)
        for reason, executor, product in (
                ("artifact_rejected", ScriptedExecutor([]), self.tmp / "unfrozen"),
                ("build_failed", BuildFailure([]), REFERENCE_PRODUCT),
                ("zero_tests", ScriptedExecutor([]), REFERENCE_PRODUCT)):
            with self.subTest(reason=reason):
                result = pipeline.assess_product(executor, self.task, product, self.tmp / reason, {},
                                                Audit(self.tmp / "audit"), cost_path, prep=True)
                self.assertEqual((result["status"], result["invalid_reason"]), ("invalid", reason))
                self.assertEqual(result["cost"], cost)
                self.assertEqual(result["metrics"]["K1"], cost)
                summary = aggregate.summarize_task({1: result})
                self.assertEqual(summary["K1.seconds"], {"mean": 12, "median": 12})
                self.assertEqual(summary["K1.tokens_input"]["mean"], 120)

    def test_invalid_result_reports_missing_cost(self):
        result = self.score(ScriptedExecutor([]))
        self.assertEqual(result["invalid_reason"], "zero_tests")
        self.assertIn("cost_missing", result["warnings"])


if __name__ == "__main__":
    unittest.main()
