// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include "humaneval_x_cpp_14.h"

// 负数的首位数字带符号：-109 的各位为 -1、0、9，和为 8。
TEST(ReviewSource, NegativeWithZeroDigit) {
    EXPECT_EQ(1, count_nums({-109}));
}
