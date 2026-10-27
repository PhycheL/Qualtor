// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_04.h"

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

TEST(Probe, factorize_01) {
    EXPECT_EQ((factorize(544)), (std::vector<int >{2, 2, 2, 2, 2, 17}));
    EXPECT_EQ((factorize(1)), (std::vector<int >{1}));
    EXPECT_EQ((factorize(3)), (std::vector<int >{3}));
    EXPECT_EQ((factorize(27)), (std::vector<int >{3, 3, 3}));
    EXPECT_EQ((factorize(5)), (std::vector<int >{5}));
    EXPECT_EQ((factorize(21)), (std::vector<int >{3, 7}));
    EXPECT_EQ((factorize(99999)), (std::vector<int >{3, 3, 41, 271}));
    EXPECT_EQ((factorize(-116)), (std::vector<int >{-116}));
    EXPECT_EQ((factorize(-10)), (std::vector<int >{-10}));
    EXPECT_EQ((factorize(9)), (std::vector<int >{3, 3}));
    EXPECT_EQ((factorize(671)), (std::vector<int >{11, 61}));
    EXPECT_EQ((factorize(428)), (std::vector<int >{2, 2, 107}));
    EXPECT_EQ((factorize(258)), (std::vector<int >{2, 3, 43}));
    EXPECT_EQ((factorize(20)), (std::vector<int >{2, 2, 5}));
    EXPECT_EQ((factorize(24)), (std::vector<int >{2, 2, 2, 3}));
    EXPECT_EQ((factorize(-7)), (std::vector<int >{-7}));
    EXPECT_EQ((factorize(-3)), (std::vector<int >{-3}));
    EXPECT_EQ((factorize(-5)), (std::vector<int >{-5}));
    EXPECT_EQ((factorize(-6)), (std::vector<int >{-6}));
    EXPECT_EQ((factorize(1000)), (std::vector<int >{2, 2, 2, 5, 5, 5}));
    EXPECT_EQ((factorize(13)), (std::vector<int >{13}));
    EXPECT_EQ((factorize(70)), (std::vector<int >{2, 5, 7}));
    EXPECT_EQ((factorize(6)), (std::vector<int >{2, 3}));
    EXPECT_EQ((factorize(71)), (std::vector<int >{71}));
    EXPECT_EQ((factorize(2)), (std::vector<int >{2}));
}

TEST(Probe, factorize_02) {
    EXPECT_EQ((factorize(22)), (std::vector<int >{2, 11}));
    EXPECT_EQ((factorize(12345)), (std::vector<int >{3, 5, 823}));
    EXPECT_EQ((factorize(199)), (std::vector<int >{199}));
    EXPECT_EQ((factorize(820)), (std::vector<int >{2, 2, 5, 41}));
    EXPECT_EQ((factorize(18)), (std::vector<int >{2, 3, 3}));
    EXPECT_EQ((factorize(17)), (std::vector<int >{17}));
    EXPECT_EQ((factorize(25)), (std::vector<int >{5, 5}));
    EXPECT_EQ((factorize(300)), (std::vector<int >{2, 2, 3, 5, 5}));
    EXPECT_EQ((factorize(16)), (std::vector<int >{2, 2, 2, 2}));
    EXPECT_EQ((factorize(12)), (std::vector<int >{2, 2, 3}));
    EXPECT_EQ((factorize(-557)), (std::vector<int >{-557}));
    EXPECT_EQ((factorize(15)), (std::vector<int >{3, 5}));
    EXPECT_EQ((factorize(-9)), (std::vector<int >{-9}));
    EXPECT_EQ((factorize(-777)), (std::vector<int >{-777}));
    EXPECT_EQ((factorize(100)), (std::vector<int >{2, 2, 5, 5}));
    EXPECT_EQ((factorize(10)), (std::vector<int >{2, 5}));
    EXPECT_EQ((factorize(14)), (std::vector<int >{2, 7}));
    EXPECT_EQ((factorize(-8)), (std::vector<int >{-8}));
    EXPECT_EQ((factorize(895)), (std::vector<int >{5, 179}));
    EXPECT_EQ((factorize(801)), (std::vector<int >{3, 3, 89}));
    EXPECT_EQ((factorize(-508)), (std::vector<int >{-508}));
    EXPECT_EQ((factorize(114)), (std::vector<int >{2, 3, 19}));
    EXPECT_EQ((factorize(30)), (std::vector<int >{2, 3, 5}));
}

TEST(Probe, remove_duplicates_01) {
    EXPECT_EQ((remove_duplicates(std::vector<int >{3, 4})), (std::vector<int >{3, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{})), (std::vector<int >{}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{143})), (std::vector<int >{143}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{4, 19, 6, -1, 3})), (std::vector<int >{4, 19, 6, -1, 3}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 4, 5})), (std::vector<int >{1, 4, 5}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{6, 7, 4})), (std::vector<int >{6, 7, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{2})), (std::vector<int >{2}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 3})), (std::vector<int >{1, 2, 3}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 3, 2, 4, 3, 5})), (std::vector<int >{1, 4, 5}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{2, -5, 29, -990})), (std::vector<int >{2, -5, 29, -990}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 489, 5})), (std::vector<int >{1, 489, 5}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{469, 4, 21})), (std::vector<int >{469, 4, 21}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{846, 2, 4, 274, 235})), (std::vector<int >{846, 2, 4, 274, 235}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{-835, 543, 5, 30})), (std::vector<int >{-835, 543, 5, 30}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, -573, 2, 4, 3, 5})), (std::vector<int >{1, -573, 4, 3, 5}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{3, 2, 1, 2, 4})), (std::vector<int >{3, 1, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 3, 4, -465})), (std::vector<int >{1, 2, 3, 4, -465}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{-104, -779})), (std::vector<int >{-104, -779}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{5, -739, 29, 26, 0})), (std::vector<int >{5, -739, 29, 26, 0}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 3, 4})), (std::vector<int >{1, 3, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{4, 3, -7, 3, 5, 6, 26})), (std::vector<int >{4, -7, 5, 6, 26}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{610})), (std::vector<int >{610}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 3, 4, -5})), (std::vector<int >{1, 2, 3, 4, -5}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 8, 3, 5, 2, 4, 0})), (std::vector<int >{1, 8, 3, 5, 2, 4, 0}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{-7, 273, 29, 11, 3, 3})), (std::vector<int >{-7, 273, 29, 11}));
}

TEST(Probe, remove_duplicates_02) {
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 3})), (std::vector<int >{1, 3}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{82, 3})), (std::vector<int >{82, 3}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 4})), (std::vector<int >{1, 2, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 3, 4, 0})), (std::vector<int >{1, 3, 4, 0}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{4, 11})), (std::vector<int >{4, 11}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 3, 2, 4})), (std::vector<int >{1, 3, 2, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{-1, 3, 4})), (std::vector<int >{-1, 3, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 3, 22})), (std::vector<int >{1, 2, 3, 22}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{27})), (std::vector<int >{27}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{-571, 0, 5, 4, 11, -1})), (std::vector<int >{-571, 0, 5, 4, 11, -1}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{495, 189, 0})), (std::vector<int >{495, 189, 0}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{17})), (std::vector<int >{17}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{22, 4, -5})), (std::vector<int >{22, 4, -5}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{644})), (std::vector<int >{644}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{27, -1, 0, -617, -2, 5, 5})), (std::vector<int >{27, -1, 0, -617, -2}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{0, 1, 4, 1, 14, 19})), (std::vector<int >{0, 4, 14, 19}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{19, 3, 1, 5, 4})), (std::vector<int >{19, 3, 1, 5, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{3, 157, 28})), (std::vector<int >{3, 157, 28}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 5})), (std::vector<int >{1, 5}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{-5})), (std::vector<int >{-5}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{12, 2, 3, 2, 4})), (std::vector<int >{12, 3, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{-8})), (std::vector<int >{-8}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{4})), (std::vector<int >{4}));
}

TEST(Probe, filp_case_01) {
    EXPECT_EQ((filp_case(std::string("o"))), (std::string("O")));
    EXPECT_EQ((filp_case(std::string("7tMe7o8ti8"))), (std::string("7TmE7O8TI8")));
    EXPECT_EQ((filp_case(std::string("A"))), (std::string("a")));
    EXPECT_EQ((filp_case(std::string("Hello!"))), (std::string("hELLO!")));
    EXPECT_EQ((filp_case(std::string("Hep2lo"))), (std::string("hEP2LO")));
    EXPECT_EQ((filp_case(std::string("ozQRD1ZKzh"))), (std::string("OZqrd1zkZH")));
    EXPECT_EQ((filp_case(std::string("tHESE VIOLENT DELIYHTS HAVE VIOLENT ENDS"))), (std::string("These violent deliyhts have violent ends")));
    EXPECT_EQ((filp_case(std::string(" k"))), (std::string(" K")));
    EXPECT_EQ((filp_case(std::string("h!ELG0O!"))), (std::string("H!elg0o!")));
    EXPECT_EQ((filp_case(std::string("HelE4o"))), (std::string("hELe4O")));
    EXPECT_EQ((filp_case(std::string("95InSx53LuH"))), (std::string("95iNsX53lUh")));
    EXPECT_EQ((filp_case(std::string("i"))), (std::string("I")));
    EXPECT_EQ((filp_case(std::string("S!"))), (std::string("s!")));
    EXPECT_EQ((filp_case(std::string("Helo"))), (std::string("hELO")));
    EXPECT_EQ((filp_case(std::string("hELhO"))), (std::string("HelHo")));
    EXPECT_EQ((filp_case(std::string("HElhlo!"))), (std::string("heLHLO!")));
    EXPECT_EQ((filp_case(std::string("AF15"))), (std::string("af15")));
    EXPECT_EQ((filp_case(std::string("qRqsTxn"))), (std::string("QrQStXN")));
    EXPECT_EQ((filp_case(std::string("l2"))), (std::string("L2")));
    EXPECT_EQ((filp_case(std::string("u"))), (std::string("U")));
    EXPECT_EQ((filp_case(std::string("tHESE VIOLENT DELIGHTS HAVE IOLENJT EzNDS"))), (std::string("These violent delights have iolenjt eZnds")));
    EXPECT_EQ((filp_case(std::string("fihPNZaWcGkc"))), (std::string("FIHpnzAwCgKC")));
    EXPECT_EQ((filp_case(std::string("PYVeNQzRl"))), (std::string("pyvEnqZrL")));
    EXPECT_EQ((filp_case(std::string("Theshe violent delights have violent ends"))), (std::string("tHESHE VIOLENT DELIGHTS HAVE VIOLENT ENDS")));
    EXPECT_EQ((filp_case(std::string("Hell5o"))), (std::string("hELL5O")));
}

TEST(Probe, filp_case_02) {
    EXPECT_EQ((filp_case(std::string("u2cyq0"))), (std::string("U2CYQ0")));
    EXPECT_EQ((filp_case(std::string("9wg0wR"))), (std::string("9WG0Wr")));
    EXPECT_EQ((filp_case(std::string("tHESE VIOLENkT DEEGHTS HAVE VIOLENT ENDS"))), (std::string("These violenKt deeghts have violent ends")));
    EXPECT_EQ((filp_case(std::string("HewloS!"))), (std::string("hEWLOs!")));
    EXPECT_EQ((filp_case(std::string("nHESECVIOLENT DELsGHTS HAVE VIOLENT ENDS"))), (std::string("Nhesecviolent delSghts have violent ends")));
    EXPECT_EQ((filp_case(std::string("tHLSE VIOLENT DELIGHTS HAVE VIOLENT ENDS"))), (std::string("Thlse violent delights have violent ends")));
    EXPECT_EQ((filp_case(std::string("delloio!"))), (std::string("DELLOIO!")));
    EXPECT_EQ((filp_case(std::string("hese viol5nt delights have violent ends"))), (std::string("HESE VIOL5NT DELIGHTS HAVE VIOLENT ENDS")));
    EXPECT_EQ((filp_case(std::string("hELGO"))), (std::string("Helgo")));
    EXPECT_EQ((filp_case(std::string("hEJAO"))), (std::string("Hejao")));
    EXPECT_EQ((filp_case(std::string("k"))), (std::string("K")));
    EXPECT_EQ((filp_case(std::string("HPlloT!"))), (std::string("hpLLOt!")));
    EXPECT_EQ((filp_case(std::string("UifPw"))), (std::string("uIFpW")));
    EXPECT_EQ((filp_case(std::string("vm"))), (std::string("VM")));
    EXPECT_EQ((filp_case(std::string("gsAGbwsPLUb"))), (std::string("GSagBWSpluB")));
    EXPECT_EQ((filp_case(std::string("MUz"))), (std::string("muZ")));
    EXPECT_EQ((filp_case(std::string("I"))), (std::string("i")));
    EXPECT_EQ((filp_case(std::string("W"))), (std::string("w")));
    EXPECT_EQ((filp_case(std::string("hELULO"))), (std::string("Helulo")));
    EXPECT_EQ((filp_case(std::string("xXby"))), (std::string("XxBY")));
    EXPECT_EQ((filp_case(std::string("AGxG"))), (std::string("agXg")));
    EXPECT_EQ((filp_case(std::string("WMw8mv0bt"))), (std::string("wmW8MV0BT")));
    EXPECT_EQ((filp_case(std::string("HKcuMT 6"))), (std::string("hkCUmt 6")));
}

TEST(Probe, concatenate_01) {
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("xyz"), std::string("y"), std::string("z")})), (std::string("xyzyz")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("b")})), (std::string("b")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("xy4zwk")})), (std::string("xy4zwk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("HFVldt"), std::string("w"), std::string("k")})), (std::string("xyHFVldtwk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z"), std::string("DTPei")})), (std::string("xyzDTPei")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("c"), std::string("b"), std::string("a")})), (std::string("cba")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("L"), std::string("w"), std::string("a"), std::string("aZxc")})), (std::string("LwaaZxc")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("c")})), (std::string("c")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("k"), std::string("87"), std::string(""), std::string("f"), std::string("abc"), std::string("oY2"), std::string("a")})), (std::string("k87fabcoY2a")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z"), std::string("w"), std::string("k"), std::string("abc")})), (std::string("xyzwkabc")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("xyz"), std::string("x"), std::string("kV1g"), std::string("x")})), (std::string("xyzxkV1gx")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("a"), std::string("c"), std::string("b")})), (std::string("acb")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("y"), std::string("z"), std::string("y"), std::string("k"), std::string(""), std::string("")})), (std::string("yzyk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("NmykU"), std::string("y"), std::string("z")})), (std::string("NmykUyz")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("n"), std::string("aHd"), std::string("a")})), (std::string("naHda")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("xyz"), std::string("xyzwk"), std::string("dyhzu"), std::string("fy"), std::string("8ZraXhsVGdAh")})), (std::string("xyzxyzwkdyhzufy8ZraXhsVGdAh")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("y"), std::string("abc")})), (std::string("yabc")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("Q")})), (std::string("Q")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("xyzwk")})), (std::string("xyxyzwk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("a"), std::string("b"), std::string("c"), std::string("xyzwk")})), (std::string("abcxyzwk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("r"), std::string("B"), std::string("cytrC6")})), (std::string("rBcytrC6")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("a"), std::string("yzwk"), std::string("K")})), (std::string("ayzwkK")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("5ui"), std::string("e"), std::string("TMx77PQ"), std::string(""), std::string("T"), std::string("")})), (std::string("5uieTMx77PQT")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y")})), (std::string("xy")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("a"), std::string("b")})), (std::string("ab")));
}

TEST(Probe, concatenate_02) {
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("y"), std::string("z")})), (std::string("yz")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("61")})), (std::string("61")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("v54NCPT bqYg"), std::string("7w"), std::string("0"), std::string("f")})), (std::string("v54NCPT bqYg7w0f")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("tUCg91Q e")})), (std::string("tUCg91Q e")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("mhNhXdhR"), std::string(" L3zc4hie7"), std::string("c"), std::string(""), std::string("h"), std::string("ycwZk")})), (std::string("mhNhXdhR L3zc4hie7chycwZk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("xyrw"), std::string("xyGz")})), (std::string("xyrwxyGz")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z"), std::string("xyz")})), (std::string("xyzxyz")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("Uw"), std::string("Hv")})), (std::string("UwHv")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("ya")})), (std::string("ya")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x")})), (std::string("x")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("LXAzCtqj"), std::string("x")})), (std::string("LXAzCtqjx")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("kT uBN8mfxH"), std::string("4gTR2KXk"), std::string("y"), std::string("w"), std::string("6"), std::string("5ZSgqr"), std::string(""), std::string("xyz")})), (std::string("kT uBN8mfxH4gTR2KXkyw65ZSgqrxyz")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("hN")})), (std::string("hN")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z"), std::string("w"), std::string("k"), std::string("")})), (std::string("xyzwk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("abpyc"), std::string("y"), std::string("z")})), (std::string("abpycyz")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z"), std::string("q")})), (std::string("xyzq")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("")})), (std::string("")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string(""), std::string("MeFBOLa"), std::string("X7")})), (std::string("MeFBOLaX7")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string(""), std::string("abc"), std::string("xy"), std::string("PLY OL du"), std::string("x"), std::string("va7GoZCB"), std::string("5GFhTOd")})), (std::string("abcxyPLY OL duxva7GoZCB5GFhTOd")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("q"), std::string("v"), std::string("y"), std::string("C"), std::string("b"), std::string("7XGAV"), std::string("xyzwk"), std::string("hx0z")})), (std::string("qvyCb7XGAVxyzwkhx0z")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("o"), std::string("Mz"), std::string("c"), std::string("fupevI"), std::string("xyzwk"), std::string("E0qc3N5d"), std::string("z")})), (std::string("oMzcfupevIxyzwkE0qc3N5dz")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("g"), std::string("xyz"), std::string("N2yp2VlxtbXb"), std::string("1"), std::string("SyY")})), (std::string("gxyzN2yp2VlxtbXb1SyY")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("yDu"), std::string("JXPUeCGZ"), std::string("xyTewK"), std::string("k"), std::string("n9zFhMHvJW"), std::string("R")})), (std::string("yDuJXPUeCGZxyTewKkn9zFhMHvJWR")));
}

TEST(Probe, filter_by_prefix_01) {
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx"), std::string("vector")}, std::string("a"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("array")}, std::string("veor"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("vector")}, std::string("bcd"))), (std::vector<std::string >{std::string("bcd")}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("bmar8ay"), std::string("xxxAAA"), std::string("xxx")}, std::string("abc"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx"), std::string("PvFnj5rcFscd")}, std::string(""))), (std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx"), std::string("PvFnj5rcFscd")}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("d0QZJ"), std::string("john doe"), std::string("n"), std::string("array"), std::string("nmGjPawym14r"), std::string("7hQbSKk")}, std::string("xxy"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("vector")}, std::string("j"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("l")}, std::string("jdfQrm"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("array")}, std::string("q8d"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx")}, std::string("john"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("array")}, std::string("bsd"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("fh"), std::string("c8Qw"), std::string("x"), std::string("r"), std::string("Bihh67H")}, std::string("vectoFjrr"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("vector")}, std::string("asd"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("vector"), std::string("mdwLDFI5"), std::string("x5tf epLP")}, std::string("UoYYJy0"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string(""), std::string("john doe"), std::string("D"), std::string("xxy"), std::string("IajI"), std::string("bc"), std::string("abc")}, std::string("bcd"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("vector")}, std::string("rsD 7 "))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("ce"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx")}, std::string("a Cc"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("array"), std::string("arrac")}, std::string("john doe"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{}, std::string("q8h6k"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde")}, std::string("HaZz6d5"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("john")}, std::string("ri1"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("bcd"), std::string("2"), std::string("eyWK5Jef8Q2"), std::string("lCPfB8"), std::string("xxxAA"), std::string("xxy"), std::string("DMTa")}, std::string("b"))), (std::vector<std::string >{std::string("bcd")}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("d6atZs73lDfL")}, std::string("a"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("array")}, std::string("vector"))), (std::vector<std::string >{}));
}

TEST(Probe, filter_by_prefix_02) {
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("lEfLEmUO85j"), std::string(" ")}, std::string("de"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("ad"), std::string("john doe"), std::string("john oJ")}, std::string("Dxxy"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxy"), std::string("asd"), std::string("xxx"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("x1xx"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{}, std::string("jun"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("john"), std::string("3CaN3C")}, std::string("bc"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("06"), std::string("RHmz5")}, std::string("xc"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx")}, std::string("xOy"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("vector")}, std::string("bc"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("asg"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("AxAAA"), std::string("TFo24AsKqH"), std::string("vccHoN")}, std::string("abc"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("vector")}, std::string("john"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("vector")}, std::string("gstBZfiF aLM"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx")}, std::string("uAEczi"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string(""), std::string("cAce"), std::string("mE7")}, std::string("vector"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("vector"), std::string("")}, std::string("VkyCY0f"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("array")}, std::string("c9d"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("array")}, std::string("john doe"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("ZF Kr2rnd")}, std::string("xxy"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("bcd"), std::string("cde"), std::string("vector"), std::string("xxx")}, std::string("bcd"))), (std::vector<std::string >{std::string("bcd")}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("abc")}, std::string("asd"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("xxx")}, std::string("array"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("u")}, std::string("xxxAAA"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("array")}, std::string("bcd"))), (std::vector<std::string >{}));
}

TEST(Probe, get_positive_01) {
    ExpectNearVec(get_positive(std::vector<float >{-11.8000002f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{0.900099993f}), std::vector<float >{0.900099993f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{11.5f}), std::vector<float >{11.5f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{0.300099999f, -12.0f, 0.0f}), std::vector<float >{0.300099999f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-2.0f, -1.5f, -4.0f, 9.99999975e-05f, -5.0f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-8.80000019f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{17.2000008f, 9.99999975e-05f, 5.69999981f, 9.0f, -15.6999998f, 1.77999997f, 9.99999975e-05f, 12.5f}), std::vector<float >{17.2000008f, 9.99999975e-05f, 5.69999981f, 9.0f, 1.77999997f, 9.99999975e-05f, 12.5f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.99999975e-05f, 19.7999992f, 0.800100029f, 9.80000019f, 9.14999962f, 9.99999975e-05f, 9.99999975e-05f, 2.0f}), std::vector<float >{9.99999975e-05f, 19.7999992f, 0.800100029f, 9.80000019f, 9.14999962f, 9.99999975e-05f, 9.99999975e-05f, 2.0f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.0f}), std::vector<float >{9.0f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-3.0f, 123.0f}), std::vector<float >{123.0f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-2.0f, 3.80999994f, 13.8999996f, 9.99999975e-05f, 9.99999975e-05f, 15.0f, 0.0f}), std::vector<float >{3.80999994f, 13.8999996f, 9.99999975e-05f, 9.99999975e-05f, 15.0f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-1.79990005f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-3.0f, 7.5999999f, 4.65999985f, 2.0000999f, 9.99999975e-05f}), std::vector<float >{7.5999999f, 4.65999985f, 2.0000999f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{19.5f, 9.99999975e-05f, 9.80000019f}), std::vector<float >{19.5f, 9.99999975e-05f, 9.80000019f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-10.0f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.99999975e-05f, -1.69990003f}), std::vector<float >{9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{0.449999988f}), std::vector<float >{0.449999988f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{0.100100003f}), std::vector<float >{0.100100003f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.0f, -7.69999981f, 9.99999975e-05f}), std::vector<float >{9.0f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-2.70000005f, -1.70000005f, 5.46000004f, -14.0f, -13.1999998f}), std::vector<float >{5.46000004f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-2.20000005f, 9.99999975e-05f, 2.0999999f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 2.0999999f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-1.39999998f, 3.0f, -8.30000019f, 9.99999975e-05f}), std::vector<float >{3.0f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.99999975e-05f, 5.76000023f, -3.0999999f, -5.0f, -5.69999981f, -1.89989996f, -1.79990005f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 5.76000023f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{0.0f, 2.0f, 9.99999975e-05f}), std::vector<float >{2.0f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{1.00010002f}), std::vector<float >{1.00010002f}, 1e-5);
}

TEST(Probe, get_positive_02) {
    ExpectNearVec(get_positive(std::vector<float >{0.700100005f}), std::vector<float >{0.700100005f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{7.46000004f}), std::vector<float >{7.46000004f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{2.0f}), std::vector<float >{2.0f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.99999975e-05f, -3.0f, 15.1999998f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 15.1999998f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-6.5999999f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{7.80000019f, 9.99999975e-05f, -0.140000001f, 1.90009999f, 17.8999996f, 1.50010002f, 6.0f}), std::vector<float >{7.80000019f, 9.99999975e-05f, 1.90009999f, 17.8999996f, 1.50010002f, 6.0f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{3.05999994f}), std::vector<float >{3.05999994f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{1.80009997f, 9.80000019f, 9.99999975e-05f, 9.0f, 9.99999975e-05f, -11.1000004f, 9.99999975e-05f}), std::vector<float >{1.80009997f, 9.80000019f, 9.99999975e-05f, 9.0f, 9.99999975e-05f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{1.60000002f}), std::vector<float >{1.60000002f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-13.6999998f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{19.7999992f}), std::vector<float >{19.7999992f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{2.0999999f, -7.51999998f, 9.99999975e-05f, -4.0f}), std::vector<float >{2.0999999f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-1.20000005f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-10.0f, 17.1000004f, 13.6999998f, 9.99999975e-05f, -10.0f}), std::vector<float >{17.1000004f, 13.6999998f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-17.3999996f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-2.0f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-6.0999999f, 9.99999975e-05f, -11.6999998f, 9.99999975e-05f, 1.80009997f}), std::vector<float >{9.99999975e-05f, 9.99999975e-05f, 1.80009997f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{10.8000002f, -0.199900001f, 1.80009997f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, 3.0f, 0.300099999f}), std::vector<float >{10.8000002f, 1.80009997f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, 3.0f, 0.300099999f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.99999975e-05f, -0.199900001f}), std::vector<float >{9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-4.0f, 0.700100005f, -4.0f, 9.99999975e-05f, 7.48000002f, 9.99999975e-05f}), std::vector<float >{0.700100005f, 9.99999975e-05f, 7.48000002f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.99999975e-05f, 9.99999975e-05f, 4.0f, -12.3999996f, 1.95000005f, 9.99999975e-05f, -19.8999996f}), std::vector<float >{9.99999975e-05f, 9.99999975e-05f, 4.0f, 1.95000005f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-10.0f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, -19.7000008f, 9.99999975e-05f, -0.499900013f}), std::vector<float >{9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-1.19990003f}), std::vector<float >{}, 1e-5);
}

TEST(Probe, is_prime_01) {
    EXPECT_EQ((is_prime(-764LL)), (false));
    EXPECT_EQ((is_prime(-7LL)), (false));
    EXPECT_EQ((is_prime(14LL)), (false));
    EXPECT_EQ((is_prime(6LL)), (false));
    EXPECT_EQ((is_prime(23LL)), (true));
    EXPECT_EQ((is_prime(7LL)), (true));
    EXPECT_EQ((is_prime(3LL)), (true));
    EXPECT_EQ((is_prime(-737LL)), (false));
    EXPECT_EQ((is_prime(85LL)), (false));
    EXPECT_EQ((is_prime(5LL)), (true));
    EXPECT_EQ((is_prime(-978LL)), (false));
    EXPECT_EQ((is_prime(25LL)), (false));
    EXPECT_EQ((is_prime(18LL)), (false));
    EXPECT_EQ((is_prime(-242LL)), (false));
    EXPECT_EQ((is_prime(-4LL)), (false));
    EXPECT_EQ((is_prime(-793LL)), (false));
    EXPECT_EQ((is_prime(101LL)), (true));
    EXPECT_EQ((is_prime(592LL)), (false));
    EXPECT_EQ((is_prime(27LL)), (false));
    EXPECT_EQ((is_prime(99999LL)), (false));
    EXPECT_EQ((is_prime(452LL)), (false));
    EXPECT_EQ((is_prime(0LL)), (false));
    EXPECT_EQ((is_prime(4LL)), (false));
    EXPECT_EQ((is_prime(1LL)), (false));
    EXPECT_EQ((is_prime(-5LL)), (false));
}

TEST(Probe, is_prime_02) {
    EXPECT_EQ((is_prime(-253LL)), (false));
    EXPECT_EQ((is_prime(60LL)), (false));
    EXPECT_EQ((is_prime(-157LL)), (false));
    EXPECT_EQ((is_prime(-211LL)), (false));
    EXPECT_EQ((is_prime(-581LL)), (false));
    EXPECT_EQ((is_prime(9LL)), (false));
    EXPECT_EQ((is_prime(2LL)), (true));
    EXPECT_EQ((is_prime(231LL)), (false));
    EXPECT_EQ((is_prime(-998LL)), (false));
    EXPECT_EQ((is_prime(11LL)), (true));
    EXPECT_EQ((is_prime(-12LL)), (false));
    EXPECT_EQ((is_prime(88LL)), (false));
    EXPECT_EQ((is_prime(24LL)), (false));
    EXPECT_EQ((is_prime(933LL)), (false));
    EXPECT_EQ((is_prime(-10LL)), (false));
    EXPECT_EQ((is_prime(-911LL)), (false));
    EXPECT_EQ((is_prime(793LL)), (false));
    EXPECT_EQ((is_prime(-123LL)), (false));
    EXPECT_EQ((is_prime(29LL)), (true));
    EXPECT_EQ((is_prime(-534LL)), (false));
    EXPECT_EQ((is_prime(-950LL)), (false));
    EXPECT_EQ((is_prime(836LL)), (false));
    EXPECT_EQ((is_prime(-389LL)), (false));
}

TEST(Probe, poly_01) {
    ExpectNearScalar(poly(std::vector<double >{-8.1999999999999993}, -8.9000000000000004), -8.1999999999999993, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 1.0), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{11.6, 0.29999999999999999, -10.0, -12.6, 100.0}, 1.3), 253.01780000000005, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{2.5}, 16.300000000000001), 2.5, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.44, 3.4500000000000002, -1.0, -6.0, 1.0}, 0.001), 0.44344899400100002, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{11.199999999999999, -17.800000000000001, 100.0, 0.0001, 3.0, 7.7999999999999998}, -3.2999999999999998), -1537.8479476999992, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{8.4199999999999999}, -2.1000000000000001), 8.4199999999999999, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.099999999999999978}, 11.199999999999999), 0.099999999999999978, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.30009999999999998, -0.5, -14.699999999999999}, 6.7000000000000002), -662.93290000000002, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-0.89999999999999991}, 9.1999999999999993), -0.89999999999999991, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{21.0}, 0.59999999999999998), 21.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-7.0}, 0.0001), -7.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 6.79), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-10.0}, -0.5), -10.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.0001}, -1.3998999999999999), 0.0001, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 6.5), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-7.71, 5.0, 0.5, -4.7000000000000002, 0.0, 0.5, 3.6400000000000001, -1.6990000000000001}, 3.6000000000000001), -5290.7660968704013, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{100.0, -5.7999999999999998, 2.75, 0.5}, 7.4000000000000004), 410.28200000000004, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 0.60009999999999997), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{7.9000000000000004}, 21.0), 7.9000000000000004, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-0.5, 9.0999999999999996, 15.199999999999999}, 0.0001), -0.499089848, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 0.0001), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, -0.10000000000000009), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-2.0, 1.0}, 7.5), 5.5, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{19.899999999999999, -2.8999999999999999, 0.5, 18.300000000000001}, 1.0), 35.799999999999997, 1e-9);
}

TEST(Probe, poly_02) {
    ExpectNearScalar(poly(std::vector<double >{}, -0.5), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 0.5), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, -8.5999999999999996), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 18.199999999999999), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.12}, 2.5), 0.12, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-6.2000000000000002}, -10.0), -6.2000000000000002, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{9.9700000000000006, -2.0, -0.5, -3.8999999999999999, 0.001, -12.800000000000001}, -0.5), 11.732562500000002, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-1.0}, -5.0), -1.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 2.8999999999999999), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 4.1900000000000004), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 3.7599999999999998), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, -10.0), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{2.7999999999999998}, -1.6000000000000001), 2.7999999999999998, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 11.4), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.5}, 1.0), 0.5, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{8.4000000000000004}, 0.5), 8.4000000000000004, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{1.0, 0.29999999999999999, -0.69989999999999997, 1.0, 21.0, -1.8999999999999999, -4.0999999999999996, 13.300000000000001}, 1.601), 411.31381437941252, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{11.0, 1.0, 0.20100000000000001, -1.0}, 1.0), 11.201000000000001, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-5.0}, 0.0001), -5.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.001}, 0.001), 0.001, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, -5.2000000000000002), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 10.300000000000001), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-7.9000000000000004, -1.2, 8.9000000000000004, -0.5}, -18.600000000000001), 6310.8920000000016, 1e-9);
}

TEST(Probe, find_zero_01) {
    ExpectNearScalar(find_zero(std::vector<double >{3.0, 0.14000000000000001, -3.7000000000000002, -0.5, 4.2999999999999998, 1.0, -0.5, 2.0}), -1.0374310418875072, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-6.0, 0.001, -2.3999999999999999, -6.1399999999999997, 0.001, -10.1, -15.5, -9.0}), -0.95699352574981966, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, 0.001, 21.0, -0.29999999999999999, 1.601, -6.0}), 1.6103233509003498, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{7.0, 2.0, -17.399999999999999}), -0.57939747952214538, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{11.300000000000001, 1.0, 0.0001, 0.90100000000000002, 1.0, 2.0, -7.7999999999999998}), -1.0103462964241428, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{12.699999999999999, 1.8999999999999999, 4.04, 0.0001, -0.5, 0.0001, -0.40000000000000002}), -1.8709649217350601, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{11.0, 0.5}), -22.0, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-0.19900000000000001, 3.2999999999999998}), 0.06030303030303031, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, 10.199999999999999, 1.7000999999999999, 11.0}), -0.098625957919047158, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{9.1999999999999993, 1.0, -0.49990000000000001, -0.80000000000000004, -0.69989999999999997, 2.6400000000000001}), -1.2200899084958734, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{5.5999999999999996, -6.5}), 0.86153846153846148, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.001, -18.399999999999999, 14.300000000000001, -0.63, 0.0001, 6.0, -19.5}), 5.4347826086956524e-05, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.001, 1.0, 1.6599999999999999}), -0.0010016655295581331, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-1.04, -2.2999999999999998, 100.0, -17.5, 0.001}), -0.090492972599930707, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-0.5, 0.10100000000000001, -0.29899999999999999, -1.0}), -0.95411073584172212, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{3.0, 1.0, 11.1, 13.699999999999999, 9.0800000000000001, 0.5, 0.20000000000000001, 1.0}), -1.6807651388181364, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, -2.7000000000000002, -10.0, -1.2999000000000001, -18.600000000000001, 0.5, 2.5, -16.300000000000001}), 0.20266368559097855, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.2, 9.0999999999999996}), -0.13186813186813187, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-5.9000000000000004, -12.6, 13.300000000000001, -0.5, -1.7}), -0.34377749818677111, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, -5.5999999999999996, 1.03, -0.71999999999999997}), 0.18399743810805741, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{11.699999999999999, 0.0001}), -116999.99999999999, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{3.8900000000000001, -0.5, 0.5, -9.1999999999999993, -19.800000000000001}), 0.56887621295345525, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.0, -0.19999999999999996, -14.1, 1.0, -11.300000000000001, -6.2000000000000002}), 0.0, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, -10.0}), 0.10000000000000001, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, 1.0, -9.4000000000000004, -0.5, -6.9000000000000004}), -0.27273765967691521, 1e-9);
}

TEST(Probe, find_zero_02) {
    ExpectNearScalar(find_zero(std::vector<double >{-16.899999999999999, 11.0, 0.0, 0.40000000000000002, 0.0, 1.0}), 1.2221314952293949, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.5, -7.9000000000000004}), 0.063291139240506319, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, -10.0, 8.0399999999999991}), 0.10967013440606231, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{2.7999999999999998, 5.3200000000000003, 4.7199999999999998, 5.0999999999999996, 4.0, 1.5001, 0.5, 100.0}), -0.50787002186078467, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, 0.001}), -1000.0, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.001, -5.9000000000000004, 11.0, 0.001, 0.0}), 0.0001694915254237288, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{5.5599999999999996, -14.1, 0.40100000000000002, 1.5009999999999999, 18.800000000000001, 1.0}), 0.50146609570763556, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{11.300000000000001, 1.0, -0.30000000000000004, -0.5, -5.3300000000000001}), -1.1854497549636511, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-8.5999999999999996, 6.0899999999999999, 12.9, 4.9000000000000004, 5.1799999999999997}), 0.55208977034188988, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{11.0, -0.99990000000000001, 8.5500000000000007, 1.0, -1.9999}), 2.4912732453500945, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.59999999999999998, 1.1000000000000001, 0.0001, 100.0, 4.0, -7.6900000000000004, 1.0}), -0.16203164564022624, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-4.8300000000000001, -13.300000000000001, -14.199999999999999, -12.9, 3.0, 13.6}), -0.56482346781146919, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, -2.0, -16.899999999999999, 1.0, 3.0, -18.199999999999999}), 0.19192923705289111, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.0}), 0.0, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{12.699999999999999, -0.80000000000000004, -0.5}), 4.3029403455207547, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{7.4000000000000004, -6.0, 2.2999999999999998, -0.11, 1.9009999999999998, -7.5}), 0.92685491860388347, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{6.7999999999999998, 0.0001, -0.5, 9.9000000000000004}), -0.86579526636239168, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.0001, 0.90000000000000002, 0.001, 1.0}), -0.00011111111111111112, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, 11.0, -19.199999999999999, 6.5999999999999996, 1.2, 0.89999999999999991, -0.5, -12.0}), -0.07956213263891844, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{8.9299999999999997, 6.5999999999999996, 4.2000000000000002, -8.4199999999999999}), 1.4963344692970526, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-8.0, 1.0, 0.0001}), 7.9936102236421727, 1e-9);
}
