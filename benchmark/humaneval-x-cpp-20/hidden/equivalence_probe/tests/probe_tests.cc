// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_20.h"

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

TEST(Probe, cycpattern_check_01) {
    EXPECT_EQ((cycpattern_check(std::string("xyzw"), std::string("abc"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("Gabd"), std::string("tabd"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("J"), std::string("whattup"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("5erEf"), std::string("K1QriTI"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("ell"), std::string("c50 "))), (false));
    EXPECT_EQ((cycpattern_check(std::string("JgziJkRhLVlD"), std::string("psus"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("efef"), std::string("6KTY"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("whattup"), std::string("biKbK3sQxY4"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("psus"), std::string("ptut"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("abgab"), std::string("L4lSeuHpCHtM"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("mB6G"), std::string("rhJello"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("whassup"), std::string(" "))), (false));
    EXPECT_EQ((cycpattern_check(std::string("hlo"), std::string("ptut"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("whafssu"), std::string("xyzw"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("himenss"), std::string("e39lT"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("bab"), std::string("Wpsfs"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("exlo"), std::string("QpwY 0"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("abJ"), std::string("xyz"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("abd"), std::string("xyzw"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("TZ94NvE7K"), std::string("8xyD"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("winett"), std::string("MwcBGS36RZk"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("1Heff"), std::string("whattup"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("PYO4FeyK "), std::string("whassUu2"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("b"), std::string("lY"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("EujSZQpZFK"), std::string("fee"))), (false));
}

TEST(Probe, cycpattern_check_02) {
    EXPECT_EQ((cycpattern_check(std::string("xtZIyzw"), std::string("WuoJn7OQprI"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("wiJnemtt"), std::string("aea"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("ba"), std::string("abd"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("simen"), std::string("aabb"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("Ereh"), std::string("fee"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("baa"), std::string("ptut"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("abcd"), std::string("NGu6 xA13"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("whattup"), std::string("ptut"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("G44Tp"), std::string("himeUnss"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("ZIGVXIX08x4C"), std::string("yelo"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("lFRXt"), std::string("Hy 1"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("ONllNk"), std::string("CwUSvwDQdmT"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("abcd"), std::string("ps"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("xyw"), std::string("imeen"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("whassup"), std::string("eeff"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("ptut"), std::string("eeff"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("efef"), std::string("NZh06yTS"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("eeff"), std::string("bb"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("gwsyO"), std::string(" zy"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("tC"), std::string("OZA6xAf5"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("eeTf"), std::string("aabb"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("YwAT77oLP"), std::string("e"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("xyzw"), std::string("efef"))), (false));
}

TEST(Probe, even_odd_count_01) {
    EXPECT_EQ((even_odd_count(523)), (std::vector<int >{1, 2}));
    EXPECT_EQ((even_odd_count(-10)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(-8)), (std::vector<int >{1, 0}));
    EXPECT_EQ((even_odd_count(-4)), (std::vector<int >{1, 0}));
    EXPECT_EQ((even_odd_count(28)), (std::vector<int >{2, 0}));
    EXPECT_EQ((even_odd_count(3)), (std::vector<int >{0, 1}));
    EXPECT_EQ((even_odd_count(0)), (std::vector<int >{1, 0}));
    EXPECT_EQ((even_odd_count(-77)), (std::vector<int >{0, 2}));
    EXPECT_EQ((even_odd_count(18)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(212)), (std::vector<int >{2, 1}));
    EXPECT_EQ((even_odd_count(9)), (std::vector<int >{0, 1}));
    EXPECT_EQ((even_odd_count(100)), (std::vector<int >{2, 1}));
    EXPECT_EQ((even_odd_count(442)), (std::vector<int >{3, 0}));
    EXPECT_EQ((even_odd_count(-45349)), (std::vector<int >{2, 3}));
    EXPECT_EQ((even_odd_count(7)), (std::vector<int >{0, 1}));
    EXPECT_EQ((even_odd_count(6)), (std::vector<int >{1, 0}));
    EXPECT_EQ((even_odd_count(22)), (std::vector<int >{2, 0}));
    EXPECT_EQ((even_odd_count(190)), (std::vector<int >{1, 2}));
    EXPECT_EQ((even_odd_count(533)), (std::vector<int >{0, 3}));
    EXPECT_EQ((even_odd_count(-5)), (std::vector<int >{0, 1}));
    EXPECT_EQ((even_odd_count(-45345)), (std::vector<int >{2, 3}));
    EXPECT_EQ((even_odd_count(17)), (std::vector<int >{0, 2}));
    EXPECT_EQ((even_odd_count(-345819)), (std::vector<int >{2, 4}));
    EXPECT_EQ((even_odd_count(12)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(-345822)), (std::vector<int >{4, 2}));
}

TEST(Probe, even_odd_count_02) {
    EXPECT_EQ((even_odd_count(117)), (std::vector<int >{0, 3}));
    EXPECT_EQ((even_odd_count(-80)), (std::vector<int >{2, 0}));
    EXPECT_EQ((even_odd_count(10)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(11)), (std::vector<int >{0, 2}));
    EXPECT_EQ((even_odd_count(26)), (std::vector<int >{2, 0}));
    EXPECT_EQ((even_odd_count(-6)), (std::vector<int >{1, 0}));
    EXPECT_EQ((even_odd_count(1)), (std::vector<int >{0, 1}));
    EXPECT_EQ((even_odd_count(469)), (std::vector<int >{2, 1}));
    EXPECT_EQ((even_odd_count(4)), (std::vector<int >{1, 0}));
    EXPECT_EQ((even_odd_count(21)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(136)), (std::vector<int >{1, 2}));
    EXPECT_EQ((even_odd_count(846)), (std::vector<int >{3, 0}));
    EXPECT_EQ((even_odd_count(274)), (std::vector<int >{2, 1}));
    EXPECT_EQ((even_odd_count(235)), (std::vector<int >{1, 2}));
    EXPECT_EQ((even_odd_count(-835)), (std::vector<int >{1, 2}));
    EXPECT_EQ((even_odd_count(543)), (std::vector<int >{1, 2}));
    EXPECT_EQ((even_odd_count(-345821)), (std::vector<int >{3, 3}));
    EXPECT_EQ((even_odd_count(30)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(29)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(99999)), (std::vector<int >{0, 5}));
    EXPECT_EQ((even_odd_count(-465)), (std::vector<int >{2, 1}));
    EXPECT_EQ((even_odd_count(-78)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(-779)), (std::vector<int >{0, 3}));
}

TEST(Probe, int_to_mini_romank_01) {
    EXPECT_EQ((int_to_mini_romank(20)), (std::string("xx")));
    EXPECT_EQ((int_to_mini_romank(-5)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(532)), (std::string("dxxxii")));
    EXPECT_EQ((int_to_mini_romank(-10)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(129)), (std::string("cxxix")));
    EXPECT_EQ((int_to_mini_romank(486)), (std::string("cdlxxxvi")));
    EXPECT_EQ((int_to_mini_romank(-603)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(8)), (std::string("viii")));
    EXPECT_EQ((int_to_mini_romank(100)), (std::string("c")));
    EXPECT_EQ((int_to_mini_romank(18)), (std::string("xviii")));
    EXPECT_EQ((int_to_mini_romank(10)), (std::string("x")));
    EXPECT_EQ((int_to_mini_romank(251)), (std::string("ccli")));
    EXPECT_EQ((int_to_mini_romank(-763)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(992)), (std::string("cmxcii")));
    EXPECT_EQ((int_to_mini_romank(179)), (std::string("clxxix")));
    EXPECT_EQ((int_to_mini_romank(99999)), (std::string("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmcmxcix")));
    EXPECT_EQ((int_to_mini_romank(13)), (std::string("xiii")));
    EXPECT_EQ((int_to_mini_romank(11)), (std::string("xi")));
    EXPECT_EQ((int_to_mini_romank(17)), (std::string("xvii")));
    EXPECT_EQ((int_to_mini_romank(899)), (std::string("dcccxcix")));
    EXPECT_EQ((int_to_mini_romank(22)), (std::string("xxii")));
    EXPECT_EQ((int_to_mini_romank(-8)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(92)), (std::string("xcii")));
    EXPECT_EQ((int_to_mini_romank(428)), (std::string("cdxxviii")));
    EXPECT_EQ((int_to_mini_romank(1000)), (std::string("m")));
}

TEST(Probe, int_to_mini_romank_02) {
    EXPECT_EQ((int_to_mini_romank(43)), (std::string("xliii")));
    EXPECT_EQ((int_to_mini_romank(375)), (std::string("ccclxxv")));
    EXPECT_EQ((int_to_mini_romank(2)), (std::string("ii")));
    EXPECT_EQ((int_to_mini_romank(366)), (std::string("ccclxvi")));
    EXPECT_EQ((int_to_mini_romank(-356)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(19)), (std::string("xix")));
    EXPECT_EQ((int_to_mini_romank(3)), (std::string("iii")));
    EXPECT_EQ((int_to_mini_romank(44)), (std::string("xliv")));
    EXPECT_EQ((int_to_mini_romank(24)), (std::string("xxiv")));
    EXPECT_EQ((int_to_mini_romank(-498)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(14)), (std::string("xiv")));
    EXPECT_EQ((int_to_mini_romank(842)), (std::string("dcccxlii")));
    EXPECT_EQ((int_to_mini_romank(5)), (std::string("v")));
    EXPECT_EQ((int_to_mini_romank(500)), (std::string("d")));
    EXPECT_EQ((int_to_mini_romank(315)), (std::string("cccxv")));
    EXPECT_EQ((int_to_mini_romank(-7)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(136)), (std::string("cxxxvi")));
    EXPECT_EQ((int_to_mini_romank(152)), (std::string("clii")));
    EXPECT_EQ((int_to_mini_romank(-301)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(-2)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(42)), (std::string("xlii")));
    EXPECT_EQ((int_to_mini_romank(258)), (std::string("cclviii")));
    EXPECT_EQ((int_to_mini_romank(-65)), (std::string("")));
}

TEST(Probe, right_angle_triangle_01) {
    EXPECT_EQ((right_angle_triangle(48.0f, 5.0f, 1.0f)), (false));
    EXPECT_EQ((right_angle_triangle(90.0f, 13.0f, 3.0f)), (false));
    EXPECT_EQ((right_angle_triangle(5.5f, 17.0f, -3.07999992f)), (false));
    EXPECT_EQ((right_angle_triangle(9.52999973f, 8.0f, -14.1000004f)), (false));
    EXPECT_EQ((right_angle_triangle(17.0f, -15.1000004f, 17.0f)), (false));
    EXPECT_EQ((right_angle_triangle(-19.5f, 17.0f, -5.78000021f)), (false));
    EXPECT_EQ((right_angle_triangle(18.7999992f, -6.9000001f, 6.30999994f)), (false));
    EXPECT_EQ((right_angle_triangle(15.0f, 7.0f, 19.5f)), (false));
    EXPECT_EQ((right_angle_triangle(-12.3999996f, 24.0f, -2.79999995f)), (false));
    EXPECT_EQ((right_angle_triangle(24.0f, 4.9000001f, -2.44000006f)), (false));
    EXPECT_EQ((right_angle_triangle(15.0f, 4.0f, 17.0f)), (false));
    EXPECT_EQ((right_angle_triangle(2.0f, 17.8999996f, -5.69999981f)), (false));
    EXPECT_EQ((right_angle_triangle(10.0f, 90.0f, -4.19999981f)), (false));
    EXPECT_EQ((right_angle_triangle(5.0f, 2.0f, 24.0f)), (false));
    EXPECT_EQ((right_angle_triangle(7.30000019f, -17.7000008f, 73.0f)), (false));
    EXPECT_EQ((right_angle_triangle(4.0f, 8.0f, -4.19999981f)), (false));
    EXPECT_EQ((right_angle_triangle(90.0f, 25.0f, 12.0f)), (false));
    EXPECT_EQ((right_angle_triangle(1.0f, 4.0f, 90.0f)), (false));
    EXPECT_EQ((right_angle_triangle(-4.5f, 13.3000002f, -1.70000005f)), (false));
    EXPECT_EQ((right_angle_triangle(-17.3999996f, 17.0f, 19.7000008f)), (false));
    EXPECT_EQ((right_angle_triangle(25.0f, 90.0f, 10.1000004f)), (false));
    EXPECT_EQ((right_angle_triangle(17.0f, 5.0f, 12.0f)), (false));
    EXPECT_EQ((right_angle_triangle(73.0f, 5.0f, 2.0f)), (false));
    EXPECT_EQ((right_angle_triangle(3.0f, 7.0f, 4.0f)), (false));
    EXPECT_EQ((right_angle_triangle(5.0f, 1.0f, 12.0f)), (false));
}

TEST(Probe, right_angle_triangle_02) {
    EXPECT_EQ((right_angle_triangle(2.0f, 55.0f, -14.3000002f)), (false));
    EXPECT_EQ((right_angle_triangle(12.0f, 3.0f, 48.0f)), (false));
    EXPECT_EQ((right_angle_triangle(5.0f, 10.0f, 10.0f)), (false));
    EXPECT_EQ((right_angle_triangle(90.0f, 7.0f, 24.0f)), (false));
    EXPECT_EQ((right_angle_triangle(10.0f, 55.0f, 10.0f)), (false));
    EXPECT_EQ((right_angle_triangle(48.0f, 8.19999981f, 8.0f)), (false));
    EXPECT_EQ((right_angle_triangle(3.0f, -1.78999996f, -11.3999996f)), (false));
    EXPECT_EQ((right_angle_triangle(2.5999999f, 90.0f, -15.5f)), (false));
    EXPECT_EQ((right_angle_triangle(11.3999996f, -0.769999981f, 24.0f)), (false));
    EXPECT_EQ((right_angle_triangle(3.70000005f, 4.53000021f, -5.11999989f)), (false));
    EXPECT_EQ((right_angle_triangle(55.0f, 4.55999994f, 13.0f)), (false));
    EXPECT_EQ((right_angle_triangle(15.0f, 5.9000001f, -9.19999981f)), (false));
    EXPECT_EQ((right_angle_triangle(8.0f, 3.0f, 12.0f)), (false));
    EXPECT_EQ((right_angle_triangle(2.0f, 8.0f, 4.6500001f)), (false));
    EXPECT_EQ((right_angle_triangle(48.0f, 48.0f, -2.29999995f)), (false));
    EXPECT_EQ((right_angle_triangle(73.0f, 7.0f, 13.0f)), (false));
    EXPECT_EQ((right_angle_triangle(48.0f, 48.0f, 6.0f)), (false));
    EXPECT_EQ((right_angle_triangle(15.0f, 48.0f, -15.3999996f)), (false));
    EXPECT_EQ((right_angle_triangle(4.19999981f, 13.0f, 8.0f)), (false));
    EXPECT_EQ((right_angle_triangle(-19.1000004f, -1.35000002f, 5.0f)), (false));
    EXPECT_EQ((right_angle_triangle(10.0f, 0.100000001f, 12.3999996f)), (false));
    EXPECT_EQ((right_angle_triangle(1.61000001f, 14.3999996f, -6.5999999f)), (false));
    EXPECT_EQ((right_angle_triangle(-7.30000019f, 15.0f, 3.0f)), (false));
}

TEST(Probe, find_max_01) {
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("this"), std::string("a"), std::string("a"), std::string("prrk")})), (std::string("this")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("footbtt"), std::string("stcring")})), (std::string("stcring")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("tis")})), (std::string("tis")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("play"), std::string("this"), std::string("game"), std::string("of"), std::string("footbott")})), (std::string("footbott")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("name"), std::string("enam"), std::string("game")})), (std::string("enam")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("LS"), std::string("aaaaaaa"), std::string("string"), std::string("p"), std::string("is"), std::string("GJ84V16 An"), std::string("nation")})), (std::string("GJ84V16 An")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("gonna"), std::string("gp3ae"), std::string("sy8trring"), std::string("2pCrk"), std::string("CCYIela5lTtz"), std::string("thf2is"), std::string("game")})), (std::string("CCYIela5lTtz")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string(""), std::string("cc"), std::string("prrk"), std::string("mad"), std::string("cHybPa"), std::string("string"), std::string("pK")})), (std::string("cHybPa")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("arDe"), std::string("rock"), std::string("qXMVDeRComh"), std::string("a"), std::string("Xi"), std::string("footbSott"), std::string("of"), std::string("a6me")})), (std::string("qXMVDeRComh")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("game"), std::string("enam"), std::string("name")})), (std::string("enam")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("are"), std::string("gonna"), std::string("rock")})), (std::string("gonna")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("is"), std::string("bc")})), (std::string("bc")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("this"), std::string("is"), std::string("prrk"), std::string("a")})), (std::string("this")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("aaaaaaa"), std::string("cc"), std::string("bb")})), (std::string("aaaaaaa")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("bb"), std::string("iHo")})), (std::string("iHo")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("cba"), std::string("0VkzGwcb7="), std::string("zZBsH"), std::string("b"), std::string("game"), std::string("sr"), std::string("name")})), (std::string("0VkzGwcb7=")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("7")})), (std::string("7")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("this"), std::string("is"), std::string("a"), std::string("prrk"), std::string("name")})), (std::string("name")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("name"), std::string("of"), std::string("string")})), (std::string("string")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("a"), std::string("gth6i"), std::string("m60X"), std::string("aion"), std::string("q"), std::string("play")})), (std::string("gth6i")));
    EXPECT_EQ((find_max(std::vector<std::string >{})), (std::string("")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("play"), std::string("this"), std::string("game"), std::string("of"), std::string("footbott"), std::string("")})), (std::string("footbott")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("aaaaaaa"), std::string("are"), std::string("cc")})), (std::string("are")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("game"), std::string("JsS}sW6y"), std::string("tfskSeXDr")})), (std::string("tfskSeXDr")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("LS"), std::string("OMnWMDn3")})), (std::string("OMnWMDn3")));
}

TEST(Probe, find_max_02) {
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("we"), std::string("rock"), std::string("gonna"), std::string("are")})), (std::string("gonna")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("name"), std::string("e"), std::string("game")})), (std::string("game")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("hvPtzw"), std::string(""), std::string("tril3s"), std::string("oS"), std::string("footbott"), std::string("Fkam"), std::string("is"), std::string("cad")})), (std::string("hvPtzw")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("oation"), std::string("Raaaaa9"), std::string("6nCe"), std::string("plqay")})), (std::string("oation")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("this"), std::string("prrk"), std::string("a"), std::string("is")})), (std::string("this")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("this"), std::string("is"), std::string("a"), std::string("prrk"), std::string("enam")})), (std::string("enam")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("name"), std::string("uame")})), (std::string("name")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("we"), std::string("are"), std::string("gonna"), std::string("rock")})), (std::string("gonna")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("IjRJ5NJH"), std::string("fo4otboKtt"), std::string("play")})), (std::string("IjRJ5NJH")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("play"), std::string("play")})), (std::string("play")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("ARzk'rgg ")})), (std::string("ARzk'rgg ")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("c"), std::string("is"), std::string("7")})), (std::string("is")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("yG"), std::string("}) == 'string")})), (std::string("}) == 'string")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("gmnhx")})), (std::string("gmnhx")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("cba"), std::string("n=aqe"), std::string("M4e"), std::string("szrilCng"), std::string("g"), std::string("rO ock")})), (std::string("szrilCng")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("we"), std::string("nation"), std::string("a"), std::string("mad"), std::string("are")})), (std::string("nation")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("this"), std::string("play"), std::string("game"), std::string("of"), std::string("footbott")})), (std::string("footbott")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("WJkdg"), std::string("6HdI"), std::string("we")})), (std::string("WJkdg")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("name"), std::string("of"), std::string("string"), std::string("bb")})), (std::string("string")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("this"), std::string("a"), std::string("is"), std::string("prrk")})), (std::string("this")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("this"), std::string("is"), std::string("a"), std::string("ay")})), (std::string("this")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("are"), std::string(" AXvM GdWVlN"), std::string("")})), (std::string(" AXvM GdWVlN")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("rAWc"), std::string("5V'T01p1h"), std::string("play"), std::string("Enna")})), (std::string("5V'T01p1h")));
}

TEST(Probe, eat_01) {
    EXPECT_EQ((eat(248, -40, 30)), (std::vector<int >{208, 70}));
    EXPECT_EQ((eat(-1, -606, 100)), (std::vector<int >{-607, 706}));
    EXPECT_EQ((eat(-954, 3, 58)), (std::vector<int >{-951, 55}));
    EXPECT_EQ((eat(-2, 26, 21)), (std::vector<int >{19, 0}));
    EXPECT_EQ((eat(7, -3, 2)), (std::vector<int >{4, 5}));
    EXPECT_EQ((eat(12, 3, -1)), (std::vector<int >{11, 0}));
    EXPECT_EQ((eat(6, 12, 7)), (std::vector<int >{13, 0}));
    EXPECT_EQ((eat(6, 27, 3)), (std::vector<int >{9, 0}));
    EXPECT_EQ((eat(8, -626, -5)), (std::vector<int >{-618, 621}));
    EXPECT_EQ((eat(254, 14, 206)), (std::vector<int >{268, 192}));
    EXPECT_EQ((eat(-356, 15, -2)), (std::vector<int >{-358, 0}));
    EXPECT_EQ((eat(11, -6, 10)), (std::vector<int >{5, 16}));
    EXPECT_EQ((eat(10, 5, 9)), (std::vector<int >{15, 4}));
    EXPECT_EQ((eat(22, 1, -81)), (std::vector<int >{-59, 0}));
    EXPECT_EQ((eat(5, 669, -5)), (std::vector<int >{0, 0}));
    EXPECT_EQ((eat(1000, 2, 4)), (std::vector<int >{1002, 2}));
    EXPECT_EQ((eat(2, 5, 7)), (std::vector<int >{7, 2}));
    EXPECT_EQ((eat(4, 832, 6)), (std::vector<int >{10, 0}));
    EXPECT_EQ((eat(2, -817, 7)), (std::vector<int >{-815, 824}));
    EXPECT_EQ((eat(-3, 99999, 1)), (std::vector<int >{-2, 0}));
    EXPECT_EQ((eat(7, 99999, 7)), (std::vector<int >{14, 0}));
    EXPECT_EQ((eat(14, 6, 7)), (std::vector<int >{20, 1}));
    EXPECT_EQ((eat(915, 6, 2)), (std::vector<int >{917, 0}));
    EXPECT_EQ((eat(15, 1000, 17)), (std::vector<int >{32, 0}));
    EXPECT_EQ((eat(-548, 26, 12)), (std::vector<int >{-536, 0}));
}

TEST(Probe, eat_02) {
    EXPECT_EQ((eat(27, 10, 12)), (std::vector<int >{37, 2}));
    EXPECT_EQ((eat(0, 434, 9)), (std::vector<int >{9, 0}));
    EXPECT_EQ((eat(11, 7, 7)), (std::vector<int >{18, 0}));
    EXPECT_EQ((eat(6, 10, 265)), (std::vector<int >{16, 255}));
    EXPECT_EQ((eat(5, 2, 6)), (std::vector<int >{7, 4}));
    EXPECT_EQ((eat(9, 23, 25)), (std::vector<int >{32, 2}));
    EXPECT_EQ((eat(-3, 1, 6)), (std::vector<int >{-2, 5}));
    EXPECT_EQ((eat(497, 6, 19)), (std::vector<int >{503, 13}));
    EXPECT_EQ((eat(5, 21, 12)), (std::vector<int >{17, 0}));
    EXPECT_EQ((eat(920, 14, -777)), (std::vector<int >{143, 0}));
    EXPECT_EQ((eat(4, 730, 7)), (std::vector<int >{11, 0}));
    EXPECT_EQ((eat(2, 6, 2)), (std::vector<int >{4, 0}));
    EXPECT_EQ((eat(45, 12, -881)), (std::vector<int >{-836, 0}));
    EXPECT_EQ((eat(26, 892, -1)), (std::vector<int >{25, 0}));
    EXPECT_EQ((eat(8, 16, 9)), (std::vector<int >{17, 0}));
    EXPECT_EQ((eat(-5, 598, 12345)), (std::vector<int >{593, 11747}));
    EXPECT_EQ((eat(19, 637, 0)), (std::vector<int >{19, 0}));
    EXPECT_EQ((eat(11, 1, 3)), (std::vector<int >{12, 2}));
    EXPECT_EQ((eat(5, 27, -8)), (std::vector<int >{-3, 0}));
    EXPECT_EQ((eat(21, 228, 4)), (std::vector<int >{25, 0}));
    EXPECT_EQ((eat(343, 10, 12345)), (std::vector<int >{353, 12335}));
    EXPECT_EQ((eat(6, -3, 20)), (std::vector<int >{3, 23}));
    EXPECT_EQ((eat(999, 9, 4)), (std::vector<int >{1003, 0}));
}

TEST(Probe, do_algebra_01) {
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("Qer"), std::string("//"), std::string("-")}, std::vector<int >{22, 3, 4, 5})), (22));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-")}, std::vector<int >{2, 3, 5, 4})), (13));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//")}, std::vector<int >{-888, 99999, 5, 196, 4, 5, 28})), (0));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("*"), std::string("+"), std::string("-")}, std::vector<int >{2, 3, 4, 5})), (5));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("**")}, std::vector<int >{2, 3, 4, 5})), (3074));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("*"), std::string("+")}, std::vector<int >{2, 3, 4, 5})), (37));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-")}, std::vector<int >{897, 25, 28, 4, 9})), (1593));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("8CT"), std::string("*")}, std::vector<int >{2, 3, 4, 5, 5})), (2));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("qQN-")}, std::vector<int >{7, 3})), (2));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("*")}, std::vector<int >{24, 378, 2, 37, 99999, 5, 16})), (0));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("-"), std::string("*")}, std::vector<int >{2, 3, 4, 5})), (-10));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-"), std::string("8-b*+jS*e")}, std::vector<int >{7, 3, 4, 9})), (10));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("*"), std::string("+")}, std::vector<int >{-3, 5, -1, 16, -3, 14, 5})), (259));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("2"), std::string("u**"), std::string("h"), std::string("+Ydav"), std::string("e*")}, std::vector<int >{3, -366, 13, 24, 3})), (3));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("//")}, std::vector<int >{5, 4, -1, 8, 9, 3, 29, 3})), (-1));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("2G+1d-spQDGk")}, std::vector<int >{3, 3, 4})), (3));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("*"), std::string("*"), std::string("UZ")}, std::vector<int >{7, 3, 4})), (84));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("-"), std::string("*")}, std::vector<int >{7, 1, 4, 29, -3})), (-108));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("*"), std::string("DE8e ")}, std::vector<int >{7, 3, 4})), (8));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("*")}, std::vector<int >{2, 4, 3, 5})), (0));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("eph "), std::string("*")}, std::vector<int >{2, 3, 4, 5})), (2));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-")}, std::vector<int >{8, 26, 5, 28, 22, 8})), (110));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("+")}, std::vector<int >{2, 3, 4, 5})), (12));
    EXPECT_EQ((do_algebra(std::vector<std::string >{}, std::vector<int >{2, -4, 5})), (2));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("T+g"), std::string("+"), std::string("*vhrin8/Xu"), std::string("n"), std::string("T S")}, std::vector<int >{546, 5, 37, 23, 7, 25, 3, 8})), (546));
}

TEST(Probe, do_algebra_02) {
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("-"), std::string("*"), std::string("+")}, std::vector<int >{2, 808, 4, 5})), (-3225));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-")}, std::vector<int >{4, 9, -743, 4, -318})), (-6687));
    EXPECT_EQ((do_algebra(std::vector<std::string >{}, std::vector<int >{2, 3, 4, 5})), (2));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-")}, std::vector<int >{2, 3, 4, 5, 4})), (9));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("*"), std::string("+")}, std::vector<int >{20, -3, 4, -8, 9, 5})), (-8));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("-")}, std::vector<int >{2, 3, 4, -690})), (1));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("-"), std::string("+")}, std::vector<int >{2, 3, 4, 5})), (9));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("*")}, std::vector<int >{7, 3, 4})), (1372));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("*"), std::string("+"), std::string("-")}, std::vector<int >{2, 3, 4, 5, 2})), (5));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**")}, std::vector<int >{2, 3, 4, 5})), (8));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*")}, std::vector<int >{2, 3, 4, 5})), (14));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-")}, std::vector<int >{2, 3, 4, 5})), (9));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("aCZ"), std::string("*"), std::string("+")}, std::vector<int >{2, 8, 18, 11, 2})), (2));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("/na/")}, std::vector<int >{3, 4, 5})), (3));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("*"), std::string("+")}, std::vector<int >{-9, 3, 4, 5})), (-7));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("A"), std::string("*"), std::string("+")}, std::vector<int >{7, 3, 4, 30})), (7));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-"), std::string("I")}, std::vector<int >{2, 3, 4, 5})), (9));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("*"), std::string("+")}, std::vector<int >{17, -4, -892, -793, 3})), (-960));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("+")}, std::vector<int >{4, 3, 2, 5})), (66));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-")}, std::vector<int >{2, 3, 22, 5})), (63));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//")}, std::vector<int >{2, 3, 5, 5, 7})), (0));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("z7+"), std::string("SZwkI6d"), std::string("FXuNFgHfJLT"), std::string("zIa*")}, std::vector<int >{-3})), (-3));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("*-"), std::string("NlhnTZ+*"), std::string("**")}, std::vector<int >{2, 3, 5, 4})), (2));
}

TEST(Probe, solve_01) {
    EXPECT_EQ((solve(std::string("#$A^d"))), (std::string("#$a^D")));
    EXPECT_EQ((solve(std::string("bSdF"))), (std::string("BsDf")));
    EXPECT_EQ((solve(std::string("#$Ad"))), (std::string("#$aD")));
    EXPECT_EQ((solve(std::string("Cjnab"))), (std::string("cJNAB")));
    EXPECT_EQ((solve(std::string("43288"))), (std::string("88234")));
    EXPECT_EQ((solve(std::string("#ccc"))), (std::string("#CCC")));
    EXPECT_EQ((solve(std::string("431"))), (std::string("134")));
    EXPECT_EQ((solve(std::string("wD8#"))), (std::string("Wd8#")));
    EXPECT_EQ((solve(std::string("2@D@S6#"))), (std::string("2@d@s6#")));
    EXPECT_EQ((solve(std::string("$p$pH@$y"))), (std::string("$P$Ph@$Y")));
    EXPECT_EQ((solve(std::string("#aSDFws5"))), (std::string("#AsdfWS5")));
    EXPECT_EQ((solve(std::string("2@6#"))), (std::string("#6@2")));
    EXPECT_EQ((solve(std::string("AsBDf"))), (std::string("aSbdF")));
    EXPECT_EQ((solve(std::string("AB"))), (std::string("ab")));
    EXPECT_EQ((solve(std::string("aSydF"))), (std::string("AsYDf")));
    EXPECT_EQ((solve(std::string("b"))), (std::string("B")));
    EXPECT_EQ((solve(std::string("PqCCC"))), (std::string("pQccc")));
    EXPECT_EQ((solve(std::string("QQU"))), (std::string("qqu")));
    EXPECT_EQ((solve(std::string("Fw$"))), (std::string("fW$")));
    EXPECT_EQ((solve(std::string("D"))), (std::string("d")));
    EXPECT_EQ((solve(std::string("fV0XtzT"))), (std::string("Fv0xTZt")));
    EXPECT_EQ((solve(std::string("12Z4"))), (std::string("12z4")));
    EXPECT_EQ((solve(std::string("o321"))), (std::string("O321")));
    EXPECT_EQ((solve(std::string("G2I#"))), (std::string("g2i#")));
    EXPECT_EQ((solve(std::string("yf"))), (std::string("YF")));
}

TEST(Probe, solve_02) {
    EXPECT_EQ((solve(std::string("QBo^x"))), (std::string("qbO^X")));
    EXPECT_EQ((solve(std::string("#aR"))), (std::string("#Ar")));
    EXPECT_EQ((solve(std::string("ab"))), (std::string("AB")));
    EXPECT_EQ((solve(std::string("#$^1"))), (std::string("1^$#")));
    EXPECT_EQ((solve(std::string("#C$A^d"))), (std::string("#c$a^D")));
    EXPECT_EQ((solve(std::string("$zAzd"))), (std::string("$ZaZD")));
    EXPECT_EQ((solve(std::string("erbhJED0NkgL"))), (std::string("ERBHjed0nKGl")));
    EXPECT_EQ((solve(std::string("#A@c"))), (std::string("#a@C")));
    EXPECT_EQ((solve(std::string("A"))), (std::string("a")));
    EXPECT_EQ((solve(std::string("mAB"))), (std::string("Mab")));
    EXPECT_EQ((solve(std::string("^@6#"))), (std::string("#6@^")));
    EXPECT_EQ((solve(std::string("hzjEa#sCcEv"))), (std::string("HZJeA#ScCeV")));
    EXPECT_EQ((solve(std::string("paSDbw^r45"))), (std::string("PAsdBW^R45")));
    EXPECT_EQ((solve(std::string("#CC"))), (std::string("#cc")));
    EXPECT_EQ((solve(std::string("#TsdfWr45"))), (std::string("#tSDFwR45")));
    EXPECT_EQ((solve(std::string("1234"))), (std::string("4321")));
    EXPECT_EQ((solve(std::string("5#xXVX7yd0vU"))), (std::string("5#Xxvx7YD0Vu")));
    EXPECT_EQ((solve(std::string("#AsfW^45"))), (std::string("#aSFw^45")));
    EXPECT_EQ((solve(std::string("aSdF"))), (std::string("AsDf")));
    EXPECT_EQ((solve(std::string("Q#$4A^"))), (std::string("q#$4a^")));
    EXPECT_EQ((solve(std::string("6L#1E#D"))), (std::string("6l#1e#d")));
    EXPECT_EQ((solve(std::string(""))), (std::string("")));
    EXPECT_EQ((solve(std::string("f#6@2"))), (std::string("F#6@2")));
}

TEST(Probe, generate_integers_01) {
    EXPECT_EQ((generate_integers(8, 14)), (std::vector<int >{8}));
    EXPECT_EQ((generate_integers(9, 10)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(713, 11)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(12345, 10)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(-745, 5)), (std::vector<int >{-744, -742, -740, -738, -736, -734, -732, -730, -728, -726, -724, -722, -720, -718, -716, -714, -712, -710, -708, -706, -704, -702, -700, -698, -696, -694, -692, -690, -688, -686, -684, -682, -680, -678, -676, -674, -672, -670, -668, -666, -664, -662, -660, -658, -656, -654, -652, -650, -648, -646, -644, -642, -640, -638, -636, -634, -632, -630, -628, -626, -624, -622, -620, -618, -616, -614, -612, -610, -608, -606, -604, -602, -600, -598, -596, -594, -592, -590, -588, -586, -584, -582, -580, -578, -576, -574, -572, -570, -568, -566, -564, -562, -560, -558, -556, -554, -552, -550, -548, -546, -544, -542, -540, -538, -536, -534, -532, -530, -528, -526, -524, -522, -520, -518, -516, -514, -512, -510, -508, -506, -504, -502, -500, -498, -496, -494, -492, -490, -488, -486, -484, -482, -480, -478, -476, -474, -472, -470, -468, -466, -464, -462, -460, -458, -456, -454, -452, -450, -448, -446, -444, -442, -440, -438, -436, -434, -432, -430, -428, -426, -424, -422, -420, -418, -416, -414, -412, -410, -408, -406, -404, -402, -400, -398, -396, -394, -392, -390, -388, -386, -384, -382, -380, -378, -376, -374, -372, -370, -368, -366, -364, -362, -360, -358, -356, -354, -352, -350, -348, -346, -344, -342, -340, -338, -336, -334, -332, -330, -328, -326, -324, -322, -320, -318, -316, -314, -312, -310, -308, -306, -304, -302, -300, -298, -296, -294, -292, -290, -288, -286, -284, -282, -280, -278, -276, -274, -272, -270, -268, -266, -264, -262, -260, -258, -256, -254, -252, -250, -248, -246, -244, -242, -240, -238, -236, -234, -232, -230, -228, -226, -224, -222, -220, -218, -216, -214, -212, -210, -208, -206, -204, -202, -200, -198, -196, -194, -192, -190, -188, -186, -184, -182, -180, -178, -176, -174, -172, -170, -168, -166, -164, -162, -160, -158, -156, -154, -152, -150, -148, -146, -144, -142, -140, -138, -136, -134, -132, -130, -128, -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -4, -2, 0, 2, 4}));
    EXPECT_EQ((generate_integers(-895, -9)), (std::vector<int >{-894, -892, -890, -888, -886, -884, -882, -880, -878, -876, -874, -872, -870, -868, -866, -864, -862, -860, -858, -856, -854, -852, -850, -848, -846, -844, -842, -840, -838, -836, -834, -832, -830, -828, -826, -824, -822, -820, -818, -816, -814, -812, -810, -808, -806, -804, -802, -800, -798, -796, -794, -792, -790, -788, -786, -784, -782, -780, -778, -776, -774, -772, -770, -768, -766, -764, -762, -760, -758, -756, -754, -752, -750, -748, -746, -744, -742, -740, -738, -736, -734, -732, -730, -728, -726, -724, -722, -720, -718, -716, -714, -712, -710, -708, -706, -704, -702, -700, -698, -696, -694, -692, -690, -688, -686, -684, -682, -680, -678, -676, -674, -672, -670, -668, -666, -664, -662, -660, -658, -656, -654, -652, -650, -648, -646, -644, -642, -640, -638, -636, -634, -632, -630, -628, -626, -624, -622, -620, -618, -616, -614, -612, -610, -608, -606, -604, -602, -600, -598, -596, -594, -592, -590, -588, -586, -584, -582, -580, -578, -576, -574, -572, -570, -568, -566, -564, -562, -560, -558, -556, -554, -552, -550, -548, -546, -544, -542, -540, -538, -536, -534, -532, -530, -528, -526, -524, -522, -520, -518, -516, -514, -512, -510, -508, -506, -504, -502, -500, -498, -496, -494, -492, -490, -488, -486, -484, -482, -480, -478, -476, -474, -472, -470, -468, -466, -464, -462, -460, -458, -456, -454, -452, -450, -448, -446, -444, -442, -440, -438, -436, -434, -432, -430, -428, -426, -424, -422, -420, -418, -416, -414, -412, -410, -408, -406, -404, -402, -400, -398, -396, -394, -392, -390, -388, -386, -384, -382, -380, -378, -376, -374, -372, -370, -368, -366, -364, -362, -360, -358, -356, -354, -352, -350, -348, -346, -344, -342, -340, -338, -336, -334, -332, -330, -328, -326, -324, -322, -320, -318, -316, -314, -312, -310, -308, -306, -304, -302, -300, -298, -296, -294, -292, -290, -288, -286, -284, -282, -280, -278, -276, -274, -272, -270, -268, -266, -264, -262, -260, -258, -256, -254, -252, -250, -248, -246, -244, -242, -240, -238, -236, -234, -232, -230, -228, -226, -224, -222, -220, -218, -216, -214, -212, -210, -208, -206, -204, -202, -200, -198, -196, -194, -192, -190, -188, -186, -184, -182, -180, -178, -176, -174, -172, -170, -168, -166, -164, -162, -160, -158, -156, -154, -152, -150, -148, -146, -144, -142, -140, -138, -136, -134, -132, -130, -128, -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10}));
    EXPECT_EQ((generate_integers(-602, 19)), (std::vector<int >{-602, -600, -598, -596, -594, -592, -590, -588, -586, -584, -582, -580, -578, -576, -574, -572, -570, -568, -566, -564, -562, -560, -558, -556, -554, -552, -550, -548, -546, -544, -542, -540, -538, -536, -534, -532, -530, -528, -526, -524, -522, -520, -518, -516, -514, -512, -510, -508, -506, -504, -502, -500, -498, -496, -494, -492, -490, -488, -486, -484, -482, -480, -478, -476, -474, -472, -470, -468, -466, -464, -462, -460, -458, -456, -454, -452, -450, -448, -446, -444, -442, -440, -438, -436, -434, -432, -430, -428, -426, -424, -422, -420, -418, -416, -414, -412, -410, -408, -406, -404, -402, -400, -398, -396, -394, -392, -390, -388, -386, -384, -382, -380, -378, -376, -374, -372, -370, -368, -366, -364, -362, -360, -358, -356, -354, -352, -350, -348, -346, -344, -342, -340, -338, -336, -334, -332, -330, -328, -326, -324, -322, -320, -318, -316, -314, -312, -310, -308, -306, -304, -302, -300, -298, -296, -294, -292, -290, -288, -286, -284, -282, -280, -278, -276, -274, -272, -270, -268, -266, -264, -262, -260, -258, -256, -254, -252, -250, -248, -246, -244, -242, -240, -238, -236, -234, -232, -230, -228, -226, -224, -222, -220, -218, -216, -214, -212, -210, -208, -206, -204, -202, -200, -198, -196, -194, -192, -190, -188, -186, -184, -182, -180, -178, -176, -174, -172, -170, -168, -166, -164, -162, -160, -158, -156, -154, -152, -150, -148, -146, -144, -142, -140, -138, -136, -134, -132, -130, -128, -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(11, 132)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(2, 8)), (std::vector<int >{2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(28, 0)), (std::vector<int >{0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(9, 899)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(-255, -28)), (std::vector<int >{-254, -252, -250, -248, -246, -244, -242, -240, -238, -236, -234, -232, -230, -228, -226, -224, -222, -220, -218, -216, -214, -212, -210, -208, -206, -204, -202, -200, -198, -196, -194, -192, -190, -188, -186, -184, -182, -180, -178, -176, -174, -172, -170, -168, -166, -164, -162, -160, -158, -156, -154, -152, -150, -148, -146, -144, -142, -140, -138, -136, -134, -132, -130, -128, -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28}));
    EXPECT_EQ((generate_integers(809, 0)), (std::vector<int >{0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(194, -3)), (std::vector<int >{-2, 0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(133, 13)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(16, 1000)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(11, 28)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(10, 10)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(850, 91)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(89, 130)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(-8, 132)), (std::vector<int >{-8, -6, -4, -2, 0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(25, 17)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(28, 14)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(3, 4)), (std::vector<int >{4}));
    EXPECT_EQ((generate_integers(-10, 10)), (std::vector<int >{-10, -8, -6, -4, -2, 0, 2, 4, 6, 8}));
}

TEST(Probe, generate_integers_02) {
    EXPECT_EQ((generate_integers(16, 194)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(132, 11)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(16, -128)), (std::vector<int >{-128, -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(-49, 134)), (std::vector<int >{-48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(-2, 26)), (std::vector<int >{-2, 0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(89, 1)), (std::vector<int >{2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(27, 8)), (std::vector<int >{8}));
    EXPECT_EQ((generate_integers(-3, -6)), (std::vector<int >{-6, -4}));
    EXPECT_EQ((generate_integers(-466, -4)), (std::vector<int >{-466, -464, -462, -460, -458, -456, -454, -452, -450, -448, -446, -444, -442, -440, -438, -436, -434, -432, -430, -428, -426, -424, -422, -420, -418, -416, -414, -412, -410, -408, -406, -404, -402, -400, -398, -396, -394, -392, -390, -388, -386, -384, -382, -380, -378, -376, -374, -372, -370, -368, -366, -364, -362, -360, -358, -356, -354, -352, -350, -348, -346, -344, -342, -340, -338, -336, -334, -332, -330, -328, -326, -324, -322, -320, -318, -316, -314, -312, -310, -308, -306, -304, -302, -300, -298, -296, -294, -292, -290, -288, -286, -284, -282, -280, -278, -276, -274, -272, -270, -268, -266, -264, -262, -260, -258, -256, -254, -252, -250, -248, -246, -244, -242, -240, -238, -236, -234, -232, -230, -228, -226, -224, -222, -220, -218, -216, -214, -212, -210, -208, -206, -204, -202, -200, -198, -196, -194, -192, -190, -188, -186, -184, -182, -180, -178, -176, -174, -172, -170, -168, -166, -164, -162, -160, -158, -156, -154, -152, -150, -148, -146, -144, -142, -140, -138, -136, -134, -132, -130, -128, -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -4}));
    EXPECT_EQ((generate_integers(-9, 16)), (std::vector<int >{-8, -6, -4, -2, 0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(-126, -231)), (std::vector<int >{-230, -228, -226, -224, -222, -220, -218, -216, -214, -212, -210, -208, -206, -204, -202, -200, -198, -196, -194, -192, -190, -188, -186, -184, -182, -180, -178, -176, -174, -172, -170, -168, -166, -164, -162, -160, -158, -156, -154, -152, -150, -148, -146, -144, -142, -140, -138, -136, -134, -132, -130, -128, -126}));
    EXPECT_EQ((generate_integers(132, 2)), (std::vector<int >{2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(15, 23)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(10, 131)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(652, 29)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(14, 7)), (std::vector<int >{8}));
    EXPECT_EQ((generate_integers(14, 23)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(20, 14)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(13, 2)), (std::vector<int >{2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(25, -654)), (std::vector<int >{-654, -652, -650, -648, -646, -644, -642, -640, -638, -636, -634, -632, -630, -628, -626, -624, -622, -620, -618, -616, -614, -612, -610, -608, -606, -604, -602, -600, -598, -596, -594, -592, -590, -588, -586, -584, -582, -580, -578, -576, -574, -572, -570, -568, -566, -564, -562, -560, -558, -556, -554, -552, -550, -548, -546, -544, -542, -540, -538, -536, -534, -532, -530, -528, -526, -524, -522, -520, -518, -516, -514, -512, -510, -508, -506, -504, -502, -500, -498, -496, -494, -492, -490, -488, -486, -484, -482, -480, -478, -476, -474, -472, -470, -468, -466, -464, -462, -460, -458, -456, -454, -452, -450, -448, -446, -444, -442, -440, -438, -436, -434, -432, -430, -428, -426, -424, -422, -420, -418, -416, -414, -412, -410, -408, -406, -404, -402, -400, -398, -396, -394, -392, -390, -388, -386, -384, -382, -380, -378, -376, -374, -372, -370, -368, -366, -364, -362, -360, -358, -356, -354, -352, -350, -348, -346, -344, -342, -340, -338, -336, -334, -332, -330, -328, -326, -324, -322, -320, -318, -316, -314, -312, -310, -308, -306, -304, -302, -300, -298, -296, -294, -292, -290, -288, -286, -284, -282, -280, -278, -276, -274, -272, -270, -268, -266, -264, -262, -260, -258, -256, -254, -252, -250, -248, -246, -244, -242, -240, -238, -236, -234, -232, -230, -228, -226, -224, -222, -220, -218, -216, -214, -212, -210, -208, -206, -204, -202, -200, -198, -196, -194, -192, -190, -188, -186, -184, -182, -180, -178, -176, -174, -172, -170, -168, -166, -164, -162, -160, -158, -156, -154, -152, -150, -148, -146, -144, -142, -140, -138, -136, -134, -132, -130, -128, -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8}));
    EXPECT_EQ((generate_integers(-8, 0)), (std::vector<int >{-8, -6, -4, -2, 0}));
    EXPECT_EQ((generate_integers(18, 3)), (std::vector<int >{4, 6, 8}));
    EXPECT_EQ((generate_integers(4, 13)), (std::vector<int >{4, 6, 8}));
}
