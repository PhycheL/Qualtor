// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "humaneval_x_cpp_20.h"

TEST(Review, EmptyPatternAndSmallRightTriangle) {
 EXPECT_FALSE(cycpattern_check("x",""));
 EXPECT_TRUE(right_angle_triangle(0.04f,0.05f,0.03f));
 EXPECT_EQ("ab",find_max({"aaaaa","ab"}));
}

// 字符串内嵌零字符："a" 有 1 个不同字符，"b\0" 有 2 个。
TEST(ReviewSource, EmbeddedNullUniqueCount) {
    const std::string b0("b\0", 2);
    EXPECT_EQ(b0, find_max({"a", b0}));
}

// 乘方与乘法混合，需要沿父指针压缩路径。
TEST(ReviewSource, MixedPrecedence) {
    EXPECT_EQ(36, do_algebra({"*", "**", "*"}, {2, 3, 2, 2}));
}

// 超过 42 个操作数的加法链。
TEST(ReviewSource, LongAdditionChain) {
    EXPECT_EQ(50, do_algebra(std::vector<std::string>(49, "+"), std::vector<int>(50, 1)));
}
