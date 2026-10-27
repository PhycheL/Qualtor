// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_12.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_089 {


TEST(HumanEvalX, CPP_089) {

    HE_ASSERT(encrypt("hi") == "lm");
    HE_ASSERT(encrypt("asdfghjkl") == "ewhjklnop");
    HE_ASSERT(encrypt("gf") == "kj");
    HE_ASSERT(encrypt("et") == "ix");
    HE_ASSERT(encrypt("faewfawefaewg")=="jeiajeaijeiak");
    HE_ASSERT(encrypt("hellomyfriend")=="lippsqcjvmirh");
    HE_ASSERT(encrypt("dxzdlmnilfuhmilufhlihufnmlimnufhlimnufhfucufh")=="hbdhpqrmpjylqmpyjlpmlyjrqpmqryjlpmqryjljygyjl");
    HE_ASSERT(encrypt("a")=="e");
}

}  // namespace he_cpp_089

namespace he_cpp_090 {


TEST(HumanEvalX, CPP_090) {

    HE_ASSERT(next_smallest({1, 2, 3, 4, 5}) == 2);
    HE_ASSERT(next_smallest({5, 1, 4, 3, 2}) == 2);
    HE_ASSERT(next_smallest({}) == -1);
    HE_ASSERT(next_smallest({1, 1}) == -1);
    HE_ASSERT(next_smallest({1,1,1,1,0}) == 1);
    HE_ASSERT(next_smallest({-35, 34, 12, -45}) == -35);
}

}  // namespace he_cpp_090

namespace he_cpp_091 {


TEST(HumanEvalX, CPP_091) {

    HE_ASSERT(is_bored("Hello world") == 0);
    HE_ASSERT(is_bored("Is the sky blue?") == 0);
    HE_ASSERT(is_bored("I love It !") == 1);
    HE_ASSERT(is_bored("bIt") == 0);
    HE_ASSERT(is_bored("I feel good today. I will be productive. will kill It") == 2);
    HE_ASSERT(is_bored("You and I are going for a walk") == 0);
}

}  // namespace he_cpp_091

namespace he_cpp_092 {


TEST(HumanEvalX, CPP_092) {

    HE_ASSERT(any_int(2, 3, 1)==true);
    HE_ASSERT(any_int(2.5, 2, 3)==false);
    HE_ASSERT(any_int(1.5, 5, 3.5)==false);
    HE_ASSERT(any_int(2, 6, 2)==false);
    HE_ASSERT(any_int(4, 2, 2)==true);
    HE_ASSERT(any_int(2.2, 2.2, 2.2)==false);
    HE_ASSERT(any_int(-4, 6, 2)==true);
    HE_ASSERT(any_int(2,1,1)==true);
    HE_ASSERT(any_int(3,4,7)==true);
    HE_ASSERT(any_int(3.01,4,7)==false);
}

}  // namespace he_cpp_092

namespace he_cpp_093 {


TEST(HumanEvalX, CPP_093) {

    HE_ASSERT(encode("TEST") == "tgst");
    HE_ASSERT(encode("Mudasir") == "mWDCSKR");
    HE_ASSERT(encode("YES") == "ygs");
    HE_ASSERT(encode("This is a message") == "tHKS KS C MGSSCGG");
    HE_ASSERT(encode("I DoNt KnOw WhAt tO WrItE") == "k dQnT kNqW wHcT Tq wRkTg");
}

}  // namespace he_cpp_093

namespace he_cpp_094 {


TEST(HumanEvalX, CPP_094) {

    HE_ASSERT(skjkasdkd({0,3,2,1,3,5,7,4,5,5,5,2,181,32,4,32,3,2,32,324,4,3}) == 10);
    HE_ASSERT(skjkasdkd({1,0,1,8,2,4597,2,1,3,40,1,2,1,2,4,2,5,1}) == 25);
    HE_ASSERT(skjkasdkd({1,3,1,32,5107,34,83278,109,163,23,2323,32,30,1,9,3}) == 13);
    HE_ASSERT(skjkasdkd({0,724,32,71,99,32,6,0,5,91,83,0,5,6}) == 11);
    HE_ASSERT(skjkasdkd({0,81,12,3,1,21}) == 3);
    HE_ASSERT(skjkasdkd({0,8,1,2,1,7}) == 7);
    HE_ASSERT(skjkasdkd({8191}) == 19);
    HE_ASSERT(skjkasdkd({8191, 123456, 127, 7}) == 19);
    HE_ASSERT(skjkasdkd({127, 97, 8192}) == 10);
}

}  // namespace he_cpp_094

namespace he_cpp_095 {


TEST(HumanEvalX, CPP_095) {

    HE_ASSERT(check_dict_case({{"p","pineapple"}, {"b","banana"}}) == true);
    HE_ASSERT(check_dict_case({{"p","pineapple"}, {"A","banana"}, {"B","banana"}}) == false);
    HE_ASSERT(check_dict_case({{"p","pineapple"}, {"5","banana"}, {"a","apple"}}) == false);
    HE_ASSERT(check_dict_case({{"Name","John"}, {"Age","36"}, {"City","Houston"}}) == false);
    HE_ASSERT(check_dict_case({{"STATE","NC"}, {"ZIP","12345"} }) == true  );
    HE_ASSERT(check_dict_case({{"fruit","Orange"}, {"taste","Sweet"} }) == true  );
    HE_ASSERT(check_dict_case({}) == false);
}

}  // namespace he_cpp_095

namespace he_cpp_096 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_096) {

    HE_ASSERT(issame(count_up_to(5) , {2,3}));
    HE_ASSERT(issame(count_up_to(6) , {2,3,5}));
    HE_ASSERT(issame(count_up_to(7) , {2,3,5}));
    HE_ASSERT(issame(count_up_to(10) , {2,3,5,7}));
    HE_ASSERT(issame(count_up_to(0) , {}));
    HE_ASSERT(issame(count_up_to(22) , {2,3,5,7,11,13,17,19}));
    HE_ASSERT(issame(count_up_to(1) , {}));
    HE_ASSERT(issame(count_up_to(18) , {2,3,5,7,11,13,17}));
    HE_ASSERT(issame(count_up_to(47) , {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43}));
    HE_ASSERT(issame(count_up_to(101) , {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}));
}

}  // namespace he_cpp_096
