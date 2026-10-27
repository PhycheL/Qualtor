// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_16.h"

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

TEST(Probe, solutions_01) {
    EXPECT_EQ((solutions(std::vector<int >{5, 8, 7, 1, -623})), (12));
    EXPECT_EQ((solutions(std::vector<int >{23, 13, 30, 32})), (23));
    EXPECT_EQ((solutions(std::vector<int >{30, 13, 23})), (23));
    EXPECT_EQ((solutions(std::vector<int >{-3, 5, 7, 10, 2})), (7));
    EXPECT_EQ((solutions(std::vector<int >{30, 13, 23, 32})), (23));
    EXPECT_EQ((solutions(std::vector<int >{3, 13, 2, 9})), (3));
    EXPECT_EQ((solutions(std::vector<int >{-5, 313, -3, 19, 7})), (7));
    EXPECT_EQ((solutions(std::vector<int >{23})), (23));
    EXPECT_EQ((solutions(std::vector<int >{30, 24, 13, 321})), (13));
    EXPECT_EQ((solutions(std::vector<int >{5, 9})), (5));
    EXPECT_EQ((solutions(std::vector<int >{22, -7})), (0));
    EXPECT_EQ((solutions(std::vector<int >{1, 32, 12345, 199, 22})), (12346));
    EXPECT_EQ((solutions(std::vector<int >{3, 3, 3, 3, 3, 321})), (9));
    EXPECT_EQ((solutions(std::vector<int >{3, 24, 6, 1, 3})), (6));
    EXPECT_EQ((solutions(std::vector<int >{3, 4})), (3));
    EXPECT_EQ((solutions(std::vector<int >{30, 13, 24})), (0));
    EXPECT_EQ((solutions(std::vector<int >{22, 300, 0, 16, 20, 12})), (0));
    EXPECT_EQ((solutions(std::vector<int >{0, 5, -557, 25, 1, 29, 12, 7})), (1));
    EXPECT_EQ((solutions(std::vector<int >{3, 3, 3, 3})), (6));
    EXPECT_EQ((solutions(std::vector<int >{8, 12, -9, 8, 9, 3})), (9));
    EXPECT_EQ((solutions(std::vector<int >{2, 13, 3, 9})), (3));
    EXPECT_EQ((solutions(std::vector<int >{3, 13, 2, 9, 0})), (3));
    EXPECT_EQ((solutions(std::vector<int >{3, 13, 2, 9, 3})), (6));
    EXPECT_EQ((solutions(std::vector<int >{26, 4, 2, -3})), (0));
    EXPECT_EQ((solutions(std::vector<int >{3, 13, 2, -777})), (3));
}

TEST(Probe, solutions_02) {
    EXPECT_EQ((solutions(std::vector<int >{3, 4, -489, 10})), (3));
    EXPECT_EQ((solutions(std::vector<int >{-6, 4, 14, -8, 895, 801, 321})), (1216));
    EXPECT_EQ((solutions(std::vector<int >{30, 13, 24, 321, 13})), (13));
    EXPECT_EQ((solutions(std::vector<int >{3})), (3));
    EXPECT_EQ((solutions(std::vector<int >{7, 9})), (7));
    EXPECT_EQ((solutions(std::vector<int >{30})), (0));
    EXPECT_EQ((solutions(std::vector<int >{2, 6, 321, 15, 15, 1})), (336));
    EXPECT_EQ((solutions(std::vector<int >{2, 4, 8, 9})), (0));
    EXPECT_EQ((solutions(std::vector<int >{30, 3, 3, 3, 3})), (6));
    EXPECT_EQ((solutions(std::vector<int >{30, 13, 23, 32, 23})), (46));
    EXPECT_EQ((solutions(std::vector<int >{3, 13, 2, 24})), (3));
    EXPECT_EQ((solutions(std::vector<int >{0, -451, 321, 832, 135, 32})), (456));
    EXPECT_EQ((solutions(std::vector<int >{748, 26, 874, -9, 4, 19})), (0));
    EXPECT_EQ((solutions(std::vector<int >{2, 3, 3, 3, 3})), (6));
    EXPECT_EQ((solutions(std::vector<int >{5, 8, 6, 1})), (5));
    EXPECT_EQ((solutions(std::vector<int >{32, 2, 9, 24, 4})), (9));
    EXPECT_EQ((solutions(std::vector<int >{16, 24, 26, 5, 8, 0, 30, 2})), (0));
    EXPECT_EQ((solutions(std::vector<int >{30, 6, 21, 939, 14, 13, 3})), (24));
    EXPECT_EQ((solutions(std::vector<int >{4, 8})), (0));
    EXPECT_EQ((solutions(std::vector<int >{30, 13, 23, 32, 26})), (23));
    EXPECT_EQ((solutions(std::vector<int >{322})), (0));
    EXPECT_EQ((solutions(std::vector<int >{13, 13, 12, 10})), (13));
    EXPECT_EQ((solutions(std::vector<int >{8, 29})), (0));
}

TEST(Probe, add_elements_01) {
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 7, 8, 9, 17}, -1)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{6}, -5)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{3, 0, 86}, -10)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{2, 19, 99, 57, 5, 2, 90, 88}, -7)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{}, -8)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{1, -2, -3, 41, 57, 76, 87, 88, 99}, 2)), (-1));
    EXPECT_EQ((add_elements(std::vector<int >{11, 21, 3, 90, 5, 6, 7, 8, 9}, 4)), (125));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 7, 8, 9}, 6)), (35));
    EXPECT_EQ((add_elements(std::vector<int >{11, 21, 3, 90, 5, 6, 9, 8, 7}, 2)), (32));
    EXPECT_EQ((add_elements(std::vector<int >{1}, -505)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 7, 8, 9}, 9)), (59));
    EXPECT_EQ((add_elements(std::vector<int >{9, 466, 8, 41, -10, 24, 14, 121}, -135)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{-6, 90, 722, 20, 20}, 1)), (-6));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 8, 9}, 3)), (24));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 7, 8, 9}, -57)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{6}, 1)), (6));
    EXPECT_EQ((add_elements(std::vector<int >{11, 21, 3, 90, 5, 6, 7, 9}, -6)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 7, 8, 9, 23}, -13)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{1, -2, -3, 41, 57, 76, 87, 88, 99}, 5)), (94));
    EXPECT_EQ((add_elements(std::vector<int >{1, -2, -3, 41, 57, 76, 87, 88, 99}, -4)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{11, 21, 3, 90, 5, 6, 7, 8, 9}, -2)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{-958}, -905)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 7, 8, 9}, 1)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{1}, -10)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{15, 2, 0, -2}, -3)), (0));
}

TEST(Probe, add_elements_02) {
    EXPECT_EQ((add_elements(std::vector<int >{10, -3, 3999, 26, 99, -1}, -3)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{41, -3, 28, -5, 111, -9, 24, 12}, -7)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{12, 125, 21, 24, 20, 27, 16, 15}, 6)), (104));
    EXPECT_EQ((add_elements(std::vector<int >{4000, 77, 5, 12345, 9, -1, 7}, 6)), (90));
    EXPECT_EQ((add_elements(std::vector<int >{16, 28, 3, 25, -988, -2}, -4)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{11, 21, 3, 90, 5, 6, 7, 9}, 8)), (152));
    EXPECT_EQ((add_elements(std::vector<int >{11, 1000}, 1)), (11));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 5, 6, 7, 8, 9}, -319)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{8, -553, 11, 21, 7, 0, 18, 6}, 8)), (71));
    EXPECT_EQ((add_elements(std::vector<int >{9}, -234)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{111, 121, 3, 4000, 6}, 0)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{0, 3, 364}, -4)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{1, -3, 41, 57, 76, 87, 88, 99}, -2)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{111, 121, 3, 5, 6}, 1)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{-2, 87, 6}, -9)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{111, 121, 3, -2, 5, 6}, 3)), (3));
    EXPECT_EQ((add_elements(std::vector<int >{-2, 21, 100, 913, 15, 26}, -8)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{1}, -5)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{11, 3, 21, 90, 5, 6, 7, 8, 9}, 4)), (125));
    EXPECT_EQ((add_elements(std::vector<int >{1, -2, -3, 41, 57, 7, 87, 88, 99}, -3)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 7, 8, 9}, 8)), (50));
    EXPECT_EQ((add_elements(std::vector<int >{111, 21, 3, 4000, 5, 6, 7, 8, 9}, -512)), (0));
    EXPECT_EQ((add_elements(std::vector<int >{11, 21, 3, 90, 5, 6, 7, 8, 9}, 1)), (11));
}

TEST(Probe, get_odd_collatz_01) {
    EXPECT_EQ((get_odd_collatz(486)), (std::vector<int >{1, 5, 23, 35, 53, 61, 103, 137, 155, 167, 175, 233, 243, 251, 263, 283, 319, 325, 365, 377, 395, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(100)), (std::vector<int >{1, 5, 11, 13, 17, 19, 25, 29}));
    EXPECT_EQ((get_odd_collatz(18)), (std::vector<int >{1, 5, 7, 9, 11, 13, 17}));
    EXPECT_EQ((get_odd_collatz(10)), (std::vector<int >{1, 5}));
    EXPECT_EQ((get_odd_collatz(4)), (std::vector<int >{1}));
    EXPECT_EQ((get_odd_collatz(179)), (std::vector<int >{1, 5, 11, 13, 17, 19, 29, 101, 179, 269}));
    EXPECT_EQ((get_odd_collatz(99999)), (std::vector<int >{1, 227, 341, 605, 955, 1075, 1433, 1613, 1787, 2011, 2263, 2681, 3017, 3395, 4699, 5093, 5287, 6265, 6599, 7049, 7931, 8353, 8471, 8923, 9899, 10039, 10427, 11137, 11731, 11897, 12707, 13385, 14849, 15059, 15641, 17597, 19061, 22589, 27805, 99999, 149999, 152047, 224999, 228071, 329167, 337499, 342107, 360407, 379687, 384871, 416603, 438889, 468679, 493751, 506249, 513161, 540611, 569531, 577307, 585185, 593173, 624905, 640723, 649471, 703019, 740627, 790897, 810917, 854297, 865961, 961085, 974207, 1054529, 1110941, 1461311, 1560493, 2080657, 2191967, 3287951, 4931927, 7397891, 11096837}));
    EXPECT_EQ((get_odd_collatz(11)), (std::vector<int >{1, 5, 11, 13, 17}));
    EXPECT_EQ((get_odd_collatz(16)), (std::vector<int >{1}));
    EXPECT_EQ((get_odd_collatz(22)), (std::vector<int >{1, 5, 11, 13, 17}));
    EXPECT_EQ((get_odd_collatz(251)), (std::vector<int >{1, 5, 23, 35, 53, 61, 251, 283, 319, 325, 377, 425, 433, 479, 577, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(9)), (std::vector<int >{1, 5, 7, 9, 11, 13, 17}));
    EXPECT_EQ((get_odd_collatz(375)), (std::vector<int >{1, 5, 11, 13, 17, 19, 29, 101, 119, 179, 269, 317, 375, 563, 845}));
    EXPECT_EQ((get_odd_collatz(366)), (std::vector<int >{1, 5, 23, 35, 53, 61, 155, 167, 175, 183, 233, 251, 263, 275, 283, 319, 325, 377, 395, 413, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(5)), (std::vector<int >{1, 5}));
    EXPECT_EQ((get_odd_collatz(15)), (std::vector<int >{1, 5, 15, 23, 35, 53}));
    EXPECT_EQ((get_odd_collatz(24)), (std::vector<int >{1, 3, 5}));
    EXPECT_EQ((get_odd_collatz(842)), (std::vector<int >{1, 5, 11, 13, 17, 19, 29, 79, 101, 119, 179, 269, 421}));
    EXPECT_EQ((get_odd_collatz(2)), (std::vector<int >{1}));
    EXPECT_EQ((get_odd_collatz(315)), (std::vector<int >{1, 5, 11, 13, 17, 19, 25, 29, 315, 355, 473, 533}));
    EXPECT_EQ((get_odd_collatz(136)), (std::vector<int >{1, 5, 13, 17}));
    EXPECT_EQ((get_odd_collatz(258)), (std::vector<int >{1, 5, 23, 35, 47, 53, 55, 61, 71, 73, 83, 91, 97, 103, 107, 121, 125, 129, 137, 155, 161, 167, 175, 233, 251, 263, 283, 319, 325, 377, 395, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(12)), (std::vector<int >{1, 3, 5}));
    EXPECT_EQ((get_odd_collatz(669)), (std::vector<int >{1, 5, 23, 35, 53, 61, 251, 283, 319, 325, 377, 425, 433, 479, 577, 669, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(29)), (std::vector<int >{1, 5, 11, 13, 17, 29}));
}

TEST(Probe, get_odd_collatz_02) {
    EXPECT_EQ((get_odd_collatz(26)), (std::vector<int >{1, 5, 13}));
    EXPECT_EQ((get_odd_collatz(352)), (std::vector<int >{1, 5, 11, 13, 17}));
    EXPECT_EQ((get_odd_collatz(193)), (std::vector<int >{1, 5, 23, 31, 35, 41, 47, 53, 61, 71, 91, 103, 107, 109, 121, 137, 145, 155, 161, 167, 175, 193, 233, 251, 263, 283, 319, 325, 377, 395, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(19)), (std::vector<int >{1, 5, 11, 13, 17, 19, 29}));
    EXPECT_EQ((get_odd_collatz(645)), (std::vector<int >{1, 5, 23, 35, 53, 61, 91, 103, 121, 137, 155, 167, 175, 233, 251, 263, 283, 319, 325, 377, 395, 425, 433, 445, 479, 577, 593, 645, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(226)), (std::vector<int >{1, 85, 113}));
    EXPECT_EQ((get_odd_collatz(349)), (std::vector<int >{1, 5, 7, 11, 13, 17, 37, 131, 197, 349}));
    EXPECT_EQ((get_odd_collatz(292)), (std::vector<int >{1, 5, 23, 35, 47, 53, 55, 61, 71, 73, 83, 91, 103, 107, 121, 125, 137, 155, 161, 167, 175, 233, 251, 263, 283, 319, 325, 377, 395, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(121)), (std::vector<int >{1, 5, 23, 35, 53, 61, 91, 103, 121, 137, 155, 167, 175, 233, 251, 263, 283, 319, 325, 377, 395, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(386)), (std::vector<int >{1, 5, 23, 31, 35, 41, 47, 53, 61, 71, 91, 103, 107, 109, 121, 137, 145, 155, 161, 167, 175, 193, 233, 251, 263, 283, 319, 325, 377, 395, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(819)), (std::vector<int >{1, 5, 7, 11, 13, 17, 37, 49, 65, 173, 461, 819, 1229}));
    EXPECT_EQ((get_odd_collatz(837)), (std::vector<int >{1, 5, 11, 13, 17, 19, 29, 59, 67, 89, 101, 157, 837}));
    EXPECT_EQ((get_odd_collatz(30)), (std::vector<int >{1, 5, 15, 23, 35, 53}));
    EXPECT_EQ((get_odd_collatz(1000)), (std::vector<int >{1, 5, 23, 35, 47, 53, 61, 71, 91, 103, 107, 121, 125, 137, 155, 161, 167, 175, 233, 251, 263, 283, 319, 325, 377, 395, 425, 433, 445, 479, 577, 593, 719, 911, 1079, 1367, 1619, 2051, 2429, 3077}));
    EXPECT_EQ((get_odd_collatz(298)), (std::vector<int >{1, 5, 7, 11, 13, 17, 149}));
    EXPECT_EQ((get_odd_collatz(454)), (std::vector<int >{1, 227, 341}));
    EXPECT_EQ((get_odd_collatz(116)), (std::vector<int >{1, 5, 11, 13, 17, 29}));
    EXPECT_EQ((get_odd_collatz(25)), (std::vector<int >{1, 5, 11, 13, 17, 19, 25, 29}));
    EXPECT_EQ((get_odd_collatz(698)), (std::vector<int >{1, 5, 7, 11, 13, 17, 37, 131, 197, 349}));
    EXPECT_EQ((get_odd_collatz(23)), (std::vector<int >{1, 5, 23, 35, 53}));
    EXPECT_EQ((get_odd_collatz(604)), (std::vector<int >{1, 151, 227, 341}));
    EXPECT_EQ((get_odd_collatz(847)), (std::vector<int >{1, 151, 227, 341, 805, 847, 1073, 1271, 1907, 2861}));
    EXPECT_EQ((get_odd_collatz(180)), (std::vector<int >{1, 5, 13, 17, 45}));
}

TEST(Probe, valid_date_01) {
    EXPECT_EQ((valid_date(std::string("2p-31K20500"))), (false));
    EXPECT_EQ((valid_date(std::string("200304"))), (false));
    EXPECT_EQ((valid_date(std::string("0-4-2020"))), (false));
    EXPECT_EQ((valid_date(std::string("N1bNAunkfIv"))), (false));
    EXPECT_EQ((valid_date(std::string("uOG2"))), (false));
    EXPECT_EQ((valid_date(std::string("GRA yPNN"))), (false));
    EXPECT_EQ((valid_date(std::string(" iAoU"))), (false));
    EXPECT_EQ((valid_date(std::string("SXmTnx"))), (false));
    EXPECT_EQ((valid_date(std::string("l9T64hPnHv"))), (false));
    EXPECT_EQ((valid_date(std::string("9cybH"))), (false));
    EXPECT_EQ((valid_date(std::string("8K1"))), (false));
    EXPECT_EQ((valid_date(std::string("200-4"))), (false));
    EXPECT_EQ((valid_date(std::string("5-01-2012"))), (false));
    EXPECT_EQ((valid_date(std::string("04-2003"))), (false));
    EXPECT_EQ((valid_date(std::string("BNU9RwuFT5"))), (false));
    EXPECT_EQ((valid_date(std::string("20030412"))), (false));
    EXPECT_EQ((valid_date(std::string("eGqf"))), (false));
    EXPECT_EQ((valid_date(std::string("h03-11-s2000"))), (false));
    EXPECT_EQ((valid_date(std::string(""))), (false));
    EXPECT_EQ((valid_date(std::string("15-01-2012"))), (false));
    EXPECT_EQ((valid_date(std::string("XuQnGmg8zG"))), (false));
    EXPECT_EQ((valid_date(std::string("Q"))), (false));
    EXPECT_EQ((valid_date(std::string("m20030412"))), (false));
    EXPECT_EQ((valid_date(std::string("06-06-2005"))), (true));
    EXPECT_EQ((valid_date(std::string("21-31-200"))), (false));
}

TEST(Probe, valid_date_02) {
    EXPECT_EQ((valid_date(std::string("/6G-06-2005"))), (false));
    EXPECT_EQ((valid_date(std::string("0606-2005"))), (false));
    EXPECT_EQ((valid_date(std::string("01221O03"))), (false));
    EXPECT_EQ((valid_date(std::string("200J04-12"))), (false));
    EXPECT_EQ((valid_date(std::string("4568jjQY4gOr"))), (false));
    EXPECT_EQ((valid_date(std::string("04-12-2003"))), (true));
    EXPECT_EQ((valid_date(std::string("21-31-2000"))), (false));
    EXPECT_EQ((valid_date(std::string("R6dv"))), (false));
    EXPECT_EQ((valid_date(std::string("0W4-31-300"))), (false));
    EXPECT_EQ((valid_date(std::string("awYjFO0iw"))), (false));
    EXPECT_EQ((valid_date(std::string("06/04/020"))), (false));
    EXPECT_EQ((valid_date(std::string("2fnv"))), (false));
    EXPECT_EQ((valid_date(std::string("iiUkxoQD"))), (false));
    EXPECT_EQ((valid_date(std::string("wDeX0TUpl iS"))), (false));
    EXPECT_EQ((valid_date(std::string("04-12M2003"))), (false));
    EXPECT_EQ((valid_date(std::string("vfc"))), (false));
    EXPECT_EQ((valid_date(std::string("F6L5aYYRGW20"))), (false));
    EXPECT_EQ((valid_date(std::string("9yjVqV52d3vv"))), (false));
    EXPECT_EQ((valid_date(std::string("0G6-0c4-2020"))), (false));
    EXPECT_EQ((valid_date(std::string("d"))), (false));
    EXPECT_EQ((valid_date(std::string("15-0M1-2012"))), (false));
    EXPECT_EQ((valid_date(std::string("04331-300"))), (false));
    EXPECT_EQ((valid_date(std::string("bipkIBZ4zt"))), (false));
}

TEST(Probe, split_words_01) {
    EXPECT_EQ((split_words(std::string("HlLp8PMcNS0p"))), (std::vector<std::string >{std::string("3")}));
    EXPECT_EQ((split_words(std::string("GLfHOUfi"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string("aaaBb"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string("aaBb"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string(""))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("aab"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string("Hello,Hello,world"))), (std::vector<std::string >{std::string("Hello"), std::string("Hello"), std::string("world")}));
    EXPECT_EQ((split_words(std::string("a"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("Hello world,!"))), (std::vector<std::string >{std::string("Hello"), std::string("world,!")}));
    EXPECT_EQ((split_words(std::string("44f72D0rfDCK"))), (std::vector<std::string >{std::string("3")}));
    EXPECT_EQ((split_words(std::string("b"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string("HelRlo,world!"))), (std::vector<std::string >{std::string("HelRlo"), std::string("world!")}));
    EXPECT_EQ((split_words(std::string("3"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("ellao wOorld,!"))), (std::vector<std::string >{std::string("ellao"), std::string("wOorld,!")}));
    EXPECT_EQ((split_words(std::string("1nbPk0PFCy"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string("world,!"))), (std::vector<std::string >{std::string("world"), std::string("!")}));
    EXPECT_EQ((split_words(std::string("HeNlo"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string("world!"))), (std::vector<std::string >{std::string("3")}));
    EXPECT_EQ((split_words(std::string("g36a"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("HellQo,worlG!"))), (std::vector<std::string >{std::string("HellQo"), std::string("worlG!")}));
    EXPECT_EQ((split_words(std::string("uAdNcYJY9lJL"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string(",ca"))), (std::vector<std::string >{std::string("ca")}));
    EXPECT_EQ((split_words(std::string("raUfEJF7"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string("Hello wNorf!"))), (std::vector<std::string >{std::string("Hello"), std::string("wNorf!")}));
    EXPECT_EQ((split_words(std::string("7"))), (std::vector<std::string >{std::string("0")}));
}

TEST(Probe, split_words_02) {
    EXPECT_EQ((split_words(std::string("F"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("Kok!"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("L"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("wo1ldUK!"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string("Pb2"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string("DHelo,Hello,world"))), (std::vector<std::string >{std::string("DHelo"), std::string("Hello"), std::string("world")}));
    EXPECT_EQ((split_words(std::string("aaabb"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string("orrld,!"))), (std::vector<std::string >{std::string("orrld"), std::string("!")}));
    EXPECT_EQ((split_words(std::string("5h2a8K"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string("M"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("wrZlZ!"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string("yUnL74"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string("Helo wrld!"))), (std::vector<std::string >{std::string("Helo"), std::string("wrld!")}));
    EXPECT_EQ((split_words(std::string("eyqycScIO2w"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("worD,"))), (std::vector<std::string >{std::string("worD")}));
    EXPECT_EQ((split_words(std::string("21lwmht! 0Zt"))), (std::vector<std::string >{std::string("21lwmht!"), std::string("0Zt")}));
    EXPECT_EQ((split_words(std::string("tQaDcr!u"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string("weo3rld,!"))), (std::vector<std::string >{std::string("weo3rld"), std::string("!")}));
    EXPECT_EQ((split_words(std::string("VSBbk"))), (std::vector<std::string >{std::string("1")}));
    EXPECT_EQ((split_words(std::string("ajabmb"))), (std::vector<std::string >{std::string("3")}));
    EXPECT_EQ((split_words(std::string("S"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((split_words(std::string("nelo"))), (std::vector<std::string >{std::string("2")}));
    EXPECT_EQ((split_words(std::string("abcdef"))), (std::vector<std::string >{std::string("3")}));
}

TEST(Probe, is_sorted_01) {
    EXPECT_EQ((is_sorted(std::vector<int >{-3, 3, 6})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 3, 3, 4, 6})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 3, 2, 4, 5, 6, 7})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 2, 7, 3, 4})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 3, 3, 4, 5})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{5, -626, -5, 254, 8, 206, -356})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{5})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{4, 3, 2, 1, 5})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 4, 7})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 3, 4})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{26, 15, 669, -5, 6, 2, 4})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{315, 3, 2, 4, 5})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 832, 6, 1, -817, 7})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 4, 5, 6})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{3, 4, 14, 2, 7, 915})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 4, 5})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 15, 6, 17, -548, 26, 12, 27})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 3, 2, 4, 5})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{12345, 7})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{-3, 7, 1, 7, 6, 2, 265})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{2, 1, 3, 4, 5, 6, 7})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{4, 14, 691})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{2, 3, 572, 6, 4, 28, 8, 920})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 7, 2, 2, 3, 4})), (false));
}

TEST(Probe, is_sorted_02) {
    EXPECT_EQ((is_sorted(std::vector<int >{7, 0})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 4})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{3, 2})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 2, 2, 26, 4})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{16, 4, 6})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{-5, 598, 12345, 19, 637})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{520, 6, 3, 2})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{-8, 21, 228, 6})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{5, 12345, 6, -3, 20, 4, 2, 1})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{-2, 5, 4})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 4, 6, 6})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{4, 2, 3, 1, 5, 6})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{30, 14, 25, -1, 5})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 4, 5, 6, 7})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{16, 2, -8, 1, 410, 6, 1, 9})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 2, 2, 3, 684})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 2, 3, 4})), (true));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 5, 2, 4, 5})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 4, 7, 6, 5})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 2, 3, 3, 3, 4, 4})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{19, 4, -14, 4, 9, 3, -1})), (false));
    EXPECT_EQ((is_sorted(std::vector<int >{1, 5, 2, 4, 3, 6, 7})), (false));
}

TEST(Probe, intersection_01) {
    EXPECT_EQ((intersection(std::vector<int >{-2, -2, 5}, std::vector<int >{3, 5})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-2, 1}, std::vector<int >{-5, 5})), (std::string("YES")));
    EXPECT_EQ((intersection(std::vector<int >{29, 2, -3, -2, 353, 22, 1}, std::vector<int >{300, 11, 4, 1, 21})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, 16, -344, 2, -4, 328, -3}, std::vector<int >{-1, 1})), (std::string("YES")));
    EXPECT_EQ((intersection(std::vector<int >{5, 5, -2}, std::vector<int >{-1, -1})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{2, 3, 1}, std::vector<int >{0, 4})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-3, -2, 23}, std::vector<int >{-4, 0})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, -1, 4}, std::vector<int >{-11, 2, -747})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-11, 0}, std::vector<int >{-1, 20})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{3, 1, 26, 3, 2}, std::vector<int >{897, 25, 28, 3, 1})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{5, 3}, std::vector<int >{0, 4})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, -1}, std::vector<int >{-3, -2, 4})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{0, 4}, std::vector<int >{3, -9})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-3, -1}, std::vector<int >{-2, -2})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{8, -13, 2, 11, 22, -1, 514, -4}, std::vector<int >{0, 0})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{14, 4, 5, -3, -8, 3, 378}, std::vector<int >{2, 3})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-2, 3}, std::vector<int >{0, 4})), (std::string("YES")));
    EXPECT_EQ((intersection(std::vector<int >{2, -6, -447, 5, -244}, std::vector<int >{-3, -2})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-2, -2}, std::vector<int >{0, 4, 984})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-4, 0, -3}, std::vector<int >{-5, 5, 1})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, -3, -8}, std::vector<int >{16, -3, 14})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, 0}, std::vector<int >{-4, 585})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-4, 0, 18}, std::vector<int >{0, 4, -7})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, -383, 3, -366, 13, 24}, std::vector<int >{3, 5})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-2, -2}, std::vector<int >{-1, -2})), (std::string("NO")));
}

TEST(Probe, intersection_02) {
    EXPECT_EQ((intersection(std::vector<int >{3, 5}, std::vector<int >{-5, 5})), (std::string("YES")));
    EXPECT_EQ((intersection(std::vector<int >{0, 4}, std::vector<int >{0, -4})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-5, 5, 27}, std::vector<int >{3, 5})), (std::string("YES")));
    EXPECT_EQ((intersection(std::vector<int >{-3, 1}, std::vector<int >{-1, 1})), (std::string("YES")));
    EXPECT_EQ((intersection(std::vector<int >{-3, -2}, std::vector<int >{3, 1, 3, 29, -3})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-2, -2, -571}, std::vector<int >{-2, -2})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-2, -2, -9}, std::vector<int >{-2, -2})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-821, 0}, std::vector<int >{-11, 2})), (std::string("YES")));
    EXPECT_EQ((intersection(std::vector<int >{-11, 2}, std::vector<int >{-11, 2})), (std::string("YES")));
    EXPECT_EQ((intersection(std::vector<int >{0, 4, 2}, std::vector<int >{5, -7, 26, 0, -799})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, -1}, std::vector<int >{-1, -1, 13})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{10, 4}, std::vector<int >{-5, 5})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-3, -1, -6}, std::vector<int >{0, 4})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-11, 26, 5, 28, 22, -5}, std::vector<int >{-2, -2})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, -4, 5}, std::vector<int >{1, 27, -3, 19, -3})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{19, 2, -2, -4, 1, -502}, std::vector<int >{0, 4})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{0, 4}, std::vector<int >{-5, 5})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{3, 5}, std::vector<int >{-11, 2})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-2, 2, 3}, std::vector<int >{2, 3})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-4, 0}, std::vector<int >{15, -2, 16, -6, 22, -182})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{2, -1}, std::vector<int >{3, 5})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-1, 1}, std::vector<int >{-3, -1, 4})), (std::string("NO")));
    EXPECT_EQ((intersection(std::vector<int >{-11, 2}, std::vector<int >{2, -1, -6, -202, -174, 4, -3})), (std::string("NO")));
}

TEST(Probe, prod_signs_01) {
    EXPECT_EQ((prod_signs(std::vector<int >{1, 2, 2, 24})), (29));
    EXPECT_EQ((prod_signs(std::vector<int >{2, 4, 1, 2, -1, -1, 9})), (20));
    EXPECT_EQ((prod_signs(std::vector<int >{1, 2, -7, -4})), (14));
    EXPECT_EQ((prod_signs(std::vector<int >{-32768, 207, 0, 269, 7, 18})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{-1, -1, 1, 1})), (4));
    EXPECT_EQ((prod_signs(std::vector<int >{1, 1, 1, 1, 3, -1, 2})), (-10));
    EXPECT_EQ((prod_signs(std::vector<int >{14})), (14));
    EXPECT_EQ((prod_signs(std::vector<int >{2, -1, 1, 2, -1, 4, 9})), (20));
    EXPECT_EQ((prod_signs(std::vector<int >{1, -1, -1, 1})), (4));
    EXPECT_EQ((prod_signs(std::vector<int >{0})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{7, -3, 162, 8, 1, 100, 797, 5})), (-1083));
    EXPECT_EQ((prod_signs(std::vector<int >{30, 3, -3, 20, 7, 1, -32769})), (32833));
    EXPECT_EQ((prod_signs(std::vector<int >{4})), (4));
    EXPECT_EQ((prod_signs(std::vector<int >{-10})), (-10));
    EXPECT_EQ((prod_signs(std::vector<int >{-8, 6, 4})), (-18));
    EXPECT_EQ((prod_signs(std::vector<int >{-32768})), (-32768));
    EXPECT_EQ((prod_signs(std::vector<int >{})), (-32768));
    EXPECT_EQ((prod_signs(std::vector<int >{2, 4, 1, 2, -1, -1, 9, 0})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{-9, 27, 20, -1})), (57));
    EXPECT_EQ((prod_signs(std::vector<int >{7, 0})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{2, 919, 1000, 0})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{-1, 1, -4, 0})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{1, 2, 2, -4})), (-9));
    EXPECT_EQ((prod_signs(std::vector<int >{5})), (5));
    EXPECT_EQ((prod_signs(std::vector<int >{1, 1, 1, 2, -1, 1})), (-7));
}

TEST(Probe, prod_signs_02) {
    EXPECT_EQ((prod_signs(std::vector<int >{23, 3, -4, -2, 13})), (45));
    EXPECT_EQ((prod_signs(std::vector<int >{2, 2, 1, -4})), (-9));
    EXPECT_EQ((prod_signs(std::vector<int >{-8, 9})), (-17));
    EXPECT_EQ((prod_signs(std::vector<int >{26, 25, -3, 2, -102, 4, -6})), (-168));
    EXPECT_EQ((prod_signs(std::vector<int >{-1, 1, -1, 1, -10})), (-14));
    EXPECT_EQ((prod_signs(std::vector<int >{0, 27, 22, 3, 4})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{2, 3, 2})), (7));
    EXPECT_EQ((prod_signs(std::vector<int >{-989, -10})), (999));
    EXPECT_EQ((prod_signs(std::vector<int >{-32768, -389, -10})), (-33167));
    EXPECT_EQ((prod_signs(std::vector<int >{0, 3, 419})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{0, 7, 24, 21, -6, 4, 3, 1})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{-1, 1, 1, 1, 2})), (-6));
    EXPECT_EQ((prod_signs(std::vector<int >{2, 1, 1, 1, 3, -1, 1})), (-10));
    EXPECT_EQ((prod_signs(std::vector<int >{2, 4, 1, 2, -1, -1, 9, 63})), (83));
    EXPECT_EQ((prod_signs(std::vector<int >{0, 1, 1, 1})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{1, 1, 1, 2, 3, -1, 1})), (-10));
    EXPECT_EQ((prod_signs(std::vector<int >{20, -496})), (-516));
    EXPECT_EQ((prod_signs(std::vector<int >{-8, 6, 14, -11, -1, -4, 26, 23})), (93));
    EXPECT_EQ((prod_signs(std::vector<int >{1, 351, 0, 2, 3, -4})), (0));
    EXPECT_EQ((prod_signs(std::vector<int >{10, 27, -7})), (-44));
    EXPECT_EQ((prod_signs(std::vector<int >{-10, 20, -390, -4})), (-424));
    EXPECT_EQ((prod_signs(std::vector<int >{16, -6, -9, 4, 175})), (210));
    EXPECT_EQ((prod_signs(std::vector<int >{13, 7, -9})), (-29));
}
