// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "hamming.h"

#include <stdexcept>

namespace {

TEST(Hamming, T001_single_letter_identical_strands) {
    REQUIRE(0 == hamming::compute("A", "A"));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Hamming, T002_empty_strands) {
    REQUIRE(0 == hamming::compute("", ""));
}

TEST(Hamming, T003_single_letter_different_strands) {
    REQUIRE(1 == hamming::compute("G", "T"));
}

TEST(Hamming, T004_long_identical_strands) {
    REQUIRE(0 == hamming::compute("GGACTGAAATCTG", "GGACTGAAATCTG"));
}

TEST(Hamming, T005_long_different_strands) {
    REQUIRE(9 == hamming::compute("GGACGGATTCTG", "AGGACGGATTCT"));
}

TEST(Hamming, T006_disallow_first_strand_longer) {
    REQUIRE_THROWS_AS(hamming::compute("AATG", "AAA"), std::domain_error);
}

TEST(Hamming, T007_disallow_second_strand_longer) {
    REQUIRE_THROWS_AS(hamming::compute("ATA", "AGTG"), std::domain_error);
}

TEST(Hamming, T008_disallow_empty_first_strand) {
    REQUIRE_THROWS_AS(hamming::compute("", "G"), std::domain_error);
}

TEST(Hamming, T009_disallow_empty_second_strand) {
    REQUIRE_THROWS_AS(hamming::compute("G", ""), std::domain_error);
}
#endif

}  // namespace
