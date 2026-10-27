// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "allergies.h"

namespace {

TEST(Allergies, T001_testing_for_eggs_allergy_not_allergic_to_anything) {
    REQUIRE(false == allergies::allergy_test(0).is_allergic_to("eggs"));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(Allergies, T002_testing_for_eggs_allergy_allergic_only_to_eggs) {
    REQUIRE(true == allergies::allergy_test(1).is_allergic_to("eggs"));
}

TEST(Allergies, T003_testing_for_eggs_allergy_allergic_to_eggs_and_something_else) {
    REQUIRE(true == allergies::allergy_test(3).is_allergic_to("eggs"));
}

TEST(Allergies, T004_testing_for_eggs_allergy_allergic_to_something_but_not_eggs) {
    REQUIRE(false == allergies::allergy_test(2).is_allergic_to("eggs"));
}

TEST(Allergies, T005_testing_for_eggs_allergy_allergic_to_everything) {
    REQUIRE(true == allergies::allergy_test(255).is_allergic_to("eggs"));
}

TEST(Allergies, T006_testing_for_peanuts_allergy_not_allergic_to_anything) {
    REQUIRE(false == allergies::allergy_test(0).is_allergic_to("peanuts"));
}

TEST(Allergies, T007_testing_for_peanuts_allergy_allergic_only_to_peanuts) {
    REQUIRE(true == allergies::allergy_test(2).is_allergic_to("peanuts"));
}

TEST(Allergies, T008_testing_for_peanuts_allergy_allergic_to_peanuts_and_somethin) {
    REQUIRE(true == allergies::allergy_test(7).is_allergic_to("peanuts"));
}

TEST(Allergies, T009_testing_for_peanuts_allergy_allergic_to_something_but_not_pe) {
    REQUIRE(false == allergies::allergy_test(5).is_allergic_to("peanuts"));
}

TEST(Allergies, T010_testing_for_peanuts_allergy_allergic_to_everything) {
    REQUIRE(true == allergies::allergy_test(255).is_allergic_to("peanuts"));
}

TEST(Allergies, T011_testing_for_shellfish_allergy_not_allergic_to_anything) {
    REQUIRE(false == allergies::allergy_test(0).is_allergic_to("shellfish"));
}

TEST(Allergies, T012_testing_for_shellfish_allergy_allergic_only_to_shellfish) {
    REQUIRE(true == allergies::allergy_test(4).is_allergic_to("shellfish"));
}

TEST(Allergies, T013_testing_for_shellfish_allergy_allergic_to_shellfish_and_some) {
    REQUIRE(true == allergies::allergy_test(14).is_allergic_to("shellfish"));
}

TEST(Allergies, T014_testing_for_shellfish_allergy_allergic_to_something_but_not) {
    REQUIRE(false == allergies::allergy_test(10).is_allergic_to("shellfish"));
}

TEST(Allergies, T015_testing_for_shellfish_allergy_allergic_to_everything) {
    REQUIRE(true == allergies::allergy_test(255).is_allergic_to("shellfish"));
}

TEST(Allergies, T016_testing_for_strawberries_allergy_not_allergic_to_anything) {
    REQUIRE(false == allergies::allergy_test(0).is_allergic_to("strawberries"));
}

TEST(Allergies, T017_testing_for_strawberries_allergy_allergic_only_to_strawberri) {
    REQUIRE(true == allergies::allergy_test(8).is_allergic_to("strawberries"));
}

TEST(Allergies, T018_testing_for_strawberries_allergy_allergic_to_strawberries_an) {
    REQUIRE(true == allergies::allergy_test(28).is_allergic_to("strawberries"));
}

TEST(Allergies, T019_testing_for_strawberries_allergy_allergic_to_something_but_n) {
    REQUIRE(false ==
            allergies::allergy_test(20).is_allergic_to("strawberries"));
}

TEST(Allergies, T020_testing_for_strawberries_allergy_allergic_to_everything) {
    REQUIRE(true ==
            allergies::allergy_test(255).is_allergic_to("strawberries"));
}

TEST(Allergies, T021_testing_for_tomatoes_allergy_not_allergic_to_anything) {
    REQUIRE(false == allergies::allergy_test(0).is_allergic_to("tomatoes"));
}

TEST(Allergies, T022_testing_for_tomatoes_allergy_allergic_only_to_tomatoes) {
    REQUIRE(true == allergies::allergy_test(16).is_allergic_to("tomatoes"));
}

TEST(Allergies, T023_testing_for_tomatoes_allergy_allergic_to_tomatoes_and_someth) {
    REQUIRE(true == allergies::allergy_test(56).is_allergic_to("tomatoes"));
}

TEST(Allergies, T024_testing_for_tomatoes_allergy_allergic_to_something_but_not_t) {
    REQUIRE(false == allergies::allergy_test(40).is_allergic_to("tomatoes"));
}

TEST(Allergies, T025_testing_for_tomatoes_allergy_allergic_to_everything) {
    REQUIRE(true == allergies::allergy_test(255).is_allergic_to("tomatoes"));
}

TEST(Allergies, T026_testing_for_chocolate_allergy_not_allergic_to_anything) {
    REQUIRE(false == allergies::allergy_test(0).is_allergic_to("chocolate"));
}

TEST(Allergies, T027_testing_for_chocolate_allergy_allergic_only_to_chocolate) {
    REQUIRE(true == allergies::allergy_test(32).is_allergic_to("chocolate"));
}

TEST(Allergies, T028_testing_for_chocolate_allergy_allergic_to_chocolate_and_some) {
    REQUIRE(true == allergies::allergy_test(112).is_allergic_to("chocolate"));
}

TEST(Allergies, T029_testing_for_chocolate_allergy_allergic_to_something_but_not) {
    REQUIRE(false == allergies::allergy_test(80).is_allergic_to("chocolate"));
}

TEST(Allergies, T030_testing_for_chocolate_allergy_allergic_to_everything) {
    REQUIRE(true == allergies::allergy_test(255).is_allergic_to("chocolate"));
}

TEST(Allergies, T031_testing_for_pollen_allergy_not_allergic_to_anything) {
    REQUIRE(false == allergies::allergy_test(0).is_allergic_to("pollen"));
}

TEST(Allergies, T032_testing_for_pollen_allergy_allergic_only_to_pollen) {
    REQUIRE(true == allergies::allergy_test(64).is_allergic_to("pollen"));
}

TEST(Allergies, T033_testing_for_pollen_allergy_allergic_to_pollen_and_something) {
    REQUIRE(true == allergies::allergy_test(224).is_allergic_to("pollen"));
}

TEST(Allergies, T034_testing_for_pollen_allergy_allergic_to_something_but_not_pol) {
    REQUIRE(false == allergies::allergy_test(160).is_allergic_to("pollen"));
}

TEST(Allergies, T035_testing_for_pollen_allergy_allergic_to_everything) {
    REQUIRE(true == allergies::allergy_test(255).is_allergic_to("pollen"));
}

TEST(Allergies, T036_testing_for_cats_allergy_not_allergic_to_anything) {
    REQUIRE(false == allergies::allergy_test(0).is_allergic_to("cats"));
}

TEST(Allergies, T037_testing_for_cats_allergy_allergic_only_to_cats) {
    REQUIRE(true == allergies::allergy_test(128).is_allergic_to("cats"));
}

TEST(Allergies, T038_testing_for_cats_allergy_allergic_to_cats_and_something_else) {
    REQUIRE(true == allergies::allergy_test(192).is_allergic_to("cats"));
}

TEST(Allergies, T039_testing_for_cats_allergy_allergic_to_something_but_not_cats) {
    REQUIRE(false == allergies::allergy_test(64).is_allergic_to("cats"));
}

TEST(Allergies, T040_testing_for_cats_allergy_allergic_to_everything) {
    REQUIRE(true == allergies::allergy_test(255).is_allergic_to("cats"));
}

TEST(Allergies, T041_list_when_no_allergies) {
    std::unordered_set<std::string> expected = {};
    REQUIRE(expected == allergies::allergy_test(0).get_allergies());
}

TEST(Allergies, T042_list_when_just_eggs) {
    std::unordered_set<std::string> expected = {"eggs"};
    REQUIRE(expected == allergies::allergy_test(1).get_allergies());
}

TEST(Allergies, T043_list_when_just_peanuts) {
    std::unordered_set<std::string> expected = {"peanuts"};
    REQUIRE(expected == allergies::allergy_test(2).get_allergies());
}

TEST(Allergies, T044_list_when_just_strawberries) {
    std::unordered_set<std::string> expected = {"strawberries"};
    REQUIRE(expected == allergies::allergy_test(8).get_allergies());
}

TEST(Allergies, T045_list_when_eggs_and_peanuts) {
    std::unordered_set<std::string> expected = {"eggs", "peanuts"};
    REQUIRE(expected == allergies::allergy_test(3).get_allergies());
}

TEST(Allergies, T046_list_when_more_than_eggs_but_not_peanuts) {
    std::unordered_set<std::string> expected = {"eggs", "shellfish"};
    REQUIRE(expected == allergies::allergy_test(5).get_allergies());
}

TEST(Allergies, T047_list_when_lots_of_stuff) {
    std::unordered_set<std::string> expected = {"strawberries", "tomatoes",
                                                "chocolate", "pollen", "cats"};
    REQUIRE(expected == allergies::allergy_test(248).get_allergies());
}

TEST(Allergies, T048_list_when_everything) {
    std::unordered_set<std::string> expected = {
        "eggs",     "peanuts",   "shellfish", "strawberries",
        "tomatoes", "chocolate", "pollen",    "cats"};
    REQUIRE(expected == allergies::allergy_test(255).get_allergies());
}

TEST(Allergies, T049_list_when_no_allergen_score_parts) {
    std::unordered_set<std::string> expected = {
        "eggs",      "shellfish", "strawberries", "tomatoes",
        "chocolate", "pollen",    "cats"};
    REQUIRE(expected == allergies::allergy_test(509).get_allergies());
}

TEST(Allergies, T050_list_when_no_allergen_score_parts_without_highest_valid_scor) {
    std::unordered_set<std::string> expected = {"eggs"};
    REQUIRE(expected == allergies::allergy_test(257).get_allergies());
}

#endif

}  // namespace
