// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_16.h"

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

TEST(Characterization, solutions_01) {
    EXPECT_EQ((solutions(std::vector<int >{2, 4, 8})), (0));
    EXPECT_EQ((solutions(std::vector<int >{1, -238, 26, 99999, 0, 12, -1})), (1));
    EXPECT_EQ((solutions(std::vector<int >{5, 8, 7, 1, 99999})), (100011));
    EXPECT_EQ((solutions(std::vector<int >{5, 8, 7, 1})), (12));
    EXPECT_EQ((solutions(std::vector<int >{3, 3, 3, 3, 3})), (9));
    EXPECT_EQ((solutions(std::vector<int >{1, 544, 2, 0, 23})), (24));
    EXPECT_EQ((solutions(std::vector<int >{5, 0})), (5));
    EXPECT_EQ((solutions(std::vector<int >{30, 13, 24, 321})), (0));
    EXPECT_EQ((solutions(std::vector<int >{5, 4, 7, 1})), (12));
    EXPECT_EQ((solutions(std::vector<int >{19, 15, 0, 21})), (19));
    EXPECT_EQ((solutions(std::vector<int >{1, 13, -116, 8, -10, 322, 3, -1})), (4));
    EXPECT_EQ((solutions(std::vector<int >{})), (0));
}

TEST(Characterization, add_elements_01) {
    EXPECT_EQ((add_elements(std::vector<int >{11, 21, 5, 90, 3, 6, 7, 8, 9}, -546)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{1, -2, -3, 41, 2, 76, 87, 88, 99}, -272)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{11, 682, 523, -4, -10, -8}, -4)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{212}, -6)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{}, -532)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{111, 121, 3, 4000, 5, 6}, 1)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{77}, -784)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{1, -2, -3, 41, 57, 76, 87, 9, 99}, -1)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{11, 21, 3, 90, 5, 6, 7, 8, 9}, 8)), (151));
    EXPECT_EQ((add_elements(std::vector<int >{-4, 11}, -6)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 7, 7, 9}, -93)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{101, 8, 11, -1, 19, 20, 495, 189}, 0)), (0));
}

TEST(Characterization, get_odd_collatz_01) {
    EXPECT_EQ((get_odd_collatz(1)), (std::vector<int >{1}));
    EXPECT_EQ((get_odd_collatz(8)), (std::vector<int >{1}));
    EXPECT_EQ((get_odd_collatz(571)), (std::vector<int >{1, 5, 13, 17, 181, 571, 643, 857, 965}));
    EXPECT_EQ((get_odd_collatz(7)), (std::vector<int >{1, 5, 7, 11, 13, 17}));
    EXPECT_EQ((get_odd_collatz(6)), (std::vector<int >{1, 3, 5}));
    EXPECT_EQ((get_odd_collatz(17)), (std::vector<int >{1, 5, 13, 17}));
    EXPECT_EQ((get_odd_collatz(27)), (std::vector<int >{1, 5, 23, 27, 31, 35, 41, 47, 53, 61, 71, 91, 103, 107, 121, 137, 155, 161, 167, 175, 233, 251, 263, 283, 319, 325, 377, 395, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(14)), (std::vector<int >{1, 5, 7, 11, 13, 17}));
    EXPECT_EQ((get_odd_collatz(3)), (std::vector<int >{1, 3, 5}));
    EXPECT_EQ((get_odd_collatz(20)), (std::vector<int >{1, 5}));
    EXPECT_EQ((get_odd_collatz(13)), (std::vector<int >{1, 5, 13}));
    EXPECT_EQ((get_odd_collatz(129)), (std::vector<int >{1, 5, 23, 35, 47, 53, 55, 61, 71, 73, 83, 91, 97, 103, 107, 121, 125, 129, 137, 155, 161, 167, 175, 233, 251, 263, 283, 319, 325, 377, 395, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
}

TEST(Characterization, valid_date_01) {
    EXPECT_EQ((valid_date(std::string("01-01-2007"))), (true));
    EXPECT_EQ((valid_date(std::string("03-11-2000"))), (true));
    EXPECT_EQ((valid_date(std::string("06-06-x200"))), (false));
    EXPECT_EQ((valid_date(std::string("wBvv/yV"))), (false));
    EXPECT_EQ((valid_date(std::string("06-0T6-2005"))), (false));
    EXPECT_EQ((valid_date(std::string("WRpa"))), (false));
    EXPECT_EQ((valid_date(std::string("ZE98IBI"))), (false));
    EXPECT_EQ((valid_date(std::string("06/04/2020"))), (false));
    EXPECT_EQ((valid_date(std::string("W00A-04"))), (false));
    EXPECT_EQ((valid_date(std::string("2003-04-12"))), (false));
    EXPECT_EQ((valid_date(std::string("04-0-2040"))), (false));
    EXPECT_EQ((valid_date(std::string("04-31-3000"))), (false));
}

TEST(Characterization, split_words_01) {
    EXPECT_EQ((split_words(std::string("1uSgSeTNe0"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("D4u"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("K6nbsIxX,"))), (std::vector<std::string >{std::string("K6nbsIxX")}));
    EXPECT_EQ((split_words(std::string("BJTj!jv"))), (std::vector<std::string >{std::string("3")}));
    EXPECT_EQ((split_words(std::string("Hello,world!"))), (std::vector<std::string >{std::string("Hello"), std::string("world!")}));
    EXPECT_EQ((split_words(std::string("Hello wold!"))), (std::vector<std::string >{std::string("Hello"), std::string("wold!")}));
    EXPECT_EQ((split_words(std::string("Hello wrlde!"))), (std::vector<std::string >{std::string("Hello"), std::string("wrlde!")}));
    EXPECT_EQ((split_words(std::string("jiq1TuRq7"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string("!"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("Hello"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string("g"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("h"))), (std::vector<std::string >{std::string("1")}));
}

TEST(Characterization, is_sorted_01) {
    EXPECT_EQ((is_sorted(std::vector<int >{4})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{3, 2, 1})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{6, 507, 6, 7})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{7, 0, 2, 4, 1, -6, 4, 1})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 2, 2, 3, 4})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{15, 671, 1, 6, 2, 5, -656, 4})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 2, 3, 3, 4})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{4, 25})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 6, 5, 4})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 3, 2, 4, 5, 11})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{8, 20})), (true));
}

TEST(Characterization, intersection_01) {
    EXPECT_EQ((intersection(std::vector<int >{-8, 3, 574}, std::vector<int >{-2, -2})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{3, -7, 14, -12, 23}, std::vector<int >{3, -737, -11, 85, 2, -978, 25})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, 18}, std::vector<int >{-1, -11})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{6, 3, 592, -2, 27, 99999}, std::vector<int >{-1, 4, 1})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{3, -1}, std::vector<int >{-1, 5})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{2, 3}, std::vector<int >{-11, 2, -7})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{78, 21, 3, -215, 22, -2, 1}, std::vector<int >{3, 25})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{2, 4}, std::vector<int >{0, 4})), (std::string("YES")));
    EXPECT_EQ((intersection(std::vector<int >{0, 4}, std::vector<int >{5, -5, -4, 1, -3, -911, -3, 1})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-123, 29, 5, -534, 11}, std::vector<int >{-1, -1})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, -389}, std::vector<int >{2, 3})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{0, -5, -7, 28, -4, 3, 221, -1}, std::vector<int >{108, 6, -128, -2, 21, 0, 3, 2})), (std::string("NO")));
}

TEST(Characterization, prod_signs_01) {
    EXPECT_EQ((prod_signs(std::vector<int >{1, 966, -32770, 9, -4})), (33750));
    EXPECT_EQ((prod_signs(std::vector<int >{-1})), (-1));
    EXPECT_EQ((prod_signs(std::vector<int >{0, 1})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{-8, 20, 15, 8, 14})), (-65));
    EXPECT_EQ((prod_signs(std::vector<int >{-355, 14, 1, -4, 4, 21})), (399));
    EXPECT_EQ((prod_signs(std::vector<int >{-1, 1, -1, 1})), (4));
    EXPECT_EQ((prod_signs(std::vector<int >{-1, 1, 1, 0})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{4, 4, -5, 1, -5, 27})), (46));
    EXPECT_EQ((prod_signs(std::vector<int >{2, 4, 9, 2, -1, -1, 1})), (20));
    EXPECT_EQ((prod_signs(std::vector<int >{-2})), (-2));
    EXPECT_EQ((prod_signs(std::vector<int >{-1, 1, 1, 1})), (-4));
    EXPECT_EQ((prod_signs(std::vector<int >{21, 11, 24, 7, 21, -4, -1, 0})), (0));
}
