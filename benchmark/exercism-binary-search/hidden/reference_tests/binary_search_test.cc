// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "binary_search.h"
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace {

using namespace std;

// Binary-Search exercise test case data version 1.3.0

TEST(BinarySearch, T001_finds_a_value_in_an_array_with_one_element) {
    const std::vector<int> data{6};

    const std::size_t actual = binary_search::find(data, 6);

    const std::size_t expected = 0;

    REQUIRE(expected == actual);
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(BinarySearch, T002_finds_a_value_in_the_middle_of_an_array) {
    const std::vector<int> data{1, 3, 4, 6, 8, 9, 11};

    const std::size_t actual = binary_search::find(data, 6);

    const std::size_t expected = 3;

    REQUIRE(expected == actual);
}

TEST(BinarySearch, T003_finds_a_value_at_the_beginning_of_an_array) {
    const std::vector<int> data{1, 3, 4, 6, 8, 9, 11};

    const std::size_t actual = binary_search::find(data, 1);

    const std::size_t expected = 0;

    REQUIRE(expected == actual);
}

TEST(BinarySearch, T004_finds_a_value_at_the_end_of_an_array) {
    const std::vector<int> data{1, 3, 4, 6, 8, 9, 11};

    const std::size_t actual = binary_search::find(data, 11);

    const std::size_t expected = 6;

    REQUIRE(expected == actual);
}

TEST(BinarySearch, T005_finds_a_value_in_an_array_of_odd_length) {
    const std::vector<int> data{1,  3,  5,   8,   13,  21, 34,
                                55, 89, 144, 233, 377, 634};

    const std::size_t actual = binary_search::find(data, 144);

    const std::size_t expected = 9;

    REQUIRE(expected == actual);
}

TEST(BinarySearch, T006_finds_a_value_in_an_array_of_even_length) {
    const std::vector<int> data{1, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377};

    const std::size_t actual = binary_search::find(data, 21);

    const std::size_t expected = 5;

    REQUIRE(expected == actual);
}

TEST(BinarySearch, T007_identifies_that_a_value_is_not_included_in_the_array) {
    const std::vector<int> data{1, 3, 4, 6, 8, 9, 11};

    REQUIRE_THROWS_AS(binary_search::find(data, 7), std::domain_error);
}

TEST(BinarySearch, T008_a_value_smaller_than_the_arrays_smallest_value_is_not_found) {
    const std::vector<int> data{1, 3, 4, 6, 8, 9, 11};

    REQUIRE_THROWS_AS(binary_search::find(data, 0), std::domain_error);
}

TEST(BinarySearch, T009_a_value_larger_than_the_arrays_largest_value_is_not_found) {
    const std::vector<int> data{1, 3, 4, 6, 8, 9, 11};

    REQUIRE_THROWS_AS(binary_search::find(data, 13), std::domain_error);
}

TEST(BinarySearch, T010_nothing_is_found_in_an_empty_array) {
    const std::vector<int> data{};

    REQUIRE_THROWS_AS(binary_search::find(data, 1), std::domain_error);
}

TEST(BinarySearch, T011_nothing_is_found_when_the_left_and_right_bounds_cross) {
    const std::vector<int> data{1, 2};

    REQUIRE_THROWS_AS(binary_search::find(data, 0), std::domain_error);
}

#endif

}  // namespace
