// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_20.h"
#include <gtest/gtest.h>
TEST(StepAGaps, AlphabetEndpoints) { EXPECT_EQ("zZ", solve("Zz")); }
TEST(StepAGaps, OperatorsBeyond42) {
 std::vector<std::string> ops(43,"+"); std::vector<int> args(44,1); args[42]=2; args[43]=3;
 ops[42]="**"; EXPECT_EQ(50, do_algebra(ops,args));
 ops[42]="*"; EXPECT_EQ(48, do_algebra(ops,args));
}
