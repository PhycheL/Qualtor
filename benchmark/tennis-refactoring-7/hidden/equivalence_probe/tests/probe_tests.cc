// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "tennis.h"

#include <gtest/gtest.h>

#include <cmath>
#include <map>
#include <string>
#include <vector>

namespace {

template <class T>
void ExpectNearScalar(T actual, T expected, double tolerance) {
    EXPECT_NEAR(actual, expected, tolerance * (1 + std::fabs(static_cast<double>(expected))));
}

template <class T>
void ExpectNearVec(const std::vector<T>& actual, const std::vector<T>& expected, double tolerance) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) ExpectNearScalar(actual[i], expected[i], tolerance);
}

}  // namespace

TEST(Probe, tennis_score_01) {
    EXPECT_EQ((tennis_score(11, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(15, 15)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(1, 9)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(5, 4)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(7, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(10, 7)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(1, 3)), (std::string("Fifteen-Forty")));
    EXPECT_EQ((tennis_score(0, 1)), (std::string("Love-Fifteen")));
    EXPECT_EQ((tennis_score(15, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(12, 6)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(1, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(11, 9)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(14, 13)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(6, 5)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(4, 9)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(9, 4)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(9, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(4, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(2, 5)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(13, 14)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(3, 3)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(7, 6)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(1, 6)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(15, 8)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(2, 2)), (std::string("Thirty-All")));
}

TEST(Probe, tennis_score_02) {
    EXPECT_EQ((tennis_score(13, 7)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(1, 10)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(0, 6)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(4, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(12, 12)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(11, 8)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(15, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(8, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(3, 0)), (std::string("Forty-Love")));
    EXPECT_EQ((tennis_score(11, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(14, 6)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(4, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(5, 8)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(8, 5)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(13, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(0, 5)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(4, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(15, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(0, 9)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(10, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(10, 4)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(9, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(3, 2)), (std::string("Forty-Thirty")));
    EXPECT_EQ((tennis_score(4, 10)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(0, 13)), (std::string("Win for player2")));
}

TEST(Probe, tennis_score_03) {
    EXPECT_EQ((tennis_score(11, 11)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(13, 6)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(9, 10)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(7, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(8, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(2, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(12, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(5, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(3, 4)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(11, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(14, 11)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(11, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(1, 0)), (std::string("Fifteen-Love")));
    EXPECT_EQ((tennis_score(13, 13)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(1, 4)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(9, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(7, 5)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(13, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(10, 11)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(1, 7)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(6, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(10, 6)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(1, 2)), (std::string("Fifteen-Thirty")));
    EXPECT_EQ((tennis_score(8, 10)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(12, 14)), (std::string("Win for player2")));
}

TEST(Probe, tennis_score_04) {
    EXPECT_EQ((tennis_score(14, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(6, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(9, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(0, 7)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(8, 9)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(8, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(9, 8)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(7, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(6, 8)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(5, 10)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(12, 13)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(6, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(15, 5)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(10, 5)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(7, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(12, 5)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(2, 4)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(1, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(5, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(8, 4)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(13, 4)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(9, 9)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(2, 6)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(7, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(7, 13)), (std::string("Win for player2")));
}

TEST(Probe, tennis_score_05) {
    EXPECT_EQ((tennis_score(15, 6)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(5, 7)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(4, 7)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(3, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(8, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(0, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(3, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(7, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(15, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(3, 8)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(7, 9)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(1, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(13, 11)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(9, 7)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(7, 4)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(12, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(14, 8)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(7, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(14, 4)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(8, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(10, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(11, 10)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(2, 1)), (std::string("Thirty-Fifteen")));
    EXPECT_EQ((tennis_score(5, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(15, 4)), (std::string("Win for player1")));
}

TEST(Probe, tennis_score_06) {
    EXPECT_EQ((tennis_score(12, 11)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(15, 14)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(2, 8)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(7, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(5, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(10, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(8, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(13, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(15, 13)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(1, 5)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(11, 5)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(1, 1)), (std::string("Fifteen-All")));
    EXPECT_EQ((tennis_score(3, 10)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(8, 8)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(2, 10)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(10, 8)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(0, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(6, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(14, 15)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(6, 7)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(12, 7)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(2, 3)), (std::string("Thirty-Forty")));
    EXPECT_EQ((tennis_score(3, 6)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(5, 9)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(15, 12)), (std::string("Win for player1")));
}

TEST(Probe, tennis_score_07) {
    EXPECT_EQ((tennis_score(13, 9)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(6, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(12, 10)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(9, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(0, 4)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(14, 10)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(13, 5)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(7, 10)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(10, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(11, 6)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(6, 9)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(13, 12)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(2, 7)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(12, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(11, 12)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(9, 6)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(5, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(4, 6)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(3, 7)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(11, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(5, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(14, 9)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(9, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(11, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(11, 14)), (std::string("Win for player2")));
}

TEST(Probe, tennis_score_08) {
    EXPECT_EQ((tennis_score(2, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(4, 4)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(8, 6)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(6, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(0, 2)), (std::string("Love-Thirty")));
    EXPECT_EQ((tennis_score(2, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(15, 7)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(7, 8)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(6, 4)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(3, 5)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(8, 7)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(6, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(10, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(10, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(14, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(9, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(0, 0)), (std::string("Love-All")));
    EXPECT_EQ((tennis_score(2, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(1, 8)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(14, 14)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(4, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(0, 10)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(10, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(12, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(11, 4)), (std::string("Win for player1")));
}

TEST(Probe, tennis_score_09) {
    EXPECT_EQ((tennis_score(3, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(0, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(2, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(7, 7)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(5, 5)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(4, 3)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(3, 9)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(5, 12)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(3, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(14, 7)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(8, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(4, 5)), (std::string("Advantage player2")));
    EXPECT_EQ((tennis_score(14, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(5, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(6, 6)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(1, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(0, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(6, 10)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(12, 9)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(13, 8)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(13, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(13, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(14, 5)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(4, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(8, 14)), (std::string("Win for player2")));
}

TEST(Probe, tennis_score_10) {
    EXPECT_EQ((tennis_score(4, 8)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(1, 11)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(0, 8)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(6, 14)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(9, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(4, 0)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(15, 10)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(10, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(12, 8)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(14, 12)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(5, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(11, 7)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(2, 9)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(3, 1)), (std::string("Forty-Fifteen")));
    EXPECT_EQ((tennis_score(3, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(10, 9)), (std::string("Advantage player1")));
    EXPECT_EQ((tennis_score(15, 9)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(14, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(5, 6)), (std::string("Advantage player2")));
}
