// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "knapsack.h"

#include <vector>

namespace {

TEST(Knapsack, T001_no_items) {
    int max_weight = 100;
    const std::vector<knapsack::Item> items{};
    REQUIRE(knapsack::maximum_value(max_weight, items) == 0);
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(Knapsack, T002_one_item_too_heavy) {
    int max_weight = 10;
    const std::vector<knapsack::Item> items{{100, 1}};
    REQUIRE(knapsack::maximum_value(max_weight, items) == 0);
}

TEST(Knapsack, T003_five_items_cannot_be_greedy_by_weight) {
    int max_weight = 10;
    const std::vector<knapsack::Item> items{
        {2, 5}, {2, 5}, {2, 5}, {2, 5}, {10, 21}};
    REQUIRE(knapsack::maximum_value(max_weight, items) == 21);
}

TEST(Knapsack, T004_five_items_cannot_be_greedy_by_value) {
    int max_weight = 10;
    const std::vector<knapsack::Item> items{
        {2, 20}, {2, 20}, {2, 20}, {2, 20}, {10, 50}};
    REQUIRE(knapsack::maximum_value(max_weight, items) == 80);
}

TEST(Knapsack, T005_example_knapsack) {
    int max_weight = 10;
    const std::vector<knapsack::Item> items{{5, 10}, {4, 40}, {6, 30}, {4, 50}};
    REQUIRE(knapsack::maximum_value(max_weight, items) == 90);
}

TEST(Knapsack, T006_8_items) {
    int max_weight = 104;
    const std::vector<knapsack::Item> items{{25, 350}, {35, 400}, {45, 450},
                                            {5, 20},   {25, 70},  {3, 8},
                                            {2, 5},    {2, 5}};
    REQUIRE(knapsack::maximum_value(max_weight, items) == 900);
}

TEST(Knapsack, T007_15_items) {
    int max_weight = 750;
    const std::vector<knapsack::Item> items{
        {70, 135},  {73, 139},  {77, 149},  {80, 150},  {82, 156},
        {87, 163},  {90, 173},  {94, 184},  {98, 192},  {106, 201},
        {110, 210}, {113, 214}, {115, 221}, {118, 229}, {120, 240}};
    REQUIRE(knapsack::maximum_value(max_weight, items) == 1458);
}

#endif  // EXERCISM_RUN_ALL_TESTS

}  // namespace
