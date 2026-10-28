// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_04.h"
#include <gtest/gtest.h>
TEST(StepAGaps, AlphabetEndpointsAndSmallestPrime) { EXPECT_EQ("Zz", filp_case("zZ")); EXPECT_TRUE(is_prime(2)); }
