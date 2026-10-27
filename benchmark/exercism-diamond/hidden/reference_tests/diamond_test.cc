// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "diamond.h"

namespace {

/*
 The tests contained within this canonical data file are suitable
 for value-based testing, in which each test case checks that the
 value returned by the function under test is in every way
 identical to a given expected value.

 This exercise is also amenable to property-based testing, in which
 each test case verifies that the value returned by the function
 under test exhibits a specific desired property.

 Several tracks (notably, C# and Go) forgo the value-based tests
 below in favor of property-based tests. If you are feeling
 adventurous and would like to use this exercise to introduce the
 concept of property-based testing to participants in your track,
 please ignore the value-based tests below and instead reference
 the test suites in the aforementioned tracks.
*/

TEST(Diamond, T001_Degenerate_case_with_a_single_A_row) {
    std::vector<std::string> expected{"A"};
    REQUIRE(diamond::rows('A') == expected);
}

TEST(Diamond, T002_Degenerate_case_with_no_row_containing_3_distinct_groups_of) {
    std::vector<std::string> expected{" A ", "B B", " A "};
    REQUIRE(diamond::rows('B') == expected);
}

TEST(Diamond, T003_Smallest_non_degenerate_case_with_odd_diamond_side_length) {
    std::vector<std::string> expected{"  A  ", " B B ", "C   C", " B B ",
                                      "  A  "};
    REQUIRE(diamond::rows('C') == expected);
}

TEST(Diamond, T004_Smallest_non_degenerate_case_with_even_diamond_side_length) {
    std::vector<std::string> expected{"   A   ", "  B B  ", " C   C ",
                                      "D     D", " C   C ", "  B B  ",
                                      "   A   "};
    REQUIRE(diamond::rows('D') == expected);
}

TEST(Diamond, T005_Largest_possible_diamond) {
    std::vector<std::string> expected{
        "                         A                         ",
        "                        B B                        ",
        "                       C   C                       ",
        "                      D     D                      ",
        "                     E       E                     ",
        "                    F         F                    ",
        "                   G           G                   ",
        "                  H             H                  ",
        "                 I               I                 ",
        "                J                 J                ",
        "               K                   K               ",
        "              L                     L              ",
        "             M                       M             ",
        "            N                         N            ",
        "           O                           O           ",
        "          P                             P          ",
        "         Q                               Q         ",
        "        R                                 R        ",
        "       S                                   S       ",
        "      T                                     T      ",
        "     U                                       U     ",
        "    V                                         V    ",
        "   W                                           W   ",
        "  X                                             X  ",
        " Y                                               Y ",
        "Z                                                 Z",
        " Y                                               Y ",
        "  X                                             X  ",
        "   W                                           W   ",
        "    V                                         V    ",
        "     U                                       U     ",
        "      T                                     T      ",
        "       S                                   S       ",
        "        R                                 R        ",
        "         Q                               Q         ",
        "          P                             P          ",
        "           O                           O           ",
        "            N                         N            ",
        "             M                       M             ",
        "              L                     L              ",
        "               K                   K               ",
        "                J                 J                ",
        "                 I               I                 ",
        "                  H             H                  ",
        "                   G           G                   ",
        "                    F         F                    ",
        "                     E       E                     ",
        "                      D     D                      ",
        "                       C   C                       ",
        "                        B B                        ",
        "                         A                         "};
    REQUIRE(diamond::rows('Z') == expected);
}
#if defined(EXERCISM_RUN_ALL_TESTS)
#endif

}  // namespace
