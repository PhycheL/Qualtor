"""步骤 C 收尾（0.5.1）补充的回归测试：按题选择派生镜像、替换版本复制生成器输入、环境构建参数、
补评与分母的环境分支，以及 agents/ 与 evaluator/ 两侧环境文件的防漂移断言。不需要 Docker。"""
import copy
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
from unittest.mock import patch

from support import ASSESSMENT
import common
import docker_runner
import pipeline
import prepare_task
from build_contract import cmake_build_args, generated_units, task_environment
from test_docker_wiring import FakeAudit, ScriptedExecutor

ROOT = ASSESSMENT.parents[1]


class EnvironmentAudit(FakeAudit):
    """在 FakeAudit 之上为派生镜像返回配方标签与基础层，模拟本机已构建的环境镜像。"""

    def __init__(self, digest):
        super().__init__()
        self.digest = digest

    def run(self, stage, command, **kwargs):
        out = super().run(stage, command, **kwargs)
        args = command[command.index("--host") + 2:] if "--host" in command else command[1:]
        if args[:2] == ["image", "inspect"]:
            record = json.loads(out["stdout"])[0]
            record["RootFS"] = {"Layers": ["base-layer"]}
            if "qualtor-env-" in args[2]:
                record["Id"] = "sha256:env-" + ("gcc" if "-gcc:" in args[2] else "clang")
                record["RootFS"]["Layers"].append("environment-layer")
                record["Config"] = {"Labels": {"org.qualtor.environment.recipe-sha256": self.digest}}
            out["stdout"] = json.dumps([record])
        return out


class EnvironmentScripted(ScriptedExecutor):
    """按阶段返回结果的执行器；坐标改为本题被测文件，并记录环境选择。"""

    def __init__(self, task, tests, environment):
        super().__init__(tests)
        self.target = "/repo/" + task["target_sources"][0]
        self.record = environment
        self.inputs = [p for e in task.get("build", {}).get("codegen", []) for p in e.get("inputs", [])]
        self.task_root = common.source_root(task)
        self.copies = {}

    def environment(self, task):
        return self.record

    def run_phase(self, label, toolchain, mounts, env, job, out_host, timeout, audit):
        # 替换版本的源码副本在评测结束后清理；构建阶段时记录副本里的生成器输入与被测文件。
        root = Path(mounts["repo"][0]) if "repo" in mounts else self.task_root
        if root != self.task_root:
            self.copies[label] = {rel: (root / rel).read_bytes() for rel in self.inputs + [self.target[len("/repo/"):]]}
        step = super().run_phase(label, toolchain, mounts, env, job, out_host, timeout, audit)
        text = json.dumps(step).replace("/repo/cpp/src/GildedRose.cc", self.target)
        return json.loads(text)


class PhaseImageTest(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        self.recipe, self.digest = task_environment({"environment": "bank-20261021"})

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def test_docker_executor_selects_environment_image_per_job(self):
        audit = EnvironmentAudit(self.digest)
        ex = docker_runner.DockerExecutor(audit, self.tmp / "evidence", "env-images")
        for toolchain in ("gcc", "clang"):
            with self.subTest(toolchain=toolchain):
                ex.run_phase(f"{toolchain}-env", toolchain, {}, {}, {"_environment": "bank-20261021"},
                             self.tmp / f"{toolchain}-env", 60, audit)
                create = [c for c in audit.commands if "create" in c][-1]
                self.assertIn("sha256:env-" + toolchain, create)
                ex.run_phase(f"{toolchain}-base", toolchain, {}, {}, {}, self.tmp / f"{toolchain}-base", 60, audit)
                create = [c for c in audit.commands if "create" in c][-1]
                self.assertIn(ex.images[toolchain]["id"], create)
                self.assertFalse(any(token.startswith("sha256:env-") for token in create))
        record = ex.environment({"build": {"environment": "bank-20261021"}})
        self.assertEqual(record["recipe_sha256"], self.digest)
        self.assertEqual({k: v["id"] for k, v in record["images"].items()},
                         {"gcc": "sha256:env-gcc", "clang": "sha256:env-clang"})

    def test_every_assessment_phase_uses_the_task_environment(self):
        task = common.load_task("orc-bloom-filter")
        # 内存中加一个替换被测源文件的版本，覆盖替换版本的构建与运行阶段。
        rel = task["target_sources"][0]
        variant_root = self.tmp / "variants"
        replaced = variant_root / "hw-test" / rel
        replaced.parent.mkdir(parents=True)
        replaced.write_bytes((common.source_root(task) / rel).read_bytes() + b"\n// replaced\n")
        task["variants"] = [{"id": "hw-test", "kind": "handwritten", "expect": "fail",
                             "files": {rel: common.sha256_file(replaced)}}]
        product = self.tmp / "product"
        (product / "tests").mkdir(parents=True)
        (product / "tests/t.cc").write_text("// frozen\n")
        common.freeze_product(product)
        environment = {"name": self.recipe["name"], "recipe_sha256": self.digest,
                       "images": {"gcc": {"id": "env-gcc"}, "clang": {"id": "env-clang"}}}
        ex = EnvironmentScripted(task, ["S.A"], environment)
        from audit import Audit
        with patch.object(pipeline, "variant_dir", lambda t, v: variant_root / v["id"]), \
                patch.object(common, "variant_dir", lambda t, v: variant_root / v["id"]):
            result = pipeline.assess_product(ex, task, product, self.tmp / "out", {}, Audit(self.tmp / "audit"), prep=True)
        labels = [c["label"] for c in ex.calls]
        self.assertEqual(labels, ["gcc-build", "gcc-run", "clang-build", "mull", "v01-build", "v01-run"],
                         result.get("infra_detail"))
        self.assertTrue(all(c["job"].get("_environment") == "bank-20261021" for c in ex.calls))
        self.assertEqual(result["environment"], environment)
        for call in ex.calls:
            if call["label"].endswith("-build"):
                self.assertEqual(call["job"]["environment_recipe"], self.recipe)
                self.assertEqual(call["job"]["build"]["codegen"], task["build"]["codegen"])
        # 替换版本：整棵树复制，.proto 等生成器输入随之复制，生成单元只由题目声明推出。
        self.assertEqual(sorted(ex.copies), ["v01-build"])
        copied = ex.copies["v01-build"]
        for proto in task["build"]["codegen"][0]["inputs"]:
            self.assertEqual(copied[proto], (common.source_root(task) / proto).read_bytes())
        self.assertEqual(copied[rel], replaced.read_bytes())

    def test_variant_copy_includes_generator_inputs(self):
        task = common.load_task("libphonenumber-lite")
        rel = task["target_sources"][0]
        variant_root = self.tmp / "variants"
        replaced = variant_root / "v" / rel
        replaced.parent.mkdir(parents=True)
        replaced.write_text("// replacement\n")
        variant = {"id": "v", "files": {rel: common.sha256_file(replaced)}}
        before = generated_units(task["build"], "/build")
        with patch.object(common, "variant_dir", lambda t, v: variant_root / v["id"]):
            common.copy_variant_tree(task, variant, self.tmp / "copy")
        inputs = task["build"]["codegen"][0]["inputs"]
        self.assertTrue(all(p in task["source"]["files"] for p in inputs))
        for proto in inputs:
            self.assertEqual(common.sha256_file(self.tmp / "copy" / proto), task["source"]["files"][proto])
        self.assertEqual(generated_units(task["build"], "/build"), before)


class EnvironmentArgumentsTest(unittest.TestCase):
    def test_cmake_build_args_environment_branch(self):
        recipe, _ = task_environment({"environment": "bank-20261021"})
        build = {"environment": "bank-20261021", "link_libraries": ["Qt5::Core", "protobuf::libprotobuf"],
                 "codegen": [{"tool": "moc"},
                             {"tool": "protoc", "inputs": ["proto/a/x.proto"], "import_dirs": ["proto", "other"]}]}
        args = cmake_build_args(build, [], None, recipe, "/repo", ["/repo/a.h", "/product/tests/t.h"])
        self.assertEqual(args[:3], ["-DQUALTOR_SUPPORT_SOURCES=", "-DQUALTOR_DEFINES=", "-DQUALTOR_COMPILE_OPTIONS="])
        self.assertEqual(args[3:], [
            "-DQUALTOR_LIBRARIES=Qt5::Core;protobuf::libprotobuf",
            "-DQUALTOR_PACKAGES=Protobuf;Qt5",
            "-DCMAKE_PREFIX_PATH=" + ";".join(["/opt/googletest", *recipe["cmake_prefix_path"]]),
            "-DQUALTOR_AUTOMOC=ON", "-DQUALTOR_MOC_HEADERS=/repo/a.h;/product/tests/t.h",
            "-DQUALTOR_PROTO_FILES=/repo/proto/a/x.proto",
            "-DQUALTOR_PROTO_IMPORT_DIRS=/repo/proto;/repo/other",
            "-DQUALTOR_PROTO_OUTPUTS=a/x.pb.cc"])
        for missing in ((None, "/repo"), (recipe, None)):
            with self.subTest(missing=missing), self.assertRaises(ValueError):
                cmake_build_args(build, [], None, *missing)
        with self.assertRaises(ValueError):
            cmake_build_args({**build, "link_libraries": ["GTest::gtest"]}, [], None, recipe, "/repo")
        # 没有环境的题：不出现任何环境参数，旧题命令不变。
        legacy = cmake_build_args({"defines": ["A=1"]}, [], None, recipe, "/repo", ["/repo/a.h"])
        self.assertFalse(any(a.startswith(("-DQUALTOR_LIBRARIES", "-DQUALTOR_PACKAGES", "-DCMAKE_PREFIX_PATH",
                                           "-DQUALTOR_AUTOMOC", "-DQUALTOR_PROTO")) for a in legacy))


class EnvironmentRecordsTest(unittest.TestCase):
    def setUp(self):
        self.task = common.load_task("humaneval-x-cpp-openssl")
        self.environment = common.load_baseline(self.task)["environment"]

    def test_pending_jobs_compare_environment_records(self):
        import evaluate
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            product, out = root / "product", root / "score/final"
            (product / "tests").mkdir(parents=True)
            (product / "tests/a.cc").write_text("// frozen\n")
            common.freeze_product(product)
            calibration = {"status": "passed", "run_id": "calibration"}
            result = {"status": "scored", "scorer": {"version": evaluate.assessment_version(),
                      "code_sha256": evaluate.assessment_code_sha256(), "calibration": calibration},
                      "task": {"task_json_sha256": self.task["_sha256"]}, "images": {},
                      "product": {"manifest_sha256": common.sha256_file(product / "manifest.json")},
                      "environment": self.environment}
            rebuilt = copy.deepcopy(self.environment)
            rebuilt["images"]["gcc"]["id"] = "sha256:rebuilt"
            for current, expected_pending in ((self.environment, 0), (rebuilt, 1), (None, 1)):
                with self.subTest(current=current):
                    common.write_json(out / "result.json", result)
                    environments = {self.task["id"]: current} if current else {}
                    pending, skipped = evaluate.pending_jobs([(self.task, product, None, {}, out)],
                                                             {self.task["id"]: calibration}, {}, environments)
                    self.assertEqual((len(pending), len(skipped)), (expected_pending, 1 - expected_pending))
                    if out.exists() and pending:
                        shutil.rmtree(out.parent)

    def test_build_baseline_records_one_environment(self):
        def run(environment):
            return {"raw_mutants": [{"id": "a", "mutator": "m", "status": "Killed", "location": {}}],
                    "mull_config_sha256": "cfg", "variants": [], "environment": environment}
        runs = {"reference": [run(self.environment), run(self.environment)],
                "probe": [run(self.environment), run(self.environment)]}
        draft = prepare_task.build_baseline(self.task, runs, "text", {}, "run")
        self.assertEqual(draft["environment"], self.environment)
        changed = copy.deepcopy(runs)
        changed["probe"][1]["environment"] = {**self.environment, "recipe_sha256": "other"}
        with self.assertRaisesRegex(ValueError, "环境不一致"):
            prepare_task.build_baseline(self.task, changed, "text", {}, "run")
        missing = {"reference": [run(None)], "probe": [run(None)]}
        with self.assertRaisesRegex(ValueError, "环境不一致"):
            prepare_task.build_baseline(self.task, missing, "text", {}, "run")
        legacy = common.load_task("gildedrose-update-quality")
        plain = {"reference": [run(None)], "probe": [run(None)]}
        self.assertNotIn("environment", prepare_task.build_baseline(legacy, plain, "text", {}, "run"))


class DriftTest(unittest.TestCase):
    def test_environment_files_are_identical_on_both_sides(self):
        pairs = [("agents/toolchains/check_environment.py", "evaluator/toolchains/check_environment.py"),
                 ("agents/toolchains/docker/Dockerfile.environment", "evaluator/toolchains/docker/Dockerfile.environment"),
                 ("agents/toolchains/docker/Dockerfile.environment.dockerignore",
                  "evaluator/toolchains/docker/Dockerfile.environment.dockerignore"),
                 ("agents/generator/build/contract.py", "evaluator/assessment/build_contract.py")]
        for left, right in pairs:
            with self.subTest(file=left):
                self.assertEqual((ROOT / left).read_bytes(), (ROOT / right).read_bytes())
        sides = [ROOT / "agents/toolchains/environment_smoke", ROOT / "evaluator/toolchains/environment_smoke"]
        listings = [sorted(str(p.relative_to(side)) for p in side.rglob("*") if p.is_file()
                           and "__pycache__" not in p.parts) for side in sides]
        self.assertEqual(listings[0], listings[1])
        self.assertTrue(listings[0])
        for rel in listings[0]:
            with self.subTest(smoke=rel):
                self.assertEqual((sides[0] / rel).read_bytes(), (sides[1] / rel).read_bytes())

    def test_environment_build_copies_differ_only_in_import(self):
        product = (ROOT / "agents/generator/build/environment.py").read_text().splitlines()
        evaluator = (ROOT / "evaluator/toolchains/environment_build.py").read_text().splitlines()
        self.assertEqual(len(product), len(evaluator))
        different = [(a, b) for a, b in zip(product, evaluator) if a != b]
        self.assertEqual(different, [("from generator.build.contract import environment_tag",
                                      "from build_contract import environment_tag")])


class SmokeCheckTest(unittest.TestCase):
    """冒烟检查只能在 Docker 中运行；这里核对生成的 CMake 与模板的 protoc 接线一致。"""

    def test_smoke_generates_protobuf_like_the_template(self):
        sys.path.insert(0, str(ROOT / "evaluator/common"))
        sys.path.insert(0, str(ROOT / "evaluator/toolchains"))
        import check_environment
        recipe, _ = task_environment({"environment": "bank-20261021"})

        class StopAtConfigure:
            def __init__(self, root):
                pass

            def run(self, stage, argv, **kwargs):
                if stage == "cmake-configure":
                    raise RuntimeError("stop before cmake")
                stdout = {"protoc-version": "libprotoc 3.21.12\n", "compiler-version": "g++-14 (Debian 14.2.0-19) 14.2.0\n"}
                return {"returncode": 0, "timed_out": False, "stdout": stdout.get(stage, ""), "stderr": ""}

        with tempfile.TemporaryDirectory() as tmp, patch.object(check_environment, "Audit", StopAtConfigure):
            with self.assertRaisesRegex(RuntimeError, "stop before cmake"):
                check_environment.check("gcc", recipe, Path(tmp), {})
            text = (Path(tmp) / "smoke-input/CMakeLists.txt").read_text()
        self.assertNotIn("protobuf_generate", text)
        self.assertIn('COMMAND protobuf::protoc "--cpp_out=${CMAKE_CURRENT_BINARY_DIR}"', text)
        self.assertIn('target_sources(env_tests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/probe.pb.cc"', text)
        template = (ROOT / "evaluator/assessment/cmake/CMakeLists.txt").read_text()
        self.assertIn('COMMAND protobuf::protoc "--cpp_out=${CMAKE_CURRENT_BINARY_DIR}"', template)
        source = (ROOT / "evaluator/toolchains/check_environment.py").read_text()
        # 覆盖率断言针对未过滤的 gcov 数据，不能先按被测文件过滤再断言。
        self.assertIn("gcda = sorted(prefix.rglob('*.gcda'))", source)
        self.assertNotIn("if entry['file'] == str(smoke / 'subject.cc'):", source)


if __name__ == "__main__":
    unittest.main()
