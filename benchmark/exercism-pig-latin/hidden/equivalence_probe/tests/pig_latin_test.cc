// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "pig_latin.h"

namespace {

TEST(PigLatin, T001_word_beginning_with_a) {
    REQUIRE("appleay" == pig_latin::translate("apple"));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(PigLatin, T002_word_beginning_with_e) {
    REQUIRE("earay" == pig_latin::translate("ear"));
}

TEST(PigLatin, T003_word_beginning_with_i) {
    REQUIRE("iglooay" == pig_latin::translate("igloo"));
}

TEST(PigLatin, T004_word_beginning_with_o) {
    REQUIRE("objectay" == pig_latin::translate("object"));
}

TEST(PigLatin, T005_word_beginning_with_u) {
    REQUIRE("underay" == pig_latin::translate("under"));
}

TEST(PigLatin, T006_word_beginning_with_a_vowel_and_followed_by_a_qu) {
    REQUIRE("equalay" == pig_latin::translate("equal"));
}

TEST(PigLatin, T007_word_beginning_with_p) {
    REQUIRE("igpay" == pig_latin::translate("pig"));
}

TEST(PigLatin, T008_word_beginning_with_k) {
    REQUIRE("oalakay" == pig_latin::translate("koala"));
}

TEST(PigLatin, T009_word_beginning_with_x) {
    REQUIRE("enonxay" == pig_latin::translate("xenon"));
}

TEST(PigLatin, T010_word_beginning_with_q_without_a_following_u) {
    REQUIRE("atqay" == pig_latin::translate("qat"));
}

TEST(PigLatin, T011_word_beginning_with_ch) {
    REQUIRE("airchay" == pig_latin::translate("chair"));
}

TEST(PigLatin, T012_word_beginning_with_qu) {
    REQUIRE("eenquay" == pig_latin::translate("queen"));
}

TEST(PigLatin, T013_word_beginning_with_qu_and_a_preceding_consonant) {
    REQUIRE("aresquay" == pig_latin::translate("square"));
}

TEST(PigLatin, T014_word_beginning_with_th) {
    REQUIRE("erapythay" == pig_latin::translate("therapy"));
}

TEST(PigLatin, T015_word_beginning_with_thr) {
    REQUIRE("ushthray" == pig_latin::translate("thrush"));
}

TEST(PigLatin, T016_word_beginning_with_sch) {
    REQUIRE("oolschay" == pig_latin::translate("school"));
}

TEST(PigLatin, T017_word_beginning_with_yt) {
    REQUIRE("yttriaay" == pig_latin::translate("yttria"));
}

TEST(PigLatin, T018_word_beginning_with_xr) {
    REQUIRE("xrayay" == pig_latin::translate("xray"));
}

TEST(PigLatin, T019_y_is_treated_like_a_consonant_at_the_beginning_of_a_word) {
    REQUIRE("ellowyay" == pig_latin::translate("yellow"));
}

TEST(PigLatin, T020_y_is_treated_like_a_vowel_at_the_end_of_a_consonant_cluster) {
    REQUIRE("ythmrhay" == pig_latin::translate("rhythm"));
}
TEST(PigLatin, T021_first_letter_and_ay_are_moved_to_the_end_of_words_that_start) {
    REQUIRE("iquidlay" == pig_latin::translate("liquid"));
}

TEST(PigLatin, T022_y_as_second_letter_in_two_letter_word) {
    REQUIRE("ymay" == pig_latin::translate("my"));
}

TEST(PigLatin, T023_a_whole_phrase) {
    REQUIRE("ickquay astfay unray" == pig_latin::translate("quick fast run"));
}

#endif

}  // namespace
