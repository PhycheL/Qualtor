// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_15.h"

#include <gtest/gtest.h>

#include <cmath>
#include <map>
#include <string>
#include <vector>

namespace {

template <class T>
void ExpectNearScalar(T actual, T expected, double tolerance) {
    EXPECT_NEAR(actual, expected, tolerance * (1 + std::fabs(static_cast<double>(expected))));
}

template <class T>
void ExpectNearVec(const std::vector<T>& actual, const std::vector<T>& expected, double tolerance) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) ExpectNearScalar(actual[i], expected[i], tolerance);
}

}  // namespace

TEST(Characterization, odd_count_01) {
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("137"), std::string("Z2P2o7"), std::string("0C3k"), std::string(""), std::string("NwNH8Cykmc4"), std::string("3")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 1n the str1ng 1 of the 1nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("271"), std::string("314")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("1w111111")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 7n the str7ng 7 of the 7nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("thv numberF of odd elements7 2n the str2ng 2 of the 2nput."), std::string("937"), std::string("H.XyfWd"), std::string("the number of odd elements 3n the str3ng 3 of the3nput.")})), (std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("bqQVeaZMKRU"), std::string("11111111")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{})), (std::vector<std::string >{}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("1234567")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("271"), std::string("137"), std::string("314")})), (std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 3n the str3ng 3 of the 3nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput."), std::string("271")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 2n the str2ng 2 of the 2nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 2n the str2ng 2 of the 2nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")})), (std::vector<std::string >{std::string("the number of odd elements 0n the str0ng 0 of the 0nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
    EXPECT_EQ((odd_count(std::vector<std::string >{std::string("the number of odd elements 1n the str1ng 1 of the 1nput."), std::string("the number of odd elements 8n the str8ng 8 of the 8nput.")})), (std::vector<std::string >{std::string("the number of odd elements 4n the str4ng 4 of the 4nput."), std::string("the number of odd elements 0n the str0ng 0 of the 0nput.")}));
}

TEST(Characterization, minSubArraySum_01) {
    EXPECT_EQ((minSubArraySum(std::vector<long long >{1LL, -1LL})), (-1LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-8LL, 0LL, 1LL, -272LL})), (-279LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{100LL, -1LL, -2LL, -3LL, 10LL, -5LL})), (-6LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-9999999999999999LL, 1LL})), (-9999999999999999LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-10LL})), (-10LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{275LL})), (275LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-9999999999999999LL, -10LL, -8LL, -4LL, 28LL})), (-10000000000000021LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{100LL, 28LL, 11LL, -5LL, -3LL})), (-8LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{212LL, 28LL})), (28LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{-1LL, 28LL})), (-1LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{8LL})), (8LL));
    EXPECT_EQ((minSubArraySum(std::vector<long long >{2LL, 3LL, 4LL, 1LL, 2LL, 4LL})), (1LL));
}

TEST(Characterization, max_fill_01) {
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 0, 0, 1}}, -7)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{}}, 24)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{1}, std::vector<int >{1}, std::vector<int >{1}, std::vector<int >{1}}, -2)), (4));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{3, 5, 24}, std::vector<int >{9, 9, -10}, std::vector<int >{486}}, 10)), (54));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, 9)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 1}, std::vector<int >{1}}, 10)), (2));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, 1)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{0, 0, 1}, std::vector<int >{}, std::vector<int >{}}, 179)), (1));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{std::vector<int >{13}, std::vector<int >{23}, std::vector<int >{-3}, std::vector<int >{5}}, 22)), (4));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, 2)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, -660)), (0));
    EXPECT_EQ((max_fill(std::vector<std::vector<int > >{}, 6)), (0));
}

TEST(Characterization, sort_array_01) {
    EXPECT_EQ((sort_array(std::vector<int >{-6, -5, -4, -3, -2})), (std::vector<int >{-4, -2, -6, -5, -3}));
    EXPECT_EQ((sort_array(std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 5, 77, 4, 5, 3, 5, 15, 2, 3, 4})), (std::vector<int >{2, 2, 4, 4, 3, 3, 5, 5, 5, 15, 77}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 12, 1000})), (std::vector<int >{2, 12, 1000}));
    EXPECT_EQ((sort_array(std::vector<int >{-2, -3, -4, -5, -6})), (std::vector<int >{-4, -2, -6, -5, -3}));
    EXPECT_EQ((sort_array(std::vector<int >{-6, -5, -4, -3, -2, -221})), (std::vector<int >{-4, -2, -6, -5, -3, -221}));
    EXPECT_EQ((sort_array(std::vector<int >{26, -5, -4, -3, -2})), (std::vector<int >{-4, -2, -5, -3, 26}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 5, 77, 4, 5, 3, 5, 7, 2, 3, 4})), (std::vector<int >{2, 2, 4, 4, 3, 3, 5, 5, 5, 7, 77}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 2, 4, 4, 3, 3, 5, 5, 5, 7, 77})), (std::vector<int >{2, 2, 4, 4, 3, 3, 5, 5, 5, 7, 77}));
    EXPECT_EQ((sort_array(std::vector<int >{76, 28, 5, -921, -4})), (std::vector<int >{-4, 5, 28, 76, -921}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 5, 2, 3, 4})), (std::vector<int >{1, 2, 4, 3, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 0, 2, 3, 4})), (std::vector<int >{0, 1, 2, 4, 3}));
}

TEST(Characterization, select_words_01) {
    EXPECT_EQ((select_words(std::string("wylhXA Net"), -3)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("UPCm"), -121)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("llamb"), 12345)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Ba b c d e f"), 0)), (std::vector<std::string >{std::string("e")}));
    EXPECT_EQ((select_words(std::string(""), 20)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("c"), 2)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("a bx c  e f"), 0)), (std::vector<std::string >{std::string("a"), std::string(""), std::string("e")}));
    EXPECT_EQ((select_words(std::string("amb"), 1)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Mary"), 2)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string(" "), -1)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Uncle sam"), 30)), (std::vector<std::string >{}));
    EXPECT_EQ((select_words(std::string("Uncle sam"), 710)), (std::vector<std::string >{}));
}

TEST(Characterization, get_closest_vowel_01) {
    EXPECT_EQ((get_closest_vowel(std::string("FUzL"))), (std::string("U")));
    EXPECT_EQ((get_closest_vowel(std::string("Pp6OGv"))), (std::string("O")));
    EXPECT_EQ((get_closest_vowel(std::string("an"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("U"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("u"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("abu"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("eAsy"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("nEimwe"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("ab"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("baU"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("ia"))), (std::string("")));
    EXPECT_EQ((get_closest_vowel(std::string("FULL"))), (std::string("U")));
}

TEST(Characterization, match_parens_01) {
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()"), std::string("Ry50nqxN"), std::string("1y85r9CqgeR")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("Yes"), std::string("(")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("("), std::string("Q3F8(IWN1fdu")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("((())"), std::string("(()())(("), std::string("nXYJT("), std::string("72j1YJDOy"), std::string(""), std::string("Yes")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")())"), std::string("(()())((")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()()("), std::string("((())"), std::string("0(o")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()("), std::string("()))()"), std::string("())")})), (std::string("Yes")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string(")(()"), std::string(")("), std::string(")Yes")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("fU"), std::string("Cd(QIOb")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()(())"), std::string("())())"), std::string("(l()")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("(()(())"), std::string("())())")})), (std::string("No")));
    EXPECT_EQ((match_parens(std::vector<std::string >{std::string("("), std::string(")")})), (std::string("Yes")));
}

TEST(Characterization, maximum_01) {
    EXPECT_EQ((maximum(std::vector<int >{-999, -355, -1, 999, -1000}, 0)), (std::vector<int >{}));
    EXPECT_EQ((maximum(std::vector<int >{-771, 1, 5, 27, 20, 243, 2, -6}, 0)), (std::vector<int >{}));
    EXPECT_EQ((maximum(std::vector<int >{1, -23, 4}, 2)), (std::vector<int >{1, 4}));
    EXPECT_EQ((maximum(std::vector<int >{1, 0, 5, -7}, 1)), (std::vector<int >{5}));
    EXPECT_EQ((maximum(std::vector<int >{-123, 20, 0, 1, 2, -3}, 6)), (std::vector<int >{-123, -3, 0, 1, 2, 20}));
    EXPECT_EQ((maximum(std::vector<int >{1, 1000}, 1)), (std::vector<int >{1000}));
    EXPECT_EQ((maximum(std::vector<int >{-123, 20, 0, -3, 2, 1}, 0)), (std::vector<int >{}));
    EXPECT_EQ((maximum(std::vector<int >{-1, 0, 2, 5, 3, -10, 10}, 1)), (std::vector<int >{10}));
    EXPECT_EQ((maximum(std::vector<int >{1, 0, 5, -7}, 2)), (std::vector<int >{1, 5}));
    EXPECT_EQ((maximum(std::vector<int >{465, 13, 19, 7, -1, 1000}, 5)), (std::vector<int >{7, 13, 19, 465, 1000}));
}
