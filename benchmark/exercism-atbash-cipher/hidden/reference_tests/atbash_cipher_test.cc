// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "atbash_cipher.h"

namespace {

TEST(AtbashCipher, T001_encode_yes) { REQUIRE("bvh" == atbash_cipher::encode("yes")); }

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(AtbashCipher, T002_encode_no) { REQUIRE("ml" == atbash_cipher::encode("no")); }

TEST(AtbashCipher, T003_encode_OMG) { REQUIRE("lnt" == atbash_cipher::encode("OMG")); }

TEST(AtbashCipher, T004_encode_spaces) { REQUIRE("lnt" == atbash_cipher::encode("O M G")); }

TEST(AtbashCipher, T005_encode_mindblowingly) {
    REQUIRE("nrmwy oldrm tob" == atbash_cipher::encode("mindblowingly"));
}

TEST(AtbashCipher, T006_encode_numbers) {
    REQUIRE("gvhgr mt123 gvhgr mt" ==
            atbash_cipher::encode("Testing,1 2 3, testing."));
}

TEST(AtbashCipher, T007_encode_deep_thought) {
    REQUIRE("gifgs rhurx grlm" == atbash_cipher::encode("Truth is fiction."));
}

TEST(AtbashCipher, T008_encode_all_the_letters) {
    REQUIRE(
        "gsvjf rxpyi ldmul cqfnk hlevi gsvoz abwlt" ==
        atbash_cipher::encode("The quick brown fox jumps over the lazy dog."));
}

TEST(AtbashCipher, T009_decode_exercism) {
    REQUIRE("exercism" == atbash_cipher::decode("vcvix rhn"));
}

TEST(AtbashCipher, T010_decode_a_sentence) {
    REQUIRE("anobstacleisoftenasteppingstone" ==
            atbash_cipher::decode("zmlyh gzxov rhlug vmzhg vkkrm thglm v"));
}

TEST(AtbashCipher, T011_decode_numbers) {
    REQUIRE("testing123testing" ==
            atbash_cipher::decode("gvhgr mt123 gvhgr mt"));
}

TEST(AtbashCipher, T012_decode_all_the_letters) {
    REQUIRE("thequickbrownfoxjumpsoverthelazydog" ==
            atbash_cipher::decode("gsvjf rxpyi ldmul cqfnk hlevi gsvoz abwlt"));
}
#endif

}  // namespace
