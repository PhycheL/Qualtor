// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "food_chain.h"

namespace {

using namespace std;

TEST(FoodChain, T001_fly) {
    string expected =
        "I know an old lady who swallowed a fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";

    REQUIRE(expected == food_chain::verse(1));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST(FoodChain, T002_spider) {
    string expected =
        "I know an old lady who swallowed a spider.\n"
        "It wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";

    REQUIRE(expected == food_chain::verse(2));
}

TEST(FoodChain, T003_bird) {
    string expected =
        "I know an old lady who swallowed a bird.\n"
        "How absurd to swallow a bird!\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled "
        "and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";

    REQUIRE(expected == food_chain::verse(3));
}

TEST(FoodChain, T004_cat) {
    string expected =
        "I know an old lady who swallowed a cat.\n"
        "Imagine that, to swallow a cat!\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled "
        "and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. "
        "Perhaps she'll die.\n";

    REQUIRE(expected == food_chain::verse(4));
}

TEST(FoodChain, T005_dog) {
    string expected =
        "I know an old lady who swallowed a dog.\n"
        "What a hog, to swallow a dog!\n"
        "She swallowed the dog to catch the cat.\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled "
        "and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. "
        "Perhaps she'll die.\n";

    REQUIRE(expected == food_chain::verse(5));
}

TEST(FoodChain, T006_goat) {
    string expected =
        "I know an old lady who swallowed a goat.\n"
        "Just opened her throat and swallowed a goat!\n"
        "She swallowed the goat to catch the dog.\n"
        "She swallowed the dog to catch the cat.\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled "
        "and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. "
        "Perhaps she'll die.\n";

    REQUIRE(expected == food_chain::verse(6));
}

TEST(FoodChain, T007_cow) {
    string expected =
        "I know an old lady who swallowed a cow.\n"
        "I don't know how she swallowed a cow!\n"
        "She swallowed the cow to catch the goat.\n"
        "She swallowed the goat to catch the dog.\n"
        "She swallowed the dog to catch the cat.\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled "
        "and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. "
        "Perhaps she'll die.\n";

    REQUIRE(expected == food_chain::verse(7));
}

TEST(FoodChain, T008_horse) {
    string expected =
        "I know an old lady who swallowed a horse.\n"
        "She's dead, of course!\n";

    REQUIRE(expected == food_chain::verse(8));
}

TEST(FoodChain, T009_multiple_verses) {
    string expected =
        "I know an old lady who swallowed a fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a spider.\n"
        "It wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n";

    REQUIRE(expected == food_chain::verses(1, 2));
}

TEST(FoodChain, T010_the_whole_song) {
    REQUIRE(food_chain::verses(1, 8) == food_chain::sing());
}
#endif

}  // namespace
