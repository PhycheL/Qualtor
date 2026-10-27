// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_01.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_000 {


TEST(HumanEvalX, CPP_000) {

    vector<float> a={1.0, 2.0, 3.9, 4.0, 5.0, 2.2};
    HE_ASSERT(has_close_elements(a, 0.3)==true);
    HE_ASSERT(has_close_elements(a, 0.05) == false);

    HE_ASSERT(has_close_elements({1.0, 2.0, 5.9, 4.0, 5.0}, 0.95) == true);
    HE_ASSERT(has_close_elements({1.0, 2.0, 5.9, 4.0, 5.0}, 0.8) ==false);
    HE_ASSERT(has_close_elements({1.0, 2.0, 3.0, 4.0, 5.0}, 2.0) == true);
    HE_ASSERT(has_close_elements({1.1, 2.2, 3.1, 4.1, 5.1}, 1.0) == true);
    HE_ASSERT(has_close_elements({1.1, 2.2, 3.1, 4.1, 5.1}, 0.5) == false);
}

}  // namespace he_cpp_000

namespace he_cpp_001 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_001) {
  
    HE_ASSERT(issame(separate_paren_groups("(()()) ((())) () ((())()())"),{"(()())", "((()))", "()", "((())()())"}));
    HE_ASSERT(issame(separate_paren_groups("() (()) ((())) (((())))"), {"()", "(())", "((()))", "(((())))" }));
    HE_ASSERT(issame(separate_paren_groups("(()(())((())))") ,{ "(()(())((())))" }));
    HE_ASSERT(issame(separate_paren_groups("( ) (( )) (( )( ))") ,{"()", "(())", "(()())"}));
}

}  // namespace he_cpp_001

namespace he_cpp_002 {


TEST(HumanEvalX, CPP_002) {

 HE_ASSERT(truncate_number(3.5) == 0.5); 
 HE_ASSERT(abs(truncate_number(1.33) - 0.33) < 1e-4);
  HE_ASSERT(abs(truncate_number(123.456) - 0.456) < 1e-4);
}

}  // namespace he_cpp_002

namespace he_cpp_003 {


TEST(HumanEvalX, CPP_003) {

    HE_ASSERT(below_zero({}) == false);
    HE_ASSERT(below_zero({1, 2, -3, 1, 2, -3}) == false);
    HE_ASSERT(below_zero({1, 2, -4, 5, 6}) == true);
    HE_ASSERT(below_zero({1, -1, 2, -2, 5, -5, 4, -4}) == false);
    HE_ASSERT(below_zero({1, -1, 2, -2, 5, -5, 4, -5}) == true);
    HE_ASSERT(below_zero({1, -2, 2, -2, 5, -5, 4, -4}) == true);
}

}  // namespace he_cpp_003

namespace he_cpp_004 {


TEST(HumanEvalX, CPP_004) {

    HE_ASSERT(abs(mean_absolute_deviation({1.0, 2.0, 3.0}) - 2.0/3.0) < 1e-4);
    HE_ASSERT(abs(mean_absolute_deviation({1.0, 2.0, 3.0, 4.0}) - 1.0) < 1e-4);
    HE_ASSERT(abs(mean_absolute_deviation({1.0, 2.0, 3.0, 4.0, 5.0}) - 6.0/5.0) < 1e-4);
}

}  // namespace he_cpp_004

namespace he_cpp_005 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_005) {

    HE_ASSERT(issame(intersperse({}, 7), {}));
    
    HE_ASSERT(issame(intersperse({5, 6, 3, 2}, 8),{5, 8, 6, 8, 3, 8, 2}));
    HE_ASSERT(issame(intersperse({2, 2, 2}, 2),{2, 2, 2, 2, 2}));
}

}  // namespace he_cpp_005

namespace he_cpp_006 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_006) {

    HE_ASSERT(issame(parse_nested_parens("(()()) ((())) () ((())()())"),{2, 3, 1, 3}));
     HE_ASSERT(issame(parse_nested_parens("() (()) ((())) (((())))") , {1, 2, 3, 4}));
    HE_ASSERT(issame(parse_nested_parens("(()(())((())))") ,{4}));
}

}  // namespace he_cpp_006

namespace he_cpp_007 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_007) {

    HE_ASSERT(issame(filter_by_substring({}, "john"),{}));
     HE_ASSERT(issame(filter_by_substring({"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"}, "xxx"), {"xxx", "xxxAAA", "xxx"}));
    HE_ASSERT(issame(filter_by_substring({"xxx", "asd", "aaaxxy", "john doe", "xxxAAA", "xxx"}, "xx"),{"xxx", "aaaxxy", "xxxAAA", "xxx"}));
     HE_ASSERT(issame(filter_by_substring({"grunt", "trumpet", "prune", "gruesome"}, "run") ,{"grunt", "prune"}));
}

}  // namespace he_cpp_007
