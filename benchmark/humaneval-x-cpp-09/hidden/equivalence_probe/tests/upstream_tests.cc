// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_09.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_065 {


TEST(HumanEvalX, CPP_065) {

    HE_ASSERT(circular_shift(100, 2) == "001");
    HE_ASSERT(circular_shift(12, 2) == "12");
    HE_ASSERT(circular_shift(97, 8) == "79");
    HE_ASSERT(circular_shift(12, 1) == "21");
    HE_ASSERT(circular_shift(11, 101) == "11");
}

}  // namespace he_cpp_065

namespace he_cpp_066 {


TEST(HumanEvalX, CPP_066) {

    HE_ASSERT(digitSum("") == 0);
    HE_ASSERT(digitSum("abAB") == 131);
    HE_ASSERT(digitSum("abcCd") == 67);
    HE_ASSERT(digitSum("helloE") == 69);
    HE_ASSERT(digitSum("woArBld") == 131);
    HE_ASSERT(digitSum("aAaaaXa") == 153);
    HE_ASSERT(digitSum(" How are yOu?") == 151);
    HE_ASSERT(digitSum("You arE Very Smart") == 327);
}

}  // namespace he_cpp_066

namespace he_cpp_067 {


TEST(HumanEvalX, CPP_067) {

    HE_ASSERT(fruit_distribution("5 apples and 6 oranges",19) == 8);
    HE_ASSERT(fruit_distribution("5 apples and 6 oranges",21) == 10);
    HE_ASSERT(fruit_distribution("0 apples and 1 oranges",3) == 2);
    HE_ASSERT(fruit_distribution("1 apples and 0 oranges",3) == 2);
    HE_ASSERT(fruit_distribution("2 apples and 3 oranges",100) == 95);
    HE_ASSERT(fruit_distribution("2 apples and 3 oranges",5) == 0);
    HE_ASSERT(fruit_distribution("1 apples and 100 oranges",120) == 19);
}

}  // namespace he_cpp_067

namespace he_cpp_068 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_068) {

    HE_ASSERT(issame(pluck({4,2,3}) , {2, 1}));
    HE_ASSERT(issame(pluck({1,2,3}) , {2, 1}));
    HE_ASSERT(issame(pluck({}) , {}));
    HE_ASSERT(issame(pluck({5, 0, 3, 0, 4, 2}) , {0, 1}));
    HE_ASSERT(issame(pluck({1, 2, 3, 0, 5, 3}) , {0, 3}));
    HE_ASSERT(issame(pluck({5, 4, 8, 4 ,8}) , {4, 1}));
    HE_ASSERT(issame(pluck({7, 6, 7, 1}) , {6, 1}));
    HE_ASSERT(issame(pluck({7, 9, 7, 1}) , {}));
}

}  // namespace he_cpp_068

namespace he_cpp_069 {


TEST(HumanEvalX, CPP_069) {

    HE_ASSERT(search({5, 5, 5, 5, 1}) == 1);
    HE_ASSERT(search({4, 1, 4, 1, 4, 4}) == 4);
    HE_ASSERT(search({3, 3}) == -1);
    HE_ASSERT(search({8, 8, 8, 8, 8, 8, 8, 8}) == 8);
    HE_ASSERT(search({2, 3, 3, 2, 2}) == 2);
    HE_ASSERT(search({2, 7, 8, 8, 4, 8, 7, 3, 9, 6, 5, 10, 4, 3, 6, 7, 1, 7, 4, 10, 8, 1}) == 1);
    HE_ASSERT(search({3, 2, 8, 2}) == 2);
    HE_ASSERT(search({6, 7, 1, 8, 8, 10, 5, 8, 5, 3, 10}) == 1);
    HE_ASSERT(search({8, 8, 3, 6, 5, 6, 4}) == -1);
    HE_ASSERT(search({6, 9, 6, 7, 1, 4, 7, 1, 8, 8, 9, 8, 10, 10, 8, 4, 10, 4, 10, 1, 2, 9, 5, 7, 9}) == 1);
    HE_ASSERT(search({1, 9, 10, 1, 3}) == 1);
    HE_ASSERT(search({6, 9, 7, 5, 8, 7, 5, 3, 7, 5, 10, 10, 3, 6, 10, 2, 8, 6, 5, 4, 9, 5, 3, 10}) == 5);
    HE_ASSERT(search({1}) == 1);
    HE_ASSERT(search({8, 8, 10, 6, 4, 3, 5, 8, 2, 4, 2, 8, 4, 6, 10, 4, 2, 1, 10, 2, 1, 1, 5}) == 4);
    HE_ASSERT(search({2, 10, 4, 8, 2, 10, 5, 1, 2, 9, 5, 5, 6, 3, 8, 6, 4, 10}) == 2);
    HE_ASSERT(search({1, 6, 10, 1, 6, 9, 10, 8, 6, 8, 7, 3}) == 1);
    HE_ASSERT(search({9, 2, 4, 1, 5, 1, 5, 2, 5, 7, 7, 7, 3, 10, 1, 5, 4, 2, 8, 4, 1, 9, 10, 7, 10, 2, 8, 10, 9, 4}) == 4);
    HE_ASSERT(search({2, 6, 4, 2, 8, 7, 5, 6, 4, 10, 4, 6, 3, 7, 8, 8, 3, 1, 4, 2, 2, 10, 7}) == 4);
    HE_ASSERT(search({9, 8, 6, 10, 2, 6, 10, 2, 7, 8, 10, 3, 8, 2, 6, 2, 3, 1}) == 2);
    HE_ASSERT(search({5, 5, 3, 9, 5, 6, 3, 2, 8, 5, 6, 10, 10, 6, 8, 4, 10, 7, 7, 10, 8}) == -1);
    HE_ASSERT(search({10}) == -1);
    HE_ASSERT(search({9, 7, 7, 2, 4, 7, 2, 10, 9, 7, 5, 7, 2}) == 2);
    HE_ASSERT(search({5, 4, 10, 2, 1, 1, 10, 3, 6, 1, 8}) == 1);
    HE_ASSERT(search({7, 9, 9, 9, 3, 4, 1, 5, 9, 1, 2, 1, 1, 10, 7, 5, 6, 7, 6, 7, 7, 6}) == 1);
    HE_ASSERT(search({3, 10, 10, 9, 2}) == -1);
}

}  // namespace he_cpp_069

namespace he_cpp_070 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_070) {

    HE_ASSERT(issame(strange_sort_list({1, 2, 3, 4}) , {1, 4, 2, 3}));
    HE_ASSERT(issame(strange_sort_list({5, 6, 7, 8, 9}) , {5, 9, 6, 8, 7}));
    HE_ASSERT(issame(strange_sort_list({1, 2, 3, 4, 5}) , {1, 5, 2, 4, 3}));
    HE_ASSERT(issame(strange_sort_list({5, 6, 7, 8, 9, 1}) , {1, 9, 5, 8, 6, 7}));
    HE_ASSERT(issame(strange_sort_list({5, 5, 5, 5}) , {5, 5, 5, 5}));
    HE_ASSERT(issame(strange_sort_list({}) , {}));
    HE_ASSERT(issame(strange_sort_list({1,2,3,4,5,6,7,8}) , {1, 8, 2, 7, 3, 6, 4, 5}));
    HE_ASSERT(issame(strange_sort_list({0,2,2,2,5,5,-5,-5}) , {-5, 5, -5, 5, 0, 2, 2, 2}));
    HE_ASSERT(issame(strange_sort_list({111111}) , {111111}));
}

}  // namespace he_cpp_070

namespace he_cpp_071 {


TEST(HumanEvalX, CPP_071) {

    HE_ASSERT(abs(triangle_area(3, 4, 5)-6.00)<0.01);
    HE_ASSERT(abs(triangle_area(1, 2, 10) +1)<0.01);
    HE_ASSERT(abs(triangle_area(4, 8, 5) -8.18)<0.01);
    HE_ASSERT(abs(triangle_area(2, 2, 2) -1.73)<0.01);
    HE_ASSERT(abs(triangle_area(1, 2, 3) +1)<0.01);
    HE_ASSERT(abs(triangle_area(10, 5, 7) - 16.25)<0.01);
    HE_ASSERT(abs(triangle_area(2, 6, 3) +1)<0.01);
    HE_ASSERT(abs(triangle_area(1, 1, 1) -0.43)<0.01);
    HE_ASSERT(abs(triangle_area(2, 2, 10) +1)<0.01);
}

}  // namespace he_cpp_071

namespace he_cpp_072 {


TEST(HumanEvalX, CPP_072) {

    HE_ASSERT(will_it_fly({3, 2, 3}, 9)==true);
    HE_ASSERT(will_it_fly({1, 2}, 5) == false);
    HE_ASSERT(will_it_fly({3}, 5) == true);
    HE_ASSERT(will_it_fly({3, 2, 3}, 1) == false);
    HE_ASSERT(will_it_fly({1, 2, 3}, 6) ==false);
    HE_ASSERT(will_it_fly({5}, 5) == true);
}

}  // namespace he_cpp_072
