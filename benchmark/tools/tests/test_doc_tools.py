"""文档辅助工具：题库事实只读生成、相对链接与锚点检查。"""
from pathlib import Path
import sys
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import bank_facts  # noqa: E402
import check_doc_links  # noqa: E402


class BankFactsTest(unittest.TestCase):
    def test_facts_are_consistent_and_read_only(self):
        facts = bank_facts.collect()
        self.assertEqual(sum(facts["tiers"].values()), facts["total_tasks"])
        self.assertEqual(facts["legacy_tasks"] + facts["new_tasks"], facts["total_tasks"])
        caps = facts["capabilities"]
        self.assertEqual(caps["linking_tasks"]["count"],
                         len(set().union(*map(set, caps["linking_tasks"]["by_library"].values()))))
        self.assertNotIn("Boost::headers", str(caps["linking_tasks"]["by_library"]))
        for tid, info in facts["new_tasks_detail"].items():
            if info["mutation_applicable"]:
                self.assertEqual(info["denominator"], info["mutants_reported"] - info["equivalent"] - info["unstable"], tid)
        # 渲染不改变数据，且不同格式的事实相同。
        self.assertIn(f"{facts['total_tasks']} 题", bank_facts.markdown(facts))


class LinkCheckTest(unittest.TestCase):
    def test_slug_follows_github_rules(self):
        self.assertEqual(check_doc_links.slug("D020 第三方构建环境与代码生成（步骤 C）"), "d020-第三方构建环境与代码生成步骤-c")
        self.assertEqual(check_doc_links.slug("7. 后续工作与待定事项"), "7-后续工作与待定事项")
        self.assertEqual(check_doc_links.slug("`run.py` 与 **结果**"), "runpy-与-结果")

    def test_missing_files_and_anchors_are_reported(self):
        with tempfile.TemporaryDirectory(dir=check_doc_links.REPO) as temp:
            root = Path(temp)
            (root / "a.md").write_text("# 标题\n\n## 重复\n\n## 重复\n\n[好](b.md#第二节) [同文件](#重复-1)\n"
                                       "[坏锚点](b.md#没有) [缺文件](c.md) [外部](https://example.com)\n"
                                       "```\n[代码块](不检查.md)\n```\n")
            (root / "b.md").write_text("# 第二节\n")
            rel = str((root / "a.md").relative_to(check_doc_links.REPO))
            total, problems, missing = check_doc_links.check([rel])
            self.assertEqual(total, 4)
            self.assertEqual(len(problems), 2)
            self.assertTrue(any("锚点不存在 b.md#没有" in p for p in problems))
            self.assertTrue(any("目标不存在 c.md" in p for p in problems))
            self.assertEqual(missing, [])


if __name__ == "__main__":
    unittest.main()
