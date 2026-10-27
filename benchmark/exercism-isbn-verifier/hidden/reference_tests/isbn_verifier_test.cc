// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "isbn_verifier.h"

namespace {

TEST(IsbnVerifier, T001_valid_isbn) { REQUIRE(isbn_verifier::is_valid("3-598-21508-8")); }

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(IsbnVerifier, T002_invalid_isbn_check_digit) {
    REQUIRE_FALSE(isbn_verifier::is_valid("3-598-21508-9"));
}

TEST(IsbnVerifier, T003_valid_isbn_with_a_check_digit_of_10) {
    REQUIRE(isbn_verifier::is_valid("3-598-21507-X"));
}

TEST(IsbnVerifier, T004_check_digit_is_a_character_other_than_x) {
    REQUIRE_FALSE(isbn_verifier::is_valid("3-598-21507-A"));
}

TEST(IsbnVerifier, T005_invalid_check_digit_in_isbn_is_not_treated_as_zero) {
    REQUIRE_FALSE(isbn_verifier::is_valid("4-598-21507-B"));
}

TEST(IsbnVerifier, T006_invalid_character_in_isbn_is_not_treated_as_zero) {
    REQUIRE_FALSE(isbn_verifier::is_valid("3-598-P1581-X"));
}

TEST(IsbnVerifier, T007_x_is_only_valid_as_a_check_digit) {
    REQUIRE_FALSE(isbn_verifier::is_valid("3-598-2X507-9"));
}

TEST(IsbnVerifier, T008_valid_isbn_without_separating_dashes) {
    REQUIRE(isbn_verifier::is_valid("3598215088"));
}

TEST(IsbnVerifier, T009_isbn_without_separating_dashes_and_x_as_check_digit) {
    REQUIRE(isbn_verifier::is_valid("359821507X"));
}

TEST(IsbnVerifier, T010_isbn_without_check_digit_and_dashes) {
    REQUIRE_FALSE(isbn_verifier::is_valid("359821507"));
}

TEST(IsbnVerifier, T011_too_long_isbn_and_no_dashes) {
    REQUIRE_FALSE(isbn_verifier::is_valid("3598215078X"));
}

TEST(IsbnVerifier, T012_too_short_isbn) { REQUIRE_FALSE(isbn_verifier::is_valid("00")); }

TEST(IsbnVerifier, T013_isbn_without_check_digit) {
    REQUIRE_FALSE(isbn_verifier::is_valid("3-598-21507"));
}

TEST(IsbnVerifier, T014_check_digit_of_x_should_not_be_used_for_0) {
    REQUIRE_FALSE(isbn_verifier::is_valid("3-598-21515-X"));
}

TEST(IsbnVerifier, T015_empty_isbn) { REQUIRE_FALSE(isbn_verifier::is_valid("")); }

TEST(IsbnVerifier, T016_input_is_9_characters) {
    REQUIRE_FALSE(isbn_verifier::is_valid("134456729"));
}

TEST(IsbnVerifier, T017_invalid_characters_are_not_ignored_after_checking_length) {
    REQUIRE_FALSE(isbn_verifier::is_valid("3132P34035"));
}

TEST(IsbnVerifier, T018_invalid_characters_are_not_ignored_before_checking_length) {
    REQUIRE_FALSE(isbn_verifier::is_valid("3598P215088"));
}

TEST(IsbnVerifier, T019_input_is_too_long_but_contains_a_valid_isbn) {
    REQUIRE_FALSE(isbn_verifier::is_valid("98245726788"));
}
#endif

}  // namespace
