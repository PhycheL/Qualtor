// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_11.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_081 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_081) {

    HE_ASSERT(issame(numerical_letter_grade({4.0, 3, 1.7, 2, 3.5}) , {"A+", "B", "C-", "C", "A-"}));
    HE_ASSERT(issame(numerical_letter_grade({1.2}) , {"D+"}));
    HE_ASSERT(issame(numerical_letter_grade({0.5}) , {"D-"}));
    HE_ASSERT(issame(numerical_letter_grade({0.0}) , {"E"}));
    HE_ASSERT(issame(numerical_letter_grade({1, 0.3, 1.5, 2.8, 3.3}) , {"D", "D-", "C-", "B", "B+"}));
    HE_ASSERT(issame(numerical_letter_grade({0, 0.7}) , {"E", "D-"}));
}

}  // namespace he_cpp_081

namespace he_cpp_082 {


TEST(HumanEvalX, CPP_082) {

    HE_ASSERT(prime_length("Hello") == true);
    HE_ASSERT(prime_length("abcdcba") == true);
    HE_ASSERT(prime_length("kittens") == true);
    HE_ASSERT(prime_length("orange") == false);
    HE_ASSERT(prime_length("wow") == true);
    HE_ASSERT(prime_length("world") == true);
    HE_ASSERT(prime_length("MadaM") == true);
    HE_ASSERT(prime_length("Wow") == true);
    HE_ASSERT(prime_length("") == false);
    HE_ASSERT(prime_length("HI") == true);
    HE_ASSERT(prime_length("go") == true);
    HE_ASSERT(prime_length("gogo") == false);
    HE_ASSERT(prime_length("aaaaaaaaaaaaaaa") == false);
    HE_ASSERT(prime_length("Madam") == true);
    HE_ASSERT(prime_length("M") == false);
    HE_ASSERT(prime_length("0") == false);
}

}  // namespace he_cpp_082

namespace he_cpp_083 {


TEST(HumanEvalX, CPP_083) {

    HE_ASSERT(starts_one_ends(1) == 1);
    HE_ASSERT(starts_one_ends(2) == 18);
    HE_ASSERT(starts_one_ends(3) == 180);
    HE_ASSERT(starts_one_ends(4) == 1800);
    HE_ASSERT(starts_one_ends(5) == 18000);
}

}  // namespace he_cpp_083

namespace he_cpp_084 {


TEST(HumanEvalX, CPP_084) {

    HE_ASSERT(solve(1000) == "1");
    HE_ASSERT(solve(150) == "110");
    HE_ASSERT(solve(147) == "1100");
    HE_ASSERT(solve(333) == "1001");
    HE_ASSERT(solve(963) == "10010");
}

}  // namespace he_cpp_084

namespace he_cpp_085 {


TEST(HumanEvalX, CPP_085) {

    HE_ASSERT(add({4, 88}) == 88);
    HE_ASSERT(add({4, 5, 6, 7, 2, 122}) == 122);
    HE_ASSERT(add({4, 0, 6, 7}) == 0);
    HE_ASSERT(add({4, 4, 6, 8}) == 12);
}

}  // namespace he_cpp_085

namespace he_cpp_086 {


TEST(HumanEvalX, CPP_086) {

    HE_ASSERT(anti_shuffle("Hi") == "Hi");
    HE_ASSERT(anti_shuffle("hello") == "ehllo");
    HE_ASSERT(anti_shuffle("number") == "bemnru");
    HE_ASSERT(anti_shuffle("abcd") == "abcd");
    HE_ASSERT(anti_shuffle("Hello World!!!") == "Hello !!!Wdlor");
    HE_ASSERT(anti_shuffle("") == "");
    HE_ASSERT(anti_shuffle("Hi. My name is Mister Robot. How are you?") == ".Hi My aemn is Meirst .Rboot How aer ?ouy");
}

}  // namespace he_cpp_086

namespace he_cpp_087 {
bool issame(vector<vector<int>> a,vector<vector<int>> b){
    if (a.size()!=b.size()) return false;

    for (int i=0;i<a.size();i++)
    {
        if (a[i].size()!=b[i].size()) return false;
        for (int j=0;j<a[i].size();j++)
            if (a[i][j]!=b[i][j]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_087) {

    HE_ASSERT(issame(get_row({
        {1,2,3,4,5,6},
        {1,2,3,4,1,6},
        {1,2,3,4,5,1}}, 1) , {{0, 0}, {1, 4}, {1, 0}, {2, 5}, {2, 0}}));
    HE_ASSERT(issame(get_row({
        {1,2,3,4,5,6},
        {1,2,3,4,5,6},
        {1,2,3,4,5,6},
        {1,2,3,4,5,6},
        {1,2,3,4,5,6},
        {1,2,3,4,5,6}}, 2) , {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}}));
    HE_ASSERT(issame(get_row({
        {1,2,3,4,5,6},
        {1,2,3,4,5,6},
        {1,1,3,4,5,6},
        {1,2,1,4,5,6},
        {1,2,3,1,5,6},
        {1,2,3,4,1,6},
        {1,2,3,4,5,1}
    }, 1) , {{0, 0}, {1, 0}, {2, 1}, {2, 0}, {3, 2}, {3, 0}, {4, 3}, {4, 0}, {5, 4}, {5, 0}, {6, 5}, {6, 0}}));
    HE_ASSERT(issame(get_row({}, 1) , {}));
    HE_ASSERT(issame(get_row({{1}}, 2) , {}));
    HE_ASSERT(issame(get_row({{}, {1}, {1, 2, 3}}, 3) , {{2, 2}}));
}

}  // namespace he_cpp_087

namespace he_cpp_088 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_088) {

    HE_ASSERT(issame(sort_array({}) , {}));
    HE_ASSERT(issame(sort_array({5}) , {5}));
    HE_ASSERT(issame(sort_array({2, 4, 3, 0, 1, 5}) , {0, 1, 2, 3, 4, 5}));
    HE_ASSERT(issame(sort_array({2, 4, 3, 0, 1, 5, 6}) , {6, 5, 4, 3, 2, 1, 0}));
    HE_ASSERT(issame(sort_array({2, 1}) , {1, 2}));
    HE_ASSERT(issame(sort_array({15, 42, 87, 32 ,11, 0}) , {0, 11, 15, 32, 42, 87}));
    HE_ASSERT(issame(sort_array({21, 14, 23, 11}) , {23, 21, 14, 11}));
}

}  // namespace he_cpp_088
