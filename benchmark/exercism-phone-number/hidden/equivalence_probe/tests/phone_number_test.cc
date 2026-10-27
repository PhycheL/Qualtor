// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "phone_number.h"

namespace {

TEST(PhoneNumber, T001_cleans_the_number) {
    REQUIRE("2234567890" ==
            phone_number::phone_number("(223) 456-7890").number());
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(PhoneNumber, T002_cleans_numbers_with_dots) {
    REQUIRE("2234567890" ==
            phone_number::phone_number("223.456.7890").number());
}

TEST(PhoneNumber, T003_cleans_numbers_with_multiple_spaces) {
    REQUIRE("2234567890" ==
            phone_number::phone_number("223 456   7890   ").number());
}

TEST(PhoneNumber, T004_invalid_when_9_digits) {
    REQUIRE_THROWS_AS(phone_number::phone_number("123456789"),
                      std::domain_error);
}

TEST(PhoneNumber, T005_invalid_when_11_digits_does_not_start_with_a_1) {
    REQUIRE_THROWS_AS(phone_number::phone_number("22234567890"),
                      std::domain_error);
}

TEST(PhoneNumber, T006_valid_when_11_digits_and_starting_with_1) {
    REQUIRE("2234567890" == phone_number::phone_number("12234567890").number());
}

TEST(PhoneNumber, T007_valid_when_11_digits_and_starting_with_1_even_with_punctuati) {
    REQUIRE("2234567890" ==
            phone_number::phone_number("+1 (223) 456-7890").number());
}

TEST(PhoneNumber, T008_invalid_when_more_than_11_digits) {
    REQUIRE_THROWS_AS(phone_number::phone_number("321234567890"),
                      std::domain_error);
}

TEST(PhoneNumber, T009_invalid_with_letters) {
    REQUIRE_THROWS_AS(phone_number::phone_number("123-abc-7890"),
                      std::domain_error);
}

TEST(PhoneNumber, T010_invalid_with_punctuation) {
    REQUIRE_THROWS_AS(phone_number::phone_number("123-@:!-7890"),
                      std::domain_error);
}

TEST(PhoneNumber, T011_invalid_if_area_code_starts_with_0) {
    REQUIRE_THROWS_AS(phone_number::phone_number("(023) 456-7890"),
                      std::domain_error);
}

TEST(PhoneNumber, T012_invalid_if_area_code_starts_with_1) {
    REQUIRE_THROWS_AS(phone_number::phone_number("(123) 456-7890"),
                      std::domain_error);
}

TEST(PhoneNumber, T013_invalid_if_exchange_code_starts_with_0) {
    REQUIRE_THROWS_AS(phone_number::phone_number("(223) 056-7890"),
                      std::domain_error);
}

TEST(PhoneNumber, T014_invalid_if_exchange_code_starts_with_1) {
    REQUIRE_THROWS_AS(phone_number::phone_number("(223) 156-7890"),
                      std::domain_error);
}

TEST(PhoneNumber, T015_invalid_if_area_code_starts_with_0_on_valid_11_digit_number) {
    REQUIRE_THROWS_AS(phone_number::phone_number("1 (023) 456-7890"),
                      std::domain_error);
}

TEST(PhoneNumber, T016_invalid_if_area_code_starts_with_1_on_valid_11_digit_number) {
    REQUIRE_THROWS_AS(phone_number::phone_number("1 (123) 456-7890"),
                      std::domain_error);
}

TEST(PhoneNumber, T017_invalid_if_exchange_code_starts_with_0_on_valid_11_digit_num) {
    REQUIRE_THROWS_AS(phone_number::phone_number("1 (223) 056-7890"),
                      std::domain_error);
}

TEST(PhoneNumber, T018_invalid_if_exchange_code_starts_with_1_on_valid_11_digit_num) {
    REQUIRE_THROWS_AS(phone_number::phone_number("1 (223) 156-7890"),
                      std::domain_error);
}

#endif

}  // namespace
