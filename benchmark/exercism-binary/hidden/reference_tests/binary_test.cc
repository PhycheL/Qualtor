// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "binary.h"

namespace {

TEST(Binary, T001_b1_is_decimal_1) { REQUIRE(1 == binary::convert("1")); }

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Binary, T002_b10_is_decimal_2) { REQUIRE(2 == binary::convert("10")); }

TEST(Binary, T003_b11_is_decimal_3) { REQUIRE(3 == binary::convert("11")); }

TEST(Binary, T004_b100_is_decimal_4) { REQUIRE(4 == binary::convert("100")); }

TEST(Binary, T005_b1001_is_decimal_9) { REQUIRE(9 == binary::convert("1001")); }

TEST(Binary, T006_b11010_is_decimal_26) { REQUIRE(26 == binary::convert("11010")); }

TEST(Binary, T007_b10001101000_is_decimal_1128) {
    REQUIRE(1128 == binary::convert("10001101000"));
}

TEST(Binary, T008_carrot_is_decimal_0) { REQUIRE(0 == binary::convert("carrot")); }

TEST(Binary, T009_x1100101b_is_decimal_0) {
    REQUIRE(0 == binary::convert("1100101b"));
}
#endif

}  // namespace
