// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_08.h"
#include <gtest/gtest.h>
TEST(StepAGaps, ClosingBracketAfter42) { EXPECT_FALSE(correct_bracketing(std::string(42,' ') + ")")); }
