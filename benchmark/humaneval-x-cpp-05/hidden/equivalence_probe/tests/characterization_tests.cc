// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_05.h"

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

TEST(Characterization, sort_third_01) {
    EXPECT_EQ((sort_third(std::vector<int >{1, 2, 3})), (std::vector<int >{1, 2, 3}));
    EXPECT_EQ((sort_third(std::vector<int >{11, -238, 26, 99999, -5, 4, -1})), (std::vector<int >{-1, -238, 26, 11, -5, 4, 99999}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 6, 3, 4, 8, 9, 2, 99999})), (std::vector<int >{2, 6, 3, 4, 8, 9, 5, 99999}));
    EXPECT_EQ((sort_third(std::vector<int >{5, 8, 3, 4, 6, 9, 2})), (std::vector<int >{2, 8, 3, 4, 6, 9, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 3, 4, 8, 9, 5})), (std::vector<int >{2, 6, 3, 4, 8, 9, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{1, 544, -10, 4, 9})), (std::vector<int >{1, 544, -10, 4, 9}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 3, 4, 8, 3, 5})), (std::vector<int >{2, 6, 3, 4, 8, 3, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 6, 9, 4, 8, 3, 5})), (std::vector<int >{2, 6, 9, 4, 8, 3, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{2, 4, 9, 4, 8, 3, 5})), (std::vector<int >{2, 4, 9, 4, 8, 3, 5}));
    EXPECT_EQ((sort_third(std::vector<int >{19, 10, 8, 21})), (std::vector<int >{19, 10, 8, 21}));
    EXPECT_EQ((sort_third(std::vector<int >{-12, 6, -116, 5, -10, 3, 11, -1})), (std::vector<int >{-12, 6, -116, 5, -10, 3, 11, -1}));
    EXPECT_EQ((sort_third(std::vector<int >{})), (std::vector<int >{}));
}

TEST(Characterization, unique_01) {
    EXPECT_EQ((unique(std::vector<int >{0, 2, 9, 5, 3, 123})), (std::vector<int >{0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{-8, 0, 1, -272})), (std::vector<int >{-272, -8, 0, 1}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 0, 123})), (std::vector<int >{0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 3, 5, 9, 123, 2})), (std::vector<int >{0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 3, 5, 9, 123})), (std::vector<int >{0, 2, 3, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 0, 275})), (std::vector<int >{0, 2, 3, 5, 9, 275}));
    EXPECT_EQ((unique(std::vector<int >{123, -10, -8, -4, 28})), (std::vector<int >{-10, -8, -4, 28, 123}));
    EXPECT_EQ((unique(std::vector<int >{123, 28, 3, 9, 2})), (std::vector<int >{2, 3, 9, 28, 123}));
    EXPECT_EQ((unique(std::vector<int >{212, 28})), (std::vector<int >{28, 212}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 5, 9, 123})), (std::vector<int >{0, 2, 5, 9, 123}));
    EXPECT_EQ((unique(std::vector<int >{121, 28})), (std::vector<int >{28, 121}));
    EXPECT_EQ((unique(std::vector<int >{0, 2, 3, 9, 123})), (std::vector<int >{0, 2, 3, 9, 123}));
}

TEST(Characterization, max_element_01) {
    ExpectNearScalar(max_element(std::vector<float >{9.99999975e-05f}), 9.99999975e-05f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-12.3999996f, -10.0f, -1.29990005f, -10.3000002f, 17.3999996f, -12.1000004f, -1.89989996f, 0.400099993f}), 17.3999996f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 124.0f, 1.0f, -10.0f}), 124.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-1.35000002f, 9.99999975e-05f, 4.19999981f, 5.19999981f, -13.0f}), 5.19999981f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 123.0f, 1.0f, -10.0f}), 123.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{5.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 9.0f, 0.0f, 123.0f, 1.0f, -10.0f, -19.0f}), 123.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.0f, 2.0f, 3.0f}), 3.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-3.0f, -4.0999999f, 1.0f, 3.0f, 15.0f, 9.99999975e-05f, 3.79999995f, 5.80000019f}), 15.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{0.400099993f, 0.219999999f, -1.89989996f, -5.9000001f}), 0.400099993f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{-5.51000023f, -2.5f, 1.0f, -7.19999981f, 5.69999981f, -1.69990003f, -7.0999999f, 7.19999981f}), 7.19999981f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{}), -10000.0f, 1e-5);
    ExpectNearScalar(max_element(std::vector<float >{1.20009995f, 15.3999996f, -7.19999981f, -5.5f}), 15.3999996f, 1e-5);
}

TEST(Characterization, fizz_buzz_01) {
    EXPECT_EQ((fizz_buzz(4)), (0));
    EXPECT_EQ((fizz_buzz(21)), (0));
    EXPECT_EQ((fizz_buzz(-4)), (0));
    EXPECT_EQ((fizz_buzz(50)), (0));
    EXPECT_EQ((fizz_buzz(192)), (6));
    EXPECT_EQ((fizz_buzz(12)), (0));
    EXPECT_EQ((fizz_buzz(1000)), (47));
    EXPECT_EQ((fizz_buzz(4000)), (192));
    EXPECT_EQ((fizz_buzz(20)), (0));
    EXPECT_EQ((fizz_buzz(1)), (0));
    EXPECT_EQ((fizz_buzz(-102)), (0));
    EXPECT_EQ((fizz_buzz(551)), (17));
}

TEST(Characterization, sort_even_01) {
    ExpectNearVec(sort_even(std::vector<float >{6.0999999f, 9.99999975e-05f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 9.99999975e-05f, 6.0999999f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 8.0f, -12.0f, 4.0f, 23.0f, 2.0f, 3.0f, 11.0f, 12.0f, -10.0f, 5.0f}), std::vector<float >{-12.0f, 8.0f, 3.0f, 4.0f, 5.0f, 2.0f, 5.0f, 11.0f, 12.0f, -10.0f, 23.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f}), std::vector<float >{-10.0f, 3.0f, -5.0f, 2.0f, -3.0f, 3.0f, 5.0f, 0.0f, 9.0f, 1.0f, 123.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-1.09990001f}), std::vector<float >{-1.09990001f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{}), std::vector<float >{}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{2.0f, 6.9000001f}), std::vector<float >{2.0f, 6.9000001f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{-12.0f, 8.0f, 3.0f, 4.0f, 5.0f, 2.0f, 12.0f, 11.0f, 23.0f, -10.0f}), std::vector<float >{-12.0f, 8.0f, 3.0f, 4.0f, 5.0f, 2.0f, 12.0f, 11.0f, 23.0f, -10.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{9.99999975e-05f}), std::vector<float >{9.99999975e-05f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{5.0f, 6.0f, 3.0f, 4.0f}), std::vector<float >{3.0f, 6.0f, 5.0f, 4.0f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{8.0f, 11.1000004f, 9.60000038f, -19.2000008f, 12.3000002f}), std::vector<float >{8.0f, 11.1000004f, 9.60000038f, -19.2000008f, 12.3000002f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{9.19999981f, 9.60000038f, -15.3000002f}), std::vector<float >{-15.3000002f, 9.60000038f, 9.19999981f}, 1e-5);
    ExpectNearVec(sort_even(std::vector<float >{3.0f, 6.0f, 5.0f, 4.0f, -1.49989998f}), std::vector<float >{-1.49989998f, 6.0f, 3.0f, 4.0f, 5.0f}, 1e-5);
}

TEST(Characterization, encode_cyclic_01) {
    EXPECT_EQ((encode_cyclic(std::string("z"))), (std::string("z")));
    EXPECT_EQ((encode_cyclic(std::string("EPp6OGvn"))), (std::string("PpEOG6vn")));
    EXPECT_EQ((encode_cyclic(std::string("l f3nt"))), (std::string(" flnt3")));
    EXPECT_EQ((encode_cyclic(std::string(""))), (std::string("")));
    EXPECT_EQ((encode_cyclic(std::string("X"))), (std::string("X")));
    EXPECT_EQ((encode_cyclic(std::string("K"))), (std::string("K")));
    EXPECT_EQ((encode_cyclic(std::string("cOouagz5RU1"))), (std::string("Oocagu5RzU1")));
    EXPECT_EQ((encode_cyclic(std::string("nH"))), (std::string("nH")));
    EXPECT_EQ((encode_cyclic(std::string("M 5"))), (std::string(" 5M")));
    EXPECT_EQ((encode_cyclic(std::string("G3f3gZv2GD"))), (std::string("3fGgZ32GvD")));
    EXPECT_EQ((encode_cyclic(std::string("R"))), (std::string("R")));
    EXPECT_EQ((encode_cyclic(std::string("MnmTDjAYG"))), (std::string("nmMDjTYGA")));
}

TEST(Characterization, decode_cyclic_01) {
    EXPECT_EQ((decode_cyclic(std::string("ygdY"))), (std::string("dygY")));
    EXPECT_EQ((decode_cyclic(std::string(""))), (std::string("")));
    EXPECT_EQ((decode_cyclic(std::string("7fsRi1ZC"))), (std::string("s7f1RiZC")));
    EXPECT_EQ((decode_cyclic(std::string("stuO0GVK0wR"))), (std::string("ustGO00VKwR")));
    EXPECT_EQ((decode_cyclic(std::string("JY"))), (std::string("JY")));
    EXPECT_EQ((decode_cyclic(std::string("A"))), (std::string("A")));
    EXPECT_EQ((decode_cyclic(std::string("IaUrYD"))), (std::string("UIaDrY")));
    EXPECT_EQ((decode_cyclic(std::string("hp2lijAr"))), (std::string("2hpjliAr")));
    EXPECT_EQ((decode_cyclic(std::string("36PTn9qLnbS"))), (std::string("P369TnnqLbS")));
    EXPECT_EQ((decode_cyclic(std::string("G4Hv77vTZ"))), (std::string("HG47v7ZvT")));
    EXPECT_EQ((decode_cyclic(std::string("m"))), (std::string("m")));
    EXPECT_EQ((decode_cyclic(std::string("y"))), (std::string("y")));
}

TEST(Characterization, prime_fib_01) {
    EXPECT_EQ((prime_fib(1)), (2));
    EXPECT_EQ((prime_fib(5)), (89));
    EXPECT_EQ((prime_fib(9)), (514229));
    EXPECT_EQ((prime_fib(7)), (1597));
    EXPECT_EQ((prime_fib(8)), (28657));
    EXPECT_EQ((prime_fib(3)), (5));
    EXPECT_EQ((prime_fib(4)), (13));
    EXPECT_EQ((prime_fib(10)), (433494437));
    EXPECT_EQ((prime_fib(2)), (3));
    EXPECT_EQ((prime_fib(6)), (233));
}

TEST(Characterization, triples_sum_to_zero_01) {
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{28, 29, 26, 1, 27, 0, -688, -1})), (true));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{-98, 1, 2, 5})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, -100})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{-2, 10, 21})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 2, 3, 7, 9})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{11, 1, 14, 9, 2, 713, 11})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{2, -745, 5, -895, -9, -602, 19})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 2, 5, 7, 0})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, 5, 0})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 899, 5, -1})), (false));
    EXPECT_EQ((triples_sum_to_zero(std::vector<int >{1, 3, 0, 5})), (false));
}
