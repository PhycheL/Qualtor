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

#include "humaneval_x_cpp_01.h"

TEST(Review, ClosePairOnlyAfterFortyTwo) {
 std::vector<float> v;for(int i=0;i<43;++i)v.push_back(100.0f*i);v.push_back(4200);
 EXPECT_TRUE(has_close_elements(v,0.1f));
}
