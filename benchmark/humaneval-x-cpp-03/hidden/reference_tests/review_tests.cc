// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "humaneval_x_cpp_03.h"

TEST(Review, LongMusicAndClosestTailPair) {
 std::string music;for(int i=0;i<50;++i)music+="o ";
 EXPECT_EQ(std::vector<int>(50,4),parse_music(music));
 std::vector<float> v;for(int i=0;i<43;++i)v.push_back(100.0f*i);v.push_back(4200);
 EXPECT_EQ((std::vector<float>{4200,4200}),find_closest_elements(v));
}

// 两个相等的浮点零：+0 在前、-0 在后，原代码不交换顺序。
TEST(ReviewSource, SignedZeroOrder) {
    const std::vector<float> out = find_closest_elements({0.0f, -0.0f});
    ASSERT_EQ(2u, out.size());
    EXPECT_FALSE(std::signbit(out[0]));
    EXPECT_TRUE(std::signbit(out[1]));
}

// 先 +0 后 -0：最小值保持 +0，-0 元素归一化后仍是 -0（-0 - (+0) = -0）。
TEST(ReviewSource, SignedZeroMinimum) {
    const std::vector<float> out = rescale_to_unit({0.0f, -0.0f, 1.0f});
    ASSERT_EQ(3u, out.size());
    EXPECT_FALSE(std::signbit(out[0]));
    EXPECT_TRUE(std::signbit(out[1]));
    EXPECT_EQ(1.0f, out[2]);
}
