"""覆盖 run 不挂死、出错即止、反馈截断、补评续跑、run 记录格式和依赖指纹；容器内行为由 Docker 剧本验收覆盖。"""
import json
import os
from pathlib import Path
import re
import shutil
import signal
import subprocess
import sys
import tempfile
import time
import unittest
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE.parent), str(HERE.parent / "runtime")]
import host  # noqa: E402  (同时把 common/、scorer/ 加入导入路径)
import audit  # noqa: E402
import build_service  # noqa: E402
import launch  # noqa: E402
import run as run_module  # noqa: E402
import runs  # noqa: E402
import score  # noqa: E402
import aggregate  # noqa: E402
from common import write_json  # noqa: E402


def alive(pid):
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    return True


class AuditLeftoverProcessTest(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.audit = audit.Audit(Path(temporary.name))

    def test_background_child_holding_stdout_is_killed(self):
        # 测试进程留下一个继承了 stdout 的后台进程；修复前这里会一直等到它结束。
        code = "import subprocess,sys; p=subprocess.Popen(['sleep','60']); print(p.pid, flush=True)"
        started = time.monotonic()
        result = self.audit.run("leftover", [sys.executable, "-c", code], timeout=30)
        self.assertLess(time.monotonic() - started, audit.DRAIN_GRACE_SECONDS)
        self.assertEqual(result["returncode"], 0)
        self.assertFalse(result["output_incomplete"])
        child = int(result["stdout"].split()[0])
        time.sleep(0.2)
        self.assertFalse(alive(child) and Path(f"/proc/{child}").exists(), "后台进程应已被结束")

    def test_child_escaping_process_group_does_not_block_forever(self):
        code = ("import subprocess,sys; p=subprocess.Popen(['sleep','60'], start_new_session=True); "
                "print(p.pid, flush=True)")
        with patch.object(audit, "DRAIN_GRACE_SECONDS", 1):
            started = time.monotonic()
            result = self.audit.run("escaped", [sys.executable, "-c", code], timeout=30)
            elapsed = time.monotonic() - started
        try:
            self.assertLess(elapsed, 10)
            self.assertTrue(result["output_incomplete"])
            self.assertEqual(result["returncode"], 0)
        finally:
            pid = re.search(r"\d+", result["stdout"] or "")
            if pid:
                try:
                    os.kill(int(pid.group()), signal.SIGKILL)
                except ProcessLookupError:
                    pass


class BuildServiceTest(unittest.TestCase):
    def test_feedback_lists_every_failure_before_details(self):
        outcomes = {f"Suite.Test{i:03d}": {"outcome": "passed"} for i in range(300)}
        for i in (5, 150, 299):
            outcomes[f"Suite.Test{i:03d}"] = {"outcome": "failed"}
        outcomes["Suite.Timeout"] = {"outcome": "timed_out"}
        details = {name: "x" * 5000 + "\n" for name in outcomes}
        text = build_service.feedback_text(outcomes, details)
        self.assertLessEqual(len(text), build_service.FEEDBACK_LIMIT)
        self.assertTrue(text.startswith("测试结果：共 301 个，通过 297 个，未通过 4 个。"))
        for name in ("Suite.Test005", "Suite.Test150", "Suite.Test299", "Suite.Timeout"):
            self.assertIn(f"- {name}:", text)
        self.assertIn("已截断", text)
        self.assertNotIn("Suite.Test006", text)  # 通过的测试不逐个列出

    def test_all_passed_feedback(self):
        text = build_service.feedback_text({"S.A": {"outcome": "passed"}}, {"S.A": "ok"})
        self.assertIn("全部通过", text)
        self.assertNotIn("失败详情", text)

    def test_kill_uid_only_kills_matching_processes(self):
        sleeper = subprocess.Popen(["sleep", "60"])
        self.addCleanup(lambda: sleeper.poll() is None and sleeper.kill())
        with tempfile.TemporaryDirectory() as tmp:
            proc = Path(tmp)
            (proc / str(sleeper.pid)).mkdir()
            (proc / "self").mkdir()
            self.assertEqual(build_service.kill_uid(os.getuid() + 12345, proc), [])
            self.assertIsNone(sleeper.poll())
            self.assertEqual(build_service.kill_uid(os.getuid(), proc), [sleeper.pid])
        sleeper.wait(timeout=5)
        self.assertEqual(sleeper.returncode, -signal.SIGKILL)


class WatchdogTest(unittest.TestCase):
    class Service:
        busy = False
        last_activity = 0.0

    def test_build_in_progress_pauses_watchdog(self):
        service = self.Service()
        self.assertEqual(launch.stalled_for(1000.0, 10.0, service), 990.0)
        service.busy = True
        self.assertEqual(launch.stalled_for(1000.0, 10.0, service), 0.0)

    def test_build_end_counts_as_activity(self):
        service = self.Service()
        service.last_activity = 900.0
        self.assertEqual(launch.stalled_for(1000.0, 10.0, service), 100.0)

    def test_copy_regular_skips_links_and_special_files(self):
        with tempfile.TemporaryDirectory() as tmp:
            source, target = Path(tmp) / "src", Path(tmp) / "dst"
            (source / "sub").mkdir(parents=True)
            (source / "a.cc").write_text("a")
            (source / "sub/b.h").write_text("b")
            os.symlink("/etc/passwd", source / "link.cc")
            os.mkfifo(source / "pipe")
            launch.copy_regular(source, target)
            self.assertEqual(sorted(str(p.relative_to(target)) for p in target.rglob("*")), ["a.cc", "sub", "sub/b.h"])


class RunTrialsTest(unittest.TestCase):
    def test_first_error_cancels_trials_not_yet_started(self):
        started = []

        def work(task, index):
            started.append(index)
            if index == 1:
                raise OSError("docker create failed")
            return {"task": task["id"], "trial": index, "status": "finished"}

        jobs = [({"id": "t"}, index) for index in range(1, 6)]
        results, errors, cancelled = run_module.run_trials(work, jobs, 1)
        self.assertEqual(started, [1])
        self.assertEqual(results, [])
        self.assertEqual(errors[0]["trial"], 1)
        self.assertIn("docker create failed", errors[0]["error"])
        self.assertEqual(sorted(c["trial"] for c in cancelled), [2, 3, 4, 5])

    def test_all_trials_run_without_errors(self):
        results, errors, cancelled = run_module.run_trials(
            lambda task, index: {"task": task["id"], "trial": index}, [({"id": "t"}, i) for i in range(1, 4)], 2)
        self.assertEqual(sorted(r["trial"] for r in results), [1, 2, 3])
        self.assertEqual((errors, cancelled), ([], []))


class RescoreResumeTest(unittest.TestCase):
    def test_finished_results_skipped_and_incomplete_set_aside(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            done, infra, partial, fresh = (root / f"trial-{i}/score/0.1.3/final" for i in range(1, 5))
            write_json(done / "result.json", {"status": "scored"})
            write_json(infra / "result.json", {"status": "infra_error"})
            (partial / "gcc-build").mkdir(parents=True)
            jobs = [("task", "product", None, {}, out) for out in (done, infra, partial, fresh)]
            pending, skipped = score.pending_jobs(jobs)
            self.assertEqual(skipped, [done])
            self.assertEqual([job[4] for job in pending], [infra, partial, fresh])
            self.assertFalse(infra.exists())
            self.assertTrue((infra.parent / "incomplete/final-1/result.json").is_file())
            self.assertTrue((partial.parent / "incomplete/final-1/gcc-build").is_dir())
            # 汇总不读取被移开的结果
            result = {"mode": "score", "meta": {"agent_version": "pi"}, "scorer": {"version": "0.1.3"},
                      "status": "scored"}
            write_json(infra.parent / "incomplete/final-1/result.json", result)
            self.assertEqual(aggregate.load_results([root], "0.1.3"), [])

    def test_rescore_refuses_uncalibrated_scorer(self):
        with tempfile.TemporaryDirectory() as tmp:
            run = Path(tmp) / "eval-x"
            out = run / "trials/t/trial-1/score/0.1.3/final"
            job = ({"id": "t"}, Path(tmp) / "product", None, {}, out)
            with patch.object(score, "RUNS", Path(tmp)), patch.object(score, "rescore_jobs", return_value=[job]), \
                 patch.object(score, "calibration_status", return_value={"status": "stale"}), \
                 patch("docker_runner.DockerExecutor") as docker, \
                 patch.object(score.pipeline, "score_product") as scored, \
                 patch.object(sys, "argv", ["score.py", "--rescore", "eval-x"]):
                docker.return_value.images = {}
                with self.assertRaises(SystemExit) as caught:
                    score.main()
            self.assertEqual(caught.exception.code, 2)
            scored.assert_not_called()
            record = json.loads(next((run / "score/0.1.3").glob("*/rescore.json")).read_text())
            self.assertEqual(record["status"], "failed")


class RunManifestTest(unittest.TestCase):
    def test_manifest_fields_and_vocabulary(self):
        with tempfile.TemporaryDirectory() as tmp:
            manifest = runs.new_manifest("eval-1", "eval", operation="generate")
            self.assertEqual((manifest["schema"], manifest["run_id"], manifest["status"]), (1, "eval-1", "running"))
            runs.finish(Path(tmp), manifest, "completed", passed=True)
            written = json.loads((Path(tmp) / "run.json").read_text())
            self.assertEqual((written["status"], written["passed"]), ("completed", True))
            self.assertIn("finished_at", written)
        with self.assertRaisesRegex(ValueError, "kind"):
            runs.new_manifest("x", "validation")
        with self.assertRaisesRegex(ValueError, "status"):
            runs.check_manifest(dict(runs.new_manifest("x", "eval"), status="passed"))
        with self.assertRaisesRegex(ValueError, "passed"):
            runs.check_manifest(dict(runs.new_manifest("x", "eval"), passed="yes"))


class PiRuntimeHashTest(unittest.TestCase):
    def test_dependency_changes_alter_runtime_hash_only(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "packages/a/node_modules/dep").mkdir(parents=True)
            (root / "packages/a/index.ts").write_text("source")
            dependency = root / "packages/a/node_modules/dep/index.js"
            dependency.write_text("module.exports = 1;")
            source, runtime = host.tree_hash(root), host.tree_hash(root, runtime=True)
            dependency.write_text("module.exports = 'tampered';")
            self.assertEqual(host.tree_hash(root), source)
            self.assertNotEqual(host.tree_hash(root, runtime=True), runtime)


class GuardNodeTest(unittest.TestCase):
    def test_guard_rules(self):
        node = shutil.which("node")
        if not node:
            self.skipTest("本机没有 node")
        version = subprocess.run([node, "--version"], capture_output=True, text=True).stdout.strip().lstrip("v")
        if tuple(int(x) for x in version.split(".")[:2]) < (23, 6):
            self.skipTest(f"node {version} 不能原生运行 .ts")
        result = subprocess.run([node, "--test", str(HERE / "guard.test.mjs")], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout[-3000:] + result.stderr[-2000:])


if __name__ == "__main__":
    unittest.main()
