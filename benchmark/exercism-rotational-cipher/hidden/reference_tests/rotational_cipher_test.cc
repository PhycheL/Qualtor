// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "rotational_cipher.h"

namespace {

/*
The tests are a series of rotation tests:
*/

TEST(RotationalCipher, T001_rotate_a_by_0_same_output_as_input) {
    REQUIRE(rotational_cipher::rotate("a", 0) == "a");
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(RotationalCipher, T002_rotate_a_by_1) {
    REQUIRE(rotational_cipher::rotate("a", 1) == "b");
}

TEST(RotationalCipher, T003_rotate_a_by_26_same_output_as_input) {
    REQUIRE(rotational_cipher::rotate("a", 26) == "a");
}

TEST(RotationalCipher, T004_rotate_m_by_13) {
    REQUIRE(rotational_cipher::rotate("m", 13) == "z");
}

TEST(RotationalCipher, T005_rotate_n_by_13_with_wrap_around_alphabet) {
    REQUIRE(rotational_cipher::rotate("n", 13) == "a");
}

TEST(RotationalCipher, T006_rotate_capital_letters) {
    REQUIRE(rotational_cipher::rotate("OMG", 5) == "TRL");
}

TEST(RotationalCipher, T007_rotate_spaces) {
    REQUIRE(rotational_cipher::rotate("O M G", 5) == "T R L");
}

TEST(RotationalCipher, T008_rotate_numbers) {
    REQUIRE(rotational_cipher::rotate("Testing 1 2 3 testing", 4) ==
            "Xiwxmrk 1 2 3 xiwxmrk");
}

TEST(RotationalCipher, T009_rotate_punctuation) {
    REQUIRE(rotational_cipher::rotate("Let's eat, Grandma!", 21) ==
            "Gzo'n zvo, Bmviyhv!");
}

TEST(RotationalCipher, T010_rotate_all_letters) {
    REQUIRE(rotational_cipher::rotate(
                "The quick brown fox jumps over the lazy dog.", 13) ==
            "Gur dhvpx oebja sbk whzcf bire gur ynml qbt.");
}

#endif

}  // namespace
