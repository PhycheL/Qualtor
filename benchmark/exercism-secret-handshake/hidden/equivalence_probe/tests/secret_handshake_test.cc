// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include <string>
#include <vector>

#include "secret_handshake.h"

namespace {

using namespace std;

// Secret-handshake exercise test case data version 1.2.1

TEST(SecretHandshake, T001_wink_for_1) {
    REQUIRE(vector<string>{"wink"} == secret_handshake::commands(1));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(SecretHandshake, T002_double_blink_for_10) {
    REQUIRE(vector<string>{"double blink"} == secret_handshake::commands(2));
}

TEST(SecretHandshake, T003_close_your_eyes_for_100) {
    REQUIRE(vector<string>{"close your eyes"} == secret_handshake::commands(4));
}

TEST(SecretHandshake, T004_jump_for_1000) {
    REQUIRE(vector<string>{"jump"} == secret_handshake::commands(8));
}

TEST(SecretHandshake, T005_combine_two_actions) {
    REQUIRE(vector<string>{"wink", "double blink"} ==
            secret_handshake::commands(3));
}

TEST(SecretHandshake, T006_reverse_two_actions) {
    REQUIRE(vector<string>{"double blink", "wink"} ==
            secret_handshake::commands(19));
}

TEST(SecretHandshake, T007_reversing_one_action_gives_the_same_action) {
    REQUIRE(vector<string>{"jump"} == secret_handshake::commands(24));
}

TEST(SecretHandshake, T008_reversing_no_actions_still_gives_no_actions) {
    REQUIRE(vector<string>{} == secret_handshake::commands(16));
}

TEST(SecretHandshake, T009_all_possible_actions) {
    REQUIRE(vector<string>{"wink", "double blink", "close your eyes", "jump"} ==
            secret_handshake::commands(15));
}

TEST(SecretHandshake, T010_reverse_all_possible_actions) {
    REQUIRE(vector<string>{"jump", "close your eyes", "double blink", "wink"} ==
            secret_handshake::commands(31));
}

TEST(SecretHandshake, T011_do_nothing_for_zero) {
    REQUIRE(vector<string>{} == secret_handshake::commands(0));
}

#endif  // !EXERCISM_RUN_ALL_TESTS

}  // namespace
