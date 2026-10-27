// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_05.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_033 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_033) {

    HE_ASSERT(issame(sort_third({1, 2, 3}) , sort_third({1, 2, 3})));
    HE_ASSERT(issame(sort_third({5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10}) , sort_third({5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10})));
    HE_ASSERT(issame(sort_third({5, 8, -12, 4, 23, 2, 3, 11, 12, -10}) , sort_third({5, 8, -12, 4, 23, 2, 3, 11, 12, -10})));
    HE_ASSERT(issame(sort_third({5, 6, 3, 4, 8, 9, 2}) , {2, 6, 3, 4, 8, 9, 5}));
    HE_ASSERT(issame(sort_third({5, 8, 3, 4, 6, 9, 2}) , {2, 8, 3, 4, 6, 9, 5}));
    HE_ASSERT(issame(sort_third({5, 6, 9, 4, 8, 3, 2}) , {2, 6, 9, 4, 8, 3, 5}));
    HE_ASSERT(issame(sort_third({5, 6, 3, 4, 8, 9, 2, 1}) , {2, 6, 3, 4, 8, 9, 5, 1}));
}

}  // namespace he_cpp_033

namespace he_cpp_034 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_034) {

    HE_ASSERT(issame(unique({5, 3, 5, 2, 3, 3, 9, 0, 123}) , {0, 2, 3, 5, 9, 123}));
}

}  // namespace he_cpp_034

namespace he_cpp_035 {


TEST(HumanEvalX, CPP_035) {

    HE_ASSERT(abs(max_element({1, 2, 3})- 3)<1e-4);
    HE_ASSERT(abs(max_element({5, 3, -5, 2, -3, 3, 9, 0, 124, 1, -10})- 124)<1e-4);
}

}  // namespace he_cpp_035

namespace he_cpp_036 {


TEST(HumanEvalX, CPP_036) {

    HE_ASSERT(fizz_buzz(50) == 0);
    HE_ASSERT(fizz_buzz(78) == 2);
    HE_ASSERT(fizz_buzz(79) == 3);
    HE_ASSERT(fizz_buzz(100) == 3);
    HE_ASSERT(fizz_buzz(200) == 6);
    HE_ASSERT(fizz_buzz(4000) == 192);
    HE_ASSERT(fizz_buzz(10000) == 639);
    HE_ASSERT(fizz_buzz(100000) == 8026);
}

}  // namespace he_cpp_036

namespace he_cpp_037 {
bool issame(vector<float> a,vector<float>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (abs(a[i]-b[i])>1e-4) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_037) {

    HE_ASSERT(issame(sort_even({1, 2, 3}), {1, 2, 3}));
    HE_ASSERT(issame(sort_even({5, 3, -5, 2, -3, 3, 9, 0, 123, 1, -10}) , {-10, 3, -5, 2, -3, 3, 5, 0, 9, 1, 123}));
    HE_ASSERT(issame(sort_even({5, 8, -12, 4, 23, 2, 3, 11, 12, -10}) , {-12, 8, 3, 4, 5, 2, 12, 11, 23, -10}));
}

}  // namespace he_cpp_037

namespace he_cpp_038 {


TEST(HumanEvalX, CPP_038) {

    
    for (int i=0;i<100;i++)
    {
        int l=10+rand()%11;
        string str="";
        for (int j=0;j<l;j++)
        {
            char chr=97+rand()%26;
            str+=chr;
        }

        string encoded_str = encode_cyclic(str);
        HE_ASSERT(decode_cyclic(encoded_str) == str);
    }
}

}  // namespace he_cpp_038

namespace he_cpp_039 {


TEST(HumanEvalX, CPP_039) {

    HE_ASSERT(prime_fib(1) == 2);
    HE_ASSERT(prime_fib(2) == 3);
    HE_ASSERT(prime_fib(3) == 5);
    HE_ASSERT(prime_fib(4) == 13);
    HE_ASSERT(prime_fib(5) == 89);
    HE_ASSERT(prime_fib(6) == 233);
    HE_ASSERT(prime_fib(7) == 1597);
    HE_ASSERT(prime_fib(8) == 28657);
    HE_ASSERT(prime_fib(9) == 514229);
    HE_ASSERT(prime_fib(10) == 433494437);
}

}  // namespace he_cpp_039

namespace he_cpp_040 {


TEST(HumanEvalX, CPP_040) {

    HE_ASSERT(triples_sum_to_zero({1, 3, 5, 0}) == false);
    HE_ASSERT(triples_sum_to_zero({1, 3, 5, -1}) == false);
    HE_ASSERT(triples_sum_to_zero({1, 3, -2, 1}) == true);
    HE_ASSERT(triples_sum_to_zero({1, 2, 3, 7}) == false);
    HE_ASSERT(triples_sum_to_zero({1, 2, 5, 7}) == false);
    HE_ASSERT(triples_sum_to_zero({2, 4, -5, 3, 9, 7}) == true);
    HE_ASSERT(triples_sum_to_zero({1}) == false);
    HE_ASSERT(triples_sum_to_zero({1, 3, 5, -100}) == false);
    HE_ASSERT(triples_sum_to_zero({100, 3, 5, -100}) == false);
}

}  // namespace he_cpp_040
