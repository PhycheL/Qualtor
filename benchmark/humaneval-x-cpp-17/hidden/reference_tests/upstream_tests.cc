// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_17.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_129 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_129) {

    HE_ASSERT(issame(minPath({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 3) , {1, 2, 1}));
    HE_ASSERT(issame(minPath({{5, 9, 3}, {4, 1, 6}, {7, 8, 2}}, 1) , {1}));
    HE_ASSERT(issame(minPath({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}, 4) , {1, 2, 1, 2}));
    HE_ASSERT(issame(minPath({{6, 4, 13, 10}, {5, 7, 12, 1}, {3, 16, 11, 15}, {8, 14, 9, 2}}, 7) , {1, 10, 1, 10, 1, 10, 1}));
    HE_ASSERT(issame(minPath({{8, 14, 9, 2}, {6, 4, 13, 15}, {5, 7, 1, 12}, {3, 10, 11, 16}}, 5) , {1, 7, 1, 7, 1}));
    HE_ASSERT(issame(minPath({{11, 8, 7, 2}, {5, 16, 14, 4}, {9, 3, 15, 6}, {12, 13, 10, 1}}, 9) , {1, 6, 1, 6, 1, 6, 1, 6, 1}));
    HE_ASSERT(issame(minPath({{12, 13, 10, 1}, {9, 3, 15, 6}, {5, 16, 14, 4}, {11, 8, 7, 2}}, 12) , {1, 6, 1, 6, 1, 6, 1, 6, 1, 6, 1, 6}));
    HE_ASSERT(issame(minPath({{2, 7, 4}, {3, 1, 5}, {6, 8, 9}}, 8) , {1, 3, 1, 3, 1, 3, 1, 3}));
    HE_ASSERT(issame(minPath({{6, 1, 5}, {3, 8, 9}, {2, 7, 4}}, 8) , {1, 5, 1, 5, 1, 5, 1, 5}));
    HE_ASSERT(issame(minPath({{1, 2}, {3, 4}}, 10) , {1, 2, 1, 2, 1, 2, 1, 2, 1, 2}));
    HE_ASSERT(issame(minPath({{1, 3}, {3, 2}}, 10) , {1, 3, 1, 3, 1, 3, 1, 3, 1, 3}));
}

}  // namespace he_cpp_129

namespace he_cpp_130 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_130) {

    HE_ASSERT(issame(tri(3) , {1, 3, 2, 8}));
    HE_ASSERT(issame(tri(4) , {1, 3, 2, 8, 3}));
    HE_ASSERT(issame(tri(5) , {1, 3, 2, 8, 3, 15}));
    HE_ASSERT(issame(tri(6) , {1, 3, 2, 8, 3, 15, 4}));
    HE_ASSERT(issame(tri(7) , {1, 3, 2, 8, 3, 15, 4, 24}));
    HE_ASSERT(issame(tri(8) , {1, 3, 2, 8, 3, 15, 4, 24, 5}));
    HE_ASSERT(issame(tri(9) , {1, 3, 2, 8, 3, 15, 4, 24, 5, 35}));
    HE_ASSERT(issame(tri(20) , {1, 3, 2, 8, 3, 15, 4, 24, 5, 35, 6, 48, 7, 63, 8, 80, 9, 99, 10, 120, 11}));
    HE_ASSERT(issame(tri(0) , {1}));
    HE_ASSERT(issame(tri(1) , {1, 3}));
}

}  // namespace he_cpp_130

namespace he_cpp_131 {


TEST(HumanEvalX, CPP_131) {

    HE_ASSERT(digits(5) == 5);
    HE_ASSERT(digits(54) == 5);
    HE_ASSERT(digits(120) ==1);
    HE_ASSERT(digits(5014) == 5);
    HE_ASSERT(digits(98765) == 315);
    HE_ASSERT(digits(5576543) == 2625);
    HE_ASSERT(digits(2468) == 0);
}

}  // namespace he_cpp_131

namespace he_cpp_132 {


TEST(HumanEvalX, CPP_132) {

    HE_ASSERT(is_nested("[[]]") == true);
    HE_ASSERT(is_nested("[]]]]]]][[[[[]") == false);
    HE_ASSERT(is_nested("[][]") == false);
    HE_ASSERT(is_nested(("[]")) == false);
    HE_ASSERT(is_nested("[[[[]]]]") == true);
    HE_ASSERT(is_nested("[]]]]]]]]]]") == false);
    HE_ASSERT(is_nested("[][][[]]") == true);
    HE_ASSERT(is_nested("[[]") == false);
    HE_ASSERT(is_nested("[]]") == false);
    HE_ASSERT(is_nested("[[]][[") == true);
    HE_ASSERT(is_nested("[[][]]") == true);
    HE_ASSERT(is_nested("") == false);
    HE_ASSERT(is_nested("[[[[[[[[") == false);
    HE_ASSERT(is_nested("]]]]]]]]") == false);
}

}  // namespace he_cpp_132

namespace he_cpp_133 {


TEST(HumanEvalX, CPP_133) {

    HE_ASSERT(sum_squares({1,2,3})==14);
    HE_ASSERT(sum_squares({1.0,2,3})==14);
    HE_ASSERT(sum_squares({1,3,5,7})==84);
    HE_ASSERT(sum_squares({1.4,4.2,0})==29);
    HE_ASSERT(sum_squares({-2.4,1,1})==6);
    HE_ASSERT(sum_squares({100,1,15,2})==10230);
    HE_ASSERT(sum_squares({10000,10000})==200000000);
    HE_ASSERT(sum_squares({-1.4,4.6,6.3})==75);
    HE_ASSERT(sum_squares({-1.4,17.9,18.9,19.9})==1086);
    HE_ASSERT(sum_squares({0})==0);
    HE_ASSERT(sum_squares({-1})==1);
    HE_ASSERT(sum_squares({-1,1,0})==2);
}

}  // namespace he_cpp_133

namespace he_cpp_134 {


TEST(HumanEvalX, CPP_134) {

    HE_ASSERT(check_if_last_char_is_a_letter("apple") == false);
    HE_ASSERT(check_if_last_char_is_a_letter("apple pi e") == true);
    HE_ASSERT(check_if_last_char_is_a_letter("eeeee") == false);
    HE_ASSERT(check_if_last_char_is_a_letter("A") == true);
    HE_ASSERT(check_if_last_char_is_a_letter("Pumpkin pie ") == false);
    HE_ASSERT(check_if_last_char_is_a_letter("Pumpkin pie 1") == false);
    HE_ASSERT(check_if_last_char_is_a_letter("") == false);
    HE_ASSERT(check_if_last_char_is_a_letter("eeeee e ") == false);
    HE_ASSERT(check_if_last_char_is_a_letter("apple pie") == false);
    HE_ASSERT(check_if_last_char_is_a_letter("apple pi e ") == false);
}

}  // namespace he_cpp_134

namespace he_cpp_135 {


TEST(HumanEvalX, CPP_135) {

    HE_ASSERT(can_arrange({1,2,4,3,5})==3);
    HE_ASSERT(can_arrange({1,2,4,5})==-1);
    HE_ASSERT(can_arrange({1,4,2,5,6,7,8,9,10})==2);
    HE_ASSERT(can_arrange({4,8,5,7,3})==4);
    HE_ASSERT(can_arrange({})==-1);
}

}  // namespace he_cpp_135

namespace he_cpp_136 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_136) {

    HE_ASSERT(issame(largest_smallest_integers({2, 4, 1, 3, 5, 7}) , {0, 1}));
    HE_ASSERT(issame(largest_smallest_integers({2, 4, 1, 3, 5, 7, 0}) , {0, 1}));
    HE_ASSERT(issame(largest_smallest_integers({1, 3, 2, 4, 5, 6, -2}) , {-2, 1}));
    HE_ASSERT(issame(largest_smallest_integers({4, 5, 3, 6, 2, 7, -7}) , {-7, 2}));
    HE_ASSERT(issame(largest_smallest_integers({7, 3, 8, 4, 9, 2, 5, -9}) , {-9, 2}));
    HE_ASSERT(issame(largest_smallest_integers({}) , {0, 0}));
    HE_ASSERT(issame(largest_smallest_integers({0}) , {0, 0}));
    HE_ASSERT(issame(largest_smallest_integers({-1, -3, -5, -6}) , {-1, 0}));
    HE_ASSERT(issame(largest_smallest_integers({-1, -3, -5, -6, 0}) , {-1, 0}));
    HE_ASSERT(issame(largest_smallest_integers({-6, -4, -4, -3, 1}) , {-3, 1}));
    HE_ASSERT(issame(largest_smallest_integers({-6, -4, -4, -3, -100, 1}) , {-3, 1}));
}

}  // namespace he_cpp_136
