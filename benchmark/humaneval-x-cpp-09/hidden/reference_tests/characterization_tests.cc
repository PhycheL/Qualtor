// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_09.h"

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

TEST(Characterization, circular_shift_01) {
    EXPECT_EQ((circular_shift(12, 26)), (std::string("21")));
    EXPECT_EQ((circular_shift(29, 101)), (std::string("92")));
    EXPECT_EQ((circular_shift(28, 4)), (std::string("82")));
    EXPECT_EQ((circular_shift(903, 12)), (std::string("309")));
    EXPECT_EQ((circular_shift(-1, 8)), (std::string("1-")));
    EXPECT_EQ((circular_shift(77, 23)), (std::string("77")));
    EXPECT_EQ((circular_shift(29, 8)), (std::string("92")));
    EXPECT_EQ((circular_shift(544, 1)), (std::string("454")));
    EXPECT_EQ((circular_shift(95, 1)), (std::string("59")));
    EXPECT_EQ((circular_shift(77, 27)), (std::string("77")));
    EXPECT_EQ((circular_shift(19, 79)), (std::string("91")));
    EXPECT_EQ((circular_shift(8, 4)), (std::string("8")));
}

TEST(Characterization, digitSum_01) {
    EXPECT_EQ((digitSum(std::string("Yod arE Vry Smart"))), (327));
    EXPECT_EQ((digitSum(std::string("JbeB"))), (140));
    EXPECT_EQ((digitSum(std::string("abAP"))), (145));
    EXPECT_EQ((digitSum(std::string("abAB"))), (131));
    EXPECT_EQ((digitSum(std::string("DPM1b0"))), (225));
    EXPECT_EQ((digitSum(std::string("\?hellUo"))), (85));
    EXPECT_EQ((digitSum(std::string("tueKxA\?gCWBv"))), (360));
    EXPECT_EQ((digitSum(std::string("helloE"))), (69));
    EXPECT_EQ((digitSum(std::string("YwBwC"))), (222));
    EXPECT_EQ((digitSum(std::string("ht9m1"))), (0));
    EXPECT_EQ((digitSum(std::string("7nPyh8"))), (80));
    EXPECT_EQ((digitSum(std::string(" How are ytu\?"))), (72));
}

TEST(Characterization, fruit_distribution_01) {
    EXPECT_EQ((fruit_distribution(std::string(""), 2)), (2));
    EXPECT_EQ((fruit_distribution(std::string("wtEc"), 120)), (120));
    EXPECT_EQ((fruit_distribution(std::string("1 aBpples and 100 o3ranges"), 5)), (-999));
    EXPECT_EQ((fruit_distribution(std::string("1 apples and 0 oranges"), 2)), (1));
    EXPECT_EQ((fruit_distribution(std::string("10 apples and 1 orangPs"), -5)), (-16));
    EXPECT_EQ((fruit_distribution(std::string("1 apples and 100 oranges"), 1)), (-100));
    EXPECT_EQ((fruit_distribution(std::string("10 VppJles and 1 oranges"), 0)), (-11));
    EXPECT_EQ((fruit_distribution(std::string("5 applefs and 6 Boranes"), -5)), (-16));
    EXPECT_EQ((fruit_distribution(std::string("1 apples and 100 oranges"), -2)), (-103));
    EXPECT_EQ((fruit_distribution(std::string("5 apples and 6J oranges"), -1)), (-12));
    EXPECT_EQ((fruit_distribution(std::string("H ci wExwZ"), -3)), (-3));
    EXPECT_EQ((fruit_distribution(std::string("5 apples and 6 oranges"), 0)), (-11));
}

TEST(Characterization, pluck_01) {
    EXPECT_EQ((pluck(std::vector<int >{0, 1})), (std::vector<int >{0, 0}));
    EXPECT_EQ((pluck(std::vector<int >{4, 1})), (std::vector<int >{4, 0}));
    EXPECT_EQ((pluck(std::vector<int >{15, 1})), (std::vector<int >{}));
    EXPECT_EQ((pluck(std::vector<int >{2, 12, 1000})), (std::vector<int >{2, 0}));
    EXPECT_EQ((pluck(std::vector<int >{7, 9, 7, 1})), (std::vector<int >{}));
    EXPECT_EQ((pluck(std::vector<int >{5, 4, 8, 4, 8})), (std::vector<int >{4, 1}));
    EXPECT_EQ((pluck(std::vector<int >{0, 1, -221})), (std::vector<int >{0, 0}));
    EXPECT_EQ((pluck(std::vector<int >{26, 2, 3})), (std::vector<int >{2, 1}));
    EXPECT_EQ((pluck(std::vector<int >{5, 0, 3, 0, 4, 2})), (std::vector<int >{0, 1}));
    EXPECT_EQ((pluck(std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((pluck(std::vector<int >{3, 28, 9, -921, -4})), (std::vector<int >{-4, 4}));
    EXPECT_EQ((pluck(std::vector<int >{7, 6, 1, 7})), (std::vector<int >{6, 1}));
}

TEST(Characterization, search_01) {
    EXPECT_EQ((search(std::vector<int >{3, 6, 8})), (-1));
    EXPECT_EQ((search(std::vector<int >{3, 3, 27})), (-1));
    EXPECT_EQ((search(std::vector<int >{1, 6, 10, 1, 6, 9, 10, 8, 6, 8, 7, 3})), (1));
    EXPECT_EQ((search(std::vector<int >{1})), (1));
    EXPECT_EQ((search(std::vector<int >{})), (-1));
    EXPECT_EQ((search(std::vector<int >{22, 679})), (-1));
    EXPECT_EQ((search(std::vector<int >{2, 6, 4, 2, 8, 7, 5, 6, 4, 10, 4, 6, 3, 7, 8, 8, 3, 1, 4, 2, 2, 10, 7})), (4));
    EXPECT_EQ((search(std::vector<int >{8})), (-1));
    EXPECT_EQ((search(std::vector<int >{15, 25, 960, 22, 30})), (-1));
    EXPECT_EQ((search(std::vector<int >{-412, -9, 24})), (-1));
    EXPECT_EQ((search(std::vector<int >{3, 2, 8, 2, 10})), (2));
    EXPECT_EQ((search(std::vector<int >{5, 4, 10, 2, 1, 1, 10, 3, 6, 1, 8, 1000})), (1));
}

TEST(Characterization, strange_sort_list_01) {
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 5, 2, 4, 3})), (std::vector<int >{2, 5, 3, 5, 4}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 9, 6, 8, 7})), (std::vector<int >{5, 9, 6, 8, 7}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 507, 6, 7})), (std::vector<int >{5, 507, 6, 7}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 4, 3, 2, 5})), (std::vector<int >{1, 5, 2, 4, 3}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 1, 0, 3, 1, -6, 10, 6})), (std::vector<int >{-6, 10, 0, 6, 1, 5, 1, 3}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 6, 7, 8, 9})), (std::vector<int >{5, 9, 6, 8, 7}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{15, 671, 1, 1, 2, 9, -656, 1})), (std::vector<int >{-656, 671, 1, 15, 1, 9, 1, 2}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 5, 5, 5})), (std::vector<int >{5, 5, 5, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{0, 25})), (std::vector<int >{0, 25}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{30})), (std::vector<int >{30}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{-5, 5, -5, 5, 0, 2, 2, 2, 11})), (std::vector<int >{-5, 11, -5, 5, 0, 5, 2, 2, 2}));
}

TEST(Characterization, triangle_area_01) {
    ExpectNearScalar(triangle_area(1.10000002f, 4.0f, -6.5f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(10.6999998f, 16.25f, 19.7999992f), 86.8720932f, 1e-5);
    ExpectNearScalar(triangle_area(7.19999981f, -9.55000019f, -0.129999995f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-18.5f, 16.25f, -5.19999981f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-0.730000019f, 15.6999998f, 16.25f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(3.0f, 15.0f, -7.0999999f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-5.30000019f, 19.0f, -6.69999981f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(7.9000001f, 16.25f, 19.8999996f), 61.7884979f, 1e-5);
    ExpectNearScalar(triangle_area(0.00999999978f, 2.5999999f, 9.80000019f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-0.430000007f, 3.20000005f, -2.42000008f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(17.4500008f, 13.6999998f, -7.92999983f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-18.8999996f, -1.73000002f, 5.92000008f), -1.0f, 1e-5);
}

TEST(Characterization, will_it_fly_01) {
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 966, 3, 9, 9}, 22)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 2, 3, -1}, -779)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{}, 15)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 3, 2}, 1)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3}, 6)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 19, 9, 422}, 3)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3}, -87)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{-4}, 9)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{9, 1, 717, -2, 1}, 27)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{30, -2, 11, 11, 1, 1, 23}, -9)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2, 3}, -5)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{5}, 16)), (true));
}
