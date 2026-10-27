// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "scrabble_score.h"

namespace {

TEST(ScrabbleScore, T001_scores_an_empty_word_as_zero) {
    REQUIRE(0 == scrabble_score::score(""));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(ScrabbleScore, T002_scores_a_very_short_word) {
    REQUIRE(1 == scrabble_score::score("a"));
}

TEST(ScrabbleScore, T003_scores_the_word_by_the_number_of_letters) {
    REQUIRE(6 == scrabble_score::score("street"));
}

TEST(ScrabbleScore, T004_scores_more_complicated_words_with_more) {
    REQUIRE(22 == scrabble_score::score("quirky"));
}

TEST(ScrabbleScore, T005_scores_case_insensitive_words) {
    REQUIRE(41 == scrabble_score::score("OXYPHENBUTAZONE"));
}

TEST(ScrabbleScore, T006_scores_z_word) { REQUIRE(12 == scrabble_score::score("zoo")); }
#endif

}  // namespace
