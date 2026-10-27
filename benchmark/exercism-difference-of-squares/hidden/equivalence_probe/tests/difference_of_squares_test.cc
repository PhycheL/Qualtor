// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "difference_of_squares.h"

namespace {

TEST(DifferenceOfSquares, T001_up_to_5) {
    REQUIRE(225 == difference_of_squares::square_of_sum(5));
    REQUIRE(55 == difference_of_squares::sum_of_squares(5));
    REQUIRE(170 == difference_of_squares::difference(5));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(DifferenceOfSquares, T002_up_to_10) {
    REQUIRE(3025 == difference_of_squares::square_of_sum(10));
    REQUIRE(385 == difference_of_squares::sum_of_squares(10));
    REQUIRE(2640 == difference_of_squares::difference(10));
}

TEST(DifferenceOfSquares, T003_up_to_100) {
    REQUIRE(25502500 == difference_of_squares::square_of_sum(100));
    REQUIRE(338350 == difference_of_squares::sum_of_squares(100));
    REQUIRE(25164150 == difference_of_squares::difference(100));
}
#endif

}  // namespace
