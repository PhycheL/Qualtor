// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "armstrong_numbers.h"

namespace {

// Armstrong-numbers exercise test case data version 1.1.0

TEST(ArmstrongNumbers, T001_zero_is_an_armstrong_number) {
    REQUIRE(armstrong_numbers::is_armstrong_number(0));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(ArmstrongNumbers, T002_single_digit_numbers_are_armstrong_numbers) {
    REQUIRE(armstrong_numbers::is_armstrong_number(5));
}

TEST(ArmstrongNumbers, T003_there_are_no_2_digit_armstrong_numbers) {
    REQUIRE_FALSE(armstrong_numbers::is_armstrong_number(10));
}

TEST(ArmstrongNumbers, T004_three_digit_number_that_is_an_armstrong_number) {
    REQUIRE(armstrong_numbers::is_armstrong_number(153));
}

TEST(ArmstrongNumbers, T005_three_digit_number_that_is_not_an_armstrong_number) {
    REQUIRE_FALSE(armstrong_numbers::is_armstrong_number(100));
}

TEST(ArmstrongNumbers, T006_four_digit_number_that_is_an_armstrong_number) {
    REQUIRE(armstrong_numbers::is_armstrong_number(9474));
}

TEST(ArmstrongNumbers, T007_four_digit_number_that_is_not_an_armstrong_number) {
    REQUIRE_FALSE(armstrong_numbers::is_armstrong_number(9475));
}

TEST(ArmstrongNumbers, T008_seven_digit_number_that_is_an_armstrong_number) {
    REQUIRE(armstrong_numbers::is_armstrong_number(9926315));
}

TEST(ArmstrongNumbers, T009_seven_digit_number_that_is_not_an_armstrong_number) {
    REQUIRE_FALSE(armstrong_numbers::is_armstrong_number(9926314));
}
#endif  // !EXERCISM_RUN_ALL_TESTS

}  // namespace
