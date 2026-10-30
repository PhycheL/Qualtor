"""runner 的准入门禁（--allow-unadmitted）与产品/评测环境记录比较；用替身执行器，不需要 Docker。"""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import Mock, patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import host  # noqa: E402
import run  # noqa: E402
from common import load_task, write_json  # noqa: E402


class FakeExecutor:
    images = {"gcc": {"id": "sha256:base-gcc"}, "clang": {"id": "sha256:base-clang"}}

    def __init__(self, *args, **kwargs):
        pass

    def environment(self, task):
        return {"name": "bank-20261021", "recipe_sha256": "recipe",
                "images": {"gcc": {"id": "sha256:env-gcc"}, "clang": {"id": "sha256:env-clang"}}}

    def image_for(self, task, toolchain):
        return self.environment(task)["images"][toolchain]


class AllowUnadmittedTest(unittest.TestCase):
    """a273de2 的行为：加 --allow-unadmitted 时，准入后材料变化（stale）的题也能做非正式冒烟。"""

    def execute(self, allow, admission):
        task = load_task("gildedrose-update-quality")
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        trial_result = {"task": task["id"], "trial": 1, "status": "finished", "set": "dev", "scores": {},
                        "cost": {"final": {"tokens": {"input": 0, "output": 0, "cache_read": 0, "cache_write": 0},
                                           "seconds": 0, "model_calls": 0, "repair_rounds": 0, "usd": 0}}}
        with patch("run.RUNS", Path(tmp.name)), patch("run.DockerExecutor", FakeExecutor), \
                patch("run.GenerationExecutor") as generator, \
                patch("run.calibration_status", return_value={"status": "passed", "run_id": "cal"}), \
                patch("run.admission_status", return_value=admission), \
                patch("run.trial", return_value=trial_result) as trial, \
                patch("run.tree_hash", return_value="hash"), patch("run.assessment_code_sha256", return_value="code"), \
                patch("run.git_snapshot", return_value={"commit": "0" * 40}):
            try:
                outcome = run.execute({}, {"name": "test", "sha256": "x" * 64}, [task], 1, 1, "unit", allow_unadmitted=allow)
            except ValueError as error:
                outcome = error
            manifest = json.loads((Path(tmp.name) / "unit/run.json").read_text())
        return outcome, manifest, generator, trial

    def test_stale_admission_is_rejected_without_flag(self):
        stale = {"status": "stale", "reason": "材料已变化"}
        outcome, manifest, generator, trial = self.execute(False, stale)
        self.assertIsInstance(outcome, ValueError)
        self.assertIn("--allow-unadmitted", str(outcome))
        generator.assert_not_called()
        trial.assert_not_called()
        self.assertEqual(manifest["status"], "failed")
        self.assertEqual(manifest["admission"]["gildedrose-update-quality"]["status"], "stale")

    def test_stale_admission_continues_with_flag_and_keeps_state(self):
        stale = {"status": "stale", "reason": "材料已变化"}
        outcome, manifest, generator, trial = self.execute(True, stale)
        self.assertNotIsInstance(outcome, Exception)
        trial.assert_called_once()
        self.assertEqual(manifest["status"], "completed")
        self.assertTrue(manifest["allow_unadmitted"])
        # stale 状态原样留在 manifest 中；汇总按指纹核对准入，结果不能用于正式比较。
        self.assertEqual(manifest["admission"]["gildedrose-update-quality"]["status"], "stale")

    def test_admitted_tasks_run_without_flag(self):
        outcome, manifest, _, trial = self.execute(False, {"status": "admitted"})
        self.assertNotIsInstance(outcome, Exception)
        trial.assert_called_once()
        self.assertFalse(manifest["allow_unadmitted"])

    def test_main_passes_flag_to_execute(self):
        with patch.object(sys, "argv", ["run.py", "--tasks", "gildedrose-update-quality", "--trials", "1",
                                        "--allow-unadmitted"]), \
                patch("run.load_config", return_value=({}, {})), \
                patch("run.select_tasks", return_value=[]) as select, \
                patch("run.execute", return_value=(Path("/tmp/x"), {"status": "completed"})) as execute:
            run.main()
        self.assertTrue(select.call_args.args[2])
        self.assertTrue(execute.call_args.kwargs["allow_unadmitted"])


class EnvironmentComparisonTest(unittest.TestCase):
    """GenerationExecutor 只在产品确实返回工具链记录时比较环境；没有记录时按状态处理。"""

    def generate(self, result, returncode=0, environment=True):
        task = load_task("humaneval-x-cpp-openssl")
        if not environment:
            task = load_task("gildedrose-update-quality")
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        record = Path(tmp.name) / "trial"

        def product(audit, command, cancel):
            write_json(record / "result.json", {"schema": 1, **result})
            return {"returncode": returncode, "stderr_log": "stderr.log"}

        generator = host.GenerationExecutor(FakeExecutor())
        with patch.object(host, "run_product", side_effect=product):
            return generator.generate(task, {}, record)

    def toolchain(self, **environment):
        return {"id": "sha256:env-gcc", "environment": {"name": "bank-20261021", "recipe_sha256": "recipe",
                                                        "gcc_image_id": "sha256:env-gcc", **environment}}

    def test_matching_environment_is_accepted(self):
        result = self.generate({"status": "finished", "toolchain": self.toolchain()})
        self.assertEqual(result["status"], "finished")

    def test_mismatched_environment_is_rejected(self):
        for change in ({"recipe_sha256": "other"}, {"name": "other"}, {"gcc_image_id": "sha256:other"}):
            with self.subTest(change=change), self.assertRaisesRegex(ValueError, "构建环境记录不一致"):
                self.generate({"status": "finished", "toolchain": self.toolchain(**change)})
        with self.assertRaisesRegex(ValueError, "构建环境记录不一致"):
            self.generate({"status": "finished", "toolchain": {"id": "sha256:env-gcc"}})
        with self.assertRaisesRegex(ValueError, "GCC 镜像不同"):
            self.generate({"status": "finished", "toolchain": {**self.toolchain(), "id": "sha256:base-gcc"}})

    def test_missing_toolchain_keeps_cancelled_and_agent_error_handling(self):
        for status, code in (("cancelled", 143), ("agent_error", 1)):
            with self.subTest(status=status):
                result = self.generate({"status": status, "toolchain": None}, returncode=code)
                self.assertEqual(result["status"], status)
        with self.assertRaisesRegex(RuntimeError, "产品入口异常退出"):
            self.generate({"status": "finished", "toolchain": None}, returncode=2)

    def test_legacy_tasks_compare_base_image_only(self):
        result = self.generate({"status": "finished", "toolchain": {"id": "sha256:base-gcc"}}, environment=False)
        self.assertEqual(result["status"], "finished")
        with self.assertRaisesRegex(ValueError, "GCC 镜像不同"):
            self.generate({"status": "finished", "toolchain": {"id": "sha256:env-gcc"}}, environment=False)


if __name__ == "__main__":
    unittest.main()
