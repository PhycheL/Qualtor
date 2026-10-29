// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "leap.h"

namespace {

TEST(Leap, T001_not_divisible_by_4) { REQUIRE(!leap::is_leap_year(2015)); }

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Leap, T002_divisible_by_2_not_divisible_by_4) {
    REQUIRE(!leap::is_leap_year(1970));
}

TEST(Leap, T003_divisible_by_4_not_divisible_by_100) {
    REQUIRE(leap::is_leap_year(1996));
}

TEST(Leap, T004_divisible_by_100_not_divisible_by_400) {
    REQUIRE(!leap::is_leap_year(2100));
}

TEST(Leap, T005_divisible_by_400) { REQUIRE(leap::is_leap_year(2000)); }

TEST(Leap, T006_divisible_by_200_not_divisible_by_400) {
    REQUIRE(!leap::is_leap_year(1800));
}
#endif

}  // namespace
