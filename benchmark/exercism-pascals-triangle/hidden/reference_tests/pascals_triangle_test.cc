// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "pascals_triangle.h"

namespace {

TEST(PascalsTriangle, T001_zero_rows) {
    const std::vector<std::vector<int>> expected;

    const std::vector<std::vector<int>> actual{
        pascals_triangle::generate_rows(0)};

    REQUIRE(expected == actual);
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(PascalsTriangle, T002_single_row) {
    const std::vector<std::vector<int>> expected{{1}};

    const std::vector<std::vector<int>> actual{
        pascals_triangle::generate_rows(1)};

    REQUIRE(expected == actual);
}

TEST(PascalsTriangle, T003_two_rows) {
    const std::vector<std::vector<int>> expected{{1}, {1, 1}};

    const std::vector<std::vector<int>> actual{
        pascals_triangle::generate_rows(2)};

    REQUIRE(expected == actual);
}

TEST(PascalsTriangle, T004_three_rows) {
    const std::vector<std::vector<int>> expected{{1}, {1, 1}, {1, 2, 1}};

    const std::vector<std::vector<int>> actual{
        pascals_triangle::generate_rows(3)};

    REQUIRE(expected == actual);
}

TEST(PascalsTriangle, T005_four_rows) {
    const std::vector<std::vector<int>> expected{
        {1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}};

    const std::vector<std::vector<int>> actual{
        pascals_triangle::generate_rows(4)};

    REQUIRE(expected == actual);
}

TEST(PascalsTriangle, T006_five_rows) {
    const std::vector<std::vector<int>> expected{
        {1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}};

    const std::vector<std::vector<int>> actual{
        pascals_triangle::generate_rows(5)};

    REQUIRE(expected == actual);
}

TEST(PascalsTriangle, T007_six_rows) {
    const std::vector<std::vector<int>> expected{
        {1},          {1, 1},          {1, 2, 1},
        {1, 3, 3, 1}, {1, 4, 6, 4, 1}, {1, 5, 10, 10, 5, 1}};

    const std::vector<std::vector<int>> actual{
        pascals_triangle::generate_rows(6)};

    REQUIRE(expected == actual);
}

TEST(PascalsTriangle, T008_ten_rows) {
    const std::vector<std::vector<int>> expected{
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1},
        {1, 5, 10, 10, 5, 1},
        {1, 6, 15, 20, 15, 6, 1},
        {1, 7, 21, 35, 35, 21, 7, 1},
        {1, 8, 28, 56, 70, 56, 28, 8, 1},
        {1, 9, 36, 84, 126, 126, 84, 36, 9, 1}};

    const std::vector<std::vector<int>> actual{
        pascals_triangle::generate_rows(10)};

    REQUIRE(expected == actual);
}

#endif

}  // namespace
