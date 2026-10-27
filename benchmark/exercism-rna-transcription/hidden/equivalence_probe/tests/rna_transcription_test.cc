// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "rna_transcription.h"

namespace {

TEST(RnaTranscription, T001_transcribes_cytidine_to_guanosine) {
    REQUIRE('G' == rna_transcription::to_rna('C'));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(RnaTranscription, T002_transcribes_guanosine_to_cytidine) {
    REQUIRE('C' == rna_transcription::to_rna('G'));
}

TEST(RnaTranscription, T003_transcribes_adenosine_to_uracil) {
    REQUIRE('U' == rna_transcription::to_rna('A'));
}

TEST(RnaTranscription, T004_transcribes_thymidine_to_adenosine) {
    REQUIRE('A' == rna_transcription::to_rna('T'));
}

TEST(RnaTranscription, T005_transcribes_all_dna_nucleotides_to_their_rna_complements) {
    REQUIRE("UGCACCAGAAUU" == rna_transcription::to_rna("ACGTGGTCTTAA"));
}
#endif

}  // namespace
