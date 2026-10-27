// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_08.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_057 {


TEST(HumanEvalX, CPP_057) {

    HE_ASSERT(monotonic({1, 2, 4, 10}) == true);
    HE_ASSERT(monotonic({1, 2, 4, 20}) == true);
    HE_ASSERT(monotonic({1, 20, 4, 10}) == false);
    HE_ASSERT(monotonic({4, 1, 0, -10}) == true);
    HE_ASSERT(monotonic({4, 1, 1, 0}) == true);
    HE_ASSERT(monotonic({1, 2, 3, 2, 5, 60}) == false);
    HE_ASSERT(monotonic({1, 2, 3, 4, 5, 60}) == true);
    HE_ASSERT(monotonic({9, 9, 9, 9}) == true);
}

}  // namespace he_cpp_057

namespace he_cpp_058 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_058) {

    HE_ASSERT(issame(common({1, 4, 3, 34, 653, 2, 5}, {5, 7, 1, 5, 9, 653, 121}) , {1, 5, 653}));
    HE_ASSERT(issame(common({5, 3, 2, 8}, {3, 2}) , {2, 3}));
    HE_ASSERT(issame(common({4, 3, 2, 8}, {3, 2, 4}) , {2, 3, 4}));
    HE_ASSERT(issame(common({4, 3, 2, 8}, {}) , {}));
}

}  // namespace he_cpp_058

namespace he_cpp_059 {


TEST(HumanEvalX, CPP_059) {

    HE_ASSERT(largest_prime_factor(15) == 5);
    HE_ASSERT(largest_prime_factor(27) == 3);
    HE_ASSERT(largest_prime_factor(63) == 7);
    HE_ASSERT(largest_prime_factor(330) == 11);
    HE_ASSERT(largest_prime_factor(13195) == 29);
}

}  // namespace he_cpp_059

namespace he_cpp_060 {


TEST(HumanEvalX, CPP_060) {

    HE_ASSERT(sum_to_n(1) == 1);
    HE_ASSERT(sum_to_n(6) == 21);
    HE_ASSERT(sum_to_n(11) == 66);
    HE_ASSERT(sum_to_n(30) == 465);
    HE_ASSERT(sum_to_n(100) == 5050);
}

}  // namespace he_cpp_060

namespace he_cpp_061 {


TEST(HumanEvalX, CPP_061) {

    HE_ASSERT(correct_bracketing("()"));
    HE_ASSERT(correct_bracketing("(()())"));
    HE_ASSERT(correct_bracketing("()()(()())()"));
    HE_ASSERT(correct_bracketing("()()((()()())())(()()(()))"));
    HE_ASSERT(not (correct_bracketing("((()())))")));
    HE_ASSERT(not (correct_bracketing(")(()")));
    HE_ASSERT(not (correct_bracketing("(")));
    HE_ASSERT(not (correct_bracketing("((((")));
    HE_ASSERT(not (correct_bracketing(")")));
    HE_ASSERT(not (correct_bracketing("(()")));
    HE_ASSERT(not (correct_bracketing("()()(()())())(()")));
    HE_ASSERT(not (correct_bracketing("()()(()())()))()")));
}

}  // namespace he_cpp_061

namespace he_cpp_062 {
bool issame(vector<float> a,vector<float>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (abs(a[i]-b[i])>1e-4) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_062) {

    HE_ASSERT(issame(derivative({3, 1, 2, 4, 5}) , {1, 4, 12, 20}));
    HE_ASSERT(issame(derivative({1, 2, 3}) , {2, 6}));
    HE_ASSERT(issame(derivative({3, 2, 1}) , {2, 2}));
    HE_ASSERT(issame(derivative({3, 2, 1, 0, 4}) , {2, 2, 0, 16}));
    HE_ASSERT(issame(derivative({1}) , {}));
}

}  // namespace he_cpp_062

namespace he_cpp_063 {


TEST(HumanEvalX, CPP_063) {

    HE_ASSERT(fibfib(2) == 1);
    HE_ASSERT(fibfib(1) == 0);
    HE_ASSERT(fibfib(5) == 4);
    HE_ASSERT(fibfib(8) == 24);
    HE_ASSERT(fibfib(10) == 81);
    HE_ASSERT(fibfib(12) == 274);
    HE_ASSERT(fibfib(14) == 927);
}

}  // namespace he_cpp_063

namespace he_cpp_064 {


TEST(HumanEvalX, CPP_064) {

    HE_ASSERT(vowels_count("abcde") == 2);
    HE_ASSERT(vowels_count("Alone") == 3);
    HE_ASSERT(vowels_count("key") == 2);
    HE_ASSERT(vowels_count("bye") == 1);
    HE_ASSERT(vowels_count("keY") == 2);
    HE_ASSERT(vowels_count("bYe") == 1);
    HE_ASSERT(vowels_count("ACEDY") == 3);
}

}  // namespace he_cpp_064
