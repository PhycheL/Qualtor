// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_10.h"

#include <gtest/gtest.h>

#include <cmath>
#include <map>
#include <string>
#include <vector>

namespace {

template <class T>
void ExpectNearScalar(T actual, T expected, double tolerance) {
    EXPECT_NEAR(actual, expected, tolerance * (1 + std::fabs(static_cast<double>(expected))));
}

template <class T>
void ExpectNearVec(const std::vector<T>& actual, const std::vector<T>& expected, double tolerance) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) ExpectNearScalar(actual[i], expected[i], tolerance);
}

}  // namespace

TEST(Characterization, smallest_change_01) {
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 5, 4, 7, 9, 6})), (4));
    EXPECT_EQ((smallest_change(std::vector<int >{2, -238, 26, 99999, 2, 2, -1})), (3));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 5, 4, 7, 9, 6, 99999})), (4));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 4, 2})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 544, 1, -2, 0})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{5, 2, 3, 2, 1})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 4, 3, 2, 2})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 4, 1})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{19, 3, 4, 21})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{5, 9, -116, 6, -10, 1, 1, -1})), (4));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 4, 3, 2, 2, -623})), (3));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 5, 9, 7, 4, 6})), (4));
}

TEST(Characterization, total_match_01) {
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("admin"), std::string("hi"), std::string("hi"), std::string("project")}, std::vector<std::string >{std::string("hli"), std::string("JKisouPx"), std::string("THOG vSwf8J"), std::string("U")})), (std::vector<std::string >{std::string("admin"), std::string("hi"), std::string("hi"), std::string("project")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hi")}, std::vector<std::string >{std::string("hi")})), (std::vector<std::string >{std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hi"), std::string("hi")}, std::vector<std::string >{std::string("proje t"), std::string("this"), std::string("ETy4G"), std::string("c7M36"), std::string("mufPKZ"), std::string("XI"), std::string("hii")})), (std::vector<std::string >{std::string("hi"), std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("y")}, std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("admin"), std::string("project")})), (std::vector<std::string >{std::string("y")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("Hi"), std::string("admin"), std::string("J"), std::string(""), std::string("prject")}, std::vector<std::string >{std::string("hi"), std::string("admin")})), (std::vector<std::string >{std::string("hi"), std::string("admin")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("udmmwn")}, std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("project")})), (std::vector<std::string >{std::string("udmmwn")}));
    EXPECT_EQ((total_match(std::vector<std::string >{}, std::vector<std::string >{std::string("hEs"), std::string("l"), std::string("admin"), std::string("4")})), (std::vector<std::string >{}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("L6eWbFSl9rUq"), std::string("admin"), std::string("x dVVHKE"), std::string("prJoect"), std::string("rTgfTG2Vd")}, std::vector<std::string >{})), (std::vector<std::string >{}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("N"), std::string(""), std::string("5"), std::string("3u2ueJt"), std::string("b")}, std::vector<std::string >{std::string("admin"), std::string("hi"), std::string("hi"), std::string("project")})), (std::vector<std::string >{std::string("N"), std::string(""), std::string("5"), std::string("3u2ueJt"), std::string("b")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("admiH")}, std::vector<std::string >{std::string("hI"), std::string("Hi"), std::string("xj")})), (std::vector<std::string >{std::string("admiH")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("1"), std::string("3"), std::string("4"), std::string("5")}, std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("admin"), std::string("project")})), (std::vector<std::string >{std::string("1"), std::string("3"), std::string("4"), std::string("5")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("4")}, std::vector<std::string >{})), (std::vector<std::string >{}));
}

TEST(Characterization, is_multiply_prime_01) {
    EXPECT_EQ((is_multiply_prime(1)), (false));
    EXPECT_EQ((is_multiply_prime(3)), (false));
    EXPECT_EQ((is_multiply_prime(571)), (false));
    EXPECT_EQ((is_multiply_prime(7)), (false));
    EXPECT_EQ((is_multiply_prime(6)), (false));
    EXPECT_EQ((is_multiply_prime(-3)), (false));
    EXPECT_EQ((is_multiply_prime(27)), (true));
    EXPECT_EQ((is_multiply_prime(0)), (false));
    EXPECT_EQ((is_multiply_prime(9)), (false));
    EXPECT_EQ((is_multiply_prime(11)), (false));
    EXPECT_EQ((is_multiply_prime(2)), (false));
    EXPECT_EQ((is_multiply_prime(5)), (false));
}

TEST(Characterization, is_simple_power_01) {
    EXPECT_EQ((is_simple_power(7, 21)), (false));
    EXPECT_EQ((is_simple_power(-4, 5)), (false));
    EXPECT_EQ((is_simple_power(6, 12)), (false));
    EXPECT_EQ((is_simple_power(1000, 6)), (false));
    EXPECT_EQ((is_simple_power(20, 1)), (false));
    EXPECT_EQ((is_simple_power(-102, 551)), (false));
    EXPECT_EQ((is_simple_power(26, 1)), (false));
    EXPECT_EQ((is_simple_power(6, -579)), (false));
    EXPECT_EQ((is_simple_power(-9, -959)), (false));
    EXPECT_EQ((is_simple_power(2, 1)), (false));
    EXPECT_EQ((is_simple_power(-921, -4)), (false));
    EXPECT_EQ((is_simple_power(-5, -4)), (false));
}

TEST(Characterization, iscuber_01) {
    EXPECT_EQ((iscuber(-1)), (true));
    EXPECT_EQ((iscuber(3)), (false));
    EXPECT_EQ((iscuber(1000)), (true));
    EXPECT_EQ((iscuber(16)), (false));
    EXPECT_EQ((iscuber(-3)), (false));
    EXPECT_EQ((iscuber(-446)), (false));
    EXPECT_EQ((iscuber(-434)), (false));
    EXPECT_EQ((iscuber(19)), (false));
    EXPECT_EQ((iscuber(-121)), (false));
    EXPECT_EQ((iscuber(27)), (true));
    EXPECT_EQ((iscuber(99999)), (false));
    EXPECT_EQ((iscuber(12345)), (false));
}

TEST(Characterization, hex_key_01) {
    EXPECT_EQ((hex_key(std::string("112233445566778899AABBzCDDEEFF00"))), (12));
    EXPECT_EQ((hex_key(std::string("Pp6OGv"))), (0));
    EXPECT_EQ((hex_key(std::string("n"))), (0));
    EXPECT_EQ((hex_key(std::string("ABED1A33"))), (4));
    EXPECT_EQ((hex_key(std::string("2020"))), (2));
    EXPECT_EQ((hex_key(std::string("AuED1A3b"))), (2));
    EXPECT_EQ((hex_key(std::string("wEB"))), (1));
    EXPECT_EQ((hex_key(std::string("AB"))), (1));
    EXPECT_EQ((hex_key(std::string("202U"))), (2));
    EXPECT_EQ((hex_key(std::string("12233445566778899AABBCCDDEEF00"))), (12));
    EXPECT_EQ((hex_key(std::string(""))), (0));
    EXPECT_EQ((hex_key(std::string("FV65"))), (1));
}

TEST(Characterization, decimal_to_binary_01) {
    EXPECT_EQ((decimal_to_binary(8)), (std::string("db1000db")));
    EXPECT_EQ((decimal_to_binary(-8)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(-1)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(574)), (std::string("db1000111110db")));
    EXPECT_EQ((decimal_to_binary(103)), (std::string("db1100111db")));
    EXPECT_EQ((decimal_to_binary(16)), (std::string("db10000db")));
    EXPECT_EQ((decimal_to_binary(-2)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(-955)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(30)), (std::string("db11110db")));
    EXPECT_EQ((decimal_to_binary(-609)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(32)), (std::string("db100000db")));
    EXPECT_EQ((decimal_to_binary(12)), (std::string("db1100db")));
}

TEST(Characterization, is_happy_01) {
    EXPECT_EQ((is_happy(std::string("u"))), (false));
    EXPECT_EQ((is_happy(std::string("q"))), (false));
    EXPECT_EQ((is_happy(std::string("abcd"))), (true));
    EXPECT_EQ((is_happy(std::string("adb"))), (true));
    EXPECT_EQ((is_happy(std::string("eyy"))), (false));
    EXPECT_EQ((is_happy(std::string("o"))), (false));
    EXPECT_EQ((is_happy(std::string("ala"))), (false));
    EXPECT_EQ((is_happy(std::string("Ic3MCh0j"))), (true));
    EXPECT_EQ((is_happy(std::string("aodm"))), (true));
    EXPECT_EQ((is_happy(std::string("Ny1oAh9bXH"))), (true));
    EXPECT_EQ((is_happy(std::string("aa"))), (false));
    EXPECT_EQ((is_happy(std::string("ad3b"))), (true));
}
