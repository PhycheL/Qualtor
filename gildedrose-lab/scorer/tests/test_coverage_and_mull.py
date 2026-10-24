import json
import unittest

from support import FIXTURES
import container_steps
import coverage


class CoverageParsingTest(unittest.TestCase):
    """用工具链验收中 gcov 14.2.0 的真实输出核对多文件解析和函数覆盖。"""

    def test_json_counts_lines_branches_functions(self):
        stats = coverage.parse_json_sources(FIXTURES / "gcov_gildedrose_cxx11_final.gcov.json.gz",
                                            {"/repo/cpp/src/GildedRose.cc"})
        source = stats["/repo/cpp/src/GildedRose.cc"]
        self.assertEqual((source["line"]["covered"], source["line"]["total"]), (29, 29))
        self.assertEqual((source["branch_all"]["covered"], source["branch_all"]["total"]), (38, 38))
        self.assertEqual((source["function"]["covered"], source["function"]["total"]), (2, 2))
        self.assertEqual(source["uncovered_functions"], [])

    def test_headers_are_not_counted(self):
        stats = coverage.parse_json_sources(FIXTURES / "gcov_gildedrose_cxx11_final.gcov.json.gz",
                                            {"/repo/cpp/src/GildedRose.cc"})
        self.assertEqual(list(stats), ["/repo/cpp/src/GildedRose.cc"])

    def test_text_header_and_agreement(self):
        path = FIXTURES / "gcov_gildedrose_cxx11_final.gcov"
        self.assertEqual(coverage.text_source(path), "/repo/cpp/src/GildedRose.cc")
        text = coverage.parse_text(path)
        stats = coverage.parse_json_sources(FIXTURES / "gcov_gildedrose_cxx11_final.gcov.json.gz",
                                            {"/repo/cpp/src/GildedRose.cc"})["/repo/cpp/src/GildedRose.cc"]
        for key in ("line", "branch_all", "branch_nonthrow"):
            self.assertEqual(text[key], stats[key])


class MullParsingTest(unittest.TestCase):
    """用工具链验收中 Mull 0.34.2 的真实 Elements 报告核对解析。"""

    def setUp(self):
        self.report = json.loads((FIXTURES / "mull_elements_cxx11_final.json").read_text())

    def test_parse_report(self):
        mutants, problem = container_steps.parse_mull_report(self.report, ["/repo/cpp/src/GildedRose.cc"])
        self.assertIsNone(problem)
        self.assertEqual(len(mutants), 8)
        self.assertTrue(all(m["status"] == "Killed" for m in mutants))
        self.assertTrue(all(m["id"].startswith(m["mutator"] + ":/repo/cpp/src/GildedRose.cc:") for m in mutants))

    def test_unexpected_file_is_rejected(self):
        mutants, problem = container_steps.parse_mull_report(self.report, ["/repo/other.cc"])
        self.assertIsNone(mutants)
        self.assertTrue(problem.startswith("mutated_unexpected_file"))


if __name__ == "__main__":
    unittest.main()
