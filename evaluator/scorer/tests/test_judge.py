import copy
import unittest

import support  # noqa: F401
import judge

TESTS = [{"name": "S.A"}, {"name": "S.B"}, {"name": "S.C"}]


def full(outcomes, returncode=0, timed_out=False, has_json=True):
    return {"returncode": returncode, "timed_out": timed_out, "json": has_json,
            "outcomes": {n: {"outcome": o, "failures": []} for n, o in outcomes.items()} if has_json else None}


class Step3Test(unittest.TestCase):
    def test_usable_full_run(self):
        statuses, problem = judge.step3_statuses(TESTS, full({"S.A": "passed", "S.B": "failed", "S.C": "skipped"}, 1), {})
        self.assertIsNone(problem)
        self.assertEqual(statuses, {"S.A": "passed", "S.B": "failed_on_target", "S.C": "skipped"})

    def test_protocol_mismatch(self):
        statuses, problem = judge.step3_statuses(TESTS, full({"S.A": "passed"}), {})
        self.assertEqual(problem, "protocol_mismatch")

    def test_crashed_run_uses_isolation(self):
        isolation = {"S.A": {"outcome": "passed"}, "S.B": {"outcome": "crashed"}, "S.C": {"outcome": "timed_out"}}
        statuses, problem = judge.step3_statuses(TESTS, full({}, -11, has_json=False), isolation)
        self.assertIsNone(problem)
        self.assertEqual(statuses, {"S.A": "passed", "S.B": "crashed", "S.C": "timed_out"})

    def test_all_without_result(self):
        isolation = {n["name"]: {"outcome": "crashed"} for n in TESTS}
        _, problem = judge.step3_statuses(TESTS, full({}, 0, has_json=False), isolation)
        self.assertEqual(problem, "no_result")

    def test_exit_code_other_than_0_or_1_is_not_trusted(self):
        self.assertFalse(judge.full_run_usable(full({"S.A": "passed"}, returncode=-6)))
        self.assertFalse(judge.full_run_usable(full({"S.A": "passed"}, timed_out=True)))


class StabilityAndStatusTest(unittest.TestCase):
    def test_flaky(self):
        self.assertFalse(judge.is_flaky({"repeat_failures": 0, "shuffle_failures": 0, "isolation_outcome": "passed"}))
        self.assertTrue(judge.is_flaky({"repeat_failures": 1}))
        self.assertTrue(judge.is_flaky({"shuffle_failures": 1}))
        self.assertTrue(judge.is_flaky({"isolation_outcome": "failed"}))

    def record(self, final):
        return {"discovery": {"ok": True, "tests": [{"name": n} for n in final]}, "step3_problem": None,
                "final_statuses": final, "stability": {}}

    def test_artifact_status_order(self):
        built = {"status": "built"}
        self.assertEqual(judge.artifact_status(infra="x"), ("infra_error", "x"))
        self.assertEqual(judge.artifact_status(product_problem="bad"), ("invalid", "artifact_rejected"))
        self.assertEqual(judge.artifact_status(build={"status": "build_failed"}), ("invalid", "build_failed"))
        self.assertEqual(judge.artifact_status(build=built, record={"discovery": {"ok": False}}), ("invalid", "no_result"))
        self.assertEqual(judge.artifact_status(build=built, record={"discovery": {"ok": True, "tests": []}}),
                         ("invalid", "zero_tests"))
        self.assertEqual(judge.artifact_status(build=built, record=self.record({"S.A": "skipped"})),
                         ("invalid", "no_valid_tests"))
        self.assertEqual(judge.artifact_status(build=built, record=self.record({"S.A": "flaky"})), ("invalid", "all_flaky"))
        self.assertEqual(judge.artifact_status(build=built, record=self.record({"S.A": "valid", "S.B": "flaky"})),
                         ("scored", None))

    def test_counts(self):
        record = self.record({"S.A": "valid", "S.B": "flaky", "S.C": "failed_on_target"})
        record["stability"] = {"S.B": {"repeat_failures": 3}}
        counts = judge.test_counts(record, 10)
        self.assertEqual((counts["n_discovered"], counts["n_invalid"], counts["n_passed_1_3"], counts["n_flaky"],
                          counts["n_valid"]), (3, 1, 2, 1, 1))
        self.assertEqual(counts["flaky_failures"], {"S.B": 3})


BASELINE = {"mull": {"config_sha256": "cfg"},
            "mutants": [{"id": m} for m in ("m1", "m2", "m3", "m4", "m5", "m6")],
            "equivalent": [{"id": "m5"}], "unstable": [{"id": "m6"}]}


class MutantsTest(unittest.TestCase):
    def report(self, statuses):
        return [{"id": mid, "status": status} for mid, status in statuses.items()]

    def test_counts_and_exclusions(self):
        report = self.report({"m1": "Killed", "m2": "Survived", "m3": "NoCoverage", "m4": "Timeout",
                              "m5": "Survived", "m6": "Killed"})
        problem, counts, per = judge.evaluate_mutants(report, BASELINE, "cfg")
        self.assertIsNone(problem)
        self.assertEqual((counts["killed"], counts["survived"], counts["not_covered"], counts["timeout"], counts["total"]),
                         (1, 1, 1, 1, 4))
        self.assertEqual(per["m5"], "equivalent")
        self.assertEqual(per["m6"], "unstable")
        self.assertAlmostEqual(judge.m1(counts), 1 / 3)

    def test_mismatch_and_config(self):
        self.assertEqual(judge.evaluate_mutants([], None, "cfg")[0], "missing_mutation_baseline")
        self.assertEqual(judge.evaluate_mutants([], BASELINE, "other")[0], "mull_config_changed")
        problem = judge.evaluate_mutants(self.report({"m1": "Killed"}), BASELINE, "cfg")[0]
        self.assertTrue(problem.startswith("mutant_set_mismatch"))


class VariantTest(unittest.TestCase):
    valid = ["S.A", "S.B"]

    def test_expect_fail(self):
        v = {"id": "x", "expect": "fail"}
        self.assertEqual(judge.variant_outcome(v, False, {}, self.valid)[0], "build_failed")
        self.assertEqual(judge.variant_outcome(v, True, {"S.A": {"outcome": "failed"}}, self.valid)[:2],
                         ("detected", ["S.A"]))
        self.assertEqual(judge.variant_outcome(v, True, {"S.A": {"outcome": "crashed"}}, self.valid)[0], "detected")
        self.assertEqual(judge.variant_outcome(v, True, {"S.A": {"outcome": "timed_out"}}, self.valid)[0], "timeout")
        self.assertEqual(judge.variant_outcome(v, True, {"S.A": {"outcome": "passed"}}, self.valid)[0], "not_detected")

    def test_expect_pass(self):
        v = {"id": "x", "expect": "pass"}
        self.assertIsNotNone(judge.variant_outcome(v, False, {}, self.valid)[2])
        self.assertEqual(judge.variant_outcome(v, True, {"S.B": {"outcome": "failed"}}, self.valid)[:2],
                         ("false_alarm", ["S.B"]))
        self.assertEqual(judge.variant_outcome(v, True, {}, self.valid)[0], "clean")


class MetricsTest(unittest.TestCase):
    def base(self, status="scored", reason=None):
        return {"status": status, "invalid_reason": reason, "build": {"status": "built"},
                "counts": {"tests": {"n_discovered": 4, "n_invalid": 1, "n_passed_1_3": 3, "n_flaky": 1, "n_valid": 2,
                                     "flaky_failures": {"S.C": 5}, "repeats": 10},
                           "mutants": {"killed": 6, "survived": 2, "not_covered": 0, "timeout": 2, "other": 0, "total": 10},
                           "coverage": {"total": {"lines": {"covered": 9, "total": 10},
                                                  "branches": {"covered": 3, "total": 4},
                                                  "functions": {"covered": 1, "total": 1}}}},
                "variants": [{"kind": "handwritten", "outcome": "detected", "failed_tests": ["S.A"]},
                             {"kind": "equivalent", "outcome": "false_alarm", "failed_tests": ["S.B"]}],
                "cost": {"seconds": 1}}

    def test_scored(self):
        m = judge.metrics(self.base())
        self.assertEqual((m["V1"], m["V2"]), (1, 1))
        self.assertAlmostEqual(m["V3"], 0.25)
        self.assertAlmostEqual(m["S1"], 1 / 3)
        self.assertEqual(m["S2"], {"S.C": 0.5})
        self.assertAlmostEqual(m["M1_e2e"], 6 / 8)
        self.assertEqual((m["C1"], m["C2"], m["C3"]), (0.9, 0.75, 1.0))
        self.assertEqual((m["M2"], m["M4"]), (1.0, None))
        self.assertAlmostEqual(m["F1"], 0.5)

    def test_invalid_scores_zero_end_to_end(self):
        m = judge.metrics(self.base("invalid", "build_failed"))
        self.assertEqual((m["M1_e2e"], m["M1_valid"], m["C1"], m["F1"]), (0.0, None, None, None))
        self.assertEqual(judge.metrics(self.base("invalid", "all_flaky"))["V2"], 1)

    def test_stable_view_ignores_timing(self):
        a = dict(self.base(), started_at="t1", finished_at="t2", steps={"x": 1}, tests={"S.A": "valid"})
        b = copy.deepcopy(a)
        b.update(started_at="t3", finished_at="t4", steps={"x": 2})
        self.assertEqual(judge.stable_view(a), judge.stable_view(b))
        b["tests"] = {"S.A": "flaky"}
        self.assertNotEqual(judge.stable_view(a), judge.stable_view(b))


if __name__ == "__main__":
    unittest.main()
