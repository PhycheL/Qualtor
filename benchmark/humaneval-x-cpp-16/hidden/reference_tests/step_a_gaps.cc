// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_16.h"
#include <gtest/gtest.h>
TEST(StepAGaps, PrimeAndSquareIntersection) {
 EXPECT_EQ("NO", intersection({0,4},{0,4})); EXPECT_EQ("YES", intersection({0,5},{0,5}));
}
