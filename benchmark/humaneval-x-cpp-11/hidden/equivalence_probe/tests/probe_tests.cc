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

TEST(Probe, numerical_letter_grade_01) {
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{4.0f, 3.0f, 1.70000005f, 3.5f})), (std::vector<std::string >{std::string("A+"), std::string("B"), std::string("C-"), std::string("A-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.0f, 0.300000012f, 1.5f, 2.79999995f, 3.29999995f})), (std::vector<std::string >{std::string("D"), std::string("D-"), std::string("C-"), std::string("B"), std::string("B+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{7.0999999f, 1.89999998f, 0.5f, 3.20000005f, 3.29999995f})), (std::vector<std::string >{std::string("A+"), std::string("C"), std::string("D-"), std::string("B+"), std::string("B+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.0f})), (std::vector<std::string >{std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.20000005f})), (std::vector<std::string >{std::string("D+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{-5.80000019f, -2.5f, 2.0f, -6.69999981f, 2.79999995f})), (std::vector<std::string >{std::string("E"), std::string("E"), std::string("C"), std::string("E"), std::string("B")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{4.0f, 3.0f, 1.70000005f, 2.0f, 3.5f})), (std::vector<std::string >{std::string("A+"), std::string("B"), std::string("C-"), std::string("C"), std::string("A-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{18.1000004f})), (std::vector<std::string >{std::string("A+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{4.0f, 3.5f, 1.70000005f, 2.0f, 3.0f})), (std::vector<std::string >{std::string("A+"), std::string("A-"), std::string("C-"), std::string("C"), std::string("B")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.0f, 2.0f})), (std::vector<std::string >{std::string("D"), std::string("C")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.300000012f, 2.79999995f, -1.83000004f, 3.9000001f, 2.4000001f})), (std::vector<std::string >{std::string("D-"), std::string("B"), std::string("E"), std::string("A"), std::string("B-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.5f, 2.70000005f})), (std::vector<std::string >{std::string("D-"), std::string("B-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.0f, 3.70000005f, 7.19999981f, -1.20000005f, -0.400000006f})), (std::vector<std::string >{std::string("E"), std::string("A-"), std::string("A+"), std::string("E"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{3.70000005f, -1.0f})), (std::vector<std::string >{std::string("A-"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{3.0f, 4.0f, 1.70000005f, 2.0f, 3.5f})), (std::vector<std::string >{std::string("B"), std::string("A+"), std::string("C-"), std::string("C"), std::string("A-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.39999998f, 12.6999998f, -1.0f, -0.800000012f, -2.5f, -9.89999962f})), (std::vector<std::string >{std::string("C-"), std::string("A+"), std::string("E"), std::string("E"), std::string("E"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{7.19000006f, 2.79999995f, -14.6000004f, -1.60000002f, 9.69999981f, -5.4000001f, 1.5f, 17.2000008f})), (std::vector<std::string >{std::string("A+"), std::string("B"), std::string("E"), std::string("E"), std::string("A+"), std::string("E"), std::string("C-"), std::string("A+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.70000005f, 2.9000001f, 0.0f, 1.0f, 0.699999988f, 3.0f})), (std::vector<std::string >{std::string("C-"), std::string("B"), std::string("E"), std::string("D"), std::string("D-"), std::string("B")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.0f, 0.5f})), (std::vector<std::string >{std::string("E"), std::string("D-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.0f, 0.300000012f, 1.5f, 2.79999995f, 3.29999995f, -0.800000012f})), (std::vector<std::string >{std::string("D"), std::string("D-"), std::string("C-"), std::string("B"), std::string("B+"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{-14.8000002f, 2.0f, -13.3000002f, 0.5f})), (std::vector<std::string >{std::string("E"), std::string("C"), std::string("E"), std::string("D-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{-16.6000004f})), (std::vector<std::string >{std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{2.29999995f, 14.8999996f, -9.30000019f, 2.0f})), (std::vector<std::string >{std::string("C+"), std::string("A+"), std::string("E"), std::string("C")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.60000002f, 1.0f, 7.19999981f, -11.1000004f, 8.94999981f, 15.0f, 2.70000005f})), (std::vector<std::string >{std::string("C-"), std::string("D"), std::string("A+"), std::string("E"), std::string("A+"), std::string("A+"), std::string("B-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.5f, 4.0f})), (std::vector<std::string >{std::string("D-"), std::string("A+")}));
}

TEST(Probe, numerical_letter_grade_02) {
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{3.0f})), (std::vector<std::string >{std::string("B")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{-14.1999998f})), (std::vector<std::string >{std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{2.70000005f, -16.1000004f, 1.29999995f, 3.0f, 3.5999999f, 1.20000005f})), (std::vector<std::string >{std::string("B-"), std::string("E"), std::string("D+"), std::string("B"), std::string("A-"), std::string("D+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.5f, 0.699999988f})), (std::vector<std::string >{std::string("D-"), std::string("D-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{2.0f})), (std::vector<std::string >{std::string("C")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.0f, 0.300000012f, 1.5f, 2.79999995f, 3.29999995f, 0.5f})), (std::vector<std::string >{std::string("D"), std::string("D-"), std::string("C-"), std::string("B"), std::string("B+"), std::string("D-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{3.70000005f})), (std::vector<std::string >{std::string("A-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.300000012f, 19.6000004f, 0.699999988f, 8.31999969f, 1.35000002f, 3.0f})), (std::vector<std::string >{std::string("D-"), std::string("A+"), std::string("D-"), std::string("A+"), std::string("C-"), std::string("B")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{7.48000002f, -15.1000004f, -7.19999981f, 5.0999999f, -18.0f, 1.0f})), (std::vector<std::string >{std::string("A+"), std::string("E"), std::string("E"), std::string("A+"), std::string("E"), std::string("D")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{-12.8000002f})), (std::vector<std::string >{std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{2.79999995f, 2.0f, 0.5f, 0.300000012f, 5.30000019f})), (std::vector<std::string >{std::string("B"), std::string("C"), std::string("D-"), std::string("D-"), std::string("A+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{5.0999999f, 3.70000005f, -8.69999981f, 3.29999995f, 4.4000001f, -6.0999999f, 3.0f, 0.5f})), (std::vector<std::string >{std::string("A+"), std::string("A-"), std::string("E"), std::string("B+"), std::string("A+"), std::string("E"), std::string("B"), std::string("D-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.0f, 2.4000001f, 1.79999995f, 13.3000002f, 7.5f, 0.5f, -17.7999992f})), (std::vector<std::string >{std::string("D"), std::string("B-"), std::string("C"), std::string("A+"), std::string("A+"), std::string("D-"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.699999988f})), (std::vector<std::string >{std::string("D-")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.20000005f, -1.60000002f})), (std::vector<std::string >{std::string("D+"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.0f})), (std::vector<std::string >{std::string("D")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.0f, 3.5f, 3.5f, -8.72999954f})), (std::vector<std::string >{std::string("E"), std::string("A-"), std::string("A-"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{2.79999995f, 9.5f})), (std::vector<std::string >{std::string("B"), std::string("A+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{4.0f, 3.0f, 1.70000005f, 2.0f, 3.5f, -1.79999995f})), (std::vector<std::string >{std::string("A+"), std::string("B"), std::string("C-"), std::string("C"), std::string("A-"), std::string("E")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.0f, 12.6999998f, 1.5f, 2.79999995f, 3.29999995f})), (std::vector<std::string >{std::string("D"), std::string("A+"), std::string("C-"), std::string("B"), std::string("B+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{0.0f, 2.0f, 1.5f, 3.0f})), (std::vector<std::string >{std::string("E"), std::string("C"), std::string("C-"), std::string("B")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{3.5f, 6.9000001f})), (std::vector<std::string >{std::string("A-"), std::string("A+")}));
    EXPECT_EQ((numerical_letter_grade(std::vector<float >{1.20000005f, -4.78999996f})), (std::vector<std::string >{std::string("D+"), std::string("E")}));
}

TEST(Probe, prime_length_01) {
    EXPECT_EQ((prime_length(std::string("MadaM"))), (true));
    EXPECT_EQ((prime_length(std::string("o"))), (false));
    EXPECT_EQ((prime_length(std::string("world"))), (true));
    EXPECT_EQ((prime_length(std::string("aJaaaaaaaaaaa"))), (true));
    EXPECT_EQ((prime_length(std::string("fb44rt"))), (false));
    EXPECT_EQ((prime_length(std::string("e"))), (false));
    EXPECT_EQ((prime_length(std::string("HzCG6oqm"))), (false));
    EXPECT_EQ((prime_length(std::string("7WKF"))), (false));
    EXPECT_EQ((prime_length(std::string("FsG1owhQEF4T"))), (false));
    EXPECT_EQ((prime_length(std::string("Hello"))), (true));
    EXPECT_EQ((prime_length(std::string("t1lXt"))), (true));
    EXPECT_EQ((prime_length(std::string("abcdcba"))), (true));
    EXPECT_EQ((prime_length(std::string("gYL6"))), (false));
    EXPECT_EQ((prime_length(std::string("bFS"))), (true));
    EXPECT_EQ((prime_length(std::string("wow"))), (true));
    EXPECT_EQ((prime_length(std::string("xada3"))), (true));
    EXPECT_EQ((prime_length(std::string("JggKo"))), (true));
    EXPECT_EQ((prime_length(std::string("SrTgfTG2VdY"))), (true));
    EXPECT_EQ((prime_length(std::string("aaaaaaaaaaaaaaa"))), (false));
    EXPECT_EQ((prime_length(std::string("Madam"))), (true));
    EXPECT_EQ((prime_length(std::string("AdwjhD3u"))), (false));
    EXPECT_EQ((prime_length(std::string("HeTo"))), (false));
    EXPECT_EQ((prime_length(std::string("vbSx"))), (false));
    EXPECT_EQ((prime_length(std::string("MdaM"))), (false));
    EXPECT_EQ((prime_length(std::string("Maam"))), (false));
}

TEST(Probe, prime_length_02) {
    EXPECT_EQ((prime_length(std::string(""))), (false));
    EXPECT_EQ((prime_length(std::string("GadNM"))), (true));
    EXPECT_EQ((prime_length(std::string("QoDbq1NJph"))), (false));
    EXPECT_EQ((prime_length(std::string("MyaM"))), (false));
    EXPECT_EQ((prime_length(std::string("gCglo"))), (true));
    EXPECT_EQ((prime_length(std::string("GmR"))), (true));
    EXPECT_EQ((prime_length(std::string("gogo"))), (false));
    EXPECT_EQ((prime_length(std::string("Wow"))), (true));
    EXPECT_EQ((prime_length(std::string("0bC2dCFCV"))), (false));
    EXPECT_EQ((prime_length(std::string("2"))), (false));
    EXPECT_EQ((prime_length(std::string("bcdgb"))), (true));
    EXPECT_EQ((prime_length(std::string("8P9MhhZGr"))), (false));
    EXPECT_EQ((prime_length(std::string("WI"))), (true));
    EXPECT_EQ((prime_length(std::string("aaHaa aaaaaaaaaa"))), (false));
    EXPECT_EQ((prime_length(std::string("QQ5w"))), (false));
    EXPECT_EQ((prime_length(std::string("P5hMfEztrqj"))), (true));
    EXPECT_EQ((prime_length(std::string("5Cuu"))), (false));
    EXPECT_EQ((prime_length(std::string("nm6U823"))), (true));
    EXPECT_EQ((prime_length(std::string("aaaaaaaaaaaaaa"))), (false));
    EXPECT_EQ((prime_length(std::string("O"))), (false));
    EXPECT_EQ((prime_length(std::string("DeED03Y4A8"))), (false));
    EXPECT_EQ((prime_length(std::string("p"))), (false));
    EXPECT_EQ((prime_length(std::string("Hllo"))), (false));
}

TEST(Probe, starts_one_ends_01) {
    EXPECT_EQ((starts_one_ends(-763)), (0));
    EXPECT_EQ((starts_one_ends(3)), (180));
    EXPECT_EQ((starts_one_ends(-8)), (0));
    EXPECT_EQ((starts_one_ends(5)), (18000));
    EXPECT_EQ((starts_one_ends(-356)), (0));
    EXPECT_EQ((starts_one_ends(-498)), (0));
    EXPECT_EQ((starts_one_ends(-7)), (0));
    EXPECT_EQ((starts_one_ends(-301)), (0));
    EXPECT_EQ((starts_one_ends(-2)), (0));
    EXPECT_EQ((starts_one_ends(-65)), (0));
    EXPECT_EQ((starts_one_ends(-791)), (0));
    EXPECT_EQ((starts_one_ends(-264)), (0));
    EXPECT_EQ((starts_one_ends(-4)), (0));
    EXPECT_EQ((starts_one_ends(-1)), (0));
    EXPECT_EQ((starts_one_ends(-6)), (0));
    EXPECT_EQ((starts_one_ends(-51)), (0));
    EXPECT_EQ((starts_one_ends(9)), (180000000));
    EXPECT_EQ((starts_one_ends(-976)), (0));
    EXPECT_EQ((starts_one_ends(-990)), (0));
    EXPECT_EQ((starts_one_ends(-218)), (0));
    EXPECT_EQ((starts_one_ends(-674)), (0));
    EXPECT_EQ((starts_one_ends(-381)), (0));
    EXPECT_EQ((starts_one_ends(-955)), (0));
    EXPECT_EQ((starts_one_ends(-895)), (0));
    EXPECT_EQ((starts_one_ends(-114)), (0));
}

TEST(Probe, starts_one_ends_02) {
    EXPECT_EQ((starts_one_ends(-793)), (0));
    EXPECT_EQ((starts_one_ends(-628)), (0));
    EXPECT_EQ((starts_one_ends(-932)), (0));
    EXPECT_EQ((starts_one_ends(-790)), (0));
    EXPECT_EQ((starts_one_ends(-977)), (0));
    EXPECT_EQ((starts_one_ends(-704)), (0));
    EXPECT_EQ((starts_one_ends(-490)), (0));
    EXPECT_EQ((starts_one_ends(-145)), (0));
    EXPECT_EQ((starts_one_ends(-512)), (0));
    EXPECT_EQ((starts_one_ends(-537)), (0));
    EXPECT_EQ((starts_one_ends(-505)), (0));
    EXPECT_EQ((starts_one_ends(-9)), (0));
    EXPECT_EQ((starts_one_ends(-449)), (0));
    EXPECT_EQ((starts_one_ends(-701)), (0));
    EXPECT_EQ((starts_one_ends(-351)), (0));
    EXPECT_EQ((starts_one_ends(-529)), (0));
    EXPECT_EQ((starts_one_ends(-721)), (0));
    EXPECT_EQ((starts_one_ends(-920)), (0));
    EXPECT_EQ((starts_one_ends(-711)), (0));
    EXPECT_EQ((starts_one_ends(-660)), (0));
    EXPECT_EQ((starts_one_ends(-392)), (0));
    EXPECT_EQ((starts_one_ends(-905)), (0));
    EXPECT_EQ((starts_one_ends(-427)), (0));
}

TEST(Probe, solve_01) {
    EXPECT_EQ((solve(-579)), (std::string("10010")));
    EXPECT_EQ((solve(-9)), (std::string("110")));
    EXPECT_EQ((solve(-959)), (std::string("10100")));
    EXPECT_EQ((solve(150)), (std::string("110")));
    EXPECT_EQ((solve(-921)), (std::string("1001")));
    EXPECT_EQ((solve(335)), (std::string("1011")));
    EXPECT_EQ((solve(108)), (std::string("1001")));
    EXPECT_EQ((solve(-5)), (std::string("10")));
    EXPECT_EQ((solve(2)), (std::string("10")));
    EXPECT_EQ((solve(-878)), (std::string("10100")));
    EXPECT_EQ((solve(-406)), (std::string("111")));
    EXPECT_EQ((solve(0)), (std::string("")));
    EXPECT_EQ((solve(173)), (std::string("1011")));
    EXPECT_EQ((solve(964)), (std::string("10011")));
    EXPECT_EQ((solve(333)), (std::string("1001")));
    EXPECT_EQ((solve(-255)), (std::string("1001")));
    EXPECT_EQ((solve(963)), (std::string("10010")));
    EXPECT_EQ((solve(-591)), (std::string("1100")));
    EXPECT_EQ((solve(998)), (std::string("11010")));
    EXPECT_EQ((solve(-778)), (std::string("10011")));
    EXPECT_EQ((solve(3)), (std::string("11")));
    EXPECT_EQ((solve(999)), (std::string("11011")));
    EXPECT_EQ((solve(-1)), (std::string("")));
    EXPECT_EQ((solve(614)), (std::string("1011")));
    EXPECT_EQ((solve(-2)), (std::string("")));
}

TEST(Probe, solve_02) {
    EXPECT_EQ((solve(25)), (std::string("111")));
    EXPECT_EQ((solve(1001)), (std::string("10")));
    EXPECT_EQ((solve(-6)), (std::string("11")));
    EXPECT_EQ((solve(-244)), (std::string("111")));
    EXPECT_EQ((solve(22)), (std::string("100")));
    EXPECT_EQ((solve(109)), (std::string("1010")));
    EXPECT_EQ((solve(-3)), (std::string("")));
    EXPECT_EQ((solve(623)), (std::string("1011")));
    EXPECT_EQ((solve(905)), (std::string("1110")));
    EXPECT_EQ((solve(11)), (std::string("10")));
    EXPECT_EQ((solve(346)), (std::string("1101")));
    EXPECT_EQ((solve(370)), (std::string("1010")));
    EXPECT_EQ((solve(14)), (std::string("101")));
    EXPECT_EQ((solve(235)), (std::string("1010")));
    EXPECT_EQ((solve(24)), (std::string("110")));
    EXPECT_EQ((solve(10)), (std::string("1")));
    EXPECT_EQ((solve(6)), (std::string("110")));
    EXPECT_EQ((solve(231)), (std::string("110")));
    EXPECT_EQ((solve(13)), (std::string("100")));
    EXPECT_EQ((solve(1100)), (std::string("10")));
    EXPECT_EQ((solve(751)), (std::string("1101")));
    EXPECT_EQ((solve(-629)), (std::string("1110")));
    EXPECT_EQ((solve(-77)), (std::string("1011")));
}

TEST(Probe, add_01) {
    EXPECT_EQ((add(std::vector<int >{4, 88, 1000})), (88));
    EXPECT_EQ((add(std::vector<int >{4, 4, 6, 8, 28})), (12));
    EXPECT_EQ((add(std::vector<int >{4, 88})), (88));
    EXPECT_EQ((add(std::vector<int >{4, 5, 6, 7, 2, 122})), (122));
    EXPECT_EQ((add(std::vector<int >{7, 2, 6, 4})), (6));
    EXPECT_EQ((add(std::vector<int >{4, 6, 2, 7})), (6));
    EXPECT_EQ((add(std::vector<int >{13, 2, 0})), (2));
    EXPECT_EQ((add(std::vector<int >{4, 88, 0})), (88));
    EXPECT_EQ((add(std::vector<int >{4, 0, 6, 7, 19})), (0));
    EXPECT_EQ((add(std::vector<int >{5, 12, 120, 12})), (24));
    EXPECT_EQ((add(std::vector<int >{4, 28, 6, 7})), (28));
    EXPECT_EQ((add(std::vector<int >{4, 0, 6, 7, 9})), (0));
    EXPECT_EQ((add(std::vector<int >{4, 5, 6, 7, -1, 122})), (122));
    EXPECT_EQ((add(std::vector<int >{-653, 3, 4, 14, 30, -8, 122})), (6));
    EXPECT_EQ((add(std::vector<int >{4, 0, 6, 7, 4})), (0));
    EXPECT_EQ((add(std::vector<int >{-6, 14, 635, 12, 168, 9})), (26));
    EXPECT_EQ((add(std::vector<int >{880, 30, 2})), (30));
    EXPECT_EQ((add(std::vector<int >{123, 11, -35})), (0));
    EXPECT_EQ((add(std::vector<int >{10, 23, -808, 3, -9, 592, -313})), (592));
    EXPECT_EQ((add(std::vector<int >{29, 559, 2, 813, 19, 3, 90})), (0));
    EXPECT_EQ((add(std::vector<int >{2, 6, 7})), (6));
    EXPECT_EQ((add(std::vector<int >{4, 12, 6, 7})), (12));
    EXPECT_EQ((add(std::vector<int >{7})), (0));
    EXPECT_EQ((add(std::vector<int >{4, 2, 6, 7, 88})), (2));
    EXPECT_EQ((add(std::vector<int >{1, 6, -1, 21, 8, 8, 287})), (14));
}

TEST(Probe, add_02) {
    EXPECT_EQ((add(std::vector<int >{5, 4, 6, 7, 2, 122})), (126));
    EXPECT_EQ((add(std::vector<int >{12})), (0));
    EXPECT_EQ((add(std::vector<int >{8, 4, 6, 4})), (8));
    EXPECT_EQ((add(std::vector<int >{4, 7, 6, 2})), (2));
    EXPECT_EQ((add(std::vector<int >{0, 28})), (28));
    EXPECT_EQ((add(std::vector<int >{5, 7, 19, -4, 850, -810, 5})), (-814));
    EXPECT_EQ((add(std::vector<int >{0, 6, 7})), (6));
    EXPECT_EQ((add(std::vector<int >{4, 6, 7, 2, 122})), (8));
    EXPECT_EQ((add(std::vector<int >{12, 6, 5})), (6));
    EXPECT_EQ((add(std::vector<int >{-566, -2, -1, 26, 88, 3, 15, 100})), (124));
    EXPECT_EQ((add(std::vector<int >{4, 2, 7})), (2));
    EXPECT_EQ((add(std::vector<int >{12, 5, 4, 11, 20, 271})), (0));
    EXPECT_EQ((add(std::vector<int >{19})), (0));
    EXPECT_EQ((add(std::vector<int >{88, 24, 12345, 22, -1000, 23, 2})), (46));
    EXPECT_EQ((add(std::vector<int >{4, 5, 6, 7, 2})), (0));
    EXPECT_EQ((add(std::vector<int >{6, 4, 6, 8})), (12));
    EXPECT_EQ((add(std::vector<int >{5})), (0));
    EXPECT_EQ((add(std::vector<int >{4, 0, 6, 7, 5})), (0));
    EXPECT_EQ((add(std::vector<int >{13, 12, 0, 2, -9})), (14));
    EXPECT_EQ((add(std::vector<int >{19, 8, -718})), (8));
    EXPECT_EQ((add(std::vector<int >{-1, 6, 88, 418, 10, 2, 691, 15})), (426));
    EXPECT_EQ((add(std::vector<int >{4, 12})), (12));
    EXPECT_EQ((add(std::vector<int >{4, 10, 6, 7})), (10));
}

TEST(Probe, anti_shuffle_01) {
    EXPECT_EQ((anti_shuffle(std::string("Hello !!!Wdlor"))), (std::string("Hello !!!Wdlor")));
    EXPECT_EQ((anti_shuffle(std::string("k7I1"))), (std::string("17Ik")));
    EXPECT_EQ((anti_shuffle(std::string("dZBr1zs3i"))), (std::string("13BZdirsz")));
    EXPECT_EQ((anti_shuffle(std::string("nuDbr"))), (std::string("Dbnru")));
    EXPECT_EQ((anti_shuffle(std::string("bmnru"))), (std::string("bmnru")));
    EXPECT_EQ((anti_shuffle(std::string("THi. My name is Mister Robot.Y How are you\?"))), (std::string(".HTi My aemn is Meirst .RYboot How aer \?ouy")));
    EXPECT_EQ((anti_shuffle(std::string("HelloWorld!!!"))), (std::string("!!!HWdellloor")));
    EXPECT_EQ((anti_shuffle(std::string("Hejllo !!Wdlog"))), (std::string("Hejllo !!Wdglo")));
    EXPECT_EQ((anti_shuffle(std::string("gSko1 k"))), (std::string("1Sgko k")));
    EXPECT_EQ((anti_shuffle(std::string("yjMW"))), (std::string("MWjy")));
    EXPECT_EQ((anti_shuffle(std::string("JP5itGaLTnZ!"))), (std::string("!5GJLPTZaint")));
    EXPECT_EQ((anti_shuffle(std::string("nupb6etr"))), (std::string("6benprtu")));
    EXPECT_EQ((anti_shuffle(std::string("dGMfO"))), (std::string("GMOdf")));
    EXPECT_EQ((anti_shuffle(std::string("Gnl"))), (std::string("Gln")));
    EXPECT_EQ((anti_shuffle(std::string("besmUrmu"))), (std::string("Ubemmrsu")));
    EXPECT_EQ((anti_shuffle(std::string("fJB"))), (std::string("BJf")));
    EXPECT_EQ((anti_shuffle(std::string("Z7zF4!bSMVEg"))), (std::string("!47EFMSVZbgz")));
    EXPECT_EQ((anti_shuffle(std::string(".pHi My aen is Meirst .Rboot How aer \?Xouy"))), (std::string(".Hip My aen is Meirst .Rboot How aer \?Xouy")));
    EXPECT_EQ((anti_shuffle(std::string("at9cd"))), (std::string("9acdt")));
    EXPECT_EQ((anti_shuffle(std::string("ehllo"))), (std::string("ehllo")));
    EXPECT_EQ((anti_shuffle(std::string("bemnru"))), (std::string("bemnru")));
    EXPECT_EQ((anti_shuffle(std::string(" k OFtnan"))), (std::string("k FOannt")));
    EXPECT_EQ((anti_shuffle(std::string("AoikbgbCVSl"))), (std::string("ACSVbbgiklo")));
    EXPECT_EQ((anti_shuffle(std::string("ehlTo"))), (std::string("Tehlo")));
    EXPECT_EQ((anti_shuffle(std::string(".gW0NX"))), (std::string(".0NWXg")));
}

TEST(Probe, anti_shuffle_02) {
    EXPECT_EQ((anti_shuffle(std::string("hN"))), (std::string("Nh")));
    EXPECT_EQ((anti_shuffle(std::string("Helo !!!Wdlor"))), (std::string("Helo !!!Wdlor")));
    EXPECT_EQ((anti_shuffle(std::string("Hello !E!Wdlor"))), (std::string("Hello !!EWdlor")));
    EXPECT_EQ((anti_shuffle(std::string(""))), (std::string("")));
    EXPECT_EQ((anti_shuffle(std::string("Hi"))), (std::string("Hi")));
    EXPECT_EQ((anti_shuffle(std::string("Hdl6OfM"))), (std::string("6HMOdfl")));
    EXPECT_EQ((anti_shuffle(std::string("5oL0 1"))), (std::string("05Lo 1")));
    EXPECT_EQ((anti_shuffle(std::string("!"))), (std::string("!")));
    EXPECT_EQ((anti_shuffle(std::string(".abyucd"))), (std::string(".abcduy")));
    EXPECT_EQ((anti_shuffle(std::string("hel lo"))), (std::string("ehl lo")));
    EXPECT_EQ((anti_shuffle(std::string("be.m1nu"))), (std::string(".1bemnu")));
    EXPECT_EQ((anti_shuffle(std::string("eluo"))), (std::string("elou")));
    EXPECT_EQ((anti_shuffle(std::string("lNRa"))), (std::string("NRal")));
    EXPECT_EQ((anti_shuffle(std::string("L1"))), (std::string("1L")));
    EXPECT_EQ((anti_shuffle(std::string("Hello !!!Wlor"))), (std::string("Hello !!!Wlor")));
    EXPECT_EQ((anti_shuffle(std::string("kuMfOJ"))), (std::string("JMOfku")));
    EXPECT_EQ((anti_shuffle(std::string("acYd"))), (std::string("Yacd")));
    EXPECT_EQ((anti_shuffle(std::string("eFmnru"))), (std::string("Femnru")));
    EXPECT_EQ((anti_shuffle(std::string("A"))), (std::string("A")));
    EXPECT_EQ((anti_shuffle(std::string("number"))), (std::string("bemnru")));
    EXPECT_EQ((anti_shuffle(std::string("Hello World!!!"))), (std::string("Hello !!!Wdlor")));
    EXPECT_EQ((anti_shuffle(std::string("t"))), (std::string("t")));
    EXPECT_EQ((anti_shuffle(std::string("JB"))), (std::string("BJ")));
}

TEST(Probe, get_row_01) {
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{3}, std::vector<int >{2, 8}, std::vector<int >{0}}, 100)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1}, std::vector<int >{0}}, 933)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1, 0, 0}, std::vector<int >{}}, 6)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1, 0, 0, 0}, std::vector<int >{0, 0, 1, 1}, std::vector<int >{1, 0, 0, 0}, std::vector<int >{0, 0, 1, 0}}, -975)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1, 1}}, 13)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{-8, 2, -950, 836}, std::vector<int >{-1, 1, -148, 6}}, 2)), (std::vector<std::vector<int > >{std::vector<int >{0, 1}}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{6, 3, 5}}, 221)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{108, 2, -128, 6}, std::vector<int >{24, 29, 1, 0}, std::vector<int >{6, 14, 12, 20}}, 20)), (std::vector<std::vector<int > >{std::vector<int >{2, 3}}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 963)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1}, std::vector<int >{1}, std::vector<int >{0}, std::vector<int >{1}}, 20)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{3, 26, 72}}, 5)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 2)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{29}}, 5)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0, 1, 0, 1}, std::vector<int >{0, 1, 0, 0}}, 2)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1}, std::vector<int >{}, std::vector<int >{0}}, -10)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0, 2, 328}}, 2)), (std::vector<std::vector<int > >{std::vector<int >{0, 1}}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{}}, 5)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{}, std::vector<int >{}}, 3)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{8}, std::vector<int >{1}, std::vector<int >{9}}, 23)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1, 0, 1}, std::vector<int >{1, 0, 0}, std::vector<int >{0, 0, 0}, std::vector<int >{1, 0, 0}}, 224)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{-227, 12, -1}, std::vector<int >{0, -2, 1}}, 6)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{}}, -9)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 707)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 6)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 5)), (std::vector<std::vector<int > >{}));
}

TEST(Probe, get_row_02) {
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0, 1, 0}, std::vector<int >{0, 0, 1}, std::vector<int >{0}}, 20)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{6}}, 23)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{4, 196, 505}, std::vector<int >{3, 7, 4}, std::vector<int >{5, 492, 8}, std::vector<int >{11, -417, -860}}, 2)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 1)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{117}}, 1)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1}, std::vector<int >{1}, std::vector<int >{}}, 10)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{}}, 4)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{14, 1}}, 5)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 3)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, 378)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{}, std::vector<int >{}, std::vector<int >{}}, 99999)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{2, 0, -447}, std::vector<int >{1, 0, -1}}, 446)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{-3, 1, 2}}, -312)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1, 0}, std::vector<int >{0, 1}, std::vector<int >{0, 1}, std::vector<int >{0, 1}}, -7)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{27, 21, 0}, std::vector<int >{25}}, -10)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0, 1}, std::vector<int >{1, 1}, std::vector<int >{1}, std::vector<int >{0, 1}}, 943)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0, 0, 0}, std::vector<int >{1, 1, 1}}, 5)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{}, -1)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0}, std::vector<int >{1}}, -1)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0}, std::vector<int >{1}}, 2)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{1, 1, 1, 0}, std::vector<int >{0, 1, 1, 1}}, 4)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0, 1}, std::vector<int >{0}}, 2)), (std::vector<std::vector<int > >{}));
    EXPECT_EQ((get_row(std::vector<std::vector<int > >{std::vector<int >{0, 1, 1}}, 5)), (std::vector<std::vector<int > >{}));
}

TEST(Probe, sort_array_01) {
    EXPECT_EQ((sort_array(std::vector<int >{-7})), (std::vector<int >{-7}));
    EXPECT_EQ((sort_array(std::vector<int >{23})), (std::vector<int >{23}));
    EXPECT_EQ((sort_array(std::vector<int >{21, 269, -2, 18})), (std::vector<int >{-2, 18, 21, 269}));
    EXPECT_EQ((sort_array(std::vector<int >{0, 11, 15, 32, 42, 87})), (std::vector<int >{0, 11, 15, 32, 42, 87}));
    EXPECT_EQ((sort_array(std::vector<int >{32, 11, 15, 0, 42, 87})), (std::vector<int >{0, 11, 15, 32, 42, 87}));
    EXPECT_EQ((sort_array(std::vector<int >{2})), (std::vector<int >{2}));
    EXPECT_EQ((sort_array(std::vector<int >{0, 11, 15, 32, 42, 87, -2})), (std::vector<int >{87, 42, 32, 15, 11, 0, -2}));
    EXPECT_EQ((sort_array(std::vector<int >{0, 1, -4, 3, 4, 5})), (std::vector<int >{-4, 0, 1, 3, 4, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{21, 0, 23, 11})), (std::vector<int >{23, 21, 11, 0}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 1, -3})), (std::vector<int >{2, 1, -3}));
    EXPECT_EQ((sort_array(std::vector<int >{8})), (std::vector<int >{8}));
    EXPECT_EQ((sort_array(std::vector<int >{100, 797})), (std::vector<int >{100, 797}));
    EXPECT_EQ((sort_array(std::vector<int >{0, 1, 2, 3, 4, 5})), (std::vector<int >{0, 1, 2, 3, 4, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{30, 3, 30, 1, 7, 87, 41})), (std::vector<int >{1, 3, 7, 30, 30, 41, 87}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 5, 3, 0, 1, 4})), (std::vector<int >{5, 4, 3, 2, 1, 0}));
    EXPECT_EQ((sort_array(std::vector<int >{24, 87, 5, -135, 23, -1, 42, -8})), (std::vector<int >{87, 42, 24, 23, 5, -1, -8, -135}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 1, 1})), (std::vector<int >{1, 1, 2}));
    EXPECT_EQ((sort_array(std::vector<int >{0, 11, 15, 32, 87})), (std::vector<int >{0, 11, 15, 32, 87}));
    EXPECT_EQ((sort_array(std::vector<int >{15, 42, 87, 32, 11, 0})), (std::vector<int >{0, 11, 15, 32, 42, 87}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 13, 0, -120, 2, 919})), (std::vector<int >{-120, 0, 2, 2, 13, 919}));
    EXPECT_EQ((sort_array(std::vector<int >{3, 15, 8, 14, 15, 5})), (std::vector<int >{15, 15, 14, 8, 5, 3}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 4, 3, 0, 1, 5})), (std::vector<int >{0, 1, 2, 3, 4, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{23, 3, 0, 17, 13})), (std::vector<int >{23, 17, 13, 3, 0}));
    EXPECT_EQ((sort_array(std::vector<int >{21})), (std::vector<int >{21}));
    EXPECT_EQ((sort_array(std::vector<int >{5, 86})), (std::vector<int >{5, 86}));
}

TEST(Probe, sort_array_02) {
    EXPECT_EQ((sort_array(std::vector<int >{26, 1})), (std::vector<int >{1, 26}));
    EXPECT_EQ((sort_array(std::vector<int >{3, 1, 2, 0, 4, 5})), (std::vector<int >{5, 4, 3, 2, 1, 0}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 4, 23, 0, 1, 5, 6})), (std::vector<int >{23, 6, 5, 4, 2, 1, 0}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 2, 27, 22, 15, 4})), (std::vector<int >{1, 2, 4, 15, 22, 27}));
    EXPECT_EQ((sort_array(std::vector<int >{4, 3, 5})), (std::vector<int >{3, 4, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{-989, 1})), (std::vector<int >{1, -989}));
    EXPECT_EQ((sort_array(std::vector<int >{4, -389, 1})), (std::vector<int >{-389, 1, 4}));
    EXPECT_EQ((sort_array(std::vector<int >{4, 6, 419})), (std::vector<int >{4, 6, 419}));
    EXPECT_EQ((sort_array(std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((sort_array(std::vector<int >{3, 7, 24, 21, 30, 6, 15, 3})), (std::vector<int >{30, 24, 21, 15, 7, 6, 3, 3}));
    EXPECT_EQ((sort_array(std::vector<int >{21, 14, 23, 11, 2})), (std::vector<int >{2, 11, 14, 21, 23}));
    EXPECT_EQ((sort_array(std::vector<int >{6, 5, 4, 3, 2, 0, 1})), (std::vector<int >{0, 1, 2, 3, 4, 5, 6}));
    EXPECT_EQ((sort_array(std::vector<int >{0, 1, 3, 2, 4, 5})), (std::vector<int >{0, 1, 2, 3, 4, 5}));
    EXPECT_EQ((sort_array(std::vector<int >{63})), (std::vector<int >{63}));
    EXPECT_EQ((sort_array(std::vector<int >{0, 14, 23, 11})), (std::vector<int >{0, 11, 14, 23}));
    EXPECT_EQ((sort_array(std::vector<int >{20, -496})), (std::vector<int >{20, -496}));
    EXPECT_EQ((sort_array(std::vector<int >{43, 8, 14, 2, -1, 2, 26, 23})), (std::vector<int >{43, 26, 23, 14, 8, 2, 2, -1}));
    EXPECT_EQ((sort_array(std::vector<int >{87, 351, 21, 21, 2, 0})), (std::vector<int >{0, 2, 21, 21, 87, 351}));
    EXPECT_EQ((sort_array(std::vector<int >{10, 27, -7})), (std::vector<int >{-7, 10, 27}));
    EXPECT_EQ((sort_array(std::vector<int >{1, 20, -390, -4})), (std::vector<int >{20, 1, -4, -390}));
    EXPECT_EQ((sort_array(std::vector<int >{16, 12, -9, 4, 175})), (std::vector<int >{-9, 4, 12, 16, 175}));
    EXPECT_EQ((sort_array(std::vector<int >{13, 7, 23})), (std::vector<int >{23, 13, 7}));
    EXPECT_EQ((sort_array(std::vector<int >{2, 1, 0, 3, 4, 5})), (std::vector<int >{0, 1, 2, 3, 4, 5}));
}
