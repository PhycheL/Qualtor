// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "zebra_puzzle.h"

namespace {

TEST(ZebraPuzzle, T001_drinks_water) {
    zebra_puzzle::Solution solution = zebra_puzzle::solve();

    SECTION("Drinks water") { REQUIRE(solution.drinksWater == "Norwegian"); }
}

TEST(ZebraPuzzle, T002_owns_zebra) {
    zebra_puzzle::Solution solution = zebra_puzzle::solve();

    SECTION("Owns zebra") { REQUIRE(solution.ownsZebra == "Japanese"); }
}

}  // namespace
