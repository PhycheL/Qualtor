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

#include "humaneval_x_cpp_10.h"

TEST(Review, EmbeddedNullHappy) { EXPECT_TRUE(is_happy(std::string("ab\0",3))); }

// 长度超过 42 的十六进制串要逐位统计到末尾。
TEST(ReviewSource, LongHexString) {
    EXPECT_EQ(50, hex_key(std::string(50, '2')));
}
