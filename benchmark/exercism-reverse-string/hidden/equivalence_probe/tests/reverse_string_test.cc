// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "reverse_string.h"

namespace {

TEST(ReverseString, T001_an_empty_string) {
    REQUIRE("" == reverse_string::reverse_string(""));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(ReverseString, T002_a_word) {
    REQUIRE("tobor" == reverse_string::reverse_string("robot"));
}

TEST(ReverseString, T003_a_capitalized_word) {
    REQUIRE("nemaR" == reverse_string::reverse_string("Ramen"));
}

TEST(ReverseString, T004_a_sentence_with_punctuation) {
    REQUIRE("!yrgnuh m'I" == reverse_string::reverse_string("I'm hungry!"));
}

TEST(ReverseString, T005_a_palindrome) {
    REQUIRE("racecar" == reverse_string::reverse_string("racecar"));
}
#endif

}  // namespace
