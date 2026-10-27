// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_19.h"

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

TEST(Probe, specialFilter_01) {
    EXPECT_EQ((specialFilter(std::vector<int >{15, -73, 14, -15, -623})), (1));
    EXPECT_EQ((specialFilter(std::vector<int >{1})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{-3, 3, 4, -4, 7})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{33, 45, -3, -2, 21, 109})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{-5, 313, -3, 19, 14})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{23})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{5, 1, -2, -5})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{43, -12, 93, 125, 121, 109})), (4));
    EXPECT_EQ((specialFilter(std::vector<int >{22, -7})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{-2, -73, 12345, 199, 0})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{33, -2, -3, 45, 21, 109, 7})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{125, 71, 6, 1, 14})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{-5, 4})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{5, -2, 1})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{-3, 300, 0, 16, 20, 12})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{0, 93, -557, -72, 1, 29, -2, 7})), (1));
    EXPECT_EQ((specialFilter(std::vector<int >{33, -3, 45, 21, 109})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{121, -12, -9, 45, 14, 44})), (1));
    EXPECT_EQ((specialFilter(std::vector<int >{-3})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{3})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{69})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{26, 4, 2, -3})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{-777})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{6, -73, 7, 10, 10})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{-6, 125, 14, -8, 895, 801, 7})), (1));
}

TEST(Probe, specialFilter_02) {
    EXPECT_EQ((specialFilter(std::vector<int >{5, -2, 1, -5, -15})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{-73, -5})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{30})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{33, 6, 45, 15, 15, -3})), (3));
    EXPECT_EQ((specialFilter(std::vector<int >{71, -2, -33, 75, 21, 19, 121})), (4));
    EXPECT_EQ((specialFilter(std::vector<int >{30, -2, -3, 45, 21, 109})), (1));
    EXPECT_EQ((specialFilter(std::vector<int >{1, 45})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{2})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{-259})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{33, -2, -3, 45, 21, 109, -451})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{-3, 466, 0, 22, 26})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{26, 874})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{-15, -73, 14, 15})), (1));
    EXPECT_EQ((specialFilter(std::vector<int >{-33, -2, 71, 75, 21, 19})), (3));
    EXPECT_EQ((specialFilter(std::vector<int >{33, 2, -3, 45, 21, 109})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{15, -73, 6, -15})), (1));
    EXPECT_EQ((specialFilter(std::vector<int >{33, -2, -3, 45, 109})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{10, 2, -5, -12, 4})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{16, 5, 26, -12, 8, 0, 10, 43})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{30, 41, 21, 939, 14, 71, 3})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{-2, -33, 75, 21, 19})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{1, 77})), (1));
    EXPECT_EQ((specialFilter(std::vector<int >{126})), (0));
}

TEST(Probe, get_matrix_triples_01) {
    EXPECT_EQ((get_matrix_triples(11)), (39));
    EXPECT_EQ((get_matrix_triples(10)), (36));
    EXPECT_EQ((get_matrix_triples(18)), (240));
    EXPECT_EQ((get_matrix_triples(212)), (514465));
    EXPECT_EQ((get_matrix_triples(9)), (21));
    EXPECT_EQ((get_matrix_triples(100)), (53361));
    EXPECT_EQ((get_matrix_triples(442)), (4753980));
    EXPECT_EQ((get_matrix_triples(1)), (0));
    EXPECT_EQ((get_matrix_triples(22)), (490));
    EXPECT_EQ((get_matrix_triples(190)), (373086));
    EXPECT_EQ((get_matrix_triples(533)), (8317761));
    EXPECT_EQ((get_matrix_triples(23)), (511));
    EXPECT_EQ((get_matrix_triples(17)), (185));
    EXPECT_EQ((get_matrix_triples(38)), (2586));
    EXPECT_EQ((get_matrix_triples(12)), (60));
    EXPECT_EQ((get_matrix_triples(35)), (1991));
    EXPECT_EQ((get_matrix_triples(117)), (85215));
    EXPECT_EQ((get_matrix_triples(5)), (1));
    EXPECT_EQ((get_matrix_triples(8)), (11));
    EXPECT_EQ((get_matrix_triples(26)), (764));
    EXPECT_EQ((get_matrix_triples(0)), (0));
    EXPECT_EQ((get_matrix_triples(469)), (5682456));
    EXPECT_EQ((get_matrix_triples(4)), (1));
    EXPECT_EQ((get_matrix_triples(136)), (135675));
    EXPECT_EQ((get_matrix_triples(846)), (33440124));
}

TEST(Probe, get_matrix_triples_02) {
    EXPECT_EQ((get_matrix_triples(274)), (1126216));
    EXPECT_EQ((get_matrix_triples(235)), (708786));
    EXPECT_EQ((get_matrix_triples(543)), (8812890));
    EXPECT_EQ((get_matrix_triples(30)), (1260));
    EXPECT_EQ((get_matrix_triples(29)), (1089));
    EXPECT_EQ((get_matrix_triples(301)), (1495000));
    EXPECT_EQ((get_matrix_triples(610)), (12527536));
    EXPECT_EQ((get_matrix_triples(19)), (306));
    EXPECT_EQ((get_matrix_triples(878)), (37345486));
    EXPECT_EQ((get_matrix_triples(273)), (1109745));
    EXPECT_EQ((get_matrix_triples(109)), (69336));
    EXPECT_EQ((get_matrix_triples(82)), (29160));
    EXPECT_EQ((get_matrix_triples(34)), (1936));
    EXPECT_EQ((get_matrix_triples(13)), (88));
    EXPECT_EQ((get_matrix_triples(325)), (1883736));
    EXPECT_EQ((get_matrix_triples(27)), (900));
    EXPECT_EQ((get_matrix_triples(495)), (6670290));
    EXPECT_EQ((get_matrix_triples(189)), (365211));
    EXPECT_EQ((get_matrix_triples(644)), (14700409));
    EXPECT_EQ((get_matrix_triples(1000)), (55333611));
    EXPECT_EQ((get_matrix_triples(14)), (94));
    EXPECT_EQ((get_matrix_triples(959)), (48692479));
    EXPECT_EQ((get_matrix_triples(15)), (130));
}

TEST(Probe, bf_01) {
    EXPECT_EQ((bf(std::string("uercugry"), std::string("5vvvwY40V9n"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("5Mars"), std::string("gd"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Jupiter"), std::string("Saturn"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Saturn"), std::string("Jupiter"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Earth"), std::string("sQiyhu"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Urwnus"), std::string("Venus"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("wuIejLGT4nKq"), std::string("A"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("upitekbr"), std::string("Saturn"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("hH4EsPIlrQno"), std::string("Wg8zoNrvZ"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("FMars"), std::string("VenuOs"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("dUyLmO"), std::string("Venus"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Makemake"), std::string("Saturn"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Saturn"), std::string("FOKUUq"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("2kUemake"), std::string("Uronuss"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("QatkrW"), std::string("Ma5emake"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("VMakemAkye"), std::string("Mars"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Mercury"), std::string("a3emake"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("NeptuOe"), std::string("Uranus"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Meecurk"), std::string("A"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("MSercuEy"), std::string("5ewA4"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("zB"), std::string("ypMOVOX2oiJ"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Lxw"), std::string("w"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Saurn"), std::string("UranuT"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("aVwns"), std::string("TQiz6PJepi"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("MakemZe"), std::string("Mars"))), (std::vector<std::string >{}));
}

TEST(Probe, bf_02) {
    EXPECT_EQ((bf(std::string("Mars"), std::string("Venus"))), (std::vector<std::string >{std::string("Earth")}));
    EXPECT_EQ((bf(std::string("NeptuPne"), std::string("EVarth"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Mars"), std::string("Saturn"))), (std::vector<std::string >{std::string("Jupiter")}));
    EXPECT_EQ((bf(std::string("irls"), std::string("Neptune"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("qgbDHZ"), std::string("harth"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Mercury"), std::string("Mercury"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("7zI"), std::string("VSk5nWKNCuF"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("fDxovMvX"), std::string(""))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("R4kdhi"), std::string("Earth"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Uranus"), std::string("Neptune"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("herpcry"), std::string("sJupiter"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("ZTHhxrCecR58"), std::string("Saturn"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string(""), std::string("5Ti0oYIX"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Yphu"), std::string("Mars"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Makemake"), std::string("Mercury"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("VMeury"), std::string("MerpHcurT"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Sa1trn"), std::string("Uranus"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Mars"), std::string("upiur"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("nGRuJ"), std::string("MakLa3ke"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("b3jZMq1X3zcb"), std::string("MeNrcury"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("5NKQirH"), std::string("Uranus"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("S2Eturn"), std::string("Uranua8s"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Makemake"), std::string("akuyrn"))), (std::vector<std::string >{}));
}

TEST(Probe, sorted_list_sum_01) {
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("cc"), std::string("dd"), std::string("aaaa"), std::string("bbbb")})), (std::vector<std::string >{std::string("cc"), std::string("dd"), std::string("aaaa"), std::string("bbbb")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("a w"), std::string("asdf"), std::string("Kd7"), std::string("USab"), std::string("mjbqMcUBKclb"), std::string("rwI"), std::string("uQGDBGd")})), (std::vector<std::string >{std::string("USab"), std::string("asdf"), std::string("mjbqMcUBKclb")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("ab"), std::string("a"), std::string("aa"), std::string("cd")})), (std::vector<std::string >{std::string("aa"), std::string("ab"), std::string("cd")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("aaaa"), std::string("bbbb"), std::string("dd"), std::string("cc"), std::string("aa")})), (std::vector<std::string >{std::string("aa"), std::string("cc"), std::string("dd"), std::string("aaaa"), std::string("bbbb")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("4ab")})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("HFVldt")})), (std::vector<std::string >{std::string("HFVldt")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("d"), std::string("b"), std::string("c"), std::string("a")})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("aa"), std::string("aaa")})), (std::vector<std::string >{std::string("aa")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("school"), std::string("i5r")})), (std::vector<std::string >{std::string("school")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("aa")})), (std::vector<std::string >{std::string("aa")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("a"), std::string("b"), std::string("b"), std::string("a"), std::string("c"), std::string("c")})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("L"), std::string("a"), std::string("bbbb"), std::string("Zxa")})), (std::vector<std::string >{std::string("bbbb")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("aaaa"), std::string("bbbb"), std::string("dd"), std::string("cc")})), (std::vector<std::string >{std::string("cc"), std::string("dd"), std::string("aaaa"), std::string("bbbb")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("AI"), std::string("ai"), std::string("d")})), (std::vector<std::string >{std::string("AI"), std::string("ai")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string(""), std::string("aaa"), std::string("au"), std::string("afaa")})), (std::vector<std::string >{std::string(""), std::string("au"), std::string("afaa")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("AI"), std::string("N"), std::string("Fz"), std::string("a"), std::string("aaaa"), std::string("V1gk")})), (std::vector<std::string >{std::string("AI"), std::string("Fz"), std::string("V1gk"), std::string("aaaa")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("dcba"), std::string("abcd")})), (std::vector<std::string >{std::string("abcd"), std::string("dcba")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("d"), std::string("dcba"), std::string("abcd"), std::string("a"), std::string("jHKnSmNqX")})), (std::vector<std::string >{std::string("abcd"), std::string("dcba")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("ab"), std::string("a"), std::string("aaa"), std::string("cd"), std::string("asdf")})), (std::vector<std::string >{std::string("ab"), std::string("cd"), std::string("asdf")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("NmykU"), std::string("dcba"), std::string("abcd"), std::string("a")})), (std::vector<std::string >{std::string("abcd"), std::string("dcba")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("n"), std::string("Hd"), std::string("b")})), (std::vector<std::string >{std::string("Hd")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("aaa"), std::string("c"), std::string("dyhzu"), std::string("fb"), std::string("8ZraXhsVGdAh")})), (std::vector<std::string >{std::string("fb"), std::string("8ZraXhsVGdAh")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("bbbb"), std::string("c")})), (std::vector<std::string >{std::string("bbbb")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("ca")})), (std::vector<std::string >{std::string("ca")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("dd"), std::string(" 6ouIRvP"), std::string("rd"), std::string("aaaa"), std::string("m8b"), std::string("Ubbb"), std::string("cd")})), (std::vector<std::string >{std::string("cd"), std::string("dd"), std::string("rd"), std::string("Ubbb"), std::string("aaaa"), std::string(" 6ouIRvP")}));
}

TEST(Probe, sorted_list_sum_02) {
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("au"), std::string("J8"), std::string("s"), std::string("eb"), std::string("c"), std::string("cd"), std::string("abcd"), std::string("CD")})), (std::vector<std::string >{std::string("CD"), std::string("J8"), std::string("au"), std::string("cd"), std::string("eb"), std::string("abcd")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("aa"), std::string("a")})), (std::vector<std::string >{std::string("aa")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("abcd"), std::string("dcba")})), (std::vector<std::string >{std::string("abcd"), std::string("dcba")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("x")})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("6ab"), std::string("CoXl"), std::string("54"), std::string("PT bqYgZN"), std::string("7ZX"), std::string("I")})), (std::vector<std::string >{std::string("54"), std::string("CoXl")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("Cab"), std::string("Q e5HA"), std::string("a"), std::string("Rb"), std::string("cc")})), (std::vector<std::string >{std::string("Rb"), std::string("cc"), std::string("Q e5HA")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("a"), std::string("b"), std::string("b"), std::string("c"), std::string("c"), std::string("a")})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("sdho")})), (std::vector<std::string >{std::string("sdho")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("q4nhAq"), std::string("co7Xc"), std::string("9aa"), std::string("0f33w1BrY"), std::string("aGb"), std::string("a"), std::string("aaa"), std::string("f24xgpNUpEEw")})), (std::vector<std::string >{std::string("q4nhAq"), std::string("f24xgpNUpEEw")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("aHdf")})), (std::vector<std::string >{std::string("aHdf")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("b"), std::string("b"), std::string("c"), std::string("c"), std::string("a")})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("asdf"), std::string("AI"), std::string("asdf"), std::string("b")})), (std::vector<std::string >{std::string("AI"), std::string("asdf"), std::string("asdf")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("ab"), std::string("a"), std::string("aaa"), std::string("cd"), std::string("jwCR838")})), (std::vector<std::string >{std::string("ab"), std::string("cd")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("school"), std::string("u"), std::string("LXAzCtqj")})), (std::vector<std::string >{std::string("school"), std::string("LXAzCtqj")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("abcd"), std::string("dcba"), std::string("dd")})), (std::vector<std::string >{std::string("dd"), std::string("abcd"), std::string("dcba")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("ab"), std::string("T"), std::string("abcd"), std::string("afu"), std::string("s4gTR2KXk6gX"), std::string("17fy"), std::string("S")})), (std::vector<std::string >{std::string("ab"), std::string("17fy"), std::string("abcd"), std::string("s4gTR2KXk6gX")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("ab"), std::string("a"), std::string("a"), std::string("cd")})), (std::vector<std::string >{std::string("ab"), std::string("cd")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("AI"), std::string("asdf"), std::string("school"), std::string("school")})), (std::vector<std::string >{std::string("AI"), std::string("asdf"), std::string("school"), std::string("school")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("bdb"), std::string("a"), std::string("aaa")})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("cc")})), (std::vector<std::string >{std::string("cc")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("d")})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("yDq8n9415")})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("lvxzzC1Kgc")})), (std::vector<std::string >{std::string("lvxzzC1Kgc")}));
}

TEST(Probe, x_or_y_01) {
    EXPECT_EQ((x_or_y(580, 29, -6)), (-6));
    EXPECT_EQ((x_or_y(3, -5, -481)), (-5));
    EXPECT_EQ((x_or_y(13, 2, 56)), (2));
    EXPECT_EQ((x_or_y(6, -59, 3609)), (3609));
    EXPECT_EQ((x_or_y(9, 19, 129)), (129));
    EXPECT_EQ((x_or_y(12, -3, 1)), (1));
    EXPECT_EQ((x_or_y(10, 1, 3)), (3));
    EXPECT_EQ((x_or_y(5211, 6, 7)), (7));
    EXPECT_EQ((x_or_y(28, 27, 5212)), (5212));
    EXPECT_EQ((x_or_y(4, 1, -669)), (-669));
    EXPECT_EQ((x_or_y(5, 549, -653)), (549));
    EXPECT_EQ((x_or_y(11, 5212, 585)), (5212));
    EXPECT_EQ((x_or_y(30, -8, 52)), (52));
    EXPECT_EQ((x_or_y(584, 0, -35)), (-35));
    EXPECT_EQ((x_or_y(7, 146, -6)), (146));
    EXPECT_EQ((x_or_y(14, 635, 12)), (12));
    EXPECT_EQ((x_or_y(168, 9, -319)), (-319));
    EXPECT_EQ((x_or_y(880, 30, 1)), (1));
    EXPECT_EQ((x_or_y(-1, 33, 15)), (15));
    EXPECT_EQ((x_or_y(23, 13, -631)), (13));
    EXPECT_EQ((x_or_y(5, -9, 10)), (-9));
    EXPECT_EQ((x_or_y(23, -808, 3)), (-808));
    EXPECT_EQ((x_or_y(-9, 592, -313)), (-313));
    EXPECT_EQ((x_or_y(54, 12345, 29)), (29));
    EXPECT_EQ((x_or_y(559, 2, 813)), (813));
}

TEST(Probe, x_or_y_02) {
    EXPECT_EQ((x_or_y(19, 1257, 4)), (1257));
    EXPECT_EQ((x_or_y(0, 8, 17)), (17));
    EXPECT_EQ((x_or_y(-1, 28, -5)), (-5));
    EXPECT_EQ((x_or_y(3609, 1, 100)), (100));
    EXPECT_EQ((x_or_y(13, 15, 25)), (15));
    EXPECT_EQ((x_or_y(5211, -445, 22)), (22));
    EXPECT_EQ((x_or_y(26, 307, 11)), (11));
    EXPECT_EQ((x_or_y(12, 2, 21)), (21));
    EXPECT_EQ((x_or_y(10, 622, 25)), (25));
    EXPECT_EQ((x_or_y(-10, 3609, 34)), (34));
    EXPECT_EQ((x_or_y(-5, -6, -361)), (-361));
    EXPECT_EQ((x_or_y(93, 1246, 6)), (6));
    EXPECT_EQ((x_or_y(22, 5, 12345)), (12345));
    EXPECT_EQ((x_or_y(26, 28, -927)), (-927));
    EXPECT_EQ((x_or_y(15, 7, 19)), (19));
    EXPECT_EQ((x_or_y(-4, 850, -810)), (-810));
    EXPECT_EQ((x_or_y(0, 8, 1)), (1));
    EXPECT_EQ((x_or_y(33, 1246, -606)), (-606));
    EXPECT_EQ((x_or_y(5, 52, 582)), (52));
    EXPECT_EQ((x_or_y(1232, -2, 34)), (34));
    EXPECT_EQ((x_or_y(52, 3, 15)), (15));
    EXPECT_EQ((x_or_y(100, 14, -6)), (-6));
    EXPECT_EQ((x_or_y(-959, 9, 3609)), (3609));
}

TEST(Probe, double_the_difference_01) {
    EXPECT_EQ((double_the_difference(std::vector<float >{19.7000008f, 4.0f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.200000003f, 3.0f, 5.0f, 14.3999996f})), (34LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{10.3999996f, 0.200000003f, 0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-11.8000002f, 3.0f, 5.0f})), (34LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 0.200000003f, 0.300000012f, -0.800000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, -6.69999981f, -3.70000005f, -16.3999996f, 1.5f, 2.05999994f, -13.5f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.200000003f, 10.0f, 5.0f})), (25LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 0.200000003f, 0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.5f})), (1LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 0.200000003f, 0.300000012f, 0.100000001f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{10.0f, -1.5f, 81.0f, 0.100000001f, 0.0f, 0.0f})), (6561LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-8.80000019f, 3.0f, 5.0f})), (34LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.0f, 8.31999969f, 17.2000008f, 0.300000012f, 5.69999981f, 1.0f})), (1LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.200000003f, 3.0f})), (9LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 0.0f, 19.7999992f, 0.800000012f, 9.80000019f, 9.14999962f})), (1LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-5.03999996f, 2.0f, 0.0f, -99.0f, -18.1000004f, 4.0f, -10.0f, -10.0f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{1.32000005f, 0.0f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{13.8999996f, 0.100000001f, 0.200000003f, 15.0f, 3.0f, 0.200000003f, 6.5f})), (283LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.0f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-10.0f, 0.0f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 0.200000003f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.200000003f, 2.20000005f, 9.69999981f, 0.400000006f, -12.3999996f, 0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.0f, -7.0999999f, -2.0f, -0.400000006f, 0.0f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.200000003f, -1.70000005f})), (0LL));
}

TEST(Probe, double_the_difference_02) {
    EXPECT_EQ((double_the_difference(std::vector<float >{})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 81.0f, 0.300000012f})), (6561LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{34.0f, -7.69999981f, 0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-2.70000005f, -1.70000005f, 5.46000004f, -14.0f, -13.1999998f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-2.20000005f, 0.200000003f, 2.0999999f, 0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-1.39999998f, -2.0f, -8.30000019f, 0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.300000012f, 5.76000023f, -3.0999999f, 4.0f, -5.69999981f, -1.60000002f, -1.70000005f, 0.100000001f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{34.0f, 34.0f, 0.100000001f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 1.10000002f, 0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{3.0f, 14.0f, -14.8999996f, 7.46000004f, -2.70000005f})), (9LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{3.5f, 0.0f, 18.5f, -1.60000002f, -7.0999999f, 0.0f, -18.2000008f, 0.0f})), (361LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.200000003f, 3.0f, 1.79999995f})), (9LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{5.0f, 3.0f, 0.200000003f})), (34LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-6.5999999f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{7.80000019f, 0.0f, -0.140000001f, 1.89999998f, 17.8999996f, 1.5f, 10.0f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{3.05999994f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{100.0f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{1.79999995f, 9.80000019f, 0.0f, 100.0f, 0.300000012f, -11.1000004f, 0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.300000012f, 0.200000003f, 0.100000001f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{19.7999992f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{2.0999999f, -7.51999998f, 0.200000003f, 81.0f})), (6561LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{25.0f, 1.38f, -6.0f, 0.200000003f, 0.200000003f, 15.3000002f})), (625LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.300000012f, -1.89999998f, -10.1999998f, 6.48999977f, 0.200000003f, 8.0f, 9.0f})), (81LL));
}

TEST(Probe, compare_01) {
    EXPECT_EQ((compare(std::vector<int >{-1, 1, 3, 4}, std::vector<int >{4, 4, 1, 0, 0, 6})), (std::vector<int >{5, 3, 2, 4}));
    EXPECT_EQ((compare(std::vector<int >{5, 0, -5}, std::vector<int >{2, 4, 6})), (std::vector<int >{3, 4, 11}));
    EXPECT_EQ((compare(std::vector<int >{2, 4, 6, -3}, std::vector<int >{-1, -2, -3, -747})), (std::vector<int >{3, 6, 9, 744}));
    EXPECT_EQ((compare(std::vector<int >{5, -2, -3}, std::vector<int >{0, 0, 0, 0, 3, 20})), (std::vector<int >{5, 2, 3}));
    EXPECT_EQ((compare(std::vector<int >{-2, 1, 26, 0, -2}, std::vector<int >{897, 25, 28, 2, -2})), (std::vector<int >{899, 24, 2, 2, 0}));
    EXPECT_EQ((compare(std::vector<int >{-1, -2, -3, -1}, std::vector<int >{1, 1, 0, 0, -2})), (std::vector<int >{2, 3, 3, 1}));
    EXPECT_EQ((compare(std::vector<int >{2, 1, 3, 5}, std::vector<int >{0, 5, 0, 0, 0, 4})), (std::vector<int >{2, 4, 3, 5}));
    EXPECT_EQ((compare(std::vector<int >{2, 4, -1}, std::vector<int >{2, 0, 0, 1, 4})), (std::vector<int >{0, 4, 1}));
    EXPECT_EQ((compare(std::vector<int >{-417, -860, 7, 18, 3}, std::vector<int >{1, 2, 4, 5, 1})), (std::vector<int >{418, 862, 3, 13, 2}));
    EXPECT_EQ((compare(std::vector<int >{-1, 3, 3, 4}, std::vector<int >{0, 5, 0, 0, 0, 4})), (std::vector<int >{1, 2, 3, 4}));
    EXPECT_EQ((compare(std::vector<int >{-1, 2, 3, 4}, std::vector<int >{0, 5, 0, 0, 0, 4, 984})), (std::vector<int >{1, 3, 3, 4}));
    EXPECT_EQ((compare(std::vector<int >{1, 2, 3, -3}, std::vector<int >{4, 4, 1, 0, 0, 6, 1})), (std::vector<int >{3, 2, 2, 3}));
    EXPECT_EQ((compare(std::vector<int >{-1, -3, -8}, std::vector<int >{16, -3, 14})), (std::vector<int >{17, 0, 22}));
    EXPECT_EQ((compare(std::vector<int >{1, 2, 3, 18}, std::vector<int >{0, 5, 0, 0, 0, 4, -1})), (std::vector<int >{1, 3, 3, 18}));
    EXPECT_EQ((compare(std::vector<int >{-1, 2, 3, 4}, std::vector<int >{-2, 0, 0, 1})), (std::vector<int >{1, 2, 3, 3}));
    EXPECT_EQ((compare(std::vector<int >{1, 2, 3, 5}, std::vector<int >{4, 4, 1, 0, 0, 6})), (std::vector<int >{3, 2, 2, 5}));
    EXPECT_EQ((compare(std::vector<int >{}, std::vector<int >{3, -1, 19, 12, 8, 99999})), (std::vector<int >{}));
    EXPECT_EQ((compare(std::vector<int >{1, 3, 5}, std::vector<int >{9, 5, 25, 12})), (std::vector<int >{8, 2, 20}));
    EXPECT_EQ((compare(std::vector<int >{-2, -1, -3}, std::vector<int >{4, 4, 1, 0, 0})), (std::vector<int >{6, 5, 4}));
    EXPECT_EQ((compare(std::vector<int >{0, 0, 5, 0, 3, 3}, std::vector<int >{0, 0, 0, 0, 3, 3})), (std::vector<int >{0, 0, 5, 0, 0, 0}));
    EXPECT_EQ((compare(std::vector<int >{2, 1, 0, 0}, std::vector<int >{0, 1, -2, 29, -3})), (std::vector<int >{2, 0, 2, 29}));
    EXPECT_EQ((compare(std::vector<int >{-821, 6}, std::vector<int >{-3, -2, -1})), (std::vector<int >{818, 8}));
    EXPECT_EQ((compare(std::vector<int >{-1, -2, -3}, std::vector<int >{-1, -2, -3})), (std::vector<int >{0, 0, 0}));
    EXPECT_EQ((compare(std::vector<int >{2, 4, 6}, std::vector<int >{2, 4, 6, 13})), (std::vector<int >{0, 0, 0}));
    EXPECT_EQ((compare(std::vector<int >{10, 4}, std::vector<int >{4, 4, 1, 0, 0, 6})), (std::vector<int >{6, 0}));
}

TEST(Probe, compare_02) {
    EXPECT_EQ((compare(std::vector<int >{4}, std::vector<int >{1, 3})), (std::vector<int >{3}));
    EXPECT_EQ((compare(std::vector<int >{-1, -4, 5}, std::vector<int >{1, 27, -1, 19, -3})), (std::vector<int >{2, 31, 6}));
    EXPECT_EQ((compare(std::vector<int >{19, 6, 1, 2, 6, -502}, std::vector<int >{0, 5, 0, 0, 0, 4})), (std::vector<int >{19, 1, 1, 2, 6, 506}));
    EXPECT_EQ((compare(std::vector<int >{0, 0, 0, 0, 0}, std::vector<int >{-2, -1, 2, 25, -2, 1, 21, -9})), (std::vector<int >{2, 1, 2, 25, 2}));
    EXPECT_EQ((compare(std::vector<int >{0, 5, 0, 0, 0, 4}, std::vector<int >{4, 4, 1, 0, 0, 6})), (std::vector<int >{4, 1, 1, 0, 0, 2}));
    EXPECT_EQ((compare(std::vector<int >{1, 2, 3}, std::vector<int >{15, -3, 16, 0, 22, -182})), (std::vector<int >{14, 5, 13}));
    EXPECT_EQ((compare(std::vector<int >{6, -1}, std::vector<int >{1, 2, 3, 5})), (std::vector<int >{5, 3}));
    EXPECT_EQ((compare(std::vector<int >{-1, -3}, std::vector<int >{1, 2, 3, 5})), (std::vector<int >{2, 5}));
    EXPECT_EQ((compare(std::vector<int >{}, std::vector<int >{0, 0, 2, 0, 0, 0})), (std::vector<int >{}));
    EXPECT_EQ((compare(std::vector<int >{2, 4, -2}, std::vector<int >{4, 1, 1, 0, 0, -2, -3})), (std::vector<int >{2, 3, 3}));
    EXPECT_EQ((compare(std::vector<int >{-1, -2, -3}, std::vector<int >{-3, -2, -6, -202, -174, 1, -1})), (std::vector<int >{2, 0, 3}));
    EXPECT_EQ((compare(std::vector<int >{1, 2, 3, 4, 5, 1}, std::vector<int >{6, 1, 0, 6, -7, 9, 4})), (std::vector<int >{5, 1, 3, 2, 12, 8}));
    EXPECT_EQ((compare(std::vector<int >{1, 2, 3, 4, 2, -2}, std::vector<int >{4, 4, 1, 0, 0, 6, 9})), (std::vector<int >{3, 2, 2, 4, 2, 8}));
    EXPECT_EQ((compare(std::vector<int >{2, 0, 0, 1}, std::vector<int >{-1, -2, -3, 4})), (std::vector<int >{3, 2, 3, 3}));
    EXPECT_EQ((compare(std::vector<int >{1, 2, 3, 4, 2, -2}, std::vector<int >{1, 2, 3, 4, 2, -2, -8})), (std::vector<int >{0, 0, 0, 0, 0, 0}));
    EXPECT_EQ((compare(std::vector<int >{0}, std::vector<int >{4, 4, 1, 0, 0})), (std::vector<int >{4}));
    EXPECT_EQ((compare(std::vector<int >{4, 2, 6}, std::vector<int >{1, 12, 2, 2, -2})), (std::vector<int >{3, 10, 4}));
    EXPECT_EQ((compare(std::vector<int >{1, 2, 3, 4, 5, 1}, std::vector<int >{0, 0, 0, 0, 0, 0})), (std::vector<int >{1, 2, 3, 4, 5, 1}));
    EXPECT_EQ((compare(std::vector<int >{-8, 2, 3}, std::vector<int >{0, 0, 0, 0, 3, 3})), (std::vector<int >{8, 2, 3}));
    EXPECT_EQ((compare(std::vector<int >{18, 11, -2, 1, -3}, std::vector<int >{1, 2, 3, 1, 5, 4})), (std::vector<int >{17, 9, 5, 0, 8}));
    EXPECT_EQ((compare(std::vector<int >{-1, 2, 3, 4}, std::vector<int >{1000, 25, 5, 0})), (std::vector<int >{1001, 23, 2, 4}));
    EXPECT_EQ((compare(std::vector<int >{-1, -2, -3, -480}, std::vector<int >{4, 1, 1, 0, 0, -2})), (std::vector<int >{5, 3, 4, 480}));
    EXPECT_EQ((compare(std::vector<int >{}, std::vector<int >{2, 4, 6})), (std::vector<int >{}));
}

TEST(Probe, Strongest_Extension_01) {
    EXPECT_EQ((Strongest_Extension(std::string("u-H_-"), std::vector<std::string >{std::string("t234An"), std::string("TAR"), std::string("Ta"), std::string("cosSo")})), (std::string("u-H_-.TAR")));
    EXPECT_EQ((Strongest_Extension(std::string("NoReW"), std::vector<std::string >{std::string("AA"), std::string("Be"), std::string("CC")})), (std::string("NoReW.AA")));
    EXPECT_EQ((Strongest_Extension(std::string("gs"), std::vector<std::string >{std::string("AA"), std::string("Be"), std::string("CC")})), (std::string("gs.AA")));
    EXPECT_EQ((Strongest_Extension(std::string("NVowU"), std::vector<std::string >{std::string("SErviNGSliCes"), std::string("Cheese"), std::string("StuFfed")})), (std::string("NVowU.SErviNGSliCes")));
    EXPECT_EQ((Strongest_Extension(std::string("__HAHA"), std::vector<std::string >{})), (std::string("__HAHA.")));
    EXPECT_EQ((Strongest_Extension(std::string("671235"), std::vector<std::string >{std::string("91245"), std::string("Bb")})), (std::string("671235.91245")));
    EXPECT_EQ((Strongest_Extension(std::string("hHAHA.13"), std::vector<std::string >{std::string("Slicexs.SErviNGSliCes"), std::string("kIKILL123"), std::string("Nae1")})), (std::string("hHAHA.13.kIKILL123")));
    EXPECT_EQ((Strongest_Extension(std::string("C__YESIMHERE"), std::vector<std::string >{std::string("t"), std::string("eMptY"), std::string("(nothing"), std::string("zeR00"), std::string("NuLl__"), std::string("123NoooneB321")})), (std::string("C__YESIMHERE.NuLl__")));
    EXPECT_EQ((Strongest_Extension(std::string("z23"), std::vector<std::string >{std::string("b"), std::string("YEs.WeCaNe"), std::string("Lt"), std::string("zeR0"), std::string("Fails"), std::string("_(L(e"), std::string("hzjEa.sCcEv"), std::string("pIGHb8OrKe")})), (std::string("z23.YEs.WeCaNe")));
    EXPECT_EQ((Strongest_Extension(std::string("123NooonB321"), std::vector<std::string >{std::string("__YESIMHERE"), std::string("niNE"), std::string("eIGHt8OKe")})), (std::string("123NooonB321.__YESIMHERE")));
    EXPECT_EQ((Strongest_Extension(std::string("Slices.SErviNGSliCes"), std::vector<std::string >{std::string("tEN"), std::string("eIGHt8OKe"), std::string("niNE")})), (std::string("Slices.SErviNGSliCes.eIGHt8OKe")));
    EXPECT_EQ((Strongest_Extension(std::string("CC"), std::vector<std::string >{std::string("BokV123.Yvs.WCaNe"), std::string("__YSIMHERE.NuLl__"), std::string("__YESIMHERE"), std::string("91245"), std::string("QFa4il"), std::string("6L.1E.D")})), (std::string("CC.__YESIMHERE")));
    EXPECT_EQ((Strongest_Extension(std::string(""), std::vector<std::string >{std::string("ft"), std::string("YameRore.okIWILL123"), std::string("Boku123"), std::string("_"), std::string("g"), std::string("TAR")})), (std::string(".TAR")));
    EXPECT_EQ((Strongest_Extension(std::string("-w7Dcs"), std::vector<std::string >{std::string("__HAHA.123"), std::string("Boku123"), std::string("__YESIMHERE")})), (std::string("-w7Dcs.__YESIMHERE")));
    EXPECT_EQ((Strongest_Extension(std::string("KSuTAR"), std::vector<std::string >{std::string("__HAHA.123"), std::string("HAu"), std::string("Tab"), std::string("xK"), std::string("234Av-"), std::string("_"), std::string("Die"), std::string("__YESIMHERE")})), (std::string("KSuTAR.__YESIMHERE")));
    EXPECT_EQ((Strongest_Extension(std::string("Watashi.eIGHt8OKe"), std::vector<std::string >{std::string("NazeDa"), std::string("zeR00"), std::string("Slicev"), std::string("nani")})), (std::string("Watashi.eIGHt8OKe.zeR00")));
    EXPECT_EQ((Strongest_Extension(std::string("Chee2e"), std::vector<std::string >{std::string("HhAas")})), (std::string("Chee2e.HhAas")));
    EXPECT_EQ((Strongest_Extension(std::string("A "), std::vector<std::string >{std::string("K.TAR"), std::string("92"), std::string("32144tggg"), std::string("Boku123.YEs.WeCaNe"), std::string("nanj")})), (std::string("A .K.TAR")));
    EXPECT_EQ((Strongest_Extension(std::string("TgpE"), std::vector<std::string >{std::string("v"), std::string("UG123"), std::string(""), std::string(""), std::string("8Inm9aZwEQ_"), std::string("jezDycB8N3Zu"), std::string("JLHqwhW")})), (std::string("TgpE.UG123")));
    EXPECT_EQ((Strongest_Extension(std::string("gw9rIIV"), std::vector<std::string >{std::string("Die"), std::string("NowW"), std::string("Wow"), std::string("WoW"), std::string("Watashi")})), (std::string("gw9rIIV.WoW")));
    EXPECT_EQ((Strongest_Extension(std::string("lWf"), std::vector<std::string >{std::string("nani"), std::string("YEs.WeCaNe"), std::string("NazeDa"), std::string("32145tggg")})), (std::string("lWf.YEs.WeCaNe")));
    EXPECT_EQ((Strongest_Extension(std::string("wXrcyQ"), std::vector<std::string >{})), (std::string("wXrcyQ.")));
    EXPECT_EQ((Strongest_Extension(std::string("my_class"), std::vector<std::string >{std::string("__YESIMHERE"), std::string("dT"), std::string("my_class"), std::string("ameRore.okIWILL123"), std::string("t"), std::string("YameRore")})), (std::string("my_class.__YESIMHERE")));
    EXPECT_EQ((Strongest_Extension(std::string("Yaeore"), std::vector<std::string >{std::string("__HHA.123"), std::string("Wow"), std::string("mWy2_czass"), std::string("SErvN5SliCes")})), (std::string("Yaeore.__HHA.123")));
    EXPECT_EQ((Strongest_Extension(std::string("S Bb"), std::vector<std::string >{std::string("Tab"), std::string("123"), std::string("781345"), std::string("-_-")})), (std::string("S Bb.123")));
}

TEST(Probe, Strongest_Extension_02) {
    EXPECT_EQ((Strongest_Extension(std::string("finNNalLLly.WoW"), std::vector<std::string >{std::string("t"), std::string("eMptY"), std::string("(nothing"), std::string("zeR00"), std::string("NuLl__"), std::string("123NoooneB321")})), (std::string("finNNalLLly.WoW.NuLl__")));
    EXPECT_EQ((Strongest_Extension(std::string("d"), std::vector<std::string >{std::string("dDxaP_3-"), std::string("123"), std::string("R1pkoV"), std::string("ABZ RYRu2B"), std::string("DoeyZuWe"), std::string("StuFfed")})), (std::string("d.ABZ RYRu2B")));
    EXPECT_EQ((Strongest_Extension(std::string("Chese"), std::vector<std::string >{std::string("nani"), std::string("NazeDa"), std::string("t234An"), std::string("32145tggg")})), (std::string("Chese.t234An")));
    EXPECT_EQ((Strongest_Extension(std::string(""), std::vector<std::string >{std::string("Tx"), std::string("wB6F"), std::string("hx4S")})), (std::string(".wB6F")));
    EXPECT_EQ((Strongest_Extension(std::string("oSf"), std::vector<std::string >{std::string("nani"), std::string("NazeDa"), std::string("32145tggg"), std::string("YEs.WeCaNe")})), (std::string("oSf.YEs.WeCaNe")));
    EXPECT_EQ((Strongest_Extension(std::string("Nvb8G1nty."), std::vector<std::string >{std::string("nani"), std::string("NazeDa"), std::string("YEs.WeCaNe"), std::string("32145tggg")})), (std::string("Nvb8G1nty..YEs.WeCaNe")));
    EXPECT_EQ((Strongest_Extension(std::string("Slices"), std::vector<std::string >{std::string("YameRore.okIWILL123"), std::string("eMptY"), std::string("YameRore"), std::string(""), std::string("Sp.671235"), std::string("t"), std::string("-_-"), std::string("NuLl__")})), (std::string("Slices.")));
    EXPECT_EQ((Strongest_Extension(std::string("-_-"), std::vector<std::string >{std::string("CC"), std::string("Ta"), std::string("r0qrR70nu0qq"), std::string("Tab"), std::string("Sp"), std::string("cosSo"), std::string("123NoooneB321")})), (std::string("-_-.CC")));
    EXPECT_EQ((Strongest_Extension(std::string("--ZbPvZlW"), std::vector<std::string >{std::string("SErviNGSliCes"), std::string("Cheese"), std::string("StuFfed")})), (std::string("--ZbPvZlW.SErviNGSliCes")));
    EXPECT_EQ((Strongest_Extension(std::string("NazeDa"), std::vector<std::string >{std::string("Die"), std::string("NowW"), std::string("WoW")})), (std::string("NazeDa.WoW")));
    EXPECT_EQ((Strongest_Extension(std::string("Wow"), std::vector<std::string >{std::string("Bb")})), (std::string("Wow.Bb")));
    EXPECT_EQ((Strongest_Extension(std::string("12NoooneB35T1"), std::vector<std::string >{std::string("671235"), std::string("Bb"), std::string("krEl")})), (std::string("12NoooneB35T1.671235")));
    EXPECT_EQ((Strongest_Extension(std::string("StuFfed"), std::vector<std::string >{std::string("Tab"), std::string("123"), std::string("781345"), std::string("-_-"), std::string("Fails")})), (std::string("StuFfed.123")));
    EXPECT_EQ((Strongest_Extension(std::string("-"), std::vector<std::string >{std::string("YKTR"), std::string("Kf"), std::string("tu_dPg_"), std::string("f9Zgjy9MAHX"), std::string("mYZrjO"), std::string("78145")})), (std::string("-.YKTR")));
    EXPECT_EQ((Strongest_Extension(std::string("Lww"), std::vector<std::string >{std::string("915"), std::string("csSo"), std::string("qBe")})), (std::string("Lww.915")));
    EXPECT_EQ((Strongest_Extension(std::string("t"), std::vector<std::string >{std::string("Die"), std::string("NowW"), std::string("Wow"), std::string("okSWILL123")})), (std::string("t.okSWILL123")));
    EXPECT_EQ((Strongest_Extension(std::string("cosSo"), std::vector<std::string >{std::string("nani"), std::string("NazeDa"), std::string("32145tggg")})), (std::string("cosSo.NazeDa")));
    EXPECT_EQ((Strongest_Extension(std::string("pnpUK"), std::vector<std::string >{std::string(""), std::string("WEZW"), std::string("tZ"), std::string("YameRore")})), (std::string("pnpUK.WEZW")));
    EXPECT_EQ((Strongest_Extension(std::string("Watashi.eIGWt8OKe"), std::vector<std::string >{std::string("t"), std::string("eMptY"), std::string("(nothing"), std::string("zeR00"), std::string("NuLl__"), std::string("123NoooneB321")})), (std::string("Watashi.eIGWt8OKe.NuLl__")));
    EXPECT_EQ((Strongest_Extension(std::string("finNNalLLly.WoW"), std::vector<std::string >{std::string("FfSls")})), (std::string("finNNalLLly.WoW.FfSls")));
    EXPECT_EQ((Strongest_Extension(std::string("6125"), std::vector<std::string >{std::string("nani"), std::string("NazeDa"), std::string("YEs.WeCaNe"), std::string("32145tggg")})), (std::string("6125.YEs.WeCaNe")));
    EXPECT_EQ((Strongest_Extension(std::string("g"), std::vector<std::string >{std::string("eIGHt8OKe"), std::string("YameRore"), std::string("(0e4hsxkv")})), (std::string("g.eIGHt8OKe")));
    EXPECT_EQ((Strongest_Extension(std::string("1f3"), std::vector<std::string >{std::string("Die"), std::string("NowW"), std::string("Wow"), std::string("WoW")})), (std::string("1f3.WoW")));
}
