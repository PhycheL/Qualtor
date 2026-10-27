// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_02.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_008 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_008) {

    HE_ASSERT(issame(sum_product({}) ,{0, 1}));
    HE_ASSERT(issame(sum_product({1, 1, 1}), {3, 1}));
    HE_ASSERT(issame(sum_product({100, 0}),{100, 0}));
     HE_ASSERT(issame(sum_product({3, 5, 7}) , {3 + 5 + 7, 3 * 5 * 7}));
      HE_ASSERT(issame(sum_product({10}) ,{10, 10}));
}

}  // namespace he_cpp_008

namespace he_cpp_009 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_009) {

     HE_ASSERT(issame(rolling_max({}),{}));
    HE_ASSERT(issame(rolling_max({1, 2, 3, 4}) , {1, 2, 3, 4}));
     HE_ASSERT(issame(rolling_max({4, 3, 2, 1}),{4, 4, 4, 4}));
      HE_ASSERT(issame(rolling_max({3, 2, 3, 100, 3}) ,{3, 3, 3, 100, 100}));
}

}  // namespace he_cpp_009

namespace he_cpp_010 {


TEST(HumanEvalX, CPP_010) {

    HE_ASSERT(make_palindrome("") == "");
    HE_ASSERT(make_palindrome("x") == "x");
     HE_ASSERT(make_palindrome("xyz") == "xyzyx");
     HE_ASSERT(make_palindrome("xyx") == "xyx") ;
     HE_ASSERT(make_palindrome("jerry") == "jerryrrej");
}

}  // namespace he_cpp_010

namespace he_cpp_011 {


TEST(HumanEvalX, CPP_011) {

    HE_ASSERT(string_xor("111000", "101010") == "010010");
     HE_ASSERT(string_xor("1", "1") == "0");
    HE_ASSERT(string_xor("0101", "0000") == "0101");
}

}  // namespace he_cpp_011

namespace he_cpp_012 {


TEST(HumanEvalX, CPP_012) {

    HE_ASSERT(longest({}) == "");
    HE_ASSERT(longest({"x", "y", "z"}) == "x");
    HE_ASSERT(longest({"x", "yyy", "zzzz", "www", "kkkk", "abc"}) == "zzzz");
}

}  // namespace he_cpp_012

namespace he_cpp_013 {


TEST(HumanEvalX, CPP_013) {

    HE_ASSERT(greatest_common_divisor(3, 7) == 1);
     HE_ASSERT(greatest_common_divisor(10, 15) == 5);
      HE_ASSERT(greatest_common_divisor(49, 14) == 7);
     HE_ASSERT(greatest_common_divisor(144, 60) == 12);
}

}  // namespace he_cpp_013

namespace he_cpp_014 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_014) {

    HE_ASSERT(issame(all_prefixes(""),{}));
    HE_ASSERT(issame(all_prefixes("asdfgh") ,{"a", "as", "asd", "asdf", "asdfg", "asdfgh"}));
     HE_ASSERT(issame(all_prefixes("WWW") ,{"W", "WW", "WWW"}));
}

}  // namespace he_cpp_014

namespace he_cpp_015 {


TEST(HumanEvalX, CPP_015) {

    HE_ASSERT(string_sequence(0) == "0");
    HE_ASSERT(string_sequence(3) == "0 1 2 3");
     HE_ASSERT(string_sequence(10) == "0 1 2 3 4 5 6 7 8 9 10");
}

}  // namespace he_cpp_015
