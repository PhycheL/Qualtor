// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
// Include the header file with the definitions of the functions you create.
#include "simple_linked_list.h"

namespace {

// Include the test framework.

// Declares a single test.
TEST(SimpleLinkedList, T001_EmptyListHasSizeZero) {
    simple_linked_list::List empty{};
    REQUIRE(empty.size() == 0);
}

#ifdef EXERCISM_RUN_ALL_TESTS

TEST(SimpleLinkedList, T002_SingletonListHasSizeOne) {
    simple_linked_list::List list{};
    list.push(44);
    REQUIRE(list.size() == 1);
}

TEST(SimpleLinkedList, T003_NonEmptyListHasCorrectSize) {
    simple_linked_list::List list{};
    list.push(44);
    list.push(42);
    list.push(47);
    list.push(-11);
    REQUIRE(list.size() == 4);
}

TEST(SimpleLinkedList, T004_ListHasCorrectSizeAfterPop) {
    simple_linked_list::List list{};
    list.push(24);
    list.push(2);
    list.push(17);
    list.pop();
    REQUIRE(list.size() == 2);
}

TEST(SimpleLinkedList, T005_ListHasCorrectSizeAfterPopAndPush) {
    simple_linked_list::List list{};
    list.push(242);
    list.push(21);
    list.push(-17);
    list.pop();
    list.push(34);
    REQUIRE(list.size() == 3);
}

TEST(SimpleLinkedList, T006_PopFromSize1) {
    simple_linked_list::List list{};
    auto desired = 142;
    list.push(desired);
    auto actual = list.pop();
    REQUIRE(actual == desired);
}

TEST(SimpleLinkedList, T007_PopFromSizeTwo) {
    simple_linked_list::List list{};
    auto desired_top = 112;
    auto desired_bottom = 221;
    list.push(desired_bottom);
    list.push(desired_top);
    auto actual_top = list.pop();
    REQUIRE(actual_top == desired_top);
    auto actual_bottom = list.pop();
    REQUIRE(actual_bottom == desired_bottom);
}

TEST(SimpleLinkedList, T008_PopAndPushList) {
    simple_linked_list::List list{};

    list.push(1);
    list.push(2);
    list.push(3);
    auto third = list.pop();
    list.push(4);
    list.push(5);
    auto fifth = list.pop();
    auto forth = list.pop();
    auto second = list.pop();
    list.push(6);
    auto sixth = list.pop();
    auto first = list.pop();
    REQUIRE(first == 1);
    REQUIRE(second == 2);
    REQUIRE(third == 3);
    REQUIRE(forth == 4);
    REQUIRE(fifth == 5);
    REQUIRE(sixth == 6);
}

TEST(SimpleLinkedList, T009_ReverseEmptyList) {
    simple_linked_list::List empty{};
    empty.reverse();
    REQUIRE(empty.size() == 0);
}

TEST(SimpleLinkedList, T010_ReverseNonEmptyList) {
    simple_linked_list::List list{};
    for (int i = 0; i < 5; i++) {
        list.push(i);
    }

    list.reverse();

    for (int i = 0; i < 5; i++) {
        REQUIRE(list.pop() == i);
    }
}
#endif

}  // namespace
