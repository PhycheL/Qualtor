// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_03.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_016 {


TEST(HumanEvalX, CPP_016) {

    HE_ASSERT(count_distinct_characters("") == 0);
    HE_ASSERT(count_distinct_characters("abcde") == 5);
    HE_ASSERT(count_distinct_characters("abcdecadeCADE") == 5);
    HE_ASSERT(count_distinct_characters("aaaaAAAAaaaa") == 1);
    HE_ASSERT(count_distinct_characters("Jerry jERRY JeRRRY") == 5);
}

}  // namespace he_cpp_016

namespace he_cpp_017 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_017) {

    HE_ASSERT(issame(parse_music("") , {}));
     HE_ASSERT(issame(parse_music("o o o o") ,{4, 4, 4, 4}));
      HE_ASSERT(issame(parse_music(".| .| .| .|") , {1, 1, 1, 1}));
 HE_ASSERT(issame(parse_music("o| o| .| .| o o o o") , {2, 2, 1, 1, 4, 4, 4, 4}));
  HE_ASSERT(issame(parse_music("o| .| o| .| o o| o o|") , {2, 1, 2, 1, 4, 2, 4, 2}));
}

}  // namespace he_cpp_017

namespace he_cpp_018 {


TEST(HumanEvalX, CPP_018) {

    HE_ASSERT(how_many_times("", "x") == 0);
    HE_ASSERT(how_many_times("xyxyxyx", "x") == 4);
     HE_ASSERT(how_many_times("cacacacac", "cac") == 4);
    HE_ASSERT(how_many_times("john doe", "john") == 1);
}

}  // namespace he_cpp_018

namespace he_cpp_019 {


TEST(HumanEvalX, CPP_019) {

    HE_ASSERT(sort_numbers("") == "");
    HE_ASSERT(sort_numbers("three") == "three");
    HE_ASSERT(sort_numbers("three five nine") == "three five nine");
     HE_ASSERT(sort_numbers("five zero four seven nine eight") == "zero four five seven eight nine");
      HE_ASSERT(sort_numbers("six five four three two one zero") == "zero one two three four five six");
}

}  // namespace he_cpp_019

namespace he_cpp_020 {
bool issame(vector<float> a,vector<float>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (abs(a[i]-b[i])>1e-4) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_020) {

    HE_ASSERT(issame(find_closest_elements({1.0, 2.0, 3.9, 4.0, 5.0, 2.2}) , {3.9, 4.0}));
    HE_ASSERT(issame(find_closest_elements({1.0, 2.0, 5.9, 4.0, 5.0}) , {5.0, 5.9} ));
    HE_ASSERT(issame(find_closest_elements({1.0, 2.0, 3.0, 4.0, 5.0, 2.2}) ,{2.0, 2.2}));
     HE_ASSERT(issame(find_closest_elements({1.0, 2.0, 3.0, 4.0, 5.0, 2.0}) ,{2.0, 2.0}));
      HE_ASSERT(issame(find_closest_elements({1.1, 2.2, 3.1, 4.1, 5.1}) , {2.2, 3.1}));
}

}  // namespace he_cpp_020

namespace he_cpp_021 {
bool issame(vector<float> a,vector<float>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (abs(a[i]-b[i])>1e-4) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_021) {

    HE_ASSERT(issame(rescale_to_unit({2.0, 49.9}) , {0.0, 1.0}));
     HE_ASSERT(issame(rescale_to_unit({100.0, 49.9}) ,{1.0, 0.0})); 
     HE_ASSERT(issame(rescale_to_unit({1.0, 2.0, 3.0, 4.0, 5.0}) , {0.0, 0.25, 0.5, 0.75, 1.0}));
    HE_ASSERT(issame(rescale_to_unit({2.0, 1.0, 5.0, 3.0, 4.0}) , {0.25, 0.0, 1.0, 0.5, 0.75}));
     HE_ASSERT(issame(rescale_to_unit({12.0, 11.0, 15.0, 13.0, 14.0}) ,{0.25, 0.0, 1.0, 0.5, 0.75}));
}

}  // namespace he_cpp_021

namespace he_cpp_023 {


TEST(HumanEvalX, CPP_023) {

    HE_ASSERT(strlen("") == 0);
    HE_ASSERT(strlen("x") == 1);
     HE_ASSERT(strlen("asdasnakj") == 9);
}

}  // namespace he_cpp_023

namespace he_cpp_024 {


TEST(HumanEvalX, CPP_024) {

    HE_ASSERT(largest_divisor(3) == 1);
    HE_ASSERT(largest_divisor(7) == 1);
    HE_ASSERT(largest_divisor(10) == 5);
    HE_ASSERT(largest_divisor(100) == 50);
    HE_ASSERT(largest_divisor(49) == 7);
}

}  // namespace he_cpp_024
