#!/usr/bin/env python3
"""重建 GildedRose 开发题的校准样本：写测试文件、期望结果、固定的假成本记录，并冻结 manifest。

校准样本是评分器的验收标准。修改样本（包括参考强测试集变化后重建）要升评分器版本并重新校准。
用法：python3 evaluator/scorer/calibration/gildedrose-update-quality/build_samples.py
"""
import json
from pathlib import Path
import shutil
import sys

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parents[1]))
from common import REPO, freeze_product  # noqa: E402

REFERENCE = REPO / "benchmark/gildedrose-update-quality/hidden/reference_tests/reference_tests.cc"
FROZEN_AT = "2026-10-24T00:00:00+00:00"
COST = {"tokens": {"input": 0, "output": 0}, "seconds": 0, "model_calls": 0, "repair_rounds": 0,
        "note": "校准样本没有生成过程，成本为固定的假数据"}

HEADER = """#include "GildedRose.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {

Item updateOnce(const std::string& name, int sellIn, int quality) {
    std::vector<Item> items(1, Item(name, sellIn, quality));
    GildedRose app(items);
    app.updateQuality();
    return items[0];
}

}  // namespace
"""

ORIGINAL_HELPER = """void expectItem(const Item& item, const std::string& name, int sellIn, int quality) {
    EXPECT_EQ(name, item.name);
    EXPECT_EQ(sellIn, item.sellIn);
    EXPECT_EQ(quality, item.quality);
}"""


def derived(reference, comment, helper=None, replacements=(), after_gtest=None):
    text = reference
    assert ORIGINAL_HELPER in text
    if helper:
        text = text.replace(ORIGINAL_HELPER, helper)
    for old, new in replacements:
        assert old in text, old
        text = text.replace(old, new)
    if after_gtest:
        text = text.replace("#include <gtest/gtest.h>\n", "#include <gtest/gtest.h>\n" + after_gtest, 1)
    lines = text.splitlines(keepends=True)
    body = "".join(line for line in lines if not line.startswith("// "))  # 去掉参考测试的文件头说明
    return comment + body


def samples(reference):
    expect_ref = {"eq-02": "clean", "hw-01": "detected"}
    return {
        "CAL-01": {
            "description": "测试文件里没有任何 TEST",
            "files": {"tests/empty_suite.cc": "// 校准样本 CAL-01：没有任何 TEST。\n#include \"GildedRose.h\"\n\n#include <gtest/gtest.h>\n"},
            "expected": {"hard": {"status": "invalid", "invalid_reason": "zero_tests"}}},
        "CAL-02": {
            "description": "所有测试都调用 GTEST_SKIP()",
            "files": {"tests/all_skipped.cc": "// 校准样本 CAL-02：所有测试都跳过。\n" + HEADER + """
TEST(CalibrationSkipped, First) {
    GTEST_SKIP() << "skipped on purpose";
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}

TEST(CalibrationSkipped, Second) {
    GTEST_SKIP() << "skipped on purpose";
}
"""},
            "expected": {"hard": {"status": "invalid", "invalid_reason": "no_valid_tests", "tests_default": "skipped"}}},
        "CAL-03": {
            "description": "所有测试名带 DISABLED_ 前缀",
            "files": {"tests/all_disabled.cc": "// 校准样本 CAL-03：所有测试都被禁用。\n" + HEADER + """
TEST(CalibrationDisabled, DISABLED_First) {
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}

TEST(DISABLED_CalibrationDisabledSuite, Second) {
    EXPECT_EQ(1, updateOnce("Aged Brie", 2, 0).quality);
}
"""},
            "expected": {"hard": {"status": "invalid", "invalid_reason": "no_valid_tests", "tests_default": "disabled"}}},
        "CAL-04": {
            "description": "自带 main，直接 return 0，不运行测试",
            "files": {"tests/custom_main.cc": "// 校准样本 CAL-04：自带 main 直接返回 0。\n" + HEADER + """
TEST(CalibrationCustomMain, NeverRuns) {
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}

int main() {
    return 0;
}
"""},
            "expected": {"hard": {"status": "invalid", "invalid_reason": "no_result"}}},
        "CAL-05": {
            "description": "在静态初始化中调用 std::exit(0)",
            "files": {"tests/early_exit.cc": "// 校准样本 CAL-05：静态初始化阶段就退出进程。\n#include <cstdlib>\n\n" + HEADER + """
namespace {

struct EarlyExit {
    EarlyExit() { std::exit(0); }
};

EarlyExit earlyExit;

}  // namespace

TEST(CalibrationEarlyExit, NeverRuns) {
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}
"""},
            "expected": {"hard": {"status": "invalid", "invalid_reason": "no_result"}}},
        "CAL-06": {
            "description": "在测试文件里重新定义被测函数",
            "files": {"tests/redefine_target.cc": "// 校准样本 CAL-06：重新定义 GildedRose::updateQuality()，期望链接失败。\n" + HEADER + """
void GildedRose::updateQuality() {}

TEST(CalibrationRedefinition, AlwaysPasses) {
    EXPECT_EQ(20, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}
"""},
            "expected": {"hard": {"status": "invalid", "invalid_reason": "build_failed"}}},
        "CAL-07": {
            "description": "参考强测试集，加一个断言值故意写错的测试",
            "reference_copy": True,
            "files": {"tests/wrong_expectation.cc": "// 校准样本 CAL-07：断言值故意写错（实际为 19）。\n" + HEADER + """
TEST(CalibrationWrongExpectation, ExpectedValueIsWrong) {
    EXPECT_EQ(18, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}
"""},
            "expected": {"hard": {"status": "scored", "tests_default": "valid", "variants": expect_ref,
                                  "tests": {"CalibrationWrongExpectation.ExpectedValueIsWrong": "failed_on_target"}}}},
        "CAL-08": {
            "description": "参考强测试集，加一个空指针解引用的测试",
            "reference_copy": True,
            "files": {"tests/crash.cc": "// 校准样本 CAL-08：空指针解引用，进程崩溃。\n" + HEADER + """
TEST(CalibrationCrash, NullDereference) {
    int* volatile pointer = 0;
    *pointer = 42;
}
"""},
            "expected": {"hard": {"status": "scored", "tests_default": "valid", "variants": expect_ref,
                                  "tests": {"CalibrationCrash.NullDereference": "crashed"}}}},
        "CAL-09": {
            "description": "一个正常测试，加一个死循环的测试",
            "files": {"tests/hang.cc": "// 校准样本 CAL-09：死循环测试应判为超时；只放两个测试，缩短整体运行的超时等待。\n" + HEADER + """
TEST(CalibrationHang, NormalTest) {
    EXPECT_EQ(23, updateOnce("Backstage passes to a TAFKAL80ETC concert", 5, 20).quality);
}

TEST(CalibrationHang, InfiniteLoop) {
    volatile bool keepRunning = true;
    while (keepRunning) {
    }
}
"""},
            "expected": {"hard": {"status": "scored", "variants": expect_ref,
                                  "tests": {"CalibrationHang.NormalTest": "valid",
                                            "CalibrationHang.InfiniteLoop": "timed_out"}}}},
        "CAL-10": {
            "description": "两个测试共享全局变量，后一个依赖前一个先运行",
            "reference_copy": True,
            "files": {"tests/order_dependency.cc": "// 校准样本 CAL-10：B 依赖 A 先运行，单独运行或乱序时失败。\n" + HEADER + """
namespace {

bool g_inventoryPrepared = false;

}  // namespace

TEST(CalibrationOrder, APreparesSharedState) {
    g_inventoryPrepared = true;
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}

TEST(CalibrationOrder, BDependsOnSharedState) {
    EXPECT_TRUE(g_inventoryPrepared);
}
"""},
            "expected": {"hard": {"status": "scored", "tests_default": "valid", "variants": expect_ref,
                                  "tests": {"CalibrationOrder.BDependsOnSharedState": "flaky"}},
                         "relations": [{"metric": "S1", "op": ">", "value": 0}]}},
        "CAL-11": {
            "description": "时好时坏的测试：用工作目录中的计数文件确定性地模拟，第 1 次通过、之后偶数次失败",
            "reference_copy": True,
            "files": {"tests/alternating.cc": "// 校准样本 CAL-11：确定性地模拟时好时坏。\n// 评分器在同一个工作目录里按固定顺序运行测试，所以每次评分的失败次数相同。\n#include <fstream>\n\n" + HEADER + """
TEST(CalibrationFlaky, FailsOnEveryOtherRun) {
    int count = 0;
    {
        std::ifstream in("qualtor_calibration_counter.txt");
        if (in) {
            in >> count;
        }
    }
    ++count;
    {
        std::ofstream out("qualtor_calibration_counter.txt");
        out << count;
    }
    EXPECT_NE(0, count % 2) << "run " << count;
}
"""},
            "expected": {"hard": {"status": "scored", "tests_default": "valid", "variants": expect_ref,
                                  "tests": {"CalibrationFlaky.FailsOnEveryOtherRun": "flaky"}},
                         "relations": [{"metric": "S2_max", "op": "between", "range": [0.2, 0.8]}]}},
        "CAL-12": {
            "description": "与参考强测试集相同的输入，只调用、不断言",
            "files": {"tests/no_assertions.cc": derived(
                reference, "// 校准样本 CAL-12：由参考强测试集改写，保留全部输入，去掉所有断言。\n",
                helper="""void expectItem(const Item& item, const std::string& name, int sellIn, int quality) {
    (void)item;
    (void)name;
    (void)sellIn;
    (void)quality;
}""",
                replacements=[("    EXPECT_TRUE(items.empty());\n", "    (void)items.empty();\n"),
                              ("    ASSERT_EQ(5u, items.size());\n", "    (void)items.size();\n")])},
            "expected": {"hard": {"status": "scored", "tests_default": "valid",
                                  "variants": {"eq-02": "clean", "hw-01": "not_detected"}},
                         "relations": [{"metric": "M1_e2e", "op": "<=", "ref": "CAL-15", "factor": 0.2},
                                       {"metric": "C1", "op": "abs_diff_le", "ref": "CAL-15", "value": 0.05}]}},
        "CAL-13": {
            "description": "参考强测试集原样，但把断言宏定义为空",
            "files": {"tests/neutralized_macros.cc": derived(
                reference, "// 校准样本 CAL-13：断言写法正常，但断言宏被重新定义为空。\n",
                after_gtest="""
#undef EXPECT_EQ
#define EXPECT_EQ(expected, actual) ((void)(expected), (void)(actual))
#undef EXPECT_TRUE
#define EXPECT_TRUE(condition) ((void)(condition))
#undef ASSERT_EQ
#define ASSERT_EQ(expected, actual) ((void)(expected), (void)(actual))
""")},
            "expected": {"hard": {"status": "scored", "tests_default": "valid",
                                  "variants": {"eq-02": "clean", "hw-01": "not_detected"}},
                         "relations": [{"metric": "M1_e2e", "op": "<=", "ref": "CAL-15", "factor": 0.2}]}},
        "CAL-14": {
            "description": "参考强测试集，只断言 sellIn，不检查质量",
            "files": {"tests/sellin_only.cc": derived(
                reference, "// 校准样本 CAL-14：由参考强测试集改写，只断言 sellIn。\n",
                helper="""void expectItem(const Item& item, const std::string& name, int sellIn, int quality) {
    (void)name;
    (void)quality;
    EXPECT_EQ(sellIn, item.sellIn);
}""")},
            "expected": {"hard": {"status": "scored", "tests_default": "valid",
                                  "variants": {"eq-02": "clean", "hw-01": "not_detected"}},
                         "relations": [{"metric": "M1_e2e", "op": ">", "ref": "CAL-12"},
                                       {"metric": "M1_e2e", "op": ">", "ref": "CAL-13"},
                                       {"metric": "M1_e2e", "op": "<", "ref": "CAL-15"}]}},
        "CAL-15": {
            "description": "参考强测试集原样",
            "reference_copy": True,
            "files": {},
            "expected": {"hard": {"status": "scored", "tests_default": "valid", "variants": expect_ref},
                         "relations": [{"metric": "M1_valid", "op": ">=", "value": 0.8},
                                       {"metric": "S1", "op": "==", "value": 0}]}},
        "CAL-16": {
            "description": "参考强测试集，加两条测试：一条断言输入域外但行为确定的结果（Aged Brie 质量 60 保持 60），"
                           "一条依赖有符号溢出（普通商品 sellIn 为 INT_MIN）",
            "reference_copy": True,
            "files": {"tests/out_of_domain.cc": "// 校准样本 CAL-16：域外但行为确定的断言不应误报；"
                      "依赖有符号溢出（未定义行为）的断言在等价版本 eq-02 上应误报（D011）。\n#include <climits>\n" + HEADER + """
TEST(CalibrationDomain, AgedBrieAboveFiftyStaysUnchanged) {
    EXPECT_EQ(60, updateOnce("Aged Brie", 5, 60).quality);
}

TEST(CalibrationUndefined, SellInWrapsAroundAtIntMin) {
    const Item item = updateOnce("+5 Dexterity Vest", INT_MIN, 10);
    EXPECT_EQ(INT_MAX, item.sellIn);
    EXPECT_EQ(9, item.quality);
}
"""},
            "expected": {"hard": {"status": "scored", "tests_default": "valid",
                                  "variants": {"eq-02": "false_alarm", "hw-01": "detected"},
                                  "variant_failed_tests": {"eq-02": ["CalibrationUndefined.SellInWrapsAroundAtIntMin"]}}}},
    }


def main():
    reference = REFERENCE.read_text()
    for sample_id, spec in samples(reference).items():
        sample = HERE / sample_id
        if sample.exists():
            shutil.rmtree(sample)
        tests = sample / "final" / "tests"
        tests.mkdir(parents=True)
        if spec.get("reference_copy"):
            shutil.copy2(REFERENCE, tests / "reference_tests.cc")
        for rel, text in spec["files"].items():
            (sample / "final" / rel).write_text(text)
        freeze_product(sample / "final", frozen_at=FROZEN_AT)
        (sample / "generation").mkdir()
        (sample / "generation" / "cost.json").write_text(json.dumps(COST, ensure_ascii=False, indent=2) + "\n")
        expected = {"sample": sample_id, "description": spec["description"],
                    "reference_copy": "tests/reference_tests.cc" if spec.get("reference_copy") else None,
                    **spec["expected"]}
        (sample / "expected.json").write_text(json.dumps(expected, ensure_ascii=False, indent=2) + "\n")
        print(sample_id, sorted(p.name for p in tests.iterdir()))


if __name__ == "__main__":
    main()
