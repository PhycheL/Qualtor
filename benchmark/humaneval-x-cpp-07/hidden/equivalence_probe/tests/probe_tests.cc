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

TEST(Probe, modp_01) {
    EXPECT_EQ((modp(100, 19)), (17));
    EXPECT_EQ((modp(103, 100)), (8));
    EXPECT_EQ((modp(21, 99999)), (97172));
    EXPECT_EQ((modp(2, 1101)), (4));
    EXPECT_EQ((modp(-116, 11)), (1));
    EXPECT_EQ((modp(-10, 4)), (1));
    EXPECT_EQ((modp(0, -1)), (1));
    EXPECT_EQ((modp(671, -10)), (8));
    EXPECT_EQ((modp(428, 258)), (256));
    EXPECT_EQ((modp(20, 11)), (1));
    EXPECT_EQ((modp(24, -7)), (1));
    EXPECT_EQ((modp(3, -3)), (2));
    EXPECT_EQ((modp(5, 30)), (2));
    EXPECT_EQ((modp(9, 1)), (0));
    EXPECT_EQ((modp(98, -5)), (4));
    EXPECT_EQ((modp(-6, 1000)), (1));
    EXPECT_EQ((modp(13, 6)), (2));
    EXPECT_EQ((modp(1, 19)), (2));
    EXPECT_EQ((modp(31, 1)), (0));
    EXPECT_EQ((modp(1, 23)), (2));
    EXPECT_EQ((modp(21, 101)), (89));
    EXPECT_EQ((modp(1, 28)), (2));
    EXPECT_EQ((modp(3, 2)), (0));
    EXPECT_EQ((modp(22, -7)), (2));
    EXPECT_EQ((modp(24, 3)), (1));
}

TEST(Probe, modp_02) {
    EXPECT_EQ((modp(8, 12345)), (256));
    EXPECT_EQ((modp(199, 3)), (2));
    EXPECT_EQ((modp(11, 8)), (0));
    EXPECT_EQ((modp(820, 11)), (1));
    EXPECT_EQ((modp(4, 6)), (4));
    EXPECT_EQ((modp(1, 4)), (2));
    EXPECT_EQ((modp(27, 1101)), (323));
    EXPECT_EQ((modp(4, 13)), (3));
    EXPECT_EQ((modp(17, 18)), (14));
    EXPECT_EQ((modp(1101, 101)), (2));
    EXPECT_EQ((modp(0, 4)), (1));
    EXPECT_EQ((modp(16, 20)), (16));
    EXPECT_EQ((modp(12, -2)), (0));
    EXPECT_EQ((modp(0, 1101)), (1));
    EXPECT_EQ((modp(-557, 32)), (1));
    EXPECT_EQ((modp(1, 29)), (2));
    EXPECT_EQ((modp(5, 7)), (4));
    EXPECT_EQ((modp(100, 30)), (16));
    EXPECT_EQ((modp(15, 30)), (8));
    EXPECT_EQ((modp(0, -9)), (1));
    EXPECT_EQ((modp(11, 30)), (8));
    EXPECT_EQ((modp(31, 2)), (0));
    EXPECT_EQ((modp(18, -5)), (4));
}

TEST(Probe, encode_shift_01) {
    EXPECT_EQ((encode_shift(std::string("dQqtPg VkWMx"))), (std::string("iVvyUlY[p\\Rc")));
    EXPECT_EQ((encode_shift(std::string("H"))), (std::string("M")));
    EXPECT_EQ((encode_shift(std::string("G6oqmr6"))), (std::string("LUtvrwU")));
    EXPECT_EQ((encode_shift(std::string("71"))), (std::string("VP")));
    EXPECT_EQ((encode_shift(std::string("FsG1owhQEF4T"))), (std::string("KxLPtbmVJKSY")));
    EXPECT_EQ((encode_shift(std::string("t1lXt"))), (std::string("yPq]y")));
    EXPECT_EQ((encode_shift(std::string("gYL6"))), (std::string("l^QU")));
    EXPECT_EQ((encode_shift(std::string("bFS"))), (std::string("gKX")));
    EXPECT_EQ((encode_shift(std::string("X3"))), (std::string("]R")));
    EXPECT_EQ((encode_shift(std::string("FH"))), (std::string("KM")));
    EXPECT_EQ((encode_shift(std::string("SrTgfTG2VdY"))), (std::string("XwYlkYLQ[i^")));
    EXPECT_EQ((encode_shift(std::string("AdwjhD3u"))), (std::string("`ibomIRz")));
    EXPECT_EQ((encode_shift(std::string("TzbEEv"))), (std::string("YegJJa")));
    EXPECT_EQ((encode_shift(std::string("u3f"))), (std::string("zRk")));
    EXPECT_EQ((encode_shift(std::string("1"))), (std::string("P")));
    EXPECT_EQ((encode_shift(std::string("zjKsxozr"))), (std::string("eoPxctew")));
    EXPECT_EQ((encode_shift(std::string("NG"))), (std::string("SL")));
    EXPECT_EQ((encode_shift(std::string("QoDbq1NJph"))), (std::string("VtIgvPSOum")));
    EXPECT_EQ((encode_shift(std::string("bX"))), (std::string("g]")));
    EXPECT_EQ((encode_shift(std::string("M0FCbslO"))), (std::string("ROKHgxqT")));
    EXPECT_EQ((encode_shift(std::string("GmR"))), (std::string("LrW")));
    EXPECT_EQ((encode_shift(std::string("0bC2dCFCV"))), (std::string("OgHQiHKH[")));
    EXPECT_EQ((encode_shift(std::string("2"))), (std::string("Q")));
    EXPECT_EQ((encode_shift(std::string("V"))), (std::string("[")));
    EXPECT_EQ((encode_shift(std::string("8P9MhhZGr"))), (std::string("WUXRmm_Lw")));
}

TEST(Probe, encode_shift_02) {
    EXPECT_EQ((encode_shift(std::string("yndH t dt"))), (std::string("dsiMYyYiy")));
    EXPECT_EQ((encode_shift(std::string("t"))), (std::string("y")));
    EXPECT_EQ((encode_shift(std::string("jqr5CuubK"))), (std::string("ovwTHzzgP")));
    EXPECT_EQ((encode_shift(std::string("6U8"))), (std::string("UZW")));
    EXPECT_EQ((encode_shift(std::string("3"))), (std::string("R")));
    EXPECT_EQ((encode_shift(std::string("Ye"))), (std::string("^j")));
    EXPECT_EQ((encode_shift(std::string("vbf8KmANpKB"))), (std::string("agkWPr`SuPa")));
    EXPECT_EQ((encode_shift(std::string("EJC"))), (std::string("JOH")));
    EXPECT_EQ((encode_shift(std::string("Re y"))), (std::string("WjYd")));
    EXPECT_EQ((encode_shift(std::string("jVPmfETg"))), (std::string("o[UrkJYl")));
    EXPECT_EQ((encode_shift(std::string("Z"))), (std::string("_")));
    EXPECT_EQ((encode_shift(std::string("D"))), (std::string("I")));
    EXPECT_EQ((encode_shift(std::string("rIxWAQUeTDj3"))), (std::string("wNc\\`VZjYIoR")));
    EXPECT_EQ((encode_shift(std::string("7QaTs"))), (std::string("VVfYx")));
    EXPECT_EQ((encode_shift(std::string("cP"))), (std::string("hU")));
    EXPECT_EQ((encode_shift(std::string("a"))), (std::string("f")));
    EXPECT_EQ((encode_shift(std::string("9"))), (std::string("X")));
    EXPECT_EQ((encode_shift(std::string("yYTjRdd"))), (std::string("d^YoWii")));
    EXPECT_EQ((encode_shift(std::string("L"))), (std::string("Q")));
    EXPECT_EQ((encode_shift(std::string("X "))), (std::string("]Y")));
    EXPECT_EQ((encode_shift(std::string("5POx4jOcE"))), (std::string("TUTcSoThJ")));
    EXPECT_EQ((encode_shift(std::string("MFKNfLvE"))), (std::string("RKPSkQaJ")));
    EXPECT_EQ((encode_shift(std::string("7b tTZeHBi"))), (std::string("VgYyY_jMan")));
}

TEST(Probe, decode_shift_01) {
    EXPECT_EQ((decode_shift(std::string("U8XIDbX5 f"))), (std::string("jMm^YwmJOa")));
    EXPECT_EQ((decode_shift(std::string("F"))), (std::string("[")));
    EXPECT_EQ((decode_shift(std::string("q"))), (std::string("l")));
    EXPECT_EQ((decode_shift(std::string("z"))), (std::string("u")));
    EXPECT_EQ((decode_shift(std::string("ofbOQeu"))), (std::string("jawdfzp")));
    EXPECT_EQ((decode_shift(std::string("vvvwY40V"))), (std::string("qqqrnI_k")));
    EXPECT_EQ((decode_shift(std::string("y"))), (std::string("t")));
    EXPECT_EQ((decode_shift(std::string("dN"))), (std::string("yc")));
    EXPECT_EQ((decode_shift(std::string("G"))), (std::string("\\")));
    EXPECT_EQ((decode_shift(std::string("iyhu"))), (std::string("dtcp")));
    EXPECT_EQ((decode_shift(std::string("w"))), (std::string("r")));
    EXPECT_EQ((decode_shift(std::string("C"))), (std::string("X")));
    EXPECT_EQ((decode_shift(std::string("j"))), (std::string("e")));
    EXPECT_EQ((decode_shift(std::string("T4nKqglAHB1B"))), (std::string("iIi`lbgV]W`W")));
    EXPECT_EQ((decode_shift(std::string("tl"))), (std::string("og")));
    EXPECT_EQ((decode_shift(std::string("hH4EsPIlrQno"))), (std::string("c]IZne^gmfij")));
    EXPECT_EQ((decode_shift(std::string("Wg8zoNrvZ"))), (std::string("lbMujcmqo")));
    EXPECT_EQ((decode_shift(std::string("dUyLmO"))), (std::string("yjtahd")));
    EXPECT_EQ((decode_shift(std::string("FOKUUq"))), (std::string("[d`jjl")));
    EXPECT_EQ((decode_shift(std::string("s"))), (std::string("n")));
    EXPECT_EQ((decode_shift(std::string("s6"))), (std::string("nK")));
    EXPECT_EQ((decode_shift(std::string("e"))), (std::string("z")));
    EXPECT_EQ((decode_shift(std::string(" "))), (std::string("O")));
    EXPECT_EQ((decode_shift(std::string("K"))), (std::string("`")));
    EXPECT_EQ((decode_shift(std::string("Es"))), (std::string("Zn")));
}

TEST(Probe, decode_shift_02) {
    EXPECT_EQ((decode_shift(std::string("Y"))), (std::string("n")));
    EXPECT_EQ((decode_shift(std::string("WFe6"))), (std::string("l[zK")));
    EXPECT_EQ((decode_shift(std::string("m"))), (std::string("h")));
    EXPECT_EQ((decode_shift(std::string("c5ewA4"))), (std::string("xJzrVI")));
    EXPECT_EQ((decode_shift(std::string("zB"))), (std::string("uW")));
    EXPECT_EQ((decode_shift(std::string("ypMOVOX2oiJ"))), (std::string("tkbdkdmajd_")));
    EXPECT_EQ((decode_shift(std::string("Lxw"))), (std::string("asr")));
    EXPECT_EQ((decode_shift(std::string("X"))), (std::string("m")));
    EXPECT_EQ((decode_shift(std::string("a"))), (std::string("v")));
    EXPECT_EQ((decode_shift(std::string("xTQiz6PJe"))), (std::string("sifduKe_z")));
    EXPECT_EQ((decode_shift(std::string("D wV0YzZ"))), (std::string("YOrk_nuo")));
    EXPECT_EQ((decode_shift(std::string("zCqrHs"))), (std::string("uXlm]n")));
    EXPECT_EQ((decode_shift(std::string("t"))), (std::string("o")));
    EXPECT_EQ((decode_shift(std::string("V"))), (std::string("k")));
    EXPECT_EQ((decode_shift(std::string("h"))), (std::string("c")));
    EXPECT_EQ((decode_shift(std::string("7zI"))), (std::string("Lu^")));
    EXPECT_EQ((decode_shift(std::string("VSk5nWKNCuF"))), (std::string("khfJil`cXp[")));
    EXPECT_EQ((decode_shift(std::string("fDxovMvX"))), (std::string("aYsjqbqm")));
    EXPECT_EQ((decode_shift(std::string("R4kdhi"))), (std::string("gIfycd")));
    EXPECT_EQ((decode_shift(std::string("y0"))), (std::string("t_")));
    EXPECT_EQ((decode_shift(std::string("Z"))), (std::string("o")));
    EXPECT_EQ((decode_shift(std::string(" rZTHhxrCe"))), (std::string("Omoi]csmXz")));
    EXPECT_EQ((decode_shift(std::string("5"))), (std::string("J")));
}

TEST(Probe, remove_vowels_01) {
    EXPECT_EQ((remove_vowels(std::string("ouBoAA"))), (std::string("B")));
    EXPECT_EQ((remove_vowels(std::string("bcdf\012ghjkm"))), (std::string("bcdf\012ghjkm")));
    EXPECT_EQ((remove_vowels(std::string("zc"))), (std::string("zc")));
    EXPECT_EQ((remove_vowels(std::string("eeeee"))), (std::string("")));
    EXPECT_EQ((remove_vowels(std::string("abcdef\012ghijklm"))), (std::string("bcdf\012ghjklm")));
    EXPECT_EQ((remove_vowels(std::string("39aPdc7NvxO"))), (std::string("39Pdc7Nvx")));
    EXPECT_EQ((remove_vowels(std::string("3xUh"))), (std::string("3xh")));
    EXPECT_EQ((remove_vowels(std::string("FCh61 DH"))), (std::string("FCh61 DH")));
    EXPECT_EQ((remove_vowels(std::string("fdcb"))), (std::string("fdcb")));
    EXPECT_EQ((remove_vowels(std::string("7Rbu\012"))), (std::string("7Rb\012")));
    EXPECT_EQ((remove_vowels(std::string("yoT fh"))), (std::string("yT fh")));
    EXPECT_EQ((remove_vowels(std::string("cihUyWVDoD"))), (std::string("chyWVDD")));
    EXPECT_EQ((remove_vowels(std::string("\012oCrx"))), (std::string("\012Crx")));
    EXPECT_EQ((remove_vowels(std::string("wfS"))), (std::string("wfS")));
    EXPECT_EQ((remove_vowels(std::string("aaa"))), (std::string("")));
    EXPECT_EQ((remove_vowels(std::string("cBAA"))), (std::string("cB")));
    EXPECT_EQ((remove_vowels(std::string("aaBAA"))), (std::string("B")));
    EXPECT_EQ((remove_vowels(std::string("RVWYQcg3D6"))), (std::string("RVWYQcg3D6")));
    EXPECT_EQ((remove_vowels(std::string("abcdef"))), (std::string("bcdf")));
    EXPECT_EQ((remove_vowels(std::string("Wj w"))), (std::string("Wj w")));
    EXPECT_EQ((remove_vowels(std::string("E3cBCOO"))), (std::string("3cBC")));
    EXPECT_EQ((remove_vowels(std::string(""))), (std::string("")));
    EXPECT_EQ((remove_vowels(std::string("UnOwTFRNGT"))), (std::string("nwTFRNGT")));
    EXPECT_EQ((remove_vowels(std::string("v"))), (std::string("v")));
    EXPECT_EQ((remove_vowels(std::string("vbcdf"))), (std::string("vbcdf")));
}

TEST(Probe, remove_vowels_02) {
    EXPECT_EQ((remove_vowels(std::string("EcBOO"))), (std::string("cB")));
    EXPECT_EQ((remove_vowels(std::string("t"))), (std::string("t")));
    EXPECT_EQ((remove_vowels(std::string("fecby"))), (std::string("fcby")));
    EXPECT_EQ((remove_vowels(std::string("cBFO"))), (std::string("cBF")));
    EXPECT_EQ((remove_vowels(std::string("9zampmN"))), (std::string("9zmpmN")));
    EXPECT_EQ((remove_vowels(std::string("zbcd"))), (std::string("zbcd")));
    EXPECT_EQ((remove_vowels(std::string("N"))), (std::string("N")));
    EXPECT_EQ((remove_vowels(std::string("BeGe"))), (std::string("BG")));
    EXPECT_EQ((remove_vowels(std::string("aaaaa"))), (std::string("")));
    EXPECT_EQ((remove_vowels(std::string("i25 "))), (std::string("25 ")));
    EXPECT_EQ((remove_vowels(std::string("bBcd"))), (std::string("bBcd")));
    EXPECT_EQ((remove_vowels(std::string("HQGFQMyQP"))), (std::string("HQGFQMyQP")));
    EXPECT_EQ((remove_vowels(std::string("bcd"))), (std::string("bcd")));
    EXPECT_EQ((remove_vowels(std::string("2QiX"))), (std::string("2QX")));
    EXPECT_EQ((remove_vowels(std::string("XixKzL7c"))), (std::string("XxKzL7c")));
    EXPECT_EQ((remove_vowels(std::string("KLHqGm9ZmL\012 "))), (std::string("KLHqGm9ZmL\012 ")));
    EXPECT_EQ((remove_vowels(std::string("lcBAA"))), (std::string("lcB")));
    EXPECT_EQ((remove_vowels(std::string("A0Q"))), (std::string("0Q")));
    EXPECT_EQ((remove_vowels(std::string("z8AG7RyU4N6B"))), (std::string("z8G7Ry4N6B")));
    EXPECT_EQ((remove_vowels(std::string("Yy0sBOCufkuH"))), (std::string("Yy0sBCfkH")));
    EXPECT_EQ((remove_vowels(std::string("dfdAcb"))), (std::string("dfdcb")));
    EXPECT_EQ((remove_vowels(std::string("U"))), (std::string("")));
    EXPECT_EQ((remove_vowels(std::string("Dybcd"))), (std::string("Dybcd")));
}

TEST(Probe, below_threshold_01) {
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 21, 10}, -4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{2, 5}, 5)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{21, 8, 4, 10}, 8)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{-653, 9, 4, 24, 30, -8, 21}, 101)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10, 22}, 146)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10, 21}, 12)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{9}, -319)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{30, 4}, 21)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10}, 20)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10, -35}, 3)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10}, -9)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10}, 4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10, 5}, 7)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{29, 559, 2, 813, 19, 98, 3}, 0)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 11, 10}, 4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10, 6}, 15)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10}, 552)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 10, 4, 20}, 25)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 8, 4, 10}, 22)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 6, 19, 21, 4, 22, 287}, 4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4}, -2)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10}, 15)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{10, 8, 4, 1}, 4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 10, 4, 8}, 2)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{12345, 26, 28, -927, 10, 7}, 19)), (false));
}

TEST(Probe, below_threshold_02) {
    EXPECT_EQ((below_threshold(std::vector<int >{850, -810, 10, 10}, 5)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{4, 5}, 2)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{9}, 99)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10}, 4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{22, 10, -6}, -959)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{11, 20, 10, 9, 20, 271}, 11)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10}, 22)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10}, 8)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{4, 2, 1, 10}, 1)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 8, 4, 10, 2}, 8)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{3, 8}, 2)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 4, 10}, 19)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10, 1}, 5)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 20, 4, 10, 4}, 6)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 10, 4}, 4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10}, 22)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{11, -7, 19}, 2)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{910, -1, 6}, 1)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{10, 2, 691, 15, 130}, 4)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{1, 2, 4, 10}, -993)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{10, 816, 14, 22, -10, 2, 24, 20}, -32)), (false));
    EXPECT_EQ((below_threshold(std::vector<int >{8, -1, 2}, 523)), (true));
    EXPECT_EQ((below_threshold(std::vector<int >{10, 2, 4, 1}, -3)), (false));
}

TEST(Probe, add_01) {
    EXPECT_EQ((add(2, 15)), (17));
    EXPECT_EQ((add(671, 1)), (672));
    EXPECT_EQ((add(1, 2)), (3));
    EXPECT_EQ((add(7, -656)), (-649));
    EXPECT_EQ((add(6, 0)), (6));
    EXPECT_EQ((add(-291, 3)), (-288));
    EXPECT_EQ((add(248, -40)), (208));
    EXPECT_EQ((add(30, -1)), (29));
    EXPECT_EQ((add(-606, 100)), (-506));
    EXPECT_EQ((add(-954, 3)), (-951));
    EXPECT_EQ((add(58, -2)), (56));
    EXPECT_EQ((add(26, 21)), (47));
    EXPECT_EQ((add(3, -3)), (0));
    EXPECT_EQ((add(2, 1000)), (1002));
    EXPECT_EQ((add(3, -1)), (2));
    EXPECT_EQ((add(3, 0)), (3));
    EXPECT_EQ((add(7, 5)), (12));
    EXPECT_EQ((add(27, 10)), (37));
    EXPECT_EQ((add(0, -626)), (-626));
    EXPECT_EQ((add(-5, 254)), (249));
    EXPECT_EQ((add(9, 206)), (215));
    EXPECT_EQ((add(-356, 15)), (-341));
    EXPECT_EQ((add(-2, 11)), (9));
    EXPECT_EQ((add(-6, 0)), (-6));
    EXPECT_EQ((add(101, 5)), (106));
}

TEST(Probe, add_02) {
    EXPECT_EQ((add(1, 22)), (23));
    EXPECT_EQ((add(5, -81)), (-76));
    EXPECT_EQ((add(1000, 669)), (1669));
    EXPECT_EQ((add(-5, 3)), (-2));
    EXPECT_EQ((add(2, 7)), (9));
    EXPECT_EQ((add(3, 1000)), (1003));
    EXPECT_EQ((add(2, 9)), (11));
    EXPECT_EQ((add(832, 6)), (838));
    EXPECT_EQ((add(5, -817)), (-812));
    EXPECT_EQ((add(7, -3)), (4));
    EXPECT_EQ((add(99999, 3)), (100002));
    EXPECT_EQ((add(7, 99999)), (100006));
    EXPECT_EQ((add(3, 14)), (17));
    EXPECT_EQ((add(98, 7)), (105));
    EXPECT_EQ((add(915, 0)), (915));
    EXPECT_EQ((add(100, 15)), (115));
    EXPECT_EQ((add(12, 17)), (29));
    EXPECT_EQ((add(-548, 26)), (-522));
    EXPECT_EQ((add(12, 27)), (39));
    EXPECT_EQ((add(5, 12)), (17));
    EXPECT_EQ((add(0, 434)), (434));
    EXPECT_EQ((add(12, 100)), (112));
    EXPECT_EQ((add(3, 7)), (10));
}

TEST(Probe, same_chars_01) {
    EXPECT_EQ((same_chars(std::string("ddddddkbxce"), std::string("dddddddabcf"))), (false));
    EXPECT_EQ((same_chars(std::string("dddddddabce"), std::string("jdddddbc"))), (false));
    EXPECT_EQ((same_chars(std::string("dddzzzzzzzddddabc"), std::string("dddddTdabAce"))), (false));
    EXPECT_EQ((same_chars(std::string("dddzzzzzzzddddabc"), std::string("dddddddabcf"))), (false));
    EXPECT_EQ((same_chars(std::string("Muccc"), std::string("dddddddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("dddddddabce"), std::string("dddzzzzzzzddddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("aabb"), std::string("xQtiyY760GC"))), (false));
    EXPECT_EQ((same_chars(std::string("aabb"), std::string("dddddddabcf"))), (false));
    EXPECT_EQ((same_chars(std::string("aab"), std::string("eabcd"))), (false));
    EXPECT_EQ((same_chars(std::string("dddzzzzzzzddeddabc"), std::string("4b"))), (false));
    EXPECT_EQ((same_chars(std::string("apcd"), std::string("S4jE"))), (false));
    EXPECT_EQ((same_chars(std::string("a"), std::string("x"))), (false));
    EXPECT_EQ((same_chars(std::string("jI74"), std::string("Lnqdaxu5rh"))), (false));
    EXPECT_EQ((same_chars(std::string("PdOdCdddabce"), std::string("TpzrmLSyct"))), (false));
    EXPECT_EQ((same_chars(std::string("aavc"), std::string("j5BAH"))), (false));
    EXPECT_EQ((same_chars(std::string("dddzzzzWzzddddabc"), std::string("dddddddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("lCs"), std::string("vdddddddabcf"))), (false));
    EXPECT_EQ((same_chars(std::string("n4zzl"), std::string("aabb"))), (false));
    EXPECT_EQ((same_chars(std::string("eabc6zzzz"), std::string("ddUIddddaAbce"))), (false));
    EXPECT_EQ((same_chars(std::string(""), std::string("ddddddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("B8zeJXr"), std::string("eNAaUkan"))), (false));
    EXPECT_EQ((same_chars(std::string("aaccc"), std::string("dddzzzzzzzddddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("Aeufv4"), std::string("abcd"))), (false));
    EXPECT_EQ((same_chars(std::string("dddddddabce"), std::string("eHaMbcfdzzzz"))), (false));
    EXPECT_EQ((same_chars(std::string("dfdzzczzzzddddab"), std::string("bb"))), (false));
}

TEST(Probe, same_chars_02) {
    EXPECT_EQ((same_chars(std::string("d6ddddabce"), std::string("dddddddabce"))), (false));
    EXPECT_EQ((same_chars(std::string("aaccc"), std::string("dddddddabce"))), (false));
    EXPECT_EQ((same_chars(std::string("lz3M0lIfcK"), std::string("dddzzzzzzzddeddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("dpddzzzzzzzAdedda9c"), std::string("aaccc"))), (false));
    EXPECT_EQ((same_chars(std::string("aaccc"), std::string("j9L9bxo"))), (false));
    EXPECT_EQ((same_chars(std::string("o0H9piitvrQ"), std::string("2"))), (false));
    EXPECT_EQ((same_chars(std::string("aaccc"), std::string("eabcd"))), (false));
    EXPECT_EQ((same_chars(std::string("UggI5Q"), std::string("dddzzzzzzLzddeQddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("aabb"), std::string("eabcd"))), (false));
    EXPECT_EQ((same_chars(std::string("z9AvxLla"), std::string("aaccc"))), (false));
    EXPECT_EQ((same_chars(std::string("7"), std::string("eabcdzzzz"))), (false));
    EXPECT_EQ((same_chars(std::string("a"), std::string("GrZZYlw0fB T"))), (false));
    EXPECT_EQ((same_chars(std::string("aabb"), std::string("9rnLPcA4Tqax"))), (false));
    EXPECT_EQ((same_chars(std::string("dddddddabc"), std::string("dddddda9c"))), (false));
    EXPECT_EQ((same_chars(std::string("dddzzzz2zzddddqabc"), std::string("Qdddddddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("Croaabb"), std::string("ORQlrqX"))), (false));
    EXPECT_EQ((same_chars(std::string("dddzzzzzzzdddwdabc"), std::string("lARk bucM8iA"))), (false));
    EXPECT_EQ((same_chars(std::string("9v9P5gichZ1"), std::string("dddddddabcf"))), (false));
    EXPECT_EQ((same_chars(std::string("S20I1d"), std::string("dddzzzzzzzddeddabRc"))), (false));
    EXPECT_EQ((same_chars(std::string("dddddddabc"), std::string("yG"))), (false));
    EXPECT_EQ((same_chars(std::string("dddddddabce"), std::string("dddzzzzzzzddeddabc"))), (false));
    EXPECT_EQ((same_chars(std::string("0VpTB"), std::string("aaccc"))), (false));
    EXPECT_EQ((same_chars(std::string("2C23WsLlGLCk"), std::string("aabb"))), (false));
}

TEST(Probe, fib_01) {
    EXPECT_EQ((fib(10)), (55));
    EXPECT_EQ((fib(27)), (196418));
    EXPECT_EQ((fib(4)), (3));
    EXPECT_EQ((fib(30)), (832040));
    EXPECT_EQ((fib(23)), (28657));
    EXPECT_EQ((fib(12)), (144));
    EXPECT_EQ((fib(16)), (987));
    EXPECT_EQ((fib(3)), (2));
    EXPECT_EQ((fib(18)), (2584));
    EXPECT_EQ((fib(13)), (233));
    EXPECT_EQ((fib(19)), (4181));
    EXPECT_EQ((fib(6)), (8));
    EXPECT_EQ((fib(5)), (5));
    EXPECT_EQ((fib(20)), (6765));
    EXPECT_EQ((fib(7)), (13));
    EXPECT_EQ((fib(2)), (1));
    EXPECT_EQ((fib(28)), (317811));
    EXPECT_EQ((fib(29)), (514229));
    EXPECT_EQ((fib(17)), (1597));
    EXPECT_EQ((fib(43)), (433494437));
}

TEST(Probe, correct_bracketing_01) {
    EXPECT_EQ((correct_bracketing(std::string("<P<2><<<><><>><>><<><><<>>>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("Z"))), (true));
    EXPECT_EQ((correct_bracketing(std::string(""))), (true));
    EXPECT_EQ((correct_bracketing(std::string("g<<>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("elv"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("s>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<<<><m>>>>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<><><4<T><><>><>><<><><<>>>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("m6azNx8p1"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("H6<V"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("OllUC7a7"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("7N>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<><>w<<<><><>><><<<><<>>>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("tc>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<><><<<<><>><>><1><><<>>>"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<><><<<><><>><>><<><><<>>>"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<<<S<"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("pViNq F"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("AN"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("kqn<"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("4gHiLtmuLZ"))), (true));
    EXPECT_EQ((correct_bracketing(std::string(">89<>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("gpPx0ZisNXa7"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<<><<><>><>><>"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<><><<><>><>><<>"))), (false));
}

TEST(Probe, correct_bracketing_02) {
    EXPECT_EQ((correct_bracketing(std::string("<><><<><>>>>><>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("g5nbdp<"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<<><>>"))), (true));
    EXPECT_EQ((correct_bracketing(std::string(">"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("j"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("VG6>mqi5"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("7<"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("<><><<><><>><>"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("5fban"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("Ty7ECs"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("B1DpesG"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("G52w"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("cIlp"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("z6SYpFgno"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("hKgn"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("S"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<A><>>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("QgXTo4"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<<<>>>T>"))), (false));
    EXPECT_EQ((correct_bracketing(std::string("02NAAsWMKOKE"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("<W<><>>"))), (true));
    EXPECT_EQ((correct_bracketing(std::string("d<"))), (false));
}
