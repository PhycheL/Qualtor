// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_14.h"
#include <gtest/gtest.h>
TEST(StepAGaps, EqualNeighborsAreNotDescents) { EXPECT_TRUE(move_one_ball({1,1,1})); }
