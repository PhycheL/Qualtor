// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_11.h"

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

TEST(Characterization, numerical_letter_grade_01) {
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.5f})), (std::vector<std::string >{std::string("D-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{2.70000005f, -18.5f, 7.4000001f, 7.5999999f, 3.70000005f, 0.699999988f, -1.60000002f})), (std::vector<std::string >{std::string("B-"), std::string("E"), std::string("A+"), std::string("A+"), std::string("A-"), std::string("D-"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.0f, 0.300000012f, 1.5f, 2.79999995f, 3.29999995f, -6.01999998f})), (std::vector<std::string >{std::string("D"), std::string("D-"), std::string("C-"), std::string("B"), std::string("B+"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.0f, 0.699999988f})), (std::vector<std::string >{std::string("E"), std::string("D-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{-10.8000002f, 15.3999996f, 4.0f, 2.0f, 1.29999995f})), (std::vector<std::string >{std::string("E"), std::string("A+"), std::string("A+"), std::string("C"), std::string("D+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.70000005f, 3.0f, 1.70000005f, 2.0f, 3.5f})), (std::vector<std::string >{std::string("C-"), std::string("B"), std::string("C-"), std::string("C"), std::string("A-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{4.0f, 3.0f, 1.70000005f, -17.3999996f, 3.5f})), (std::vector<std::string >{std::string("A+"), std::string("B"), std::string("C-"), std::string("E"), std::string("A-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{-2.5f, 4.5999999f, 1.20000005f, 2.0f})), (std::vector<std::string >{std::string("E"), std::string("A+"), std::string("D+"), std::string("C")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{3.0f, 2.0f, -1.15999997f, 1.70000005f, 3.0f, 2.5f, 1.0f, 0.899999976f})), (std::vector<std::string >{std::string("B"), std::string("C"), std::string("E"), std::string("C-"), std::string("B"), std::string("B-"), std::string("D"), std::string("D")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{})), (std::vector<std::string >{}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.20000005f, -11.1999998f})), (std::vector<std::string >{std::string("D+"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.0f, 2.79999995f, 1.5f, 0.300000012f, 3.29999995f})), (std::vector<std::string >{std::string("D"), std::string("B"), std::string("C-"), std::string("D-"), std::string("B+")}));
}

TEST(Characterization, prime_length_01) {
    EXPECT_EQ((prime_length(std::string("l"))), (false));
    EXPECT_EQ((prime_length(std::string("dlwsxJKiso"))), (false));
    EXPECT_EQ((prime_length(std::string("go"))), (true));
    EXPECT_EQ((prime_length(std::string("HI"))), (true));
    EXPECT_EQ((prime_length(std::string("Jf"))), (true));
    EXPECT_EQ((prime_length(std::string("Rsgog"))), (true));
    EXPECT_EQ((prime_length(std::string("LqlI m5qtVxo"))), (false));
    EXPECT_EQ((prime_length(std::string("orange"))), (false));
    EXPECT_EQ((prime_length(std::string("ETy4G"))), (true));
    EXPECT_EQ((prime_length(std::string("c7M36"))), (true));
    EXPECT_EQ((prime_length(std::string("mufPKZ"))), (false));
    EXPECT_EQ((prime_length(std::string("X"))), (false));
}

TEST(Characterization, starts_one_ends_01) {
    EXPECT_EQ((starts_one_ends(1)), (1));
    EXPECT_EQ((starts_one_ends(7)), (1800000));
    EXPECT_EQ((starts_one_ends(6)), (180000));
    EXPECT_EQ((starts_one_ends(-3)), (0));
    EXPECT_EQ((starts_one_ends(0)), (0));
    EXPECT_EQ((starts_one_ends(4)), (1800));
    EXPECT_EQ((starts_one_ends(2)), (18));
    EXPECT_EQ((starts_one_ends(-5)), (0));
    EXPECT_EQ((starts_one_ends(-10)), (0));
    EXPECT_EQ((starts_one_ends(-603)), (0));
    EXPECT_EQ((starts_one_ends(8)), (18000000));
    EXPECT_EQ((starts_one_ends(10)), (1800000000));
}

TEST(Characterization, solve_01) {
    EXPECT_EQ((solve(149)), (std::string("1110")));
    EXPECT_EQ((solve(21)), (std::string("11")));
    EXPECT_EQ((solve(-4)), (std::string("1")));
    EXPECT_EQ((solve(147)), (std::string("1100")));
    EXPECT_EQ((solve(10010)), (std::string("10")));
    EXPECT_EQ((solve(12)), (std::string("11")));
    EXPECT_EQ((solve(1000)), (std::string("1")));
    EXPECT_EQ((solve(20)), (std::string("10")));
    EXPECT_EQ((solve(1)), (std::string("1")));
    EXPECT_EQ((solve(-102)), (std::string("")));
    EXPECT_EQ((solve(551)), (std::string("1011")));
    EXPECT_EQ((solve(26)), (std::string("1000")));
}

TEST(Characterization, add_01) {
    EXPECT_EQ((add(std::vector<int >{3, 122, 4})), (122));
    EXPECT_EQ((add(std::vector<int >{4, 5, 6, 7, 2, 122, 27})), (122));
    EXPECT_EQ((add(std::vector<int >{4, 2, 6, 7})), (2));
    EXPECT_EQ((add(std::vector<int >{6})), (0));
    EXPECT_EQ((add(std::vector<int >{})), (0));
    EXPECT_EQ((add(std::vector<int >{22, 679})), (0));
    EXPECT_EQ((add(std::vector<int >{4, 0, 6, 7})), (0));
    EXPECT_EQ((add(std::vector<int >{122})), (0));
    EXPECT_EQ((add(std::vector<int >{4, 4, 6, 8})), (12));
    EXPECT_EQ((add(std::vector<int >{15, 25, 960, 22, 30})), (22));
    EXPECT_EQ((add(std::vector<int >{-412, -9, 24})), (0));
    EXPECT_EQ((add(std::vector<int >{4, 88, 9})), (88));
}

TEST(Characterization, anti_shuffle_01) {
    EXPECT_EQ((anti_shuffle(std::string("6ello"))), (std::string("6ello")));
    EXPECT_EQ((anti_shuffle(std::string("GKe6YH"))), (std::string("6GHKYe")));
    EXPECT_EQ((anti_shuffle(std::string("I"))), (std::string("I")));
    EXPECT_EQ((anti_shuffle(std::string("hello"))), (std::string("ehllo")));
    EXPECT_EQ((anti_shuffle(std::string("abcd"))), (std::string("abcd")));
    EXPECT_EQ((anti_shuffle(std::string("Hi. MyLname is Mister Robot. How are youx"))), (std::string(".Hi LMaemny is Meirst .Rboot How aer ouxy")));
    EXPECT_EQ((anti_shuffle(std::string(".Hi My aemn is Meirst .Rboot How aer \?ouy"))), (std::string(".Hi My aemn is Meirst .Rboot How aer \?ouy")));
    EXPECT_EQ((anti_shuffle(std::string("Hello World9!a!"))), (std::string("Hello !!9Wadlor")));
    EXPECT_EQ((anti_shuffle(std::string("Hi. My name is Mister Robot. How are you\?"))), (std::string(".Hi My aemn is Meirst .Rboot How aer \?ouy")));
    EXPECT_EQ((anti_shuffle(std::string("z"))), (std::string("z")));
    EXPECT_EQ((anti_shuffle(std::string("U94JfDvjxwa"))), (std::string("49DJUafjvwx")));
    EXPECT_EQ((anti_shuffle(std::string("bemu"))), (std::string("bemu")));
}

TEST(Characterization, get_row_01) {
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 4)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{}}, 6)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{9, 168, 17, 23}, std::vector<int >{4, 0, -764}}, 6)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{}, std::vector<int >{6, 820}}, 1)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 20)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 0)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{}, std::vector<int >{}, std::vector<int >{}}, 4)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{}, std::vector<int >{}, std::vector<int >{}, std::vector<int >{}}, -764)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1, 1, 0}, std::vector<int >{1, 1, 0}}, 1)), (std::vector<std::vector<int > >{std::vector<int >{0, 1}, std::vector<int >{0, 0}, std::vector<int >{1, 1}, std::vector<int >{1, 0}}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{-5, 3}, std::vector<int >{2, -157, 2}, std::vector<int >{23, 2}, std::vector<int >{237, -581}}, 16)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0, 1, 0}, std::vector<int >{0, 0, 0}, std::vector<int >{0, 1, 0}}, 21)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{22, 1, 1}, std::vector<int >{2, 25, 28}, std::vector<int >{}, std::vector<int >{1}}, -7)), (std::vector<std::vector<int > >{}));
}

TEST(Characterization, sort_array_01) {
    EXPECT_EQ((sort_array(std::vector<int >{1, 966, 2, 9, 32})), (std::vector<int >{1, 2, 9, 32, 966}));
    EXPECT_EQ((sort_array(std::vector<int >{11, 14, 23, 21})), (std::vector<int >{23, 21, 14, 11}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 1})), (std::vector<int >{1, 2}));
    EXPECT_EQ((sort_array(std::vector<int >{6, 5, 4, 3, 2, 1, 0})), (std::vector<int >{6, 5, 4, 3, 2, 1, 0}));
    EXPECT_EQ((sort_array(std::vector<int >{-8, 20, 15, 8, 14})), (std::vector<int >{20, 15, 14, 8, -8}));
    EXPECT_EQ((sort_array(std::vector<int >{-355, 14, 87, 15, 21, 21})), (std::vector<int >{87, 21, 21, 15, 14, -355}));
    EXPECT_EQ((sort_array(std::vector<int >{5})), (std::vector<int >{5}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 2})), (std::vector<int >{1, 2}));
    EXPECT_EQ((sort_array(std::vector<int >{5, 21, -5, 21, -5, 27})), (std::vector<int >{27, 21, 21, 5, -5, -5}));
    EXPECT_EQ((sort_array(std::vector<int >{-2, 87, 27, -4, 30, -2, 2})), (std::vector<int >{87, 30, 27, 2, -2, -2, -4}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 4, 3, 0, 1, 5, 6})), (std::vector<int >{6, 5, 4, 3, 2, 1, 0}));
    EXPECT_EQ((sort_array(std::vector<int >{21, 14, 23, 11})), (std::vector<int >{23, 21, 14, 11}));
}
