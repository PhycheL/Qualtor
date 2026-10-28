// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_03.h"
#include <gtest/gtest.h>
TEST(StepAGaps, EqualDistancePreservesFirstPair) { EXPECT_EQ((std::vector<float>{0,1}), find_closest_elements({0,1,2})); }
