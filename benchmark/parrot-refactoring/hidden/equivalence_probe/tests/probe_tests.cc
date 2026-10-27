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

TEST(Probe, getSpeed_01) {
    ExpectNearScalar(Parrot(EUROPEAN, 5, 0.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 2.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 0.5, false).getSpeed(), 6.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 4.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 2.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 1.0, true).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 0.5, false).getSpeed(), 6.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 1.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 4.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 4.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 2.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 3.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 3.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 1.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 2.5, false).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 1.5, true).getSpeed(), 12.0, 1e-9);
}

TEST(Probe, getSpeed_02) {
    ExpectNearScalar(Parrot(AFRICAN, 2, 1.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 1.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 0.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 3.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 1.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 2.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 2.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 0.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 2.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 1.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 3.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 2.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 3.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 1.5, false).getSpeed(), 18.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 1.5, false).getSpeed(), 18.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 4.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 1.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 4.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 0.0, true).getSpeed(), 0.0, 1e-9);
}

TEST(Probe, getSpeed_03) {
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 1.5, false).getSpeed(), 18.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 2.5, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 2.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 3.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 1.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 0.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 1.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 2.5, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 0.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 2.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 0.0, true).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 0.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 0.5, false).getSpeed(), 6.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 3.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 1.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 1.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 4.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 2.0, false).getSpeed(), 24.0, 1e-9);
}

TEST(Probe, getSpeed_04) {
    ExpectNearScalar(Parrot(AFRICAN, 3, 2.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 2.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 1.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 0.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 0.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 4.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 3.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 1.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 4.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 2.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 3.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 1.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 2.0, true).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 4.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 0.5, false).getSpeed(), 6.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 2.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 0.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 2.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 4.0, false).getSpeed(), 24.0, 1e-9);
}

TEST(Probe, getSpeed_05) {
    ExpectNearScalar(Parrot(AFRICAN, 4, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 2.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 1.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 4.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 4.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 0.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 3.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 2.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 0.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 0.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 2.0, false).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 2.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 0.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 0.5, false).getSpeed(), 6.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 1.5, false).getSpeed(), 18.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 3.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 0.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 3.0, true).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 0.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 0.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 2.5, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 4.0, false).getSpeed(), 0.0, 1e-9);
}

TEST(Probe, getSpeed_06) {
    ExpectNearScalar(Parrot(EUROPEAN, 4, 1.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 0.5, false).getSpeed(), 6.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 4.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 0.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 1.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 0.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 2.5, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 2.5, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 1.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 1.5, false).getSpeed(), 18.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 0.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 2.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 2.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 0.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 1.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 4.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 0.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 1.0, false).getSpeed(), 12.0, 1e-9);
}

TEST(Probe, getSpeed_07) {
    ExpectNearScalar(Parrot(AFRICAN, 5, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 1.5, false).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 0.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 0.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 1.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 0.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 1.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 0.5, false).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 4.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 0.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 4.0, true).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 0.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 1.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 0.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 2.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 2.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 0.5, true).getSpeed(), 0.0, 1e-9);
}

TEST(Probe, getSpeed_08) {
    ExpectNearScalar(Parrot(EUROPEAN, 3, 0.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 0.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 0.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 2.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 2.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 3.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 0.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 2.5, true).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 0.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 2.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 4.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 3.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 0.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 3.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 2.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 4.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 0.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 0.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 2.5, false).getSpeed(), 12.0, 1e-9);
}

TEST(Probe, getSpeed_09) {
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 1.5, false).getSpeed(), 18.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 2.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 3.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 0.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 0, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 2.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 4.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 3.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 2.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 0.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 2.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 4.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 2.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 3.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 4.0, false).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 0.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 4.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 0.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 1.0, false).getSpeed(), 12.0, 1e-9);
}

TEST(Probe, getSpeed_10) {
    ExpectNearScalar(Parrot(AFRICAN, 3, 4.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 4.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 0.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 0.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 0.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 1.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 3.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 3.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 3.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 2, 3.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 3.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 1.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 4, 2.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 0.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 2, 2.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 4.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 2.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 1.0, false).getSpeed(), 3.0, 1e-9);
}

TEST(Probe, getSpeed_11) {
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 1.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 2.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 3.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 0.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 0.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 2, 2.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 3.0, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 5, 1.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 2.0, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 4, 2.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 0, 2.5, false).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 0.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 3, 0.5, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 3, 1.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 4, 0.5, false).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 4.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 0, 1.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 5, 0.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 1, 2.0, true).getSpeed(), 0.0, 1e-9);
    ExpectNearScalar(Parrot(NORWEGIAN_BLUE, 5, 3.0, false).getSpeed(), 24.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 1.5, true).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 3, 0.5, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(EUROPEAN, 1, 2.0, true).getSpeed(), 12.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 0.5, true).getSpeed(), 3.0, 1e-9);
    ExpectNearScalar(Parrot(AFRICAN, 1, 0.0, false).getSpeed(), 3.0, 1e-9);
}

TEST(Probe, getSpeed_12) {
    ExpectNearScalar(Parrot(AFRICAN, 3, 1.5, false).getSpeed(), 0.0, 1e-9);
}

TEST(Probe, getCry_01) {
    EXPECT_EQ((Parrot(EUROPEAN, 5, 0.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 2.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 1.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 0.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 2.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 4.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 2.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 1.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 1.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 0.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 1.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 1.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 4.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 1.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 4.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 2.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 1.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 3.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 1.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 3.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 0.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 2.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 1.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 2.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 1.5, true).getCry()), (std::string("Squaark!")));
}

TEST(Probe, getCry_02) {
    EXPECT_EQ((Parrot(AFRICAN, 2, 1.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 1.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 0.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 0.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 3.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 1.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 2.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 2.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 0.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 1.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 1.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 2.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 4.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 1.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 3.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 2.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 3.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 0.0, false).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 1.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 0.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 1.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 4.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 1.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 4.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 0.0, true).getCry()), (std::string("...")));
}

TEST(Probe, getCry_03) {
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 1.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 2.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 2.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 3.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 2.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 1.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 0.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 2.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 2.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 1.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 3.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 2.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 0.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 2.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 0.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 0.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 3.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 0.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 2.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 3.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 1.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 1.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 1.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 4.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 2.0, false).getCry()), (std::string("Bzzzzzz")));
}

TEST(Probe, getCry_04) {
    EXPECT_EQ((Parrot(AFRICAN, 3, 2.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 2.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 1.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 1.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 0.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 0.0, true).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 1.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 4.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 3.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 1.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 4.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 0.0, false).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 2.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 3.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 0.0, false).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 1.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 2.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 2.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 4.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 0.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 2.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 1.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 0.0, true).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 2.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 4.0, false).getCry()), (std::string("Bzzzzzz")));
}

TEST(Probe, getCry_05) {
    EXPECT_EQ((Parrot(AFRICAN, 4, 3.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 2.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 1.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 4.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 4.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 0.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 3.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 1.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 2.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 0.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 0.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 2.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 2.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 0.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 0.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 3.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 1.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 3.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 0.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 3.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 0.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 0.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 2.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 1.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 4.0, false).getCry()), (std::string("Squaark!")));
}

TEST(Probe, getCry_06) {
    EXPECT_EQ((Parrot(EUROPEAN, 4, 1.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 4.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 0.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 4.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 0.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 1.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 0.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 2.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 1.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 2.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 1.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 1.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 4.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 1.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 0.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 2.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 2.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 0.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 3.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 2.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 1.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 1.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 4.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 0.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 1.0, false).getCry()), (std::string("Sqoork!")));
}

TEST(Probe, getCry_07) {
    EXPECT_EQ((Parrot(AFRICAN, 5, 3.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 1.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 0.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 0.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 1.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 0.0, true).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 1.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 0.0, false).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 0.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 1.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 4.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 2.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 2.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 0.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 4.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 2.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 0.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 1.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 4.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 1.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 0.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 2.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 1.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 2.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 0.5, true).getCry()), (std::string("Squaark!")));
}

TEST(Probe, getCry_08) {
    EXPECT_EQ((Parrot(EUROPEAN, 3, 0.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 1.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 1.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 4.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 0.0, true).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 0.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 2.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 2.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 3.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 0.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 2.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 4.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 0.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 2.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 4.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 3.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 0.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 2.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 4.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 3.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 2.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 4.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 0.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 0.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 2.5, false).getCry()), (std::string("Sqoork!")));
}

TEST(Probe, getCry_09) {
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 1.5, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 2.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 3.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 2.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 0.0, true).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 0, 1.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 2.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 3.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 4.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 3.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 2.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 0.0, false).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 0.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 2.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 2.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 2.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 4.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 2.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 3.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 4.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 0.0, false).getCry()), (std::string("...")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 4.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 0.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 1.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 1.0, false).getCry()), (std::string("Sqoork!")));
}

TEST(Probe, getCry_10) {
    EXPECT_EQ((Parrot(AFRICAN, 3, 4.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 2.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 4.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 0.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 0.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 2.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 0.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 1.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 4.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 3.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 4.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 3.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 2.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 3.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 2, 3.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 3.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 1.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 4, 2.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 1.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 0.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 1.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 2, 2.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 4.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 2.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 1.0, false).getCry()), (std::string("Squaark!")));
}

TEST(Probe, getCry_11) {
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 1.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 2.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 3.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 0.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 0.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 2, 2.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 3.0, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 5, 1.5, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 2.0, false).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 4, 2.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 0, 2.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 0.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 3, 0.5, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 3, 1.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 4, 0.5, false).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 4.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(EUROPEAN, 0, 1.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 5, 0.0, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 1, 2.0, true).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(NORWEGIAN_BLUE, 5, 3.0, false).getCry()), (std::string("Bzzzzzz")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 1.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(EUROPEAN, 3, 0.5, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(EUROPEAN, 1, 2.0, true).getCry()), (std::string("Sqoork!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 0.5, true).getCry()), (std::string("Squaark!")));
    EXPECT_EQ((Parrot(AFRICAN, 1, 0.0, false).getCry()), (std::string("Squaark!")));
}

TEST(Probe, getCry_12) {
    EXPECT_EQ((Parrot(AFRICAN, 3, 1.5, false).getCry()), (std::string("Squaark!")));
}
