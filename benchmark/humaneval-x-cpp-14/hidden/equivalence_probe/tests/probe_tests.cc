// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_14.h"

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

TEST(Probe, by_length_01) {
    EXPECT_EQ((by_length(std::vector<int >{-2})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{-116, 4, -10, 2, 0, -1})), (std::vector<std::string >{std::string("Four"), std::string("Two")}));
    EXPECT_EQ((by_length(std::vector<int >{1, -1, 3, 2, -623})), (std::vector<std::string >{std::string("Three"), std::string("Two"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{1, 55, -1})), (std::vector<std::string >{std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{2, 1, 1, 5, 8, 2, 3})), (std::vector<std::string >{std::string("Eight"), std::string("Five"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{-3, 1, 1, 53, 1})), (std::vector<std::string >{std::string("One"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{55, 1, -1})), (std::vector<std::string >{std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{1, 2, 2, 1, 3, 4, 5, 8})), (std::vector<std::string >{std::string("Eight"), std::string("Five"), std::string("Four"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{1, 1, 2, 2, 3, 4, 5, 8})), (std::vector<std::string >{std::string("Eight"), std::string("Five"), std::string("Four"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{-5, 313, -3, 19, 1})), (std::vector<std::string >{std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{23})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{-1})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{22, -7})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{4, 9, 12345, 199, 0})), (std::vector<std::string >{std::string("Nine"), std::string("Four")}));
    EXPECT_EQ((by_length(std::vector<int >{9, 4, 8, 5})), (std::vector<std::string >{std::string("Nine"), std::string("Eight"), std::string("Five"), std::string("Four")}));
    EXPECT_EQ((by_length(std::vector<int >{0, -1, 6, 1, -1})), (std::vector<std::string >{std::string("Six"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{8, 4})), (std::vector<std::string >{std::string("Eight"), std::string("Four")}));
    EXPECT_EQ((by_length(std::vector<int >{2, 1, 5, 4, 1, 8, 2, 3})), (std::vector<std::string >{std::string("Eight"), std::string("Five"), std::string("Four"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{1, 1, 2, 2, 3, 4, 5})), (std::vector<std::string >{std::string("Five"), std::string("Four"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{54, 300, 0, 16, 20, 12})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{0, 5, -557, 1, 1, 29, 2, 7})), (std::vector<std::string >{std::string("Seven"), std::string("Five"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{55, -1})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{9, 3, -9, -1, 2, 4})), (std::vector<std::string >{std::string("Nine"), std::string("Four"), std::string("Three"), std::string("Two")}));
    EXPECT_EQ((by_length(std::vector<int >{-1, 55})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{2, 1, 1, 4, 5, 8, 2, 3, 1})), (std::vector<std::string >{std::string("Eight"), std::string("Five"), std::string("Four"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One"), std::string("One")}));
}

TEST(Probe, by_length_02) {
    EXPECT_EQ((by_length(std::vector<int >{1, -1, 55, 0})), (std::vector<std::string >{std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{26, 4, 2, -3})), (std::vector<std::string >{std::string("Four"), std::string("Two")}));
    EXPECT_EQ((by_length(std::vector<int >{55, -777, -1})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{8, 4, -489, 10})), (std::vector<std::string >{std::string("Eight"), std::string("Four")}));
    EXPECT_EQ((by_length(std::vector<int >{-6, 9, 14, -8, 895, 801, 55})), (std::vector<std::string >{std::string("Nine")}));
    EXPECT_EQ((by_length(std::vector<int >{8, 5, 4, 3, 2, 2, 1, 1, 5})), (std::vector<std::string >{std::string("Eight"), std::string("Five"), std::string("Five"), std::string("Four"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{3})), (std::vector<std::string >{std::string("Three")}));
    EXPECT_EQ((by_length(std::vector<int >{3, 5})), (std::vector<std::string >{std::string("Five"), std::string("Three")}));
    EXPECT_EQ((by_length(std::vector<int >{30})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{5, 6, 55, 15, 15, 0})), (std::vector<std::string >{std::string("Six"), std::string("Five")}));
    EXPECT_EQ((by_length(std::vector<int >{-1, 1, 55, 2})), (std::vector<std::string >{std::string("Two"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{1, -1})), (std::vector<std::string >{std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{30, -1, 55})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{1, -1, 55, 2})), (std::vector<std::string >{std::string("Two"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{1, -1, 3, -1})), (std::vector<std::string >{std::string("Three"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{0, -451, 2, 832, 135, 9})), (std::vector<std::string >{std::string("Nine"), std::string("Two")}));
    EXPECT_EQ((by_length(std::vector<int >{748, 26, 874, -9, 4, 19})), (std::vector<std::string >{std::string("Four")}));
    EXPECT_EQ((by_length(std::vector<int >{1, 2, 3, 2})), (std::vector<std::string >{std::string("Three"), std::string("Two"), std::string("Two"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{6})), (std::vector<std::string >{std::string("Six")}));
    EXPECT_EQ((by_length(std::vector<int >{28, -473, 0, -9})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{2, 1, 2, 4, 5, 8, 1, 3})), (std::vector<std::string >{std::string("Eight"), std::string("Five"), std::string("Four"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{5})), (std::vector<std::string >{std::string("Five")}));
    EXPECT_EQ((by_length(std::vector<int >{16, 9, 26, 5, 8, 0, 9, 5})), (std::vector<std::string >{std::string("Nine"), std::string("Nine"), std::string("Eight"), std::string("Five"), std::string("Five")}));
}

TEST(Probe, f_01) {
    EXPECT_EQ((f(12)), (std::vector<int >{1, 2, 6, 24, 15, 720, 28, 40320, 45, 3628800, 66, 479001600}));
    EXPECT_EQ((f(5)), (std::vector<int >{1, 2, 6, 24, 15}));
    EXPECT_EQ((f(-1)), (std::vector<int >{}));
    EXPECT_EQ((f(10)), (std::vector<int >{1, 2, 6, 24, 15, 720, 28, 40320, 45, 3628800}));
    EXPECT_EQ((f(11)), (std::vector<int >{1, 2, 6, 24, 15, 720, 28, 40320, 45, 3628800, 66}));
    EXPECT_EQ((f(-6)), (std::vector<int >{}));
    EXPECT_EQ((f(4)), (std::vector<int >{1, 2, 6, 24}));
    EXPECT_EQ((f(-835)), (std::vector<int >{}));
    EXPECT_EQ((f(-465)), (std::vector<int >{}));
    EXPECT_EQ((f(-779)), (std::vector<int >{}));
    EXPECT_EQ((f(-739)), (std::vector<int >{}));
    EXPECT_EQ((f(-709)), (std::vector<int >{}));
    EXPECT_EQ((f(-7)), (std::vector<int >{}));
    EXPECT_EQ((f(-882)), (std::vector<int >{}));
    EXPECT_EQ((f(-9)), (std::vector<int >{}));
    EXPECT_EQ((f(-3)), (std::vector<int >{}));
    EXPECT_EQ((f(-678)), (std::vector<int >{}));
    EXPECT_EQ((f(-2)), (std::vector<int >{}));
    EXPECT_EQ((f(-93)), (std::vector<int >{}));
    EXPECT_EQ((f(-401)), (std::vector<int >{}));
    EXPECT_EQ((f(-15)), (std::vector<int >{}));
    EXPECT_EQ((f(-617)), (std::vector<int >{}));
    EXPECT_EQ((f(-177)), (std::vector<int >{}));
    EXPECT_EQ((f(8)), (std::vector<int >{1, 2, 6, 24, 15, 720, 28, 40320}));
    EXPECT_EQ((f(-215)), (std::vector<int >{}));
}

TEST(Probe, f_02) {
    EXPECT_EQ((f(-578)), (std::vector<int >{}));
    EXPECT_EQ((f(-491)), (std::vector<int >{}));
    EXPECT_EQ((f(-644)), (std::vector<int >{}));
    EXPECT_EQ((f(-333)), (std::vector<int >{}));
    EXPECT_EQ((f(-135)), (std::vector<int >{}));
    EXPECT_EQ((f(-676)), (std::vector<int >{}));
    EXPECT_EQ((f(-231)), (std::vector<int >{}));
    EXPECT_EQ((f(-747)), (std::vector<int >{}));
    EXPECT_EQ((f(-193)), (std::vector<int >{}));
    EXPECT_EQ((f(-579)), (std::vector<int >{}));
    EXPECT_EQ((f(-376)), (std::vector<int >{}));
    EXPECT_EQ((f(-988)), (std::vector<int >{}));
    EXPECT_EQ((f(-680)), (std::vector<int >{}));
    EXPECT_EQ((f(-346)), (std::vector<int >{}));
    EXPECT_EQ((f(-587)), (std::vector<int >{}));
    EXPECT_EQ((f(-796)), (std::vector<int >{}));
    EXPECT_EQ((f(-374)), (std::vector<int >{}));
    EXPECT_EQ((f(-663)), (std::vector<int >{}));
    EXPECT_EQ((f(-234)), (std::vector<int >{}));
    EXPECT_EQ((f(-319)), (std::vector<int >{}));
    EXPECT_EQ((f(-695)), (std::vector<int >{}));
    EXPECT_EQ((f(-291)), (std::vector<int >{}));
    EXPECT_EQ((f(-743)), (std::vector<int >{}));
}

TEST(Probe, even_odd_palindrome_01) {
    EXPECT_EQ((even_odd_palindrome(-10)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(129)), (std::vector<int >{8, 13}));
    EXPECT_EQ((even_odd_palindrome(486)), (std::vector<int >{27, 30}));
    EXPECT_EQ((even_odd_palindrome(-603)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(8)), (std::vector<int >{4, 4}));
    EXPECT_EQ((even_odd_palindrome(100)), (std::vector<int >{8, 10}));
    EXPECT_EQ((even_odd_palindrome(18)), (std::vector<int >{4, 6}));
    EXPECT_EQ((even_odd_palindrome(10)), (std::vector<int >{4, 5}));
    EXPECT_EQ((even_odd_palindrome(-763)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(179)), (std::vector<int >{8, 18}));
    EXPECT_EQ((even_odd_palindrome(13)), (std::vector<int >{4, 6}));
    EXPECT_EQ((even_odd_palindrome(11)), (std::vector<int >{4, 6}));
    EXPECT_EQ((even_odd_palindrome(17)), (std::vector<int >{4, 6}));
    EXPECT_EQ((even_odd_palindrome(22)), (std::vector<int >{5, 6}));
    EXPECT_EQ((even_odd_palindrome(-8)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(251)), (std::vector<int >{13, 20}));
    EXPECT_EQ((even_odd_palindrome(3)), (std::vector<int >{1, 2}));
    EXPECT_EQ((even_odd_palindrome(19)), (std::vector<int >{4, 6}));
    EXPECT_EQ((even_odd_palindrome(375)), (std::vector<int >{18, 28}));
    EXPECT_EQ((even_odd_palindrome(9)), (std::vector<int >{4, 5}));
    EXPECT_EQ((even_odd_palindrome(366)), (std::vector<int >{18, 27}));
    EXPECT_EQ((even_odd_palindrome(-356)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(64)), (std::vector<int >{6, 8}));
    EXPECT_EQ((even_odd_palindrome(24)), (std::vector<int >{5, 6}));
    EXPECT_EQ((even_odd_palindrome(-498)), (std::vector<int >{0, 0}));
}

TEST(Probe, even_odd_palindrome_02) {
    EXPECT_EQ((even_odd_palindrome(14)), (std::vector<int >{4, 6}));
    EXPECT_EQ((even_odd_palindrome(842)), (std::vector<int >{42, 50}));
    EXPECT_EQ((even_odd_palindrome(2)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_palindrome(315)), (std::vector<int >{18, 22}));
    EXPECT_EQ((even_odd_palindrome(-7)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(136)), (std::vector<int >{8, 14}));
    EXPECT_EQ((even_odd_palindrome(63)), (std::vector<int >{6, 8}));
    EXPECT_EQ((even_odd_palindrome(-301)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(-2)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(258)), (std::vector<int >{14, 20}));
    EXPECT_EQ((even_odd_palindrome(-65)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(12)), (std::vector<int >{4, 6}));
    EXPECT_EQ((even_odd_palindrome(-791)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(669)), (std::vector<int >{35, 40}));
    EXPECT_EQ((even_odd_palindrome(29)), (std::vector<int >{5, 6}));
    EXPECT_EQ((even_odd_palindrome(26)), (std::vector<int >{5, 6}));
    EXPECT_EQ((even_odd_palindrome(-264)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(4)), (std::vector<int >{2, 2}));
    EXPECT_EQ((even_odd_palindrome(-4)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(-1)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(-6)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(-51)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(352)), (std::vector<int >{18, 25}));
}

TEST(Probe, count_nums_01) {
    EXPECT_EQ((count_nums(std::vector<int >{-370, 760, 1, 173})), (4));
    EXPECT_EQ((count_nums(std::vector<int >{0, 1})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{7, -4, 11, -591, 12})), (4));
    EXPECT_EQ((count_nums(std::vector<int >{-45, -1})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{1, 0})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{-919, -7})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{13, 6, -9, 35, 146, 14, 1, 100})), (7));
    EXPECT_EQ((count_nums(std::vector<int >{-1, 11, -11})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{-1})), (0));
    EXPECT_EQ((count_nums(std::vector<int >{12, 23, 34, -45, -56, 0})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{98})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{-2, 1, 2, -2, 3, 4, 5})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{0, 1, -1})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{23, 235, 98})), (3));
    EXPECT_EQ((count_nums(std::vector<int >{-3, 20, 3})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{-670, -1, 5, 99})), (3));
    EXPECT_EQ((count_nums(std::vector<int >{10})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{21, 13, 3, -1})), (3));
    EXPECT_EQ((count_nums(std::vector<int >{1, 751})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{34, -179, -6, 802})), (3));
    EXPECT_EQ((count_nums(std::vector<int >{1, 1, 2, -2, 3, 4, 5})), (6));
    EXPECT_EQ((count_nums(std::vector<int >{23, -77, 12, -7, -56, 456, 25, 0})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{12, 23, 34, -45, -56, 0, 0})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{-123, 1, 99999, -1, 99, -5, 1000, 0})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{8})), (1));
}

TEST(Probe, count_nums_02) {
    EXPECT_EQ((count_nums(std::vector<int >{2, -5, -4, 3, -1})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{-56, 895, 6, -8, -5, -56})), (4));
    EXPECT_EQ((count_nums(std::vector<int >{0, 34, 96, 99999, 812, -857})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{2, 4, 190})), (3));
    EXPECT_EQ((count_nums(std::vector<int >{-9, 11, 2})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{1, 443, 0, -9, -1, 11})), (3));
    EXPECT_EQ((count_nums(std::vector<int >{100, -846})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{-427})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{5, -123, 13, 9, 4, 0})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{2, 14, 1, 7, 33, 7})), (6));
    EXPECT_EQ((count_nums(std::vector<int >{1, 455})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{1, 1, 3, -2, 3, 4, 5})), (6));
    EXPECT_EQ((count_nums(std::vector<int >{-835, 24, 5, -628, 1, 8})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{29})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{14, 32})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{-11, 100, -54, -1, 19})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{1, 1, 2, -2, 3, 4})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{1, 2})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{632, 1})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{-63, 19, 667, 7})), (3));
    EXPECT_EQ((count_nums(std::vector<int >{-1, -2})), (0));
    EXPECT_EQ((count_nums(std::vector<int >{1, -57, 9, -6, 0, 1, 5})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{16, -564, 586, 24, 2, 18})), (6));
}

TEST(Probe, move_one_ball_01) {
    EXPECT_EQ((move_one_ball(std::vector<int >{28})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 5, 4, 1, 2})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 5, 10, 1, 2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 4, 1, 5, 2})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{5, 4, 3, 1, 2})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{13, 2, 10})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 5, 4, 1, 2, 0})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{4, 3, 1, 2, 19})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{2, 4, 1, 4})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{4, 28, 1, 2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{4, 3, 1, 2, 9})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, -1, 10, 1, 2})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{-653, 2, 3, 6, 30, -8, 5})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{4, 3, 1, 2, 3})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{-6, 14, 635, 12, 168, 9})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{880, 30, 4})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{6, 11, -35})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{10, 23, -808, 3, -9, 592, -313})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{29, 559, 2, 813, 19, 2, 7})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 4, 5, 2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{4, 10, 1, 2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{15})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 4, 5, 1, 2, 5})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{1, 6, 9, 21, 1, 3, 287})), (false));
}

TEST(Probe, move_one_ball_02) {
    EXPECT_EQ((move_one_ball(std::vector<int >{-361})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 4, 1, 2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{4, 28})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{4, 7, 19, -4, 850, -810, 10})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 1, 2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{5, 10, 1, 2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{12, 5, 5})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{-566, -2, -1, 26, 5, 3, 15, 100})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{2, 4, 1, 9, 20, 271})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{19})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{-8})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{1, 24, 12345, 22, -1000, 23, 10})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 5, 10, 2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{4})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 5, 4, 1, 4})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{19, 3, -718})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{-1, 6, 5, 418, 10, 2, 691, 15})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{1, 4})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 4, 5, 1, 2, 22})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 24})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{-32})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{10, -1, 1})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{8, 9, 5, 437, -2})), (false));
}

TEST(Probe, exchange_01) {
    EXPECT_EQ((exchange(std::vector<int >{100, 200}, std::vector<int >{1, 2, 3, 4, 100})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{5, 7}, std::vector<int >{26, 15, 669, -5, 3, 2, 6})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 6, 3}, std::vector<int >{315, 6, 3})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{5, 832, 6, 7, -817, 7}, std::vector<int >{5, 7})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{3, 5, 5, 1, 1, 1}, std::vector<int >{1, 5, 14, 7, 7, 915})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{1, 2, 3, 4}, std::vector<int >{1, 15, 3, 17, -548, 26, 12, 27})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{1, 5, 3, 4}, std::vector<int >{12345, 7})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{-3, 9, 5, 7, 6, 3, 265}, std::vector<int >{3, 6, 2})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{}, std::vector<int >{2, 6, 3})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{4, 14, 691}, std::vector<int >{3, 100, 572, 6, 4, 28, 6, 920})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 3, 4, 3}, std::vector<int >{7, 0})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{100, 200}, std::vector<int >{5, 7, 3})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 1, 3}, std::vector<int >{2, 1, 4, 3})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{3, 2, 6, 1, 26, 9}, std::vector<int >{16, 4, 3})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{-5, 598, 12345, 19, 637}, std::vector<int >{2, 6, 4})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{520, 5, 3, 4}, std::vector<int >{-8, 21, 228, 7})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{9, 12345, 6, -3, 20, 2, 2, 6}, std::vector<int >{-2, 5, 9})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{5, 7, 3}, std::vector<int >{3, 2, 6, 1, 4, 9})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{200, 100}, std::vector<int >{30, 14, 25, -1, 5})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{1, 2, 3, 4}, std::vector<int >{16, 4, -8, 2, 410, 3, 1, 9})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 684, 4, 3}, std::vector<int >{2, 1, 4, 3})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{3, 5, 5, 1, 1}, std::vector<int >{1, 5, 3, 4})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{2, 6, 3}, std::vector<int >{4, 6, 2})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{200, 200}, std::vector<int >{2, 1, 4, 3})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{5, 7, 3}, std::vector<int >{3, 2, 6, 1, 8, 9, 4})), (std::string("YES")));
}

TEST(Probe, exchange_02) {
    EXPECT_EQ((exchange(std::vector<int >{19, 6, -14, 6, 9, 5, -1}, std::vector<int >{200, 200})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{1, 2, 3, 4}, std::vector<int >{2, -3, 4})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 6, 4}, std::vector<int >{5, 27, 100})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{200, 100}, std::vector<int >{200, 200})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 1, 4}, std::vector<int >{5, 7, 3})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{200, 200}, std::vector<int >{1, 4, 3, 5})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 1, 4, 3}, std::vector<int >{28})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{2, 1, 4, 3}, std::vector<int >{1, 5, 3, 4})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{3, 5, 5, 1, 1, 1}, std::vector<int >{27, 99999, 2, 22})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{1, 5, 7, 4}, std::vector<int >{14, 10, -600, 100, 9, 452})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{3, 6, 1, 8, 9}, std::vector<int >{5, 7, 3})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{200, -7, 4, 649, 7, 18, -5}, std::vector<int >{4, 4})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{1, 2, 4, 3}, std::vector<int >{5, 7, 3})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{2, 6, 3}, std::vector<int >{1, 5, 3, 4})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{6, 200}, std::vector<int >{2, 6, 3, 1})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{100, 200}, std::vector<int >{2, 3, 4})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 6, 3, -388}, std::vector<int >{})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{2, 1, 3, 4}, std::vector<int >{1, 2, 3, 4})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{5, 7, 3}, std::vector<int >{3, 5, 5, 1, 1, 1, 28})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{100, -732, 4, 7, -1, 344, 12345, 100}, std::vector<int >{4, 15})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{2, 1, 4, 3}, std::vector<int >{7, 3})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{2, 6, 4}, std::vector<int >{7, 6, 5, -6, -405, 4, 2})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{8, 19, 7, -1, 3, 4}, std::vector<int >{200, 200})), (std::string("NO")));
}

TEST(Probe, histogram_01) {
    EXPECT_EQ((histogram(std::string("b"))), (std::map<char, int >{{'b', 1}}));
    EXPECT_EQ((histogram(std::string("a b c d g"))), (std::map<char, int >{{'a', 1}, {'b', 1}, {'c', 1}, {'d', 1}, {'g', 1}}));
    EXPECT_EQ((histogram(std::string("a"))), (std::map<char, int >{{'a', 1}}));
    EXPECT_EQ((histogram(std::string("r tg"))), (std::map<char, int >{{'g', 1}, {'r', 1}, {'t', 1}}));
    EXPECT_EQ((histogram(std::string("r t g"))), (std::map<char, int >{{'g', 1}, {'r', 1}, {'t', 1}}));
    EXPECT_EQ((histogram(std::string("b b b b a"))), (std::map<char, int >{{'b', 4}}));
    EXPECT_EQ((histogram(std::string("4y"))), (std::map<char, int >{{'4', 1}, {'y', 1}}));
    EXPECT_EQ((histogram(std::string("b b b  a"))), (std::map<char, int >{{'b', 3}}));
    EXPECT_EQ((histogram(std::string("pgN"))), (std::map<char, int >{{'N', 1}, {'g', 1}, {'p', 1}}));
    EXPECT_EQ((histogram(std::string("a b k xab"))), (std::map<char, int >{{'a', 2}, {'b', 2}}));
    EXPECT_EQ((histogram(std::string("k"))), (std::map<char, int >{{'k', 1}}));
    EXPECT_EQ((histogram(std::string("a b b a"))), (std::map<char, int >{{'a', 2}, {'b', 2}}));
    EXPECT_EQ((histogram(std::string("W"))), (std::map<char, int >{{'W', 1}}));
    EXPECT_EQ((histogram(std::string("Q b c"))), (std::map<char, int >{{'Q', 1}, {'b', 1}, {'c', 1}}));
    EXPECT_EQ((histogram(std::string("abyc a b"))), (std::map<char, int >{{'a', 2}, {'b', 2}}));
    EXPECT_EQ((histogram(std::string("Ai"))), (std::map<char, int >{{'A', 1}, {'i', 1}}));
    EXPECT_EQ((histogram(std::string("h"))), (std::map<char, int >{{'h', 1}}));
    EXPECT_EQ((histogram(std::string("c"))), (std::map<char, int >{{'c', 1}}));
    EXPECT_EQ((histogram(std::string("jVA"))), (std::map<char, int >{{'A', 1}, {'V', 1}, {'j', 1}}));
    EXPECT_EQ((histogram(std::string("z"))), (std::map<char, int >{{'z', 1}}));
    EXPECT_EQ((histogram(std::string("4jEgVaQOxkL"))), (std::map<char, int >{{'4', 1}, {'E', 1}, {'L', 1}, {'O', 1}, {'Q', 1}, {'V', 1}, {'a', 1}, {'g', 1}, {'j', 1}, {'k', 1}, {'x', 1}}));
    EXPECT_EQ((histogram(std::string("a bacna b"))), (std::map<char, int >{{'a', 3}}));
    EXPECT_EQ((histogram(std::string("a b cb a"))), (std::map<char, int >{{'a', 2}, {'b', 2}}));
    EXPECT_EQ((histogram(std::string("O"))), (std::map<char, int >{{'O', 1}}));
    EXPECT_EQ((histogram(std::string("yctThqIvR"))), (std::map<char, int >{{'I', 1}, {'R', 1}, {'T', 1}, {'c', 1}, {'h', 1}, {'q', 1}, {'t', 1}, {'v', 1}, {'y', 1}}));
}

TEST(Probe, histogram_02) {
    EXPECT_EQ((histogram(std::string("q9gj5BAHX3gw"))), (std::map<char, int >{{'g', 2}}));
    EXPECT_EQ((histogram(std::string(" bSb b N"))), (std::map<char, int >{{'b', 3}}));
    EXPECT_EQ((histogram(std::string("d6a b c d g"))), (std::map<char, int >{{'d', 2}}));
    EXPECT_EQ((histogram(std::string("AI"))), (std::map<char, int >{{'A', 1}, {'I', 1}}));
    EXPECT_EQ((histogram(std::string("B8zeJXr"))), (std::map<char, int >{{'8', 1}, {'B', 1}, {'J', 1}, {'X', 1}, {'e', 1}, {'r', 1}, {'z', 1}}));
    EXPECT_EQ((histogram(std::string("eNAaUkan"))), (std::map<char, int >{{'a', 2}}));
    EXPECT_EQ((histogram(std::string("Aeufv4"))), (std::map<char, int >{{'4', 1}, {'A', 1}, {'e', 1}, {'f', 1}, {'u', 1}, {'v', 1}}));
    EXPECT_EQ((histogram(std::string("Ma Hbf c"))), (std::map<char, int >{{'H', 1}, {'M', 1}, {'a', 1}, {'b', 1}, {'c', 1}, {'f', 1}}));
    EXPECT_EQ((histogram(std::string(" f b c a"))), (std::map<char, int >{{'a', 1}, {'b', 1}, {'c', 1}, {'f', 1}}));
    EXPECT_EQ((histogram(std::string("ab c d "))), (std::map<char, int >{{'a', 1}, {'b', 1}, {'c', 1}, {'d', 1}}));
    EXPECT_EQ((histogram(std::string("a b 6a b"))), (std::map<char, int >{{'a', 2}, {'b', 2}}));
    EXPECT_EQ((histogram(std::string("lz3M0lIfcK"))), (std::map<char, int >{{'l', 2}}));
    EXPECT_EQ((histogram(std::string("9A"))), (std::map<char, int >{{'9', 1}, {'A', 1}}));
    EXPECT_EQ((histogram(std::string("j9L9bxo"))), (std::map<char, int >{{'9', 2}}));
    EXPECT_EQ((histogram(std::string("o0H9piitvrQ"))), (std::map<char, int >{{'i', 2}}));
    EXPECT_EQ((histogram(std::string("2"))), (std::map<char, int >{{'2', 1}}));
    EXPECT_EQ((histogram(std::string("UggI5Q"))), (std::map<char, int >{{'g', 2}}));
    EXPECT_EQ((histogram(std::string("LQa"))), (std::map<char, int >{{'L', 1}, {'Q', 1}, {'a', 1}}));
    EXPECT_EQ((histogram(std::string("z9AvxLla"))), (std::map<char, int >{{'9', 1}, {'A', 1}, {'L', 1}, {'a', 1}, {'l', 1}, {'v', 1}, {'x', 1}, {'z', 1}}));
    EXPECT_EQ((histogram(std::string("7"))), (std::map<char, int >{{'7', 1}}));
    EXPECT_EQ((histogram(std::string("a b cd"))), (std::map<char, int >{{'a', 1}, {'b', 1}, {'c', 1}, {'d', 1}}));
    EXPECT_EQ((histogram(std::string("GrZZYlw0fB T"))), (std::map<char, int >{{'Z', 2}}));
    EXPECT_EQ((histogram(std::string("9rnLPcA4Tqax"))), (std::map<char, int >{{'4', 1}, {'9', 1}, {'A', 1}, {'L', 1}, {'P', 1}, {'T', 1}, {'a', 1}, {'c', 1}, {'n', 1}, {'q', 1}, {'r', 1}, {'x', 1}}));
}

TEST(Probe, reverse_delete_01) {
    EXPECT_EQ((reverse_delete(std::string("b"), std::string("Ust9T7n6"))), (std::vector<std::string >{std::string("b"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("ka"), std::string("cdedc"))), (std::vector<std::string >{std::string("ka"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("2acdef"), std::string("bcd"))), (std::vector<std::string >{std::string("2aef"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("cvdedc"), std::string(""))), (std::vector<std::string >{std::string("cvdedc"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("ws"), std::string("kJa"))), (std::vector<std::string >{std::string("ws"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("lsk"), std::string("E"))), (std::vector<std::string >{std::string("lsk"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("o3TQbRZ"), std::string("acd9f"))), (std::vector<std::string >{std::string("o3TQbRZ"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("ab"), std::string("Xb"))), (std::vector<std::string >{std::string("a"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("qa"), std::string("7R"))), (std::vector<std::string >{std::string("qa"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("QqQpq"), std::string("Fals"))), (std::vector<std::string >{std::string("QqQpq"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("dik"), std::string("dwik"))), (std::vector<std::string >{std::string(""), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("aceO"), std::string("akb"))), (std::vector<std::string >{std::string("ceO"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("mamma"), std::string("ncd"))), (std::vector<std::string >{std::string("mamma"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("Yfpi5lF4EZej"), std::string("False"))), (std::vector<std::string >{std::string("Yfpi54EZj"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string(""), std::string("vaBbba"))), (std::vector<std::string >{std::string(""), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("mb"), std::string("OzFBwFg7e5A"))), (std::vector<std::string >{std::string("mb"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("vNqk"), std::string("abb"))), (std::vector<std::string >{std::string("vNqk"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("qW"), std::string("abba"))), (std::vector<std::string >{std::string("qW"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("dwik"), std::string("vabba"))), (std::vector<std::string >{std::string("dwik"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("pDPqHd4mwUA5"), std::string("cdef"))), (std::vector<std::string >{std::string("pDPqH4mwUA5"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("True"), std::string("cdedc"))), (std::vector<std::string >{std::string("Tru"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("Ap"), std::string("3cKPDZl"))), (std::vector<std::string >{std::string("Ap"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string(""), std::string(""))), (std::vector<std::string >{std::string(""), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("0cdedc"), std::string("False"))), (std::vector<std::string >{std::string("0cddc"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("ab"), std::string("abcde"))), (std::vector<std::string >{std::string(""), std::string("True")}));
}

TEST(Probe, reverse_delete_02) {
    EXPECT_EQ((reverse_delete(std::string("U"), std::string("v"))), (std::vector<std::string >{std::string("U"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("2kFYP3"), std::string("ktM28TcX3Xp5"))), (std::vector<std::string >{std::string("FYP"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("w"), std::string("v"))), (std::vector<std::string >{std::string("w"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("cv"), std::string("a"))), (std::vector<std::string >{std::string("cv"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("a"), std::string("2jau655v"))), (std::vector<std::string >{std::string(""), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("ab"), std::string("xiRjuV8"))), (std::vector<std::string >{std::string("ab"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("1 z4JmX2"), std::string("mia"))), (std::vector<std::string >{std::string("1 z4JX2"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("0xO"), std::string("abcdedcba"))), (std::vector<std::string >{std::string("0xO"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("Qw"), std::string("mamma"))), (std::vector<std::string >{std::string("Qw"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("cdjldc"), std::string("Zbcdff"))), (std::vector<std::string >{std::string("jl"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("mL2IfF8x3R8"), std::string(" UyYyZdt0Ly"))), (std::vector<std::string >{std::string("m2IfF8x3R8"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("a"), std::string("True"))), (std::vector<std::string >{std::string("a"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("Eae"), std::string("1G "))), (std::vector<std::string >{std::string("Eae"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("EzBS0sE"), std::string("ab"))), (std::vector<std::string >{std::string("EzBS0sE"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("VhVTi5"), std::string("False"))), (std::vector<std::string >{std::string("VhVTi5"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string(""), std::string("Qa6gGZl07kuw"))), (std::vector<std::string >{std::string(""), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("qqyhRMx"), std::string("EAjXO5r"))), (std::vector<std::string >{std::string("qqyhRMx"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("dkk"), std::string("bgdOOcU8"))), (std::vector<std::string >{std::string("kk"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("ade"), std::string("EKdwik"))), (std::vector<std::string >{std::string("ae"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("vgrsOrPJH"), std::string("lVK"))), (std::vector<std::string >{std::string("vgrsOrPJH"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("iWk9"), std::string("dwik"))), (std::vector<std::string >{std::string("W9"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("fX7ej1C"), std::string("acndef"))), (std::vector<std::string >{std::string("X7j1C"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("a"), std::string("Jwebik"))), (std::vector<std::string >{std::string("a"), std::string("True")}));
}
