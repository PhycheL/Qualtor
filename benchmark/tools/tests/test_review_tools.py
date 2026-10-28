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


IR = r'''
@s1 = private constant [24 x i8] c"cxx_x:/repo/src/a.cc:1\00"
define void @f(ptr %p) {
  br label %10

5:
  %6 = call ptr @getenv(ptr @s1)
  %7 = icmp ne ptr %6, null
  br i1 %7, label %8, label %20

8:
  store ptr @"cxx_x:/repo/src/a.cc:1", ptr %p, align 8
  br label %30

10:
  %11 = call ptr @getenv(ptr @s1)
  %12 = icmp ne ptr %11, null
  br i1 %12, label %13, label %5

13:
  store ptr @"cxx_x:/repo/src/a.cc:1.2", ptr %p, align 8
  br label %30

20:
  br label %30

30:
  ret void
}
define void @mull_f_original(ptr %x) {
  call void @g()
  call void @_ZN1SD2Ev(ptr %x)
  ret void
}
define void @"cxx_x:/repo/src/a.cc:1"(ptr %x) {
  call void @_ZN1SD2Ev(ptr %x)
  ret void
}
define void @"cxx_x:/repo/src/a.cc:1.2"(ptr %x) {
  call void @g()
  ret void
}
'''


class MutantIrTest(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        (self.tmp / "a.ll").write_text(IR)
        self.patch = patch.object(bankutil, "MUTANT_REVIEW", self.tmp)
        self.patch.start()

    def tearDown(self):
        self.patch.stop()
        shutil.rmtree(self.tmp)

    def test_first_checked_copy_is_active_and_calls_are_compared_with_original(self):
        import mutant_ir
        report = mutant_ir.analyze(self.tmp / "a.ll", ["cxx_x:/repo/src/a.cc:1", "cxx_y:/repo/src/a.cc:2"])
        self.assertEqual(report[0]["active"], "cxx_x:/repo/src/a.cc:1.2")   # 后定义、先被检查的副本
        self.assertEqual(report[0]["copies"], ["cxx_x:/repo/src/a.cc:1.2", "cxx_x:/repo/src/a.cc:1"])
        self.assertEqual((report[0]["removed_calls"], report[0]["added_calls"]), ({"_ZN1SD2Ev": 1}, {}))
        self.assertIn("problem", report[1])

    def test_resolve_only_clears_destructor_only_deletions(self):
        import mutant_ir
        (self.tmp / "t").mkdir()
        entries = [{"id": i, "reason": "r", "evidence": [], "pending": "待 mutant_ir.py 核对"}
                   for i in ("cxx_x:/repo/src/a.cc:1", "cxx_z:/repo/src/a.cc:3")]
        (self.tmp / "t" / "equivalent.json").write_text(json.dumps({"mutants": entries}))
        report = mutant_ir.analyze(self.tmp / "a.ll", ["cxx_x:/repo/src/a.cc:1"])
        report.append({"id": "cxx_z:/repo/src/a.cc:3", "removed_calls": {"g": 1}, "added_calls": {}, "ir": "a.ll"})
        self.assertEqual(mutant_ir.resolve("t", report, "r1"), ["cxx_x:/repo/src/a.cc:1"])
        data = {m["id"]: m for m in json.loads((self.tmp / "t" / "equivalent.json").read_text())["mutants"]}
        self.assertNotIn("pending", data["cxx_x:/repo/src/a.cc:1"])
        self.assertIn("pending", data["cxx_z:/repo/src/a.cc:3"])        # 删去的不是析构，保留待复核


class ReviewGapsTest(unittest.TestCase):
    def test_pending_conclusions_block_admission(self):
        tmp = Path(tempfile.mkdtemp())
        try:
            with patch.object(bankutil, "MUTANT_REVIEW", tmp):
                (tmp / "t").mkdir()
                (tmp / "t" / "equivalent.json").write_text(json.dumps({"mutants": [
                    {"id": "c", "reason": "r", "evidence": []}, {"id": "d", "reason": "r", "evidence": [], "pending": "x"}]}))
                (tmp / "t" / "confirmed.json").write_text(json.dumps({"mutants": [
                    {"id": "a", "verdict": bankutil.UNDEFINED_ONLY, "evidence": [], "pending": "y"}]}))
                b = baseline()
                b["equivalent"].append({"id": "e"})
                self.assertEqual(bankutil.review_gaps(b, "t"), (["e"], ["d", "a"]))
        finally:
            shutil.rmtree(tmp)


class UbSweepResolveTest(unittest.TestCase):
    def test_only_matching_outcomes_clear_pending(self):
        import ub_sweep
        tmp = Path(tempfile.mkdtemp())
        try:
            with patch.object(bankutil, "MUTANT_REVIEW", tmp):
                (tmp / "t").mkdir()
                mark = "待复核（ub_sweep.py）"
                (tmp / "t" / "equivalent.json").write_text(json.dumps({"mutants": [
                    {"id": "e1", "reason": "r", "evidence": [], "pending": mark},
                    {"id": "e2", "reason": "r", "evidence": [], "pending": mark}]}))
                (tmp / "t" / "confirmed.json").write_text(json.dumps({"mutants": [
                    {"id": "u1", "verdict": bankutil.UNDEFINED_ONLY, "evidence": [], "pending": mark}]}))
                report = [{"id": "e1", "outcome": "same_output"}, {"id": "e2", "outcome": "undefined_behavior"},
                          {"id": "u1", "outcome": "undefined_behavior"}]
                self.assertEqual(ub_sweep.resolve("t", report, "r1"), ["e1", "u1"])
                eq = {m["id"]: m for m in json.loads((tmp / "t" / "equivalent.json").read_text())["mutants"]}
                self.assertIn("pending", eq["e2"])          # 结果与记录的等价结论不一致，留待复核人处理
                self.assertEqual(eq["e1"]["evidence"], ["runs/r1/ub-sweep.md", "runs/r1/ub-sweep.json"])
        finally:
            shutil.rmtree(tmp)
