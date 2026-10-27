// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "bob.h"

namespace {

// Bob exercise test case data version 1.4.0

TEST(Bob, T001_stating_something) {
    REQUIRE("Whatever." == bob::hey("Tom-ay-to, tom-aaaah-to."));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Bob, T002_shouting) {
    REQUIRE("Whoa, chill out!" == bob::hey("WATCH OUT!"));
}

TEST(Bob, T003_shouting_gibberish) {
    REQUIRE("Whoa, chill out!" == bob::hey("FCECDFCAAB"));
}

TEST(Bob, T004_asking_a_question) {
    REQUIRE("Sure." ==
            bob::hey("Does this cryogenic chamber make me look fat?"));
}

TEST(Bob, T005_asking_a_numeric_question) {
    REQUIRE("Sure." == bob::hey("You are, what, like 15?"));
}

TEST(Bob, T006_asking_gibberish) {
    REQUIRE("Sure." == bob::hey("fffbbcbeab?"));
}

TEST(Bob, T007_talking_forcefully) {
    REQUIRE("Whatever." == bob::hey("Let's go make out behind the gym!"));
}

TEST(Bob, T008_using_acronyms_in_regular_speech) {
    REQUIRE("Whatever." ==
            bob::hey("It's OK if you don't want to go to the DMV."));
}

TEST(Bob, T009_forceful_questions) {
    REQUIRE("Calm down, I know what I'm doing!" ==
            bob::hey("WHAT THE HELL WERE YOU THINKING?"));
}

TEST(Bob, T010_shouting_numbers) {
    REQUIRE("Whoa, chill out!" == bob::hey("1, 2, 3 GO!"));
}

TEST(Bob, T011_no_letters) {
    REQUIRE("Whatever." == bob::hey("1, 2, 3"));
}

TEST(Bob, T012_question_with_no_letters) {
    REQUIRE("Sure." == bob::hey("4?"));
}

TEST(Bob, T013_shouting_with_special_characters) {
    REQUIRE("Whoa, chill out!" ==
            bob::hey("ZOMG THE %^*@#$(*^ ZOMBIES ARE COMING!!11!!1!"));
}

TEST(Bob, T014_shouting_with_no_exclamation_mark) {
    REQUIRE("Whoa, chill out!" == bob::hey("I HATE THE DMV"));
}

TEST(Bob, T015_statement_containing_question_mark) {
    REQUIRE("Whatever." == bob::hey("Ending with ? means a question."));
}

TEST(Bob, T016_non_letters_with_question) {
    REQUIRE("Sure." == bob::hey(":) ?"));
}

TEST(Bob, T017_prattling_on) {
    REQUIRE("Sure." == bob::hey("Wait! Hang on. Are you going to be OK?"));
}

TEST(Bob, T018_silence) {
    REQUIRE("Fine. Be that way!" == bob::hey(""));
}

TEST(Bob, T019_prolonged_silence) {
    REQUIRE("Fine. Be that way!" == bob::hey("          "));
}

TEST(Bob, T020_alternate_silence) {
    REQUIRE("Fine. Be that way!" == bob::hey("\t\t\t\t\t\t\t\t\t\t"));
}

TEST(Bob, T021_multiple_line_question) {
    REQUIRE("Sure." ==
            bob::hey("\nDoes this cryogenic chamber make\n me look fat?"));
}

TEST(Bob, T022_starting_with_whitespace) {
    REQUIRE("Whatever." == bob::hey("         hmmmmmmm..."));
}

TEST(Bob, T023_ending_with_whitespace) {
    REQUIRE("Sure." == bob::hey("Okay if like my  spacebar  quite a bit?   "));
}

TEST(Bob, T024_other_whitespace) {
    REQUIRE("Fine. Be that way!" == bob::hey("\n\r \t"));
}

TEST(Bob, T025_non_question_ending_with_whitespace) {
    REQUIRE("Whatever." ==
            bob::hey("This is a statement ending with whitespace      "));
}
#endif

}  // namespace
