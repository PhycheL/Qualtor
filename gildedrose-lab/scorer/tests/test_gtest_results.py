import unittest

from support import FIXTURES
import gtest_results


class GtestResultsTest(unittest.TestCase):
    def test_list_includes_disabled_and_parameterized_tests(self):
        tests = gtest_results.parse_list(gtest_results.load_json(FIXTURES / "gtest_1_12_1_list.json"))
        names = [t["name"] for t in tests]
        self.assertEqual(names, ["Exp.Passes", "Exp.Fails", "Exp.Skips", "Exp.DISABLED_Disabled",
                                 "DISABLED_ExpSuite.InDisabledSuite", "Inst/P.Param/0", "Inst/P.Param/1"])

    def test_run_outcomes(self):
        outcomes = gtest_results.parse_run(gtest_results.load_json(FIXTURES / "gtest_1_12_1_run.json"))
        simple = {name: o["outcome"] for name, o in outcomes.items()}
        self.assertEqual(simple, {"Exp.Passes": "passed", "Exp.Fails": "failed", "Exp.Skips": "skipped",
                                  "Exp.DISABLED_Disabled": "disabled", "DISABLED_ExpSuite.InDisabledSuite": "disabled",
                                  "Inst/P.Param/0": "passed", "Inst/P.Param/1": "passed"})
        self.assertIn("Expected equality", outcomes["Exp.Fails"]["failures"][0])

    def test_missing_or_broken_json_is_no_result(self):
        self.assertIsNone(gtest_results.load_json(FIXTURES / "does-not-exist.json"))
        self.assertIsNone(gtest_results.parse_list({"unexpected": 1}))
        self.assertIsNone(gtest_results.parse_run(None))

    def test_stdout_ignores_summary_lines(self):
        text = (FIXTURES / "gtest_1_12_1_run.stdout").read_text()
        parsed = gtest_results.parse_stdout(text)
        self.assertEqual(parsed["finished"], {"Exp.Passes": "passed", "Exp.Fails": "failed", "Exp.Skips": "skipped",
                                              "Inst/P.Param/0": "passed", "Inst/P.Param/1": "passed"})
        self.assertIsNone(parsed["in_progress"])

    def test_stdout_finds_test_running_at_crash(self):
        text = "[ RUN      ] A.First\n[       OK ] A.First (0 ms)\n[ RUN      ] A.Second\n"
        parsed = gtest_results.parse_stdout(text)
        self.assertEqual(parsed["finished"], {"A.First": "passed"})
        self.assertEqual(parsed["in_progress"], "A.Second")

    def test_filter(self):
        self.assertEqual(gtest_results.gtest_filter(["A.B", "Inst/P.Q/0"]), "A.B:Inst/P.Q/0")


if __name__ == "__main__":
    unittest.main()
