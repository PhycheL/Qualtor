// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_19.h"
#include <gtest/gtest.h>
TEST(StepAGaps, PrimeSquare) { EXPECT_EQ(9, x_or_y(4,7,9)); }
