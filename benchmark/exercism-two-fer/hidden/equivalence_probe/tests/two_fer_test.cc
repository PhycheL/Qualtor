// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "two_fer.h"
#include <string>

namespace {

// two-fer exercise test case data version 1.2.0

TEST(TwoFer, T001_no_name_given) {
    const std::string actual = two_fer::two_fer();
    const std::string expected = "One for you, one for me.";
    REQUIRE(actual == expected);
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(TwoFer, T002_a_name_given) {
    const std::string name = "Alice";
    const std::string actual = two_fer::two_fer(name);
    const std::string expected = "One for Alice, one for me.";
    REQUIRE(actual == expected);
}

TEST(TwoFer, T003_another_name_given) {
    const std::string name = "Bob";
    const std::string actual = two_fer::two_fer(name);
    const std::string expected = "One for Bob, one for me.";
    REQUIRE(actual == expected);
}
#endif

}  // namespace
