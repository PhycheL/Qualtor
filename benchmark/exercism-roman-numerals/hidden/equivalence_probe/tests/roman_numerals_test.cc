// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "roman_numerals.h"

namespace {

TEST(RomanNumerals, T001_1_is_i) { REQUIRE("I" == roman_numerals::convert(1)); }
#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(RomanNumerals, T002_2_is_ii) { REQUIRE("II" == roman_numerals::convert(2)); }
TEST(RomanNumerals, T003_3_is_iii) { REQUIRE("III" == roman_numerals::convert(3)); }
TEST(RomanNumerals, T004_4_is_iv) { REQUIRE("IV" == roman_numerals::convert(4)); }
TEST(RomanNumerals, T005_5_is_v) { REQUIRE("V" == roman_numerals::convert(5)); }
TEST(RomanNumerals, T006_6_is_vi) { REQUIRE("VI" == roman_numerals::convert(6)); }
TEST(RomanNumerals, T007_9_is_ix) { REQUIRE("IX" == roman_numerals::convert(9)); }
TEST(RomanNumerals, T008_16_is_xvi) { REQUIRE("XVI" == roman_numerals::convert(16)); }
TEST(RomanNumerals, T009_27_is_xxvii) { REQUIRE("XXVII" == roman_numerals::convert(27)); }
TEST(RomanNumerals, T010_48_is_xlviii) { REQUIRE("XLVIII" == roman_numerals::convert(48)); }
TEST(RomanNumerals, T011_49_is_xlix) { REQUIRE("XLIX" == roman_numerals::convert(49)); }
TEST(RomanNumerals, T012_59_is_lix) { REQUIRE("LIX" == roman_numerals::convert(59)); }
TEST(RomanNumerals, T013_66_is_lxvi) { REQUIRE("LXVI" == roman_numerals::convert(66)); }
TEST(RomanNumerals, T014_93_is_xciii) { REQUIRE("XCIII" == roman_numerals::convert(93)); }
TEST(RomanNumerals, T015_141_is_cxli) { REQUIRE("CXLI" == roman_numerals::convert(141)); }
TEST(RomanNumerals, T016_163_is_clxiii) {
    REQUIRE("CLXIII" == roman_numerals::convert(163));
}
TEST(RomanNumerals, T017_166_is_clxvi) { REQUIRE("CLXVI" == roman_numerals::convert(166)); }
TEST(RomanNumerals, T018_402_is_cdii) { REQUIRE("CDII" == roman_numerals::convert(402)); }
TEST(RomanNumerals, T019_575_is_dlxxv) { REQUIRE("DLXXV" == roman_numerals::convert(575)); }
TEST(RomanNumerals, T020_666_is_dclxvi) {
    REQUIRE("DCLXVI" == roman_numerals::convert(666));
}
TEST(RomanNumerals, T021_911_is_cmxi) { REQUIRE("CMXI" == roman_numerals::convert(911)); }
TEST(RomanNumerals, T022_1024_is_mxxiv) {
    REQUIRE("MXXIV" == roman_numerals::convert(1024));
}
TEST(RomanNumerals, T023_1666_is_mdclxvi) {
    REQUIRE("MDCLXVI" == roman_numerals::convert(1666));
}
TEST(RomanNumerals, T024_3000_is_mmm) { REQUIRE("MMM" == roman_numerals::convert(3000)); }
TEST(RomanNumerals, T025_3001_is_mmmi) { REQUIRE("MMMI" == roman_numerals::convert(3001)); }
TEST(RomanNumerals, T026_3888_is_mmmdccclxxxviii) {
    REQUIRE("MMMDCCCLXXXVIII" == roman_numerals::convert(3888));
}
TEST(RomanNumerals, T027_3999_is_mmmcmxcix) {
    REQUIRE("MMMCMXCIX" == roman_numerals::convert(3999));
}
#endif

}  // namespace
