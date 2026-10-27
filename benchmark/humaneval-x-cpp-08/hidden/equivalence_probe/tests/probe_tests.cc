// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_08.h"

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

TEST(Probe, monotonic_01) {
    EXPECT_EQ((monotonic(std::vector<float >{-1.15999997f, 10.0f, -2.20000005f, 14.6999998f, 9.0f, 10.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{0.899999976f, 7.19999981f, 9.0f, -18.6000004f, 2.57999992f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{2.0f, 4.0f, 10.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 3.0f, 4.0f, 5.0f, 60.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 60.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{7.0999999f, 4.0f, 2.0f, 4.0f, -11.1000004f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{3.0f, -13.1000004f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 2.0f, 3.0f, 2.0f, 5.0f, 60.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{-5.80000019f, -2.5f, 60.0f, -6.69999981f, 4.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{18.1000004f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 4.0f, 2.0f, 10.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 1.0f, 0.0f, -10.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 2.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{-10.0f, 14.8000002f, -10.0f, -1.83000004f, 3.9000001f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 1.0f, 0.0f, -10.0f, 20.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{9.0f, 9.0f, 9.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 9.0f, -7.19999981f, 9.0f, 1.0f, 1.0f, 1.0f, 20.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 2.0f, 3.0f, 2.0f, 5.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{-10.0f, 60.0f, 12.6999998f, -1.0f, -0.800000012f, -2.5f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{-1.29999995f, 7.19000006f, 4.0f, 10.0f, -14.6000004f, 1.0f, 60.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 2.0f, 4.0f, 10.0f, 4.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{17.2000008f, 60.0f, -17.2000008f, 2.0f, 1.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 60.0f, 7.30000019f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{9.0f, 10.0f, 16.0f, 14.6000004f, 5.0f, 0.0f})), (false));
}

TEST(Probe, monotonic_02) {
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 2.0f, 4.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 2.0f, 4.0f, 20.0f, 4.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 1.0f, 1.0f, 0.0f, 2.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{-14.8000002f, 10.0f, -13.3000002f, 0.5f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{9.0f, 9.0f, 9.0f, -16.6000004f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{20.0f, -8.39999962f, 4.0f, -5.30000019f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{9.0f, 9.0f, 9.0f, 9.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{5.0f, 7.19999981f, -11.1000004f, 8.94999981f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{20.0f, 12.1999998f, 6.5999999f, 4.0f, 10.0f, 0.0f, 2.9000001f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{0.0f, 20.0f, 10.0f, 9.0f, 9.60000038f, 1.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{4.30000019f, 6.19999981f, -16.1000004f, 60.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{8.31999969f, 20.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{-4.4000001f, 0.0f, 7.5f, 1.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 1.0f, 0.0f, -10.0f, 5.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 16.8999996f, 0.0f, -10.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{-10.0f, -2.58999991f, -10.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 60.0f, 1.0f, 0.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{1.35000002f, 9.0f, -7.82000017f, 19.2000008f, 0.0500000007f, 1.0f, 6.21999979f, -7.5f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 4.0f, 2.0f, 9.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 4.5999999f, 3.0f, 2.0f, 5.0f, 60.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{-3.19000006f, 20.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 0.0f, -10.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 11.3000002f, -10.0f, 3.0f})), (false));
}

TEST(Probe, common_01) {
    EXPECT_EQ((common(std::vector<int >{489}, std::vector<int >{469, 2, 4})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 5, 653}, std::vector<int >{1, 4, 3, 34, 653, 2, 5})), (std::vector<int >{1, 5, 653}));
    EXPECT_EQ((common(std::vector<int >{15, 123, 14, 21, -2, -756}, std::vector<int >{1, 5, 653})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{2, 3}, std::vector<int >{5, 7, 1, 5, 9, 653, 121})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{3, 2}, std::vector<int >{3, 2, 4})), (std::vector<int >{2, 3}));
    EXPECT_EQ((common(std::vector<int >{24}, std::vector<int >{2, 3})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{2, 3, -465}, std::vector<int >{3, 2, 4})), (std::vector<int >{2, 3}));
    EXPECT_EQ((common(std::vector<int >{-104, -779}, std::vector<int >{2, 3, 4})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{}, std::vector<int >{2, -739, 29, 26, 0})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{5, 2, 8}, std::vector<int >{5, 3, 2, 8})), (std::vector<int >{2, 5, 8}));
    EXPECT_EQ((common(std::vector<int >{5, 3, 2, 8}, std::vector<int >{4, 7, -7, 3, 2, 123, 26})), (std::vector<int >{2, 3}));
    EXPECT_EQ((common(std::vector<int >{610}, std::vector<int >{1, 4, 3, 34, 653, 2, 4})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{}, std::vector<int >{1, 5, 653, -3})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 4, 3, 34, 653, 2, 5}, std::vector<int >{1, 4, 3, 34, 653, 2, 5})), (std::vector<int >{1, 2, 3, 4, 5, 34, 653}));
    EXPECT_EQ((common(std::vector<int >{1, 4, 3, 34, 653, 2, 5}, std::vector<int >{1, 5, 653})), (std::vector<int >{1, 5, 653}));
    EXPECT_EQ((common(std::vector<int >{4, 3, 2, 9}, std::vector<int >{3, 2, 4})), (std::vector<int >{2, 3, 4}));
    EXPECT_EQ((common(std::vector<int >{2, 3}, std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{}, std::vector<int >{20, 652, 2, 3, 9})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{2, 3}, std::vector<int >{5, 3, 2})), (std::vector<int >{2, 3}));
    EXPECT_EQ((common(std::vector<int >{4, 3, 2, 8}, std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{82, 9}, std::vector<int >{1, 5, 653})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{3, 32, 4}, std::vector<int >{5, 3, 2, 8})), (std::vector<int >{3}));
    EXPECT_EQ((common(std::vector<int >{653}, std::vector<int >{5, 7, 1, 5, 9, 653, 121})), (std::vector<int >{653}));
    EXPECT_EQ((common(std::vector<int >{121, 11}, std::vector<int >{5, 2, 3, 8})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{-1}, std::vector<int >{0, -93})), (std::vector<int >{}));
}

TEST(Probe, common_02) {
    EXPECT_EQ((common(std::vector<int >{3, 2, 4}, std::vector<int >{0})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 6, 11, 34, 9, -401, 653, 0}, std::vector<int >{4, 3, 2, -833})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 5, 653, -1}, std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 4, 3, 34, 653, 2, 5}, std::vector<int >{495, 189, 5})), (std::vector<int >{5}));
    EXPECT_EQ((common(std::vector<int >{1, 4, 3, 34, 653, 2, 5, 17}, std::vector<int >{22, 121, -5})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{5, 7, 1, 5, 9, 653, 121}, std::vector<int >{3, 2, 644})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{27, -1, 0, -617, -2, 0, 2}, std::vector<int >{5, 1, 121, 1, 14, 19})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{19, 9, 1, 5, 34}, std::vector<int >{2, 3, 4})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{3, 157, 28}, std::vector<int >{2, 3})), (std::vector<int >{3}));
    EXPECT_EQ((common(std::vector<int >{5, 2, 8}, std::vector<int >{-5})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{12, 2}, std::vector<int >{4, 3, 8, 2})), (std::vector<int >{2}));
    EXPECT_EQ((common(std::vector<int >{1, 4, 3, 34, 653, 5}, std::vector<int >{3, 2, 4, -3})), (std::vector<int >{3, 4}));
    EXPECT_EQ((common(std::vector<int >{2, 3, 4}, std::vector<int >{5, 3, 2, 8})), (std::vector<int >{2, 3}));
    EXPECT_EQ((common(std::vector<int >{}, std::vector<int >{34, 3, 2, 4, 4, 0})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1000, 21, 959, 7, 3, 0, 653, 21}, std::vector<int >{2})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 4, 3, 34, 653, 2, 5}, std::vector<int >{5, 7, 1, 5, 9, 653, 121})), (std::vector<int >{1, 5, 653}));
    EXPECT_EQ((common(std::vector<int >{655}, std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 4, 3, 34, 653, 2, 5}, std::vector<int >{1, 4, 3, 34, 2, 5})), (std::vector<int >{1, 2, 3, 4, 5, 34}));
    EXPECT_EQ((common(std::vector<int >{3, 2, 8}, std::vector<int >{5, 7, 497})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 5, 653}, std::vector<int >{4, 2, 2, 8})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{5, 7, 1, 5, 9, 653, 121}, std::vector<int >{19, 11, 10})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 5, 653, 10}, std::vector<int >{2, 4, 3})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{-4, 3, 9, -491, 7}, std::vector<int >{3, 4, 1, 34, 653, 2, 5})), (std::vector<int >{3}));
}

TEST(Probe, largest_prime_factor_01) {
    EXPECT_EQ((largest_prime_factor(-5)), (-5));
    EXPECT_EQ((largest_prime_factor(-10)), (-10));
    EXPECT_EQ((largest_prime_factor(129)), (43));
    EXPECT_EQ((largest_prime_factor(486)), (3));
    EXPECT_EQ((largest_prime_factor(-603)), (-603));
    EXPECT_EQ((largest_prime_factor(8)), (2));
    EXPECT_EQ((largest_prime_factor(100)), (5));
    EXPECT_EQ((largest_prime_factor(18)), (3));
    EXPECT_EQ((largest_prime_factor(10)), (5));
    EXPECT_EQ((largest_prime_factor(-763)), (-763));
    EXPECT_EQ((largest_prime_factor(63)), (7));
    EXPECT_EQ((largest_prime_factor(13)), (13));
    EXPECT_EQ((largest_prime_factor(179)), (179));
    EXPECT_EQ((largest_prime_factor(99999)), (271));
    EXPECT_EQ((largest_prime_factor(11)), (11));
    EXPECT_EQ((largest_prime_factor(17)), (17));
    EXPECT_EQ((largest_prime_factor(2047)), (89));
    EXPECT_EQ((largest_prime_factor(22)), (11));
    EXPECT_EQ((largest_prime_factor(-8)), (-8));
    EXPECT_EQ((largest_prime_factor(251)), (251));
    EXPECT_EQ((largest_prime_factor(332)), (83));
    EXPECT_EQ((largest_prime_factor(29)), (29));
    EXPECT_EQ((largest_prime_factor(375)), (5));
    EXPECT_EQ((largest_prime_factor(64)), (2));
    EXPECT_EQ((largest_prime_factor(366)), (61));
}

TEST(Probe, largest_prime_factor_02) {
    EXPECT_EQ((largest_prime_factor(-356)), (-356));
    EXPECT_EQ((largest_prime_factor(3)), (3));
    EXPECT_EQ((largest_prime_factor(2049)), (683));
    EXPECT_EQ((largest_prime_factor(24)), (3));
    EXPECT_EQ((largest_prime_factor(-498)), (-498));
    EXPECT_EQ((largest_prime_factor(14)), (7));
    EXPECT_EQ((largest_prime_factor(2048)), (2));
    EXPECT_EQ((largest_prime_factor(842)), (421));
    EXPECT_EQ((largest_prime_factor(5)), (5));
    EXPECT_EQ((largest_prime_factor(315)), (7));
    EXPECT_EQ((largest_prime_factor(-7)), (-7));
    EXPECT_EQ((largest_prime_factor(26)), (13));
    EXPECT_EQ((largest_prime_factor(136)), (17));
    EXPECT_EQ((largest_prime_factor(-301)), (-301));
    EXPECT_EQ((largest_prime_factor(-2)), (-2));
    EXPECT_EQ((largest_prime_factor(28)), (7));
    EXPECT_EQ((largest_prime_factor(258)), (43));
    EXPECT_EQ((largest_prime_factor(-65)), (-65));
    EXPECT_EQ((largest_prime_factor(12)), (3));
    EXPECT_EQ((largest_prime_factor(-791)), (-791));
    EXPECT_EQ((largest_prime_factor(330)), (11));
    EXPECT_EQ((largest_prime_factor(669)), (223));
    EXPECT_EQ((largest_prime_factor(-264)), (-264));
}

TEST(Probe, sum_to_n_01) {
    EXPECT_EQ((sum_to_n(-579)), (167331));
    EXPECT_EQ((sum_to_n(-9)), (36));
    EXPECT_EQ((sum_to_n(-959)), (459361));
    EXPECT_EQ((sum_to_n(465)), (108345));
    EXPECT_EQ((sum_to_n(-921)), (423660));
    EXPECT_EQ((sum_to_n(8)), (36));
    EXPECT_EQ((sum_to_n(5048)), (12743676));
    EXPECT_EQ((sum_to_n(-5)), (10));
    EXPECT_EQ((sum_to_n(2)), (3));
    EXPECT_EQ((sum_to_n(-878)), (385003));
    EXPECT_EQ((sum_to_n(-406)), (82215));
    EXPECT_EQ((sum_to_n(55)), (1540));
    EXPECT_EQ((sum_to_n(173)), (15051));
    EXPECT_EQ((sum_to_n(6)), (21));
    EXPECT_EQ((sum_to_n(-255)), (32385));
    EXPECT_EQ((sum_to_n(11)), (66));
    EXPECT_EQ((sum_to_n(-591)), (174345));
    EXPECT_EQ((sum_to_n(-1)), (0));
    EXPECT_EQ((sum_to_n(-778)), (302253));
    EXPECT_EQ((sum_to_n(3)), (6));
    EXPECT_EQ((sum_to_n(19)), (190));
    EXPECT_EQ((sum_to_n(614)), (188805));
    EXPECT_EQ((sum_to_n(-2)), (1));
    EXPECT_EQ((sum_to_n(25)), (325));
    EXPECT_EQ((sum_to_n(-6)), (15));
}

TEST(Probe, sum_to_n_02) {
    EXPECT_EQ((sum_to_n(-244)), (29646));
    EXPECT_EQ((sum_to_n(22)), (253));
    EXPECT_EQ((sum_to_n(5049)), (12748725));
    EXPECT_EQ((sum_to_n(0)), (0));
    EXPECT_EQ((sum_to_n(-3)), (3));
    EXPECT_EQ((sum_to_n(623)), (194376));
    EXPECT_EQ((sum_to_n(905)), (409965));
    EXPECT_EQ((sum_to_n(14)), (105));
    EXPECT_EQ((sum_to_n(346)), (60031));
    EXPECT_EQ((sum_to_n(370)), (68635));
    EXPECT_EQ((sum_to_n(235)), (27730));
    EXPECT_EQ((sum_to_n(24)), (300));
    EXPECT_EQ((sum_to_n(13)), (91));
    EXPECT_EQ((sum_to_n(30)), (465));
    EXPECT_EQ((sum_to_n(100)), (5050));
    EXPECT_EQ((sum_to_n(10)), (55));
    EXPECT_EQ((sum_to_n(231)), (26796));
    EXPECT_EQ((sum_to_n(751)), (282376));
    EXPECT_EQ((sum_to_n(-629)), (197506));
    EXPECT_EQ((sum_to_n(-77)), (2926));
    EXPECT_EQ((sum_to_n(65)), (2145));
    EXPECT_EQ((sum_to_n(456)), (104196));
    EXPECT_EQ((sum_to_n(5051)), (12758826));
}

TEST(Probe, correct_bracketing_01) {
    EXPECT_EQ((correct_bracketing(std::string("GLfHOUfi"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("(()(()())()"))), (false));
    EXPECT_EQ((correct_bracketing(std::string(""))), (true));
    EXPECT_EQ((correct_bracketing(std::string("(()()))"))), (false));
    EXPECT_EQ((correct_bracketing(std::string(")"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("44f72D0rfDCK"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("()()((()()())())(()()(()))"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("(()R())"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("()()(()())())(()"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("aO("))), (false));
    EXPECT_EQ((correct_bracketing(std::string("1nbPk0PFCy"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("()()N()())()"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("()"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("g36)"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("(G()(()())()Q)(()"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("uAdNcYJY9lJL"))), (true));
    EXPECT_EQ((correct_bracketing(std::string(")c("))), (false));
    EXPECT_EQ((correct_bracketing(std::string("()()(()())()"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("raUfEJF7"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("()()(()())f)))()"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("7(()())"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("()()0(()())())i()"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("Jk0ToB"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("8e7b1xLVZ4k"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("((()())))"))), (false));
}

TEST(Probe, correct_bracketing_02) {
    EXPECT_EQ((correct_bracketing(std::string("G()"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("(J)"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("D"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("DvJq1r1a0r"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("5h2a8K"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("()()(()(()())(()()(()))"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("()()(()())()))()"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("16ZxhvuJgyUn"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("4 1HyX3"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("y"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("IO"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("grdtfTf2I"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("l(9())"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("(((("))), (false));
    EXPECT_EQ((correct_bracketing(std::string("((Z("))), (false));
    EXPECT_EQ((correct_bracketing(std::string("tQaDcr(u"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("((3e()())))"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("VSBbk"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("(()(m))"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("S"))), (true));
    EXPECT_EQ((correct_bracketing(std::string(")()(()())())(()"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("())n(()())("))), (false));
    EXPECT_EQ((correct_bracketing(std::string(")(()"))), (false));
}

TEST(Probe, derivative_01) {
    ExpectNearVec(derivative(std::vector<float >{10.3999996f, 9.99999975e-05f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 0.000199999995f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-11.8000002f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{0.900099993f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{11.5f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{0.300099999f, -12.0f, 4.0f}), std::vector<float >{-12.0f, 8.0f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{3.0f, -1.5f, 20.0f, 9.99999975e-05f, 12.0f, 9.99999975e-05f}), std::vector<float >{-1.5f, 40.0f, 0.000299999985f, 48.0f, 0.000499999966f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-8.80000019f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{17.2000008f, 9.99999975e-05f, 5.69999981f, 3.0f, -15.6999998f, 1.77999997f, 9.99999975e-05f, 12.5f}), std::vector<float >{9.99999975e-05f, 11.3999996f, 9.0f, -62.7999992f, 8.89999962f, 0.00059999997f, 87.5f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{9.99999975e-05f, 19.7999992f, 0.800100029f, 9.80000019f, 9.14999962f, 9.99999975e-05f, 9.99999975e-05f, 1.0f}), std::vector<float >{19.7999992f, 1.60020006f, 29.4000015f, 36.5999985f, 0.000499999966f, 0.00059999997f, 7.0f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{6.0f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{20.0f, 5.0f}), std::vector<float >{5.0f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{3.0f, 3.80999994f, 13.8999996f, 9.99999975e-05f, 9.99999975e-05f, 15.0f, 4.0f}), std::vector<float >{3.80999994f, 27.7999992f, 0.000299999985f, 0.00039999999f, 75.0f, 24.0f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-1.79990005f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{2.0f, 7.5999999f, 4.65999985f, 2.0000999f, 9.99999975e-05f}), std::vector<float >{7.5999999f, 9.31999969f, 6.00029945f, 0.00039999999f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{19.5f, 9.99999975e-05f, 9.80000019f}), std::vector<float >{9.99999975e-05f, 19.6000004f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{20.0f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{9.99999975e-05f, -1.69990003f}), std::vector<float >{-1.69990003f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{0.449999988f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{0.100100003f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{6.0f, -7.69999981f, 9.99999975e-05f}), std::vector<float >{-7.69999981f, 0.000199999995f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-2.70000005f, -1.70000005f, 5.46000004f, -14.0f, -13.1999998f}), std::vector<float >{-1.70000005f, 10.9200001f, -42.0f, -52.7999992f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-2.20000005f, 9.99999975e-05f, 2.0999999f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 4.19999981f, 0.000299999985f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-1.39999998f, 0.0f, -8.30000019f, 9.99999975e-05f}), std::vector<float >{0.0f, -16.6000004f, 0.000299999985f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{9.99999975e-05f, 5.76000023f, -3.0999999f, 1.0f, -5.69999981f, -1.89989996f, -1.79990005f, 9.99999975e-05f}), std::vector<float >{5.76000023f, -6.19999981f, 3.0f, -22.7999992f, -9.49950027f, -10.7994003f, 0.000699999975f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{16.0f, 12.0f, 9.99999975e-05f}), std::vector<float >{12.0f, 0.000199999995f}, 1e-5);
}

TEST(Probe, derivative_02) {
    ExpectNearVec(derivative(std::vector<float >{1.00010002f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{0.700100005f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{7.46000004f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{1.0f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{9.99999975e-05f, 20.0f, 15.1999998f, 9.99999975e-05f}), std::vector<float >{20.0f, 30.3999996f, 0.000299999985f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{2.0f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-6.5999999f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{7.80000019f, 9.99999975e-05f, -0.140000001f, 1.90009999f, 17.8999996f, 1.50010002f, 16.0f}), std::vector<float >{9.99999975e-05f, -0.280000001f, 5.70030022f, 71.5999985f, 7.5005002f, 96.0f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{3.05999994f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{1.80009997f, 9.80000019f, 9.99999975e-05f, 3.0f, 9.99999975e-05f, -11.1000004f, 9.99999975e-05f}), std::vector<float >{9.80000019f, 0.000199999995f, 9.0f, 0.00039999999f, -55.5f, 0.00059999997f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{1.60000002f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-13.6999998f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{19.7999992f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{2.0999999f, -7.51999998f, 9.99999975e-05f, 2.0f}), std::vector<float >{-7.51999998f, 0.000199999995f, 6.0f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-1.20000005f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-10.0f, 17.1000004f, 13.6999998f, 9.99999975e-05f, 20.0f}), std::vector<float >{17.1000004f, 27.3999996f, 0.000299999985f, 80.0f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-17.3999996f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-6.0999999f, 9.99999975e-05f, -11.6999998f, 9.99999975e-05f, 1.80009997f}), std::vector<float >{9.99999975e-05f, -23.3999996f, 0.000299999985f, 7.20039988f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{10.8000002f, -0.199900001f, 1.80009997f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, 5.0f, 0.300099999f}), std::vector<float >{-0.199900001f, 3.60019994f, 0.000299999985f, 0.00039999999f, 0.000499999966f, 30.0f, 2.1006999f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{9.99999975e-05f, -0.199900001f}), std::vector<float >{-0.199900001f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{20.0f, 0.700100005f, 20.0f, 9.99999975e-05f, 7.48000002f, 9.99999975e-05f}), std::vector<float >{0.700100005f, 40.0f, 0.000299999985f, 29.9200001f, 0.000499999966f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{9.99999975e-05f, 9.99999975e-05f, 4.0f, -12.3999996f, 1.95000005f, 9.99999975e-05f, -19.8999996f}), std::vector<float >{9.99999975e-05f, 8.0f, -37.1999969f, 7.80000019f, 0.000499999966f, -119.399994f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{20.0f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, -19.7000008f, 9.99999975e-05f, -0.499900013f}), std::vector<float >{9.99999975e-05f, 0.000199999995f, 0.000299999985f, 0.00039999999f, -98.5f, 0.00059999997f, -3.4993f}, 1e-5);
}

TEST(Probe, fibfib_01) {
    EXPECT_EQ((fibfib(6)), (7));
    EXPECT_EQ((fibfib(5)), (4));
    EXPECT_EQ((fibfib(27)), (2555757));
    EXPECT_EQ((fibfib(1)), (0));
    EXPECT_EQ((fibfib(24)), (410744));
    EXPECT_EQ((fibfib(9)), (44));
    EXPECT_EQ((fibfib(19)), (19513));
    EXPECT_EQ((fibfib(17)), (5768));
    EXPECT_EQ((fibfib(11)), (149));
    EXPECT_EQ((fibfib(13)), (504));
    EXPECT_EQ((fibfib(29)), (8646064));
    EXPECT_EQ((fibfib(21)), (66012));
    EXPECT_EQ((fibfib(20)), (35890));
    EXPECT_EQ((fibfib(22)), (121415));
    EXPECT_EQ((fibfib(10)), (81));
    EXPECT_EQ((fibfib(15)), (1705));
    EXPECT_EQ((fibfib(35)), (334745777));
    EXPECT_EQ((fibfib(26)), (1389537));
    EXPECT_EQ((fibfib(28)), (4700770));
    EXPECT_EQ((fibfib(30)), (15902591));
}

TEST(Probe, vowels_count_01) {
    EXPECT_EQ((vowels_count(std::string("key"))), (2));
    EXPECT_EQ((vowels_count(std::string("bY3e"))), (1));
    EXPECT_EQ((vowels_count(std::string("abcde"))), (2));
    EXPECT_EQ((vowels_count(std::string("ACxDY"))), (2));
    EXPECT_EQ((vowels_count(std::string("be"))), (1));
    EXPECT_EQ((vowels_count(std::string("I0abtcde"))), (3));
    EXPECT_EQ((vowels_count(std::string("by n"))), (0));
    EXPECT_EQ((vowels_count(std::string("bYe"))), (1));
    EXPECT_EQ((vowels_count(std::string("acde"))), (2));
    EXPECT_EQ((vowels_count(std::string("zZHo"))), (1));
    EXPECT_EQ((vowels_count(std::string("6SbYGe"))), (1));
    EXPECT_EQ((vowels_count(std::string("Ust9T7n6"))), (1));
    EXPECT_EQ((vowels_count(std::string("ke"))), (1));
    EXPECT_EQ((vowels_count(std::string("2abcde"))), (2));
    EXPECT_EQ((vowels_count(std::string("vkey"))), (2));
    EXPECT_EQ((vowels_count(std::string("bY"))), (1));
    EXPECT_EQ((vowels_count(std::string("bYws"))), (0));
    EXPECT_EQ((vowels_count(std::string("kJa"))), (1));
    EXPECT_EQ((vowels_count(std::string("lsk"))), (0));
    EXPECT_EQ((vowels_count(std::string("E"))), (1));
    EXPECT_EQ((vowels_count(std::string("o3TQbRZ"))), (1));
    EXPECT_EQ((vowels_count(std::string("abc9e"))), (2));
    EXPECT_EQ((vowels_count(std::string("AlonX"))), (2));
    EXPECT_EQ((vowels_count(std::string("jAloq"))), (2));
    EXPECT_EQ((vowels_count(std::string("7R"))), (0));
}

TEST(Probe, vowels_count_02) {
    EXPECT_EQ((vowels_count(std::string("QqQpq"))), (0));
    EXPECT_EQ((vowels_count(std::string("ACED"))), (2));
    EXPECT_EQ((vowels_count(std::string("abdO"))), (2));
    EXPECT_EQ((vowels_count(std::string("Aklone"))), (3));
    EXPECT_EQ((vowels_count(std::string("nye"))), (1));
    EXPECT_EQ((vowels_count(std::string("Yfpi5lF4EZej"))), (3));
    EXPECT_EQ((vowels_count(std::string("eY"))), (2));
    EXPECT_EQ((vowels_count(std::string("keBy"))), (2));
    EXPECT_EQ((vowels_count(std::string("Alonm"))), (2));
    EXPECT_EQ((vowels_count(std::string("OzFBwFg7e5A"))), (3));
    EXPECT_EQ((vowels_count(std::string("vNqe"))), (1));
    EXPECT_EQ((vowels_count(std::string("ye"))), (1));
    EXPECT_EQ((vowels_count(std::string("AWonq"))), (2));
    EXPECT_EQ((vowels_count(std::string("pDPqHd4mwUA5"))), (2));
    EXPECT_EQ((vowels_count(std::string("bcde"))), (1));
    EXPECT_EQ((vowels_count(std::string("bAYp"))), (1));
    EXPECT_EQ((vowels_count(std::string("3cKPDZl"))), (0));
    EXPECT_EQ((vowels_count(std::string("0key"))), (2));
    EXPECT_EQ((vowels_count(std::string("U"))), (1));
    EXPECT_EQ((vowels_count(std::string("2kFYP3"))), (0));
    EXPECT_EQ((vowels_count(std::string("ktM28TcX3Xp5"))), (0));
    EXPECT_EQ((vowels_count(std::string("yv"))), (0));
    EXPECT_EQ((vowels_count(std::string("2jau655v"))), (2));
}
