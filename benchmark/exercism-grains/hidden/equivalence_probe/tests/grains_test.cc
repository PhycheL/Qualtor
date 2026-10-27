// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "grains.h"

namespace {

TEST(Grains, T001_square_1) { REQUIRE(1ULL == grains::square(1)); }

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Grains, T002_square_2) { REQUIRE(2ULL == grains::square(2)); }

TEST(Grains, T003_square_3) { REQUIRE(4ULL == grains::square(3)); }

TEST(Grains, T004_square_4) { REQUIRE(8ULL == grains::square(4)); }

TEST(Grains, T005_square_16) { REQUIRE(32768ULL == grains::square(16)); }

TEST(Grains, T006_square_32) { REQUIRE(2147483648ULL == grains::square(32)); }

TEST(Grains, T007_square_64) {
    REQUIRE(9223372036854775808ULL == grains::square(64));
}

TEST(Grains, T008_total) { REQUIRE(18446744073709551615ULL == grains::total()); }
#endif

}  // namespace
