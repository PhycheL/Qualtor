import unittest

import support  # noqa: F401
import common
import prepare_task


def run(statuses, variants=None):
    return {"raw_mutants": [{"id": mid, "mutator": "m", "status": status, "location": {}} for mid, status in statuses.items()],
            "mull_config_sha256": "cfg", "variants": variants or []}


class BaselineTest(unittest.TestCase):
    def setUp(self):
        self.task = common.load_task("gildedrose-update-quality")

    def test_classification_and_reference_strength(self):
        reference = [run({"a": "Killed", "b": "Killed", "c": "Survived", "d": "Killed", "e": "Timeout", "f": "Killed"}),
                     run({"a": "Killed", "b": "Killed", "c": "Survived", "d": "Survived", "e": "Timeout", "f": "Killed"})]
        probe = [run({"a": "Killed", "b": "Survived", "c": "Killed", "d": "Killed", "e": "Timeout", "f": "NoCoverage"}),
                 run({"a": "Killed", "b": "Survived", "c": "Killed", "d": "Killed", "e": "Timeout", "f": "NoCoverage"})]
        draft = prepare_task.build_baseline(self.task, {"reference": reference, "probe": probe}, "text", {}, "run")
        self.assertEqual([m["id"] for m in draft["unstable"]], ["d"])          # 参考测试两次结果不同
        self.assertEqual([m["id"] for m in draft["equivalent"]], ["b", "f"])   # 探针区分不出
        self.assertEqual([m["id"] for m in draft["review_needed"]], ["e"])     # 探针超时
        # 分母：a、c、e；参考测试杀死 a，e 超时不计入；M1 = 1 / (3 - 1)
        self.assertEqual((draft["reference"]["killed"], draft["reference"]["total"], draft["reference"]["timeout"]),
                         (1, 3, 1))
        self.assertAlmostEqual(draft["reference"]["m1"], 0.5)
        self.assertFalse(draft["reference"]["passes"])
        self.assertEqual(draft["review"]["status"], "pending")

    def test_inconsistent_mutant_sets_stop(self):
        with self.assertRaises(SystemExit):
            prepare_task.build_baseline(self.task, {"reference": [run({"a": "Killed"})],
                                                    "probe": [run({"b": "Killed"})]}, "text", {}, "run")

    def test_admission(self):
        variants = [{"id": "eq-01", "expect": "pass", "outcome": "false_alarm"},
                    {"id": "hw-01", "expect": "fail", "outcome": "detected"}]
        problems = prepare_task.admission(self.task, {"reference": [run({}, variants)], "probe": []})
        self.assertEqual(problems, ["reference 在 eq-01 上为 false_alarm，应为 clean"])


if __name__ == "__main__":
    unittest.main()
