// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "linked_list.h"

namespace {

/*
`delete`cannot be used as a name in C++ as it is reserved.
This track implements `erase` instead.
The tests have been renamed accordingly.
*/

TEST(LinkedList, T001_pop_gets_element_from_the_list) {
    linked_list::List<int> llist{};
    llist.push(7);
    REQUIRE(7 == llist.pop());
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(LinkedList, T002_push_pop_respectively_add_remove_at_the_end_of_the_list) {
    linked_list::List<int> llist{};
    llist.push(11);
    llist.push(13);
    REQUIRE(13 == llist.pop());
    REQUIRE(11 == llist.pop());
}

TEST(LinkedList, T003_shift_gets_an_element_from_the_list) {
    linked_list::List<int> llist{};
    llist.push(17);
    REQUIRE(17 == llist.shift());
}

TEST(LinkedList, T004_shift_gets_first_element_from_the_list) {
    linked_list::List<int> llist{};
    llist.push(23);
    llist.push(5);
    REQUIRE(23 == llist.shift());
    REQUIRE(5 == llist.shift());
}

TEST(LinkedList, T005_unshift_adds_element_at_start_of_the_list) {
    linked_list::List<int> llist{};
    llist.unshift(23);
    llist.unshift(5);
    REQUIRE(5 == llist.shift());
    REQUIRE(23 == llist.shift());
}

TEST(LinkedList, T006_pop_push_shift_and_unshift_can_be_used_in_any_order) {
    linked_list::List<int> llist{};
    llist.push(1);
    llist.push(2);
    REQUIRE(2 == llist.pop());
    llist.push(3);
    REQUIRE(1 == llist.shift());
    llist.unshift(4);
    llist.push(5);
    REQUIRE(4 == llist.shift());
    REQUIRE(5 == llist.pop());
    REQUIRE(3 == llist.shift());
}

TEST(LinkedList, T007_count_an_empty_list) {
    linked_list::List<int> llist{};
    REQUIRE(0 == llist.count());
}

TEST(LinkedList, T008_count_a_list_with_items) {
    linked_list::List<int> llist{};
    llist.push(37);
    llist.push(1);
    REQUIRE(2 == llist.count());
}

TEST(LinkedList, T009_count_is_correct_after_mutation) {
    linked_list::List<int> llist{};
    llist.push(31);
    REQUIRE(1 == llist.count());
    llist.unshift(43);
    REQUIRE(2 == llist.count());
    llist.shift();
    REQUIRE(1 == llist.count());
    llist.pop();
    REQUIRE(0 == llist.count());
}

TEST(LinkedList, T010_popping_to_empty_doesn_t_break_the_list) {
    linked_list::List<int> llist{};
    llist.push(41);
    llist.push(59);
    llist.pop();
    llist.pop();
    llist.push(47);
    REQUIRE(1 == llist.count());
    REQUIRE(47 == llist.pop());
}

TEST(LinkedList, T011_shifting_to_empty_doesn_t_break_the_list) {
    linked_list::List<int> llist{};
    llist.push(41);
    llist.push(59);
    llist.shift();
    llist.shift();
    llist.push(47);
    REQUIRE(1 == llist.count());
    REQUIRE(47 == llist.shift());
}

TEST(LinkedList, T012_erases_the_only_element) {
    linked_list::List<int> llist{};
    llist.push(61);
    llist.erase(61);
    REQUIRE(0 == llist.count());
}

TEST(LinkedList, T013_erases_the_element_with_the_specified_value_from_the_list) {
    linked_list::List<int> llist{};
    llist.push(71);
    llist.push(83);
    llist.push(79);
    llist.erase(83);
    REQUIRE(2 == llist.count());
    REQUIRE(79 == llist.pop());
    REQUIRE(71 == llist.shift());
}

TEST(LinkedList, T014_erases_the_element_with_the_specified_value_from_the_list_re) {
    linked_list::List<int> llist{};
    llist.push(71);
    llist.push(83);
    llist.push(79);
    llist.erase(83);
    REQUIRE(2 == llist.count());
    REQUIRE(79 == llist.pop());
    REQUIRE(71 == llist.pop());
}

TEST(LinkedList, T015_erases_the_element_with_the_specified_value_from_the_list_re) {
    linked_list::List<int> llist{};
    llist.push(71);
    llist.push(83);
    llist.push(79);
    llist.erase(83);
    REQUIRE(2 == llist.count());
    REQUIRE(71 == llist.shift());
    REQUIRE(79 == llist.shift());
}

TEST(LinkedList, T016_erases_the_first_of_two_elements) {
    linked_list::List<int> llist{};
    llist.push(97);
    llist.push(101);
    llist.erase(97);
    REQUIRE(1 == llist.count());
    REQUIRE(101 == llist.pop());
}

TEST(LinkedList, T017_erases_the_second_of_two_elements) {
    linked_list::List<int> llist{};
    llist.push(97);
    llist.push(101);
    llist.erase(101);
    REQUIRE(1 == llist.count());
    REQUIRE(97 == llist.pop());
}

TEST(LinkedList, T018_erase_does_not_modify_the_list_if_the_element_is_not_found) {
    linked_list::List<int> llist{};
    llist.push(89);
    llist.erase(103);
    REQUIRE(1 == llist.count());
}

TEST(LinkedList, T019_erases_only_the_first_occurrence) {
    linked_list::List<int> llist{};
    llist.push(73);
    llist.push(9);
    llist.push(9);
    llist.push(107);
    llist.erase(9);
    REQUIRE(3 == llist.count());
    REQUIRE(107 == llist.pop());
    REQUIRE(9 == llist.pop());
    REQUIRE(73 == llist.pop());
}

#endif

}  // namespace
