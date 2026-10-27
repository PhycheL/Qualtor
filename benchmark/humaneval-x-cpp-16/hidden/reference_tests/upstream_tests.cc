// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_16.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_121 {


TEST(HumanEvalX, CPP_121) {

    HE_ASSERT(solutions({5, 8, 7, 1})    == 12);
    HE_ASSERT(solutions({3, 3, 3, 3, 3}) == 9);
    HE_ASSERT(solutions({30, 13, 24, 321}) == 0);
    HE_ASSERT(solutions({5, 9}) == 5);
    HE_ASSERT(solutions({2, 4, 8}) == 0);
    HE_ASSERT(solutions({30, 13, 23, 32}) == 23);
    HE_ASSERT(solutions({3, 13, 2, 9}) == 3);
}

}  // namespace he_cpp_121

namespace he_cpp_122 {


TEST(HumanEvalX, CPP_122) {

    HE_ASSERT(add_elements({1,-2,-3,41,57,76,87,88,99}, 3) == -4);
    HE_ASSERT(add_elements({111,121,3,4000,5,6}, 2) == 0);
    HE_ASSERT(add_elements({11,21,3,90,5,6,7,8,9}, 4) == 125);
    HE_ASSERT(add_elements({111,21,3,4000,5,6,7,8,9}, 4) == 24);
    HE_ASSERT(add_elements({1}, 1) == 1);
}

}  // namespace he_cpp_122

namespace he_cpp_123 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_123) {

    HE_ASSERT(issame(get_odd_collatz(14) , {1, 5, 7, 11, 13, 17}));
    HE_ASSERT(issame(get_odd_collatz(5) , {1, 5}));
    HE_ASSERT(issame(get_odd_collatz(12) , {1, 3, 5}));
    HE_ASSERT(issame(get_odd_collatz(1) , {1}));
}

}  // namespace he_cpp_123

namespace he_cpp_124 {


TEST(HumanEvalX, CPP_124) {

    HE_ASSERT(valid_date("03-11-2000") == true);
    HE_ASSERT(valid_date("15-01-2012") == false);
    HE_ASSERT(valid_date("04-0-2040") == false);
    HE_ASSERT(valid_date("06-04-2020") == true);
    HE_ASSERT(valid_date("01-01-2007") == true);
    HE_ASSERT(valid_date("03-32-2011") == false);
    HE_ASSERT(valid_date("") == false);
    HE_ASSERT(valid_date("04-31-3000") == false);
    HE_ASSERT(valid_date("06-06-2005") == true);
    HE_ASSERT(valid_date("21-31-2000") == false);
    HE_ASSERT(valid_date("04-12-2003") == true);
    HE_ASSERT(valid_date("04122003") == false);
    HE_ASSERT(valid_date("20030412") == false);
    HE_ASSERT(valid_date("2003-04") == false);
    HE_ASSERT(valid_date("2003-04-12") == false);
    HE_ASSERT(valid_date("04-2003") == false);
}

}  // namespace he_cpp_124

namespace he_cpp_125 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_125) {

    HE_ASSERT(issame(split_words("Hello world!") , {"Hello","world!"}));
    HE_ASSERT(issame(split_words("Hello,world!") , {"Hello","world!"}));
    HE_ASSERT(issame(split_words("Hello world,!") , {"Hello","world,!"}));
    HE_ASSERT(issame(split_words("Hello,Hello,world !") , {"Hello,Hello,world","!"}));
    HE_ASSERT(issame(split_words("abcdef") , {"3"}));
    HE_ASSERT(issame(split_words("aaabb") , {"2"}));
    HE_ASSERT(issame(split_words("aaaBb") , {"1"}));
    HE_ASSERT(issame(split_words("") ,{"0"}));
}

}  // namespace he_cpp_125

namespace he_cpp_126 {


TEST(HumanEvalX, CPP_126) {

    HE_ASSERT(is_sorted({5}) == true);
    HE_ASSERT(is_sorted({1, 2, 3, 4, 5}) == true);
    HE_ASSERT(is_sorted({1, 3, 2, 4, 5}) == false);
    HE_ASSERT(is_sorted({1, 2, 3, 4, 5, 6}) == true);
    HE_ASSERT(is_sorted({1, 2, 3, 4, 5, 6, 7}) == true);
    HE_ASSERT(is_sorted({1, 3, 2, 4, 5, 6, 7}) == false);
    HE_ASSERT(is_sorted({}) == true);
    HE_ASSERT(is_sorted({1}) == true);
    HE_ASSERT(is_sorted({3, 2, 1}) == false);
    HE_ASSERT(is_sorted({1, 2, 2, 2, 3, 4}) == false);
    HE_ASSERT(is_sorted({1, 2, 3, 3, 3, 4}) == false);
    HE_ASSERT(is_sorted({1, 2, 2, 3, 3, 4}) == true);
    HE_ASSERT(is_sorted({1, 2, 3, 4}) == true);
}

}  // namespace he_cpp_126

namespace he_cpp_127 {


TEST(HumanEvalX, CPP_127) {

    HE_ASSERT(intersection({1, 2}, {2, 3}) == "NO");
    HE_ASSERT(intersection({-1, 1}, {0, 4}) == "NO");
    HE_ASSERT(intersection({-3, -1}, {-5, 5}) == "YES");
    HE_ASSERT(intersection({-2, 2}, {-4, 0}) == "YES");
    HE_ASSERT(intersection({-11, 2}, {-1, -1}) == "NO");
    HE_ASSERT(intersection({1, 2}, {3, 5}) == "NO");
    HE_ASSERT(intersection({1, 2}, {1, 2}) == "NO");
    HE_ASSERT(intersection({-2, -2}, {-3, -2}) == "NO");
}

}  // namespace he_cpp_127

namespace he_cpp_128 {


TEST(HumanEvalX, CPP_128) {

    HE_ASSERT(prod_signs({1, 2, 2, -4}) == -9);
    HE_ASSERT(prod_signs({0, 1}) == 0);
    HE_ASSERT(prod_signs({1, 1, 1, 2, 3, -1, 1}) == -10);
    HE_ASSERT(prod_signs({}) == -32768);
    HE_ASSERT(prod_signs({2, 4,1, 2, -1, -1, 9}) == 20);
    HE_ASSERT(prod_signs({-1, 1, -1, 1}) == 4);
    HE_ASSERT(prod_signs({-1, 1, 1, 1}) == -4);
    HE_ASSERT(prod_signs({-1, 1, 1, 0}) == 0);
}

}  // namespace he_cpp_128
