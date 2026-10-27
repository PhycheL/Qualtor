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

TEST(Characterization, monotonic_01) {
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 2.0f, 4.0f, 20.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{10.0f, 3.0f, -18.5f, 7.4000001f, 7.5999999f, 20.0f, -13.3999996f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 1.0f, 0.0f, 1.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{-6.01999998f, 0.0f, 4.0f, -0.170000002f, -10.8000002f, 15.3999996f, 0.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{10.6000004f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{-4.44000006f, 5.0f, 2.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 3.0f, 2.0f, 5.0f, 60.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{1.0f, 20.0f, 4.0f, 10.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, -17.3999996f, 0.0f, -10.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{-2.5f, -10.0f, 20.0f, 4.0f})), (false));
    EXPECT_EQ((monotonic(std::vector<float >{0.0f})), (true));
    EXPECT_EQ((monotonic(std::vector<float >{4.0f, 1.0f, 1.0f, 0.0f})), (true));
}

TEST(Characterization, common_01) {
    EXPECT_EQ((common(std::vector<int >{2, 3, 5, 8}, std::vector<int >{-8, 0, 1, -272})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 5, 653}, std::vector<int >{5, 3, 2, 8, 3})), (std::vector<int >{5}));
    EXPECT_EQ((common(std::vector<int >{}, std::vector<int >{1, 5, 275})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{2, -10, -8, -4, 28}, std::vector<int >{0, 28, 10, 34, 9})), (std::vector<int >{28}));
    EXPECT_EQ((common(std::vector<int >{212, 28}, std::vector<int >{5, 7, 1, 5, 653, 121})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{-2, 28}, std::vector<int >{10, 3})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{3, 2}, std::vector<int >{5, 3, 2})), (std::vector<int >{2, 3}));
    EXPECT_EQ((common(std::vector<int >{}, std::vector<int >{1, 5})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{190, 533, -5, 4, 25, 17, 123}, std::vector<int >{3, 2, 34})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{5, 3, 2, 8}, std::vector<int >{5, 7, 1, 5, 9, 653, 121})), (std::vector<int >{5}));
    EXPECT_EQ((common(std::vector<int >{4}, std::vector<int >{5, 7, 5, 9, 653, 121})), (std::vector<int >{}));
    EXPECT_EQ((common(std::vector<int >{1, 4, 3, 34, 653, 2, 5}, std::vector<int >{7, -5, 29, -990})), (std::vector<int >{}));
}

TEST(Characterization, largest_prime_factor_01) {
    EXPECT_EQ((largest_prime_factor(1)), (1));
    EXPECT_EQ((largest_prime_factor(27)), (3));
    EXPECT_EQ((largest_prime_factor(571)), (571));
    EXPECT_EQ((largest_prime_factor(7)), (7));
    EXPECT_EQ((largest_prime_factor(6)), (3));
    EXPECT_EQ((largest_prime_factor(-3)), (-3));
    EXPECT_EQ((largest_prime_factor(0)), (0));
    EXPECT_EQ((largest_prime_factor(4)), (2));
    EXPECT_EQ((largest_prime_factor(61)), (61));
    EXPECT_EQ((largest_prime_factor(15)), (5));
    EXPECT_EQ((largest_prime_factor(2)), (2));
    EXPECT_EQ((largest_prime_factor(20)), (5));
}

TEST(Characterization, sum_to_n_01) {
    EXPECT_EQ((sum_to_n(7)), (28));
    EXPECT_EQ((sum_to_n(21)), (231));
    EXPECT_EQ((sum_to_n(-4)), (6));
    EXPECT_EQ((sum_to_n(5)), (15));
    EXPECT_EQ((sum_to_n(66)), (2211));
    EXPECT_EQ((sum_to_n(12)), (78));
    EXPECT_EQ((sum_to_n(1000)), (500500));
    EXPECT_EQ((sum_to_n(20)), (210));
    EXPECT_EQ((sum_to_n(1)), (1));
    EXPECT_EQ((sum_to_n(-102)), (5151));
    EXPECT_EQ((sum_to_n(551)), (152076));
    EXPECT_EQ((sum_to_n(26)), (351));
}

TEST(Characterization, correct_bracketing_01) {
    EXPECT_EQ((correct_bracketing(std::string("1uSgSeTNe0"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("D4u"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("K6nbsIxX)"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("BJTj(jv"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("(()())"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("((("))), (false));
    EXPECT_EQ((correct_bracketing(std::string("((e)"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("jiq1TuRq7"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("(()"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("("))), (false));
    EXPECT_EQ((correct_bracketing(std::string("g("))), (false));
    EXPECT_EQ((correct_bracketing(std::string("HlLp8PMcNS0p"))), (true));
}

TEST(Characterization, derivative_01) {
    ExpectNearVec(derivative(std::vector<float >{9.99999975e-05f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{6.0f, -3.99000001f, 9.99999975e-05f}), std::vector<float >{-3.99000001f, 0.000199999995f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{0.0f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-1.89989996f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{9.99999975e-05f, 2.0000999f, 9.99999975e-05f, 9.99999975e-05f, -18.2999992f, 6.0f, -1.09990001f, 9.99999975e-05f}), std::vector<float >{2.0000999f, 0.000199999995f, 0.000299999985f, -73.1999969f, 30.0f, -6.59940004f, 0.000699999975f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{9.60000038f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-13.1999998f, 6.71000004f, 1.79999995f, 9.99999975e-05f, -8.14999962f, 9.99999975e-05f, -2.5f, 0.400099993f}), std::vector<float >{6.71000004f, 3.5999999f, 0.000299999985f, -32.5999985f, 0.000499999966f, -15.0f, 2.80069995f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{9.99999975e-05f, 16.8999996f}), std::vector<float >{16.8999996f}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{5.0f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-9.39999962f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(derivative(std::vector<float >{-0.0998999998f, 14.3999996f}), std::vector<float >{14.3999996f}, 1e-5);
}

TEST(Characterization, fibfib_01) {
    EXPECT_EQ((fibfib(8)), (24));
    EXPECT_EQ((fibfib(4)), (2));
    EXPECT_EQ((fibfib(16)), (3136));
    EXPECT_EQ((fibfib(3)), (1));
    EXPECT_EQ((fibfib(14)), (927));
    EXPECT_EQ((fibfib(12)), (274));
    EXPECT_EQ((fibfib(0)), (0));
    EXPECT_EQ((fibfib(23)), (223317));
    EXPECT_EQ((fibfib(7)), (13));
    EXPECT_EQ((fibfib(25)), (755476));
    EXPECT_EQ((fibfib(18)), (10609));
    EXPECT_EQ((fibfib(2)), (1));
}

TEST(Characterization, vowels_count_01) {
    EXPECT_EQ((vowels_count(std::string("u"))), (1));
    EXPECT_EQ((vowels_count(std::string("q"))), (0));
    EXPECT_EQ((vowels_count(std::string("Alone"))), (3));
    EXPECT_EQ((vowels_count(std::string("bye"))), (1));
    EXPECT_EQ((vowels_count(std::string("eye"))), (2));
    EXPECT_EQ((vowels_count(std::string("o"))), (1));
    EXPECT_EQ((vowels_count(std::string("kleY"))), (2));
    EXPECT_EQ((vowels_count(std::string("Ic3MCh0j"))), (1));
    EXPECT_EQ((vowels_count(std::string("ACEDY"))), (3));
    EXPECT_EQ((vowels_count(std::string("keY"))), (2));
    EXPECT_EQ((vowels_count(std::string("koem"))), (2));
    EXPECT_EQ((vowels_count(std::string("Ny1oAh9bXH"))), (2));
}
