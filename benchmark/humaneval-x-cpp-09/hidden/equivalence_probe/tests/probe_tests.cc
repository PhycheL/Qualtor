// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_09.h"

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

TEST(Probe, circular_shift_01) {
    EXPECT_EQ((circular_shift(11, 19)), (std::string("11")));
    EXPECT_EQ((circular_shift(99, 21)), (std::string("99")));
    EXPECT_EQ((circular_shift(21, 99999)), (std::string("12")));
    EXPECT_EQ((circular_shift(97, 79)), (std::string("79")));
    EXPECT_EQ((circular_shift(-116, 100)), (std::string("611-")));
    EXPECT_EQ((circular_shift(-10, 3)), (std::string("-10")));
    EXPECT_EQ((circular_shift(21, -1)), (std::string("12")));
    EXPECT_EQ((circular_shift(671, -10)), (std::string("176")));
    EXPECT_EQ((circular_shift(428, 258)), (std::string("824")));
    EXPECT_EQ((circular_shift(20, 100)), (std::string("02")));
    EXPECT_EQ((circular_shift(24, -7)), (std::string("42")));
    EXPECT_EQ((circular_shift(97, -3)), (std::string("79")));
    EXPECT_EQ((circular_shift(22, 21)), (std::string("22")));
    EXPECT_EQ((circular_shift(9, 1)), (std::string("9")));
    EXPECT_EQ((circular_shift(-1, -5)), (std::string("1-")));
    EXPECT_EQ((circular_shift(-6, 1000)), (std::string("6-")));
    EXPECT_EQ((circular_shift(13, 101)), (std::string("31")));
    EXPECT_EQ((circular_shift(8, 19)), (std::string("8")));
    EXPECT_EQ((circular_shift(21, 100)), (std::string("12")));
    EXPECT_EQ((circular_shift(1, 23)), (std::string("1")));
    EXPECT_EQ((circular_shift(21, 101)), (std::string("12")));
    EXPECT_EQ((circular_shift(12, 28)), (std::string("21")));
    EXPECT_EQ((circular_shift(21, 2)), (std::string("21")));
    EXPECT_EQ((circular_shift(22, -7)), (std::string("22")));
    EXPECT_EQ((circular_shift(24, 97)), (std::string("42")));
}

TEST(Probe, circular_shift_02) {
    EXPECT_EQ((circular_shift(2, 12345)), (std::string("2")));
    EXPECT_EQ((circular_shift(199, 96)), (std::string("991")));
    EXPECT_EQ((circular_shift(2, 2)), (std::string("2")));
    EXPECT_EQ((circular_shift(820, 101)), (std::string("028")));
    EXPECT_EQ((circular_shift(21, 6)), (std::string("12")));
    EXPECT_EQ((circular_shift(1, 0)), (std::string("1")));
    EXPECT_EQ((circular_shift(27, 11)), (std::string("72")));
    EXPECT_EQ((circular_shift(4, 13)), (std::string("4")));
    EXPECT_EQ((circular_shift(17, 18)), (std::string("71")));
    EXPECT_EQ((circular_shift(21, 1)), (std::string("12")));
    EXPECT_EQ((circular_shift(0, 12)), (std::string("0")));
    EXPECT_EQ((circular_shift(300, 0)), (std::string("300")));
    EXPECT_EQ((circular_shift(16, 20)), (std::string("61")));
    EXPECT_EQ((circular_shift(12, -2)), (std::string("21")));
    EXPECT_EQ((circular_shift(0, 21)), (std::string("0")));
    EXPECT_EQ((circular_shift(-557, 13)), (std::string("755-")));
    EXPECT_EQ((circular_shift(1, 29)), (std::string("1")));
    EXPECT_EQ((circular_shift(12, 7)), (std::string("21")));
    EXPECT_EQ((circular_shift(11, 100)), (std::string("11")));
    EXPECT_EQ((circular_shift(15, 97)), (std::string("51")));
    EXPECT_EQ((circular_shift(97, -9)), (std::string("79")));
    EXPECT_EQ((circular_shift(1, 12)), (std::string("1")));
    EXPECT_EQ((circular_shift(98, 2)), (std::string("98")));
}

TEST(Probe, digitSum_01) {
    EXPECT_EQ((digitSum(std::string(" How are yOu\?"))), (151));
    EXPECT_EQ((digitSum(std::string("woAlz"))), (65));
    EXPECT_EQ((digitSum(std::string("aAaaaXa"))), (153));
    EXPECT_EQ((digitSum(std::string("woAPl"))), (145));
    EXPECT_EQ((digitSum(std::string("bDAiBG"))), (270));
    EXPECT_EQ((digitSum(std::string("g"))), (0));
    EXPECT_EQ((digitSum(std::string("Plchv6rv"))), (80));
    EXPECT_EQ((digitSum(std::string("You HrE Very Smoar3"))), (399));
    EXPECT_EQ((digitSum(std::string("UaZn35aXv2Zu"))), (353));
    EXPECT_EQ((digitSum(std::string(""))), (0));
    EXPECT_EQ((digitSum(std::string("TsvJv"))), (158));
    EXPECT_EQ((digitSum(std::string("1nbj"))), (0));
    EXPECT_EQ((digitSum(std::string("Pjp"))), (80));
    EXPECT_EQ((digitSum(std::string("woArBld"))), (131));
    EXPECT_EQ((digitSum(std::string(" Hon7are yOu\?"))), (151));
    EXPECT_EQ((digitSum(std::string("heplloE"))), (69));
    EXPECT_EQ((digitSum(std::string("abcCd"))), (67));
    EXPECT_EQ((digitSum(std::string("yXYznyo9ndr"))), (177));
    EXPECT_EQ((digitSum(std::string("Pv5fAjyH"))), (217));
    EXPECT_EQ((digitSum(std::string("1pvhXt"))), (88));
    EXPECT_EQ((digitSum(std::string(" Hw ar yvu\?"))), (72));
    EXPECT_EQ((digitSum(std::string("4oABl2d"))), (131));
    EXPECT_EQ((digitSum(std::string("NhAaaXa"))), (231));
    EXPECT_EQ((digitSum(std::string("Vou"))), (86));
    EXPECT_EQ((digitSum(std::string("You arE Very Smart"))), (327));
}

TEST(Probe, digitSum_02) {
    EXPECT_EQ((digitSum(std::string("YTou arE Very SRmtrt"))), (493));
    EXPECT_EQ((digitSum(std::string("hBeloE"))), (135));
    EXPECT_EQ((digitSum(std::string("W4hreBEhHD\?1"))), (362));
    EXPECT_EQ((digitSum(std::string("aYSbAWB"))), (390));
    EXPECT_EQ((digitSum(std::string("9pXsNBLd"))), (308));
    EXPECT_EQ((digitSum(std::string("XAaFXa"))), (311));
    EXPECT_EQ((digitSum(std::string("aVAB"))), (217));
    EXPECT_EQ((digitSum(std::string("woArBePd"))), (211));
    EXPECT_EQ((digitSum(std::string("FWmW"))), (244));
    EXPECT_EQ((digitSum(std::string("WL1S2 dm4o\?"))), (246));
    EXPECT_EQ((digitSum(std::string("nvMC"))), (144));
    EXPECT_EQ((digitSum(std::string("ChhRZ19"))), (239));
    EXPECT_EQ((digitSum(std::string("woArBd"))), (131));
    EXPECT_EQ((digitSum(std::string(" How are pOu\?"))), (151));
    EXPECT_EQ((digitSum(std::string("\?rNB0\?jmAr"))), (209));
    EXPECT_EQ((digitSum(std::string("L"))), (76));
    EXPECT_EQ((digitSum(std::string("v"))), (0));
    EXPECT_EQ((digitSum(std::string("X"))), (88));
    EXPECT_EQ((digitSum(std::string("ouTCdNy44g6"))), (229));
    EXPECT_EQ((digitSum(std::string("E2vhQwU"))), (235));
    EXPECT_EQ((digitSum(std::string("OnPNE1O9Lk8G"))), (532));
    EXPECT_EQ((digitSum(std::string(" How are SyOu\?"))), (234));
    EXPECT_EQ((digitSum(std::string("FNMAY5b0XHNe"))), (617));
}

TEST(Probe, fruit_distribution_01) {
    EXPECT_EQ((fruit_distribution(std::string("s42vrx"), 95)), (53));
    EXPECT_EQ((fruit_distribution(std::string("1 apples and 0 oranges"), 19)), (18));
    EXPECT_EQ((fruit_distribution(std::string("5 fzB5L"), 96)), (86));
    EXPECT_EQ((fruit_distribution(std::string("Zu"), 95)), (95));
    EXPECT_EQ((fruit_distribution(std::string("1 appTles andg 0 oraeges"), -10)), (-11));
    EXPECT_EQ((fruit_distribution(std::string("OQeuQBgm"), -8)), (-8));
    EXPECT_EQ((fruit_distribution(std::string("100 apples and 1 oranges"), -10)), (-111));
    EXPECT_EQ((fruit_distribution(std::string("W1 apVles and 100 orangvs"), 315)), (214));
    EXPECT_EQ((fruit_distribution(std::string("100 apples and 1 orjnges"), -5)), (-106));
    EXPECT_EQ((fruit_distribution(std::string("0 apples and 1 oranges"), 3)), (2));
    EXPECT_EQ((fruit_distribution(std::string("sQiyhu"), 0)), (0));
    EXPECT_EQ((fruit_distribution(std::string("w4RpkWZRusC"), 18)), (14));
    EXPECT_EQ((fruit_distribution(std::string("2 apples and 3 oranges"), 456)), (451));
    EXPECT_EQ((fruit_distribution(std::string("0 apples and 1 oranges"), 9)), (8));
    EXPECT_EQ((fruit_distribution(std::string("Kq"), -791)), (-791));
    EXPECT_EQ((fruit_distribution(std::string("100 apples and 1 oranges"), 2)), (-99));
    EXPECT_EQ((fruit_distribution(std::string("0 apples and 1 oranges"), 4)), (3));
    EXPECT_EQ((fruit_distribution(std::string("tl"), 1000)), (1000));
    EXPECT_EQ((fruit_distribution(std::string("5 applls nsand 6 oranges"), -710)), (-721));
    EXPECT_EQ((fruit_distribution(std::string("5 apples and 6 oranges"), 12345)), (12334));
    EXPECT_EQ((fruit_distribution(std::string("rvZ"), 5)), (5));
    EXPECT_EQ((fruit_distribution(std::string(" tQTsOQF"), -6)), (-6));
    EXPECT_EQ((fruit_distribution(std::string("5 apples and 6 oranges"), 3)), (-8));
    EXPECT_EQ((fruit_distribution(std::string("100 apples and 1 iranges"), 26)), (-75));
    EXPECT_EQ((fruit_distribution(std::string("cFOK"), 5)), (5));
}

TEST(Probe, fruit_distribution_02) {
    EXPECT_EQ((fruit_distribution(std::string("2 apples Uand 3 ora2es"), -7)), (-41));
    EXPECT_EQ((fruit_distribution(std::string("s7"), 0)), (-7));
    EXPECT_EQ((fruit_distribution(std::string("Q appWes knd 100 oranges"), 26)), (-74));
    EXPECT_EQ((fruit_distribution(std::string("5Gur"), 100)), (95));
    EXPECT_EQ((fruit_distribution(std::string("V2XAWI0d"), 16)), (14));
    EXPECT_EQ((fruit_distribution(std::string("1 appEles and 0soranges"), 0)), (-1));
    EXPECT_EQ((fruit_distribution(std::string("1 apples and 0 oranges"), 3)), (2));
    EXPECT_EQ((fruit_distribution(std::string("3GWFe60kWYdA"), 26)), (-37));
    EXPECT_EQ((fruit_distribution(std::string("E"), 4)), (4));
    EXPECT_EQ((fruit_distribution(std::string("5ewA4"), 7)), (-2));
    EXPECT_EQ((fruit_distribution(std::string("5 apples and 6 oranges"), 931)), (920));
    EXPECT_EQ((fruit_distribution(std::string("5 apples and 6 oranges"), 6)), (-5));
    EXPECT_EQ((fruit_distribution(std::string("2oiJHTLxw5"), 100)), (93));
    EXPECT_EQ((fruit_distribution(std::string("100 apple4 anDd 1 orang2es"), 100)), (-412));
    EXPECT_EQ((fruit_distribution(std::string("5 apples and 6 oranges"), 1)), (-10));
    EXPECT_EQ((fruit_distribution(std::string("1oL0xT"), 26)), (25));
    EXPECT_EQ((fruit_distribution(std::string("0 apples and 1 oranges"), 2)), (1));
    EXPECT_EQ((fruit_distribution(std::string("1 apples and 100 oranges"), 21)), (-80));
    EXPECT_EQ((fruit_distribution(std::string("1 apples and 100 oranges"), 10)), (-91));
    EXPECT_EQ((fruit_distribution(std::string("0 apples and 1 oranges"), 22)), (21));
    EXPECT_EQ((fruit_distribution(std::string("0 Papples and 1 oranges"), 2)), (1));
    EXPECT_EQ((fruit_distribution(std::string("10 applls axd 1 oranges"), 0)), (-11));
    EXPECT_EQ((fruit_distribution(std::string("1 apples n 100 ornges"), 19)), (-82));
}

TEST(Probe, pluck_01) {
    EXPECT_EQ((pluck(std::vector<int >{7, 6, 7, 1})), (std::vector<int >{6, 1}));
    EXPECT_EQ((pluck(std::vector<int >{-370, 760, 1, 173})), (std::vector<int >{-370, 0}));
    EXPECT_EQ((pluck(std::vector<int >{6, 1})), (std::vector<int >{6, 0}));
    EXPECT_EQ((pluck(std::vector<int >{1, 2, 3, 0, 5, 3})), (std::vector<int >{0, 3}));
    EXPECT_EQ((pluck(std::vector<int >{7, -4, 10, -591, 12})), (std::vector<int >{-4, 1}));
    EXPECT_EQ((pluck(std::vector<int >{5})), (std::vector<int >{}));
    EXPECT_EQ((pluck(std::vector<int >{6})), (std::vector<int >{6, 0}));
    EXPECT_EQ((pluck(std::vector<int >{1, 2, 3, 0, 3, 5})), (std::vector<int >{0, 3}));
    EXPECT_EQ((pluck(std::vector<int >{2, 0, 3, 0, 4, 5})), (std::vector<int >{0, 1}));
    EXPECT_EQ((pluck(std::vector<int >{-919, 2})), (std::vector<int >{2, 1}));
    EXPECT_EQ((pluck(std::vector<int >{13, 6, -9, 4, 146, 14, 1, 100})), (std::vector<int >{4, 3}));
    EXPECT_EQ((pluck(std::vector<int >{-1})), (std::vector<int >{}));
    EXPECT_EQ((pluck(std::vector<int >{5, 4, 10000, 4, 8})), (std::vector<int >{4, 1}));
    EXPECT_EQ((pluck(std::vector<int >{6, -1, 4, 346, 370, -9})), (std::vector<int >{4, 2}));
    EXPECT_EQ((pluck(std::vector<int >{9998, 1, 235})), (std::vector<int >{9998, 0}));
    EXPECT_EQ((pluck(std::vector<int >{7, 9, 7, 1, -2})), (std::vector<int >{-2, 4}));
    EXPECT_EQ((pluck(std::vector<int >{6, 1, 22})), (std::vector<int >{6, 0}));
    EXPECT_EQ((pluck(std::vector<int >{2, 1})), (std::vector<int >{2, 0}));
    EXPECT_EQ((pluck(std::vector<int >{-670, 7, 10000, 2})), (std::vector<int >{-670, 0}));
    EXPECT_EQ((pluck(std::vector<int >{7, 10, 7, 1})), (std::vector<int >{10, 1}));
    EXPECT_EQ((pluck(std::vector<int >{0, 1, -1})), (std::vector<int >{0, 0}));
    EXPECT_EQ((pluck(std::vector<int >{1, 2, 3})), (std::vector<int >{2, 1}));
    EXPECT_EQ((pluck(std::vector<int >{7, 6, 7, 1, 751})), (std::vector<int >{6, 1}));
    EXPECT_EQ((pluck(std::vector<int >{0, -179, -6, 802})), (std::vector<int >{-6, 2}));
    EXPECT_EQ((pluck(std::vector<int >{23, -77, 3, 9999, 2, 456, 25, 3})), (std::vector<int >{2, 4}));
}

TEST(Probe, pluck_02) {
    EXPECT_EQ((pluck(std::vector<int >{4})), (std::vector<int >{4, 0}));
    EXPECT_EQ((pluck(std::vector<int >{1, 2, 3, 8})), (std::vector<int >{2, 1}));
    EXPECT_EQ((pluck(std::vector<int >{10000, 1, 99999, -1, 8, -5, 1000, 0})), (std::vector<int >{0, 7}));
    EXPECT_EQ((pluck(std::vector<int >{2, 3})), (std::vector<int >{2, 0}));
    EXPECT_EQ((pluck(std::vector<int >{11, -5, -4, 0, -1})), (std::vector<int >{-4, 2}));
    EXPECT_EQ((pluck(std::vector<int >{10000, 895, 6, -8, -5, 1})), (std::vector<int >{-8, 3}));
    EXPECT_EQ((pluck(std::vector<int >{8, 3, 96, 99999, 812, -857})), (std::vector<int >{8, 0}));
    EXPECT_EQ((pluck(std::vector<int >{4, 4, 190})), (std::vector<int >{4, 0}));
    EXPECT_EQ((pluck(std::vector<int >{-9, 6, 2})), (std::vector<int >{2, 2}));
    EXPECT_EQ((pluck(std::vector<int >{2, 443, 9, -9, -1, -1})), (std::vector<int >{2, 0}));
    EXPECT_EQ((pluck(std::vector<int >{3, -846})), (std::vector<int >{-846, 1}));
    EXPECT_EQ((pluck(std::vector<int >{-427, 1})), (std::vector<int >{}));
    EXPECT_EQ((pluck(std::vector<int >{10, 5})), (std::vector<int >{10, 0}));
    EXPECT_EQ((pluck(std::vector<int >{2})), (std::vector<int >{2, 0}));
    EXPECT_EQ((pluck(std::vector<int >{8, 14, 9998, 5, 7, 7})), (std::vector<int >{8, 0}));
    EXPECT_EQ((pluck(std::vector<int >{3, 2, 1})), (std::vector<int >{2, 1}));
    EXPECT_EQ((pluck(std::vector<int >{1, 2, 3, 0, 5, 3, 455})), (std::vector<int >{0, 3}));
    EXPECT_EQ((pluck(std::vector<int >{-835, 24, 5, -628, 1, 8})), (std::vector<int >{-628, 3}));
    EXPECT_EQ((pluck(std::vector<int >{0})), (std::vector<int >{0, 0}));
    EXPECT_EQ((pluck(std::vector<int >{0, 7, -653})), (std::vector<int >{0, 0}));
    EXPECT_EQ((pluck(std::vector<int >{2, 0, 3, 0, 4, 2})), (std::vector<int >{0, 1}));
    EXPECT_EQ((pluck(std::vector<int >{2, 19, 1, 4})), (std::vector<int >{2, 0}));
    EXPECT_EQ((pluck(std::vector<int >{7, 7, 1})), (std::vector<int >{}));
}

TEST(Probe, search_01) {
    EXPECT_EQ((search(std::vector<int >{1, 6, 10, 1, 6, 9, 10, 8, 6, 8, 7, 3, 28})), (1));
    EXPECT_EQ((search(std::vector<int >{10})), (-1));
    EXPECT_EQ((search(std::vector<int >{2, 3, 3, 2, 2})), (2));
    EXPECT_EQ((search(std::vector<int >{8, 8, 3, 6, 5, 6, 4})), (-1));
    EXPECT_EQ((search(std::vector<int >{3, 6, 10, 1, 6, 9, 10, 8, 6, 8, 7, 1})), (1));
    EXPECT_EQ((search(std::vector<int >{9, 2, 4, 1, 5, 1, 5, 2, 5, 7, 7, 7, 3, 10, 1, 5, 4, 2, 8, 4, 1, 9, 10, 7, 10, 2, 8, 10, 9, 4})), (4));
    EXPECT_EQ((search(std::vector<int >{3, 3})), (-1));
    EXPECT_EQ((search(std::vector<int >{13, 2, 8})), (-1));
    EXPECT_EQ((search(std::vector<int >{2, 7, 8, 8, 4, 8, 7, 3, 9, 6, 5, 10, 4, 3, 6, 7, 1, 7, 4, 10, 8, 1, 0})), (1));
    EXPECT_EQ((search(std::vector<int >{2, 10, 4, 8, 2, 10, 5, 1, 2, 9, 5, 5, 6, 3, 8, 6, 4, 10, 19})), (2));
    EXPECT_EQ((search(std::vector<int >{8, 8, 8, 8, 8, 8, 8, 8})), (8));
    EXPECT_EQ((search(std::vector<int >{5, 5, 3, 9, 5, 6, 3, 2, 8, 5, 6, 10, 10, 6, 8, 4, 10, 7, 7, 10, 8})), (-1));
    EXPECT_EQ((search(std::vector<int >{10, 9, -3, 8})), (-1));
    EXPECT_EQ((search(std::vector<int >{9, 8, 6, 10, 2, 6, 10, 2, 7, 8, 10, 3, 8, 2, 6, 2, 3, 1})), (2));
    EXPECT_EQ((search(std::vector<int >{6, 7, 1, 8, 8, 10, 5, 8, 5, 3, 10})), (1));
    EXPECT_EQ((search(std::vector<int >{6, 9, 6, 7, 1, 4, 7, 1, 8, 8, 9, 8, 10, 10, 8, 4, 10, 4, 10, 1, 2, 9, 5, 7, 9})), (1));
    EXPECT_EQ((search(std::vector<int >{1, 2, 2, 3, 3, 3, 4, 4, 4})), (3));
    EXPECT_EQ((search(std::vector<int >{6, 9, 6, 28, 1, 4, 7, 1, 8, 8, 9, 8, 10, 10, 8, 4, 10, 4, 10, 1, 2, 9, 5, 7, 9})), (1));
    EXPECT_EQ((search(std::vector<int >{3, 10, 10, 9, 2, 9})), (-1));
    EXPECT_EQ((search(std::vector<int >{2, 10, 4, 8, 2, 10, 5, 1, 2, 9, -1, 5, 6, 3, 8, 6, 4, 10})), (2));
    EXPECT_EQ((search(std::vector<int >{4, 1, 4, 1, 4, 4})), (4));
    EXPECT_EQ((search(std::vector<int >{-653, 2, 2, 11, 30, -8, 7})), (2));
    EXPECT_EQ((search(std::vector<int >{6, 9, 7, 5, 8, 7, 5, 3, 7, 5, 10, 10, 3, 6, 10, 2, 8, 6, 5, 4, 9, 5, 3, 10})), (5));
    EXPECT_EQ((search(std::vector<int >{5, 5, 4, 4, 4, 9})), (-1));
    EXPECT_EQ((search(std::vector<int >{-6, 14, 635, 12, 168, 9})), (-1));
}

TEST(Probe, search_02) {
    EXPECT_EQ((search(std::vector<int >{880, 30, 2})), (-1));
    EXPECT_EQ((search(std::vector<int >{9, 7, 7, 2, 4, 7, 2, 10, 9, 7, 5, 7, 2})), (2));
    EXPECT_EQ((search(std::vector<int >{4, 11, -35})), (-1));
    EXPECT_EQ((search(std::vector<int >{2, 10, 4, 8, 2, 10, 5, 1, 2, 9, 5, 5, 6, 3, 8, 6, 4, 10})), (2));
    EXPECT_EQ((search(std::vector<int >{10, 23, -808, 3, -9, 592, -313})), (-1));
    EXPECT_EQ((search(std::vector<int >{8, 8, 10, 6, 4, 3, 5, 8, 2, 4, 2, 8, 4, 6, 10, 4, 2, 1, 10, 2, 1, 1, 5})), (4));
    EXPECT_EQ((search(std::vector<int >{29, 559, 2, 813, 19, 3, 6})), (-1));
    EXPECT_EQ((search(std::vector<int >{9, 7, 5, 8, 7, 5, 3, 7, 5, 10, 10, 3, 6, 10, 2, 8, 6, 5, 4, 9, 5, 3, 10})), (5));
    EXPECT_EQ((search(std::vector<int >{5, 5, 3, 9, 5, 6, 3, 2, 8, 5, -1, 10, 10, 6, 8, 4, 10, 7, 7, 10, 8})), (-1));
    EXPECT_EQ((search(std::vector<int >{7, 9, 9, 9, 3, 4, 1, 7, 9, 1, 2, 1, 1, 10, 7, 5, 6, 5, 6, 7, 7, 6})), (1));
    EXPECT_EQ((search(std::vector<int >{3})), (-1));
    EXPECT_EQ((search(std::vector<int >{8, 8, 3, 6, 5, 6, 4, 3})), (-1));
    EXPECT_EQ((search(std::vector<int >{1, 6, -2, 21, 2, 8, 287})), (1));
    EXPECT_EQ((search(std::vector<int >{6, 9, 7, 5, 8, 7, 6, 3, 7, 5, 10, 10, 3, 5, 10, 2, 8, 6, 5, 4, 9, 5, 3, 10})), (5));
    EXPECT_EQ((search(std::vector<int >{6})), (-1));
    EXPECT_EQ((search(std::vector<int >{5, 5, 5, 5, 1})), (1));
    EXPECT_EQ((search(std::vector<int >{5, 5, 4, 4, 4})), (-1));
    EXPECT_EQ((search(std::vector<int >{3, 10, 9, 2})), (-1));
    EXPECT_EQ((search(std::vector<int >{7, 28})), (-1));
    EXPECT_EQ((search(std::vector<int >{3, 7, 19, -4, 850, -810, 3})), (-1));
    EXPECT_EQ((search(std::vector<int >{2, 6, 4, 2, 8, 7, 5, 6, 4, 10, 4, 6, 3, 8, 8, 3, 1, 4, 2, 2, 10, 7})), (4));
    EXPECT_EQ((search(std::vector<int >{2, 6, 4, 2, 8, 7, 5, 4, 10, 4, 6, 3, 7, 8, 8, 3, 1, 4, 2, 2, 10, 7})), (4));
    EXPECT_EQ((search(std::vector<int >{12, 2, 5})), (-1));
}

TEST(Probe, strange_sort_list_01) {
    EXPECT_EQ((strange_sort_list(std::vector<int >{6})), (std::vector<int >{6}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{2, 20})), (std::vector<int >{2, 20}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{-3, 9, 3})), (std::vector<int >{-3, 9, 3}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{0, 2, 2, 2, 5, 5, -5, -5, 6})), (std::vector<int >{-5, 6, -5, 5, 0, 5, 2, 2, 2}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{111111})), (std::vector<int >{111111}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 6, 7, 7, 9, 1})), (std::vector<int >{1, 9, 5, 7, 6, 7}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 5, 2, 4, 3, 3})), (std::vector<int >{1, 5, 2, 4, 3, 3}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{8, -626, -5, 254, 11, 206, -356})), (std::vector<int >{-626, 254, -356, 206, -5, 11, 8}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 5, 5, 4})), (std::vector<int >{4, 5, 5, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 4, 2, 3})), (std::vector<int >{1, 4, 2, 3}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 2, 4, 3})), (std::vector<int >{1, 4, 2, 3}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 5, 2, 4, 3})), (std::vector<int >{1, 5, 2, 4, 3}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{-5, 5, -5, 5, 0, 2, 2, 2})), (std::vector<int >{-5, 5, -5, 5, 0, 2, 2, 2}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 2, 3, 4, 5, 6, 7, 8, 8})), (std::vector<int >{1, 8, 2, 8, 3, 7, 4, 6, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{0})), (std::vector<int >{0}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{15, 669, -5, 5, 2, 4})), (std::vector<int >{-5, 669, 2, 15, 4, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 2, 3, 4, 5, 6, 7, 8})), (std::vector<int >{1, 8, 2, 7, 3, 6, 4, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{315, 9, 6, 8, 7})), (std::vector<int >{6, 315, 7, 9, 8}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{111111, 832, 6, 3, -817, 7})), (std::vector<int >{-817, 111111, 3, 832, 6, 7}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 7, 14, 5, 7, 915})), (std::vector<int >{1, 915, 5, 14, 7, 7}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 15, 7, 17, -548, 26, 12, 27})), (std::vector<int >{-548, 27, 1, 26, 7, 17, 12, 15}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 8, 2, 7, 3, 6, 4, 5})), (std::vector<int >{1, 8, 2, 7, 3, 6, 4, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{12345, 7})), (std::vector<int >{7, 12345}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{-3, 5, 2, 7, 6, 0, 265})), (std::vector<int >{-3, 265, 0, 7, 2, 6, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{4, 2, 3, 1})), (std::vector<int >{1, 4, 2, 3}));
}

TEST(Probe, strange_sort_list_02) {
    EXPECT_EQ((strange_sort_list(std::vector<int >{9, 14, 691})), (std::vector<int >{9, 691, 14}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{2, 0, 572, 6, 1, 28, 3, 920})), (std::vector<int >{0, 920, 1, 572, 2, 28, 3, 6}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 4, 5, 5})), (std::vector<int >{4, 5, 5, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{9, 111109})), (std::vector<int >{9, 111109}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 6, 7, 8, 9, 1})), (std::vector<int >{1, 9, 5, 8, 6, 7}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 5, 5})), (std::vector<int >{5, 5, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 4, 26, 3})), (std::vector<int >{1, 26, 3, 4}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{16, 4, 6})), (std::vector<int >{4, 16, 6}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{-5, 598, 12345, 19, 637})), (std::vector<int >{-5, 12345, 19, 637, 598}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{520, 2, 3, 3})), (std::vector<int >{2, 520, 3, 3}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{-8, 21, 228, 3})), (std::vector<int >{-8, 228, 3, 21}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{-5, 12345, 6, -3, 20, 5, 6, 1})), (std::vector<int >{-5, 12345, -3, 20, 1, 6, 5, 6}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{-2, 5, 5})), (std::vector<int >{-2, 5, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{7, 4, 2, 3})), (std::vector<int >{2, 7, 3, 4}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{-5, -5, 5, 5, 0, 2, 2, 2})), (std::vector<int >{-5, 5, -5, 5, 0, 2, 2, 2}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{30, 14, 25, -1, 5})), (std::vector<int >{-1, 30, 5, 25, 14}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{16, 4, -8, 6, 410, 111111, 1, 9})), (std::vector<int >{-8, 111111, 1, 410, 4, 16, 6, 9}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 684, 5, 5})), (std::vector<int >{5, 684, 5, 5}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 2, 4, 3})), (std::vector<int >{2, 5, 3, 4}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{5, 4, 2, 3})), (std::vector<int >{2, 5, 3, 4}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 9, 5, 8, 6, 7})), (std::vector<int >{1, 9, 5, 8, 6, 7}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{0, 2, 2, 2, 5, 5, -5, -5})), (std::vector<int >{-5, 5, -5, 5, 0, 2, 2, 2}));
    EXPECT_EQ((strange_sort_list(std::vector<int >{1, 2, 3, 4, 5, 4})), (std::vector<int >{1, 5, 2, 4, 3, 4}));
}

TEST(Probe, triangle_area_01) {
    ExpectNearScalar(triangle_area(16.25f, 6.0f, 4.65999985f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(4.51999998f, -6.69999981f, 3.0f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(1.83000004f, 17.7999992f, 8.0f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-14.3999996f, 0.209999993f, 19.5f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-7.5999999f, 3.0f, -2.1099999f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(6.0f, -8.18000031f, -9.19999981f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(15.0f, 16.25f, -8.18000031f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(2.0f, 2.4000001f, 7.53999996f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(2.30999994f, 7.0f, -1.73000002f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(1.0f, 1.37f, -9.97999954f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(11.8000002f, 6.0f, -8.57999992f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(6.0f, 6.0f, 0.300000012f), 0.899719298f, 1e-5);
    ExpectNearScalar(triangle_area(16.0f, -8.18000031f, 18.0499992f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-9.18000031f, 13.1000004f, 6.0f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(13.5f, -2.4000001f, -8.27999973f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(17.1499996f, -8.30000019f, -7.5f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-0.300000012f, 6.80000019f, -0.430000007f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(1.70000005f, -16.7000008f, 4.4000001f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(0.00999999978f, -0.629999995f, -4.5f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(4.5f, 1.00999999f, 6.0f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(10.3000002f, -1.23000002f, 1.0f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(6.0f, 10.3999996f, -2.9000001f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-12.3999996f, 3.00999999f, 16.2999992f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(8.35999966f, -3.9000001f, 16.1000004f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-6.0f, -4.5999999f, 16.25f), -1.0f, 1e-5);
}

TEST(Probe, triangle_area_02) {
    ExpectNearScalar(triangle_area(-9.38000011f, 16.25f, 8.30000019f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(16.25f, -1.99000001f, -1.33000004f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(2.21000004f, -9.60999966f, -0.0199999996f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(19.6000004f, 0.270000011f, -11.8999996f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-1.33000004f, 8.0f, 0.00999999978f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(7.5999999f, -0.430000007f, -1.0f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(7.0f, 10.0f, -8.18000031f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(2.0f, -10.6999998f, 6.5f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-0.629999995f, 18.2000008f, -19.7999992f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(8.5f, 4.0f, -0.430000007f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(14.3000002f, 17.7999992f, 1.29999995f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-3.70000005f, 5.0f, 0.720000029f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-1.73000002f, -1.73000002f, -2.43000007f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(6.0f, 16.25f, 17.1499996f), 48.7273941f, 1e-5);
    ExpectNearScalar(triangle_area(0.910000026f, 18.5f, -13.1000004f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(1.0f, 16.25f, 1.48000002f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(9.60000038f, 4.5f, -0.289999992f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(17.3500004f, 6.0f, 7.67999983f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-0.430000007f, -1.0f, 19.0f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-1.73000002f, 6.0f, 13.8999996f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(-2.23000002f, -6.0f, 12.5f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(3.0f, 14.8999996f, 0.469999999f), -1.0f, 1e-5);
    ExpectNearScalar(triangle_area(7.0f, -1.0f, 12.1000004f), -1.0f, 1e-5);
}

TEST(Probe, will_it_fly_01) {
    EXPECT_EQ((will_it_fly(std::vector<int >{-7, 3, 12, 18, 7, -4, 269, 7}, 18)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 2, 3}, 5)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3}, 2)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{-4, 0, 5, 6, 4, 3}, -590)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 0, 3}, 12)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{4, -355, -1, 8, 9}, 0)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 0, 6, 7, 1, 4, 6, 6}, 1)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2}, 679)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2, 6}, 3)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{5}, 1)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2, 3}, 12)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{-771, 1, 6, 27, 20, 2, 2, 7}, 0)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{2, 919, 1000, 1}, 15)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 2, 3}, 2)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{2}, 5)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{}, 30)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 9, 11, 13, -5, 9}, 10)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{13, 2}, 24)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2, 3}, -444)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 2, 3}, 3)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 3, 3}, -483)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 2, -5}, 881)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{2}, 14)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{2, 2, 4}, 2)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2}, 11)), (false));
}

TEST(Probe, will_it_fly_02) {
    EXPECT_EQ((will_it_fly(std::vector<int >{2}, -389)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1}, 23)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 0}, 22)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 419, 3}, 2)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 3}, 29)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{3}, 17)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2, 3}, 2)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2, 3}, -958)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{9, 5, -1, 6, 11, 1, 2, 3}, 6)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{20, -496}, -593)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2, 3}, 0)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{5}, 14)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 5}, 23)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{5}, 10)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{1}, 3)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 2, 3}, 169)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{5}, 302)), (true));
    EXPECT_EQ((will_it_fly(std::vector<int >{27, -7, 14, 5}, 20)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{-4}, -461)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{1, 2, 3, 28}, 26)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{3, 2, 3}, 1)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{13, 7, 6}, 2)), (false));
    EXPECT_EQ((will_it_fly(std::vector<int >{379, 0, 687, 27, 1, 26, 26}, -5)), (false));
}
