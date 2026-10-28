// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <string>

#include "humaneval_x_cpp_07.h"

// 前 42 个括号配平，第 43 个才使层级为负：要检查到最后一个字符。
TEST(ReviewSource, ImbalanceAfterFortyTwo) {
    EXPECT_FALSE(correct_bracketing(std::string(21, '<') + std::string(21, '>') + ">"));
}
