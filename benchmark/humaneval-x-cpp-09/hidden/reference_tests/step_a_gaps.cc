// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_09.h"
#include <gtest/gtest.h>
TEST(StepAGaps, LeadingSeparatorAndUppercaseEndpoint) {
 EXPECT_EQ(8, fruit_distribution(" 5 apples and 6 oranges", 19)); EXPECT_EQ(90, digitSum("Z"));
}
TEST(StepAGaps, AllWeightCounts) { EXPECT_FALSE(will_it_fly({2,3,2},2)); }
