// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_20.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_154 {


TEST(HumanEvalX, CPP_154) {

    HE_ASSERT(cycpattern_check("xyzw","xyw") == false );
    HE_ASSERT(cycpattern_check("yello","ell") == true );
    HE_ASSERT(cycpattern_check("whattup","ptut") == false );
    HE_ASSERT(cycpattern_check("efef","fee") == true );
    HE_ASSERT(cycpattern_check("abab","aabb") == false );
    HE_ASSERT(cycpattern_check("winemtt","tinem") == true );
}

}  // namespace he_cpp_154

namespace he_cpp_155 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_155) {

    HE_ASSERT(issame(even_odd_count(7) , {0, 1}));
    HE_ASSERT(issame(even_odd_count(-78) , {1, 1}));
    HE_ASSERT(issame(even_odd_count(3452) , {2, 2}));
    HE_ASSERT(issame(even_odd_count(346211) , {3, 3}));
    HE_ASSERT(issame(even_odd_count(-345821) , {3, 3}));
    HE_ASSERT(issame(even_odd_count(-2) , {1, 0}));
    HE_ASSERT(issame(even_odd_count(-45347) , {2, 3}));
    HE_ASSERT(issame(even_odd_count(0) , {1, 0}));
}

}  // namespace he_cpp_155

namespace he_cpp_156 {


TEST(HumanEvalX, CPP_156) {

    HE_ASSERT(int_to_mini_romank(19) == "xix");
    HE_ASSERT(int_to_mini_romank(152) == "clii");
    HE_ASSERT(int_to_mini_romank(251) == "ccli");
    HE_ASSERT(int_to_mini_romank(426) == "cdxxvi");
    HE_ASSERT(int_to_mini_romank(500) == "d");
    HE_ASSERT(int_to_mini_romank(1) == "i");
    HE_ASSERT(int_to_mini_romank(4) == "iv");
    HE_ASSERT(int_to_mini_romank(43) == "xliii");
    HE_ASSERT(int_to_mini_romank(90) == "xc");
    HE_ASSERT(int_to_mini_romank(94) == "xciv");
    HE_ASSERT(int_to_mini_romank(532) == "dxxxii");
    HE_ASSERT(int_to_mini_romank(900) == "cm");
    HE_ASSERT(int_to_mini_romank(994) == "cmxciv");
    HE_ASSERT(int_to_mini_romank(1000) == "m");
}

}  // namespace he_cpp_156

namespace he_cpp_157 {


TEST(HumanEvalX, CPP_157) {

    HE_ASSERT(right_angle_triangle(3, 4, 5) == true);
    HE_ASSERT(right_angle_triangle(1, 2, 3) == false);
    HE_ASSERT(right_angle_triangle(10, 6, 8) == true);
    HE_ASSERT(right_angle_triangle(2, 2, 2) == false);
    HE_ASSERT(right_angle_triangle(7, 24, 25) == true);
    HE_ASSERT(right_angle_triangle(10, 5, 7) == false);
    HE_ASSERT(right_angle_triangle(5, 12, 13) == true);
    HE_ASSERT(right_angle_triangle(15, 8, 17) == true);
    HE_ASSERT(right_angle_triangle(48, 55, 73) == true);
    HE_ASSERT(right_angle_triangle(1, 1, 1) == false);
    HE_ASSERT(right_angle_triangle(2, 2, 10) == false);
}

}  // namespace he_cpp_157

namespace he_cpp_158 {


TEST(HumanEvalX, CPP_158) {

    HE_ASSERT((find_max({"name", "of", "string"}) == "string"));
    HE_ASSERT((find_max({"name", "enam", "game"}) == "enam"));
    HE_ASSERT((find_max({"aaaaaaa", "bb", "cc"}) == "aaaaaaa"));
    HE_ASSERT((find_max({"abc", "cba"}) == "abc"));
    HE_ASSERT((find_max({"play", "this", "game", "of","footbott"}) == "footbott"));
    HE_ASSERT((find_max({"we", "are", "gonna", "rock"}) == "gonna"));
    HE_ASSERT((find_max({"we", "are", "a", "mad", "nation"}) == "nation"));
    HE_ASSERT((find_max({"this", "is", "a", "prrk"}) == "this"));
    HE_ASSERT((find_max({"b"}) == "b"));
    HE_ASSERT((find_max({"play", "play", "play"}) == "play"));
}

}  // namespace he_cpp_158

namespace he_cpp_159 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_159) {

    HE_ASSERT(issame(eat(5, 6, 10) , {11, 4}));
    HE_ASSERT(issame(eat(4, 8, 9) , {12, 1}));
    HE_ASSERT(issame(eat(1, 10, 10) , {11, 0}));
    HE_ASSERT(issame(eat(2, 11, 5) , {7, 0}));
    
    HE_ASSERT(issame(eat(4, 5, 7) , {9, 2}));
    HE_ASSERT(issame(eat(4, 5, 1) , {5, 0}));
}

}  // namespace he_cpp_159

namespace he_cpp_160 {


TEST(HumanEvalX, CPP_160) {

    HE_ASSERT(do_algebra({"**", "*", "+"}, {2, 3, 4, 5}) == 37);
    HE_ASSERT(do_algebra({"+", "*", "-"}, {2, 3, 4, 5}) == 9);
    HE_ASSERT(do_algebra({"//", "*"}, {7, 3, 4}) == 8);
}

}  // namespace he_cpp_160

namespace he_cpp_161 {


TEST(HumanEvalX, CPP_161) {

    HE_ASSERT(solve("AsDf") == "aSdF");
    HE_ASSERT(solve("1234") == "4321");
    HE_ASSERT(solve("ab") == "AB");
    HE_ASSERT(solve("#a@C") == "#A@c");
    HE_ASSERT(solve("#AsdfW^45") == "#aSDFw^45");
    HE_ASSERT(solve("#6@2") == "2@6#");
    HE_ASSERT(solve("#$a^D") == "#$A^d");
    HE_ASSERT(solve("#ccc") == "#CCC");
}

}  // namespace he_cpp_161

namespace he_cpp_163 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_163) {

    HE_ASSERT(issame(generate_integers(2, 10) , {2, 4, 6, 8}));
    HE_ASSERT(issame(generate_integers(10, 2) , {2, 4, 6, 8}));
    HE_ASSERT(issame(generate_integers(132, 2) , {2, 4, 6, 8}));
    HE_ASSERT(issame(generate_integers(17,89) , {}));
}

}  // namespace he_cpp_163
