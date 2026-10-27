// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_04.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_025 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_025) {

    HE_ASSERT(issame(factorize(2) , {2}));
    HE_ASSERT(issame(factorize(4) , {2, 2}));
    HE_ASSERT(issame(factorize(8) , {2, 2, 2}));
     HE_ASSERT(issame(factorize(3 * 19) , {3, 19}));
    HE_ASSERT(issame(factorize(3 * 19 * 3 * 19) , {3, 3, 19, 19})); 
    HE_ASSERT(issame(factorize(3 * 19 * 3 * 19 * 3 * 19) , {3, 3, 3, 19, 19, 19})); 
    HE_ASSERT(issame(factorize(3 * 19 * 19 * 19) , {3, 19, 19, 19})); 
    HE_ASSERT(issame(factorize(3 * 2 * 3) , {2, 3, 3}));
}

}  // namespace he_cpp_025

namespace he_cpp_026 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_026) {

    HE_ASSERT(issame(remove_duplicates({}) , {}));
     HE_ASSERT(issame(remove_duplicates({1, 2, 3, 4}) , {1, 2, 3, 4}));
      HE_ASSERT(issame(remove_duplicates({1, 2, 3, 2, 4, 3, 5}) , {1, 4, 5}));
}

}  // namespace he_cpp_026

namespace he_cpp_027 {


TEST(HumanEvalX, CPP_027) {

    HE_ASSERT(filp_case("") == "");
    HE_ASSERT(filp_case("Hello!") == "hELLO!");
    HE_ASSERT(filp_case("These violent delights have violent ends") == "tHESE VIOLENT DELIGHTS HAVE VIOLENT ENDS");
}

}  // namespace he_cpp_027

namespace he_cpp_028 {


TEST(HumanEvalX, CPP_028) {

    HE_ASSERT(concatenate({}) == "");
     HE_ASSERT(concatenate({"x", "y", "z"}) == "xyz");
    HE_ASSERT(concatenate({"x", "y", "z", "w", "k"}) == "xyzwk");
}

}  // namespace he_cpp_028

namespace he_cpp_029 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_029) {

    HE_ASSERT(issame(filter_by_prefix({}, "john") , {}));
    HE_ASSERT(issame(filter_by_prefix({"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"}, "xxx") , {"xxx", "xxxAAA", "xxx"}));
}

}  // namespace he_cpp_029

namespace he_cpp_030 {
bool issame(vector<float> a,vector<float>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (abs(a[i]-b[i])>1e-4) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_030) {

    HE_ASSERT(issame(get_positive({-1, -2, 4, 5, 6}) , {4, 5, 6} ));
    HE_ASSERT(issame(get_positive({5, 3, -5, 2, 3, 3, 9, 0, 123, 1, -10}) , {5, 3, 2, 3, 3, 9, 123, 1}));
     HE_ASSERT(issame(get_positive({-1, -2}) , {} ));
     HE_ASSERT(issame(get_positive({}) , {}));
}

}  // namespace he_cpp_030

namespace he_cpp_031 {


TEST(HumanEvalX, CPP_031) {

    HE_ASSERT(is_prime(6) == false);
    HE_ASSERT(is_prime(101) == true);
    HE_ASSERT(is_prime(11) == true);
    HE_ASSERT(is_prime(13441) == true);
    HE_ASSERT(is_prime(61) == true);
    HE_ASSERT(is_prime(4) == false);
    HE_ASSERT(is_prime(1) == false);
    HE_ASSERT(is_prime(5) == true);
    HE_ASSERT(is_prime(11) == true);
    HE_ASSERT(is_prime(17) == true);
    HE_ASSERT(is_prime(5 * 17) == false);
    HE_ASSERT(is_prime(11 * 7) == false);
    HE_ASSERT(is_prime(13441 * 19) == false);
}

}  // namespace he_cpp_031

namespace he_cpp_032 {


TEST(HumanEvalX, CPP_032) {

   
    double solution;
    int ncoeff;
    for (int i=0;i<100;i++)
    {
        ncoeff = 2 * (1+rand()%4);
        vector<double> coeffs = {};
        for (int j=0;j<ncoeff;j++)
        {
            double coeff = -10+rand()%21;
            if (coeff == 0) coeff = 1;
            coeffs.push_back(coeff);
        }
        
        solution = find_zero(coeffs);
        HE_ASSERT(abs(poly(coeffs, solution))< 1e-3);
    }
}

}  // namespace he_cpp_032
