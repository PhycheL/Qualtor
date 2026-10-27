// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "series.h"
#include <stdexcept>

namespace {
using namespace std;

TEST(Series, T001_slices_of_one_from_one) {
    const vector<string> expected{"1"};

    const vector<string> actual{series::slice("1", 1)};

    REQUIRE(expected == actual);
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Series, T002_slices_of_one_from_two) {
    const vector<string> expected{"1", "2"};

    const vector<string> actual{series::slice("12", 1)};

    REQUIRE(expected == actual);
}

TEST(Series, T003_slices_of_two) {
    const vector<string> expected{"35"};

    const vector<string> actual{series::slice("35", 2)};

    REQUIRE(expected == actual);
}

TEST(Series, T004_slices_of_two_overlap) {
    const vector<string> expected{"91", "14", "42"};

    const vector<string> actual{series::slice("9142", 2)};

    REQUIRE(expected == actual);
}

TEST(Series, T005_slices_can_include_duplicates) {
    const vector<string> expected{"777", "777", "777", "777"};

    const vector<string> actual{series::slice("777777", 3)};

    REQUIRE(expected == actual);
}

TEST(Series, T006_slices_of_a_long_series) {
    const vector<string> expected{"91849", "18493", "84939", "49390",
                                  "93904", "39042", "90424", "04243"};

    const vector<string> actual{series::slice("918493904243", 5)};

    REQUIRE(expected == actual);
}

TEST(Series, T007_slice_length_is_too_large) {
    REQUIRE_THROWS_AS(series::slice("12345", 6), domain_error);
}

TEST(Series, T008_slice_length_cannot_be_zero) {
    REQUIRE_THROWS_AS(series::slice("12345", 0), domain_error);
}

TEST(Series, T009_slice_length_cannot_be_negative) {
    REQUIRE_THROWS_AS(series::slice("123", -1), domain_error);
}

TEST(Series, T010_empty_series_is_invalid) {
    REQUIRE_THROWS_AS(series::slice("", 1), domain_error);
}
#endif

}  // namespace
