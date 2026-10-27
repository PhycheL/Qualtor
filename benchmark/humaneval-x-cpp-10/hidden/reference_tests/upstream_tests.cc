// 由 benchmark/tools/import_humaneval_x.py 从 HumanEval-X 的 test 字段机械转换；隐藏材料，不提供给被评测的生成 Agent。
#include "humaneval_x_cpp_10.h"

#include <gtest/gtest.h>

#define HE_ASSERT(...) EXPECT_TRUE((__VA_ARGS__))

namespace he_cpp_073 {


TEST(HumanEvalX, CPP_073) {

    HE_ASSERT(smallest_change({1,2,3,5,4,7,9,6}) == 4);
    HE_ASSERT(smallest_change({1, 2, 3, 4, 3, 2, 2}) == 1);
    HE_ASSERT(smallest_change({1, 4, 2}) == 1);
    HE_ASSERT(smallest_change({1, 4, 4, 2}) == 1);
    HE_ASSERT(smallest_change({1, 2, 3, 2, 1}) == 0);
    HE_ASSERT(smallest_change({3, 1, 1, 3}) == 0);
    HE_ASSERT(smallest_change({1}) == 0);
    HE_ASSERT(smallest_change({0, 1}) == 1);
}

}  // namespace he_cpp_073

namespace he_cpp_074 {
bool issame(vector<string> a,vector<string>b){
    if (a.size()!=b.size()) return false;
    for (int i=0;i<a.size();i++)
    {
    if (a[i]!=b[i]) return false;
    }
    return true;
}

TEST(HumanEvalX, CPP_074) {

    HE_ASSERT(issame(total_match({}, {}) , {}));
    HE_ASSERT(issame(total_match({"hi", "admin"}, {"hi", "hi"}) , {"hi", "hi"}));
    HE_ASSERT(issame(total_match({"hi", "admin"}, {"hi", "hi", "admin", "project"}) , {"hi", "admin"}));
    HE_ASSERT(issame(total_match({"4"}, {"1", "2", "3", "4", "5"}) , {"4"}));
    HE_ASSERT(issame(total_match({"hi", "admin"}, {"hI", "Hi"}) , {"hI", "Hi"}));
    HE_ASSERT(issame(total_match({"hi", "admin"}, {"hI", "hi", "hi"}) , {"hI", "hi", "hi"}));
    HE_ASSERT(issame(total_match({"hi", "admin"}, {"hI", "hi", "hii"}) , {"hi", "admin"}));
    HE_ASSERT(issame(total_match({}, {"this"}) , {}));
    HE_ASSERT(issame(total_match({"this"}, {}) , {}));
}

}  // namespace he_cpp_074

namespace he_cpp_075 {


TEST(HumanEvalX, CPP_075) {

    HE_ASSERT(is_multiply_prime(5) == false);
    HE_ASSERT(is_multiply_prime(30) == true);
    HE_ASSERT(is_multiply_prime(8) == true);
    HE_ASSERT(is_multiply_prime(10) == false);
    HE_ASSERT(is_multiply_prime(125) == true);
    HE_ASSERT(is_multiply_prime(3 * 5 * 7) == true);
    HE_ASSERT(is_multiply_prime(3 * 6 * 7) == false);
    HE_ASSERT(is_multiply_prime(9 * 9 * 9) == false);
    HE_ASSERT(is_multiply_prime(11 * 9 * 9) == false);
    HE_ASSERT(is_multiply_prime(11 * 13 * 7) == true);
}

}  // namespace he_cpp_075

namespace he_cpp_076 {


TEST(HumanEvalX, CPP_076) {

    HE_ASSERT(is_simple_power(1, 4)== true);
    HE_ASSERT(is_simple_power(2, 2)==true);
    HE_ASSERT(is_simple_power(8, 2)==true);
    HE_ASSERT(is_simple_power(3, 2)==false);
    HE_ASSERT(is_simple_power(3, 1)==false);
    HE_ASSERT(is_simple_power(5, 3)==false);
    HE_ASSERT(is_simple_power(16, 2)== true);
    HE_ASSERT(is_simple_power(143214, 16)== false);
    HE_ASSERT(is_simple_power(4, 2)==true);
    HE_ASSERT(is_simple_power(9, 3)==true);
    HE_ASSERT(is_simple_power(16, 4)==true);
    HE_ASSERT(is_simple_power(24, 2)==false);
    HE_ASSERT(is_simple_power(128, 4)==false);
    HE_ASSERT(is_simple_power(12, 6)==false);
    HE_ASSERT(is_simple_power(1, 1)==true);
    HE_ASSERT(is_simple_power(1, 12)==true);
}

}  // namespace he_cpp_076

namespace he_cpp_077 {


TEST(HumanEvalX, CPP_077) {

    HE_ASSERT(iscuber(1) == true);
    HE_ASSERT(iscuber(2) == false);
    HE_ASSERT(iscuber(-1) == true);
    HE_ASSERT(iscuber(64) == true);
    HE_ASSERT(iscuber(180) == false);
    HE_ASSERT(iscuber(1000) == true);
    HE_ASSERT(iscuber(0) == true);
    HE_ASSERT(iscuber(1729) == false);
}

}  // namespace he_cpp_077

namespace he_cpp_078 {


TEST(HumanEvalX, CPP_078) {

    HE_ASSERT(hex_key("AB") == 1      );
    HE_ASSERT(hex_key("1077E") == 2 );
    HE_ASSERT(hex_key("ABED1A33") == 4     );
    HE_ASSERT(hex_key("2020") == 2 );
    HE_ASSERT(hex_key("123456789ABCDEF0") == 6      );
    HE_ASSERT(hex_key("112233445566778899AABBCCDDEEFF00") == 12 );
    HE_ASSERT(hex_key("") == 0);
}

}  // namespace he_cpp_078

namespace he_cpp_079 {


TEST(HumanEvalX, CPP_079) {

    HE_ASSERT(decimal_to_binary(0) == "db0db");
    HE_ASSERT(decimal_to_binary(32) == "db100000db");
    HE_ASSERT(decimal_to_binary(103) == "db1100111db");
    HE_ASSERT(decimal_to_binary(15) == "db1111db");
}

}  // namespace he_cpp_079

namespace he_cpp_080 {


TEST(HumanEvalX, CPP_080) {

    HE_ASSERT(is_happy("a") == false );
    HE_ASSERT(is_happy("aa") == false );
    HE_ASSERT(is_happy("abcd") == true );
    HE_ASSERT(is_happy("aabb") == false );
    HE_ASSERT(is_happy("adb") == true );
    HE_ASSERT(is_happy("xyy") == false );
    HE_ASSERT(is_happy("iopaxpoi") == true );
    HE_ASSERT(is_happy("iopaxioi") == false );
}

}  // namespace he_cpp_080
