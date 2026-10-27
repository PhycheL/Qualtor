// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "hexadecimal.h"

namespace {

TEST(Hexadecimal, T001_hex_1_is_decimal_1) { REQUIRE(0x1 == hexadecimal::convert("1")); }

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Hexadecimal, T002_hex_c_is_decimal_12) { REQUIRE(0xc == hexadecimal::convert("c")); }

TEST(Hexadecimal, T003_hex_10_is_decimal_16) {
    REQUIRE(0x10 == hexadecimal::convert("10"));
}

TEST(Hexadecimal, T004_hex_af_is_decimal_175) {
    REQUIRE(0xaf == hexadecimal::convert("af"));
}

TEST(Hexadecimal, T005_hex_100_is_decimal_256) {
    REQUIRE(0x100 == hexadecimal::convert("100"));
}

TEST(Hexadecimal, T006_hex_19ace_is_decimal_105166) {
    REQUIRE(0x19ace == hexadecimal::convert("19ace"));
}

TEST(Hexadecimal, T007_invalid_hex_is_decimal_0) {
    REQUIRE(0 == hexadecimal::convert("carrot"));
}

TEST(Hexadecimal, T008_black) { REQUIRE(0x000000 == hexadecimal::convert("000000")); }

TEST(Hexadecimal, T009_white) { REQUIRE(0xffffff == hexadecimal::convert("ffffff")); }

TEST(Hexadecimal, T010_yellow) { REQUIRE(0xffff00 == hexadecimal::convert("ffff00")); }
#endif

}  // namespace
