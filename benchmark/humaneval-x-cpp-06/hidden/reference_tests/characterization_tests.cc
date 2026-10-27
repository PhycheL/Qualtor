// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_06.h"

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

TEST(Characterization, car_race_collision_01) {
    EXPECT_EQ((car_race_collision(8)), (64));
    EXPECT_EQ((car_race_collision(26)), (676));
    EXPECT_EQ((car_race_collision(29)), (841));
    EXPECT_EQ((car_race_collision(28)), (784));
    EXPECT_EQ((car_race_collision(4)), (16));
    EXPECT_EQ((car_race_collision(903)), (815409));
    EXPECT_EQ((car_race_collision(-1)), (1));
    EXPECT_EQ((car_race_collision(23)), (529));
    EXPECT_EQ((car_race_collision(100)), (10000));
    EXPECT_EQ((car_race_collision(544)), (295936));
    EXPECT_EQ((car_race_collision(2)), (4));
    EXPECT_EQ((car_race_collision(98)), (9604));
}

TEST(Characterization, incr_list_01) {
    EXPECT_EQ((incr_list(std::vector<int >{5, 3, 3, 2, 5, 3, 9, 0, 123})), (std::vector<int >{6, 4, 4, 3, 6, 4, 10, 1, 124}));
    EXPECT_EQ((incr_list(std::vector<int >{-8, 0, 1, -272})), (std::vector<int >{-7, 1, 2, -271}));
    EXPECT_EQ((incr_list(std::vector<int >{1, 2, 3})), (std::vector<int >{2, 3, 4}));
    EXPECT_EQ((incr_list(std::vector<int >{1, 2, 3, 6})), (std::vector<int >{2, 3, 4, 7}));
    EXPECT_EQ((incr_list(std::vector<int >{275})), (std::vector<int >{276}));
    EXPECT_EQ((incr_list(std::vector<int >{4, 5, -10, -8})), (std::vector<int >{5, 6, -9, -7}));
    EXPECT_EQ((incr_list(std::vector<int >{3, 4})), (std::vector<int >{4, 5}));
    EXPECT_EQ((incr_list(std::vector<int >{0, 28, 6, 0, 2})), (std::vector<int >{1, 29, 7, 1, 3}));
    EXPECT_EQ((incr_list(std::vector<int >{212, 28})), (std::vector<int >{213, 29}));
    EXPECT_EQ((incr_list(std::vector<int >{4, 3})), (std::vector<int >{5, 4}));
    EXPECT_EQ((incr_list(std::vector<int >{8, 28})), (std::vector<int >{9, 29}));
    EXPECT_EQ((incr_list(std::vector<int >{6, 4, 6, 3, 4, 4, 10, 1, 7})), (std::vector<int >{7, 5, 7, 4, 5, 5, 11, 2, 8}));
}

TEST(Characterization, pairs_sum_to_zero_01) {
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-2})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{7, 6, 30, -3, 27, 0, 33, 1})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 2, 3, 7})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{12345, 31, 5, 24, 27})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 4, 2, 30})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 4, 2, 30, 10})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 7, 3, 2})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 3, 2, 31})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-10, 9, 12, 24, 11, 4, 10, -5})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 3, 2, 30})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 100, 29, 179})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{99999, 13, 11, 17, -3, 29, 22, -8})), (false));
}

TEST(Characterization, change_base_01) {
    EXPECT_EQ((change_base(4, 21)), (std::string("4")));
    EXPECT_EQ((change_base(-4, 10000)), (std::string("")));
    EXPECT_EQ((change_base(22, 12)), (std::string("110")));
    EXPECT_EQ((change_base(1000, 7)), (std::string("2626")));
    EXPECT_EQ((change_base(-102, 551)), (std::string("")));
    EXPECT_EQ((change_base(26, 3)), (std::string("222")));
    EXPECT_EQ((change_base(11101010, -579)), (std::string("422")));
    EXPECT_EQ((change_base(-9, -959)), (std::string("")));
    EXPECT_EQ((change_base(234, 7)), (std::string("453")));
    EXPECT_EQ((change_base(-921, -4)), (std::string("")));
    EXPECT_EQ((change_base(-5, -4)), (std::string("")));
    EXPECT_EQ((change_base(2, -878)), (std::string("2")));
}

TEST(Characterization, triangle_area_01) {
    ExpectNearScalar(triangle_area(12.3999996f, 6.0999999f), 37.8199997f, 1e-5);
    ExpectNearScalar(triangle_area(2.0f, 2.0f), 2.0f, 1e-5);
    ExpectNearScalar(triangle_area(18.3999996f, -10.8000002f), -99.3600006f, 1e-5);
    ExpectNearScalar(triangle_area(-4.46000004f, -4.34000015f), 9.67820072f, 1e-5);
    ExpectNearScalar(triangle_area(3.0f, 3.5999999f), 5.39999962f, 1e-5);
    ExpectNearScalar(triangle_area(10.0f, 9.30000019f), 46.5f, 1e-5);
    ExpectNearScalar(triangle_area(6.76000023f, -2.70000005f), -9.1260004f, 1e-5);
    ExpectNearScalar(triangle_area(-2.29999995f, 9.99999975e-05f), -0.000114999995f, 1e-5);
    ExpectNearScalar(triangle_area(18.0f, 2.0f), 18.0f, 1e-5);
    ExpectNearScalar(triangle_area(40.0f, -0.469999999f), -9.39999962f, 1e-5);
    ExpectNearScalar(triangle_area(10.0f, 8.5f), 42.5f, 1e-5);
    ExpectNearScalar(triangle_area(14.1999998f, 39.7999992f), 282.579987f, 1e-5);
}

TEST(Characterization, fib4_01) {
    EXPECT_EQ((fib4(12)), (386));
    EXPECT_EQ((fib4(5)), (4));
    EXPECT_EQ((fib4(3)), (0));
    EXPECT_EQ((fib4(6)), (8));
    EXPECT_EQ((fib4(26)), (3772632));
    EXPECT_EQ((fib4(8)), (28));
    EXPECT_EQ((fib4(11)), (200));
    EXPECT_EQ((fib4(23)), (526768));
    EXPECT_EQ((fib4(0)), (0));
    EXPECT_EQ((fib4(22)), (273282));
    EXPECT_EQ((fib4(21)), (141776));
    EXPECT_EQ((fib4(2)), (2));
}

TEST(Characterization, median_01) {
    ExpectNearScalar(median(std::vector<float >{4.0f, 14.5f, 10.6999998f}), 10.6999998f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.0f, 1.0f, 3.0f, 9.0f, 9.0f, 2.0f, 7.0f}), 7.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{5.80000019f}), 5.80000019f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{5.0999999f}), 5.0999999f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{4.0f, 6.0f, 1000.0f, 10.0f, 20.0f}), 10.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.0f, 1.0f, 3.0f, 9.0f, 9.0f, 2.0f}), 5.5f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{5.0f}), 5.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-8.0f, 8.0f, 15.0f, 4.4000001f, -5.30000019f}), 4.4000001f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-6.69999981f, 7.9000001f, 5.5f, 19.8999996f, 9.99999975e-05f, 2.5999999f, 9.80000019f}), 5.5f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{3.0f, 3.20000005f, 2.0f, 4.0f, 5.0f}), 3.20000005f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{5.5f, 1.0f, 3.0f, 9.0f, 9.0f, 2.0f, 7.0f}), 5.5f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-18.8999996f, -8.0f, 5.92000008f, 9.99999975e-05f, 20.0f, 4.65999985f}), 2.33004999f, 1e-5);
}

TEST(Characterization, is_palindrome_01) {
    EXPECT_EQ((is_palindrome(std::string("u"))), (true));
    EXPECT_EQ((is_palindrome(std::string("q"))), (true));
    EXPECT_EQ((is_palindrome(std::string("aaaaa"))), (true));
    EXPECT_EQ((is_palindrome(std::string("xywyx"))), (true));
    EXPECT_EQ((is_palindrome(std::string("xywex"))), (false));
    EXPECT_EQ((is_palindrome(std::string("o"))), (true));
    EXPECT_EQ((is_palindrome(std::string("xywlyz"))), (false));
    EXPECT_EQ((is_palindrome(std::string("Ic3MCh0j"))), (false));
    EXPECT_EQ((is_palindrome(std::string("aba"))), (true));
    EXPECT_EQ((is_palindrome(std::string("xywyz"))), (false));
    EXPECT_EQ((is_palindrome(std::string("ombcd"))), (false));
    EXPECT_EQ((is_palindrome(std::string("Ny1oAh9bXH"))), (false));
}
