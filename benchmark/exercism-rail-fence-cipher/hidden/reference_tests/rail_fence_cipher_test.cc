// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "rail_fence_cipher.h"

namespace {

TEST(RailFenceCipher, T001_encode_with_two_rails) {
    REQUIRE(rail_fence_cipher::encode("XOXOXOXOXOXOXOXOXO", 2) ==
            "XXXXXXXXXOOOOOOOOO");
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(RailFenceCipher, T002_encode_with_three_rails) {
    REQUIRE(rail_fence_cipher::encode("WEAREDISCOVEREDFLEEATONCE", 3) ==
            "WECRLTEERDSOEEFEAOCAIVDEN");
}

TEST(RailFenceCipher, T003_encode_with_ending_in_the_middle) {
    REQUIRE(rail_fence_cipher::encode("EXERCISES", 4) == "ESXIEECSR");
}

TEST(RailFenceCipher, T004_decode_with_three_rails) {
    REQUIRE(rail_fence_cipher::decode("TEITELHDVLSNHDTISEIIEA", 3) ==
            "THEDEVILISINTHEDETAILS");
}

TEST(RailFenceCipher, T005_decode_with_five_rails) {
    REQUIRE(rail_fence_cipher::decode("EIEXMSMESAORIWSCE", 5) ==
            "EXERCISMISAWESOME");
}

TEST(RailFenceCipher, T006_decode_with_six_rails) {
    REQUIRE(rail_fence_cipher::decode(
                "133714114238148966225439541018335470986172518171757571896261",
                6) ==
            "112358132134558914423337761098715972584418167651094617711286");
}

#endif

}  // namespace
