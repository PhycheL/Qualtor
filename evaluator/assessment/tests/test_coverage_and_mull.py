import json
from pathlib import Path
import tempfile
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


class CoverageMergeTest(unittest.TestCase):
    """2026-10-27 题库标定中 tennis-refactoring-4 的真实 gcov 14.2.0 输出：虚析构函数的 D0、D2 两个符号共用第 26 行。"""

    SOURCE = "/repo/src/tennis4.cc"

    def test_json_merges_symbol_variants_of_one_line(self):
        stats = coverage.parse_json_sources(FIXTURES / "gcov_tennis4_dtor_variants.gcov.json.gz", {self.SOURCE})[self.SOURCE]
        self.assertEqual((stats["line"]["covered"], stats["line"]["total"]), (79, 79))
        self.assertEqual((stats["function"]["covered"], stats["function"]["total"]), (24, 24))
        self.assertEqual(stats["uncovered_functions"], [])

    def test_text_uses_merged_listing_and_agrees_with_json(self):
        path = FIXTURES / "gcov_tennis4_dtor_variants.gcov"
        text = coverage.parse_text(path)
        self.assertNotIn(26, text["uncovered_lines"])
        stats = coverage.parse_json_sources(FIXTURES / "gcov_tennis4_dtor_variants.gcov.json.gz", {self.SOURCE})[self.SOURCE]
        for key in ("line", "branch_all", "branch_nonthrow"):
            self.assertEqual(text[key], stats[key])

    def test_source_without_executable_code_is_recognised_by_gcno(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp = Path(tmp).resolve()
            prefix, objects = tmp / "prefix", tmp / "build" / "obj"
            gcda = prefix / str(objects).lstrip("/") / "repo/src/Teller.cpp.gcda"
            gcda.parent.mkdir(parents=True)
            gcda.write_bytes(b"")
            (objects / "repo/src").mkdir(parents=True)
            (objects / "repo/src/ReceiptPrinter.cpp.gcno").write_bytes(b"")
            sources = {"/repo/src/Teller.cpp", "/repo/src/ReceiptPrinter.cpp", "/repo/src/Missing.cpp"}
            empty = coverage.empty_targets(prefix, [gcda], sources, ["/repo/src/Missing.cpp", "/repo/src/ReceiptPrinter.cpp"])
            self.assertEqual(empty, ["/repo/src/ReceiptPrinter.cpp"])
        stats = coverage.no_code_stats()
        self.assertEqual((stats["line"]["total"], stats["function"]["total"]), (0, 0))
        self.assertTrue(stats["no_executable_code"])


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
