// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "acronym.h"

namespace {

using namespace std;

TEST(Acronym, T001_basic) {
    const string actual = acronym::acronym("Portable Network Graphics");

    const string expected{"PNG"};

    REQUIRE(expected == actual);
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(Acronym, T002_lowercase_words) {
    const string actual = acronym::acronym("Ruby on Rails");

    const string expected{"ROR"};

    REQUIRE(expected == actual);
}

TEST(Acronym, T003_punctuation) {
    const string actual = acronym::acronym("First In, First Out");

    const string expected{"FIFO"};

    REQUIRE(expected == actual);
}

TEST(Acronym, T004_all_caps_word) {
    const string actual = acronym::acronym("GNU Image Manipulation Program");

    const string expected{"GIMP"};

    REQUIRE(expected == actual);
}

TEST(Acronym, T005_punctuation_without_whitespace) {
    const string actual =
        acronym::acronym("Complementary metal-oxide semiconductor");

    const string expected{"CMOS"};

    REQUIRE(expected == actual);
}

TEST(Acronym, T006_very_long_abbreviation) {
    const string actual = acronym::acronym(
        "Rolling On The Floor Laughing So Hard That My Dogs Came Over And "
        "Licked Me");

    const string expected{"ROTFLSHTMDCOALM"};

    REQUIRE(expected == actual);
}

TEST(Acronym, T007_consecutive_delimiters) {
    const string actual =
        acronym::acronym("Something - I made up from thin air");

    const string expected{"SIMUFTA"};

    REQUIRE(expected == actual);
}

TEST(Acronym, T008_apostrophes) {
    const string actual = acronym::acronym("Halley's Comet");

    const string expected{"HC"};

    REQUIRE(expected == actual);
}

TEST(Acronym, T009_underscore_emphasis) {
    const string actual = acronym::acronym("The Road _Not_ Taken");

    const string expected{"TRNT"};

    REQUIRE(expected == actual);
}
#endif

}  // namespace
