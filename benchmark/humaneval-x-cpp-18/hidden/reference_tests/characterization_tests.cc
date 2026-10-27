// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_18.h"

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

TEST(Characterization, is_equal_to_sum_even_01) {
    EXPECT_EQ((is_equal_to_sum_even(4)), (false));
    EXPECT_EQ((is_equal_to_sum_even(26)), (true));
    EXPECT_EQ((is_equal_to_sum_even(29)), (false));
    EXPECT_EQ((is_equal_to_sum_even(12)), (true));
    EXPECT_EQ((is_equal_to_sum_even(28)), (true));
    EXPECT_EQ((is_equal_to_sum_even(903)), (false));
    EXPECT_EQ((is_equal_to_sum_even(11)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-1)), (false));
    EXPECT_EQ((is_equal_to_sum_even(8)), (true));
    EXPECT_EQ((is_equal_to_sum_even(2)), (false));
    EXPECT_EQ((is_equal_to_sum_even(23)), (false));
    EXPECT_EQ((is_equal_to_sum_even(16)), (true));
}

TEST(Characterization, special_factorial_01) {
    EXPECT_EQ((special_factorial(-953)), (1LL));
    EXPECT_EQ((special_factorial(0)), (1LL));
    EXPECT_EQ((special_factorial(2)), (2LL));
    EXPECT_EQ((special_factorial(1)), (1LL));
    EXPECT_EQ((special_factorial(5)), (34560LL));
    EXPECT_EQ((special_factorial(-10)), (1LL));
    EXPECT_EQ((special_factorial(-8)), (1LL));
    EXPECT_EQ((special_factorial(-4)), (1LL));
    EXPECT_EQ((special_factorial(3)), (12LL));
    EXPECT_EQ((special_factorial(4)), (288LL));
    EXPECT_EQ((special_factorial(7)), (125411328000LL));
    EXPECT_EQ((special_factorial(6)), (24883200LL));
}

TEST(Characterization, fix_spaces_01) {
    EXPECT_EQ((fix_spaces(std::string(""))), (std::string("")));
    EXPECT_EQ((fix_spaces(std::string("Example"))), (std::string("Example")));
    EXPECT_EQ((fix_spaces(std::string(" ExampleN "))), (std::string("_ExampleN_")));
    EXPECT_EQ((fix_spaces(std::string("IExample 1"))), (std::string("IExample_1")));
    EXPECT_EQ((fix_spaces(std::string("70Jdu"))), (std::string("70Jdu")));
    EXPECT_EQ((fix_spaces(std::string(" Example   3"))), (std::string("_Example-3")));
    EXPECT_EQ((fix_spaces(std::string("SBBS4G_Sa"))), (std::string("SBBS4G_Sa")));
    EXPECT_EQ((fix_spaces(std::string("h  xa 1 2 2 mpl"))), (std::string("h__xa_1_2_2_mpl")));
    EXPECT_EQ((fix_spaces(std::string("r t"))), (std::string("r_t")));
    EXPECT_EQ((fix_spaces(std::string("xsb0lCK5zC"))), (std::string("xsb0lCK5zC")));
    EXPECT_EQ((fix_spaces(std::string("_ExampEle-3"))), (std::string("_ExampEle-3")));
    EXPECT_EQ((fix_spaces(std::string("Mudasir_Hanif_"))), (std::string("Mudasir_Hanif_")));
}

TEST(Characterization, file_name_check_01) {
    EXPECT_EQ((file_name_check(std::string(", "))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("His12FILE94.exe"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("final.1.tx"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("L5KgtIQ"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("this_is_1u2valid.6exe4.txt"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("RROp"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("\?JK3X j"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("final132"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("1el"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("Yes"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("all.exe.txt"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("1example.dll"))), (std::string("No")));
}

TEST(Characterization, sum_squares_01) {
    EXPECT_EQ((sum_squares(std::vector<int >{3, 26, 13})), (48));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -5, 2, -1, -5, 27})), (-99));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, 0, 0, 0, 0, 0, 0, 0, -1})), (0));
    EXPECT_EQ((sum_squares(std::vector<int >{25})), (625));
    EXPECT_EQ((sum_squares(std::vector<int >{})), (0));
    EXPECT_EQ((sum_squares(std::vector<int >{22, 679})), (1163));
    EXPECT_EQ((sum_squares(std::vector<int >{-26})), (676));
    EXPECT_EQ((sum_squares(std::vector<int >{1, 1, 1, 1, 1, 1, 1, 1, 1})), (9));
    EXPECT_EQ((sum_squares(std::vector<int >{15, 25, 960, 22, 30})), (28694));
    EXPECT_EQ((sum_squares(std::vector<int >{-412, -9, 24})), (169759));
    EXPECT_EQ((sum_squares(std::vector<int >{-16, -9, -2, 36, 36, 26, -20, 25, -40, 20, -4, 12, -26, 35, 37, -2})), (-14192));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -3, 17, -1, -15, 13, -1, 14, -14, -12, -5, 14, -14, 6, 13, 11, 16, 16, 4, 10, 1000})), (999998552));
}

TEST(Characterization, words_in_sentence_01) {
    EXPECT_EQ((words_in_sentence(std::string("z"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("EPp6OGvn"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("l f3nt"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("Hi am Hussein"))), (std::string("Hi am Hussein")));
    EXPECT_EQ((words_in_sentence(std::string("there is no place"))), (std::string("there is no place")));
    EXPECT_EQ((words_in_sentence(std::string("luts go forbswimming"))), (std::string("go")));
    EXPECT_EQ((words_in_sentence(std::string("go wEforit"))), (std::string("go wEforit")));
    EXPECT_EQ((words_in_sentence(std::string("Hi I am Hussein"))), (std::string("Hi am Hussein")));
    EXPECT_EQ((words_in_sentence(std::string("HiUam Hussein"))), (std::string("HiUam Hussein")));
    EXPECT_EQ((words_in_sentence(std::string(""))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("nH"))), (std::string("nH")));
    EXPECT_EQ((words_in_sentence(std::string("Hi am Husei"))), (std::string("Hi am Husei")));
}

TEST(Characterization, simplify_01) {
    EXPECT_EQ((simplify(std::string("4/2"), std::string("10/2"))), (true));
    EXPECT_EQ((simplify(std::string("/5"), std::string("11/6"))), (true));
    EXPECT_EQ((simplify(std::string("50/10"), std::string("8/4"))), (true));
    EXPECT_EQ((simplify(std::string("2/1"), std::string("1/5"))), (false));
    EXPECT_EQ((simplify(std::string("4/2"), std::string("2/10"))), (false));
    EXPECT_EQ((simplify(std::string("11/6"), std::string("6/1"))), (true));
    EXPECT_EQ((simplify(std::string("10/2"), std::string("2/1"))), (true));
    EXPECT_EQ((simplify(std::string("10/2"), std::string("6/1"))), (true));
    EXPECT_EQ((simplify(std::string("1/6"), std::string("2/4"))), (false));
    EXPECT_EQ((simplify(std::string("5/1"), std::string("5/1"))), (true));
    EXPECT_EQ((simplify(std::string("lqc/4VJkIzXr"), std::string("7/10"))), (true));
    EXPECT_EQ((simplify(std::string("2/1"), std::string("8/4"))), (true));
}

TEST(Characterization, order_by_points_01) {
    EXPECT_EQ((order_by_points(std::vector<int >{1, 966, 0, 9, 5})), (std::vector<int >{0, 1, 5, 9, 966}));
    EXPECT_EQ((order_by_points(std::vector<int >{4, 6, 6, -76, -21, 23, 0})), (std::vector<int >{-76, -21, 0, 4, 23, 6, 6}));
    EXPECT_EQ((order_by_points(std::vector<int >{-3, -32, -98, -11, 1, 2, 43, 54})), (std::vector<int >{-3, -32, -98, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{0, 2, 3, 6, 53, 423, 423, 423, 1234, 145, 37, 46, 56, 463, 3457})), (std::vector<int >{0, 2, 3, 6, 53, 423, 423, 423, 1234, 145, 37, 46, 56, 463, 3457}));
    EXPECT_EQ((order_by_points(std::vector<int >{-8, 20, 15, 8, 14})), (std::vector<int >{-8, 20, 14, 15, 8}));
    EXPECT_EQ((order_by_points(std::vector<int >{-355, 14, 5, -12, 145, 21})), (std::vector<int >{-12, 21, 14, 5, -355, 145}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11})), (std::vector<int >{1, 10, 2, 11, 3, 4, 5, 6, 7, 8, 9}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, 11, -1, -11, -12})), (std::vector<int >{-1, -11, 1, -12, 11}));
    EXPECT_EQ((order_by_points(std::vector<int >{46, 7, -5, 6, -5, 27})), (std::vector<int >{-5, -5, 6, 7, 27, 46}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, -11, -1, -12, 11})), (std::vector<int >{-1, -11, 1, -12, 11}));
    EXPECT_EQ((order_by_points(std::vector<int >{-2})), (std::vector<int >{-2}));
    EXPECT_EQ((order_by_points(std::vector<int >{-76, -21, 0, 4, 23, 6, 6})), (std::vector<int >{-76, -21, 0, 4, 23, 6, 6}));
}
