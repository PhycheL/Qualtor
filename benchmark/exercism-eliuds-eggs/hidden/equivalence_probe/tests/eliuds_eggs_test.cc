// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "eliuds_eggs.h"

namespace {

TEST(EliudsEggs, T001_0_eggs) { REQUIRE(chicken_coop::positions_to_quantity(0) == 0); }

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(EliudsEggs, T002_1_egg) { REQUIRE(chicken_coop::positions_to_quantity(16) == 1); }

TEST(EliudsEggs, T003_4_eggs) { REQUIRE(chicken_coop::positions_to_quantity(89) == 4); }

TEST(EliudsEggs, T004_13_eggs) {
    REQUIRE(chicken_coop::positions_to_quantity(2000000000) == 13);
}

#endif

}  // namespace
