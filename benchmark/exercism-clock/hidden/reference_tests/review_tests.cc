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

#include "clock.h"

TEST(Review, MinusAndLargeNormalization) {
  using date_independent::clock;
  auto c=clock::at(0); c.minus(1); EXPECT_EQ("23:59",std::string(c));
  auto d=clock::at(10,30); d.minus(20); EXPECT_EQ("10:10",std::string(d));
  EXPECT_EQ("00:00",std::string(clock::at(-4000000,240000000)));
}

TEST(ReviewExtra, NegativeMillionMinutes) { EXPECT_EQ("00:00",std::string(date_independent::clock::at(16667,-1000020))); }
