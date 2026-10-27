// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "darts.h"

namespace {

TEST(Darts, T001_missed_target) { REQUIRE(darts::score(-9, 9) == 0); }

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Darts, T002_on_the_outer_circle) { REQUIRE(darts::score(0, 10) == 1); }

TEST(Darts, T003_on_the_middle_circle) { REQUIRE(darts::score(-5, 0) == 5); }

TEST(Darts, T004_on_the_inner_circle) { REQUIRE(darts::score(0, -1) == 10); }

TEST(Darts, T005_exactly_on_centre) { REQUIRE(darts::score(0, 0) == 10); }

TEST(Darts, T006_near_the_centre) { REQUIRE(darts::score(-0.1f, -0.1f) == 10); }

TEST(Darts, T007_just_within_the_inner_circle) {
    REQUIRE(darts::score(0.7f, 0.7f) == 10);
}

TEST(Darts, T008_just_outside_the_inner_circle) {
    REQUIRE(darts::score(0.8f, -0.8f) == 5);
}

TEST(Darts, T009_just_within_the_middle_circle) {
    REQUIRE(darts::score(-3.5f, 3.5f) == 5);
}

TEST(Darts, T010_just_outside_the_middle_circle) {
    REQUIRE(darts::score(-3.6f, -3.6f) == 1);
}

TEST(Darts, T011_just_within_the_outer_circle) {
    REQUIRE(darts::score(-7.0f, 7.0f) == 1);
}

TEST(Darts, T012_just_outside_the_outer_circle) {
    REQUIRE(darts::score(7.1f, -7.1f) == 0);
}

TEST(Darts, T013_asymmetric_position_between_the_inner_and_middle_circles) {
    REQUIRE(darts::score(0.5f, -4) == 5);
}
#endif

}  // namespace
