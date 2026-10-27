// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
// Include the header file with the definitions of the functions you create.
#include "high_scores.h"

namespace {

// Include the test framework.

// Declares a single test.
TEST(HighScores, T001_List_of_scores) {
    std::vector<int> scores{30, 50, 20, 70};
    arcade::HighScores hs{scores};
    REQUIRE(hs.list_scores() == scores);
}

#ifdef EXERCISM_RUN_ALL_TESTS

TEST(HighScores, T002_Latest_score) {
    std::vector<int> scores{100, 0, 90, 30};
    int expected{30};
    arcade::HighScores hs{scores};
    REQUIRE(hs.latest_score() == expected);
}

TEST(HighScores, T003_Personal_best) {
    std::vector<int> scores{40, 100, 70};
    int expected{100};
    arcade::HighScores hs{scores};
    REQUIRE(hs.personal_best() == expected);
}

TEST(HighScores, T004_Personal_top_three_from_a_list_of_scores) {
    std::vector<int> scores{10, 30, 90, 30, 100, 20, 10, 0, 30, 40, 40, 70, 70};
    std::vector<int> expected{100, 90, 70};
    arcade::HighScores hs{scores};
    REQUIRE(hs.top_three() == expected);
}

TEST(HighScores, T005_Personal_top_highest_to_lowest) {
    std::vector<int> scores{20, 10, 30};
    std::vector<int> expected{30, 20, 10};
    arcade::HighScores hs{scores};
    REQUIRE(hs.top_three() == expected);
}

TEST(HighScores, T006_Personal_top_when_there_is_a_tie) {
    std::vector<int> scores{40, 20, 40, 30};
    std::vector<int> expected{40, 40, 30};
    arcade::HighScores hs{scores};
    REQUIRE(hs.top_three() == expected);
}

TEST(HighScores, T007_Personal_top_when_there_are_less_than_3) {
    std::vector<int> scores{30, 70};
    std::vector<int> expected{70, 30};
    arcade::HighScores hs{scores};
    REQUIRE(hs.top_three() == expected);
}

TEST(HighScores, T008_Personal_top_when_there_is_only_one) {
    std::vector<int> scores{40};
    std::vector<int> expected{40};
    arcade::HighScores hs{scores};
    REQUIRE(hs.top_three() == expected);
}

TEST(HighScores, T009_Latest_score_after_personal_top_scores) {
    // Test if latest_score is still valid after calling top_three
    std::vector<int> scores{70, 50, 20, 30};
    int expected{30};
    arcade::HighScores hs{scores};
    hs.top_three();
    REQUIRE(hs.latest_score() == expected);
}

TEST(HighScores, T010_Scores_after_personal_top_scores) {
    // Test if list_scores is unchanged after calling top_three
    std::vector<int> scores{30, 50, 20, 70};
    arcade::HighScores hs{scores};
    hs.top_three();
    REQUIRE(hs.list_scores() == scores);
}

TEST(HighScores, T011_Latest_score_after_personal_best) {
    // Test if latest_score is still valid after calling personal_best
    std::vector<int> scores{20, 70, 15, 25, 30};
    int expected{30};
    arcade::HighScores hs{scores};
    hs.personal_best();
    REQUIRE(hs.latest_score() == expected);
}

TEST(HighScores, T012_Scores_after_personal_best) {
    // Test if list_scores is unchanged after calling personal_best
    std::vector<int> scores{20, 70, 15, 25, 30};
    arcade::HighScores hs{scores};
    hs.personal_best();
    REQUIRE(hs.list_scores() == scores);
}

#endif

}  // namespace
