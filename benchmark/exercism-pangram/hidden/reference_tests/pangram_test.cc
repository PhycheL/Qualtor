// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "pangram.h"

namespace {

TEST(Pangram, T001_sentence_empty) { REQUIRE(!pangram::is_pangram("")); }

#ifdef EXERCISM_RUN_ALL_TESTS
TEST(Pangram, T002_pangram_with_only_lower_case) {
    REQUIRE(pangram::is_pangram("the quick brown fox jumps over the lazy dog"));
}

TEST(Pangram, T003_missing_character_x) {
    REQUIRE(!pangram::is_pangram(
        "a quick movement of the enemy will jeopardize five gunboats"));
}

TEST(Pangram, T004_another_missing_x) {
    REQUIRE(
        !pangram::is_pangram("the quick brown fish jumps over the lazy dog"));
}

TEST(Pangram, T005_pangram_with_underscores) {
    REQUIRE(pangram::is_pangram("the_quick_brown_fox_jumps_over_the_lazy_dog"));
}

TEST(Pangram, T006_pangram_with_numbers) {
    REQUIRE(pangram::is_pangram(
        "the 1 quick brown fox jumps over the 2 lazy dogs"));
}

TEST(Pangram, T007_missing_letters_replaced_with_numbers) {
    REQUIRE(
        !pangram::is_pangram("7h3 qu1ck brown fox jumps ov3r 7h3 lazy dog"));
}

TEST(Pangram, T008_pangram_with_mixed_case_and_punctuation) {
    REQUIRE(pangram::is_pangram("\"Five quacking Zephyrs jolt my wax bed.\""));
}

TEST(Pangram, T009_a_to_m_and_A_to_M_are_26_different_characters_but_not_a_pang) {
    REQUIRE(!pangram::is_pangram("abcdefghijklm ABCDEFGHIJKLM"));
}
#endif

}  // namespace
