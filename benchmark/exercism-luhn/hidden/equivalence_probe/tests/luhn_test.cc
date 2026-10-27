// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "luhn.h"

namespace {

TEST(Luhn, T001_single_digit_strings_can_not_be_valid) {
    REQUIRE(false == luhn::valid("1"));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(Luhn, T002_a_single_zero_is_invalid) {
    REQUIRE(false == luhn::valid("0"));
}

TEST(Luhn, T003_a_simple_valid_SIN_that_remains_valid_if_reversed) {
    REQUIRE(true == luhn::valid("059"));
}

TEST(Luhn, T004_a_simple_valid_SIN_that_becomes_invalid_if_reversed) {
    REQUIRE(true == luhn::valid("59"));
}

TEST(Luhn, T005_a_valid_Canadian_SIN) {
    REQUIRE(true == luhn::valid("055 444 285"));
}

TEST(Luhn, T006_invalid_Canadian_SIN) {
    REQUIRE(false == luhn::valid("055 444 286"));
}

TEST(Luhn, T007_invalid_credit_card) {
    REQUIRE(false == luhn::valid("8273 1232 7352 0569"));
}

TEST(Luhn, T008_invalid_long_number_with_an_even_remainder) {
    REQUIRE(false == luhn::valid("1 2345 6789 1234 5678 9012"));
}

TEST(Luhn, T009_invalid_long_number_with_a_remainder_divisible_by_5) {
    REQUIRE(false == luhn::valid("1 2345 6789 1234 5678 9013"));
}

TEST(Luhn, T010_valid_number_with_an_even_number_of_digits) {
    REQUIRE(true == luhn::valid("095 245 88"));
}

TEST(Luhn, T011_valid_number_with_an_odd_number_of_spaces) {
    REQUIRE(true == luhn::valid("234 567 891 234"));
}

TEST(Luhn, T012_valid_strings_with_a_non_digit_added_at_the_end_become_inval) {
    REQUIRE(false == luhn::valid("059a"));
}

TEST(Luhn, T013_valid_strings_with_punctuation_included_become_invalid) {
    REQUIRE(false == luhn::valid("055-444-285"));
}

TEST(Luhn, T014_valid_strings_with_symbols_included_become_invalid) {
    REQUIRE(false == luhn::valid("055# 444$ 285"));
}

TEST(Luhn, T015_single_zero_with_space_is_invalid) {
    REQUIRE(false == luhn::valid(" 0"));
}

TEST(Luhn, T016_more_than_a_single_zero_is_valid) {
    REQUIRE(true == luhn::valid("0000 0"));
}

TEST(Luhn, T017_input_digit_9_is_correctly_converted_to_output_digit_9) {
    REQUIRE(true == luhn::valid("091"));
}

TEST(Luhn, T018_very_long_input_is_valid) {
    REQUIRE(true == luhn::valid("9999999999 9999999999 9999999999 9999999999"));
}

TEST(Luhn, T019_valid_luhn_with_an_odd_number_of_digits_and_non_zero_first_d) {
    REQUIRE(true == luhn::valid("109"));
}

TEST(Luhn, T020_using_ascii_value_for_non_doubled_non_digit_isn_t_allowed) {
    REQUIRE(false == luhn::valid("055b 444 285"));
}

TEST(Luhn, T021_using_ascii_value_for_doubled_non_digit_isn_t_allowed) {
    REQUIRE(false == luhn::valid(":9"));
}

TEST(Luhn, T022_non_numeric_non_space_char_in_the_middle_with_a_sum_that_s_d) {
    REQUIRE(false == luhn::valid("59%59"));
}

#endif

}  // namespace
