// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "trinary.h"

namespace {

TEST(Trinary, T001_1_yields_decimal_1) { REQUIRE(1 == trinary::to_decimal("1")); }

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Trinary, T002_2_yields_decimal_2) { REQUIRE(2 == trinary::to_decimal("2")); }

TEST(Trinary, T003_10_yields_decimal_3) { REQUIRE(3 == trinary::to_decimal("10")); }

TEST(Trinary, T004_11_yields_decimal_4) { REQUIRE(4 == trinary::to_decimal("11")); }

TEST(Trinary, T005_100_yields_decimal_9) { REQUIRE(9 == trinary::to_decimal("100")); }

TEST(Trinary, T006_112_yields_decimal_14) {
    REQUIRE(14 == trinary::to_decimal("112"));
}

TEST(Trinary, T007_222_yields_decimal_26) {
    REQUIRE(26 == trinary::to_decimal("222"));
}

TEST(Trinary, T008_1122000120_yields_decimal_32091) {
    REQUIRE(32091 == trinary::to_decimal("1122000120"));
}

TEST(Trinary, T009_invalid_yields_decimal_0) {
    REQUIRE(0 == trinary::to_decimal("carrot"));
}
#endif

}  // namespace
