// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "resistor_color_duo.h"

namespace {

TEST(ResistorColorDuo, T001_Brown_and_black) {
    REQUIRE(10 == resistor_color_duo::value({"brown", "black"}));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(ResistorColorDuo, T002_Blue_and_grey) {
    REQUIRE(68 == resistor_color_duo::value({"blue", "grey"}));
}

TEST(ResistorColorDuo, T003_Yellow_and_violet) {
    REQUIRE(47 == resistor_color_duo::value({"yellow", "violet"}));
}

TEST(ResistorColorDuo, T004_White_and_red) {
    REQUIRE(92 == resistor_color_duo::value({"white", "red"}));
}

TEST(ResistorColorDuo, T005_Orange_and_orange) {
    REQUIRE(33 == resistor_color_duo::value({"orange", "orange"}));
}

TEST(ResistorColorDuo, T006_Ignore_additional_colors) {
    REQUIRE(51 == resistor_color_duo::value({"green", "brown", "orange"}));
}

TEST(ResistorColorDuo, T007_Black_and_brown_one_digit) {
    REQUIRE(1 == resistor_color_duo::value({"black", "brown"}));
}

#endif

}  // namespace
