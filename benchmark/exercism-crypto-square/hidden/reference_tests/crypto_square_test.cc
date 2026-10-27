// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "crypto_square.h"

namespace {

TEST(CryptoSquare, T001_empty_plaintext_results_in_an_empty_ciphertext) {
    REQUIRE("" == crypto_square::cipher("").normalized_cipher_text());
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(CryptoSquare, T002_normalization_results_in_empty_plaintext) {
    REQUIRE("" ==
            crypto_square::cipher("... --- ...").normalized_cipher_text());
}

TEST(CryptoSquare, T003_Lowercase) {
    REQUIRE("a" == crypto_square::cipher("A").normalized_cipher_text());
}

TEST(CryptoSquare, T004_Remove_spaces) {
    REQUIRE("b" == crypto_square::cipher("  b ").normalized_cipher_text());
}

TEST(CryptoSquare, T005_Remove_punctuation) {
    REQUIRE("1" == crypto_square::cipher("@1,%!").normalized_cipher_text());
}

TEST(CryptoSquare, T006_9_character_plaintext_results_in_3_chunks_of_3_characters) {
    REQUIRE("tsf hiu isn" ==
            crypto_square::cipher("This is fun!").normalized_cipher_text());
}

TEST(CryptoSquare, T007_8_character_plaintext_results_in_3_chunks_the_last_one_with) {
    REQUIRE("clu hlt io " ==
            crypto_square::cipher("Chill out.").normalized_cipher_text());
}

TEST(CryptoSquare, T008_54_character_plaintext_results_in_8_chunks_the_last_two_with) {
    REQUIRE("imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn  sseoau " ==
            crypto_square::cipher("If man was meant to stay on the ground, god "
                                  "would have given us roots.")
                .normalized_cipher_text());
}
#endif

}  // namespace
