// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_01.h"
#include <gtest/gtest.h>
TEST(StepAGaps, ThresholdBoundary) { EXPECT_FALSE(has_close_elements({0.0f, 1.0f}, 1.0f)); }
TEST(StepAGaps, ParenthesesAfter42) {
 EXPECT_EQ((std::vector<std::string>{"()"}), separate_paren_groups(std::string(43, ' ') + "()"));
 EXPECT_EQ((std::vector<int>{1}), parse_nested_parens(std::string(43, ' ') + "()"));
}
