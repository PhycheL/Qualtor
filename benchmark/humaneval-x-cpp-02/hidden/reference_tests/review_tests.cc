// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <string>

#include "humaneval_x_cpp_02.h"

// 回文后缀从第 44 个字符才开始：43 个 a 后接 b，只需补 43 个 a。
TEST(ReviewSource, PalindromeSuffixAfterFortyTwo) {
    const std::string a43(43, 'a');
    EXPECT_EQ(a43 + "b" + a43, make_palindrome(a43 + "b"));
}

// 长度超过 42 的两个串逐位异或。
TEST(ReviewSource, LongXor) {
    EXPECT_EQ(std::string(50, '0'), string_xor(std::string(50, '1'), std::string(50, '1')));
}
