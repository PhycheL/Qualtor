// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_06.h"

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

TEST(Probe, car_race_collision_01) {
    EXPECT_EQ((car_race_collision(7)), (49));
    EXPECT_EQ((car_race_collision(27)), (729));
    EXPECT_EQ((car_race_collision(19)), (361));
    EXPECT_EQ((car_race_collision(3)), (9));
    EXPECT_EQ((car_race_collision(16)), (256));
    EXPECT_EQ((car_race_collision(21)), (441));
    EXPECT_EQ((car_race_collision(9)), (81));
    EXPECT_EQ((car_race_collision(64)), (4096));
    EXPECT_EQ((car_race_collision(-116)), (13456));
    EXPECT_EQ((car_race_collision(10)), (100));
    EXPECT_EQ((car_race_collision(-10)), (100));
    EXPECT_EQ((car_race_collision(101)), (10201));
    EXPECT_EQ((car_race_collision(671)), (450241));
    EXPECT_EQ((car_race_collision(428)), (183184));
    EXPECT_EQ((car_race_collision(258)), (66564));
    EXPECT_EQ((car_race_collision(20)), (400));
    EXPECT_EQ((car_race_collision(24)), (576));
    EXPECT_EQ((car_race_collision(-7)), (49));
    EXPECT_EQ((car_race_collision(-3)), (9));
    EXPECT_EQ((car_race_collision(11)), (121));
    EXPECT_EQ((car_race_collision(-5)), (25));
    EXPECT_EQ((car_race_collision(-6)), (36));
    EXPECT_EQ((car_race_collision(1000)), (1000000));
    EXPECT_EQ((car_race_collision(13)), (169));
    EXPECT_EQ((car_race_collision(1)), (1));
}

TEST(Probe, car_race_collision_02) {
    EXPECT_EQ((car_race_collision(22)), (484));
    EXPECT_EQ((car_race_collision(12345)), (152399025));
    EXPECT_EQ((car_race_collision(199)), (39601));
    EXPECT_EQ((car_race_collision(820)), (672400));
    EXPECT_EQ((car_race_collision(6)), (36));
    EXPECT_EQ((car_race_collision(63)), (3969));
    EXPECT_EQ((car_race_collision(17)), (289));
    EXPECT_EQ((car_race_collision(18)), (324));
    EXPECT_EQ((car_race_collision(0)), (0));
    EXPECT_EQ((car_race_collision(300)), (90000));
    EXPECT_EQ((car_race_collision(12)), (144));
    EXPECT_EQ((car_race_collision(-2)), (4));
    EXPECT_EQ((car_race_collision(-557)), (310249));
    EXPECT_EQ((car_race_collision(15)), (225));
    EXPECT_EQ((car_race_collision(-9)), (81));
    EXPECT_EQ((car_race_collision(65)), (4225));
    EXPECT_EQ((car_race_collision(-777)), (603729));
    EXPECT_EQ((car_race_collision(14)), (196));
    EXPECT_EQ((car_race_collision(-8)), (64));
    EXPECT_EQ((car_race_collision(895)), (801025));
    EXPECT_EQ((car_race_collision(801)), (641601));
    EXPECT_EQ((car_race_collision(62)), (3844));
    EXPECT_EQ((car_race_collision(-508)), (258064));
}

TEST(Probe, incr_list_01) {
    EXPECT_EQ((incr_list(std::vector<int >{123})), (std::vector<int >{124}));
    EXPECT_EQ((incr_list(std::vector<int >{3, 2})), (std::vector<int >{4, 3}));
    EXPECT_EQ((incr_list(std::vector<int >{190, 533, -5, 12, 25, 17, 3})), (std::vector<int >{191, 534, -4, 13, 26, 18, 4}));
    EXPECT_EQ((incr_list(std::vector<int >{10, 126, 2})), (std::vector<int >{11, 127, 3}));
    EXPECT_EQ((incr_list(std::vector<int >{4, 3, 2})), (std::vector<int >{5, 4, 3}));
    EXPECT_EQ((incr_list(std::vector<int >{4})), (std::vector<int >{5}));
    EXPECT_EQ((incr_list(std::vector<int >{6, 4, 6, 3, 4, 10, 1, 124})), (std::vector<int >{7, 5, 7, 4, 5, 11, 2, 125}));
    EXPECT_EQ((incr_list(std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((incr_list(std::vector<int >{6, -5, 29, -990})), (std::vector<int >{7, -4, 30, -989}));
    EXPECT_EQ((incr_list(std::vector<int >{3, 489, 1})), (std::vector<int >{4, 490, 2}));
    EXPECT_EQ((incr_list(std::vector<int >{469, 4, 21})), (std::vector<int >{470, 5, 22}));
    EXPECT_EQ((incr_list(std::vector<int >{846, 2, 12, 274, 235})), (std::vector<int >{847, 3, 13, 275, 236}));
    EXPECT_EQ((incr_list(std::vector<int >{-835, 543, 10, 30})), (std::vector<int >{-834, 544, 11, 31}));
    EXPECT_EQ((incr_list(std::vector<int >{5, 2, 5, 2, 3, -573, 9, 0, 123})), (std::vector<int >{6, 3, 6, 3, 4, -572, 10, 1, 124}));
    EXPECT_EQ((incr_list(std::vector<int >{6, 4, 10, 3, 4, 4, 6, 1, 124})), (std::vector<int >{7, 5, 11, 4, 5, 5, 7, 2, 125}));
    EXPECT_EQ((incr_list(std::vector<int >{6, 4, 6, 3, 4, 4, 10, 1, 124, -465})), (std::vector<int >{7, 5, 7, 4, 5, 5, 11, 2, 125, -464}));
    EXPECT_EQ((incr_list(std::vector<int >{6, 3, 6, 3, 4, 4, 10, 1, 124})), (std::vector<int >{7, 4, 7, 4, 5, 5, 11, 2, 125}));
    EXPECT_EQ((incr_list(std::vector<int >{-104, -779})), (std::vector<int >{-103, -778}));
    EXPECT_EQ((incr_list(std::vector<int >{3, 2, 1})), (std::vector<int >{4, 3, 2}));
    EXPECT_EQ((incr_list(std::vector<int >{3, -739, 29, 26, 0})), (std::vector<int >{4, -738, 30, 27, 1}));
    EXPECT_EQ((incr_list(std::vector<int >{2, 3})), (std::vector<int >{3, 4}));
    EXPECT_EQ((incr_list(std::vector<int >{4, 126, -7, 3, 123, 5, 26})), (std::vector<int >{5, 127, -6, 4, 124, 6, 27}));
    EXPECT_EQ((incr_list(std::vector<int >{610})), (std::vector<int >{611}));
    EXPECT_EQ((incr_list(std::vector<int >{3, 124, 1})), (std::vector<int >{4, 125, 2}));
    EXPECT_EQ((incr_list(std::vector<int >{1, 2, 3, -3})), (std::vector<int >{2, 3, 4, -2}));
}

TEST(Probe, incr_list_02) {
    EXPECT_EQ((incr_list(std::vector<int >{5, 2, 5, 2, 3, 3, 9, 0, 123})), (std::vector<int >{6, 3, 6, 3, 4, 4, 10, 1, 124}));
    EXPECT_EQ((incr_list(std::vector<int >{2, 9, 4})), (std::vector<int >{3, 10, 5}));
    EXPECT_EQ((incr_list(std::vector<int >{20, 4, 9, 9, 5})), (std::vector<int >{21, 5, 10, 10, 6}));
    EXPECT_EQ((incr_list(std::vector<int >{2, 3, 4})), (std::vector<int >{3, 4, 5}));
    EXPECT_EQ((incr_list(std::vector<int >{26})), (std::vector<int >{27}));
    EXPECT_EQ((incr_list(std::vector<int >{2, 109, 4})), (std::vector<int >{3, 110, 5}));
    EXPECT_EQ((incr_list(std::vector<int >{123, 5})), (std::vector<int >{124, 6}));
    EXPECT_EQ((incr_list(std::vector<int >{1})), (std::vector<int >{2}));
    EXPECT_EQ((incr_list(std::vector<int >{2, 3, 4, 25})), (std::vector<int >{3, 4, 5, 26}));
    EXPECT_EQ((incr_list(std::vector<int >{6, 4, 6, 3, 4, 4, 10, 124})), (std::vector<int >{7, 5, 7, 4, 5, 5, 11, 125}));
    EXPECT_EQ((incr_list(std::vector<int >{604, 3, 5, 2, 3, 3, 9, 0, 123})), (std::vector<int >{605, 4, 6, 3, 4, 4, 10, 1, 124}));
    EXPECT_EQ((incr_list(std::vector<int >{2, 3, 0})), (std::vector<int >{3, 4, 1}));
    EXPECT_EQ((incr_list(std::vector<int >{4, 22, 2})), (std::vector<int >{5, 23, 3}));
    EXPECT_EQ((incr_list(std::vector<int >{4, 6, 3, 4, 4, 10, 1, 124})), (std::vector<int >{5, 7, 4, 5, 5, 11, 2, 125}));
    EXPECT_EQ((incr_list(std::vector<int >{6, 3, 6, 3, 4, 4, 10, 1, 124, 27})), (std::vector<int >{7, 4, 7, 4, 5, 5, 11, 2, 125, 28}));
    EXPECT_EQ((incr_list(std::vector<int >{-571, 0, 4, 0, 11, -1})), (std::vector<int >{-570, 1, 5, 1, 12, 0}));
    EXPECT_EQ((incr_list(std::vector<int >{6, 4, 6, 3, 4, 4, 10, 1, 124})), (std::vector<int >{7, 5, 7, 4, 5, 5, 11, 2, 125}));
    EXPECT_EQ((incr_list(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 0, 123})), (std::vector<int >{6, 4, 6, 3, 4, 4, 10, 1, 124}));
    EXPECT_EQ((incr_list(std::vector<int >{495, 189, 2})), (std::vector<int >{496, 190, 3}));
    EXPECT_EQ((incr_list(std::vector<int >{5, 3, 5, 2, 3, 3, 9, 0, 123, 17})), (std::vector<int >{6, 4, 6, 3, 4, 4, 10, 1, 124, 18}));
    EXPECT_EQ((incr_list(std::vector<int >{22, 5, -5})), (std::vector<int >{23, 6, -4}));
    EXPECT_EQ((incr_list(std::vector<int >{6, 3, 6, 3, 4, 4, 10, 1, 124, 644})), (std::vector<int >{7, 4, 7, 4, 5, 5, 11, 2, 125, 645}));
    EXPECT_EQ((incr_list(std::vector<int >{27, -1, 0, -617, -2, 124, 9})), (std::vector<int >{28, 0, 1, -616, -1, 125, 10}));
}

TEST(Probe, pairs_sum_to_zero_01) {
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 4, 2, 31})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 3, -2, 1})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{30, -10, -9, 23})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 3, -2, 1, -356})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 3, 31})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 3, 2, 31, 3})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{24})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{14, 4, 30, 842})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{2, 4, -5, 3, 5, 30})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{24, 18})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{2, 4, -5, 3, 5, 7})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{2, 4, -5, 5, 7})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 5, 3, 7})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 3, 5, 0, 0})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 3, 5, 0, -251})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{18})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 4, 12, -791})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, -1, 4, 2, 31})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{18, 10, 3, 2, 29})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-10, 2, 3, 7})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 4, 2, 31, -899})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{7, 22, 0, 3, 31})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 3, 5, 0, -976})), (false));
}

TEST(Probe, pairs_sum_to_zero_02) {
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{26})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-4, 5, 352, 30})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, 30, 4, 2, -1})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-1, 3, 5, 0})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{4, -5, 3, 5, 7})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{0, -146, 20})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 3, 2, 31, 2})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, 4, 2, 31, 11})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 2, 3, 7, 5})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 3, 5, 0, 5})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 3, 5, 0})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{2, 4, -5, 5, 3, 7})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 9, -1, -6, 2, 30})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-654, -1, 8, 33})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{204, 2})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{7, 15, -674, 226, -381, 26, 4})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-260, -5, 8, 21})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{2, 4, -5, 3, 7})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{-3, 1, -1, 3, 2, 31})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{10, 189, 27, 26, -4, 5, -5, 4})), (true));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{8, 121, 386, -3, 15})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 2, 3, 7, -5})), (false));
    EXPECT_EQ((pairs_sum_to_zero(std::vector<int >{1, 9})), (false));
}

TEST(Probe, change_base_01) {
    EXPECT_EQ((change_base(-406, 111)), (std::string("")));
    EXPECT_EQ((change_base(173, 101)), (std::string("172")));
    EXPECT_EQ((change_base(7, -255)), (std::string("7")));
    EXPECT_EQ((change_base(11101010, 11)), (std::string("62102398")));
    EXPECT_EQ((change_base(-591, 12)), (std::string("")));
    EXPECT_EQ((change_base(5, -778)), (std::string("5")));
    EXPECT_EQ((change_base(3, 11101008)), (std::string("3")));
    EXPECT_EQ((change_base(-1, 1)), (std::string("")));
    EXPECT_EQ((change_base(614, 3)), (std::string("211202")));
    EXPECT_EQ((change_base(-2, 25)), (std::string("")));
    EXPECT_EQ((change_base(22, 7)), (std::string("31")));
    EXPECT_EQ((change_base(-6, -244)), (std::string("")));
    EXPECT_EQ((change_base(20, 234)), (std::string("20")));
    EXPECT_EQ((change_base(16, 22)), (std::string("16")));
    EXPECT_EQ((change_base(1, 11101009)), (std::string("1")));
    EXPECT_EQ((change_base(0, -3)), (std::string("")));
    EXPECT_EQ((change_base(4, 623)), (std::string("4")));
    EXPECT_EQ((change_base(11101009, -1)), (std::string("0")));
    EXPECT_EQ((change_base(100, 346)), (std::string("100")));
    EXPECT_EQ((change_base(370, -9)), (std::string("1")));
    EXPECT_EQ((change_base(14, 6)), (std::string("22")));
    EXPECT_EQ((change_base(1, 235)), (std::string("1")));
    EXPECT_EQ((change_base(11101010, 24)), (std::string("19110142")));
    EXPECT_EQ((change_base(0, 20)), (std::string("")));
    EXPECT_EQ((change_base(11101010, 2)), (std::string("101010010110001101010010")));
}

TEST(Probe, change_base_02) {
    EXPECT_EQ((change_base(100, 5)), (std::string("400")));
    EXPECT_EQ((change_base(8, 10)), (std::string("8")));
    EXPECT_EQ((change_base(12, 231)), (std::string("12")));
    EXPECT_EQ((change_base(10, 10)), (std::string("10")));
    EXPECT_EQ((change_base(21, 13)), (std::string("18")));
    EXPECT_EQ((change_base(8, 10000)), (std::string("8")));
    EXPECT_EQ((change_base(2, 11101010)), (std::string("2")));
    EXPECT_EQ((change_base(-9, 751)), (std::string("")));
    EXPECT_EQ((change_base(234, 111)), (std::string("212")));
    EXPECT_EQ((change_base(22, -629)), (std::string("22")));
    EXPECT_EQ((change_base(11101010, 1000)), (std::string("1110110")));
    EXPECT_EQ((change_base(111, -77)), (std::string("34")));
    EXPECT_EQ((change_base(111, 6)), (std::string("303")));
    EXPECT_EQ((change_base(16, 456)), (std::string("16")));
    EXPECT_EQ((change_base(25, 111)), (std::string("25")));
    EXPECT_EQ((change_base(1, 17)), (std::string("1")));
    EXPECT_EQ((change_base(16, 7)), (std::string("22")));
    EXPECT_EQ((change_base(465, 20)), (std::string("135")));
    EXPECT_EQ((change_base(7, 10000)), (std::string("7")));
    EXPECT_EQ((change_base(-1, 112)), (std::string("")));
    EXPECT_EQ((change_base(-5, 1000)), (std::string("")));
    EXPECT_EQ((change_base(2, -8)), (std::string("2")));
    EXPECT_EQ((change_base(8, 16)), (std::string("8")));
}

TEST(Probe, triangle_area_01) {
    ExpectNearScalar(triangle_area(2.0f, -15.3000002f), -15.3000002f, 1e-5);
    ExpectNearScalar(triangle_area(10.1000004f, 10.0f), 50.5f, 1e-5);
    ExpectNearScalar(triangle_area(5.0f, 8.39999962f), 21.0f, 1e-5);
    ExpectNearScalar(triangle_area(-2.31999993f, 8.0f), -9.27999973f, 1e-5);
    ExpectNearScalar(triangle_area(-18.6000004f, 2.0f), -18.6000004f, 1e-5);
    ExpectNearScalar(triangle_area(41.2999992f, 5.0f), 103.25f, 1e-5);
    ExpectNearScalar(triangle_area(5.80000019f, 8.0f), 23.2000008f, 1e-5);
    ExpectNearScalar(triangle_area(9.5f, -3.20000005f), -15.1999998f, 1e-5);
    ExpectNearScalar(triangle_area(2.0f, -4.80999994f), -4.80999994f, 1e-5);
    ExpectNearScalar(triangle_area(5.0f, -5.0f), -12.5f, 1e-5);
    ExpectNearScalar(triangle_area(9.99999975e-05f, -3.9000001f), -0.000195000001f, 1e-5);
    ExpectNearScalar(triangle_area(-3.4000001f, 9.99999975e-05f), -0.000169999999f, 1e-5);
    ExpectNearScalar(triangle_area(11.8000002f, -7.5999999f), -44.8400002f, 1e-5);
    ExpectNearScalar(triangle_area(9.0f, 9.99999975e-05f), 0.000449999992f, 1e-5);
    ExpectNearScalar(triangle_area(0.200000003f, 9.99999975e-05f), 9.99999975e-06f, 1e-5);
    ExpectNearScalar(triangle_area(9.99999975e-05f, 6.0999999f), 0.000304999994f, 1e-5);
    ExpectNearScalar(triangle_area(5.0999999f, 7.5f), 19.125f, 1e-5);
    ExpectNearScalar(triangle_area(8.69999981f, 2.0f), 8.69999981f, 1e-5);
    ExpectNearScalar(triangle_area(7.5f, 3.0f), 11.25f, 1e-5);
    ExpectNearScalar(triangle_area(9.99999975e-05f, 4.0999999f), 0.000204999989f, 1e-5);
    ExpectNearScalar(triangle_area(6.0999999f, 8.5f), 25.9249992f, 1e-5);
    ExpectNearScalar(triangle_area(-8.30000019f, 0.200000003f), -0.830000043f, 1e-5);
    ExpectNearScalar(triangle_area(7.5f, 41.7999992f), 156.75f, 1e-5);
    ExpectNearScalar(triangle_area(-4.5999999f, 10.0f), -23.0f, 1e-5);
    ExpectNearScalar(triangle_area(2.0f, 39.7999992f), 39.7999992f, 1e-5);
}

TEST(Probe, triangle_area_02) {
    ExpectNearScalar(triangle_area(-19.2000008f, -0.349999994f), 3.36000013f, 1e-5);
    ExpectNearScalar(triangle_area(-16.0f, 6.69999981f), -53.5999985f, 1e-5);
    ExpectNearScalar(triangle_area(13.5f, 10.0f), 67.5f, 1e-5);
    ExpectNearScalar(triangle_area(-13.5f, 12.8000002f), -86.4000015f, 1e-5);
    ExpectNearScalar(triangle_area(1.67999995f, 17.2999992f), 14.5319986f, 1e-5);
    ExpectNearScalar(triangle_area(-3.19000006f, -7.9000001f), 12.6005001f, 1e-5);
    ExpectNearScalar(triangle_area(-1.89999998f, 9.99999975e-05f), -9.49999958e-05f, 1e-5);
    ExpectNearScalar(triangle_area(7.5f, 40.0f), 150.0f, 1e-5);
    ExpectNearScalar(triangle_area(40.0f, -4.5999999f), -92.0f, 1e-5);
    ExpectNearScalar(triangle_area(2.0f, -11.8000002f), -11.8000002f, 1e-5);
    ExpectNearScalar(triangle_area(9.99999975e-05f, -16.3999996f), -0.000819999957f, 1e-5);
    ExpectNearScalar(triangle_area(5.0f, -14.8999996f), -37.25f, 1e-5);
    ExpectNearScalar(triangle_area(-15.3000002f, 3.0f), -22.9500008f, 1e-5);
    ExpectNearScalar(triangle_area(10.0f, 4.5999999f), 23.0f, 1e-5);
    ExpectNearScalar(triangle_area(9.21000004f, -15.3999996f), -70.9169998f, 1e-5);
    ExpectNearScalar(triangle_area(5.59000015f, -0.300000012f), -0.838500082f, 1e-5);
    ExpectNearScalar(triangle_area(-1.0f, 1.89999998f), -0.949999988f, 1e-5);
    ExpectNearScalar(triangle_area(-1.49989998f, 3.9000001f), -2.92480493f, 1e-5);
    ExpectNearScalar(triangle_area(5.0f, 7.0999999f), 17.75f, 1e-5);
    ExpectNearScalar(triangle_area(9.69999981f, 7.5f), 36.375f, 1e-5);
    ExpectNearScalar(triangle_area(10.0f, 8.0f), 40.0f, 1e-5);
    ExpectNearScalar(triangle_area(-1.99989998f, -7.55999994f), 7.55962181f, 1e-5);
    ExpectNearScalar(triangle_area(6.48999977f, -10.8000002f), -35.0459976f, 1e-5);
}

TEST(Probe, fib4_01) {
    EXPECT_EQ((fib4(15)), (2764));
    EXPECT_EQ((fib4(1)), (0));
    EXPECT_EQ((fib4(30)), (52080824));
    EXPECT_EQ((fib4(4)), (2));
    EXPECT_EQ((fib4(7)), (14));
    EXPECT_EQ((fib4(27)), (7271982));
    EXPECT_EQ((fib4(9)), (54));
    EXPECT_EQ((fib4(10)), (104));
    EXPECT_EQ((fib4(28)), (14017196));
    EXPECT_EQ((fib4(14)), (1434));
    EXPECT_EQ((fib4(17)), (10270));
    EXPECT_EQ((fib4(25)), (1957204));
    EXPECT_EQ((fib4(19)), (38158));
    EXPECT_EQ((fib4(16)), (5328));
    EXPECT_EQ((fib4(20)), (73552));
    EXPECT_EQ((fib4(13)), (744));
    EXPECT_EQ((fib4(18)), (19796));
    EXPECT_EQ((fib4(29)), (27019014));
    EXPECT_EQ((fib4(24)), (1015378));
    EXPECT_EQ((fib4(35)), (1385860764));
}

TEST(Probe, median_01) {
    ExpectNearScalar(median(std::vector<float >{-0.699899971f, 10.0f, 1.83000004f}), 1.83000004f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{3.0f, -14.3999996f, 15.1999998f, 19.5f, -1.59990001f}), 3.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-8.0f, 1.0f, 2.0f, 4.0f, 5.0f}), 2.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{15.0f, 5.0f}), 10.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-10.0f, 4.0f, 6.0f, 1000.0f, 10.0f, 20.0f}), 8.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{3.0f, 1.0f, 2.0f, 4.0f, 5.0f, 11.5f}), 3.5f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{1.39999998f, 1.10000002f, -8.0f, -18.0f, 2.0f, -9.19999981f, -10.0f}), -8.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-7.9000001f, -10.3999996f}), -9.14999962f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-10.0f, 4.0f, 2.8900001f, 1000.0f, 10.0f, 20.0f}), 7.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{3.0f, 1.0f, 2.0f, 4.0f, 5.0f}), 3.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{6.0f}), 6.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-8.0f, 13.1000004f, 5.5f, 13.5f, -2.4000001f, -0.0998999998f, 15.8999996f, -8.30000019f}), 2.70005012f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-0.300000012f}), -0.300000012f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{6.0f, 5.0f}), 5.5f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{15.0f, 3.9000001f, -8.0f, 16.1000004f, 1.50010002f, 4.5f, -7.0f, 15.0f}), 4.19999981f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-1.23000002f, 8.0f, 15.0f, 10.3999996f, -2.9000001f}), 8.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{3.0f, 1.0f, 5.0f, 4.0f, 2.0f}), 3.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.0f, 1.0f, 3.0f, 9.0f, -3.9000001f, 2.0f, 7.0f}), 3.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{16.0f, 5.5f, 19.5f, 1000.0f, -10.0f, -7.5999999f, 2.21000004f, -9.60999966f}), 3.85500002f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{19.6000004f, 6.19999981f, -11.8999996f, -7.5999999f, 1.0f, 9.99999975e-05f, 7.0999999f, 9.99999975e-05f}), 0.500050008f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-10.0f, 4.0f, 6.0f, 1000.0f, 10.0f, 20.0f, 15.0f}), 10.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-8.0f, 6.5f, 14.8000002f, 18.2000008f}), 10.6499996f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{20.0f, 5.5f, 14.3000002f, 17.7999992f, 1.29999995f, -3.70000005f}), 9.89999962f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.0f, 1.0f, 9.0f, 9.0f, 2.0f, 7.0f}), 7.5f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.0f, 1.0f, 3.0f, 9.0f, 9.0f, -14.0f, 7.0f}), 7.0f, 1e-5);
}

TEST(Probe, median_02) {
    ExpectNearScalar(median(std::vector<float >{-10.8999996f, -7.0999999f, 15.8999996f, 18.5f, -13.1000004f, 10.0f, 15.0f}), 10.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{9.60000038f, 4.5f, 14.6999998f, 16.1000004f, 9.0f}), 9.60000038f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{15.0f, 9.0f, 19.0f, 9.99999975e-05f, -8.0f, 13.8999996f, 3.70000005f}), 9.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-16.7000008f, 14.8999996f, 0.800100029f}), 0.800100029f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.0f, 1.0f, 3.0f, 9.0f, 9.0f, 2.0f, 7.0f, 4.30000019f}), 5.6500001f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-10.0f, 4.0f, 1000.0f, 10.0f, 20.0f}), 10.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{15.1000004f, 16.5f, -7.63999987f, 11.6999998f, -3.0f, -9.30000019f, 0.600099981f}), 0.600099981f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.0f, 1.0f, 3.0f, 9.0f, 9.0f, 2.0f, 7.0f, 5.5f}), 6.25f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-10.0f, 4.0f, 6.0f, 1000.0f, 10.0f, 20.0f, 9.5f}), 9.5f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{9.99999975e-05f, 1.0f, 2.0f, 4.0f, 5.0f}), 2.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-10.0f, 4.0f, 6.0f, 1000.0f, 10.0f, 9.5f}), 7.75f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{14.1999998f, 6.9000001f, 11.3999996f, -8.0f, -6.4000001f}), 6.9000001f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.97000027f, -5.9000001f, -6.5999999f, -8.0f, 15.0f}), -5.9000001f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.0f, 1.0f, 3.0f, 9.0f, 9.0f, 2.0f, 7.0f, 15.0f}), 7.5f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{8.0f, 1.0f, 3.0f, 9.0f, 2.0f, 7.0f}), 5.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{5.0f, 6.0f}), 5.5f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{6.0f, -16.5f}), -5.25f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{6.0f, 5.0f, -7.80000019f}), 5.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{6.0f, 4.19999981f}), 5.0999999f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-4.17000008f, 10.3999996f, 1.70009995f, 4.0f, 5.5f}), 4.0f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{-0.800000012f, 4.5f, 9.99999975e-05f, 3.70000005f, 9.0f, 12.8999996f, 6.9000001f, -8.0f}), 4.0999999f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{9.99999975e-05f, 9.99999975e-05f}), 9.99999975e-05f, 1e-5);
    ExpectNearScalar(median(std::vector<float >{14.3999996f, 5.5f, -10.0f, -10.0f, 4.69999981f, -8.0f, -4.0999999f}), -4.0999999f, 1e-5);
}

TEST(Probe, is_palindrome_01) {
    EXPECT_EQ((is_palindrome(std::string("zbcd"))), (false));
    EXPECT_EQ((is_palindrome(std::string("x3ywzx"))), (false));
    EXPECT_EQ((is_palindrome(std::string(""))), (true));
    EXPECT_EQ((is_palindrome(std::string("xba"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xywx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("K"))), (true));
    EXPECT_EQ((is_palindrome(std::string("G89g lInR3"))), (false));
    EXPECT_EQ((is_palindrome(std::string("XB4D0T1z"))), (false));
    EXPECT_EQ((is_palindrome(std::string("6gywSyz"))), (false));
    EXPECT_EQ((is_palindrome(std::string("9yUx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xywzx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xypzx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("zbvcd"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xswzwx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("kJa"))), (false));
    EXPECT_EQ((is_palindrome(std::string("lsk"))), (false));
    EXPECT_EQ((is_palindrome(std::string("E"))), (true));
    EXPECT_EQ((is_palindrome(std::string("o3TQbRZ"))), (false));
    EXPECT_EQ((is_palindrome(std::string("2b"))), (false));
    EXPECT_EQ((is_palindrome(std::string("ba"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xz2x"))), (false));
    EXPECT_EQ((is_palindrome(std::string("p"))), (true));
    EXPECT_EQ((is_palindrome(std::string("nMYfbsnf"))), (false));
    EXPECT_EQ((is_palindrome(std::string("1aa6a"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xywyY"))), (false));
}

TEST(Probe, is_palindrome_02) {
    EXPECT_EQ((is_palindrome(std::string("eMWICohv0ns"))), (false));
    EXPECT_EQ((is_palindrome(std::string("Yfpi5lF4EZej"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xywz"))), (false));
    EXPECT_EQ((is_palindrome(std::string("Bzbcd"))), (false));
    EXPECT_EQ((is_palindrome(std::string("aaaam"))), (false));
    EXPECT_EQ((is_palindrome(std::string("OzFBwFg7e5A"))), (false));
    EXPECT_EQ((is_palindrome(std::string("qxywvx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("aWaaq"))), (false));
    EXPECT_EQ((is_palindrome(std::string("pDPqHd4mwUA5"))), (false));
    EXPECT_EQ((is_palindrome(std::string("L"))), (true));
    EXPECT_EQ((is_palindrome(std::string("xywy0"))), (false));
    EXPECT_EQ((is_palindrome(std::string("J"))), (true));
    EXPECT_EQ((is_palindrome(std::string("xw2c"))), (false));
    EXPECT_EQ((is_palindrome(std::string("mOZg0QE0K"))), (false));
    EXPECT_EQ((is_palindrome(std::string("U"))), (true));
    EXPECT_EQ((is_palindrome(std::string("2kFYP3"))), (false));
    EXPECT_EQ((is_palindrome(std::string("ktM28TcX3Xp5"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xwyv"))), (false));
    EXPECT_EQ((is_palindrome(std::string("2jau655v"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xiRjuV8"))), (false));
    EXPECT_EQ((is_palindrome(std::string("1 z4JmX2"))), (false));
    EXPECT_EQ((is_palindrome(std::string("0xO"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xDQwyz"))), (false));
}
