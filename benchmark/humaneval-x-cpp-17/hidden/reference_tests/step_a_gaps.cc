// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_17.h"
#include <gtest/gtest.h>
TEST(StepAGaps, LowercaseEndpointsBeforeLastLetter) {
 EXPECT_FALSE(check_if_last_char_is_a_letter("aa")); EXPECT_FALSE(check_if_last_char_is_a_letter("za"));
}
