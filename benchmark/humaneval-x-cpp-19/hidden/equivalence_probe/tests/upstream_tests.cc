// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_19.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_146 {


TEST(HumanEvalX, CPP_146) {

    HE_ASSERT(specialFilter({5, -2, 1, -5}) == 0  );
    HE_ASSERT(specialFilter({15, -73, 14, -15}) == 1);
    HE_ASSERT(specialFilter({33, -2, -3, 45, 21, 109}) == 2);
    HE_ASSERT(specialFilter({43, -12, 93, 125, 121, 109}) == 4);
    HE_ASSERT(specialFilter({71, -2, -33, 75, 21, 19}) == 3);
    HE_ASSERT(specialFilter({1}) == 0              );
    HE_ASSERT(specialFilter({}) == 0                   );
}

}  // namespace he_cpp_146

namespace he_cpp_147 {


TEST(HumanEvalX, CPP_147) {

    HE_ASSERT(get_matrix_triples(5) == 1);
    HE_ASSERT(get_matrix_triples(6) == 4);
    HE_ASSERT(get_matrix_triples(10) == 36);
    HE_ASSERT(get_matrix_triples(100) == 53361);
}

}  // namespace he_cpp_147

namespace he_cpp_148 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_148) {

    HE_ASSERT(issame(bf("Jupiter", "Neptune") , {"Saturn", "Uranus"}));
    HE_ASSERT(issame(bf("Earth", "Mercury") , {"Venus",}));
    HE_ASSERT(issame(bf("Mercury", "Uranus") , {"Venus", "Earth", "Mars", "Jupiter", "Saturn"}));
    HE_ASSERT(issame(bf("Neptune", "Venus") , {"Earth", "Mars", "Jupiter", "Saturn", "Uranus"}));
    HE_ASSERT(issame(bf("Earth", "Earth") , {}));
    HE_ASSERT(issame(bf("Mars", "Earth") , {}));
    HE_ASSERT(issame(bf("Jupiter", "Makemake") , {}));
}

}  // namespace he_cpp_148

namespace he_cpp_149 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_149) {

    HE_ASSERT(issame(sorted_list_sum({"aa", "a", "aaa"}) , {"aa"}));
    HE_ASSERT(issame(sorted_list_sum({"school", "AI", "asdf", "b"}) , {"AI", "asdf", "school"}));
    HE_ASSERT(issame(sorted_list_sum({"d", "b", "c", "a"}) , {}));
    HE_ASSERT(issame(sorted_list_sum({"d", "dcba", "abcd", "a"}) , {"abcd", "dcba"}));
    HE_ASSERT(issame(sorted_list_sum({"AI", "ai", "au"}) , {"AI", "ai", "au"}));
    HE_ASSERT(issame(sorted_list_sum({"a", "b", "b", "c", "c", "a"}) , {}));
    HE_ASSERT(issame(sorted_list_sum({"aaaa", "bbbb", "dd", "cc"}) , {"cc", "dd", "aaaa", "bbbb"}));
}

}  // namespace he_cpp_149

namespace he_cpp_150 {


TEST(HumanEvalX, CPP_150) {

    HE_ASSERT(x_or_y(7, 34, 12) == 34);
    HE_ASSERT(x_or_y(15, 8, 5) == 5);
    HE_ASSERT(x_or_y(3, 33, 5212) == 33);
    HE_ASSERT(x_or_y(1259, 3, 52) == 3);
    HE_ASSERT(x_or_y(7919, -1, 12) == -1);
    HE_ASSERT(x_or_y(3609, 1245, 583) == 583);
    HE_ASSERT(x_or_y(91, 56, 129) == 129);
    HE_ASSERT(x_or_y(6, 34, 1234) == 1234);
    HE_ASSERT(x_or_y(1, 2, 0) == 0);
    HE_ASSERT(x_or_y(2, 2, 0) == 2);
}

}  // namespace he_cpp_150

namespace he_cpp_151 {


TEST(HumanEvalX, CPP_151) {

    HE_ASSERT(double_the_difference({}) == 0);
    HE_ASSERT(double_the_difference({5, 4}) == 25);
    HE_ASSERT(double_the_difference({0.1, 0.2, 0.3}) == 0 );
    HE_ASSERT(double_the_difference({-10, -20, -30}) == 0 );
    HE_ASSERT(double_the_difference({-1, -2, 8}) == 0);
    HE_ASSERT(double_the_difference({0.2, 3, 5}) == 34);
    
    
    long long odd_sum=0;
    vector<float> lst={};

    for (int i=-99;i<100;i+=2)
    {
        lst.push_back(i+0.0);
        if (i>0 and i%2==1) odd_sum+=i*i;
    }
  
    HE_ASSERT(double_the_difference(lst) == odd_sum );
}

}  // namespace he_cpp_151

namespace he_cpp_152 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_152) {

    HE_ASSERT(issame(compare({1,2,3,4,5,1},{1,2,3,4,2,-2}),{0,0,0,0,3,3}));
    HE_ASSERT(issame(compare({0,5,0,0,0,4},{4,1,1,0,0,-2}),{4,4,1,0,0,6}));
    HE_ASSERT(issame(compare({1,2,3,4,5,1},{1,2,3,4,2,-2}),{0,0,0,0,3,3}));
    HE_ASSERT(issame(compare({0,0,0,0,0,0},{0,0,0,0,0,0}),{0,0,0,0,0,0}));
    HE_ASSERT(issame(compare({1,2,3},{-1,-2,-3}),{2,4,6}));
    HE_ASSERT(issame(compare({1,2,3,5},{-1,2,3,4}),{2,0,0,1}));
}

}  // namespace he_cpp_152

namespace he_cpp_153 {


TEST(HumanEvalX, CPP_153) {

    HE_ASSERT(Strongest_Extension("Watashi", {"tEN", "niNE", "eIGHt8OKe"}) == "Watashi.eIGHt8OKe");
    HE_ASSERT(Strongest_Extension("Boku123", {"nani", "NazeDa", "YEs.WeCaNe", "32145tggg"}) == "Boku123.YEs.WeCaNe");
    HE_ASSERT(Strongest_Extension("__YESIMHERE", {"t", "eMptY", "(nothing", "zeR00", "NuLl__", "123NoooneB321"}) == "__YESIMHERE.NuLl__");
    HE_ASSERT(Strongest_Extension("K", {"Ta", "TAR", "t234An", "cosSo"}) == "K.TAR");
    HE_ASSERT(Strongest_Extension("__HAHA", {"Tab", "123", "781345", "-_-"}) == "__HAHA.123");
    HE_ASSERT(Strongest_Extension("YameRore", {"HhAas", "okIWILL123", "WorkOut", "Fails", "-_-"}) == "YameRore.okIWILL123");
    HE_ASSERT(Strongest_Extension("finNNalLLly", {"Die", "NowW", "Wow", "WoW"}) == "finNNalLLly.WoW");
    HE_ASSERT(Strongest_Extension("_", {"Bb", "91245"}) == "_.Bb");
    HE_ASSERT(Strongest_Extension("Sp", {"671235", "Bb"}) == "Sp.671235");
}

}  // namespace he_cpp_153
