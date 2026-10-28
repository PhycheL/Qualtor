"""建题工具中复核结论相关逻辑的单元测试：python3 -B -m unittest discover -s benchmark/tools/tests"""
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
from unittest.mock import patch

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS), str(TOOLS.parents[1] / "evaluator/assessment"), str(TOOLS.parents[1] / "evaluator/common")]

import bankutil  # noqa: E402


def mutant(mid, ref, probe):
    return {"id": mid, "mutator": "m", "location": {}, "reference_status": [ref, ref], "probe_status": [probe, probe]}


def baseline():
    """a、b 被参考测试杀死；c 参考与探针都幸存（等价候选）；d 幸存但未被探针区分（等价候选）。"""
    return {"mutants": [mutant("a", "killed", "killed"), mutant("b", "killed", "killed"),
                        mutant("c", "survived", "survived"), mutant("d", "survived", "survived")],
            "equivalent": [{"id": "c"}, {"id": "d"}], "unstable": [], "review_needed": [],
            "review": {"status": "pending"},
            "reference": {"killed": 2, "timeout": 0, "total": 2, "m1": 1.0, "threshold": 0.8, "passes": True}}


class ApplyConfirmedTest(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        self.patch = patch.object(bankutil, "MUTANT_REVIEW", self.tmp)
        self.patch.start()

    def tearDown(self):
        self.patch.stop()
        shutil.rmtree(self.tmp)

    def confirm(self, *entries):
        (self.tmp / "t").mkdir(exist_ok=True)
        (self.tmp / "t" / "confirmed.json").write_text(json.dumps(
            {"mutants": [{"id": mid, "verdict": verdict, "evidence": []} for mid, verdict in entries]}))

    def test_no_conclusions_keep_baseline(self):
        original = baseline()
        self.assertEqual(bankutil.apply_confirmed(original, "t"), (original, [], []))

    def test_verified_counterexample_moves_back_into_denominator(self):
        self.confirm(("c", bankutil.NON_EQUIVALENT))
        result, changed, problems = bankutil.apply_confirmed(baseline(), "t")
        self.assertEqual((changed, problems), (["c"], []))
        self.assertEqual([m["id"] for m in result["equivalent"]], ["d"])
        self.assertEqual([m["id"] for m in result["confirmed_non_equivalent"]], ["c"])
        self.assertEqual((result["reference"]["killed"], result["reference"]["total"]), (2, 3))
        self.assertAlmostEqual(result["reference"]["m1"], 2 / 3)
        self.assertFalse(result["reference"]["passes"])
        self.assertEqual(bankutil.apply_confirmed(result, "t")[1], [])   # 再次应用没有改动

    def test_undefined_only_is_excluded_wherever_it_is(self):
        self.confirm(("c", bankutil.NON_EQUIVALENT))
        restored, _, _ = bankutil.apply_confirmed(baseline(), "t")
        # 之后改判为只在未定义行为下不同（D015）：从分母和移回记录中移出，列为不稳定；另一项从等价候选移出
        self.confirm(("c", bankutil.UNDEFINED_ONLY), ("d", bankutil.UNDEFINED_ONLY))
        result, changed, problems = bankutil.apply_confirmed(restored, "t")
        self.assertEqual((changed, problems), (["c", "d"], []))
        self.assertEqual(result["equivalent"], [])
        self.assertNotIn("confirmed_non_equivalent", result)
        self.assertEqual([m["id"] for m in result["unstable"]], ["c", "d"])
        self.assertIn("D015", result["unstable"][0]["reason"])
        self.assertEqual((result["reference"]["total"], result["reference"]["m1"]), (2, 1.0))
        self.assertEqual(bankutil.apply_confirmed(result, "t")[1], [])

    def test_unknown_ids_or_verdicts_are_reported(self):
        self.confirm(("zz", bankutil.NON_EQUIVALENT))
        self.assertIn("不在本次变异集合中", bankutil.apply_confirmed(baseline(), "t")[2][0])
        self.confirm(("c", "maybe"))
        self.assertIn("无法识别", bankutil.apply_confirmed(baseline(), "t")[2][0])


if __name__ == "__main__":
    unittest.main()
