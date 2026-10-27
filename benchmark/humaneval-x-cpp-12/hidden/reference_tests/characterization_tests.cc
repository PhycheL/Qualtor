// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_12.h"

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

TEST(Characterization, encrypt_01) {
    EXPECT_EQ((encrypt(std::string("faewfawefaewg"))), (std::string("jeiajeaijeiak")));
    EXPECT_EQ((encrypt(std::string("tDF"))), (std::string("xHJ")));
    EXPECT_EQ((encrypt(std::string("kj"))), (std::string("on")));
    EXPECT_EQ((encrypt(std::string("ewhjklnop"))), (std::string("ialnoprst")));
    EXPECT_EQ((encrypt(std::string("S"))), (std::string("W")));
    EXPECT_EQ((encrypt(std::string("lippsqcjvmirh"))), (std::string("pmttwugnzqmvl")));
    EXPECT_EQ((encrypt(std::string("C34m"))), (std::string("aQRq")));
    EXPECT_EQ((encrypt(std::string("A"))), (std::string("_")));
    EXPECT_EQ((encrypt(std::string(" 4D40szbAm2"))), (std::string("XRHRNwdf_qP")));
    EXPECT_EQ((encrypt(std::string("a"))), (std::string("e")));
    EXPECT_EQ((encrypt(std::string("hT"))), (std::string("lX")));
    EXPECT_EQ((encrypt(std::string("asdfghjkl"))), (std::string("ewhjklnop")));
}

TEST(Characterization, next_smallest_01) {
    EXPECT_EQ((next_smallest(std::vector<int >{12, 34, -35, -45})), (-35));
    EXPECT_EQ((next_smallest(std::vector<int >{-8, 0, 1, -272})), (-8));
    EXPECT_EQ((next_smallest(std::vector<int >{1, 2, 3, 4, 5})), (2));
    EXPECT_EQ((next_smallest(std::vector<int >{1, 1, 34})), (34));
    EXPECT_EQ((next_smallest(std::vector<int >{1, 1})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{1, 1, 1, 275, 0})), (1));
    EXPECT_EQ((next_smallest(std::vector<int >{34, -10, -8, -4, 28})), (-8));
    EXPECT_EQ((next_smallest(std::vector<int >{0, 28, 6, 0, 2})), (2));
    EXPECT_EQ((next_smallest(std::vector<int >{212, 28})), (212));
    EXPECT_EQ((next_smallest(std::vector<int >{1})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{10, 28})), (28));
    EXPECT_EQ((next_smallest(std::vector<int >{35, 1})), (35));
}

TEST(Characterization, is_bored_01) {
    EXPECT_EQ((is_bored(std::string(""))), (0));
    EXPECT_EQ((is_bored(std::string("I"))), (0));
    EXPECT_EQ((is_bored(std::string("I feel good today. I will be poductive. wilekill It"))), (2));
    EXPECT_EQ((is_bored(std::string(".I"))), (0));
    EXPECT_EQ((is_bored(std::string("Jn1JO"))), (0));
    EXPECT_EQ((is_bored(std::string("I feel good today. I will be productive. will kill It"))), (2));
    EXPECT_EQ((is_bored(std::string("vIhPI!7bE"))), (0));
    EXPECT_EQ((is_bored(std::string("T"))), (0));
    EXPECT_EQ((is_bored(std::string("lBa"))), (0));
    EXPECT_EQ((is_bored(std::string("8PMWScUPQD"))), (0));
    EXPECT_EQ((is_bored(std::string("Is the sky bluhe\?"))), (0));
    EXPECT_EQ((is_bored(std::string("Hello world"))), (0));
}

TEST(Characterization, any_int_01) {
    EXPECT_EQ((any_int(-0.5f, 5.0f, 7.0f)), (false));
    EXPECT_EQ((any_int(2.20000005f, 2.5f, -11.6999998f)), (false));
    EXPECT_EQ((any_int(-5.46999979f, 2.0999999f, -13.8999996f)), (false));
    EXPECT_EQ((any_int(6.0f, -2.9000001f, -4.69999981f)), (false));
    EXPECT_EQ((any_int(17.6000004f, -2.20000005f, 1.5f)), (false));
    EXPECT_EQ((any_int(-11.3999996f, 18.5f, -13.1000004f)), (false));
    EXPECT_EQ((any_int(2.5f, 2.20000005f, -9.5f)), (false));
    EXPECT_EQ((any_int(9.69999981f, 2.0999999f, 1.5f)), (false));
    EXPECT_EQ((any_int(-2.70000005f, -2.0f, 7.0f)), (false));
    EXPECT_EQ((any_int(-17.7000008f, -4.05999994f, 3.00999999f)), (false));
    EXPECT_EQ((any_int(-4.9000001f, -3.20000005f, 2.20000005f)), (false));
    EXPECT_EQ((any_int(5.5f, 1.5f, 5.5f)), (false));
}

TEST(Characterization, encode_01) {
    EXPECT_EQ((encode(std::string("wylhXA Net"))), (std::string("WYLHxc nGT")));
    EXPECT_EQ((encode(std::string("HMU"))), (std::string("hmw")));
    EXPECT_EQ((encode(std::string("m0dWyKBlr"))), (std::string("M0DwYkbLR")));
    EXPECT_EQ((encode(std::string("JRj5B9C"))), (std::string("jrJ5b9c")));
    EXPECT_EQ((encode(std::string("TEST"))), (std::string("tgst")));
    EXPECT_EQ((encode(std::string("yg"))), (std::string("YG")));
    EXPECT_EQ((encode(std::string("gs3t"))), (std::string("GS3T")));
    EXPECT_EQ((encode(std::string("xsidURcce"))), (std::string("XSKDwrCCG")));
    EXPECT_EQ((encode(std::string("I DoNt KnOw WhAt tO WrItE"))), (std::string("k dQnT kNqW wHcT Tq wRkTg")));
    EXPECT_EQ((encode(std::string("TGST"))), (std::string("tgst")));
    EXPECT_EQ((encode(std::string("I oNt KnOw WhAC tO WrItE"))), (std::string("k QnT kNqW wHcc Tq wRkTg")));
    EXPECT_EQ((encode(std::string("J8zisg4882pt"))), (std::string("j8ZKSG4882PT")));
}

TEST(Characterization, skjkasdkd_01) {
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 0, 1, 8, 2, 4597, 2, 1, 3, 40, 1, 2, 1, 2, 4, 2, 5, 2323})), (25));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 8, 1, 2, 1, 7})), (7));
    EXPECT_EQ((skjkasdkd(std::vector<int >{111, 507, 6, 181})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 724, 32, 71, 99, 0, 6, 0, 5, 91, 83, 32, 5, 6})), (11));
    EXPECT_EQ((skjkasdkd(std::vector<int >{2323, 7, 1, 123456, 1, -6, 101, 4})), (2));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 724, 32, 71, 99, 32, 6, 0, 5, 91, 83, 0, 5, 6})), (11));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 0, 1, 8, 2, 4597, 2, 1, 3, 40, 5, 2, 1, 2, 4, 2, 1, 1})), (25));
    EXPECT_EQ((skjkasdkd(std::vector<int >{15, 671, 1, 7, 2, 8192, -656, 12})), (7));
    EXPECT_EQ((skjkasdkd(std::vector<int >{12, 25})), (0));
    EXPECT_EQ((skjkasdkd(std::vector<int >{8191})), (19));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 81, 12, 3, 1, 21, 11})), (2));
    EXPECT_EQ((skjkasdkd(std::vector<int >{18})), (0));
}

TEST(Characterization, check_dict_case_01) {
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Swet"), std::string("9qLnbS")}, {std::string("WwEe0"), std::string("YDtGW4hp2lij")}, {std::string("gdYR"), std::string(" aupl")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("4HV77vT"), std::string("Age")}, {std::string("C itaky"), std::string("yGN4OBKZDXg")}, {std::string("City"), std::string("Za4")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("2x"), std::string("12345")}, {std::string("Houston"), std::string("p")}, {std::string("K"), std::string("NaW")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("B"), std::string("STATE")}, {std::string("ORAnGE"), std::string("S5")}, {std::string("nbagan"), std::string("wM2kt")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("A"), std::string("Age")}, {std::string("a"), std::string("L")}, {std::string("b"), std::string("B")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("S4jE"), std::string("x")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string(""), std::string("a")}, {std::string("nTtAe"), std::string("NwamZe")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("1Zq9"), std::string("BAHX3gwW")}, {std::string("ZIP"), std::string("ctThqI")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Kge"), std::string("fruit")}, {std::string("Name"), std::string("B")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("12345"), std::string("banana")}, {std::string("a"), std::string("12D345")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("appl2e"), std::string("r")}, {std::string("nUVVv4ZaE"), std::string("M")}})), (false));
}

TEST(Characterization, count_up_to_01) {
    EXPECT_EQ((count_up_to(100)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}));
    EXPECT_EQ((count_up_to(1)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(966)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953}));
    EXPECT_EQ((count_up_to(15)), (std::vector<int >{2, 3, 5, 7, 11, 13}));
    EXPECT_EQ((count_up_to(9)), (std::vector<int >{2, 3, 5, 7}));
    EXPECT_EQ((count_up_to(61)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59}));
    EXPECT_EQ((count_up_to(22)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19}));
    EXPECT_EQ((count_up_to(26)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23}));
    EXPECT_EQ((count_up_to(24)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23}));
    EXPECT_EQ((count_up_to(32)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}));
    EXPECT_EQ((count_up_to(25)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23}));
    EXPECT_EQ((count_up_to(67)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61}));
}
