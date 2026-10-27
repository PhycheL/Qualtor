// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "sublist.h"

namespace {

/*
Lists are ordered and sequential.
https://en.wikipedia.org/wiki/List_%28abstract_data_type%29

Depending on your language, there may need to be some translation
to go from the JSON array to the list representation.
The expectation can be used to generate an expected value
based on your implementation (such as a constant 'EQUAL', 'SUBLIST', etc.).

If appropriate for your track, you'll need to ensure that no pair of expected
values are equal. Otherwise, an implementation that always returns a constant
value may falsely pass the tests. See
https://github.com/exercism/xpython/issues/342
*/

CATCH_REGISTER_ENUM(sublist::List_comparison, sublist::List_comparison::equal,
                    sublist::List_comparison::sublist,
                    sublist::List_comparison::superlist,
                    sublist::List_comparison::unequal)

TEST(Sublist, T001_empty_lists) {
    sublist::List_comparison expected = sublist::List_comparison::equal;
    REQUIRE(expected == sublist::sublist({}, {}));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(Sublist, T002_empty_list_within_non_empty_list) {
    sublist::List_comparison expected = sublist::List_comparison::sublist;
    REQUIRE(expected == sublist::sublist({}, {1, 2, 3}));
}

TEST(Sublist, T003_non_empty_list_contains_empty_list) {
    sublist::List_comparison expected = sublist::List_comparison::superlist;
    REQUIRE(expected == sublist::sublist({1, 2, 3}, {}));
}

TEST(Sublist, T004_list_equals_itself) {
    sublist::List_comparison expected = sublist::List_comparison::equal;
    REQUIRE(expected == sublist::sublist({1, 2, 3}, {1, 2, 3}));
}

TEST(Sublist, T005_different_lists) {
    sublist::List_comparison expected = sublist::List_comparison::unequal;
    REQUIRE(expected == sublist::sublist({1, 2, 3}, {2, 3, 4}));
}

TEST(Sublist, T006_false_start) {
    sublist::List_comparison expected = sublist::List_comparison::sublist;
    REQUIRE(expected == sublist::sublist({1, 2, 5}, {0, 1, 2, 3, 1, 2, 5, 6}));
}

TEST(Sublist, T007_consecutive) {
    sublist::List_comparison expected = sublist::List_comparison::sublist;
    REQUIRE(expected == sublist::sublist({1, 1, 2}, {0, 1, 1, 1, 2, 1, 2}));
}

TEST(Sublist, T008_sublist_at_start) {
    sublist::List_comparison expected = sublist::List_comparison::sublist;
    REQUIRE(expected == sublist::sublist({0, 1, 2}, {0, 1, 2, 3, 4, 5}));
}

TEST(Sublist, T009_sublist_in_middle) {
    sublist::List_comparison expected = sublist::List_comparison::sublist;
    REQUIRE(expected == sublist::sublist({2, 3, 4}, {0, 1, 2, 3, 4, 5}));
}

TEST(Sublist, T010_sublist_at_end) {
    sublist::List_comparison expected = sublist::List_comparison::sublist;
    REQUIRE(expected == sublist::sublist({3, 4, 5}, {0, 1, 2, 3, 4, 5}));
}

TEST(Sublist, T011_at_start_of_superlist) {
    sublist::List_comparison expected = sublist::List_comparison::superlist;
    REQUIRE(expected == sublist::sublist({0, 1, 2, 3, 4, 5}, {0, 1, 2}));
}

TEST(Sublist, T012_in_middle_of_superlist) {
    sublist::List_comparison expected = sublist::List_comparison::superlist;
    REQUIRE(expected == sublist::sublist({0, 1, 2, 3, 4, 5}, {2, 3}));
}

TEST(Sublist, T013_at_end_of_superlist) {
    sublist::List_comparison expected = sublist::List_comparison::superlist;
    REQUIRE(expected == sublist::sublist({0, 1, 2, 3, 4, 5}, {3, 4, 5}));
}

TEST(Sublist, T014_first_list_missing_element_from_second_list) {
    sublist::List_comparison expected = sublist::List_comparison::unequal;
    REQUIRE(expected == sublist::sublist({1, 3}, {1, 2, 3}));
}

TEST(Sublist, T015_second_list_missing_element_from_first_list) {
    sublist::List_comparison expected = sublist::List_comparison::unequal;
    REQUIRE(expected == sublist::sublist({1, 2, 3}, {1, 3}));
}

TEST(Sublist, T016_first_list_missing_additional_digits_from_second_list) {
    sublist::List_comparison expected = sublist::List_comparison::unequal;
    REQUIRE(expected == sublist::sublist({1, 2}, {1, 22}));
}

TEST(Sublist, T017_order_matters_to_a_list) {
    sublist::List_comparison expected = sublist::List_comparison::unequal;
    REQUIRE(expected == sublist::sublist({1, 2, 3}, {3, 2, 1}));
}

TEST(Sublist, T018_same_digits_but_different_numbers) {
    sublist::List_comparison expected = sublist::List_comparison::unequal;
    REQUIRE(expected == sublist::sublist({1, 0, 1}, {10, 1}));
}

#endif

}  // namespace
