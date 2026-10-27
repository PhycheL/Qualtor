// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "flower_field.h"

namespace {

/*
 The expected outputs are represented as arrays of strings to
 improve readability in this JSON file.
 Your track may choose whether to present the input as a single
 string (concatenating all the lines) or as the list.
*/

TEST(FlowerField, T001_no_rows) {
    const std::vector<std::string> expected{};
    REQUIRE(expected == flower_field::annotate({}));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(FlowerField, T002_no_columns) {
    const std::vector<std::string> expected{""};
    REQUIRE(expected == flower_field::annotate({""}));
}

TEST(FlowerField, T003_no_flowers) {
    const std::vector<std::string> expected{"   ", "   ", "   "};
    REQUIRE(expected == flower_field::annotate({"   ", "   ", "   "}));
}

TEST(FlowerField, T004_garden_full_of_flowers) {
    const std::vector<std::string> expected{"***", "***", "***"};
    REQUIRE(expected == flower_field::annotate({"***", "***", "***"}));
}

TEST(FlowerField, T005_flower_surrounded_by_spaces) {
    const std::vector<std::string> expected{"111", "1*1", "111"};
    REQUIRE(expected == flower_field::annotate({"   ", " * ", "   "}));
}

TEST(FlowerField, T006_space_surrounded_by_flowers) {
    const std::vector<std::string> expected{"***", "*8*", "***"};
    REQUIRE(expected == flower_field::annotate({"***", "* *", "***"}));
}

TEST(FlowerField, T007_horizontal_line) {
    const std::vector<std::string> expected{"1*2*1"};
    REQUIRE(expected == flower_field::annotate({" * * "}));
}

TEST(FlowerField, T008_horizontal_line_flowers_at_edges) {
    const std::vector<std::string> expected{"*1 1*"};
    REQUIRE(expected == flower_field::annotate({"*   *"}));
}

TEST(FlowerField, T009_vertical_line) {
    const std::vector<std::string> expected{"1", "*", "2", "*", "1"};
    REQUIRE(expected == flower_field::annotate({" ", "*", " ", "*", " "}));
}

TEST(FlowerField, T010_vertical_line_flowers_at_edges) {
    const std::vector<std::string> expected{"*", "1", " ", "1", "*"};
    REQUIRE(expected == flower_field::annotate({"*", " ", " ", " ", "*"}));
}

TEST(FlowerField, T011_cross) {
    const std::vector<std::string> expected{" 2*2 ", "25*52", "*****", "25*52",
                                            " 2*2 "};
    REQUIRE(expected == flower_field::annotate(
                            {"  *  ", "  *  ", "*****", "  *  ", "  *  "}));
}

TEST(FlowerField, T012_large_garden) {
    const std::vector<std::string> expected{"1*22*1", "12*322", " 123*2",
                                            "112*4*", "1*22*2", "111111"};
    REQUIRE(expected == flower_field::annotate({" *  * ", "  *   ", "    * ",
                                                "   * *", " *  * ", "      "}));
}

#endif

}  // namespace
