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

#include "pig_latin.h"

TEST(Review, FortyTwoCharacterWord) { EXPECT_EQ(std::string(42,'a')+"ay",pig_latin::translate(std::string(42,'a'))); }

TEST(ReviewExtra, WordStartsAtFortyTwo) { EXPECT_EQ(std::string(41,'a')+"ay atcay",pig_latin::translate(std::string(41,'a')+" cat")); }
