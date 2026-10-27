// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "resistor_color.h"

namespace {

TEST(ResistorColor, T001_Black) {
    REQUIRE(0 == resistor_color::color_code("black"));
}

TEST(ResistorColor, T002_White) {
    REQUIRE(9 == resistor_color::color_code("white"));
}

TEST(ResistorColor, T003_Orange) {
    REQUIRE(3 == resistor_color::color_code("orange"));
}

TEST(ResistorColor, T004_Colors) {
    std::vector<std::string> expected{"black",  "brown", "red",  "orange",
                                      "yellow", "green", "blue", "violet",
                                      "grey",   "white"};
    REQUIRE(expected == resistor_color::colors());
}
#if defined(EXERCISM_RUN_ALL_TESTS)

#endif

}  // namespace
