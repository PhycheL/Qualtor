// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_14.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_105 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_105) {

    HE_ASSERT(issame(by_length({2, 1, 1, 4, 5, 8, 2, 3}) , {"Eight", "Five", "Four", "Three", "Two", "Two", "One", "One"}));
    HE_ASSERT(issame(by_length({}) , {}));
    HE_ASSERT(issame(by_length({1, -1 , 55}) , {"One"}));
    HE_ASSERT(issame(by_length({1, -1, 3, 2}) , {"Three", "Two", "One"}));
    HE_ASSERT(issame(by_length({9, 4, 8}) , {"Nine", "Eight", "Four"}));
}

}  // namespace he_cpp_105

namespace he_cpp_106 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_106) {

    HE_ASSERT(issame(f(5) , {1, 2, 6, 24, 15}));
    HE_ASSERT(issame(f(7) , {1, 2, 6, 24, 15, 720, 28}));
    HE_ASSERT(issame(f(1) , {1}));
    HE_ASSERT(issame(f(3) , {1, 2, 6}));
}

}  // namespace he_cpp_106

namespace he_cpp_107 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_107) {

    HE_ASSERT(issame(even_odd_palindrome(123) , {8, 13}));
    HE_ASSERT(issame(even_odd_palindrome(12) , {4, 6}));
    HE_ASSERT(issame(even_odd_palindrome(3) , {1, 2}));
    HE_ASSERT(issame(even_odd_palindrome(63) , {6, 8}));
    HE_ASSERT(issame(even_odd_palindrome(25) , {5, 6}));
    HE_ASSERT(issame(even_odd_palindrome(19) , {4, 6}));
    HE_ASSERT(issame(even_odd_palindrome(9) , {4, 5}));
    HE_ASSERT(issame(even_odd_palindrome(1) , {0, 1}));
}

}  // namespace he_cpp_107

namespace he_cpp_108 {


TEST(HumanEvalX, CPP_108) {

    HE_ASSERT(count_nums({}) == 0);
    HE_ASSERT(count_nums({-1, -2, 0}) == 0);
    HE_ASSERT(count_nums({1, 1, 2, -2, 3, 4, 5}) == 6);
    HE_ASSERT(count_nums({1, 6, 9, -6, 0, 1, 5}) == 5);
    HE_ASSERT(count_nums({1, 100, 98, -7, 1, -1}) == 4);
    HE_ASSERT(count_nums({12, 23, 34, -45, -56, 0}) == 5);
    HE_ASSERT(count_nums({-0, 1}) == 1);
    HE_ASSERT(count_nums({1}) == 1);
}

}  // namespace he_cpp_108

namespace he_cpp_109 {


TEST(HumanEvalX, CPP_109) {

    HE_ASSERT(move_one_ball({3, 4, 5, 1, 2})==true);
    HE_ASSERT(move_one_ball({3, 5, 10, 1, 2})==true);
    HE_ASSERT(move_one_ball({4, 3, 1, 2})==false);
    HE_ASSERT(move_one_ball({3, 5, 4, 1, 2})==false);
    HE_ASSERT(move_one_ball({})==true);
}

}  // namespace he_cpp_109

namespace he_cpp_110 {


TEST(HumanEvalX, CPP_110) {

    HE_ASSERT(exchange({1, 2, 3, 4}, {1, 2, 3, 4}) == "YES");
    HE_ASSERT(exchange({1, 2, 3, 4}, {1, 5, 3, 4}) == "NO");
    HE_ASSERT(exchange({1, 2, 3, 4}, {2, 1, 4, 3}) == "YES" );
    HE_ASSERT(exchange({5, 7, 3}, {2, 6, 4}) == "YES");
    HE_ASSERT(exchange({5, 7, 3}, {2, 6, 3}) == "NO" );
    HE_ASSERT(exchange({3, 2, 6, 1, 8, 9}, {3, 5, 5, 1, 1, 1}) == "NO");
    HE_ASSERT(exchange({100, 200}, {200, 200}) == "YES");
}

}  // namespace he_cpp_110

namespace he_cpp_111 {
bool issame(map<char,int> a,map<char,int> b){
    if (a.size()!=b.size()) return false;
    map <char,int>::iterator it;
    for (it=a.begin();it!=a.end();it++)
    {
        char w1=it->first;
        int w2=it->second;
        if (b.find(w1)==b.end()) return false;
        if (b[w1]!=w2) return false;
    }

    return true;
}

TEST(HumanEvalX, CPP_111) {

    HE_ASSERT(issame(histogram("a b b a") , {{'a',2},{'b', 2}}));
    HE_ASSERT(issame(histogram("a b c a b") , {{'a', 2},{'b', 2}}));
    HE_ASSERT(issame(histogram("a b c d g") , {{'a', 1}, {'b', 1}, {'c', 1}, {'d', 1}, {'g', 1}}));
    HE_ASSERT(issame(histogram("r t g") , {{'r', 1},{'t', 1},{'g', 1}}));
    HE_ASSERT(issame(histogram("b b b b a") , {{'b', 4}}));
    HE_ASSERT(issame(histogram("r t g") , {{'r', 1},{'t', 1},{'g', 1}}));
    HE_ASSERT(issame(histogram("") , {}));
    HE_ASSERT(issame(histogram("a") , {{'a', 1}}));
}

}  // namespace he_cpp_111

namespace he_cpp_112 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_112) {

    HE_ASSERT(issame(reverse_delete("abcde","ae") , {"bcd","False"}));
    HE_ASSERT(issame(reverse_delete("abcdef", "b") , {"acdef","False"}));
    HE_ASSERT(issame(reverse_delete("abcdedcba","ab") , {"cdedc","True"}));
    HE_ASSERT(issame(reverse_delete("dwik","w") , {"dik","False"}));
    HE_ASSERT(issame(reverse_delete("a","a") , {"","True"}));
    HE_ASSERT(issame(reverse_delete("abcdedcba","") , {"abcdedcba","True"}));
    HE_ASSERT(issame(reverse_delete("abcdedcba","v") , {"abcdedcba","True"}));
    HE_ASSERT(issame(reverse_delete("vabba","v") , {"abba","True"}));
    HE_ASSERT(issame(reverse_delete("mamma", "mia") , {"", "True"}));
}

}  // namespace he_cpp_112
