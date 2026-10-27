// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "Parrot.h"

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

TEST(Characterization, getSpeed_01) {
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 1.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 3.0, false).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 2.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 0.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 2.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 1.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 2.5, false).getSpeed(), 24.0, 1e-9);
}

TEST(Characterization, getCry_01) {
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 1.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 1.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 3.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 3.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 2.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 0.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 0.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 2.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 1.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 3.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 1.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 2.5, false).getCry()), (std::string("Bzzzzzz")));
}
