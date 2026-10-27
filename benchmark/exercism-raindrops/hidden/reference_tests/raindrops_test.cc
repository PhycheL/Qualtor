// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "raindrops.h"

namespace {

TEST(Raindrops, T001_the_sound_for_1_is_1) { REQUIRE("1" == raindrops::convert(1)); }
#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Raindrops, T002_the_sound_for_3_is_pling) {
    REQUIRE("Pling" == raindrops::convert(3));
}
TEST(Raindrops, T003_the_sound_for_5_is_plang) {
    REQUIRE("Plang" == raindrops::convert(5));
}
TEST(Raindrops, T004_the_sound_for_7_is_plong) {
    REQUIRE("Plong" == raindrops::convert(7));
}
TEST(Raindrops, T005_the_sound_for_6_is_pling_as_it_has_a_factor_3) {
    REQUIRE("Pling" == raindrops::convert(6));
}
TEST(Raindrops, T006_2_to_the_power_3_does_not_make_a_raindrop_sound_as_3_is_the) {
    REQUIRE("8" == raindrops::convert(8));
}
TEST(Raindrops, T007_the_sound_for_9_is_pling_as_it_has_a_factor_3) {
    REQUIRE("Pling" == raindrops::convert(9));
}
TEST(Raindrops, T008_the_sound_for_10_is_plang_as_it_has_a_factor_5) {
    REQUIRE("Plang" == raindrops::convert(10));
}
TEST(Raindrops, T009_the_sound_for_14_is_plong_as_it_has_a_factor_of_7) {
    REQUIRE("Plong" == raindrops::convert(14));
}
TEST(Raindrops, T010_the_sound_for_15_is_plingplang_as_it_has_factors_3_and_5) {
    REQUIRE("PlingPlang" == raindrops::convert(15));
}
TEST(Raindrops, T011_the_sound_for_21_is_plingplong_as_it_has_factors_3_and_7) {
    REQUIRE("PlingPlong" == raindrops::convert(21));
}
TEST(Raindrops, T012_the_sound_for_25_is_plang_as_it_has_a_factor_5) {
    REQUIRE("Plang" == raindrops::convert(25));
}
TEST(Raindrops, T013_the_sound_for_27_is_pling_as_it_has_a_factor_3) {
    REQUIRE("Pling" == raindrops::convert(27));
}
TEST(Raindrops, T014_the_sound_for_35_is_plangplong_as_it_has_factors_5_and_7) {
    REQUIRE("PlangPlong" == raindrops::convert(35));
}
TEST(Raindrops, T015_the_sound_for_49_is_plong_as_it_has_a_factor_7) {
    REQUIRE("Plong" == raindrops::convert(49));
}
TEST(Raindrops, T016_the_sound_for_52_is_52) { REQUIRE("52" == raindrops::convert(52)); }
TEST(Raindrops, T017_the_sound_for_105_is_plingplangplong_as_it_has_factors_3_5_a) {
    REQUIRE("PlingPlangPlong" == raindrops::convert(105));
}
TEST(Raindrops, T018_the_sound_for_3125_is_plang_as_it_has_a_factor_5) {
    REQUIRE("Plang" == raindrops::convert(3125));
}
#endif

}  // namespace
