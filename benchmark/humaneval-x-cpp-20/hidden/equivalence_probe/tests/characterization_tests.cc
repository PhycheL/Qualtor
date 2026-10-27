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

TEST(Characterization, cycpattern_check_01) {
    EXPECT_EQ((cycpattern_check(std::string("xyzw"), std::string("tDF"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("whattup"), std::string("efef"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("S"), std::string("whassup"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("C34m"), std::string("ba"))), (false));
    EXPECT_EQ((cycpattern_check(std::string(" 4D40szbAm2"), std::string("psus"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("wTassup"), std::string("tinem"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("yello"), std::string("amabb"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("whattup"), std::string("YlBe"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("OQkU4"), std::string("sNmen"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("YVIZEln"), std::string("put"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("tinebOm"), std::string("efef"))), (false));
    EXPECT_EQ((cycpattern_check(std::string("PSw"), std::string("himenss"))), (false));
}

TEST(Characterization, even_odd_count_01) {
    EXPECT_EQ((even_odd_count(20)), (std::vector<int >{2, 0}));
    EXPECT_EQ((even_odd_count(-953)), (std::vector<int >{0, 3}));
    EXPECT_EQ((even_odd_count(-3)), (std::vector<int >{0, 1}));
    EXPECT_EQ((even_odd_count(25)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(2)), (std::vector<int >{1, 0}));
    EXPECT_EQ((even_odd_count(-45347)), (std::vector<int >{2, 3}));
    EXPECT_EQ((even_odd_count(-12)), (std::vector<int >{1, 1}));
    EXPECT_EQ((even_odd_count(24)), (std::vector<int >{2, 0}));
    EXPECT_EQ((even_odd_count(3452)), (std::vector<int >{2, 2}));
    EXPECT_EQ((even_odd_count(123)), (std::vector<int >{1, 2}));
    EXPECT_EQ((even_odd_count(346211)), (std::vector<int >{3, 3}));
    EXPECT_EQ((even_odd_count(682)), (std::vector<int >{3, 0}));
}

TEST(Characterization, int_to_mini_romank_01) {
    EXPECT_EQ((int_to_mini_romank(1)), (std::string("i")));
    EXPECT_EQ((int_to_mini_romank(426)), (std::string("cdxxvi")));
    EXPECT_EQ((int_to_mini_romank(571)), (std::string("dlxxi")));
    EXPECT_EQ((int_to_mini_romank(7)), (std::string("vii")));
    EXPECT_EQ((int_to_mini_romank(6)), (std::string("vi")));
    EXPECT_EQ((int_to_mini_romank(900)), (std::string("cm")));
    EXPECT_EQ((int_to_mini_romank(-3)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(27)), (std::string("xxvii")));
    EXPECT_EQ((int_to_mini_romank(0)), (std::string("")));
    EXPECT_EQ((int_to_mini_romank(996)), (std::string("cmxcvi")));
    EXPECT_EQ((int_to_mini_romank(998)), (std::string("cmxcviii")));
    EXPECT_EQ((int_to_mini_romank(4)), (std::string("iv")));
}

TEST(Characterization, right_angle_triangle_01) {
    EXPECT_EQ((right_angle_triangle(1.0f, 25.0f, 10.0f)), (false));
    EXPECT_EQ((right_angle_triangle(73.0f, 15.0f, -11.1999998f)), (false));
    EXPECT_EQ((right_angle_triangle(-4.13000011f, -11.6999998f, -5.46999979f)), (false));
    EXPECT_EQ((right_angle_triangle(6.0f, 4.0f, -13.8999996f)), (false));
    EXPECT_EQ((right_angle_triangle(1.0f, -2.9000001f, -4.69999981f)), (false));
    EXPECT_EQ((right_angle_triangle(17.6000004f, 17.0f, -12.8999996f)), (false));
    EXPECT_EQ((right_angle_triangle(9.43000031f, -11.3999996f, 18.5f)), (false));
    EXPECT_EQ((right_angle_triangle(-13.1000004f, 15.0f, 2.4000001f)), (false));
    EXPECT_EQ((right_angle_triangle(-4.4000001f, -9.5f, 9.69999981f)), (false));
    EXPECT_EQ((right_angle_triangle(12.0f, 13.0f, 12.0f)), (false));
    EXPECT_EQ((right_angle_triangle(90.0f, -2.70000005f, 12.0f)), (false));
    EXPECT_EQ((right_angle_triangle(17.0f, -17.7000008f, -4.05999994f)), (false));
}

TEST(Characterization, find_max_01) {
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("a5e"), std::string("zAe="), std::string("")})), (std::string("zAe=")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("b")})), (std::string("b")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("m5ad")})), (std::string("m5ad")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("we"), std::string("are"), std::string("a"), std::string("mad"), std::string("nation")})), (std::string("nation")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("abc"), std::string("cba")})), (std::string("abc")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("enam"), std::string("name"), std::string("game")})), (std::string("enam")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("this"), std::string("is"), std::string("a"), std::string("prrk")})), (std::string("this")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("mad"), std::string("aaaaaaa"), std::string("}) == 'string"), std::string("CauNAi")})), (std::string("}) == 'string")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("play"), std::string("this"), std::string("game"), std::string("of"), std::string("footbott"), std::string("game")})), (std::string("footbott")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("prG"), std::string("mad"), std::string("b"), std::string(""), std::string("re"), std::string("7ab")})), (std::string("7ab")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("footbott"), std::string(""), std::string("0"), std::string("7=Xf"), std::string("")})), (std::string("7=Xf")));
    EXPECT_EQ((find_max(std::vector<std::string >{std::string("play"), std::string("play"), std::string("play")})), (std::string("play")));
}

TEST(Characterization, eat_01) {
    EXPECT_EQ((eat(-3, 6, 238)), (std::vector<int >{3, 232}));
    EXPECT_EQ((eat(2, -399, 7)), (std::vector<int >{-397, 406}));
    EXPECT_EQ((eat(507, 6, 4)), (std::vector<int >{511, 0}));
    EXPECT_EQ((eat(26, 12, -1)), (std::vector<int >{25, 0}));
    EXPECT_EQ((eat(-1, 8, 23)), (std::vector<int >{7, 15}));
    EXPECT_EQ((eat(6, -7, -212)), (std::vector<int >{-206, 0}));
    EXPECT_EQ((eat(828, 1000, 22)), (std::vector<int >{850, 0}));
    EXPECT_EQ((eat(-10, -6, 21)), (std::vector<int >{-16, 27}));
    EXPECT_EQ((eat(2, 15, 671)), (std::vector<int >{17, 656}));
    EXPECT_EQ((eat(1, 12, 2)), (std::vector<int >{3, 0}));
    EXPECT_EQ((eat(0, -656, 11)), (std::vector<int >{-656, 667}));
    EXPECT_EQ((eat(9, -291, 9)), (std::vector<int >{-282, 300}));
}

TEST(Characterization, do_algebra_01) {
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("-"), std::string("*")}, std::vector<int >{2, 3, 4, 99999})), (-10));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("*"), std::string("+")}, std::vector<int >{2, 5, 4, 5})), (133));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("-"), std::string("*"), std::string("+")}, std::vector<int >{2, 3, 4, 5})), (-5));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("*")}, std::vector<int >{25, 2, 18, -242})), (216));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("*"), std::string("-")}, std::vector<int >{4, 592, 3, 27, 99999})), (2365));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("*"), std::string("Yx")}, std::vector<int >{2, 3, 4, 5, 3})), (0));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("*")}, std::vector<int >{2, 3, 4, 5})), (0));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("//"), std::string("*")}, std::vector<int >{8, 8, 24, 3, 2, 4, 933, 14})), (24));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("*")}, std::vector<int >{2, 3, 4, 5})), (32));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("*"), std::string("rS0jpGo"), std::string("y"), std::string("NG*z"), std::string("o"), std::string("5"), std::string("i37+"), std::string("80WtXYN/kQ")}, std::vector<int >{7, 3, 4})), (21));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("**"), std::string("*"), std::string("+")}, std::vector<int >{3, 4, 7, 221, -1, -2})), (788));
    EXPECT_EQ((do_algebra(std::vector<std::string >{std::string("+"), std::string("*"), std::string("-")}, std::vector<int >{29, 6, 0, -2, 353, 22, 9})), (31));
}

TEST(Characterization, solve_01) {
    EXPECT_EQ((solve(std::string("T"))), (std::string("t")));
    EXPECT_EQ((solve(std::string("#6@2"))), (std::string("2@6#")));
    EXPECT_EQ((solve(std::string("#a@C"))), (std::string("#A@c")));
    EXPECT_EQ((solve(std::string("#ANc"))), (std::string("#anC")));
    EXPECT_EQ((solve(std::string("Q"))), (std::string("q")));
    EXPECT_EQ((solve(std::string("#aaSDFw^45"))), (std::string("#AAsdfW^45")));
    EXPECT_EQ((solve(std::string("MIp2v9 R"))), (std::string("miP2V9 r")));
    EXPECT_EQ((solve(std::string("qKa@C"))), (std::string("QkA@c")));
    EXPECT_EQ((solve(std::string("jw$sGrkj0A"))), (std::string("JW$SgRKJ0a")));
    EXPECT_EQ((solve(std::string("4321"))), (std::string("1234")));
    EXPECT_EQ((solve(std::string("#a@1C"))), (std::string("#A@1c")));
    EXPECT_EQ((solve(std::string("#$a^D"))), (std::string("#$A^d")));
}

TEST(Characterization, generate_integers_01) {
    EXPECT_EQ((generate_integers(958, 28)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(29, 26)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(89, 27)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(0, -688)), (std::vector<int >{-688, -686, -684, -682, -680, -678, -676, -674, -672, -670, -668, -666, -664, -662, -660, -658, -656, -654, -652, -650, -648, -646, -644, -642, -640, -638, -636, -634, -632, -630, -628, -626, -624, -622, -620, -618, -616, -614, -612, -610, -608, -606, -604, -602, -600, -598, -596, -594, -592, -590, -588, -586, -584, -582, -580, -578, -576, -574, -572, -570, -568, -566, -564, -562, -560, -558, -556, -554, -552, -550, -548, -546, -544, -542, -540, -538, -536, -534, -532, -530, -528, -526, -524, -522, -520, -518, -516, -514, -512, -510, -508, -506, -504, -502, -500, -498, -496, -494, -492, -490, -488, -486, -484, -482, -480, -478, -476, -474, -472, -470, -468, -466, -464, -462, -460, -458, -456, -454, -452, -450, -448, -446, -444, -442, -440, -438, -436, -434, -432, -430, -428, -426, -424, -422, -420, -418, -416, -414, -412, -410, -408, -406, -404, -402, -400, -398, -396, -394, -392, -390, -388, -386, -384, -382, -380, -378, -376, -374, -372, -370, -368, -366, -364, -362, -360, -358, -356, -354, -352, -350, -348, -346, -344, -342, -340, -338, -336, -334, -332, -330, -328, -326, -324, -322, -320, -318, -316, -314, -312, -310, -308, -306, -304, -302, -300, -298, -296, -294, -292, -290, -288, -286, -284, -282, -280, -278, -276, -274, -272, -270, -268, -266, -264, -262, -260, -258, -256, -254, -252, -250, -248, -246, -244, -242, -240, -238, -236, -234, -232, -230, -228, -226, -224, -222, -220, -218, -216, -214, -212, -210, -208, -206, -204, -202, -200, -198, -196, -194, -192, -190, -188, -186, -184, -182, -180, -178, -176, -174, -172, -170, -168, -166, -164, -162, -160, -158, -156, -154, -152, -150, -148, -146, -144, -142, -140, -138, -136, -134, -132, -130, -128, -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -4, -2, 0}));
    EXPECT_EQ((generate_integers(4, 729)), (std::vector<int >{4, 6, 8}));
    EXPECT_EQ((generate_integers(6, 4)), (std::vector<int >{4, 6}));
    EXPECT_EQ((generate_integers(132, 5)), (std::vector<int >{6, 8}));
    EXPECT_EQ((generate_integers(27, 19)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(11, 89)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(10, 21)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(20, 17)), (std::vector<int >{}));
    EXPECT_EQ((generate_integers(-618, 11)), (std::vector<int >{-618, -616, -614, -612, -610, -608, -606, -604, -602, -600, -598, -596, -594, -592, -590, -588, -586, -584, -582, -580, -578, -576, -574, -572, -570, -568, -566, -564, -562, -560, -558, -556, -554, -552, -550, -548, -546, -544, -542, -540, -538, -536, -534, -532, -530, -528, -526, -524, -522, -520, -518, -516, -514, -512, -510, -508, -506, -504, -502, -500, -498, -496, -494, -492, -490, -488, -486, -484, -482, -480, -478, -476, -474, -472, -470, -468, -466, -464, -462, -460, -458, -456, -454, -452, -450, -448, -446, -444, -442, -440, -438, -436, -434, -432, -430, -428, -426, -424, -422, -420, -418, -416, -414, -412, -410, -408, -406, -404, -402, -400, -398, -396, -394, -392, -390, -388, -386, -384, -382, -380, -378, -376, -374, -372, -370, -368, -366, -364, -362, -360, -358, -356, -354, -352, -350, -348, -346, -344, -342, -340, -338, -336, -334, -332, -330, -328, -326, -324, -322, -320, -318, -316, -314, -312, -310, -308, -306, -304, -302, -300, -298, -296, -294, -292, -290, -288, -286, -284, -282, -280, -278, -276, -274, -272, -270, -268, -266, -264, -262, -260, -258, -256, -254, -252, -250, -248, -246, -244, -242, -240, -238, -236, -234, -232, -230, -228, -226, -224, -222, -220, -218, -216, -214, -212, -210, -208, -206, -204, -202, -200, -198, -196, -194, -192, -190, -188, -186, -184, -182, -180, -178, -176, -174, -172, -170, -168, -166, -164, -162, -160, -158, -156, -154, -152, -150, -148, -146, -144, -142, -140, -138, -136, -134, -132, -130, -128, -126, -124, -122, -120, -118, -116, -114, -112, -110, -108, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -86, -84, -82, -80, -78, -76, -74, -72, -70, -68, -66, -64, -62, -60, -58, -56, -54, -52, -50, -48, -46, -44, -42, -40, -38, -36, -34, -32, -30, -28, -26, -24, -22, -20, -18, -16, -14, -12, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8}));
}
