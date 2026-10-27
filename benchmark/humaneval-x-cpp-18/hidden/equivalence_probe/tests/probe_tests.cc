// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_18.h"

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

TEST(Probe, is_equal_to_sum_even_01) {
    EXPECT_EQ((is_equal_to_sum_even(544)), (true));
    EXPECT_EQ((is_equal_to_sum_even(9)), (false));
    EXPECT_EQ((is_equal_to_sum_even(13)), (false));
    EXPECT_EQ((is_equal_to_sum_even(6)), (false));
    EXPECT_EQ((is_equal_to_sum_even(27)), (false));
    EXPECT_EQ((is_equal_to_sum_even(19)), (false));
    EXPECT_EQ((is_equal_to_sum_even(10)), (true));
    EXPECT_EQ((is_equal_to_sum_even(21)), (false));
    EXPECT_EQ((is_equal_to_sum_even(99999)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-116)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-10)), (false));
    EXPECT_EQ((is_equal_to_sum_even(671)), (false));
    EXPECT_EQ((is_equal_to_sum_even(428)), (true));
    EXPECT_EQ((is_equal_to_sum_even(258)), (true));
    EXPECT_EQ((is_equal_to_sum_even(20)), (true));
    EXPECT_EQ((is_equal_to_sum_even(24)), (true));
    EXPECT_EQ((is_equal_to_sum_even(-7)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-3)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-5)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-6)), (false));
    EXPECT_EQ((is_equal_to_sum_even(1000)), (true));
    EXPECT_EQ((is_equal_to_sum_even(5)), (false));
    EXPECT_EQ((is_equal_to_sum_even(1)), (false));
    EXPECT_EQ((is_equal_to_sum_even(22)), (true));
    EXPECT_EQ((is_equal_to_sum_even(12345)), (false));
}

TEST(Probe, is_equal_to_sum_even_02) {
    EXPECT_EQ((is_equal_to_sum_even(199)), (false));
    EXPECT_EQ((is_equal_to_sum_even(820)), (true));
    EXPECT_EQ((is_equal_to_sum_even(17)), (false));
    EXPECT_EQ((is_equal_to_sum_even(18)), (true));
    EXPECT_EQ((is_equal_to_sum_even(0)), (false));
    EXPECT_EQ((is_equal_to_sum_even(300)), (true));
    EXPECT_EQ((is_equal_to_sum_even(-2)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-557)), (false));
    EXPECT_EQ((is_equal_to_sum_even(7)), (false));
    EXPECT_EQ((is_equal_to_sum_even(15)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-9)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-777)), (false));
    EXPECT_EQ((is_equal_to_sum_even(100)), (true));
    EXPECT_EQ((is_equal_to_sum_even(14)), (true));
    EXPECT_EQ((is_equal_to_sum_even(-8)), (false));
    EXPECT_EQ((is_equal_to_sum_even(895)), (false));
    EXPECT_EQ((is_equal_to_sum_even(801)), (false));
    EXPECT_EQ((is_equal_to_sum_even(-508)), (false));
    EXPECT_EQ((is_equal_to_sum_even(114)), (true));
    EXPECT_EQ((is_equal_to_sum_even(30)), (true));
    EXPECT_EQ((is_equal_to_sum_even(305)), (false));
    EXPECT_EQ((is_equal_to_sum_even(713)), (false));
    EXPECT_EQ((is_equal_to_sum_even(853)), (false));
}

TEST(Probe, special_factorial_01) {
    EXPECT_EQ((special_factorial(-5)), (1LL));
    EXPECT_EQ((special_factorial(-2)), (1LL));
    EXPECT_EQ((special_factorial(-6)), (1LL));
    EXPECT_EQ((special_factorial(-835)), (1LL));
    EXPECT_EQ((special_factorial(-465)), (1LL));
    EXPECT_EQ((special_factorial(-779)), (1LL));
    EXPECT_EQ((special_factorial(-739)), (1LL));
    EXPECT_EQ((special_factorial(-709)), (1LL));
    EXPECT_EQ((special_factorial(-7)), (1LL));
    EXPECT_EQ((special_factorial(-882)), (1LL));
    EXPECT_EQ((special_factorial(-9)), (1LL));
    EXPECT_EQ((special_factorial(-3)), (1LL));
    EXPECT_EQ((special_factorial(-678)), (1LL));
    EXPECT_EQ((special_factorial(-1)), (1LL));
    EXPECT_EQ((special_factorial(-93)), (1LL));
    EXPECT_EQ((special_factorial(-401)), (1LL));
    EXPECT_EQ((special_factorial(-15)), (1LL));
    EXPECT_EQ((special_factorial(-617)), (1LL));
    EXPECT_EQ((special_factorial(-177)), (1LL));
    EXPECT_EQ((special_factorial(-215)), (1LL));
    EXPECT_EQ((special_factorial(-578)), (1LL));
    EXPECT_EQ((special_factorial(-491)), (1LL));
    EXPECT_EQ((special_factorial(-644)), (1LL));
    EXPECT_EQ((special_factorial(-333)), (1LL));
    EXPECT_EQ((special_factorial(-135)), (1LL));
}

TEST(Probe, special_factorial_02) {
    EXPECT_EQ((special_factorial(-676)), (1LL));
    EXPECT_EQ((special_factorial(-231)), (1LL));
    EXPECT_EQ((special_factorial(-747)), (1LL));
    EXPECT_EQ((special_factorial(-193)), (1LL));
    EXPECT_EQ((special_factorial(8)), (5056584744960000LL));
    EXPECT_EQ((special_factorial(-579)), (1LL));
    EXPECT_EQ((special_factorial(-376)), (1LL));
    EXPECT_EQ((special_factorial(-988)), (1LL));
    EXPECT_EQ((special_factorial(-680)), (1LL));
    EXPECT_EQ((special_factorial(-346)), (1LL));
    EXPECT_EQ((special_factorial(-587)), (1LL));
    EXPECT_EQ((special_factorial(-796)), (1LL));
    EXPECT_EQ((special_factorial(-374)), (1LL));
    EXPECT_EQ((special_factorial(-663)), (1LL));
    EXPECT_EQ((special_factorial(-234)), (1LL));
    EXPECT_EQ((special_factorial(-319)), (1LL));
    EXPECT_EQ((special_factorial(-695)), (1LL));
    EXPECT_EQ((special_factorial(-291)), (1LL));
    EXPECT_EQ((special_factorial(-743)), (1LL));
    EXPECT_EQ((special_factorial(-151)), (1LL));
    EXPECT_EQ((special_factorial(-968)), (1LL));
    EXPECT_EQ((special_factorial(-391)), (1LL));
    EXPECT_EQ((special_factorial(-799)), (1LL));
}

TEST(Probe, fix_spaces_01) {
    EXPECT_EQ((fix_spaces(std::string("n89t1vcFmE"))), (std::string("n89t1vcFmE")));
    EXPECT_EQ((fix_spaces(std::string("7F6xzCjYPh"))), (std::string("7F6xzCjYPh")));
    EXPECT_EQ((fix_spaces(std::string("t"))), (std::string("t")));
    EXPECT_EQ((fix_spaces(std::string("   Exa 1 2 2 mple"))), (std::string("-Exa_1_2_2_mple")));
    EXPECT_EQ((fix_spaces(std::string("xExQa  mple"))), (std::string("xExQa__mple")));
    EXPECT_EQ((fix_spaces(std::string("YG2-5vH2E7"))), (std::string("YG2-5vH2E7")));
    EXPECT_EQ((fix_spaces(std::string("Yellow Yellow JDirty  Fellow"))), (std::string("Yellow_Yellow_JDirty__Fellow")));
    EXPECT_EQ((fix_spaces(std::string("Ot"))), (std::string("Ot")));
    EXPECT_EQ((fix_spaces(std::string("-Exa_1_2_2_mple"))), (std::string("-Exa_1_2_2_mple")));
    EXPECT_EQ((fix_spaces(std::string("Exa-mple"))), (std::string("Exa-mple")));
    EXPECT_EQ((fix_spaces(std::string("_ElxampX_e_2"))), (std::string("_ElxampX_e_2")));
    EXPECT_EQ((fix_spaces(std::string("Exa J  mpwm"))), (std::string("Exa_J__mpwm")));
    EXPECT_EQ((fix_spaces(std::string("i6kgSWvjhbm"))), (std::string("i6kgSWvjhbm")));
    EXPECT_EQ((fix_spaces(std::string("Examwple 1"))), (std::string("Examwple_1")));
    EXPECT_EQ((fix_spaces(std::string("mX"))), (std::string("mX")));
    EXPECT_EQ((fix_spaces(std::string("Exa   mple"))), (std::string("Exa-mple")));
    EXPECT_EQ((fix_spaces(std::string("Yellow Yellow  Dirty  Fellow"))), (std::string("Yellow_Yellow__Dirty__Fellow")));
    EXPECT_EQ((fix_spaces(std::string("Mudasir Hanif "))), (std::string("Mudasir_Hanif_")));
    EXPECT_EQ((fix_spaces(std::string("_EyktR"))), (std::string("_EyktR")));
    EXPECT_EQ((fix_spaces(std::string("Yellow Yellow 2Dirty  Fellow"))), (std::string("Yellow_Yellow_2Dirty__Fellow")));
    EXPECT_EQ((fix_spaces(std::string("ELxamle"))), (std::string("ELxamle")));
    EXPECT_EQ((fix_spaces(std::string("HrgOx_MYKCsd"))), (std::string("HrgOx_MYKCsd")));
    EXPECT_EQ((fix_spaces(std::string("A"))), (std::string("A")));
    EXPECT_EQ((fix_spaces(std::string("xamplVee"))), (std::string("xamplVee")));
    EXPECT_EQ((fix_spaces(std::string("wqlfHh5TTbIb"))), (std::string("wqlfHh5TTbIb")));
}

TEST(Probe, fix_spaces_02) {
    EXPECT_EQ((fix_spaces(std::string("EDNupdrUq"))), (std::string("EDNupdrUq")));
    EXPECT_EQ((fix_spaces(std::string("Yellow_Yellow__Dirty8__Fellow"))), (std::string("Yellow_Yellow__Dirty8__Fellow")));
    EXPECT_EQ((fix_spaces(std::string("7Example"))), (std::string("7Example")));
    EXPECT_EQ((fix_spaces(std::string("Lc4LIj"))), (std::string("Lc4LIj")));
    EXPECT_EQ((fix_spaces(std::string("Example_1"))), (std::string("Example_1")));
    EXPECT_EQ((fix_spaces(std::string("dKAhN-"))), (std::string("dKAhN-")));
    EXPECT_EQ((fix_spaces(std::string("Exar   Yle"))), (std::string("Exar-Yle")));
    EXPECT_EQ((fix_spaces(std::string("Yelflow Yelloe  Dirty  Fellow"))), (std::string("Yelflow_Yelloe__Dirty__Fellow")));
    EXPECT_EQ((fix_spaces(std::string("ExDmplV_1"))), (std::string("ExDmplV_1")));
    EXPECT_EQ((fix_spaces(std::string("Muda8ir_Hanif_"))), (std::string("Muda8ir_Hanif_")));
    EXPECT_EQ((fix_spaces(std::string(" Examp1le   83"))), (std::string("_Examp1le-83")));
    EXPECT_EQ((fix_spaces(std::string("Yellow_Yellow__Dirty__Fellow"))), (std::string("Yellow_Yellow__Dirty__Fellow")));
    EXPECT_EQ((fix_spaces(std::string("1xaple_1"))), (std::string("1xaple_1")));
    EXPECT_EQ((fix_spaces(std::string("Mudasir HaniW "))), (std::string("Mudasir_HaniW_")));
    EXPECT_EQ((fix_spaces(std::string(" ExpNple 4 3"))), (std::string("_ExpNple_4_3")));
    EXPECT_EQ((fix_spaces(std::string("a"))), (std::string("a")));
    EXPECT_EQ((fix_spaces(std::string("ExbamDle_1"))), (std::string("ExbamDle_1")));
    EXPECT_EQ((fix_spaces(std::string("4FzXb"))), (std::string("4FzXb")));
    EXPECT_EQ((fix_spaces(std::string("K5"))), (std::string("K5")));
    EXPECT_EQ((fix_spaces(std::string("FKyoV-k CLb"))), (std::string("FKyoV-k_CLb")));
    EXPECT_EQ((fix_spaces(std::string("ftv"))), (std::string("ftv")));
    EXPECT_EQ((fix_spaces(std::string("i"))), (std::string("i")));
    EXPECT_EQ((fix_spaces(std::string("-Exa_1_22_mple"))), (std::string("-Exa_1_22_mple")));
}

TEST(Probe, file_name_check_01) {
    EXPECT_EQ((file_name_check(std::string("this_is_valid.txtexe"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("_Y0.8xt"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("/tis_is_valid.dll"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("MY16FIL3exe"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("No"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("jnqtPEHfp@K"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("Tpcj"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("VsbcDAX7"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("#this2_i4s_5valid.ten"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("V1ZSP"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("S,Lkx1"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("qUps\?c9R6v"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("F0eln"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("8bW"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("Hi12FILE4.exe"))), (std::string("Yes")));
    EXPECT_EQ((file_name_check(std::string("1sdf3.asd"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("this_is_valid.txt"))), (std::string("Yes")));
    EXPECT_EQ((file_name_check(std::string("VNqUC0uv_w"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("\?aREYA.exe"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("2rga"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("Ye .s"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string(""))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("@this1_is6_valid.exe"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("y3QC//l3Eh"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("L"))), (std::string("No")));
}

TEST(Probe, file_name_check_02) {
    EXPECT_EQ((file_name_check(std::string("final..txt"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("_YLtLxt"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("this_is_12valid.6xe4.txt"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("thLis_isyvalid.wow"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("."))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string(" "))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("Isuyoufaul.#txt"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("Is3oufault.tx_"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("l xfNeValUkr"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("I563_No.exe"))), (std::string("Yes")));
    EXPECT_EQ((file_name_check(std::string("M#1g"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("Yns"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("_mY@qOG6h"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("y8s9"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("1iFOnt5o"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("w77oGEbp4hnI"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("_#Ytx7"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("KYQ"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("9M0Qz3asmH2h"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("USyQvQG21kAv"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("I/563_No.e0xe"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("6"))), (std::string("No")));
    EXPECT_EQ((file_name_check(std::string("1I563_Yes3.exxe"))), (std::string("No")));
}

TEST(Probe, sum_squares_01) {
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -3, 17, -1, -15, 13, -1, 14, -14, -12, -5, 14, -14, 6, 13, 11, 16, 16, 4, 10, 28})), (20504));
    EXPECT_EQ((sum_squares(std::vector<int >{1, 4, 9})), (14));
    EXPECT_EQ((sum_squares(std::vector<int >{-56, -99, 1, 0, -2})), (3030));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -1, -1, -1, -1, -1, -1, -1, -1})), (-3));
    EXPECT_EQ((sum_squares(std::vector<int >{1, 2, 3})), (6));
    EXPECT_EQ((sum_squares(std::vector<int >{13, 2, -3})), (168));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -3, 17, -1, -15, 13, -1, 14, -14, -12, -5, 14, -14, 6, 13, 11, 16, 16, 4, 10, 0})), (-1448));
    EXPECT_EQ((sum_squares(std::vector<int >{1, 2, 3, 19})), (367));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -3, 17, -1, -15, 13, -1, 14, -14, -12, -5, 14, -14, 6, 13, 11, 16, 16, 4, 10})), (-1448));
    EXPECT_EQ((sum_squares(std::vector<int >{-15, 17, -11, 3030})), (9181131));
    EXPECT_EQ((sum_squares(std::vector<int >{-16, -9, -2, 36, 36, 26, -20, 25, -40, 20, -4, 12, -26, 35, 37})), (-14196));
    EXPECT_EQ((sum_squares(std::vector<int >{28, 4, 9})), (797));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, 0, 0, 0, 0, 0, 0, 0, -1, 9})), (81));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -1, 0, 0, 0, 0, 0, 0, -1})), (-1));
    EXPECT_EQ((sum_squares(std::vector<int >{-653, -27, -2, -12, 30, -8, 37})), (454885));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1448})), (2096701));
    EXPECT_EQ((sum_squares(std::vector<int >{-6, 14, 635, 12, 168, 9})), (4742470));
    EXPECT_EQ((sum_squares(std::vector<int >{880, 30, 16})), (774446));
    EXPECT_EQ((sum_squares(std::vector<int >{13, 11, -35})), (145));
    EXPECT_EQ((sum_squares(std::vector<int >{0})), (0));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -5, 2, -1, -5})), (-126));
    EXPECT_EQ((sum_squares(std::vector<int >{10, 23, -808, 3, -9, 592, -313})), (97156));
    EXPECT_EQ((sum_squares(std::vector<int >{29, 559, 2, 813, 19, 14, 16})), (669500));
    EXPECT_EQ((sum_squares(std::vector<int >{1, -20, 1, 1, 1, 1, 1, 1, 1})), (-12));
    EXPECT_EQ((sum_squares(std::vector<int >{4, 1, 9})), (26));
}

TEST(Probe, sum_squares_02) {
    EXPECT_EQ((sum_squares(std::vector<int >{-15})), (225));
    EXPECT_EQ((sum_squares(std::vector<int >{1, 4, 9, 4})), (30));
    EXPECT_EQ((sum_squares(std::vector<int >{1, 6, -4, 21, -1, -39, 287})), (82773));
    EXPECT_EQ((sum_squares(std::vector<int >{26})), (676));
    EXPECT_EQ((sum_squares(std::vector<int >{9, 4, 1})), (86));
    EXPECT_EQ((sum_squares(std::vector<int >{5})), (25));
    EXPECT_EQ((sum_squares(std::vector<int >{26, 28, -927, 36, 7, 19, -4})), (1451));
    EXPECT_EQ((sum_squares(std::vector<int >{-810, -3})), (656097));
    EXPECT_EQ((sum_squares(std::vector<int >{1, 4})), (5));
    EXPECT_EQ((sum_squares(std::vector<int >{-16, -9, -2, 36, 36, 26, -20, 25, -40, 20, 12, -26, 35, 37})), (-13704));
    EXPECT_EQ((sum_squares(std::vector<int >{12, 10, 5})), (159));
    EXPECT_EQ((sum_squares(std::vector<int >{-566, -2, -1, 26, -12, 3, 15, 100})), (319629));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, 0, 0, 0, 0, 0, 0, 0})), (1));
    EXPECT_EQ((sum_squares(std::vector<int >{-16, -1, 36, 0, 20, 271})), (8562));
    EXPECT_EQ((sum_squares(std::vector<int >{19})), (361));
    EXPECT_EQ((sum_squares(std::vector<int >{-16, -9, 36, 36, 26, -20, 25, -40, 20, -4, 12, -26, 35, 37})), (28984));
    EXPECT_EQ((sum_squares(std::vector<int >{-56, 24, 12345, 22, -1000, 23, -3})), (-999983979));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -1, -1, -1, -1, -1, -1, -1})), (-2));
    EXPECT_EQ((sum_squares(std::vector<int >{20, -1, -1, -1, -1, -1, -1, -1, -1})), (396));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, -5, 2, -1, -5, 17})), (-109));
    EXPECT_EQ((sum_squares(std::vector<int >{13, -56, -1, -1, -9})), (-616));
    EXPECT_EQ((sum_squares(std::vector<int >{19, -2, -718})), (-359));
    EXPECT_EQ((sum_squares(std::vector<int >{-1, 6, 14, 418, 10, 2, 691, 15})), (653243));
}

TEST(Probe, words_in_sentence_01) {
    EXPECT_EQ((words_in_sentence(std::string("lets go for swimming"))), (std::string("go for")));
    EXPECT_EQ((words_in_sentence(std::string("LG3f"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("Zv2GD6m0f"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("Di amHussein"))), (std::string("Di")));
    EXPECT_EQ((words_in_sentence(std::string("lets go for swimmin"))), (std::string("go for swimmin")));
    EXPECT_EQ((words_in_sentence(std::string("goT fAor it"))), (std::string("goT it")));
    EXPECT_EQ((words_in_sentence(std::string(" i I a Hussein"))), (std::string("Hussein")));
    EXPECT_EQ((words_in_sentence(std::string("Wj"))), (std::string("Wj")));
    EXPECT_EQ((words_in_sentence(std::string("ZY9ol 9"))), (std::string("ZY9ol")));
    EXPECT_EQ((words_in_sentence(std::string("amrd"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("lGNobYNFmRHN"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("lets go zfor swiWmintg"))), (std::string("go")));
    EXPECT_EQ((words_in_sentence(std::string("27cr9"))), (std::string("27cr9")));
    EXPECT_EQ((words_in_sentence(std::string("it7"))), (std::string("it7")));
    EXPECT_EQ((words_in_sentence(std::string("goQ to2r"))), (std::string("goQ")));
    EXPECT_EQ((words_in_sentence(std::string("4r5"))), (std::string("4r5")));
    EXPECT_EQ((words_in_sentence(std::string("This is a test"))), (std::string("is")));
    EXPECT_EQ((words_in_sentence(std::string("N4Uwipz14Asm"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("theret i npo place"))), (std::string("npo place")));
    EXPECT_EQ((words_in_sentence(std::string("izn"))), (std::string("izn")));
    EXPECT_EQ((words_in_sentence(std::string("here is"))), (std::string("is")));
    EXPECT_EQ((words_in_sentence(std::string("7OrzLILQO"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("1lu0zyXUVJV"))), (std::string("1lu0zyXUVJV")));
    EXPECT_EQ((words_in_sentence(std::string("hese is"))), (std::string("is")));
    EXPECT_EQ((words_in_sentence(std::string("XpKIaF"))), (std::string("")));
}

TEST(Probe, words_in_sentence_02) {
    EXPECT_EQ((words_in_sentence(std::string("3W"))), (std::string("3W")));
    EXPECT_EQ((words_in_sentence(std::string("Thi is a test"))), (std::string("Thi is")));
    EXPECT_EQ((words_in_sentence(std::string("lets go forKswimming"))), (std::string("go")));
    EXPECT_EQ((words_in_sentence(std::string("is"))), (std::string("is")));
    EXPECT_EQ((words_in_sentence(std::string("8sfw0u1"))), (std::string("8sfw0u1")));
    EXPECT_EQ((words_in_sentence(std::string("NrkUGr"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("E"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("FgoK fPor"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("go for"))), (std::string("go for")));
    EXPECT_EQ((words_in_sentence(std::string("i"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("cmBJJipQD"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("wtZqlTu"))), (std::string("wtZqlTu")));
    EXPECT_EQ((words_in_sentence(std::string("vP4OVu"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("her"))), (std::string("her")));
    EXPECT_EQ((words_in_sentence(std::string("QR"))), (std::string("QR")));
    EXPECT_EQ((words_in_sentence(std::string("ThsFis atest"))), (std::string("atest")));
    EXPECT_EQ((words_in_sentence(std::string(" jxlyean"))), (std::string("jxlyean")));
    EXPECT_EQ((words_in_sentence(std::string("gbo for i"))), (std::string("gbo for")));
    EXPECT_EQ((words_in_sentence(std::string(" RPa Y"))), (std::string("RPa")));
    EXPECT_EQ((words_in_sentence(std::string("there is no place available here"))), (std::string("there is no place")));
    EXPECT_EQ((words_in_sentence(std::string("here"))), (std::string("")));
    EXPECT_EQ((words_in_sentence(std::string("Thisis a etest"))), (std::string("etest")));
    EXPECT_EQ((words_in_sentence(std::string("there is no place availaXle ee"))), (std::string("there is no place ee")));
}

TEST(Probe, simplify_01) {
    EXPECT_EQ((simplify(std::string("1/5"), std::string("3/1"))), (false));
    EXPECT_EQ((simplify(std::string("2/3"), std::string("/6"))), (true));
    EXPECT_EQ((simplify(std::string("2b/4"), std::string("50/10"))), (false));
    EXPECT_EQ((simplify(std::string("1/5"), std::string("6H/5"))), (false));
    EXPECT_EQ((simplify(std::string("2/3"), std::string("0/10"))), (true));
    EXPECT_EQ((simplify(std::string("6C/1"), std::string("11/6"))), (true));
}

TEST(Probe, order_by_points_01) {
    EXPECT_EQ((order_by_points(std::vector<int >{21, 11, 24, 7, 21, -4, 37, -21})), (std::vector<int >{-4, -21, 11, 21, 21, 24, 7, 37}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, 2, 3, 4, 24, 6, 7, 8, 9, 10, 11})), (std::vector<int >{1, 10, 2, 11, 3, 4, 24, 6, 7, 8, 9}));
    EXPECT_EQ((order_by_points(std::vector<int >{1234, 423, 463, 145, 423, 423, 2, 53, 6, 37, 3457, 3, 56, 0, 46})), (std::vector<int >{0, 2, 3, 6, 53, 423, 423, 423, 1234, 145, 37, 46, 56, 463, 3457}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, -11, -7, 43, 54, -98, 2, -3})), (std::vector<int >{-7, -3, -98, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{2, 207, 1234, 269, 1232, 18})), (std::vector<int >{2, 1232, 207, 18, 1234, 269}));
    EXPECT_EQ((order_by_points(std::vector<int >{1234, 53, 463, 145, 2, 423, 423, 423, 6, 37, 3457, 3, 56, 0, 46})), (std::vector<int >{0, 2, 3, 6, 53, 423, 423, 423, 1234, 145, 37, 46, 56, 463, 3457}));
    EXPECT_EQ((order_by_points(std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((order_by_points(std::vector<int >{423, 423, 463, 145, 2, 423, 1234, 53, 6, 37, 3457, 3, 56, 0, 46})), (std::vector<int >{0, 2, 3, 6, 53, 423, 423, 423, 145, 1234, 37, 46, 56, 463, 3457}));
    EXPECT_EQ((order_by_points(std::vector<int >{-76, -21, 0, 6, 23, 6, 4})), (std::vector<int >{-76, -21, 0, 4, 23, 6, 6}));
    EXPECT_EQ((order_by_points(std::vector<int >{-3, -32, -98, -11, 1, 43, 54})), (std::vector<int >{-3, -32, -98, -11, 1, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{-3, -32, -98, -11, 1, 2, 43, 54, -2})), (std::vector<int >{-3, -2, -32, -98, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, -11, -32, 43, -4, -98, 2, -3})), (std::vector<int >{-4, -3, -32, -98, -11, 1, 2, 43}));
    EXPECT_EQ((order_by_points(std::vector<int >{-3, 0, -98, -11, 1, 2, 43, 54})), (std::vector<int >{-3, -98, 0, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, -11, -32, 43, 54, -98, 2, -3, -3})), (std::vector<int >{-3, -3, -32, -98, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{8})), (std::vector<int >{8}));
    EXPECT_EQ((order_by_points(std::vector<int >{100, 797})), (std::vector<int >{100, 797}));
    EXPECT_EQ((order_by_points(std::vector<int >{-1, -11, 1, -12, 11})), (std::vector<int >{-1, -11, 1, -12, 11}));
    EXPECT_EQ((order_by_points(std::vector<int >{30, 3, 9, 3, 7, 10, 7})), (std::vector<int >{10, 30, 3, 3, 7, 7, 9}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, -1, 11, -11, -12})), (std::vector<int >{-1, -11, 1, -12, 11}));
    EXPECT_EQ((order_by_points(std::vector<int >{-3, -11, -32, 43, 54, -98, 2, 1})), (std::vector<int >{-3, -32, -98, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{24, 37, -98, -135, 2, 2, -32, -8})), (std::vector<int >{-8, -98, -32, 2, 2, 24, -135, 37}));
    EXPECT_EQ((order_by_points(std::vector<int >{0, 2, 3, 6, 53, 423, 423, 423, 1234, 145, 37, 46, 56, 463, 3457, 1})), (std::vector<int >{0, 1, 2, 3, 6, 53, 423, 423, 423, 1234, 145, 37, 46, 56, 463, 3457}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, -11, -32, 43, 54, -98, -3})), (std::vector<int >{-3, -32, -98, -11, 1, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{2, -5, 0, -120, 2, 919})), (std::vector<int >{-5, 0, -120, 2, 2, 919}));
    EXPECT_EQ((order_by_points(std::vector<int >{-1, 15, 13, 0, 15, 5})), (std::vector<int >{-1, 0, 13, 5, 15, 15}));
}

TEST(Probe, order_by_points_02) {
    EXPECT_EQ((order_by_points(std::vector<int >{0, 6, -21, -76, 6, 23, 4})), (std::vector<int >{-21, -76, 0, 4, 23, 6, 6}));
    EXPECT_EQ((order_by_points(std::vector<int >{23, 3, 10, 3, 13})), (std::vector<int >{10, 3, 3, 13, 23}));
    EXPECT_EQ((order_by_points(std::vector<int >{-98, -32, -3, -11, 1, 2, 43, 54})), (std::vector<int >{-3, -98, -32, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{-10, 2})), (std::vector<int >{-10, 2}));
    EXPECT_EQ((order_by_points(std::vector<int >{26, 25, -3, 3, -102, -98, 54})), (std::vector<int >{-3, -98, -102, 3, 25, 26, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, -11, -32, 43, 54, -98, 2, -3, 10})), (std::vector<int >{-3, -32, -98, -11, 1, 10, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{4, 27, 22, 53, 4})), (std::vector<int >{4, 22, 4, 53, 27}));
    EXPECT_EQ((order_by_points(std::vector<int >{-78, 3, -11})), (std::vector<int >{-11, -78, 3}));
    EXPECT_EQ((order_by_points(std::vector<int >{-989, 463})), (std::vector<int >{-989, 463}));
    EXPECT_EQ((order_by_points(std::vector<int >{1234, -389, 6})), (std::vector<int >{6, 1234, -389}));
    EXPECT_EQ((order_by_points(std::vector<int >{-3, -32, 43, -11, 1, 2, -98, 54})), (std::vector<int >{-3, -32, -98, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{-13, 424, 419})), (std::vector<int >{-13, 424, 419}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, -11, -32, 43, 54, -98, 2, -3})), (std::vector<int >{-3, -32, -98, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{8, 7, 24, 21, 461, -98, 4, -12})), (std::vector<int >{-98, -12, 21, 4, 24, 7, 8, 461}));
    EXPECT_EQ((order_by_points(std::vector<int >{-3, -32, -98, -11, 1, 2, 43, 54, 2})), (std::vector<int >{-3, -32, -98, -11, 1, 2, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{-3, -32, 2, -11, 1, -98, 43, 54})), (std::vector<int >{-3, -32, -98, -11, 1, 2, 43, 54}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, 10, 2, 11, 3, 5, 4, 6, 7, 8, 9})), (std::vector<int >{1, 10, 2, 11, 3, 4, 5, 6, 7, 8, 9}));
    EXPECT_EQ((order_by_points(std::vector<int >{0, 2, 3, 6, 53, 423, 423, 423, 1234, 145, 37, 46, 56, 463, 3457, 63})), (std::vector<int >{0, 2, 3, 6, 53, 423, 423, 423, 63, 1234, 145, 37, 46, 56, 463, 3457}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, 10, 2, 11, 3, 4, 5, 6, 7, 8, 9})), (std::vector<int >{1, 10, 2, 11, 3, 4, 5, 6, 7, 8, 9}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, 11, 0, -11, -12})), (std::vector<int >{0, -11, 1, -12, 11}));
    EXPECT_EQ((order_by_points(std::vector<int >{20, -496})), (std::vector<int >{20, -496}));
    EXPECT_EQ((order_by_points(std::vector<int >{1, 9, 14, -2, -1, -12, 26, 23})), (std::vector<int >{-2, -1, 1, -12, 14, 23, 26, 9}));
    EXPECT_EQ((order_by_points(std::vector<int >{56, 351, -3, 43, 43, 463})), (std::vector<int >{-3, 43, 43, 351, 56, 463}));
}
