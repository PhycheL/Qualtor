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

TEST(Probe, smallest_change_01) {
    EXPECT_EQ((smallest_change(std::vector<int >{1})), (0));
    EXPECT_EQ((smallest_change(std::vector<int >{-3, 7, 7, 3, 3})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{3, 3, 1, 1})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{-5, 313, -3, 19, 0})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{23})), (0));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 2, 1})), (0));
    EXPECT_EQ((smallest_change(std::vector<int >{3, 1, 1, 3})), (0));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 1, 3, 2, 2})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{22, -7})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{9, 0, 12345, 199, 2})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 2, 1, 4})), (3));
    EXPECT_EQ((smallest_change(std::vector<int >{3, 2, 6, 1, 8})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{2, 4})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{3, 1, 1})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 300, 0, 16, 20, 12})), (3));
    EXPECT_EQ((smallest_change(std::vector<int >{0, 3, -557, 4, 1, 29, 6, 7})), (4));
    EXPECT_EQ((smallest_change(std::vector<int >{6, 3, -9, 1, 2, 10})), (3));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 4})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 4, 4})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 4, 2, 7})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 4, 4, 2, 5})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{26, 4, 2, -3})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{0, -777})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{7, 4, -489, 10})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{-6, 1, 14, -8, 895, 801, 4})), (3));
}

TEST(Probe, smallest_change_02) {
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 2, 1, 1})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 4, 4, 2})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{0, 1})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{3})), (0));
    EXPECT_EQ((smallest_change(std::vector<int >{7, 4})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{30})), (0));
    EXPECT_EQ((smallest_change(std::vector<int >{4, 6, 0, 15, 15, 4})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 4, 4, 2, 2})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{4, 2})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 30, 4, 3, 2, 2})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 3, 2, 1, 7})), (3));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2, 2, 4, 3, 2, 2})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{9, -451, 2, 832, 135, 5})), (3));
    EXPECT_EQ((smallest_change(std::vector<int >{748, 26, 874, -9, 4, 19})), (3));
    EXPECT_EQ((smallest_change(std::vector<int >{3, 2, 1, 3})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 4, 6})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{1, 2})), (1));
    EXPECT_EQ((smallest_change(std::vector<int >{0, 2, 7, 1, 4})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{16, 2, 26, 3, 8, 0, 5, 7})), (4));
    EXPECT_EQ((smallest_change(std::vector<int >{30, 4, 21, 939, 14, 7, 3})), (3));
    EXPECT_EQ((smallest_change(std::vector<int >{3, 1, 1, 3, 5})), (2));
    EXPECT_EQ((smallest_change(std::vector<int >{5})), (0));
    EXPECT_EQ((smallest_change(std::vector<int >{13, 5, 5, 10})), (1));
}

TEST(Probe, total_match_01) {
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("this")}, std::vector<std::string >{std::string("Jthuq"), std::string("3"), std::string("ei"), std::string("admin"), std::string("OGlGmRs9t")})), (std::vector<std::string >{std::string("this")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hi")}, std::vector<std::string >{})), (std::vector<std::string >{}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("2")}, std::vector<std::string >{std::string("this"), std::string("project")})), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("admin"), std::string("hi")}, std::vector<std::string >{std::string("hI")})), (std::vector<std::string >{std::string("hI")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("2C6YrR4k")}, std::vector<std::string >{std::string("hi"), std::string("hi")})), (std::vector<std::string >{std::string("hi"), std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("4")}, std::vector<std::string >{std::string("hi"), std::string("admin")})), (std::vector<std::string >{std::string("4")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hi")}, std::vector<std::string >{std::string("")})), (std::vector<std::string >{std::string("")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hI"), std::string("Hi")}, std::vector<std::string >{std::string("5")})), (std::vector<std::string >{std::string("5")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("Hi"), std::string("hI")}, std::vector<std::string >{std::string("1"), std::string("QQ5w"), std::string("3"), std::string("4"), std::string("5")})), (std::vector<std::string >{std::string("Hi"), std::string("hI")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("1"), std::string("2"), std::string("3"), std::string("3"), std::string("5")}, std::vector<std::string >{std::string("Cq3"), std::string("admim"), std::string("Hi"), std::string("Amin"), std::string(""), std::string("Ie"), std::string("8")})), (std::vector<std::string >{std::string("1"), std::string("2"), std::string("3"), std::string("3"), std::string("5")}));
    EXPECT_EQ((total_match(std::vector<std::string >{}, std::vector<std::string >{std::string("hi"), std::string("hi")})), (std::vector<std::string >{}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("A"), std::string("5"), std::string("i"), std::string(" "), std::string("2"), std::string("hi"), std::string(""), std::string("ET")}, std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hii")})), (std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hii")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("4"), std::string("KG184ZTK0DE"), std::string("IxWA")}, std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("j3M")})), (std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("j3M")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("T3"), std::string("hI"), std::string("cP"), std::string("admin"), std::string("hi"), std::string("hI"), std::string("project"), std::string("")}, std::vector<std::string >{std::string("hi")})), (std::vector<std::string >{std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("this")}, std::vector<std::string >{std::string("hi")})), (std::vector<std::string >{std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("admin")}, std::vector<std::string >{std::string("1"), std::string("this"), std::string("9"), std::string("this"), std::string("2"), std::string("Du15Cz"), std::string("this"), std::string("yiyYTjRddzk")})), (std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("admin")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("4")}, std::vector<std::string >{std::string("this")})), (std::vector<std::string >{std::string("4")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("")}, std::vector<std::string >{std::string("5")})), (std::vector<std::string >{std::string("")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("Hi")}, std::vector<std::string >{std::string("hiM"), std::string("5"), std::string("hii"), std::string("jOc")})), (std::vector<std::string >{std::string("Hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("3"), std::string("Hi"), std::string("E7hI"), std::string("admin"), std::string("k1")}, std::vector<std::string >{std::string("1"), std::string("2"), std::string("Ie"), std::string("4"), std::string("5")})), (std::vector<std::string >{std::string("1"), std::string("2"), std::string("Ie"), std::string("4"), std::string("5")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("admin"), std::string("hi")}, std::vector<std::string >{std::string("5fqaGk"), std::string("pi"), std::string("C"), std::string("dSrljhs"), std::string(" YAVRe1rsfWQ"), std::string("2"), std::string("2Ri08uD")})), (std::vector<std::string >{std::string("admin"), std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hi"), std::string("hi")}, std::vector<std::string >{std::string("3"), std::string("3"), std::string("YO8U"), std::string("admin"), std::string("vwm"), std::string("ean MDZBqos"), std::string("hAi")})), (std::vector<std::string >{std::string("hi"), std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("1"), std::string("2"), std::string("3"), std::string("5")}, std::vector<std::string >{std::string("OvY7sO"), std::string("EOo"), std::string("AA4QF"), std::string("m5"), std::string("4"), std::string("uBQ9"), std::string("7kgDzMTNj0CH")})), (std::vector<std::string >{std::string("1"), std::string("2"), std::string("3"), std::string("5")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("IV38SWBdo "), std::string("p5oEect"), std::string("Hi")}, std::vector<std::string >{std::string("hi"), std::string("admin"), std::string("project")})), (std::vector<std::string >{std::string("hi"), std::string("admin"), std::string("project")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("admin"), std::string("hi")}, std::vector<std::string >{std::string("Hi"), std::string("hI")})), (std::vector<std::string >{std::string("Hi"), std::string("hI")}));
}

TEST(Probe, total_match_02) {
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("a ")}, std::vector<std::string >{std::string("4")})), (std::vector<std::string >{std::string("4")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hi"), std::string("hi")}, std::vector<std::string >{std::string("hI"), std::string("Hi")})), (std::vector<std::string >{std::string("hi"), std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hUii"), std::string("project"), std::string("Hi"), std::string("3"), std::string("Ohi")}, std::vector<std::string >{std::string(""), std::string("hi"), std::string("hii")})), (std::vector<std::string >{std::string(""), std::string("hi"), std::string("hii")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("B"), std::string("hi"), std::string("hii")}, std::vector<std::string >{std::string("4")})), (std::vector<std::string >{std::string("4")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("sAfSpb 6"), std::string("v"), std::string("4")}, std::vector<std::string >{std::string("hI"), std::string("Hi")})), (std::vector<std::string >{std::string("hI"), std::string("Hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hii"), std::string("hi"), std::string("hI")}, std::vector<std::string >{})), (std::vector<std::string >{}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("k"), std::string("kd9Dwk"), std::string("hI"), std::string("hi"), std::string("N60"), std::string("5R")}, std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("admin"), std::string("")})), (std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("admin"), std::string("")}));
    EXPECT_EQ((total_match(std::vector<std::string >{}, std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hii")})), (std::vector<std::string >{}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("1"), std::string("2"), std::string("3"), std::string("4")}, std::vector<std::string >{std::string("2"), std::string("admin")})), (std::vector<std::string >{std::string("1"), std::string("2"), std::string("3"), std::string("4")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hi"), std::string("hi")}, std::vector<std::string >{std::string("this"), std::string("projeS")})), (std::vector<std::string >{std::string("hi"), std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("admin"), std::string("hi")}, std::vector<std::string >{std::string("Xxn"), std::string(""), std::string("hI")})), (std::vector<std::string >{std::string("Xxn"), std::string(""), std::string("hI")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("this")}, std::vector<std::string >{std::string("4")})), (std::vector<std::string >{std::string("4")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("admin"), std::string("project")}, std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hi")})), (std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("YpWdSIg1wnz"), std::string("lskX"), std::string("iAp")}, std::vector<std::string >{std::string("Ua")})), (std::vector<std::string >{std::string("Ua")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hii")}, std::vector<std::string >{std::string("Hi"), std::string("hi")})), (std::vector<std::string >{std::string("Hi"), std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("H"), std::string("vh4VbRm"), std::string("h"), std::string("p4"), std::string("projVect"), std::string("pii"), std::string("admin")}, std::vector<std::string >{std::string("hi"), std::string("hii")})), (std::vector<std::string >{std::string("hi"), std::string("hii")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("4")}, std::vector<std::string >{std::string("hii"), std::string("hi"), std::string("hI")})), (std::vector<std::string >{std::string("4")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("UEGjAsYd7R"), std::string("h"), std::string("Hi"), std::string("m2"), std::string("admin"), std::string("d")}, std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hi")})), (std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("p8d"), std::string("Hi")}, std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hi")})), (std::vector<std::string >{std::string("p8d"), std::string("Hi")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("admin"), std::string("hi")}, std::vector<std::string >{std::string("4")})), (std::vector<std::string >{std::string("4")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("this")}, std::vector<std::string >{std::string("project"), std::string("hi"), std::string("DNr2UQZM2ism"), std::string("F1QcddPUzbpp"), std::string("hI"), std::string("kT0ejaRmz0vl"), std::string("Hi")})), (std::vector<std::string >{std::string("this")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hii")}, std::vector<std::string >{std::string("hi"), std::string("hi"), std::string("admin")})), (std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hii")}));
    EXPECT_EQ((total_match(std::vector<std::string >{std::string("kd"), std::string("admin")}, std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hi")})), (std::vector<std::string >{std::string("hI"), std::string("hi"), std::string("hi")}));
}

TEST(Probe, is_multiply_prime_01) {
    EXPECT_EQ((is_multiply_prime(20)), (true));
    EXPECT_EQ((is_multiply_prime(-5)), (false));
    EXPECT_EQ((is_multiply_prime(13)), (false));
    EXPECT_EQ((is_multiply_prime(-10)), (false));
    EXPECT_EQ((is_multiply_prime(129)), (false));
    EXPECT_EQ((is_multiply_prime(486)), (false));
    EXPECT_EQ((is_multiply_prime(-603)), (false));
    EXPECT_EQ((is_multiply_prime(8)), (true));
    EXPECT_EQ((is_multiply_prime(100)), (false));
    EXPECT_EQ((is_multiply_prime(18)), (true));
    EXPECT_EQ((is_multiply_prime(10)), (false));
    EXPECT_EQ((is_multiply_prime(-763)), (false));
    EXPECT_EQ((is_multiply_prime(125)), (true));
    EXPECT_EQ((is_multiply_prime(179)), (false));
    EXPECT_EQ((is_multiply_prime(99999)), (false));
    EXPECT_EQ((is_multiply_prime(17)), (false));
    EXPECT_EQ((is_multiply_prime(22)), (false));
    EXPECT_EQ((is_multiply_prime(-8)), (false));
    EXPECT_EQ((is_multiply_prime(251)), (false));
    EXPECT_EQ((is_multiply_prime(4)), (false));
    EXPECT_EQ((is_multiply_prime(30)), (true));
    EXPECT_EQ((is_multiply_prime(375)), (false));
    EXPECT_EQ((is_multiply_prime(366)), (true));
    EXPECT_EQ((is_multiply_prime(-356)), (false));
    EXPECT_EQ((is_multiply_prime(12)), (true));
}

TEST(Probe, is_multiply_prime_02) {
    EXPECT_EQ((is_multiply_prime(24)), (false));
    EXPECT_EQ((is_multiply_prime(-498)), (false));
    EXPECT_EQ((is_multiply_prime(14)), (false));
    EXPECT_EQ((is_multiply_prime(842)), (false));
    EXPECT_EQ((is_multiply_prime(315)), (false));
    EXPECT_EQ((is_multiply_prime(-7)), (false));
    EXPECT_EQ((is_multiply_prime(136)), (false));
    EXPECT_EQ((is_multiply_prime(-301)), (false));
    EXPECT_EQ((is_multiply_prime(-2)), (false));
    EXPECT_EQ((is_multiply_prime(258)), (true));
    EXPECT_EQ((is_multiply_prime(-65)), (false));
    EXPECT_EQ((is_multiply_prime(-791)), (false));
    EXPECT_EQ((is_multiply_prime(669)), (false));
    EXPECT_EQ((is_multiply_prime(29)), (false));
    EXPECT_EQ((is_multiply_prime(26)), (false));
    EXPECT_EQ((is_multiply_prime(-264)), (false));
    EXPECT_EQ((is_multiply_prime(-4)), (false));
    EXPECT_EQ((is_multiply_prime(-1)), (false));
    EXPECT_EQ((is_multiply_prime(-6)), (false));
    EXPECT_EQ((is_multiply_prime(-51)), (false));
    EXPECT_EQ((is_multiply_prime(123)), (false));
    EXPECT_EQ((is_multiply_prime(352)), (false));
    EXPECT_EQ((is_multiply_prime(193)), (false));
}

TEST(Probe, is_simple_power_01) {
    EXPECT_EQ((is_simple_power(2, -878)), (false));
    EXPECT_EQ((is_simple_power(-406, 9)), (false));
    EXPECT_EQ((is_simple_power(173, 13)), (false));
    EXPECT_EQ((is_simple_power(24, -255)), (false));
    EXPECT_EQ((is_simple_power(12, 26)), (false));
    EXPECT_EQ((is_simple_power(-591, 12)), (false));
    EXPECT_EQ((is_simple_power(-1, -778)), (false));
    EXPECT_EQ((is_simple_power(3, 126)), (false));
    EXPECT_EQ((is_simple_power(-1, 1)), (false));
    EXPECT_EQ((is_simple_power(614, 1)), (false));
    EXPECT_EQ((is_simple_power(-2, 25)), (false));
    EXPECT_EQ((is_simple_power(12, 128)), (false));
    EXPECT_EQ((is_simple_power(-6, -244)), (false));
    EXPECT_EQ((is_simple_power(20, 6)), (false));
    EXPECT_EQ((is_simple_power(128, 22)), (false));
    EXPECT_EQ((is_simple_power(1, 2)), (true));
    EXPECT_EQ((is_simple_power(0, -3)), (false));
    EXPECT_EQ((is_simple_power(26, 623)), (false));
    EXPECT_EQ((is_simple_power(905, 126)), (false));
    EXPECT_EQ((is_simple_power(1, 1)), (true));
    EXPECT_EQ((is_simple_power(15, -1)), (false));
    EXPECT_EQ((is_simple_power(24, 346)), (false));
    EXPECT_EQ((is_simple_power(370, -9)), (false));
    EXPECT_EQ((is_simple_power(14, 1)), (false));
    EXPECT_EQ((is_simple_power(1, 235)), (true));
}

TEST(Probe, is_simple_power_02) {
    EXPECT_EQ((is_simple_power(128, 24)), (false));
    EXPECT_EQ((is_simple_power(14, 20)), (false));
    EXPECT_EQ((is_simple_power(24, 2)), (false));
    EXPECT_EQ((is_simple_power(4, 7)), (false));
    EXPECT_EQ((is_simple_power(8, 10)), (false));
    EXPECT_EQ((is_simple_power(12, 231)), (false));
    EXPECT_EQ((is_simple_power(10, 10)), (true));
    EXPECT_EQ((is_simple_power(21, 13)), (false));
    EXPECT_EQ((is_simple_power(143214, 6)), (false));
    EXPECT_EQ((is_simple_power(6, 9)), (false));
    EXPECT_EQ((is_simple_power(-9, 751)), (false));
    EXPECT_EQ((is_simple_power(12, 4)), (false));
    EXPECT_EQ((is_simple_power(2, -629)), (false));
    EXPECT_EQ((is_simple_power(128, 12)), (false));
    EXPECT_EQ((is_simple_power(4, -77)), (false));
    EXPECT_EQ((is_simple_power(4, 5)), (false));
    EXPECT_EQ((is_simple_power(8, 456)), (false));
    EXPECT_EQ((is_simple_power(25, 24)), (false));
    EXPECT_EQ((is_simple_power(1, 4)), (true));
    EXPECT_EQ((is_simple_power(24, 11)), (false));
    EXPECT_EQ((is_simple_power(465, 7)), (false));
    EXPECT_EQ((is_simple_power(7, 16)), (false));
    EXPECT_EQ((is_simple_power(-1, 13)), (false));
}

TEST(Probe, iscuber_01) {
    EXPECT_EQ((iscuber(4)), (false));
    EXPECT_EQ((iscuber(180)), (false));
    EXPECT_EQ((iscuber(249)), (false));
    EXPECT_EQ((iscuber(64)), (true));
    EXPECT_EQ((iscuber(20)), (false));
    EXPECT_EQ((iscuber(0)), (true));
    EXPECT_EQ((iscuber(-792)), (false));
    EXPECT_EQ((iscuber(66)), (false));
    EXPECT_EQ((iscuber(24)), (false));
    EXPECT_EQ((iscuber(22)), (false));
    EXPECT_EQ((iscuber(12)), (false));
    EXPECT_EQ((iscuber(2)), (false));
    EXPECT_EQ((iscuber(1729)), (false));
    EXPECT_EQ((iscuber(11)), (false));
    EXPECT_EQ((iscuber(580)), (false));
    EXPECT_EQ((iscuber(29)), (false));
    EXPECT_EQ((iscuber(-6)), (false));
    EXPECT_EQ((iscuber(-5)), (false));
    EXPECT_EQ((iscuber(-481)), (false));
    EXPECT_EQ((iscuber(13)), (false));
    EXPECT_EQ((iscuber(6)), (false));
    EXPECT_EQ((iscuber(-59)), (false));
    EXPECT_EQ((iscuber(9)), (false));
    EXPECT_EQ((iscuber(-2)), (false));
    EXPECT_EQ((iscuber(182)), (false));
}

TEST(Probe, iscuber_02) {
    EXPECT_EQ((iscuber(1)), (true));
    EXPECT_EQ((iscuber(28)), (false));
    EXPECT_EQ((iscuber(-669)), (false));
    EXPECT_EQ((iscuber(549)), (false));
    EXPECT_EQ((iscuber(-653)), (false));
    EXPECT_EQ((iscuber(1731)), (false));
    EXPECT_EQ((iscuber(30)), (false));
    EXPECT_EQ((iscuber(-8)), (true));
    EXPECT_EQ((iscuber(1730)), (false));
    EXPECT_EQ((iscuber(-35)), (false));
    EXPECT_EQ((iscuber(7)), (false));
    EXPECT_EQ((iscuber(146)), (false));
    EXPECT_EQ((iscuber(14)), (false));
    EXPECT_EQ((iscuber(635)), (false));
    EXPECT_EQ((iscuber(168)), (false));
    EXPECT_EQ((iscuber(-319)), (false));
    EXPECT_EQ((iscuber(880)), (false));
    EXPECT_EQ((iscuber(23)), (false));
    EXPECT_EQ((iscuber(-631)), (false));
    EXPECT_EQ((iscuber(-9)), (false));
    EXPECT_EQ((iscuber(10)), (false));
    EXPECT_EQ((iscuber(-808)), (false));
    EXPECT_EQ((iscuber(592)), (false));
}

TEST(Probe, hex_key_01) {
    EXPECT_EQ((hex_key(std::string("cvMd7 7"))), (2));
    EXPECT_EQ((hex_key(std::string("LG3f"))), (1));
    EXPECT_EQ((hex_key(std::string("Zv2GD6m0f"))), (2));
    EXPECT_EQ((hex_key(std::string("23456789ABCDED0"))), (7));
    EXPECT_EQ((hex_key(std::string("R"))), (0));
    EXPECT_EQ((hex_key(std::string("MnmTDjAYG"))), (1));
    EXPECT_EQ((hex_key(std::string("112233445566778899AABBCCDDEEFF00"))), (12));
    EXPECT_EQ((hex_key(std::string(" Co37WWcUj"))), (2));
    EXPECT_EQ((hex_key(std::string("1077E"))), (2));
    EXPECT_EQ((hex_key(std::string("ZY9ol 9"))), (0));
    EXPECT_EQ((hex_key(std::string("amrd"))), (0));
    EXPECT_EQ((hex_key(std::string("lGNobYNFmRHN"))), (0));
    EXPECT_EQ((hex_key(std::string("ABEDzt1AW3"))), (3));
    EXPECT_EQ((hex_key(std::string("27cr9"))), (2));
    EXPECT_EQ((hex_key(std::string("it7"))), (1));
    EXPECT_EQ((hex_key(std::string("2tQ220"))), (3));
    EXPECT_EQ((hex_key(std::string("4r5"))), (1));
    EXPECT_EQ((hex_key(std::string("123456789ABCDEF0"))), (6));
    EXPECT_EQ((hex_key(std::string("N4Uwipz14Asm"))), (0));
    EXPECT_EQ((hex_key(std::string("0pt77E"))), (2));
    EXPECT_EQ((hex_key(std::string("2zn20"))), (2));
    EXPECT_EQ((hex_key(std::string("7OrzLILQO"))), (1));
    EXPECT_EQ((hex_key(std::string("1lu0zyXUVJV"))), (0));
    EXPECT_EQ((hex_key(std::string("1s2233445566778899AABBCCDDEEFF00"))), (12));
    EXPECT_EQ((hex_key(std::string("XpKIaF"))), (0));
}

TEST(Probe, hex_key_02) {
    EXPECT_EQ((hex_key(std::string("3W"))), (1));
    EXPECT_EQ((hex_key(std::string("11223344556677889AABBCCDDEEFF00"))), (12));
    EXPECT_EQ((hex_key(std::string("K"))), (0));
    EXPECT_EQ((hex_key(std::string("k85"))), (1));
    EXPECT_EQ((hex_key(std::string("07E"))), (1));
    EXPECT_EQ((hex_key(std::string("E"))), (0));
    EXPECT_EQ((hex_key(std::string("PFAKB"))), (1));
    EXPECT_EQ((hex_key(std::string("A"))), (0));
    EXPECT_EQ((hex_key(std::string("cmBJJipQD"))), (2));
    EXPECT_EQ((hex_key(std::string("wtZqlTu"))), (0));
    EXPECT_EQ((hex_key(std::string("vP4OVu"))), (0));
    EXPECT_EQ((hex_key(std::string("123456789ABDEF0"))), (6));
    EXPECT_EQ((hex_key(std::string("QR"))), (0));
    EXPECT_EQ((hex_key(std::string("P"))), (0));
    EXPECT_EQ((hex_key(std::string(" jxlyean"))), (0));
    EXPECT_EQ((hex_key(std::string("ArD1bA33"))), (3));
    EXPECT_EQ((hex_key(std::string(" RPa Y"))), (0));
    EXPECT_EQ((hex_key(std::string("eB"))), (1));
    EXPECT_EQ((hex_key(std::string("02"))), (1));
    EXPECT_EQ((hex_key(std::string("y"))), (0));
    EXPECT_EQ((hex_key(std::string("ABED1AV3"))), (3));
    EXPECT_EQ((hex_key(std::string("ABEjD1A33"))), (4));
    EXPECT_EQ((hex_key(std::string("3eQRbK"))), (1));
}

TEST(Probe, decimal_to_binary_01) {
    EXPECT_EQ((decimal_to_binary(1)), (std::string("db1db")));
    EXPECT_EQ((decimal_to_binary(-764)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(15)), (std::string("db1111db")));
    EXPECT_EQ((decimal_to_binary(-7)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(14)), (std::string("db1110db")));
    EXPECT_EQ((decimal_to_binary(23)), (std::string("db10111db")));
    EXPECT_EQ((decimal_to_binary(7)), (std::string("db111db")));
    EXPECT_EQ((decimal_to_binary(3)), (std::string("db11db")));
    EXPECT_EQ((decimal_to_binary(-737)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(85)), (std::string("db1010101db")));
    EXPECT_EQ((decimal_to_binary(-978)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(25)), (std::string("db11001db")));
    EXPECT_EQ((decimal_to_binary(0)), (std::string("db0db")));
    EXPECT_EQ((decimal_to_binary(18)), (std::string("db10010db")));
    EXPECT_EQ((decimal_to_binary(-242)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(101)), (std::string("db1100101db")));
    EXPECT_EQ((decimal_to_binary(-4)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(-793)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(6)), (std::string("db110db")));
    EXPECT_EQ((decimal_to_binary(592)), (std::string("db1001010000db")));
    EXPECT_EQ((decimal_to_binary(27)), (std::string("db11011db")));
    EXPECT_EQ((decimal_to_binary(99999)), (std::string("db11000011010011111db")));
    EXPECT_EQ((decimal_to_binary(452)), (std::string("db111000100db")));
    EXPECT_EQ((decimal_to_binary(102)), (std::string("db1100110db")));
    EXPECT_EQ((decimal_to_binary(4)), (std::string("db100db")));
}

TEST(Probe, decimal_to_binary_02) {
    EXPECT_EQ((decimal_to_binary(-5)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(-253)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(31)), (std::string("db11111db")));
    EXPECT_EQ((decimal_to_binary(-157)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(-211)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(-581)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(9)), (std::string("db1001db")));
    EXPECT_EQ((decimal_to_binary(19)), (std::string("db10011db")));
    EXPECT_EQ((decimal_to_binary(2)), (std::string("db10db")));
    EXPECT_EQ((decimal_to_binary(231)), (std::string("db11100111db")));
    EXPECT_EQ((decimal_to_binary(17)), (std::string("db10001db")));
    EXPECT_EQ((decimal_to_binary(-998)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(11)), (std::string("db1011db")));
    EXPECT_EQ((decimal_to_binary(-12)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(88)), (std::string("db1011000db")));
    EXPECT_EQ((decimal_to_binary(24)), (std::string("db11000db")));
    EXPECT_EQ((decimal_to_binary(933)), (std::string("db1110100101db")));
    EXPECT_EQ((decimal_to_binary(33)), (std::string("db100001db")));
    EXPECT_EQ((decimal_to_binary(-10)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(34)), (std::string("db100010db")));
    EXPECT_EQ((decimal_to_binary(-911)), (std::string("dbdb")));
    EXPECT_EQ((decimal_to_binary(793)), (std::string("db1100011001db")));
    EXPECT_EQ((decimal_to_binary(-123)), (std::string("dbdb")));
}

TEST(Probe, is_happy_01) {
    EXPECT_EQ((is_happy(std::string("xyy"))), (false));
    EXPECT_EQ((is_happy(std::string("iopaxioi"))), (false));
    EXPECT_EQ((is_happy(std::string("xy"))), (false));
    EXPECT_EQ((is_happy(std::string("Iatbc0d"))), (true));
    EXPECT_EQ((is_happy(std::string("ana"))), (false));
    EXPECT_EQ((is_happy(std::string("iopaxpoi"))), (true));
    EXPECT_EQ((is_happy(std::string("a"))), (false));
    EXPECT_EQ((is_happy(std::string("zZHo"))), (true));
    EXPECT_EQ((is_happy(std::string("aaGS6bb"))), (false));
    EXPECT_EQ((is_happy(std::string("Ust9T7n6"))), (true));
    EXPECT_EQ((is_happy(std::string("k"))), (false));
    EXPECT_EQ((is_happy(std::string("aabb"))), (false));
    EXPECT_EQ((is_happy(std::string("iopaxp2oi"))), (true));
    EXPECT_EQ((is_happy(std::string("iovpaxioi"))), (false));
    EXPECT_EQ((is_happy(std::string("abd"))), (true));
    EXPECT_EQ((is_happy(std::string("iwopasioi"))), (false));
    EXPECT_EQ((is_happy(std::string("kJa"))), (true));
    EXPECT_EQ((is_happy(std::string("lsk"))), (true));
    EXPECT_EQ((is_happy(std::string("E"))), (false));
    EXPECT_EQ((is_happy(std::string("o3TQbRZ"))), (true));
    EXPECT_EQ((is_happy(std::string("9"))), (false));
    EXPECT_EQ((is_happy(std::string(""))), (false));
    EXPECT_EQ((is_happy(std::string("ab2"))), (true));
    EXPECT_EQ((is_happy(std::string("xpywy"))), (false));
    EXPECT_EQ((is_happy(std::string("fbsnfGchq1mw"))), (true));
}

TEST(Probe, is_happy_02) {
    EXPECT_EQ((is_happy(std::string("xyY"))), (true));
    EXPECT_EQ((is_happy(std::string("eMWICohv0ns"))), (true));
    EXPECT_EQ((is_happy(std::string("Yfpi5lF4EZej"))), (true));
    EXPECT_EQ((is_happy(std::string("abb"))), (false));
    EXPECT_EQ((is_happy(std::string("Baabb"))), (false));
    EXPECT_EQ((is_happy(std::string("mabb"))), (false));
    EXPECT_EQ((is_happy(std::string("OzFBwFg7e5A"))), (true));
    EXPECT_EQ((is_happy(std::string("qva"))), (true));
    EXPECT_EQ((is_happy(std::string("iopaxio"))), (true));
    EXPECT_EQ((is_happy(std::string("pDPqHd4mwUA5"))), (true));
    EXPECT_EQ((is_happy(std::string("xAyp"))), (true));
    EXPECT_EQ((is_happy(std::string("3cKPDZl"))), (true));
    EXPECT_EQ((is_happy(std::string("0abcd"))), (true));
    EXPECT_EQ((is_happy(std::string("U"))), (false));
    EXPECT_EQ((is_happy(std::string("2kFYP3"))), (true));
    EXPECT_EQ((is_happy(std::string("ktM28TcX3Xp5"))), (false));
    EXPECT_EQ((is_happy(std::string("ioavpoi"))), (true));
    EXPECT_EQ((is_happy(std::string("2jau655v"))), (false));
    EXPECT_EQ((is_happy(std::string("xiRjuV8"))), (true));
    EXPECT_EQ((is_happy(std::string("1 z4JmX2"))), (true));
    EXPECT_EQ((is_happy(std::string("0xO"))), (true));
    EXPECT_EQ((is_happy(std::string("DiopaxioQ"))), (true));
    EXPECT_EQ((is_happy(std::string("abljd"))), (true));
}
