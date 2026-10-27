// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "isogram.h"

namespace {

using namespace std;

// Isogram exercise test case data version 1.7.0

TEST(Isogram, T001_empty_string) {
    const bool actual = isogram::is_isogram("");

    const bool expected{true};

    REQUIRE(expected == actual);
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Isogram, T002_isogram_with_only_lower_case_characters) {
    const bool actual = isogram::is_isogram("isogram");

    const bool expected{true};

    REQUIRE(expected == actual);
}

TEST(Isogram, T003_word_with_one_duplicated_character) {
    const bool actual = isogram::is_isogram("eleven");

    const bool expected{false};

    REQUIRE(expected == actual);
}

TEST(Isogram, T004_word_with_one_duplicated_character_from_the_end_of_the_alpha) {
    const bool actual = isogram::is_isogram("zzyzx");

    const bool expected{false};

    REQUIRE(expected == actual);
}

TEST(Isogram, T005_longest_reported_english_isogram) {
    const bool actual = isogram::is_isogram("subdermatoglyphic");

    const bool expected{true};

    REQUIRE(expected == actual);
}

TEST(Isogram, T006_word_with_duplicated_character_in_mixed_case) {
    const bool actual = isogram::is_isogram("Alphabet");

    const bool expected{false};

    REQUIRE(expected == actual);
}

TEST(Isogram, T007_word_with_duplicated_character_in_mixed_case_lowercase_first) {
    const bool actual = isogram::is_isogram("alphAbet");

    const bool expected{false};

    REQUIRE(expected == actual);
}

TEST(Isogram, T008_hypothetical_isogrammic_word_with_hyphen) {
    const bool actual = isogram::is_isogram("thumbscrew-japingly");

    const bool expected{true};

    REQUIRE(expected == actual);
}

TEST(Isogram, T009_hypothetical_word_with_duplicated_character_following_hyphen) {
    const bool actual = isogram::is_isogram("thumbscrew-jappingly");

    const bool expected{false};

    REQUIRE(expected == actual);
}

TEST(Isogram, T010_isogram_with_duplicated_hyphen) {
    const bool actual = isogram::is_isogram("six-year-old");

    const bool expected{true};

    REQUIRE(expected == actual);
}

TEST(Isogram, T011_made_up_name_that_is_an_isogram) {
    const bool actual = isogram::is_isogram("Emily Jung Schwartzkopf");

    const bool expected{true};

    REQUIRE(expected == actual);
}

TEST(Isogram, T012_duplicated_character_in_the_middle) {
    const bool actual = isogram::is_isogram("accentor");

    const bool expected{false};

    REQUIRE(expected == actual);
}

TEST(Isogram, T013_same_first_and_last_characters) {
    const bool actual = isogram::is_isogram("angola");

    const bool expected{false};

    REQUIRE(expected == actual);
}

TEST(Isogram, T014_word_with_duplicated_character_and_with_two_hyphens) {
    const bool actual = isogram::is_isogram("up-to-date");

    const bool expected{false};

    REQUIRE(expected == actual);
}

#endif

}  // namespace
