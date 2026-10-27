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

TEST(Characterization, tennis_score_01) {
    EXPECT_EQ((tennis_score(8, 13)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(12, 3)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(10, 10)), (std::string("Deuce")));
    EXPECT_EQ((tennis_score(9, 1)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(15, 11)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(6, 15)), (std::string("Win for player2")));
    EXPECT_EQ((tennis_score(9, 5)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(12, 4)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(13, 10)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(4, 2)), (std::string("Win for player1")));
    EXPECT_EQ((tennis_score(2, 0)), (std::string("Thirty-Love")));
    EXPECT_EQ((tennis_score(0, 3)), (std::string("Love-Forty")));
}
