// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_05.h"
#include <gtest/gtest.h>
TEST(StepAGaps, TripleRequiresDistinctIndices) { EXPECT_FALSE(triples_sum_to_zero({1,-2,4})); }
