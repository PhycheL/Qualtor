// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_13.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_097 {


TEST(HumanEvalX, CPP_097) {

    HE_ASSERT(multiply(148, 412) == 16                   );
    HE_ASSERT(multiply(19, 28) == 72       );
    HE_ASSERT(multiply(2020, 1851) == 0);
    HE_ASSERT(multiply(14,-15) == 20   );
    HE_ASSERT(multiply(76, 67) == 42    );
    HE_ASSERT(multiply(17, 27) == 49    );
    HE_ASSERT(multiply(0, 1) == 0);
    HE_ASSERT(multiply(0, 0) == 0);
}

}  // namespace he_cpp_097

namespace he_cpp_098 {


TEST(HumanEvalX, CPP_098) {

    HE_ASSERT(count_upper("aBCdEf")  == 1);
    HE_ASSERT(count_upper("abcdefg") == 0);
    HE_ASSERT(count_upper("dBBE") == 0);
    HE_ASSERT(count_upper("B")  == 0);
    HE_ASSERT(count_upper("U")  == 1);
    HE_ASSERT(count_upper("") == 0);
    HE_ASSERT(count_upper("EEEE") == 2);
}

}  // namespace he_cpp_098

namespace he_cpp_099 {


TEST(HumanEvalX, CPP_099) {

    HE_ASSERT(closest_integer("10") == 10);
    HE_ASSERT(closest_integer("14.5") == 15);
    HE_ASSERT(closest_integer("-15.5") == -16);
    HE_ASSERT(closest_integer("15.3") == 15);
    HE_ASSERT(closest_integer("0") == 0);
}

}  // namespace he_cpp_099

namespace he_cpp_100 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_100) {

    HE_ASSERT(issame(make_a_pile(3) , {3, 5, 7}));
    HE_ASSERT(issame(make_a_pile(4) , {4,6,8,10}));
    HE_ASSERT(issame(make_a_pile(5) , {5, 7, 9, 11, 13}));
    HE_ASSERT(issame(make_a_pile(6) , {6, 8, 10, 12, 14, 16}));
    HE_ASSERT(issame(make_a_pile(8) , {8, 10, 12, 14, 16, 18, 20, 22}));
}

}  // namespace he_cpp_100

namespace he_cpp_101 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_101) {

    HE_ASSERT(issame(words_string("Hi, my name is John") , {"Hi", "my", "name", "is", "John"}));
    HE_ASSERT(issame(words_string("One, two, three, four, five, six") , {"One", "two", "three", "four", "five", "six"}));
    HE_ASSERT(issame(words_string("Hi, my name") , {"Hi", "my", "name"}));
    HE_ASSERT(issame(words_string("One,, two, three, four, five, six,") , {"One", "two", "three", "four", "five", "six"}));
    HE_ASSERT(issame(words_string("") , {}));
    HE_ASSERT(issame(words_string("ahmed     , gamal") , {"ahmed", "gamal"}));
}

}  // namespace he_cpp_101

namespace he_cpp_102 {


TEST(HumanEvalX, CPP_102) {

    HE_ASSERT(choose_num(12, 15) == 14);
    HE_ASSERT(choose_num(13, 12) == -1);
    HE_ASSERT(choose_num(33, 12354) == 12354);
    HE_ASSERT(choose_num(5234, 5233) == -1);
    HE_ASSERT(choose_num(6, 29) == 28);
    HE_ASSERT(choose_num(27, 10) == -1);
    HE_ASSERT(choose_num(7, 7) == -1);
    HE_ASSERT(choose_num(546, 546) == 546);
}

}  // namespace he_cpp_102

namespace he_cpp_103 {


TEST(HumanEvalX, CPP_103) {

    HE_ASSERT(rounded_avg(1, 5) == "11");
    HE_ASSERT(rounded_avg(7, 13) == "1010");
    HE_ASSERT(rounded_avg(964,977) == "1111001010");
    HE_ASSERT(rounded_avg(996,997) == "1111100100");
    HE_ASSERT(rounded_avg(560,851) == "1011000001");  
    HE_ASSERT(rounded_avg(185,546) == "101101101");
    HE_ASSERT(rounded_avg(362,496) == "110101101");
    HE_ASSERT(rounded_avg(350,902) == "1001110010");
    HE_ASSERT(rounded_avg(197,233) == "11010111");
    HE_ASSERT(rounded_avg(7, 5) == "-1");
    HE_ASSERT(rounded_avg(5, 1) == "-1");
    HE_ASSERT(rounded_avg(5, 5) == "101");
}

}  // namespace he_cpp_103

namespace he_cpp_104 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_104) {

    HE_ASSERT(issame(unique_digits({15, 33, 1422, 1}) , {1, 15, 33}));
    HE_ASSERT(issame(unique_digits({152, 323, 1422, 10}) , {}));
    HE_ASSERT(issame(unique_digits({12345, 2033, 111, 151}) , {111, 151}));
    HE_ASSERT(issame(unique_digits({135, 103, 31}) , {31, 135}));
}

}  // namespace he_cpp_104
