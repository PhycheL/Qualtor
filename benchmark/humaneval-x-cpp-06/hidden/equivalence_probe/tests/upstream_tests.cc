// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_06.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_041 {


TEST(HumanEvalX, CPP_041) {

    HE_ASSERT(car_race_collision(2) == 4);
    HE_ASSERT(car_race_collision(3) == 9);
    HE_ASSERT(car_race_collision(4) == 16);
    HE_ASSERT(car_race_collision(8) == 64);
    HE_ASSERT(car_race_collision(10) == 100);
}

}  // namespace he_cpp_041

namespace he_cpp_042 {
bool issame(vector<int> a,vector<int>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
        if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_042) {

    HE_ASSERT(issame(incr_list({}) , {}));
    HE_ASSERT(issame(incr_list({3, 2, 1}) , {4, 3, 2}));
    HE_ASSERT(issame(incr_list({5, 2, 5, 2, 3, 3, 9, 0, 123}) , {6, 3, 6, 3, 4, 4, 10, 1, 124}));
}

}  // namespace he_cpp_042

namespace he_cpp_043 {


TEST(HumanEvalX, CPP_043) {

    HE_ASSERT(pairs_sum_to_zero({1, 3, 5, 0}) == false);
    HE_ASSERT(pairs_sum_to_zero({1, 3, -2, 1}) == false);
    HE_ASSERT(pairs_sum_to_zero({1, 2, 3, 7}) == false);
    HE_ASSERT(pairs_sum_to_zero({2, 4, -5, 3, 5, 7}) == true);
    HE_ASSERT(pairs_sum_to_zero({1}) == false);
    HE_ASSERT(pairs_sum_to_zero({-3, 9, -1, 3, 2, 30}) == true);
    HE_ASSERT(pairs_sum_to_zero({-3, 9, -1, 3, 2, 31}) == true);
    HE_ASSERT(pairs_sum_to_zero({-3, 9, -1, 4, 2, 30}) == false);
    HE_ASSERT(pairs_sum_to_zero({-3, 9, -1, 4, 2, 31}) == false);
}

}  // namespace he_cpp_043

namespace he_cpp_044 {


TEST(HumanEvalX, CPP_044) {

    HE_ASSERT(change_base(8, 3) == "22");
    HE_ASSERT(change_base(9, 3) == "100");
    HE_ASSERT(change_base(234, 2) == "11101010");
    HE_ASSERT(change_base(16, 2) == "10000");
    HE_ASSERT(change_base(8, 2) == "1000");
    HE_ASSERT(change_base(7, 2) == "111");
    for (int x=2;x<8;x++)
        HE_ASSERT(change_base(x, x + 1) == to_string(x));
}

}  // namespace he_cpp_044

namespace he_cpp_045 {


TEST(HumanEvalX, CPP_045) {

    HE_ASSERT(abs(triangle_area(5, 3) - 7.5)<1e-4);
    HE_ASSERT(abs(triangle_area(2, 2) - 2.0)<1e-4);
    HE_ASSERT(abs(triangle_area(10, 8) - 40.0)<1e-4);
}

}  // namespace he_cpp_045

namespace he_cpp_046 {


TEST(HumanEvalX, CPP_046) {

    HE_ASSERT(fib4(5) == 4);
    HE_ASSERT(fib4(8) == 28);
    HE_ASSERT(fib4(10) == 104);
    HE_ASSERT(fib4(12) == 386);
}

}  // namespace he_cpp_046

namespace he_cpp_047 {


TEST(HumanEvalX, CPP_047) {

    HE_ASSERT(abs(median({3, 1, 2, 4, 5}) - 3)<1e-4);
    HE_ASSERT(abs(median({-10, 4, 6, 1000, 10, 20}) -8.0)<1e-4);
    HE_ASSERT(abs(median({5}) - 5)<1e-4);
    HE_ASSERT(abs(median({6, 5}) - 5.5)<1e-4);
    HE_ASSERT(abs(median({8, 1, 3, 9, 9, 2, 7}) - 7)<1e-4 );
}

}  // namespace he_cpp_047

namespace he_cpp_048 {


TEST(HumanEvalX, CPP_048) {

    HE_ASSERT(is_palindrome("") == true);
    HE_ASSERT(is_palindrome("aba") == true);
    HE_ASSERT(is_palindrome("aaaaa") == true);
    HE_ASSERT(is_palindrome("zbcd") == false);
    HE_ASSERT(is_palindrome("xywyx") == true);
    HE_ASSERT(is_palindrome("xywyz") == false);
    HE_ASSERT(is_palindrome("xywzx") == false);
}

}  // namespace he_cpp_048
