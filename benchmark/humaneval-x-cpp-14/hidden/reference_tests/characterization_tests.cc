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

TEST(Characterization, by_length_01) {
    EXPECT_EQ((by_length(std::vector<int >{-1, 1, 55})), (std::vector<std::string >{std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{2, -238, 26, 99999, 4, 3, -1})), (std::vector<std::string >{std::string("Four"), std::string("Three"), std::string("Two")}));
    EXPECT_EQ((by_length(std::vector<int >{1, 1, 2, 2, 3, 4, 5, 8, 99999})), (std::vector<std::string >{std::string("Eight"), std::string("Five"), std::string("Four"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{9, 4, 8})), (std::vector<std::string >{std::string("Nine"), std::string("Eight"), std::string("Four")}));
    EXPECT_EQ((by_length(std::vector<int >{1, 544, 3, 53, 55})), (std::vector<std::string >{std::string("Three"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{0})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{1, -1, 3, 2})), (std::vector<std::string >{std::string("Three"), std::string("Two"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{4, 8})), (std::vector<std::string >{std::string("Eight"), std::string("Four")}));
    EXPECT_EQ((by_length(std::vector<int >{})), (std::vector<std::string >{}));
    EXPECT_EQ((by_length(std::vector<int >{9, 4, 8, 19})), (std::vector<std::string >{std::string("Nine"), std::string("Eight"), std::string("Four")}));
    EXPECT_EQ((by_length(std::vector<int >{2, 1, 1, 4, 5, 8, 2, 3})), (std::vector<std::string >{std::string("Eight"), std::string("Five"), std::string("Four"), std::string("Three"), std::string("Two"), std::string("Two"), std::string("One"), std::string("One")}));
    EXPECT_EQ((by_length(std::vector<int >{1, -1, 55})), (std::vector<std::string >{std::string("One")}));
}

TEST(Characterization, f_01) {
    EXPECT_EQ((f(-953)), (std::vector<int >{}));
    EXPECT_EQ((f(6)), (std::vector<int >{1, 2, 6, 24, 15, 720}));
    EXPECT_EQ((f(2)), (std::vector<int >{1, 2}));
    EXPECT_EQ((f(1)), (std::vector<int >{1}));
    EXPECT_EQ((f(-10)), (std::vector<int >{}));
    EXPECT_EQ((f(-8)), (std::vector<int >{}));
    EXPECT_EQ((f(-4)), (std::vector<int >{}));
    EXPECT_EQ((f(3)), (std::vector<int >{1, 2, 6}));
    EXPECT_EQ((f(0)), (std::vector<int >{}));
    EXPECT_EQ((f(9)), (std::vector<int >{1, 2, 6, 24, 15, 720, 28, 40320, 45}));
    EXPECT_EQ((f(7)), (std::vector<int >{1, 2, 6, 24, 15, 720, 28}));
    EXPECT_EQ((f(-5)), (std::vector<int >{}));
}

TEST(Characterization, even_odd_palindrome_01) {
    EXPECT_EQ((even_odd_palindrome(1)), (std::vector<int >{0, 1}));
    EXPECT_EQ((even_odd_palindrome(5)), (std::vector<int >{2, 3}));
    EXPECT_EQ((even_odd_palindrome(571)), (std::vector<int >{28, 37}));
    EXPECT_EQ((even_odd_palindrome(7)), (std::vector<int >{3, 4}));
    EXPECT_EQ((even_odd_palindrome(6)), (std::vector<int >{3, 3}));
    EXPECT_EQ((even_odd_palindrome(-3)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(27)), (std::vector<int >{5, 6}));
    EXPECT_EQ((even_odd_palindrome(0)), (std::vector<int >{0, 0}));
    EXPECT_EQ((even_odd_palindrome(121)), (std::vector<int >{8, 13}));
    EXPECT_EQ((even_odd_palindrome(25)), (std::vector<int >{5, 6}));
    EXPECT_EQ((even_odd_palindrome(20)), (std::vector<int >{4, 6}));
    EXPECT_EQ((even_odd_palindrome(-5)), (std::vector<int >{0, 0}));
}

TEST(Characterization, count_nums_01) {
    EXPECT_EQ((count_nums(std::vector<int >{-1, -2, 0})), (0));
    EXPECT_EQ((count_nums(std::vector<int >{1})), (1));
    EXPECT_EQ((count_nums(std::vector<int >{1, 6, 9, -6, 0, 15, 5})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{2, 12, 1000})), (3));
    EXPECT_EQ((count_nums(std::vector<int >{1, 1, 2})), (3));
    EXPECT_EQ((count_nums(std::vector<int >{0, 1, -221})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{26, 1})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{})), (0));
    EXPECT_EQ((count_nums(std::vector<int >{1, 100, 98, -7, 1, -1})), (4));
    EXPECT_EQ((count_nums(std::vector<int >{-124, 28, 0, -921, -4})), (2));
    EXPECT_EQ((count_nums(std::vector<int >{1, 6, 9, -6, 0, 1, 5})), (5));
    EXPECT_EQ((count_nums(std::vector<int >{1, 6, 9, -6, 5, 1, 0})), (5));
}

TEST(Characterization, move_one_ball_01) {
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 5, 3})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 5, 10, 1, 2, 27})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 4, 5, 1, 2})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{1})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{22, 679})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{4, 3, 1, 2})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{3})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{15, 25, 960, 22, 30})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{-412, -9, 24})), (true));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 5, 4, 1, 2, 6})), (false));
    EXPECT_EQ((move_one_ball(std::vector<int >{3, 5, 4, 1, 2, 1000})), (false));
}

TEST(Characterization, exchange_01) {
    EXPECT_EQ((exchange(std::vector<int >{2, 4, 4, 3}, std::vector<int >{1, 2, 3, 4})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{8, 507, 6, 3}, std::vector<int >{3, 2, 6, 9, 8, 1})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{100, 1, 200, 6, 1, -6, 3, 100}, std::vector<int >{100, 200})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{200, 200}, std::vector<int >{15, 671, 1, 1, 2, 2, -656, 101})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 1, 4, 3}, std::vector<int >{5, 25})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{3, 7, 5}, std::vector<int >{5, 7, 3, 11})), (std::string("NO")));
    EXPECT_EQ((exchange(std::vector<int >{7}, std::vector<int >{7, 20})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{-3, 2, 6}, std::vector<int >{2, 1, 4, 3, 200})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{200, 200}, std::vector<int >{100, 7})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 1, 4, 3, 8}, std::vector<int >{1, -626, -5, 254, 102, 206, -356})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 1, 4, 4}, std::vector<int >{1, 5, 3, 4})), (std::string("YES")));
    EXPECT_EQ((exchange(std::vector<int >{2, 6, 3}, std::vector<int >{2, 1, 4, 3})), (std::string("YES")));
}

TEST(Characterization, histogram_01) {
    EXPECT_EQ((histogram(std::string("ygdY"))), (std::map<char, int >{{'Y', 1}, {'d', 1}, {'g', 1}, {'y', 1}}));
    EXPECT_EQ((histogram(std::string("a b c"))), (std::map<char, int >{{'a', 1}, {'b', 1}, {'c', 1}}));
    EXPECT_EQ((histogram(std::string("7fsRi1ZC"))), (std::map<char, int >{{'1', 1}, {'7', 1}, {'C', 1}, {'R', 1}, {'Z', 1}, {'f', 1}, {'i', 1}, {'s', 1}}));
    EXPECT_EQ((histogram(std::string("stuO0GVK0wR"))), (std::map<char, int >{{'0', 2}}));
    EXPECT_EQ((histogram(std::string("JY"))), (std::map<char, int >{{'J', 1}, {'Y', 1}}));
    EXPECT_EQ((histogram(std::string("A"))), (std::map<char, int >{{'A', 1}}));
    EXPECT_EQ((histogram(std::string("IaUrYD"))), (std::map<char, int >{{'D', 1}, {'I', 1}, {'U', 1}, {'Y', 1}, {'a', 1}, {'r', 1}}));
    EXPECT_EQ((histogram(std::string("a b c a b"))), (std::map<char, int >{{'a', 2}, {'b', 2}}));
    EXPECT_EQ((histogram(std::string("hp2lijAr"))), (std::map<char, int >{{'2', 1}, {'A', 1}, {'h', 1}, {'i', 1}, {'j', 1}, {'l', 1}, {'p', 1}, {'r', 1}}));
    EXPECT_EQ((histogram(std::string("36PTn9qLnbS"))), (std::map<char, int >{{'n', 2}}));
    EXPECT_EQ((histogram(std::string("G4Hv77vTZ"))), (std::map<char, int >{{'7', 2}, {'v', 2}}));
    EXPECT_EQ((histogram(std::string(""))), (std::map<char, int >{}));
}

TEST(Characterization, reverse_delete_01) {
    EXPECT_EQ((reverse_delete(std::string("u"), std::string("q"))), (std::vector<std::string >{std::string("u"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("abcde"), std::string("bcd"))), (std::vector<std::string >{std::string("ae"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("dwek"), std::string("o"))), (std::vector<std::string >{std::string("dwek"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("mamlma"), std::string("Ic3MCh0j"))), (std::vector<std::string >{std::string("mamlma"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("abcdedcba"), std::string("w"))), (std::vector<std::string >{std::string("abcdedcba"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("cmoedc"), std::string("Ny1oAh9bXH"))), (std::vector<std::string >{std::string("cmedc"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("ae"), std::string("mi3a"))), (std::vector<std::string >{std::string("e"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("ab"), std::string("True"))), (std::vector<std::string >{std::string("ab"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("xbcdedcba"), std::string(""))), (std::vector<std::string >{std::string("xbcdedcba"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("ITtru0e"), std::string("abb n"))), (std::vector<std::string >{std::string("ITtru0e"), std::string("False")}));
    EXPECT_EQ((reverse_delete(std::string("b"), std::string("adef"))), (std::vector<std::string >{std::string("b"), std::string("True")}));
    EXPECT_EQ((reverse_delete(std::string("zZHo"), std::string("6SGb"))), (std::vector<std::string >{std::string("zZHo"), std::string("False")}));
}
