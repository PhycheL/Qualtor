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

TEST(Characterization, specialFilter_01) {
    EXPECT_EQ((specialFilter(std::vector<int >{71, -2, -33, 75, 21, 19})), (3));
    EXPECT_EQ((specialFilter(std::vector<int >{120, -238, 26, 99999, -3, 33, -1})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{15, -73, 14, -15, 99999})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{15, -73, 14, -15})), (1));
    EXPECT_EQ((specialFilter(std::vector<int >{33, -2, -3, 45, 21, 109})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{1, 544, -33, 69, 10})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{43, 21, 93, 125, 121, 109})), (4));
    EXPECT_EQ((specialFilter(std::vector<int >{5, -2, 1, -5})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{15, 4, 14, -15})), (1));
    EXPECT_EQ((specialFilter(std::vector<int >{19, 7, 19, 21})), (2));
    EXPECT_EQ((specialFilter(std::vector<int >{0, -5, -116, 4, -10, 20, 45, -1})), (0));
    EXPECT_EQ((specialFilter(std::vector<int >{})), (0));
}

TEST(Characterization, get_matrix_triples_01) {
    EXPECT_EQ((get_matrix_triples(20)), (321));
    EXPECT_EQ((get_matrix_triples(6)), (4));
    EXPECT_EQ((get_matrix_triples(25)), (736));
    EXPECT_EQ((get_matrix_triples(2)), (0));
    EXPECT_EQ((get_matrix_triples(7)), (10));
    EXPECT_EQ((get_matrix_triples(24)), (616));
    EXPECT_EQ((get_matrix_triples(3)), (0));
    EXPECT_EQ((get_matrix_triples(36)), (2244));
    EXPECT_EQ((get_matrix_triples(21)), (399));
    EXPECT_EQ((get_matrix_triples(682)), (17519860));
    EXPECT_EQ((get_matrix_triples(523)), (7886898));
    EXPECT_EQ((get_matrix_triples(28)), (1053));
}

TEST(Characterization, bf_01) {
    EXPECT_EQ((bf(std::string(""), std::string("Jupiter"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Satn"), std::string("EarBth"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("DLiu3"), std::string("Saturn"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Q0UPUfYhv"), std::string("Ntsne"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("VQg"), std::string("Q7GacVqoTf"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("wJupiter"), std::string("Mercury"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("ZKNpJ7SPbP"), std::string("H ci wExwZ"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Q"), std::string("Earth"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Makemasve"), std::string("U8XIDbX5 f"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Fupiter"), std::string("Mercury"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Zu"), std::string("Mercury"))), (std::vector<std::string >{}));
    EXPECT_EQ((bf(std::string("Venus"), std::string("gMerTs"))), (std::vector<std::string >{}));
}

TEST(Characterization, sorted_list_sum_01) {
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("ab"), std::string("cd")})), (std::vector<std::string >{std::string("ab"), std::string("cd")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("AI"), std::string("asdf"), std::string("school")})), (std::vector<std::string >{std::string("AI"), std::string("asdf"), std::string("school")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("a"), std::string("b"), std::string(""), std::string("c"), std::string("c"), std::string("a")})), (std::vector<std::string >{std::string("")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("abcd"), std::string("d")})), (std::vector<std::string >{std::string("abcd")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("aa"), std::string("a"), std::string("aaa")})), (std::vector<std::string >{std::string("aa")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("AI"), std::string("ai"), std::string("au"), std::string("kdjbR2")})), (std::vector<std::string >{std::string("AI"), std::string("ai"), std::string("au"), std::string("kdjbR2")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("d"), std::string("dcba"), std::string("abcd"), std::string("a")})), (std::vector<std::string >{std::string("abcd"), std::string("dcba")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("AI"), std::string("ai"), std::string("au")})), (std::vector<std::string >{std::string("AI"), std::string("ai"), std::string("au")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{})), (std::vector<std::string >{}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("dcba"), std::string("dd"), std::string("lU"), std::string("abcd"), std::string("ai")})), (std::vector<std::string >{std::string("ai"), std::string("dd"), std::string("lU"), std::string("abcd"), std::string("dcba")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("AI"), std::string("school"), std::string("asdf")})), (std::vector<std::string >{std::string("AI"), std::string("asdf"), std::string("school")}));
    EXPECT_EQ((sorted_list_sum(std::vector<std::string >{std::string("H7 IE2fplY"), std::string("aaaa"), std::string(""), std::string("dcbA")})), (std::vector<std::string >{std::string(""), std::string("aaaa"), std::string("dcbA"), std::string("H7 IE2fplY")}));
}

TEST(Characterization, x_or_y_01) {
    EXPECT_EQ((x_or_y(-1, 3, 2)), (2));
    EXPECT_EQ((x_or_y(12, 16, -3)), (-3));
    EXPECT_EQ((x_or_y(-446, -434, 19)), (19));
    EXPECT_EQ((x_or_y(-121, 3, 27)), (27));
    EXPECT_EQ((x_or_y(99999, 12345, 4)), (4));
    EXPECT_EQ((x_or_y(1, 249, 1245)), (1245));
    EXPECT_EQ((x_or_y(15, 99999, 20)), (20));
    EXPECT_EQ((x_or_y(-1, -792, 8)), (8));
    EXPECT_EQ((x_or_y(12, 24, 22)), (22));
    EXPECT_EQ((x_or_y(12, 22, 1236)), (1236));
    EXPECT_EQ((x_or_y(1000, 0, 4)), (4));
    EXPECT_EQ((x_or_y(12, 0, 11)), (11));
}

TEST(Characterization, double_the_difference_01) {
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 0.200000003f, 0.100000001f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.200000003f, 3.0f, 5.0f})), (34LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-0.800000012f, 5.07000017f, 10.0f, 0.0f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.200000003f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 0.200000003f, 0.300000012f, -10.6999998f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{-20.0f, -18.5f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{18.5f, -14.3000002f, 9.80000019f, 0.0f})), (361LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f, 0.300000012f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{9.60000038f, -17.3999996f, -13.1999998f, 6.71000004f, 1.79999995f, 0.100000001f, -8.14999962f, 0.200000003f})), (49LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.600000024f, 0.300000012f})), (1LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{0.100000001f})), (0LL));
    EXPECT_EQ((double_the_difference(std::vector<float >{4.0999999f, -2.0f, -13.6999998f, 2.0f, 1.80999994f, 10.0f})), (0LL));
}

TEST(Characterization, compare_01) {
    EXPECT_EQ((compare(std::vector<int >{-8, -4, 574}, std::vector<int >{-1, 2, 3, 4})), (std::vector<int >{7, 6, 571}));
    EXPECT_EQ((compare(std::vector<int >{17}, std::vector<int >{4, 6})), (std::vector<int >{13}));
    EXPECT_EQ((compare(std::vector<int >{2, -7, 14, 5, 23}, std::vector<int >{3, -737, -3, 85, 6, -978, 25})), (std::vector<int >{1, 730, 17, 80, 17}));
    EXPECT_EQ((compare(std::vector<int >{2, 18, 6}, std::vector<int >{0, 0, 0, 5, 3, 3})), (std::vector<int >{2, 18, 6}));
    EXPECT_EQ((compare(std::vector<int >{-2, 4, 6}, std::vector<int >{1, 2, -1, 5})), (std::vector<int >{3, 2, 7}));
    EXPECT_EQ((compare(std::vector<int >{0, 5, 2, 0, 0, 4}, std::vector<int >{0, 5, 0, 0, 0, 4})), (std::vector<int >{0, 0, 2, 0, 0, 0}));
    EXPECT_EQ((compare(std::vector<int >{28}, std::vector<int >{2, 88, -3, 8, 24, 6, -1, 4})), (std::vector<int >{26}));
    EXPECT_EQ((compare(std::vector<int >{14}, std::vector<int >{1, 2})), (std::vector<int >{13}));
    EXPECT_EQ((compare(std::vector<int >{0, 5, 0, 0, 0, 4}, std::vector<int >{-2, -3, 2, 1, 0, -911, -1, 2})), (std::vector<int >{2, 8, 2, 1, 0, 915}));
    EXPECT_EQ((compare(std::vector<int >{0, -389, 0, 0, 3, 3}, std::vector<int >{1, 2, 3, 4, 2, -2})), (std::vector<int >{1, 391, 3, 4, 1, 5}));
    EXPECT_EQ((compare(std::vector<int >{2, 3}, std::vector<int >{4, 1, 1, 0, 0, -2})), (std::vector<int >{2, 2}));
    EXPECT_EQ((compare(std::vector<int >{-3, -3, -7, 28, 4, 4, 221, -1}, std::vector<int >{108, 8, -128, 0, 21, 6, -4, 1})), (std::vector<int >{111, 11, 121, 28, 17, 2, 225, 2}));
}

TEST(Characterization, Strongest_Extension_01) {
    EXPECT_EQ((Strongest_Extension(std::string("T"), std::vector<std::string >{std::string("uEeU3YK"), std::string("U"), std::string("iEN"), std::string("eIGHt8OKe")})), (std::string("T.uEeU3YK")));
    EXPECT_EQ((Strongest_Extension(std::string("MIp2v9 R"), std::vector<std::string >{std::string("HhAas"), std::string("okIWILL123"), std::string("WorkOut"), std::string("Fails"), std::string("-_-")})), (std::string("MIp2v9 R.okIWILL123")));
    EXPECT_EQ((Strongest_Extension(std::string("Bb"), std::vector<std::string >{std::string("eMptY"), std::string("t"), std::string("(nothing"), std::string("zeR00"), std::string("NuLl__"), std::string("123NoooneB321")})), (std::string("Bb.NuLl__")));
    EXPECT_EQ((Strongest_Extension(std::string("Sp"), std::vector<std::string >{std::string("671235"), std::string("Bb")})), (std::string("Sp.671235")));
    EXPECT_EQ((Strongest_Extension(std::string("jw-sGrkj0A"), std::vector<std::string >{std::string("AA"), std::string("Be"), std::string("CC")})), (std::string("jw-sGrkj0A.AA")));
    EXPECT_EQ((Strongest_Extension(std::string("WorkOu1t"), std::vector<std::string >{std::string("HhAas"), std::string("okIWILL123"), std::string("Fails"), std::string("-_-")})), (std::string("WorkOu1t.okIWILL123")));
    EXPECT_EQ((Strongest_Extension(std::string("fbnNNalLLly"), std::vector<std::string >{std::string("671235")})), (std::string("fbnNNalLLly.671235")));
    EXPECT_EQ((Strongest_Extension(std::string("KOFljkGnBCC"), std::vector<std::string >{std::string("Ta"), std::string(""), std::string("t234An"), std::string("cosSo")})), (std::string("KOFljkGnBCC.Ta")));
    EXPECT_EQ((Strongest_Extension(std::string("YmeRore.okIWILL123"), std::vector<std::string >{std::string("tEN"), std::string("niNE"), std::string("eIGHt8OKe")})), (std::string("YmeRore.okIWILL123.eIGHt8OKe")));
    EXPECT_EQ((Strongest_Extension(std::string("S_WoDW"), std::vector<std::string >{std::string("AA"), std::string("Be"), std::string("CC")})), (std::string("S_WoDW.AA")));
    EXPECT_EQ((Strongest_Extension(std::string("-p-pH_-y"), std::vector<std::string >{std::string("Die"), std::string("NowW"), std::string("Wow"), std::string("WoW"), std::string("TAR")})), (std::string("-p-pH_-y.TAR")));
    EXPECT_EQ((Strongest_Extension(std::string("k1L3"), std::vector<std::string >{std::string("t"), std::string("eMptY"), std::string("zeR00"), std::string("NuLl__"), std::string("123NoooneB321")})), (std::string("k1L3.NuLl__")));
}
