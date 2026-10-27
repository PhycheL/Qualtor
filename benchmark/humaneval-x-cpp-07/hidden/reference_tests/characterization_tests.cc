// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_07.h"

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

TEST(Characterization, modp_01) {
    EXPECT_EQ((modp(2, 26)), (4));
    EXPECT_EQ((modp(29, 101)), (59));
    EXPECT_EQ((modp(28, 4)), (0));
    EXPECT_EQ((modp(903, 5)), (3));
    EXPECT_EQ((modp(-1, 8)), (1));
    EXPECT_EQ((modp(0, 23)), (1));
    EXPECT_EQ((modp(29, 100)), (12));
    EXPECT_EQ((modp(544, 101)), (71));
    EXPECT_EQ((modp(1099, 3)), (2));
    EXPECT_EQ((modp(1099, 27)), (2));
    EXPECT_EQ((modp(19, 30)), (8));
    EXPECT_EQ((modp(8, 4)), (0));
}

TEST(Characterization, encode_shift_01) {
    EXPECT_EQ((encode_shift(std::string("XO"))), (std::string("]T")));
    EXPECT_EQ((encode_shift(std::string("dlwsxJKiso"))), (std::string("iqbxcOPnxt")));
    EXPECT_EQ((encode_shift(std::string(""))), (std::string("")));
    EXPECT_EQ((encode_shift(std::string("J"))), (std::string("O")));
    EXPECT_EQ((encode_shift(std::string("U"))), (std::string("Z")));
    EXPECT_EQ((encode_shift(std::string("XH"))), (std::string("]M")));
    EXPECT_EQ((encode_shift(std::string("LqlI m5qtVxo"))), (std::string("QvqNYrTvy[ct")));
    EXPECT_EQ((encode_shift(std::string("ETy4G"))), (std::string("JYdSL")));
    EXPECT_EQ((encode_shift(std::string("c7M36"))), (std::string("hVRRU")));
    EXPECT_EQ((encode_shift(std::string("mufPKZ"))), (std::string("rzkUP_")));
    EXPECT_EQ((encode_shift(std::string("X"))), (std::string("]")));
    EXPECT_EQ((encode_shift(std::string("qTRYxYyzv"))), (std::string("vYW^c^dea")));
}

TEST(Characterization, decode_shift_01) {
    EXPECT_EQ((decode_shift(std::string(""))), (std::string("")));
    EXPECT_EQ((decode_shift(std::string("c"))), (std::string("x")));
    EXPECT_EQ((decode_shift(std::string("sB"))), (std::string("nW")));
    EXPECT_EQ((decode_shift(std::string("0"))), (std::string("_")));
    EXPECT_EQ((decode_shift(std::string("Yhvq31"))), (std::string("ncqlH`")));
    EXPECT_EQ((decode_shift(std::string("gO"))), (std::string("bd")));
    EXPECT_EQ((decode_shift(std::string("T"))), (std::string("i")));
    EXPECT_EQ((decode_shift(std::string("o"))), (std::string("j")));
    EXPECT_EQ((decode_shift(std::string("ZKNpJ7SPbP"))), (std::string("o`ck_Lhewe")));
    EXPECT_EQ((decode_shift(std::string("H ci wExwZ"))), (std::string("]OxdOrZsro")));
    EXPECT_EQ((decode_shift(std::string("Q"))), (std::string("f")));
    EXPECT_EQ((decode_shift(std::string("x"))), (std::string("s")));
}

TEST(Characterization, remove_vowels_01) {
    EXPECT_EQ((remove_vowels(std::string("B"))), (std::string("B")));
    EXPECT_EQ((remove_vowels(std::string("ybcd"))), (std::string("ybcd")));
    EXPECT_EQ((remove_vowels(std::string("eJeee"))), (std::string("J")));
    EXPECT_EQ((remove_vowels(std::string("FL0wRiy"))), (std::string("FL0wRy")));
    EXPECT_EQ((remove_vowels(std::string("acBAuA"))), (std::string("cB")));
    EXPECT_EQ((remove_vowels(std::string("DpoP"))), (std::string("DpP")));
    EXPECT_EQ((remove_vowels(std::string("iRIfFOT"))), (std::string("RfFT")));
    EXPECT_EQ((remove_vowels(std::string("bcdf"))), (std::string("bcdf")));
    EXPECT_EQ((remove_vowels(std::string("jcd1"))), (std::string("jcd1")));
    EXPECT_EQ((remove_vowels(std::string("bcdf\012ghjklm"))), (std::string("bcdf\012ghjklm")));
    EXPECT_EQ((remove_vowels(std::string("fedcba"))), (std::string("fdcb")));
    EXPECT_EQ((remove_vowels(std::string("cB"))), (std::string("cB")));
}

TEST(Characterization, below_threshold_01) {
    EXPECT_EQ((below_threshold(std::vector<int >{3, 8, 5}, 16)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{-446, -434, 19, -121, 3, 27, 99999}, 12345)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{2, 20, 4, 10}, 5)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10}, 27)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{2, 1, 4, 10}, 11)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{20, 1, 4, 10}, 4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{20, 1, 4, 10}, 7)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10, 1000}, 0)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{8, 21, 11, 580, 29, -6, 3, -5}, -481)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10, 9}, 4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{0, 16, 9, 19, 22, 11}, 0)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{4, 2, 1, 10}, 22)), (true));
}

TEST(Characterization, add_01) {
    EXPECT_EQ((add(-3, 3)), (0));
    EXPECT_EQ((add(238, 0)), (238));
    EXPECT_EQ((add(-399, 7)), (-392));
    EXPECT_EQ((add(507, 6)), (513));
    EXPECT_EQ((add(3, 26)), (29));
    EXPECT_EQ((add(12, 998)), (1010));
    EXPECT_EQ((add(2, 1002)), (1004));
    EXPECT_EQ((add(23, 2)), (25));
    EXPECT_EQ((add(-7, -212)), (-219));
    EXPECT_EQ((add(828, 5)), (833));
    EXPECT_EQ((add(22, -10)), (12));
    EXPECT_EQ((add(-6, 21)), (15));
}

TEST(Characterization, same_chars_01) {
    EXPECT_EQ((same_chars(std::string("ygdY"), std::string("eabcdzzzz"))), (false));
    EXPECT_EQ((same_chars(std::string("7fsRi1ZC"), std::string("stuO0GVK0wR"))), (false));
    EXPECT_EQ((same_chars(std::string("JY"), std::string("A"))), (false));
    EXPECT_EQ((same_chars(std::string("IaUrYD"), std::string("dddddddabce"))), (false));
    EXPECT_EQ((same_chars(std::string("hp2lijAr"), std::string("36PTn9qLnbS"))), (false));
    EXPECT_EQ((same_chars(std::string("G4Hv77vTZ"), std::string(""))), (false));
    EXPECT_EQ((same_chars(std::string("abcd"), std::string(""))), (false));
    EXPECT_EQ((same_chars(std::string("aabb"), std::string("dddzzzzzzzddeddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("aacc"), std::string("aaccc"))), (true));
    EXPECT_EQ((same_chars(std::string("dddzzzzzzzddddabc"), std::string("4aycd"))), (false));
    EXPECT_EQ((same_chars(std::string("ddzzzzzzzddddabc"), std::string("dddddddabce"))), (false));
    EXPECT_EQ((same_chars(std::string("eabcdzzzz"), std::string("pgN"))), (false));
}

TEST(Characterization, fib_01) {
    EXPECT_EQ((fib(1)), (1));
    EXPECT_EQ((fib(9)), (34));
    EXPECT_EQ((fib(21)), (10946));
    EXPECT_EQ((fib(22)), (17711));
    EXPECT_EQ((fib(26)), (121393));
    EXPECT_EQ((fib(24)), (46368));
    EXPECT_EQ((fib(11)), (89));
    EXPECT_EQ((fib(25)), (75025));
    EXPECT_EQ((fib(15)), (610));
    EXPECT_EQ((fib(8)), (21));
    EXPECT_EQ((fib(14)), (377));
    EXPECT_EQ((fib(0)), (0));
}

TEST(Characterization, correct_bracketing_01) {
    EXPECT_EQ((correct_bracketing(std::string("CAIZi"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("><<>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("Lb"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<><><<><>><>>><>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<<<><>>>0>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<>"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<<H<<"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<<<><>>>>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<><><<><>><>"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<<<<"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("5vTsJ"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("pdN4"))), (true));
}
