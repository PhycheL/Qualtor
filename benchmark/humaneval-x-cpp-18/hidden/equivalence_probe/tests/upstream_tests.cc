// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_18.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_138 {


TEST(HumanEvalX, CPP_138) {

    HE_ASSERT(is_equal_to_sum_even(4) == false);
    HE_ASSERT(is_equal_to_sum_even(6) == false);
    HE_ASSERT(is_equal_to_sum_even(8) == true);
    HE_ASSERT(is_equal_to_sum_even(10) == true);
    HE_ASSERT(is_equal_to_sum_even(11) == false);
    HE_ASSERT(is_equal_to_sum_even(12) == true);
    HE_ASSERT(is_equal_to_sum_even(13) == false);
    HE_ASSERT(is_equal_to_sum_even(16) == true);
}

}  // namespace he_cpp_138

namespace he_cpp_139 {


TEST(HumanEvalX, CPP_139) {

    HE_ASSERT(special_factorial(4) == 288);
    HE_ASSERT(special_factorial(5) == 34560);
    HE_ASSERT(special_factorial(7) == 125411328000);
    HE_ASSERT(special_factorial(1) == 1);
}

}  // namespace he_cpp_139

namespace he_cpp_140 {


TEST(HumanEvalX, CPP_140) {

    HE_ASSERT(fix_spaces("Example") == "Example");
    HE_ASSERT(fix_spaces("Mudasir Hanif ") == "Mudasir_Hanif_");
    HE_ASSERT(fix_spaces("Yellow Yellow  Dirty  Fellow") == "Yellow_Yellow__Dirty__Fellow");
    HE_ASSERT(fix_spaces("Exa   mple") == "Exa-mple");
    HE_ASSERT(fix_spaces("   Exa 1 2 2 mple") == "-Exa_1_2_2_mple");
}

}  // namespace he_cpp_140

namespace he_cpp_141 {


TEST(HumanEvalX, CPP_141) {

    HE_ASSERT(file_name_check("example.txt") == "Yes");
    HE_ASSERT(file_name_check("1example.dll") == "No");
    HE_ASSERT(file_name_check("s1sdf3.asd") == "No");
    HE_ASSERT(file_name_check("K.dll") == "Yes");
    HE_ASSERT(file_name_check("MY16FILE3.exe") == "Yes");
    HE_ASSERT(file_name_check("His12FILE94.exe") == "No");
    HE_ASSERT(file_name_check("_Y.txt") == "No");
    HE_ASSERT(file_name_check("?aREYA.exe") == "No");
    HE_ASSERT(file_name_check("/this_is_valid.dll") == "No");
    HE_ASSERT(file_name_check("this_is_valid.wow") == "No");
    HE_ASSERT(file_name_check("this_is_valid.txt") == "Yes");
    HE_ASSERT(file_name_check("this_is_valid.txtexe") == "No");
    HE_ASSERT(file_name_check("#this2_i4s_5valid.ten") == "No");
    HE_ASSERT(file_name_check("@this1_is6_valid.exe") == "No");
    HE_ASSERT(file_name_check("this_is_12valid.6exe4.txt") == "No");
    HE_ASSERT(file_name_check("all.exe.txt") == "No");
    HE_ASSERT(file_name_check("I563_No.exe") == "Yes");
    HE_ASSERT(file_name_check("Is3youfault.txt") == "Yes");
    HE_ASSERT(file_name_check("no_one#knows.dll") == "Yes");
    HE_ASSERT(file_name_check("1I563_Yes3.exe") == "No");
    HE_ASSERT(file_name_check("I563_Yes3.txtt") == "No");
    HE_ASSERT(file_name_check("final..txt") == "No");
    HE_ASSERT(file_name_check("final132") == "No");
    HE_ASSERT(file_name_check("_f4indsartal132.") == "No");
    HE_ASSERT(file_name_check(".txt") == "No");
    HE_ASSERT(file_name_check("s.") == "No");
}

}  // namespace he_cpp_141

namespace he_cpp_142 {


TEST(HumanEvalX, CPP_142) {

    HE_ASSERT(sum_squares({1,2,3}) == 6);
    HE_ASSERT(sum_squares({1,4,9}) == 14);
    HE_ASSERT(sum_squares({}) == 0);
    HE_ASSERT(sum_squares({1,1,1,1,1,1,1,1,1}) == 9);
    HE_ASSERT(sum_squares({-1,-1,-1,-1,-1,-1,-1,-1,-1}) == -3);
    HE_ASSERT(sum_squares({0}) == 0);
    HE_ASSERT(sum_squares({-1,-5,2,-1,-5}) == -126);
    HE_ASSERT(sum_squares({-56,-99,1,0,-2}) == 3030);
    HE_ASSERT(sum_squares({-1,0,0,0,0,0,0,0,-1}) == 0);
    HE_ASSERT(sum_squares({-16, -9, -2, 36, 36, 26, -20, 25, -40, 20, -4, 12, -26, 35, 37}) == -14196);
    HE_ASSERT(sum_squares({-1, -3, 17, -1, -15, 13, -1, 14, -14, -12, -5, 14, -14, 6, 13, 11, 16, 16, 4, 10}) == -1448);
}

}  // namespace he_cpp_142

namespace he_cpp_143 {


TEST(HumanEvalX, CPP_143) {

    HE_ASSERT(words_in_sentence("This is a test") == "is");
    HE_ASSERT(words_in_sentence("lets go for swimming") == "go for");
    HE_ASSERT(words_in_sentence("there is no place available here") == "there is no place");
    HE_ASSERT(words_in_sentence("Hi I am Hussein") == "Hi am Hussein");
    HE_ASSERT(words_in_sentence("go for it") == "go for it");
    HE_ASSERT(words_in_sentence("here") == "");
    HE_ASSERT(words_in_sentence("here is") == "is");
}

}  // namespace he_cpp_143

namespace he_cpp_144 {


TEST(HumanEvalX, CPP_144) {

    HE_ASSERT(simplify("1/5", "5/1") == true);
    HE_ASSERT(simplify("1/6", "2/1") == false);
    HE_ASSERT(simplify("5/1", "3/1") == true);
    HE_ASSERT(simplify("7/10", "10/2") == false);
    HE_ASSERT(simplify("2/10", "50/10") == true);
    HE_ASSERT(simplify("7/2", "4/2") == true);
    HE_ASSERT(simplify("11/6", "6/1") == true);
    HE_ASSERT(simplify("2/3", "5/2") == false);
    HE_ASSERT(simplify("5/2", "3/5") == false);
    HE_ASSERT(simplify("2/4", "8/4") == true);
    HE_ASSERT(simplify("2/4", "4/2") == true);
    HE_ASSERT(simplify("1/5", "5/1") == true);
    HE_ASSERT(simplify("1/5", "1/5") == false);
}

}  // namespace he_cpp_144

namespace he_cpp_145 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_145) {

    HE_ASSERT(issame(order_by_points({1, 11, -1, -11, -12}) , {-1, -11, 1, -12, 11}));
    HE_ASSERT(issame(order_by_points({1234,423,463,145,2,423,423,53,6,37,3457,3,56,0,46}) , {0, 2, 3, 6, 53, 423, 423, 423, 1234, 145, 37, 46, 56, 463, 3457}));
    HE_ASSERT(issame(order_by_points({}) , {}));
    HE_ASSERT(issame(order_by_points({1, -11, -32, 43, 54, -98, 2, -3}) , {-3, -32, -98, -11, 1, 2, 43, 54}));
    HE_ASSERT(issame(order_by_points({1,2,3,4,5,6,7,8,9,10,11}) , {1, 10, 2, 11, 3, 4, 5, 6, 7, 8, 9}));
    HE_ASSERT(issame(order_by_points({0,6,6,-76,-21,23,4}) , {-76, -21, 0, 4, 23, 6, 6}));
}

}  // namespace he_cpp_145
