// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_03.h"

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

TEST(Probe, count_distinct_characters_01) {
    EXPECT_EQ((count_distinct_characters(std::string("YlBe"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("OQkU4"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("Jerry NERRY JeRRRY"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("YVIZEln"))), (7));
    EXPECT_EQ((count_distinct_characters(std::string("Jrry"))), (3));
    EXPECT_EQ((count_distinct_characters(std::string("abaQaOAAAAaaaa"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("PSaaAAAAaala"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("abcde"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("xyzYZ"))), (3));
    EXPECT_EQ((count_distinct_characters(std::string("GJerry"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("Jerrty"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("JJy"))), (2));
    EXPECT_EQ((count_distinct_characters(std::string("N"))), (1));
    EXPECT_EQ((count_distinct_characters(std::string("rxJeIrry"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("ery"))), (3));
    EXPECT_EQ((count_distinct_characters(std::string("xyXhZ"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("6KTY"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("biKbK3sQxY4"))), (9));
    EXPECT_EQ((count_distinct_characters(std::string("Jegrry jERRY JeRRRY"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("L4lSeuHpCHtM"))), (10));
    EXPECT_EQ((count_distinct_characters(std::string("mB6G"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("ar"))), (2));
    EXPECT_EQ((count_distinct_characters(std::string("UvY MxD"))), (7));
    EXPECT_EQ((count_distinct_characters(std::string("abdecdeCADE"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("abfcdcadeCADE"))), (6));
}

TEST(Probe, count_distinct_characters_02) {
    EXPECT_EQ((count_distinct_characters(std::string("9ab3Tde"))), (7));
    EXPECT_EQ((count_distinct_characters(std::string("Jerry jERR JeRRRY"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("aaWaaAAAaaafa"))), (3));
    EXPECT_EQ((count_distinct_characters(std::string("Jerr jERRY xeRRRY"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("QpwY 0"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("J6rry ERRY JJRRRY"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("acdecadeCADE"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("TZ94NvE7K"))), (9));
    EXPECT_EQ((count_distinct_characters(std::string("8aaDaAAAAaaaa"))), (3));
    EXPECT_EQ((count_distinct_characters(std::string("abdecadeCADE"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("MwcBGS36RZk"))), (11));
    EXPECT_EQ((count_distinct_characters(std::string("U"))), (1));
    EXPECT_EQ((count_distinct_characters(std::string("Jerr jERyY J4RRRY"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("aaaaAAAAaaHaa"))), (2));
    EXPECT_EQ((count_distinct_characters(std::string("aaaarAAAAalaa"))), (3));
    EXPECT_EQ((count_distinct_characters(std::string("aaaPAAAAaaaa"))), (2));
    EXPECT_EQ((count_distinct_characters(std::string("kx"))), (2));
    EXPECT_EQ((count_distinct_characters(std::string("Jerry ERRY JeRRRY"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("FKlLBGrZIrd"))), (9));
    EXPECT_EQ((count_distinct_characters(std::string("5Z1ZyWu"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("xyrzYZ"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("aJbcdecadeCADE"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("Jery jERRYeJeRRRY"))), (5));
}

TEST(Probe, parse_music_01) {
    EXPECT_EQ((parse_music(std::string("o| o| .| .| o o o o"))), (std::vector<int >{2, 2, 1, 1, 4, 4, 4, 4}));
    EXPECT_EQ((parse_music(std::string("o| o .| .| o o  C"))), (std::vector<int >{2, 4, 1, 1, 4, 4}));
    EXPECT_EQ((parse_music(std::string("o|"))), (std::vector<int >{2}));
    EXPECT_EQ((parse_music(std::string(".|.X | .|"))), (std::vector<int >{1}));
    EXPECT_EQ((parse_music(std::string("gHHTkt"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o| o| | .| o o o o"))), (std::vector<int >{2, 2, 1, 4, 4, 4, 4}));
    EXPECT_EQ((parse_music(std::string(".| .| .| .|"))), (std::vector<int >{1, 1, 1, 1}));
    EXPECT_EQ((parse_music(std::string("Em.dU6u"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string(""))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("wi"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("O3.ZGTdw3Lbd"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o o| .| o| o| .| .| .| .| o o"))), (std::vector<int >{4, 2, 1, 2, 2, 1, 1, 1, 1, 4, 4}));
    EXPECT_EQ((parse_music(std::string("4HblA"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o| .| o| .| o o| o o|"))), (std::vector<int >{2, 1, 2, 1, 4, 2, 4, 2}));
    EXPECT_EQ((parse_music(std::string("pz0z"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("T A"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("w."))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("G.|"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o"))), (std::vector<int >{4}));
    EXPECT_EQ((parse_music(std::string("wIiiSjh9|.f"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("iNWwRhnj"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o| .| o| .|go o| o o"))), (std::vector<int >{2, 1, 2, 2, 4, 4}));
    EXPECT_EQ((parse_music(std::string("|ipb"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o  o o"))), (std::vector<int >{4, 4, 4}));
    EXPECT_EQ((parse_music(std::string("a0"))), (std::vector<int >{}));
}

TEST(Probe, parse_music_02) {
    EXPECT_EQ((parse_music(std::string("qQv.qbq|8."))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("z"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("tnKkSown"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("AcZ"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("nwSNJcyKb"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o W| .| o. o| .| .| .| .| o o"))), (std::vector<int >{4, 1, 2, 1, 1, 1, 1, 4, 4}));
    EXPECT_EQ((parse_music(std::string("X"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string(".| .| y| |"))), (std::vector<int >{1, 1}));
    EXPECT_EQ((parse_music(std::string("o o| .| o| fo| . .| .| .| o o"))), (std::vector<int >{4, 2, 1, 2, 1, 1, 1, 4, 4}));
    EXPECT_EQ((parse_music(std::string(".| .| o.|K.|"))), (std::vector<int >{1, 1}));
    EXPECT_EQ((parse_music(std::string("f7Qj"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("qD9pW2ittw9"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("OAJL"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("4djTXhF"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o| .|o| .| o o| o o|"))), (std::vector<int >{2, 1, 4, 2, 4, 2}));
    EXPECT_EQ((parse_music(std::string("oEo o E"))), (std::vector<int >{4}));
    EXPECT_EQ((parse_music(std::string("quabk6VQMy"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("k"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o .| o| .| Q o| o o|"))), (std::vector<int >{4, 1, 2, 1, 2, 4, 2}));
    EXPECT_EQ((parse_music(std::string("fWnDCsHH"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o||"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("9"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("gJDf"))), (std::vector<int >{}));
}

TEST(Probe, how_many_times_01) {
    EXPECT_EQ((how_many_times(std::string("Faa"), std::string("Oa"))), (0));
    EXPECT_EQ((how_many_times(std::string("dUyLmO"), std::string("a"))), (0));
    EXPECT_EQ((how_many_times(std::string("cacacacac"), std::string("cac"))), (4));
    EXPECT_EQ((how_many_times(std::string("aaa"), std::string(""))), (4));
    EXPECT_EQ((how_many_times(std::string("ea"), std::string(""))), (3));
    EXPECT_EQ((how_many_times(std::string("5Gur"), std::string("aaa"))), (0));
    EXPECT_EQ((how_many_times(std::string("cacacacac"), std::string("ek"))), (0));
    EXPECT_EQ((how_many_times(std::string("5ewA4"), std::string("zB"))), (0));
    EXPECT_EQ((how_many_times(std::string("ypMOVOX2oiJ"), std::string("Lxw"))), (0));
    EXPECT_EQ((how_many_times(std::string("TQiz6PJepi"), std::string("john Ze"))), (0));
    EXPECT_EQ((how_many_times(std::string("aaa"), std::string("cac"))), (0));
    EXPECT_EQ((how_many_times(std::string("aaVa"), std::string("aa"))), (1));
    EXPECT_EQ((how_many_times(std::string(""), std::string("i"))), (0));
    EXPECT_EQ((how_many_times(std::string("johnhdoe"), std::string("xyxyxyx"))), (0));
    EXPECT_EQ((how_many_times(std::string("cacacacac"), std::string("7zI"))), (0));
    EXPECT_EQ((how_many_times(std::string("VSk5nWKNCuF"), std::string("fDxovMvX"))), (0));
    EXPECT_EQ((how_many_times(std::string(""), std::string("R4kdhi"))), (0));
    EXPECT_EQ((how_many_times(std::string("a"), std::string(""))), (2));
    EXPECT_EQ((how_many_times(std::string("5Ti0oYIX"), std::string("Yphu"))), (0));
    EXPECT_EQ((how_many_times(std::string("john"), std::string(""))), (5));
    EXPECT_EQ((how_many_times(std::string("john doe"), std::string("Vxyxyx"))), (0));
    EXPECT_EQ((how_many_times(std::string("john doe"), std::string("Q"))), (0));
    EXPECT_EQ((how_many_times(std::string("john doe"), std::string("iaaa"))), (0));
    EXPECT_EQ((how_many_times(std::string("aaa"), std::string("aa"))), (2));
    EXPECT_EQ((how_many_times(std::string(""), std::string("joh"))), (0));
}

TEST(Probe, how_many_times_02) {
    EXPECT_EQ((how_many_times(std::string("aaaa"), std::string(""))), (5));
    EXPECT_EQ((how_many_times(std::string("john doe"), std::string("Pc"))), (0));
    EXPECT_EQ((how_many_times(std::string("john doe"), std::string("john"))), (1));
    EXPECT_EQ((how_many_times(std::string("HsnyiB "), std::string("p"))), (0));
    EXPECT_EQ((how_many_times(std::string("TXrsgNu2D6G"), std::string("a"))), (0));
    EXPECT_EQ((how_many_times(std::string("aaaa"), std::string("cac"))), (0));
    EXPECT_EQ((how_many_times(std::string("n"), std::string("a"))), (0));
    EXPECT_EQ((how_many_times(std::string("Pg1 ZoRqPC "), std::string(""))), (12));
    EXPECT_EQ((how_many_times(std::string("WzOkP4UYb"), std::string("C"))), (0));
    EXPECT_EQ((how_many_times(std::string("yeY04guQl"), std::string("e C0l8"))), (0));
    EXPECT_EQ((how_many_times(std::string("26EO00mDI1Z"), std::string("2"))), (1));
    EXPECT_EQ((how_many_times(std::string("aa"), std::string("jZ"))), (0));
    EXPECT_EQ((how_many_times(std::string("icmc"), std::string("z"))), (0));
    EXPECT_EQ((how_many_times(std::string("08ea"), std::string("a"))), (1));
    EXPECT_EQ((how_many_times(std::string("O38XQr08"), std::string("A"))), (0));
    EXPECT_EQ((how_many_times(std::string("mkZ8sIOtJ"), std::string("xyxyxyx"))), (0));
    EXPECT_EQ((how_many_times(std::string("kqg2pBe53Dy"), std::string("3hCK"))), (0));
    EXPECT_EQ((how_many_times(std::string("aaaa"), std::string("2"))), (0));
    EXPECT_EQ((how_many_times(std::string("cacaccac"), std::string("john doe"))), (0));
    EXPECT_EQ((how_many_times(std::string("YpEt5fAot"), std::string("aRa"))), (0));
    EXPECT_EQ((how_many_times(std::string("xyxyxyx"), std::string("x"))), (4));
    EXPECT_EQ((how_many_times(std::string("john de"), std::string("UtEE"))), (0));
    EXPECT_EQ((how_many_times(std::string("fcacacacauc"), std::string("UhmYCdGj"))), (0));
}

TEST(Probe, sort_numbers_01) {
    EXPECT_EQ((sort_numbers(std::string("Kpr5ee"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("six fie four three two one zero"))), (std::string("zero zero one two three four six")));
    EXPECT_EQ((sort_numbers(std::string(" 'hree"))), (std::string("zero zero")));
    EXPECT_EQ((sort_numbers(std::string("N1bNAunkfIv"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("uOG2"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("GRA yPNN"))), (std::string("zero zero")));
    EXPECT_EQ((sort_numbers(std::string(" iAoU"))), (std::string("zero zero")));
    EXPECT_EQ((sort_numbers(std::string("SXmTnx"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("l9T64hPnHv"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("9cybH"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("8K1"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("sixfive four thre two one zero"))), (std::string("zero zero zero one two four")));
    EXPECT_EQ((sort_numbers(std::string("ine"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("three one five"))), (std::string("one three five")));
    EXPECT_EQ((sort_numbers(std::string("BNU9RwuFT5"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("zero four five seven eight nine"))), (std::string("zero four five seven eight nine")));
    EXPECT_EQ((sort_numbers(std::string("eGqf"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("zehsro"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("nine"))), (std::string("nine")));
    EXPECT_EQ((sort_numbers(std::string("XuQnGmg8zG"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("Q"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("zero four five seven Qeight mnne"))), (std::string("zero zero zero four five seven")));
    EXPECT_EQ((sort_numbers(std::string("thee"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("zero four fie seven ightq nine"))), (std::string("zero zero zero four seven nine")));
    EXPECT_EQ((sort_numbers(std::string("three five nine"))), (std::string("three five nine")));
}

TEST(Probe, sort_numbers_02) {
    EXPECT_EQ((sort_numbers(std::string("Mf41dC4"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string(", 'three"))), (std::string("zero zero")));
    EXPECT_EQ((sort_numbers(std::string("one th4e2 five"))), (std::string("zero one five")));
    EXPECT_EQ((sort_numbers(std::string("hix five four three two onegero"))), (std::string("zero zero two three four five")));
    EXPECT_EQ((sort_numbers(std::string("three"))), (std::string("three")));
    EXPECT_EQ((sort_numbers(std::string("R6dv"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("one thrWe five"))), (std::string("zero one five")));
    EXPECT_EQ((sort_numbers(std::string("awYjFO0iw"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("our"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("2fnv"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("iiUkxoQD"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("wDeX0TUpl iS"))), (std::string("zero zero")));
    EXPECT_EQ((sort_numbers(std::string("theeyfiveM nine"))), (std::string("zero nine")));
    EXPECT_EQ((sort_numbers(std::string("vfc"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("F6L5aYYRGW20"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("9yjVqV52d3vv"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("c, 'thrGee"))), (std::string("zero zero")));
    EXPECT_EQ((sort_numbers(std::string("d"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("Mnine"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("ne3 three fve"))), (std::string("zero zero three")));
    EXPECT_EQ((sort_numbers(std::string("bipkIBZ4zt"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string(", 'seven"))), (std::string("zero zero")));
    EXPECT_EQ((sort_numbers(std::string("five zero Qfour seveg nine eight"))), (std::string("zero zero zero five eight nine")));
}

TEST(Probe, find_closest_elements_01) {
    ExpectNearVec(find_closest_elements(std::vector<float >{3.9000001f, 4.0f}), std::vector<float >{3.9000001f, 4.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.0f, 2.0f}), std::vector<float >{2.0f, 2.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.20000005f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f}), std::vector<float >{2.0f, 2.20000005f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{5.9000001f, 5.0f}), std::vector<float >{5.0f, 5.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{0.0f, -5.0f, 4.0999999f}), std::vector<float >{0.0f, 4.0999999f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.0f, 2.20000005f, 0.409999996f}), std::vector<float >{2.0f, 2.20000005f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{3.9000001f, 4.0f, -14.1000004f}), std::vector<float >{3.9000001f, 4.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.20000005f, 5.0f, 3.20000005f, 3.0f}), std::vector<float >{3.0f, 3.20000005f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 5.9000001f, 4.0f, 5.0f}), std::vector<float >{5.0f, 5.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.0f, 2.20000005f}), std::vector<float >{2.0f, 2.20000005f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.10000002f, 2.20000005f, 3.0999999f, 8.69999981f, 5.0999999f}), std::vector<float >{2.20000005f, 3.0999999f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{3.9000001f, 4.0f, -6.5999999f}), std::vector<float >{3.9000001f, 4.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{9.80000019f, 2.0f}), std::vector<float >{2.0f, 9.80000019f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{-8.30000019f, -0.800000012f, 2.0f, 5.69999981f, -4.5999999f, 0.0f, 3.0f}), std::vector<float >{-0.800000012f, 0.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.10000002f, 2.20000005f, 3.0999999f, 4.0999999f, 5.0999999f, 5.0999999f}), std::vector<float >{5.0999999f, 5.0999999f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{13.5f, 0.0f, -13.5f, 12.8000002f, 1.67999995f, 17.2999992f}), std::vector<float >{12.8000002f, 13.5f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{-7.9000001f, -1.89999998f, 3.0999999f}), std::vector<float >{-1.89999998f, 3.0999999f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{6.4000001f, 0.0f, -0.349999994f}), std::vector<float >{-0.349999994f, 0.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{5.0f, 5.9000001f}), std::vector<float >{5.0f, 5.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{0.0f, -14.8999996f, -15.3000002f, 0.0f, 0.0f, 4.5999999f, 8.69999981f}), std::vector<float >{0.0f, 0.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{-15.3999996f, 5.59000015f, -0.300000012f, -1.0f, 1.89999998f, 1.60000002f, 5.0f}), std::vector<float >{1.60000002f, 1.89999998f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.0f, 3.0f, 4.0f, 5.0f, 2.20000005f}), std::vector<float >{2.0f, 2.20000005f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.10000002f, 2.20000005f, 3.0999999f, 3.9000001f, 5.0999999f}), std::vector<float >{3.0999999f, 3.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 5.0f, 4.0f, 5.9000001f}), std::vector<float >{5.0f, 5.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{5.0f, 5.9000001f, 0.5f}), std::vector<float >{5.0f, 5.9000001f}, 1e-5);
}

TEST(Probe, find_closest_elements_02) {
    ExpectNearVec(find_closest_elements(std::vector<float >{-2.0999999f, -1.70000005f, 5.69999981f, -6.5f, 9.99999975e-05f, 1.60000002f, 17.7000008f}), std::vector<float >{-2.0999999f, -1.70000005f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.0f, 1.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}), std::vector<float >{3.9000001f, 4.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{3.0999999f, 2.20000005f}), std::vector<float >{2.20000005f, 3.0999999f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}), std::vector<float >{3.9000001f, 4.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 2.20000005f, 5.0f, 4.0f}), std::vector<float >{2.0f, 2.20000005f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{3.9000001f, 0.0f}), std::vector<float >{0.0f, 3.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.20000005f, 0.0f, 4.19999981f, 6.69999981f, -1.39999998f, 18.3999996f, 4.0999999f}), std::vector<float >{4.0999999f, 4.19999981f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.10000002f, 3.0999999f, 4.0999999f, 5.0999999f}), std::vector<float >{3.0999999f, 4.0999999f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}), std::vector<float >{3.9000001f, 4.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{9.39999962f, 4.0999999f, -6.9000001f}), std::vector<float >{4.0999999f, 9.39999962f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{-5.19999981f, 0.0f, 1.29999995f, -15.0f, 5.9000001f, -4.5999999f, 0.0f, 7.69000006f}), std::vector<float >{0.0f, 0.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 4.0f, 5.0f, 2.20000005f}), std::vector<float >{2.0f, 2.20000005f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{4.0f, 9.99999975e-05f, 2.20000005f, 4.69999981f, -17.8999996f, 2.71000004f}), std::vector<float >{2.20000005f, 2.71000004f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{4.9000001f, 0.0f, 1.64999998f, 0.0f, -10.0f, 5.30000019f, 4.0999999f}), std::vector<float >{0.0f, 0.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 5.9000001f, 4.0f, 3.0999999f}), std::vector<float >{3.0999999f, 4.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{3.9000001f, 4.0f, 5.0f}), std::vector<float >{3.9000001f, 4.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{0.0f, 5.0999999f, 9.99999975e-05f, -1.09990001f, 0.0f}), std::vector<float >{0.0f, 0.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{0.0f, 2.0f, -4.30000019f}), std::vector<float >{0.0f, 2.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{6.44000006f, 0.5f, 3.0999999f, 5.69999981f, -2.20000005f, 0.0f, 9.60000038f, 12.6000004f}), std::vector<float >{0.0f, 0.5f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.0f, 1.10000002f}), std::vector<float >{1.10000002f, 2.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{3.9000001f, -3.4000001f}), std::vector<float >{-3.4000001f, 3.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{5.0f, 5.9000001f, 0.0f}), std::vector<float >{5.0f, 5.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{5.0999999f, 1.89999998f}), std::vector<float >{1.89999998f, 5.0999999f}, 1e-5);
}

TEST(Probe, rescale_to_unit_01) {
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.0f, 1.0f, 2.0f}), std::vector<float >{0.0f, 0.5f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{12.0f, 11.0f, 15.0f, 13.0f, 14.0f}), std::vector<float >{0.25f, 0.0f, 1.0f, 0.5f, 0.75f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, -11.8000002f}), std::vector<float >{1.0f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.0f, 0.25f, 0.5f, 0.75f, 1.0f, -1.10000002f}), std::vector<float >{0.523809552f, 0.642857194f, 0.761904836f, 0.880952418f, 1.0f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{13.0f, -6.69999981f, -3.70000005f, -16.3999996f, 1.79999995f, 2.05999994f, -13.5f}), std::vector<float >{1.0f, 0.329931974f, 0.431972802f, 0.0f, 0.619047582f, 0.627891123f, 0.0986394435f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.25f, 0.0f, 1.0f, 0.5f, 0.75f}), std::vector<float >{0.25f, 0.0f, 1.0f, 0.5f, 0.75f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.25f, 0.0f, 1.0f, 0.5f, 0.75f, 14.0f}), std::vector<float >{0.0178571437f, 0.0f, 0.0714285746f, 0.0357142873f, 0.0535714291f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, 3.0f, 4.0f, 5.0f}), std::vector<float >{0.0f, 0.5f, 0.75f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{16.3999996f, 1.0f, -1.5f, 1.0f, 3.0f, 0.0f, 0.75f}), std::vector<float >{1.0f, 0.139664814f, 0.0f, 0.139664814f, 0.251396656f, 0.0837988853f, 0.125698328f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{-8.80000019f, 49.9000015f}), std::vector<float >{0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.5f, 8.31999969f, 17.2000008f, 3.0f, 5.69999981f, 1.0f}), std::vector<float >{0.0f, 0.468263447f, 1.0f, 0.149700597f, 0.311377227f, 0.029940119f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{49.9000015f, 14.0f, 19.7999992f, 50.7000008f, 9.80000019f, 9.14999962f}), std::vector<float >{0.980746031f, 0.116726838f, 0.256317675f, 1.0f, 0.0156438146f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{-5.03999996f, 1.0f, 15.0f, 0.0f, -18.1000004f, 1.0f, 1.0f, 1.0f}), std::vector<float >{0.394561976f, 0.577039301f, 1.0f, 0.546827853f, 0.0f, 0.577039301f, 0.577039301f, 0.577039301f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{2.0f, 49.9000015f}), std::vector<float >{0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.32000005f, 1.0f}), std::vector<float >{1.0f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{13.8999996f, 9.99999975e-05f, 4.0f, 15.0f, 0.0f, 11.0f, 6.5f}), std::vector<float >{0.926666617f, 6.66666665e-06f, 0.266666681f, 1.0f, 0.0f, 0.733333349f, 0.433333337f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{2.0f, 3.0f, 5.0f, 1.0f, 4.0f}), std::vector<float >{0.25f, 0.5f, 1.0f, 0.0f, 0.75f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{}), std::vector<float >{}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{2.0f, 0.0f, 7.5999999f}), std::vector<float >{0.263157904f, 0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{2.75f, 4.0f, 5.71999979f, 19.5f, 5.0f, 9.80000019f, 2.0f, -7.0999999f}), std::vector<float >{0.37030077f, 0.417293251f, 0.481954873f, 1.0f, 0.454887211f, 0.635338306f, 0.342105269f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, 2.0f}), std::vector<float >{0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{3.0f, 48.2000008f}), std::vector<float >{0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{2.0f, 1.0f, 5.0f, 3.0f, 4.0f}), std::vector<float >{0.25f, 0.0f, 1.0f, 0.5f, 0.75f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.0f, -7.69999981f, 12.0f}), std::vector<float >{0.390862912f, 0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{-2.70000005f, -1.70000005f, 5.46000004f, -14.0f, -13.1999998f}), std::vector<float >{0.580678344f, 0.632065833f, 1.0f, 0.0f, 0.0411099792f}, 1e-5);
}

TEST(Probe, rescale_to_unit_02) {
    ExpectNearVec(rescale_to_unit(std::vector<float >{-2.20000005f, 49.9000015f, 2.0999999f, 100.0f}), std::vector<float >{0.0f, 0.509784758f, 0.0420743674f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{-1.39999998f, 0.0f, -8.30000019f, 0.0f}), std::vector<float >{0.831325293f, 1.0f, 0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{3.0f, 5.76000023f, -3.0999999f, 1.0f, -5.69999981f, 12.1000004f, 13.1999998f, 49.9000015f}), std::vector<float >{0.156474814f, 0.206115097f, 0.0467625856f, 0.12050359f, 0.0f, 0.320143849f, 0.339928031f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, 0.0f, 15.0f}), std::vector<float >{0.0666666701f, 0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{50.9000015f, 49.9000015f}), std::vector<float >{1.0f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{49.9000015f, 100.0f}), std::vector<float >{0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, 14.0f, -14.8999996f, 7.46000004f, -2.70000005f}), std::vector<float >{0.550172985f, 1.0f, 0.0f, 0.773702443f, 0.422145337f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{3.5f, 12.0f, 18.5f, 1.10000002f, -7.0999999f, 3.0f, -18.2000008f, 0.0f}), std::vector<float >{0.591280639f, 0.822888315f, 1.0f, 0.525885582f, 0.302452326f, 0.577656686f, 0.0f, 0.49591282f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{2.0f, 1.79999995f}), std::vector<float >{1.0f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.25f, 0.5f, 0.75f, 1.0f}), std::vector<float >{0.0f, 0.333333343f, 0.666666687f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.0f, 2.0f, 0.5f, 0.75f, 1.0f}), std::vector<float >{0.0f, 1.0f, 0.25f, 0.375f, 0.5f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f}), std::vector<float >{0.0f, 0.25f, 0.5f, 0.75f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, -6.5999999f}), std::vector<float >{0.655172408f, 0.741379321f, 0.827586234f, 0.913793087f, 1.0f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{7.80000019f, 0.5f, -0.140000001f, 13.8999996f, 17.8999996f, 13.5f, 1.0f}), std::vector<float >{0.440133065f, 0.0354767181f, 0.0f, 0.778270543f, 1.0f, 0.756097615f, 0.063192904f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, 2.0f, 4.0f, 3.0f, 5.0f}), std::vector<float >{0.0f, 0.25f, 0.75f, 0.5f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, 2.0f, 3.0f, 1.0f, 5.0f}), std::vector<float >{0.0f, 0.25f, 0.5f, 0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{13.0f, 1.0f, 15.0f}), std::vector<float >{0.857142866f, 0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{12.0f, 14.0f, 15.0f, 13.0f, 11.0f}), std::vector<float >{0.25f, 0.75f, 1.0f, 0.5f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.0f, 0.25f, 0.75f, 1.0f}), std::vector<float >{0.0f, 0.25f, 0.75f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{100.0f, 49.9000015f}), std::vector<float >{1.0f, 0.0f}, 1e-5);
}

TEST(Probe, strlen_01) {
    EXPECT_EQ((strlen(std::string("bc"))), (2));
    EXPECT_EQ((strlen(std::string("abc"))), (3));
    EXPECT_EQ((strlen(std::string("KZDXgv4pw"))), (9));
    EXPECT_EQ((strlen(std::string("pgN"))), (3));
    EXPECT_EQ((strlen(std::string("xkc"))), (3));
    EXPECT_EQ((strlen(std::string("j"))), (1));
    EXPECT_EQ((strlen(std::string("TAac"))), (4));
    EXPECT_EQ((strlen(std::string("Mbu"))), (3));
    EXPECT_EQ((strlen(std::string("xQtiyY760GC"))), (11));
    EXPECT_EQ((strlen(std::string("le"))), (2));
    EXPECT_EQ((strlen(std::string("jVA"))), (3));
    EXPECT_EQ((strlen(std::string("z"))), (1));
    EXPECT_EQ((strlen(std::string("4jEgVaQOxkL"))), (11));
    EXPECT_EQ((strlen(std::string("nac"))), (3));
    EXPECT_EQ((strlen(std::string("cx"))), (2));
    EXPECT_EQ((strlen(std::string("O"))), (1));
    EXPECT_EQ((strlen(std::string("yctThqIvR"))), (9));
    EXPECT_EQ((strlen(std::string("q9gj5BAHX3gw"))), (12));
    EXPECT_EQ((strlen(std::string("S"))), (1));
    EXPECT_EQ((strlen(std::string("vk5En"))), (5));
    EXPECT_EQ((strlen(std::string("zlh42RT"))), (7));
    EXPECT_EQ((strlen(std::string("OsdDWU3I"))), (8));
    EXPECT_EQ((strlen(std::string("2abc"))), (4));
    EXPECT_EQ((strlen(std::string("FB8z"))), (4));
    EXPECT_EQ((strlen(std::string("XrzLeNAaU"))), (9));
}

TEST(Probe, strlen_02) {
    EXPECT_EQ((strlen(std::string("nUVvv4zAe"))), (9));
    EXPECT_EQ((strlen(std::string("B"))), (1));
    EXPECT_EQ((strlen(std::string("c"))), (1));
    EXPECT_EQ((strlen(std::string("2Ff"))), (3));
    EXPECT_EQ((strlen(std::string("aoc"))), (3));
    EXPECT_EQ((strlen(std::string(" x"))), (2));
    EXPECT_EQ((strlen(std::string("lz3M0lIfcK"))), (10));
    EXPECT_EQ((strlen(std::string("ap9A"))), (4));
    EXPECT_EQ((strlen(std::string("j9L9bxo"))), (7));
    EXPECT_EQ((strlen(std::string("o0H9piitvrQ"))), (11));
    EXPECT_EQ((strlen(std::string("2"))), (1));
    EXPECT_EQ((strlen(std::string("UggI5Q"))), (6));
    EXPECT_EQ((strlen(std::string("LasdasnakQj"))), (11));
    EXPECT_EQ((strlen(std::string("z9AvxLla"))), (8));
    EXPECT_EQ((strlen(std::string("7"))), (1));
    EXPECT_EQ((strlen(std::string("J"))), (1));
    EXPECT_EQ((strlen(std::string("GrZZYlw0fB T"))), (12));
    EXPECT_EQ((strlen(std::string("9rnLPcA4Tqax"))), (12));
    EXPECT_EQ((strlen(std::string("asda9akj"))), (8));
    EXPECT_EQ((strlen(std::string("q2"))), (2));
    EXPECT_EQ((strlen(std::string("asdaQsnakj"))), (10));
    EXPECT_EQ((strlen(std::string("Q"))), (1));
    EXPECT_EQ((strlen(std::string("lrqX"))), (4));
}

TEST(Probe, largest_divisor_01) {
    EXPECT_EQ((largest_divisor(15)), (5));
    EXPECT_EQ((largest_divisor(8)), (4));
    EXPECT_EQ((largest_divisor(14)), (7));
    EXPECT_EQ((largest_divisor(0)), (1));
    EXPECT_EQ((largest_divisor(-355)), (1));
    EXPECT_EQ((largest_divisor(21)), (7));
    EXPECT_EQ((largest_divisor(48)), (24));
    EXPECT_EQ((largest_divisor(422)), (211));
    EXPECT_EQ((largest_divisor(-5)), (1));
    EXPECT_EQ((largest_divisor(27)), (9));
    EXPECT_EQ((largest_divisor(-1)), (1));
    EXPECT_EQ((largest_divisor(4)), (2));
    EXPECT_EQ((largest_divisor(717)), (239));
    EXPECT_EQ((largest_divisor(-2)), (1));
    EXPECT_EQ((largest_divisor(-4)), (1));
    EXPECT_EQ((largest_divisor(30)), (15));
    EXPECT_EQ((largest_divisor(52)), (26));
    EXPECT_EQ((largest_divisor(23)), (1));
    EXPECT_EQ((largest_divisor(-9)), (1));
    EXPECT_EQ((largest_divisor(50)), (25));
    EXPECT_EQ((largest_divisor(10)), (5));
    EXPECT_EQ((largest_divisor(190)), (95));
    EXPECT_EQ((largest_divisor(-7)), (1));
    EXPECT_EQ((largest_divisor(12)), (6));
    EXPECT_EQ((largest_divisor(18)), (9));
}

TEST(Probe, largest_divisor_02) {
    EXPECT_EQ((largest_divisor(269)), (1));
    EXPECT_EQ((largest_divisor(5)), (1));
    EXPECT_EQ((largest_divisor(102)), (51));
    EXPECT_EQ((largest_divisor(6)), (3));
    EXPECT_EQ((largest_divisor(49)), (7));
    EXPECT_EQ((largest_divisor(-590)), (1));
    EXPECT_EQ((largest_divisor(20)), (10));
    EXPECT_EQ((largest_divisor(2)), (1));
    EXPECT_EQ((largest_divisor(-8)), (1));
    EXPECT_EQ((largest_divisor(-135)), (1));
    EXPECT_EQ((largest_divisor(-120)), (1));
    EXPECT_EQ((largest_divisor(919)), (1));
    EXPECT_EQ((largest_divisor(1000)), (500));
    EXPECT_EQ((largest_divisor(13)), (1));
    EXPECT_EQ((largest_divisor(28)), (14));
    EXPECT_EQ((largest_divisor(-3)), (1));
    EXPECT_EQ((largest_divisor(-102)), (1));
    EXPECT_EQ((largest_divisor(51)), (17));
    EXPECT_EQ((largest_divisor(-20)), (1));
    EXPECT_EQ((largest_divisor(99)), (33));
    EXPECT_EQ((largest_divisor(98)), (49));
    EXPECT_EQ((largest_divisor(-989)), (1));
    EXPECT_EQ((largest_divisor(-190)), (1));
}
