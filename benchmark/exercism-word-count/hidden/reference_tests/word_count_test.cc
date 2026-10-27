// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"
#include "word_count.h"

namespace {

/*
For each word in the input, count the number of times it appears in the
entire sentence.
*/

TEST(WordCount, T001_count_one_word) {
    const std::map<std::string, int> expected{{"word", 1}};
    REQUIRE(expected == word_count::words("word"));
}

#if defined(EXERCISM_RUN_ALL_TESTS)

TEST(WordCount, T002_count_one_of_each_word) {
    const std::map<std::string, int> expected{
        {"one", 1}, {"of", 1}, {"each", 1}};
    REQUIRE(expected == word_count::words("one of each"));
}

TEST(WordCount, T003_multiple_occurrences_of_a_word) {
    const std::map<std::string, int> expected{
        {"one", 1}, {"fish", 4}, {"two", 1}, {"red", 1}, {"blue", 1}};
    REQUIRE(expected ==
            word_count::words("one fish two fish red fish blue fish"));
}

TEST(WordCount, T004_handles_cramped_lists) {
    const std::map<std::string, int> expected{
        {"one", 1}, {"two", 1}, {"three", 1}};
    REQUIRE(expected == word_count::words("one,two,three"));
}

TEST(WordCount, T005_handles_expanded_lists) {
    const std::map<std::string, int> expected{
        {"one", 1}, {"two", 1}, {"three", 1}};
    REQUIRE(expected == word_count::words("one,\ntwo,\nthree"));
}

TEST(WordCount, T006_ignore_punctuation) {
    const std::map<std::string, int> expected{
        {"car", 1}, {"carpet", 1}, {"as", 1}, {"java", 1}, {"javascript", 1}};
    REQUIRE(expected ==
            word_count::words("car: carpet as java: javascript!!&@$%^&"));
}

TEST(WordCount, T007_include_numbers) {
    const std::map<std::string, int> expected{
        {"testing", 2}, {"1", 1}, {"2", 1}};
    REQUIRE(expected == word_count::words("testing, 1, 2 testing"));
}

TEST(WordCount, T008_normalize_case) {
    const std::map<std::string, int> expected{{"go", 3}, {"stop", 2}};
    REQUIRE(expected == word_count::words("go Go GO Stop stop"));
}

TEST(WordCount, T009_with_apostrophes) {
    const std::map<std::string, int> expected{
        {"first", 1}, {"don't", 2},  {"laugh", 1},   {"then", 1},
        {"cry", 1},   {"you're", 1}, {"getting", 1}, {"it", 1}};
    REQUIRE(expected ==
            word_count::words(
                "'First: don't laugh. Then: don't cry. You're getting it.'"));
}

TEST(WordCount, T010_with_quotations) {
    const std::map<std::string, int> expected{{"joe", 1},   {"can't", 1},
                                              {"tell", 1},  {"between", 1},
                                              {"large", 2}, {"and", 1}};
    REQUIRE(expected ==
            word_count::words("Joe can't tell between 'large' and large."));
}

TEST(WordCount, T011_substrings_from_the_beginning) {
    const std::map<std::string, int> expected{
        {"joe", 1}, {"can't", 1}, {"tell", 1}, {"between", 1},
        {"app", 1}, {"apple", 1}, {"and", 1},  {"a", 1}};
    REQUIRE(expected ==
            word_count::words("Joe can't tell between app, apple and a."));
}

TEST(WordCount, T012_multiple_spaces_not_detected_as_a_word) {
    const std::map<std::string, int> expected{{"multiple", 1},
                                              {"whitespaces", 1}};
    REQUIRE(expected == word_count::words(" multiple   whitespaces"));
}

TEST(WordCount, T013_alternating_word_separators_not_detected_as_a_word) {
    const std::map<std::string, int> expected{
        {"one", 1}, {"two", 1}, {"three", 1}};
    REQUIRE(expected == word_count::words(",\n,one,\n ,two \n 'three'"));
}

TEST(WordCount, T014_quotation_for_word_with_apostrophe) {
    const std::map<std::string, int> expected{{"can", 1}, {"can't", 2}};
    REQUIRE(expected == word_count::words("can, can't, 'can't'"));
}

#endif

}  // namespace
