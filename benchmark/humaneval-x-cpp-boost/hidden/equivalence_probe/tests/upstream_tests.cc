#include "functions.h"
#include <gtest/gtest.h>
#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))
namespace he_cpp_022 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_022) {

    HE_ASSERT(issame(filter_integers({}),{}));

    HE_ASSERT(issame(filter_integers({4,  {},23.2, 9, string("adasd")}) ,{4, 9}));
    HE_ASSERT(issame(filter_integers({3, 'c', 3, 3, 'a', 'b'}) ,{3, 3, 3}));
}

}  // namespace he_cpp_022

namespace he_cpp_137 {


TEST(HumanEvalX, CPP_137) {

    HE_ASSERT(boost::any_cast<int>(compare_one(1, 2)) == 2);
    HE_ASSERT(boost::any_cast<double>(compare_one(1, 2.5))== 2.5);
    HE_ASSERT(boost::any_cast<int>(compare_one(2, 3)) == 3);
    HE_ASSERT(boost::any_cast<int>(compare_one(5, 6)) == 6);
    HE_ASSERT(boost::any_cast<string>(compare_one(1, string("2,3")))== "2,3");
    HE_ASSERT(boost::any_cast<string>(compare_one(string("5,1"), string("6"))) == "6");
    HE_ASSERT(boost::any_cast<string>(compare_one(string("1"), string("2"))) == "2");
    HE_ASSERT(boost::any_cast<string>(compare_one(string("1"), 1)) == "None");
}

}  // namespace he_cpp_137
