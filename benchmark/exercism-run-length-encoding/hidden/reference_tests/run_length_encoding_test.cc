// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "run_length_encoding.h"

namespace {

TEST(RunLengthEncoding, T001_encode_empty_string) {
    REQUIRE(run_length_encoding::encode("") == "");
}
#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(RunLengthEncoding, T002_encode_single_characters_only_are_encoded_without_count) {
    REQUIRE(run_length_encoding::encode("XYZ") == "XYZ");
}

TEST(RunLengthEncoding, T003_encode_string_with_no_single_characters) {
    REQUIRE(run_length_encoding::encode("AABBBCCCC") == "2A3B4C");
}

TEST(RunLengthEncoding, T004_encode_single_characters_mixed_with_repeated_characters) {
    REQUIRE(run_length_encoding::encode(
                "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB") ==
            "12WB12W3B24WB");
}

TEST(RunLengthEncoding, T005_encode_multiple_whitespace_mixed_in_string) {
    REQUIRE(run_length_encoding::encode("  hsqq qww  ") == "2 hs2q q2w2 ");
}

TEST(RunLengthEncoding, T006_encode_lowercase_characters) {
    REQUIRE(run_length_encoding::encode("aabbbcccc") == "2a3b4c");
}

TEST(RunLengthEncoding, T007_decode_run_length_decode_a_string) {
    REQUIRE(run_length_encoding::decode("") == "");
}

TEST(RunLengthEncoding, T008_decode_single_characters_only) {
    REQUIRE(run_length_encoding::decode("XYZ") == "XYZ");
}

TEST(RunLengthEncoding, T009_decode_string_with_no_single_characters) {
    REQUIRE(run_length_encoding::decode("2A3B4C") == "AABBBCCCC");
}

TEST(RunLengthEncoding, T010_decode_single_characters_with_repeated_characters) {
    REQUIRE(run_length_encoding::decode("12WB12W3B24WB") ==
            "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB");
}

TEST(RunLengthEncoding, T011_decode_multiple_whitespace_mixed_in_string) {
    REQUIRE(run_length_encoding::decode("2 hs2q q2w2 ") == "  hsqq qww  ");
}

TEST(RunLengthEncoding, T012_decode_lowercase_string) {
    REQUIRE(run_length_encoding::decode("2a3b4c") == "aabbbcccc");
}

TEST(RunLengthEncoding, T013_encode_and_then_decode) {
    REQUIRE(run_length_encoding::decode(
                run_length_encoding::encode("zzz ZZ  zZ")) == "zzz ZZ  zZ");
}
#endif

}  // namespace
