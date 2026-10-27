// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "say.h"

namespace {

TEST(Say, T001_zero) {
    REQUIRE("zero" == say::in_english(0));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(Say, T002_one) {
    REQUIRE("one" == say::in_english(1));
}

TEST(Say, T003_fourteen) {
    REQUIRE("fourteen" == say::in_english(14));
}

TEST(Say, T004_twenty) {
    REQUIRE("twenty" == say::in_english(20));
}

TEST(Say, T005_twenty_two) {
    REQUIRE("twenty-two" == say::in_english(22));
}

TEST(Say, T006_thirty) {
    REQUIRE("thirty" == say::in_english(30));
}

TEST(Say, T007_ninety_nine) {
    REQUIRE("ninety-nine" == say::in_english(99));
}

TEST(Say, T008_one_hundred) {
    REQUIRE("one hundred" == say::in_english(100));
}

TEST(Say, T009_one_hundred_twenty_three) {
    REQUIRE("one hundred twenty-three" == say::in_english(123));
}

TEST(Say, T010_two_hundred) {
    REQUIRE("two hundred" == say::in_english(200));
}

TEST(Say, T011_nine_hundred_ninety_nine) {
    REQUIRE("nine hundred ninety-nine" == say::in_english(999));
}

TEST(Say, T012_one_thousand) {
    REQUIRE("one thousand" == say::in_english(1000));
}

TEST(Say, T013_one_thousand_two_hundred_thirty_four) {
    REQUIRE("one thousand two hundred thirty-four" == say::in_english(1234));
}

TEST(Say, T014_one_million) {
    REQUIRE("one million" == say::in_english(1000000));
}

TEST(Say, T015_one_million_two_thousand_three_hundred_forty_five) {
    REQUIRE("one million two thousand three hundred forty-five" ==
            say::in_english(1002345));
}

TEST(Say, T016_one_billion) {
    REQUIRE("one billion" == say::in_english(1000000000));
}

TEST(Say, T017_a_big_number) {
    REQUIRE(
        "nine hundred eighty-seven billion six hundred fifty-four million "
        "three hundred twenty-one thousand one hundred twenty-three" ==
        say::in_english(987654321123));
}

TEST(Say, T018_numbers_below_zero_are_out_of_range) {
    REQUIRE_THROWS_AS(say::in_english(-1), std::domain_error);
}

TEST(Say, T019_numbers_above_999_999_999_999_are_out_of_range) {
    REQUIRE_THROWS_AS(say::in_english(1000000000000), std::domain_error);
}

#endif

}  // namespace
