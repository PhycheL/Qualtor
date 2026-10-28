import json
import os
from pathlib import Path
import shutil
import tempfile
import unittest
import unittest.mock

import support  # noqa: F401
import calibrate
import common


class CalibrationChecksTest(unittest.TestCase):
    result = {"status": "scored", "invalid_reason": None,
              "tests": {"S.A": "valid", "S.B": "flaky", "S.C": "valid"},
              "variants": [{"id": "eq-02", "outcome": "false_alarm", "failed_tests": ["S.C"]},
                           {"id": "hw-01", "outcome": "detected", "failed_tests": ["S.A"]}]}

    def test_hard_expectations_pass(self):
        hard = {"status": "scored", "tests": {"S.B": "flaky"}, "tests_default": "valid",
                "variants": {"eq-02": "false_alarm", "hw-01": "detected"}, "variant_failed_tests": {"eq-02": ["S.C"]}}
        self.assertEqual(calibrate.check_hard(hard, self.result), [])

    def test_hard_expectations_report_each_mismatch(self):
        hard = {"status": "invalid", "tests_default": "valid", "variants": {"hw-01": "not_detected"},
                "variant_failed_tests": {"eq-02": []}}
        problems = calibrate.check_hard(hard, self.result)
        self.assertEqual(len(problems), 4)

    def test_relations(self):
        metrics = {"X": {"M1_e2e": 0.1, "C1": 0.95, "S2_max": 0.5, "S1": 0.0}, "REF": {"M1_e2e": 0.9, "C1": 0.97}}
        expected = {"relations": [{"metric": "M1_e2e", "op": "<=", "ref": "REF", "factor": 0.2},
                                  {"metric": "C1", "op": "abs_diff_le", "ref": "REF", "value": 0.05},
                                  {"metric": "S2_max", "op": "between", "range": [0.2, 0.8]},
                                  {"metric": "S1", "op": "==", "value": 0}]}
        problems, skipped = calibrate.check_relations("X", expected, metrics, {"mull": True, "coverage": True})
        self.assertEqual((problems, skipped), ([], []))
        metrics["X"]["M1_e2e"] = 0.5
        problems, _ = calibrate.check_relations("X", expected, metrics, {"mull": True, "coverage": True})
        self.assertEqual(len(problems), 1)

    def test_relations_skip_missing_capabilities(self):
        expected = {"relations": [{"metric": "M1_e2e", "op": ">", "value": 0}, {"metric": "C1", "op": ">", "value": 0}]}
        problems, skipped = calibrate.check_relations("X", expected, {"X": {}}, {"mull": False, "coverage": False})
        self.assertEqual(problems, [])
        self.assertEqual(len(skipped), 2)

    def test_calibration_checks_cost_even_for_invalid_samples(self):
        task = common.load_task("gildedrose-update-quality")
        samples = calibrate.load_samples(task["id"], ["CAL-01"])
        cost = common.read_json(samples["CAL-01"]["dir"] / "generation" / "cost.json")
        result = {"status": "invalid", "invalid_reason": "zero_tests", "cost": cost,
                  "metrics": {"K1": cost}}
        capabilities = {"mull": True, "coverage": True}
        report = calibrate.evaluate(task, samples, {"CAL-01": [result, result]}, capabilities)
        self.assertTrue(report["passed"])
        for field in ("cost", "metrics"):
            with self.subTest(field=field):
                broken = dict(result, **{field: None})
                report = calibrate.evaluate(task, samples, {"CAL-01": [result, broken]}, capabilities)
                self.assertFalse(report["passed"])
                self.assertTrue(any("成本" in p for p in report["samples"]["CAL-01"]["problems"]))


class ProductAndTaskTest(unittest.TestCase):
    def setUp(self):
        self.task = common.load_task("gildedrose-update-quality")
        self.tmp = Path(tempfile.mkdtemp())
        (self.tmp / "tests").mkdir()
        (self.tmp / "tests" / "a.cc").write_text("// a\n")
        common.freeze_product(self.tmp)

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def test_valid_product(self):
        self.assertIsNone(common.validate_product(self.tmp, self.task))
        self.assertEqual(common.product_test_sources(self.tmp), ["tests/a.cc"])

    def test_tampered_product(self):
        (self.tmp / "tests" / "a.cc").write_text("// changed\n")
        self.assertIn("哈希不一致", common.validate_product(self.tmp, self.task))

    def test_unlisted_and_disallowed_files(self):
        (self.tmp / "tests" / "b.cc").write_text("// b\n")
        self.assertIn("manifest 与实际文件不一致", common.validate_product(self.tmp, self.task))
        (self.tmp / "tests" / "b.cc").unlink()
        (self.tmp / "CMakeLists.txt").write_text("project(x)\n")
        common.freeze_product(self.tmp)
        self.assertIn("不允许的文件", common.validate_product(self.tmp, self.task))

    def test_symlink_rejected(self):
        os.symlink("/etc/hosts", self.tmp / "tests" / "link.h")
        self.assertIn("符号链接", common.validate_product(self.tmp, self.task))

    def test_missing_manifest(self):
        (self.tmp / "manifest.json").unlink()
        self.assertEqual(common.validate_product(self.tmp, self.task), "缺少 manifest.json")

    def test_task_rejects_tampered_variant(self):
        broken = json.loads((self.task["_dir"] / "task.json").read_text())
        broken["variants"][0]["files"]["cpp/src/GildedRose.cc"] = "0" * 64
        broken["_dir"] = self.task["_dir"]
        with self.assertRaises(common.TaskError):
            common.validate_task(broken)

    def test_mull_config_only_targets(self):
        text = common.mull_config_text(self.task)
        self.assertIn("  - cxx_all", text)
        self.assertIn("'/repo/cpp/src/GildedRose\\.cc$'", text)

    def test_mull_config_matches_frozen_baseline(self):
        baseline = common.load_baseline(self.task)
        self.assertEqual(common.sha256_text(common.mull_config_text(self.task)),
                         baseline["mull"]["config_sha256"])



class SampleVariantsTest(unittest.TestCase):
    def test_sample_expectations_only_reference_existing_variants(self):
        task = common.load_task("gildedrose-update-quality")
        ids = {variant["id"] for variant in task["variants"]}
        for sample_id, sample in calibrate.load_samples(task["id"]).items():
            hard = sample["expected"].get("hard", {})
            with self.subTest(sample=sample_id):
                self.assertLessEqual(set(hard.get("variants", {})) | set(hard.get("variant_failed_tests", {})), ids)

if __name__ == "__main__":
    unittest.main()


class CalibrationTasksTest(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        self.original = calibrate.CALIBRATION
        calibrate.CALIBRATION = self.tmp
        for task, sample in (("task-a", "CAL-01"), ("task-b", "CAL-02"), ("task-c", "notes")):
            (self.tmp / task / sample).mkdir(parents=True)
            if sample.startswith("CAL"):
                (self.tmp / task / sample / "expected.json").write_text("{}")

    def tearDown(self):
        calibrate.CALIBRATION = self.original
        shutil.rmtree(self.tmp)

    def test_all_tasks_with_samples_are_calibrated(self):
        self.assertEqual(calibrate.calibration_tasks(), ["task-a", "task-b"])

    def test_sample_ids_must_be_unique_across_tasks(self):
        (self.tmp / "task-b" / "CAL-01").mkdir()
        (self.tmp / "task-b" / "CAL-01" / "expected.json").write_text("{}")
        with unittest.mock.patch.object(calibrate, "load_task", side_effect=lambda t: {"id": t}), \
                unittest.mock.patch.object(calibrate, "load_baseline", return_value={"mutants": []}):
            with self.assertRaisesRegex(SystemExit, "样本 ID 重复"):
                calibrate.plan(["task-a", "task-b"], None)
            tasks, samples = calibrate.plan(["task-a"], None)
            self.assertEqual((list(tasks), list(samples), samples["CAL-01"]["task"]), (["task-a"], ["CAL-01"], "task-a"))
            with self.assertRaisesRegex(SystemExit, "找不到样本"):
                calibrate.plan(["task-a"], ["CAL-09"])


class AdmissionTest(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        self.original = common.ADMISSION
        common.ADMISSION = self.tmp / "admission.json"
        self.task = common.load_task("gildedrose-update-quality")

    def tearDown(self):
        common.ADMISSION = self.original
        shutil.rmtree(self.tmp)

    def test_states_follow_the_registered_fingerprint(self):
        self.assertEqual(common.admission_status(self.task)["status"], "not_admitted")
        common.write_json(common.ADMISSION, {"schema": 1, "tasks": {self.task["id"]: {
            "task_sha256": common.task_sha256(self.task), "admitted_at": "t", "by": "reviewer"}}})
        self.assertEqual(common.admission_status(self.task),
                         {"status": "admitted", "admitted_at": "t", "by": "reviewer"})
        common.write_json(common.ADMISSION, {"schema": 1, "tasks": {self.task["id"]: {"task_sha256": "old"}}})
        self.assertEqual(common.admission_status(self.task)["status"], "stale")
        self.assertEqual(common.admission_state(self.task["id"], None)["status"], "stale")


class CalibrationStatusTest(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        self.original = common.CALIBRATION_STATUS
        common.CALIBRATION_STATUS = self.tmp / "calibration-status.json"
        self.task = common.load_task("gildedrose-update-quality")
        self.images = {"gcc": {"id": "g1"}, "clang": {"id": "c1"}}

    def tearDown(self):
        common.CALIBRATION_STATUS = self.original
        shutil.rmtree(self.tmp)

    def write(self, **changes):
        record = {"scorer_version": common.assessment_version(), "scorer_code_sha256": common.assessment_code_sha256(),
                  "samples_sha256": common.samples_sha256(), "images": {"gcc": "g1", "clang": "c1"},
                  "tasks": {self.task["id"]: common.task_sha256(self.task)}, "passed": True, "run_id": "r"}
        record.update(changes)
        common.write_json(common.CALIBRATION_STATUS, record)

    def test_missing_passed_failed(self):
        self.assertEqual(common.calibration_status(self.images, self.task)["status"], "missing")
        self.write()
        self.assertEqual(common.calibration_status(self.images, self.task)["status"], "passed")
        self.write(passed=False)
        self.assertEqual(common.calibration_status(self.images, self.task)["status"], "failed")

    def test_any_fingerprint_change_makes_it_stale(self):
        for change in ({"scorer_code_sha256": "x"}, {"samples_sha256": "x"}, {"scorer_version": "9.9.9"},
                       {"images": {"gcc": "other", "clang": "c1"}}, {"tasks": {self.task["id"]: "x"}}):
            self.write(**change)
            self.assertEqual(common.calibration_status(self.images, self.task)["status"], "stale", change)
