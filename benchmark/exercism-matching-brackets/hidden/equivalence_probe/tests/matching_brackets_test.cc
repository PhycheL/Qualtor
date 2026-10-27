// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "matching_brackets.h"

namespace {

TEST(MatchingBrackets, T001_paired_square_brackets) {
    REQUIRE(matching_brackets::check("[]"));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(MatchingBrackets, T002_empty_string) {
    REQUIRE(matching_brackets::check(""));
}

TEST(MatchingBrackets, T003_unpaired_brackets) {
    REQUIRE(!matching_brackets::check("[["));
}

TEST(MatchingBrackets, T004_wrong_ordered_brackets) {
    REQUIRE(!matching_brackets::check("}{"));
}

TEST(MatchingBrackets, T005_wrong_closing_bracket) {
    REQUIRE(!matching_brackets::check("{]"));
}

TEST(MatchingBrackets, T006_paired_with_whitespace) {
    REQUIRE(matching_brackets::check("{ }"));
}

TEST(MatchingBrackets, T007_partially_paired_brackets) {
    REQUIRE(!matching_brackets::check("{[])"));
}

TEST(MatchingBrackets, T008_simple_nested_brackets) {
    REQUIRE(matching_brackets::check("{[]}"));
}

TEST(MatchingBrackets, T009_several_paired_brackets) {
    REQUIRE(matching_brackets::check("{}[]"));
}

TEST(MatchingBrackets, T010_paired_nested_brackets) {
    REQUIRE(matching_brackets::check("([{}({}[])])"));
}

TEST(MatchingBrackets, T011_unopened_closing_brackets) {
    REQUIRE(!matching_brackets::check("{[)][]}"));
}

TEST(MatchingBrackets, T012_unpaired_nested_brackets) {
    REQUIRE(!matching_brackets::check("([{])"));
}

TEST(MatchingBrackets, T013_paired_wrong_nested_brackets) {
    REQUIRE(!matching_brackets::check("[({]})"));
}

TEST(MatchingBrackets, T014_paired_and_wrong_nested_brackets_but_innermost_are_correct) {
    REQUIRE(!matching_brackets::check("[({}])"));
}

TEST(MatchingBrackets, T015_paired_incomplete_brackets) {
    REQUIRE(!matching_brackets::check("{}["));
}

TEST(MatchingBrackets, T016_too_many_closing_brackets) {
    REQUIRE(!matching_brackets::check("[]]"));
}

TEST(MatchingBrackets, T017_early_unexpected_brackets) {
    REQUIRE(!matching_brackets::check(")()"));
}

TEST(MatchingBrackets, T018_early_mismatched_brackets) {
    REQUIRE(!matching_brackets::check("{)()"));
}

TEST(MatchingBrackets, T019_math_expression) {
    REQUIRE(matching_brackets::check("(((185 + 223.85) * 15) - 543)/2"));
}

TEST(MatchingBrackets, T020_complex_latex_expression) {
    REQUIRE(matching_brackets::check(
        "\\left(\\begin{array}{cc} \\frac{1}{3} & x\\\\ \\mathrm{e}^{x} &... "
        "x^2 \\end{array}\\right)"));
}
#endif

}  // namespace
