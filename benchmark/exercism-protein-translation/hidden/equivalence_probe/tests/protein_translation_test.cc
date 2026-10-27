// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include <string>
#include <vector>

#include "protein_translation.h"

namespace {

using namespace std;

// Secret-handshake exercise test case data version 1.2.1

TEST(ProteinTranslation, T001_Methionine_RNA_sequence) {
    REQUIRE(vector<string>{"Methionine"} ==
            protein_translation::proteins("AUG"));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(ProteinTranslation, T002_Phenylalanine_RNA_sequence_1) {
    REQUIRE(vector<string>{"Phenylalanine"} ==
            protein_translation::proteins("UUU"));
}

TEST(ProteinTranslation, T003_Phenylalanine_RNA_sequence_2) {
    REQUIRE(vector<string>{"Phenylalanine"} ==
            protein_translation::proteins("UUC"));
}

TEST(ProteinTranslation, T004_Leucine_RNA_sequence_1) {
    REQUIRE(vector<string>{"Leucine"} == protein_translation::proteins("UUA"));
}

TEST(ProteinTranslation, T005_Leucine_RNA_sequence_2) {
    REQUIRE(vector<string>{"Leucine"} == protein_translation::proteins("UUG"));
}

TEST(ProteinTranslation, T006_Serine_RNA_sequence_1) {
    REQUIRE(vector<string>{"Serine"} == protein_translation::proteins("UCU"));
}

TEST(ProteinTranslation, T007_Serine_RNA_sequence_2) {
    REQUIRE(vector<string>{"Serine"} == protein_translation::proteins("UCC"));
}

TEST(ProteinTranslation, T008_Serine_RNA_sequence_3) {
    REQUIRE(vector<string>{"Serine"} == protein_translation::proteins("UCA"));
}

TEST(ProteinTranslation, T009_Serine_RNA_sequence_4) {
    REQUIRE(vector<string>{"Serine"} == protein_translation::proteins("UCG"));
}

TEST(ProteinTranslation, T010_Tyrosine_RNA_sequence_1) {
    REQUIRE(vector<string>{"Tyrosine"} == protein_translation::proteins("UAU"));
}

TEST(ProteinTranslation, T011_Tyrosine_RNA_sequence_2) {
    REQUIRE(vector<string>{"Tyrosine"} == protein_translation::proteins("UAC"));
}

TEST(ProteinTranslation, T012_Cysteine_RNA_sequence_1) {
    REQUIRE(vector<string>{"Cysteine"} == protein_translation::proteins("UGU"));
}

TEST(ProteinTranslation, T013_Cysteine_RNA_sequence_2) {
    REQUIRE(vector<string>{"Cysteine"} == protein_translation::proteins("UGC"));
}

TEST(ProteinTranslation, T014_Tryptophan_RNA_sequence) {
    REQUIRE(vector<string>{"Tryptophan"} ==
            protein_translation::proteins("UGG"));
}

TEST(ProteinTranslation, T015_STOP_codon_RNA_sequence_1) {
    REQUIRE(vector<string>{} == protein_translation::proteins("UAA"));
}

TEST(ProteinTranslation, T016_STOP_codon_RNA_sequence_2) {
    REQUIRE(vector<string>{} == protein_translation::proteins("UAG"));
}

TEST(ProteinTranslation, T017_STOP_codon_RNA_sequence_3) {
    REQUIRE(vector<string>{} == protein_translation::proteins("UGA"));
}

TEST(ProteinTranslation, T018_Translate_RNA_strand_into_correct_protein_list) {
    REQUIRE(vector<string>{"Methionine", "Phenylalanine", "Tryptophan"} ==
            protein_translation::proteins("AUGUUUUGG"));
}

TEST(ProteinTranslation, T019_Sequence_of_two_protein_codons_translates_into_proteins) {
    REQUIRE(vector<string>{"Phenylalanine", "Phenylalanine"} ==
            protein_translation::proteins("UUUUUU"));
}

TEST(ProteinTranslation, T020_Sequence_of_two_different_protein_codons_translates_into_pro) {
    REQUIRE(vector<string>{"Leucine", "Leucine"} ==
            protein_translation::proteins("UUAUUG"));
}

TEST(ProteinTranslation, T021_Empty_RNA_sequence_results_in_no_proteins) {
    REQUIRE(vector<string>{} == protein_translation::proteins(""));
}

TEST(ProteinTranslation, T022_Translation_stops_if_STOP_codon_at_beginning_of_sequence) {
    REQUIRE(vector<string>{} == protein_translation::proteins("UAGUGG"));
}

TEST(ProteinTranslation, T023_Translation_stops_if_STOP_codon_at_end_of_two_codon_sequence) {
    REQUIRE(vector<string>{"Tryptophan"} ==
            protein_translation::proteins("UGGUAG"));
}

TEST(ProteinTranslation, T024_Translation_stops_if_STOP_codon_at_end_of_three_codon_sequen) {
    REQUIRE(vector<string>{"Methionine", "Phenylalanine"} ==
            protein_translation::proteins("AUGUUUUAA"));
}

TEST(ProteinTranslation, T025_Translation_stops_if_STOP_codon_in_middle_of_three_codon_seq) {
    REQUIRE(vector<string>{"Tryptophan"} ==
            protein_translation::proteins("UGGUAGUGG"));
}

TEST(ProteinTranslation, T026_Translation_stops_if_STOP_codon_in_middle_of_six_codon_seque) {
    REQUIRE(vector<string>{"Tryptophan", "Cysteine", "Tyrosine"} ==
            protein_translation::proteins("UGGUGUUAUUAAUGGUUU"));
}

TEST(ProteinTranslation, T027_Sequence_of_two_non_STOP_codons_does_not_translate_to_a_STOP) {
    REQUIRE(vector<string>{"Methionine", "Methionine"} ==
            protein_translation::proteins("AUGAUG"));
}

#endif  // !EXERCISM_RUN_ALL_TESTS

}  // namespace
