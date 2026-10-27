// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "affine_cipher.h"

namespace {

TEST(AffineCipher, T001_encode_yes) {
    REQUIRE(affine_cipher::encode("yes", 5, 7) == "xbt");
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(AffineCipher, T002_encode_no) {
    REQUIRE(affine_cipher::encode("no", 15, 18) == "fu");
}

TEST(AffineCipher, T003_encode_OMG) {
    REQUIRE(affine_cipher::encode("OMG", 21, 3) == "lvz");
}

TEST(AffineCipher, T004_encode_O_M_G) {
    REQUIRE(affine_cipher::encode("O M G", 25, 47) == "hjp");
}

TEST(AffineCipher, T005_encode_mindblowingly) {
    REQUIRE(affine_cipher::encode("mindblowingly", 11, 15) ==
            "rzcwa gnxzc dgt");
}

TEST(AffineCipher, T006_encode_numbers) {
    REQUIRE(affine_cipher::encode("Testing,1 2 3, testing.", 3, 4) ==
            "jqgjc rw123 jqgjc rw");
}

TEST(AffineCipher, T007_encode_deep_thought) {
    REQUIRE(affine_cipher::encode("Truth is fiction.", 5, 17) ==
            "iynia fdqfb ifje");
}

TEST(AffineCipher, T008_encode_all_the_letters) {
    REQUIRE(affine_cipher::encode(
                "The quick brown fox jumps over the lazy dog.", 17, 33) ==
            "swxtj npvyk lruol iejdc blaxk swxmh qzglf");
}

TEST(AffineCipher, T009_encode_with_a_not_coprime_to_m) {
    REQUIRE_THROWS_AS(affine_cipher::encode("This is a test.", 6, 17),
                      std::invalid_argument);
}

TEST(AffineCipher, T010_decode_exercism) {
    REQUIRE(affine_cipher::decode("tytgn fjr", 3, 7) == "exercism");
}

TEST(AffineCipher, T011_decode_a_sentence) {
    REQUIRE(affine_cipher::decode("qdwju nqcro muwhn odqun oppmd aunwd o", 19,
                                  16) == "anobstacleisoftenasteppingstone");
}

TEST(AffineCipher, T012_decode_numbers) {
    REQUIRE(affine_cipher::decode("odpoz ub123 odpoz ub", 25, 7) ==
            "testing123testing");
}

TEST(AffineCipher, T013_decode_all_the_letters) {
    REQUIRE(affine_cipher::decode("swxtj npvyk lruol iejdc blaxk swxmh qzglf",
                                  17,
                                  33) == "thequickbrownfoxjumpsoverthelazydog");
}

TEST(AffineCipher, T014_decode_with_no_spaces_in_input) {
    REQUIRE(affine_cipher::decode("swxtjnpvyklruoliejdcblaxkswxmhqzglf", 17,
                                  33) == "thequickbrownfoxjumpsoverthelazydog");
}

TEST(AffineCipher, T015_decode_with_too_many_spaces) {
    REQUIRE(affine_cipher::decode("vszzm    cly   yd cg    qdp", 15, 16) ==
            "jollygreengiant");
}

TEST(AffineCipher, T016_decode_with_a_not_coprime_to_m) {
    REQUIRE_THROWS_AS(affine_cipher::decode("Test", 13, 5),
                      std::invalid_argument);
}

#endif

}  // namespace
