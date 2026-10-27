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

TEST(Probe, encrypt_01) {
    EXPECT_EQ((encrypt(std::string("lm"))), (std::string("pq")));
    EXPECT_EQ((encrypt(std::string("faewfamwefaewg"))), (std::string("jeiajeqaijeiak")));
    EXPECT_EQ((encrypt(std::string("dxzdlmnilfuhmilufhlihufnmlimnufhlimnufhfucufh"))), (std::string("hbdhpqrmpjylqmpyjlpmlyjrqpmqryjlpmqryjljygyjl")));
    EXPECT_EQ((encrypt(std::string("YlBe"))), (std::string("]p`i")));
    EXPECT_EQ((encrypt(std::string("OQkU4"))), (std::string("SUoYR")));
    EXPECT_EQ((encrypt(std::string("dxzdlmNilfuhmilufhlihufnmlimnufhlimnufhfucufh"))), (std::string("hbdhpqRmpjylqmpyjlpmlyjrqpmqryjlpmqryjljygyjl")));
    EXPECT_EQ((encrypt(std::string("YVIZEln"))), (std::string("]ZM^Ipr")));
    EXPECT_EQ((encrypt(std::string("eiajeaijeiak"))), (std::string("imeniemnimeo")));
    EXPECT_EQ((encrypt(std::string("lbQO"))), (std::string("pfUS")));
    EXPECT_EQ((encrypt(std::string("gf"))), (std::string("kj")));
    EXPECT_EQ((encrypt(std::string("hi"))), (std::string("lm")));
    EXPECT_EQ((encrypt(std::string("i"))), (std::string("m")));
    EXPECT_EQ((encrypt(std::string("hGi"))), (std::string("lKm")));
    EXPECT_EQ((encrypt(std::string("tkj"))), (std::string("xon")));
    EXPECT_EQ((encrypt(std::string("J"))), (std::string("N")));
    EXPECT_EQ((encrypt(std::string("jeiajeaijeiak"))), (std::string("nimeniemnimeo")));
    EXPECT_EQ((encrypt(std::string("rwNERoJ"))), (std::string("vaRIVsN")));
    EXPECT_EQ((encrypt(std::string("hbdhpqrmpjylqmpyjlpmlyjrqpmqryjlpmqryjljygyjl"))), (std::string("lfhltuvqtncpuqtcnptqpcnvutquvcnptquvcnpnckcnp")));
    EXPECT_EQ((encrypt(std::string("hllomyyfriend"))), (std::string("lppsqccjvmirh")));
    EXPECT_EQ((encrypt(std::string("dxzilmnilfuhmilufhlihufnmlimnufhlmnufhfucufh"))), (std::string("hbdmpqrmpjylqmpyjlpmlyjrqpmqryjlpqryjljygyjl")));
    EXPECT_EQ((encrypt(std::string("ewjklnop"))), (std::string("ianoprst")));
    EXPECT_EQ((encrypt(std::string("hellomyfriend"))), (std::string("lippsqcjvmirh")));
    EXPECT_EQ((encrypt(std::string("6KTY"))), (std::string("TOX]")));
    EXPECT_EQ((encrypt(std::string("biKbK3sQxY4"))), (std::string("fmOfOQwUb]R")));
    EXPECT_EQ((encrypt(std::string("faewfawgefaewg"))), (std::string("jeiajeakijeiak")));
}

TEST(Probe, encrypt_02) {
    EXPECT_EQ((encrypt(std::string("L4lSeuHpCHtM"))), (std::string("PRpWiyLtaLxQ")));
    EXPECT_EQ((encrypt(std::string("mB6G"))), (std::string("q`TK")));
    EXPECT_EQ((encrypt(std::string("krJj"))), (std::string("ovNn")));
    EXPECT_EQ((encrypt(std::string(" "))), (std::string("X")));
    EXPECT_EQ((encrypt(std::string("jeajeijeia1"))), (std::string("nienimnimeO")));
    EXPECT_EQ((encrypt(std::string("et"))), (std::string("ix")));
    EXPECT_EQ((encrypt(std::string("f"))), (std::string("j")));
    EXPECT_EQ((encrypt(std::string("a3sdfThj9kl"))), (std::string("eQwhjXlnWop")));
    EXPECT_EQ((encrypt(std::string("ehjklnop"))), (std::string("ilnoprst")));
    EXPECT_EQ((encrypt(std::string("Wsfdfghjkl"))), (std::string("[wjhjklnop")));
    EXPECT_EQ((encrypt(std::string("QpwY 0"))), (std::string("Uta]XN")));
    EXPECT_EQ((encrypt(std::string("h"))), (std::string("l")));
    EXPECT_EQ((encrypt(std::string("e"))), (std::string("i")));
    EXPECT_EQ((encrypt(std::string("TZ94NvE7K"))), (std::string("X^WRRzIUO")));
    EXPECT_EQ((encrypt(std::string("hbdhpqrmp8jyDqmpyjlpmlyjrqpmqryjlpmqryjljygyjl"))), (std::string("lfhltuvqtVncHuqtcnptqpcnvutquvcnptquvcnpnckcnp")));
    EXPECT_EQ((encrypt(std::string("helomyfriend"))), (std::string("lipsqcjvmirh")));
    EXPECT_EQ((encrypt(std::string("MwcBGS36RZk"))), (std::string("Qag`KWQTV^o")));
    EXPECT_EQ((encrypt(std::string("Het"))), (std::string("Lix")));
    EXPECT_EQ((encrypt(std::string("PYO4FeyK "))), (std::string("T]SRJicOX")));
    EXPECT_EQ((encrypt(std::string("hU2"))), (std::string("lYP")));
    EXPECT_EQ((encrypt(std::string(""))), (std::string("")));
    EXPECT_EQ((encrypt(std::string("faeYfawfaewg"))), (std::string("jei]jeajeiak")));
    EXPECT_EQ((encrypt(std::string("EujSZQpZFK"))), (std::string("IynW^Ut^JO")));
}

TEST(Probe, next_smallest_01) {
    EXPECT_EQ((next_smallest(std::vector<int >{5, 4, 3, 2})), (3));
    EXPECT_EQ((next_smallest(std::vector<int >{})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{143})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{5, 19, 6, -1, 3})), (3));
    EXPECT_EQ((next_smallest(std::vector<int >{-35, 34, 12, -45})), (-35));
    EXPECT_EQ((next_smallest(std::vector<int >{0, -43, 2})), (0));
    EXPECT_EQ((next_smallest(std::vector<int >{4})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{1, 1, 1, 1, 0})), (1));
    EXPECT_EQ((next_smallest(std::vector<int >{34, -5, 29, -990})), (-5));
    EXPECT_EQ((next_smallest(std::vector<int >{489, 34, 12, -45})), (12));
    EXPECT_EQ((next_smallest(std::vector<int >{469, 4, 21})), (21));
    EXPECT_EQ((next_smallest(std::vector<int >{846, 2, 14, 274, 235})), (14));
    EXPECT_EQ((next_smallest(std::vector<int >{-835, 543, 12, 30})), (12));
    EXPECT_EQ((next_smallest(std::vector<int >{1, 1, 1, 1, -573})), (1));
    EXPECT_EQ((next_smallest(std::vector<int >{3, 2, 1, 4, 5})), (2));
    EXPECT_EQ((next_smallest(std::vector<int >{1, 1, -465})), (1));
    EXPECT_EQ((next_smallest(std::vector<int >{-104, -779})), (-104));
    EXPECT_EQ((next_smallest(std::vector<int >{3, -739, 29, 26, 0})), (0));
    EXPECT_EQ((next_smallest(std::vector<int >{5, 1, 4, 3, 2})), (2));
    EXPECT_EQ((next_smallest(std::vector<int >{4, -43, -7, 3, -35, 5, 26})), (-35));
    EXPECT_EQ((next_smallest(std::vector<int >{610})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{-45})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{1, 1, -5})), (1));
    EXPECT_EQ((next_smallest(std::vector<int >{3, 8, -35, 1, 0, 2, 10})), (0));
    EXPECT_EQ((next_smallest(std::vector<int >{-7, 273, 29, 11, -1, 5})), (-1));
}

TEST(Probe, next_smallest_02) {
    EXPECT_EQ((next_smallest(std::vector<int >{5, 1, 4, 3})), (3));
    EXPECT_EQ((next_smallest(std::vector<int >{82, 2})), (82));
    EXPECT_EQ((next_smallest(std::vector<int >{5, 1, 3, 3, 2})), (2));
    EXPECT_EQ((next_smallest(std::vector<int >{5, 1, 4, 3, 2, 34})), (2));
    EXPECT_EQ((next_smallest(std::vector<int >{34, -35, 12, -45})), (-35));
    EXPECT_EQ((next_smallest(std::vector<int >{-1, 11})), (11));
    EXPECT_EQ((next_smallest(std::vector<int >{5, 1, -1, 3, 2})), (1));
    EXPECT_EQ((next_smallest(std::vector<int >{1, 22})), (22));
    EXPECT_EQ((next_smallest(std::vector<int >{27})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{-571, 0, 4, 0, 11, -1})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{495, 189, 2})), (189));
    EXPECT_EQ((next_smallest(std::vector<int >{17})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{22, 5, -5})), (5));
    EXPECT_EQ((next_smallest(std::vector<int >{644})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{27, -1, 0, -617, -2, -45, -1})), (-45));
    EXPECT_EQ((next_smallest(std::vector<int >{-1, 4, -1, 34, 14, 19})), (4));
    EXPECT_EQ((next_smallest(std::vector<int >{19, 2, 0, 5, 5})), (2));
    EXPECT_EQ((next_smallest(std::vector<int >{3, 157, 28})), (28));
    EXPECT_EQ((next_smallest(std::vector<int >{-35, 12, -45})), (-35));
    EXPECT_EQ((next_smallest(std::vector<int >{-5})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{12, 2, 3, 4, 5})), (3));
    EXPECT_EQ((next_smallest(std::vector<int >{-8})), (-1));
    EXPECT_EQ((next_smallest(std::vector<int >{-3, 13, 0, 28})), (0));
}

TEST(Probe, is_bored_01) {
    EXPECT_EQ((is_bored(std::string("Q8ysuoM1bo"))), (0));
    EXPECT_EQ((is_bored(std::string("dJiilw8lws"))), (0));
    EXPECT_EQ((is_bored(std::string("8"))), (0));
    EXPECT_EQ((is_bored(std::string("I 8feel .good today. I will be productive. willkill It"))), (2));
    EXPECT_EQ((is_bored(std::string("U.\?LJRRWr1"))), (0));
    EXPECT_EQ((is_bored(std::string("Is the skyqblue\?"))), (0));
    EXPECT_EQ((is_bored(std::string("You and I are going for a walk"))), (0));
    EXPECT_EQ((is_bored(std::string("Ei"))), (0));
    EXPECT_EQ((is_bored(std::string("I love It !"))), (1));
    EXPECT_EQ((is_bored(std::string("IE \?ove Itj !"))), (0));
    EXPECT_EQ((is_bored(std::string("E4"))), (0));
    EXPECT_EQ((is_bored(std::string("HN2N0r!zlUn"))), (0));
    EXPECT_EQ((is_bored(std::string("I feel goodE today. I will be productive. will kill It"))), (2));
    EXPECT_EQ((is_bored(std::string("jm"))), (0));
    EXPECT_EQ((is_bored(std::string("aWAjC!"))), (0));
    EXPECT_EQ((is_bored(std::string("I lOve It !"))), (1));
    EXPECT_EQ((is_bored(std::string("I feel5 good today. I will be productve. will kill It"))), (2));
    EXPECT_EQ((is_bored(std::string("qG3qgRDdVhBq"))), (0));
    EXPECT_EQ((is_bored(std::string("Y"))), (0));
    EXPECT_EQ((is_bored(std::string("IFs thne sky ble\?"))), (0));
    EXPECT_EQ((is_bored(std::string("nWlBN1k4ugqY"))), (0));
    EXPECT_EQ((is_bored(std::string("v8HI7KD.N"))), (0));
    EXPECT_EQ((is_bored(std::string("The sky is blue. Theh sun is shining. I love this weather"))), (1));
    EXPECT_EQ((is_bored(std::string("I feehl good today. I will be productive. will kill It"))), (2));
    EXPECT_EQ((is_bored(std::string("E0sCgq"))), (0));
}

TEST(Probe, is_bored_02) {
    EXPECT_EQ((is_bored(std::string("The sky is blue. The sun is shining. I love this weather"))), (1));
    EXPECT_EQ((is_bored(std::string("tOmICF"))), (0));
    EXPECT_EQ((is_bored(std::string("The sky is blue.The sun is shining. I lo8e this Oweather"))), (1));
    EXPECT_EQ((is_bored(std::string("I feel gooda today. M will be productive. will kill It"))), (1));
    EXPECT_EQ((is_bored(std::string("HellomB\?rld"))), (0));
    EXPECT_EQ((is_bored(std::string("Hello worNd"))), (0));
    EXPECT_EQ((is_bored(std::string("D2I"))), (0));
    EXPECT_EQ((is_bored(std::string("ou and I are going for a walk"))), (0));
    EXPECT_EQ((is_bored(std::string("You and I are going for a waUk"))), (0));
    EXPECT_EQ((is_bored(std::string("The sky is bloe. The sun is shining. I love 6his weatheL"))), (1));
    EXPECT_EQ((is_bored(std::string("i"))), (0));
    EXPECT_EQ((is_bored(std::string("I feel good to7day. I will be prodTctive. will kill It"))), (2));
    EXPECT_EQ((is_bored(std::string("Qe9! "))), (0));
    EXPECT_EQ((is_bored(std::string("XE"))), (0));
    EXPECT_EQ((is_bored(std::string("KQGC!0wZfif"))), (0));
    EXPECT_EQ((is_bored(std::string("0Ab"))), (0));
    EXPECT_EQ((is_bored(std::string("O"))), (0));
    EXPECT_EQ((is_bored(std::string("bIE"))), (0));
    EXPECT_EQ((is_bored(std::string("Yquand I are gmoing for a walk"))), (0));
    EXPECT_EQ((is_bored(std::string("K2MOnuDXvi"))), (0));
    EXPECT_EQ((is_bored(std::string(" loae It !"))), (0));
    EXPECT_EQ((is_bored(std::string("Is the sky blue\?"))), (0));
    EXPECT_EQ((is_bored(std::string("bIt"))), (0));
}

TEST(Probe, any_int_01) {
    EXPECT_EQ((any_int(-5.90999985f, 1.39999998f, 2.9000001f)), (false));
    EXPECT_EQ((any_int(-19.0f, -18.2999992f, 0.0f)), (false));
    EXPECT_EQ((any_int(2.29999995f, 1.64999998f, -6.5999999f)), (false));
    EXPECT_EQ((any_int(-2.20000005f, 19.5f, -12.3999996f)), (false));
    EXPECT_EQ((any_int(2.5f, 2.20000005f, 4.9000001f)), (false));
    EXPECT_EQ((any_int(-2.44000006f, 3.0f, 2.5f)), (false));
    EXPECT_EQ((any_int(3.5f, 17.8999996f, -5.69999981f)), (false));
    EXPECT_EQ((any_int(1.60000002f, -4.19999981f, 1.0f)), (false));
    EXPECT_EQ((any_int(2.5999999f, 7.30000019f, -17.7000008f)), (false));
    EXPECT_EQ((any_int(-3.4000001f, -2.0f, -4.19999981f)), (false));
    EXPECT_EQ((any_int(2.0999999f, 3.0f, -2.20000005f)), (false));
    EXPECT_EQ((any_int(-19.8999996f, 3.70000005f, 3.0f)), (false));
    EXPECT_EQ((any_int(3.0f, 2.5f, 5.0f)), (false));
    EXPECT_EQ((any_int(17.3999996f, 1.5f, 10.1000004f)), (false));
    EXPECT_EQ((any_int(0.5f, 12.0f, 1.5f)), (false));
    EXPECT_EQ((any_int(1.5f, -0.300000012f, -0.800000012f)), (false));
    EXPECT_EQ((any_int(3.5999999f, 9.0f, 2.0f)), (false));
    EXPECT_EQ((any_int(4.30000019f, -3.93000007f, 4.23000002f)), (false));
    EXPECT_EQ((any_int(-2.0f, 0.200000003f, 3.5999999f)), (false));
    EXPECT_EQ((any_int(2.20000005f, 2.70000005f, 1.5f)), (false));
    EXPECT_EQ((any_int(7.0f, 10.0f, 2.5f)), (false));
    EXPECT_EQ((any_int(3.00999999f, 2.5f, -6.28999996f)), (false));
    EXPECT_EQ((any_int(1.5f, 3.5f, 3.00999999f)), (false));
    EXPECT_EQ((any_int(-0.769999981f, 3.00999999f, 0.400000006f)), (false));
    EXPECT_EQ((any_int(3.5f, 4.55999994f, 1.0f)), (false));
}

TEST(Probe, any_int_02) {
    EXPECT_EQ((any_int(3.00999999f, -1.59000003f, 1.79999995f)), (false));
    EXPECT_EQ((any_int(3.5f, 4.4000001f, 4.6500001f)), (false));
    EXPECT_EQ((any_int(4.0999999f, -2.29999995f, 2.20000005f)), (false));
    EXPECT_EQ((any_int(5.0f, 4.01000023f, 1.0f)), (false));
    EXPECT_EQ((any_int(-1.87f, 1.5f, -15.3999996f)), (false));
    EXPECT_EQ((any_int(4.19999981f, 3.0f, 2.5f)), (false));
    EXPECT_EQ((any_int(2.5f, -4.0f, 2.20000005f)), (false));
    EXPECT_EQ((any_int(3.29999995f, -10.1999998f, 3.5f)), (false));
    EXPECT_EQ((any_int(-6.5999999f, -7.30000019f, 2.20000005f)), (false));
    EXPECT_EQ((any_int(-17.6000004f, 14.1999998f, 11.1000004f)), (false));
    EXPECT_EQ((any_int(-17.1000004f, 3.5f, 13.8000002f)), (false));
    EXPECT_EQ((any_int(3.5999999f, 3.5999999f, -6.4000001f)), (false));
    EXPECT_EQ((any_int(3.67000008f, 8.11999989f, 4.4000001f)), (false));
    EXPECT_EQ((any_int(-2.70000005f, 2.5f, 10.3999996f)), (false));
    EXPECT_EQ((any_int(19.5f, 13.8000002f, 7.0f)), (false));
    EXPECT_EQ((any_int(3.5999999f, -1.90999997f, 7.80000019f)), (false));
    EXPECT_EQ((any_int(1.29999995f, 18.8999996f, 1.5f)), (false));
    EXPECT_EQ((any_int(4.0f, 10.8999996f, 2.29999995f)), (false));
    EXPECT_EQ((any_int(-0.699999988f, 0.400000006f, -17.0f)), (false));
    EXPECT_EQ((any_int(2.5f, -10.1000004f, 10.6999998f)), (false));
    EXPECT_EQ((any_int(3.5f, 2.20000005f, -12.3000002f)), (false));
    EXPECT_EQ((any_int(2.5f, 4.0f, 3.9000001f)), (false));
    EXPECT_EQ((any_int(15.0f, 1.5f, 12.0f)), (false));
}

TEST(Probe, encode_01) {
    EXPECT_EQ((encode(std::string("D1W15tic"))), (std::string("d1w15TKC")));
    EXPECT_EQ((encode(std::string("Mdasir"))), (std::string("mDCSKR")));
    EXPECT_EQ((encode(std::string(""))), (std::string("")));
    EXPECT_EQ((encode(std::string("E"))), (std::string("g")));
    EXPECT_EQ((encode(std::string("tHKS KS C MGSSCGG"))), (std::string("Thks ks c mgsscgg")));
    EXPECT_EQ((encode(std::string("ftDFppRvUTHf"))), (std::string("FTdfPPrVwthF")));
    EXPECT_EQ((encode(std::string("mWDCSKR"))), (std::string("Mwdcskr")));
    EXPECT_EQ((encode(std::string("TsT"))), (std::string("tSt")));
    EXPECT_EQ((encode(std::string("TESsT"))), (std::string("tgsSt")));
    EXPECT_EQ((encode(std::string("k dQnT kNqW wHcT Tq wRkTg"))), (std::string("K DqNt KnQw WhCt tQ WrKtG")));
    EXPECT_EQ((encode(std::string("This isF a message"))), (std::string("tHKS KSf C MGSSCGG")));
    EXPECT_EQ((encode(std::string("EygnJpvwou"))), (std::string("gYGNjPVWQW")));
    EXPECT_EQ((encode(std::string("Nudasir"))), (std::string("nWDCSKR")));
    EXPECT_EQ((encode(std::string("This is a message"))), (std::string("tHKS KS C MGSSCGG")));
    EXPECT_EQ((encode(std::string("tHRKS 9KS C MGSS5CGG"))), (std::string("Thrks 9ks c mgss5cgg")));
    EXPECT_EQ((encode(std::string("k dQnT kNqWVwHcT Tq wRUkTg"))), (std::string("K DqNt KnQwvWhCt tQ WrwKtG")));
    EXPECT_EQ((encode(std::string("7Mjg0tmxGO5C"))), (std::string("7mJG0TMXgq5c")));
    EXPECT_EQ((encode(std::string("TGJ9ST"))), (std::string("tgj9st")));
    EXPECT_EQ((encode(std::string("Mudasir"))), (std::string("mWDCSKR")));
    EXPECT_EQ((encode(std::string("wjP4z2ie"))), (std::string("WJp4Z2KG")));
    EXPECT_EQ((encode(std::string("teV0"))), (std::string("TGv0")));
    EXPECT_EQ((encode(std::string("TE ST"))), (std::string("tg st")));
    EXPECT_EQ((encode(std::string("GtesU"))), (std::string("gTGSw")));
    EXPECT_EQ((encode(std::string("jN8s9u"))), (std::string("Jn8S9W")));
    EXPECT_EQ((encode(std::string("zLlZvlPY0ws"))), (std::string("ZlLzVLpy0WS")));
}

TEST(Probe, encode_02) {
    EXPECT_EQ((encode(std::string("YES"))), (std::string("ygs")));
    EXPECT_EQ((encode(std::string("I DoNt KnO WhAt tOi WrItE"))), (std::string("k dQnT kNq wHcT TqK wRkTg")));
    EXPECT_EQ((encode(std::string("This is a messwage"))), (std::string("tHKS KS C MGSSWCGG")));
    EXPECT_EQ((encode(std::string("GFST"))), (std::string("gfst")));
    EXPECT_EQ((encode(std::string("TcST"))), (std::string("tCst")));
    EXPECT_EQ((encode(std::string("zd0QZJ"))), (std::string("ZD0qzj")));
    EXPECT_EQ((encode(std::string("mCSR"))), (std::string("Mcsr")));
    EXPECT_EQ((encode(std::string("test"))), (std::string("TGST")));
    EXPECT_EQ((encode(std::string("nmGjPawym14r"))), (std::string("NMgJpCWYM14R")));
    EXPECT_EQ((encode(std::string("7hQbSKk"))), (std::string("7HqBskK")));
    EXPECT_EQ((encode(std::string("TjST"))), (std::string("tJst")));
    EXPECT_EQ((encode(std::string("kX"))), (std::string("Kx")));
    EXPECT_EQ((encode(std::string("vjdfQrmOV"))), (std::string("VJDFqRMqv")));
    EXPECT_EQ((encode(std::string("TE8q"))), (std::string("tg8Q")));
    EXPECT_EQ((encode(std::string("ygs"))), (std::string("YGS")));
    EXPECT_EQ((encode(std::string("bgs"))), (std::string("BGS")));
    EXPECT_EQ((encode(std::string("b5LmMHha"))), (std::string("B5lMmhHC")));
    EXPECT_EQ((encode(std::string("YREfS"))), (std::string("yrgFs")));
    EXPECT_EQ((encode(std::string("wzucz"))), (std::string("WZWCZ")));
    EXPECT_EQ((encode(std::string("KEAST"))), (std::string("kgcst")));
    EXPECT_EQ((encode(std::string("c"))), (std::string("C")));
    EXPECT_EQ((encode(std::string("k dQnT kNqW wHcT T wRkTg"))), (std::string("K DqNt KnQw WhCt t WrKtG")));
    EXPECT_EQ((encode(std::string("Mluair"))), (std::string("mLWCKR")));
}

TEST(Probe, skjkasdkd_01) {
    EXPECT_EQ((skjkasdkd(std::vector<int >{5, 20})), (5));
    EXPECT_EQ((skjkasdkd(std::vector<int >{-3, 4597, 99})), (25));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 724, 32, 71, 99, 32, 6, 0, 5, 91, 83, 0, 5, 6, 0})), (11));
    EXPECT_EQ((skjkasdkd(std::vector<int >{127, 97, 8192})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 8, 1, 7, 1, 7})), (7));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 0, 1, 8, 2, 4597, 2, 1, 3, 40, 1, 2, 1, 2, 4, 2, 5, 1, 97})), (25));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, -626, -5, 254, 13, 206, -356})), (4));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 4, 1, 2, 1, 7})), (7));
    EXPECT_EQ((skjkasdkd(std::vector<int >{8191, 123456, 127, 7})), (19));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 32, 724, 71, 99, 32, 6, 0, 5, 91, 83, 0, 5, 6})), (11));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 0, 1, 8, 2, 4597, 2, 1, 3, 40, 1, 2, 1, 2, 4, 2, 5, 1})), (25));
    EXPECT_EQ((skjkasdkd(std::vector<int >{8191, 123456, 127, 7, 123456})), (19));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 3, 2, 1, 3, 5, 7, 4, 5, 5, 5, 2, 181, 32, 4, 32, 2, 32, 324, 4, 3})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{26, 15, 669, -5, 32, 2, 13})), (4));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 3, 1, 32, 5107, 34, 83278, 109, 315, 23, 2323, 32, 30, 1, 9, 3})), (13));
    EXPECT_EQ((skjkasdkd(std::vector<int >{23, 832, 6, 8192, -817, 7})), (5));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 8, 1, 2, 1})), (2));
    EXPECT_EQ((skjkasdkd(std::vector<int >{3, 8, 14, -1, 7, 915})), (7));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 15, 9, 17, -548, 26, 12, 27})), (8));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 3, 1, 32, 5107, 34, 83278, 109, 163, 23, 2323, 32, 30, 1, 9, 3})), (13));
    EXPECT_EQ((skjkasdkd(std::vector<int >{12345, 7})), (7));
    EXPECT_EQ((skjkasdkd(std::vector<int >{-3, 181, 32, 7, 6, 2323, 265})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{})), (0));
    EXPECT_EQ((skjkasdkd(std::vector<int >{2323, 14, 691})), (16));
    EXPECT_EQ((skjkasdkd(std::vector<int >{162, 97, 572, 6, 34, 28, 5109, 920})), (16));
}

TEST(Probe, skjkasdkd_02) {
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 163, 1, 2, 1, 7})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{324, 6})), (0));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 3, 32, 5107, 34, 83278, 109, 163, 23, 2323, 32, 30, 1, 9, 3})), (13));
    EXPECT_EQ((skjkasdkd(std::vector<int >{8191, 123456, 26, 7})), (19));
    EXPECT_EQ((skjkasdkd(std::vector<int >{16, 4, 97})), (16));
    EXPECT_EQ((skjkasdkd(std::vector<int >{-5, 598, 12345, 19, 637})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{520, 3, 3, 21})), (3));
    EXPECT_EQ((skjkasdkd(std::vector<int >{-8, 21, 228, 81})), (0));
    EXPECT_EQ((skjkasdkd(std::vector<int >{32, 12345, 6, -3, 20, 12, 2324, 324})), (0));
    EXPECT_EQ((skjkasdkd(std::vector<int >{-2, 5, 99})), (5));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 81, 12, 3, 11, 21})), (2));
    EXPECT_EQ((skjkasdkd(std::vector<int >{3, 81, 12, 0, 1, 21})), (3));
    EXPECT_EQ((skjkasdkd(std::vector<int >{30, 14, 25, -1, 5})), (5));
    EXPECT_EQ((skjkasdkd(std::vector<int >{16, 724, -8, 12, 410, 3, 1, 9})), (3));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 684, 1, 32, 5107, 34, 83278, 109, 163, 23, 2323, 32, 30, 1, 9, 3})), (13));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 0, 1, 8, 2, 4597, 2, 1, 3, 40, 2, 1, 2, 4, 2, 5, 1})), (25));
    EXPECT_EQ((skjkasdkd(std::vector<int >{21, 0, 1, 8, 2, 4597, 2, 1, 3, 40, 1, 2, 1, 2, 4, 2, 5, 1})), (25));
    EXPECT_EQ((skjkasdkd(std::vector<int >{1, 8, 0, 2, 1, 7})), (7));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 3, 2, 1, 3, 5, 7, 4, 5, 5, 5, 2, 181, 32, 4, 32, 3, 2, 32, 324, 4, 3})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 3, 2, 1, 3, 5, 7, 4, 5, 5, 5, 2, 181, 32, 4, 32, 3, 2, 32, 324, 4, 3, 4})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{19, 32, -14, 99, 9, 129, -1})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 3, 2, 3, 1, 5, 7, 4, 5, 5, 5, 2, 181, 32, 4, 32, 3, 2, 32, 324, 4, 3})), (10));
    EXPECT_EQ((skjkasdkd(std::vector<int >{0, 3, 2, 1, 3, 5, 7, 4, 5, 5, 5, 2, 181, 32, 4, 32, 3, 2, 32, -3, 4, 3})), (10));
}

TEST(Probe, check_dict_case_01) {
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Houston"), std::string("OU ")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("3M0"), std::string("p")}, {std::string("N C"), std::string("XPZo3nxxH5KN")}, {std::string("fRUIT"), std::string("Aoe")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("5"), std::string("edrup9cj9L9")}, {std::string("Qwa"), std::string("ZIi")}, {std::string("i9H"), std::string("QkC2iPFmgsU")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("9"), std::string("36")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("City"), std::string("ox")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("b"), std::string("GrZZYlw0fB T")}, {std::string("pineapple"), std::string("q")}})), (true));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("8"), std::string("3t0")}, {std::string("KqToZpEQO"), std::string("City")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string(""), std::string("John")}, {std::string("Name"), std::string("1w2345")}, {std::string("STATE"), std::string("City")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string(""), std::string("a")}, {std::string("p"), std::string("b")}})), (true));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Orange"), std::string("")}, {std::string("banana"), std::string("bV")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("houstON"), std::string("5")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("CkRnuH"), std::string("SWB")}, {std::string("a"), std::string("06STATlE")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("7w"), std::string("Aica0R")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("0Orange"), std::string("mlLfo1j")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Orange"), std::string("SAUTE")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("HoUStON"), std::string("")}, {std::string("frut"), std::string("ZecLdoJJNJ6w")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Ame"), std::string("4KXNl4bMVaH")}, {std::string("nAMe"), std::string("")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("34Co"), std::string("NKame")}, {std::string("John"), std::string("MViSkdLCU4")}, {std::string("ltaMe"), std::string("b")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Houston"), std::string("fAuit")}, {std::string("u"), std::string("STATE")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("John"), std::string("4lOVqSmB")}, {std::string("Swe"), std::string("Yfp")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("36"), std::string("pineapple")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("IIbH9taCmf"), std::string("Age")}, {std::string("w"), std::string("NamTK")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("12345"), std::string("P3N")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Orange"), std::string("taste")}, {std::string("taste"), std::string("z6v7")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("12345"), std::string("rit9")}, {std::string("Naime"), std::string("oz")}, {std::string("jdis4OlnA"), std::string("yRY")}})), (false));
}

TEST(Probe, check_dict_case_02) {
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Houston"), std::string("Orange")}, {std::string("tl2"), std::string("kTd")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Ol"), std::string("yBECkWXBqmby")}, {std::string("bnanA"), std::string("12345")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("5"), std::string("Ng")}, {std::string("lc"), std::string("B")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Btame"), std::string("5")}, {std::string("a"), std::string("12345")}, {std::string("esVEf"), std::string("BD5")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("B"), std::string("zII hnMKBlll")}, {std::string("taste"), std::string("oston")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("CIsTy"), std::string("")}, {std::string("Q"), std::string("Rz")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("8bQ8CbQ92"), std::string("ZIP")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Jouston"), std::string("A")}, {std::string("cx33KdI JXMB"), std::string("Z1P")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("A"), std::string("taste")}, {std::string("ke"), std::string("apple")}, {std::string("pineapple"), std::string("Ja7m")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Ws0Do2AoE"), std::string("cMfG")}, {std::string("b"), std::string("8")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("t"), std::string("isLixH")}})), (true));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("LLC"), std::string("37")}, {std::string("ZgXPLe"), std::string("houstKon")}, {std::string("f4"), std::string("WqdoWa")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("A"), std::string("uj6zz")}})), (true));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("oc"), std::string("TATE")}})), (true));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string(""), std::string("LYaCMwJBbGN")}, {std::string("KZeKKKIB"), std::string("IJbPsNnV")}, {std::string("fRuit"), std::string("PS")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("c4yL8"), std::string(" ZMuMgrHZCde")}, {std::string("pineapple"), std::string("banvan")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string(""), std::string("kJANu")}, {std::string("SwEet"), std::string("kyo")}, {std::string("pineapple"), std::string("tastVT")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("LqjnXqWE4"), std::string("taste")}, {std::string("S"), std::string("VKoqcR7r")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("3sJhn"), std::string("iweet")}, {std::string("5"), std::string("B")}, {std::string("aPPlE"), std::string("ksyte")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("36"), std::string("8")}, {std::string("4kZBYIg"), std::string("NC")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("Name"), std::string("s")}, {std::string("smk"), std::string("z")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("234"), std::string("wa")}, {std::string("Pf"), std::string("Sweet")}, {std::string("ZI"), std::string("s2wnyp0g")}})), (false));
    EXPECT_EQ((check_dict_case(std::map<std::string, std::string >{{std::string("j"), std::string("1d3V45")}, {std::string("o"), std::string("frai1t")}})), (true));
}

TEST(Probe, count_up_to_01) {
    EXPECT_EQ((count_up_to(8)), (std::vector<int >{2, 3, 5, 7}));
    EXPECT_EQ((count_up_to(14)), (std::vector<int >{2, 3, 5, 7, 11, 13}));
    EXPECT_EQ((count_up_to(0)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(-355)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(5)), (std::vector<int >{2, 3}));
    EXPECT_EQ((count_up_to(43)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41}));
    EXPECT_EQ((count_up_to(21)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19}));
    EXPECT_EQ((count_up_to(11)), (std::vector<int >{2, 3, 5, 7}));
    EXPECT_EQ((count_up_to(422)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421}));
    EXPECT_EQ((count_up_to(6)), (std::vector<int >{2, 3, 5}));
    EXPECT_EQ((count_up_to(31)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}));
    EXPECT_EQ((count_up_to(-5)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(27)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23}));
    EXPECT_EQ((count_up_to(-1)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(4)), (std::vector<int >{2, 3}));
    EXPECT_EQ((count_up_to(717)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709}));
    EXPECT_EQ((count_up_to(-2)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(-4)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(30)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}));
    EXPECT_EQ((count_up_to(91)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89}));
    EXPECT_EQ((count_up_to(103)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101}));
    EXPECT_EQ((count_up_to(23)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19}));
    EXPECT_EQ((count_up_to(-9)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(101)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}));
    EXPECT_EQ((count_up_to(3)), (std::vector<int >{2}));
}

TEST(Probe, count_up_to_02) {
    EXPECT_EQ((count_up_to(16)), (std::vector<int >{2, 3, 5, 7, 11, 13}));
    EXPECT_EQ((count_up_to(190)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181}));
    EXPECT_EQ((count_up_to(-7)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(12)), (std::vector<int >{2, 3, 5, 7, 11}));
    EXPECT_EQ((count_up_to(18)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17}));
    EXPECT_EQ((count_up_to(19)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17}));
    EXPECT_EQ((count_up_to(269)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263}));
    EXPECT_EQ((count_up_to(71)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67}));
    EXPECT_EQ((count_up_to(33)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}));
    EXPECT_EQ((count_up_to(47)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43}));
    EXPECT_EQ((count_up_to(79)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73}));
    EXPECT_EQ((count_up_to(-590)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(55)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53}));
    EXPECT_EQ((count_up_to(20)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19}));
    EXPECT_EQ((count_up_to(44)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43}));
    EXPECT_EQ((count_up_to(37)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}));
    EXPECT_EQ((count_up_to(7)), (std::vector<int >{2, 3, 5}));
    EXPECT_EQ((count_up_to(59)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53}));
    EXPECT_EQ((count_up_to(53)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}));
    EXPECT_EQ((count_up_to(17)), (std::vector<int >{2, 3, 5, 7, 11, 13}));
    EXPECT_EQ((count_up_to(-8)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(-135)), (std::vector<int >{}));
    EXPECT_EQ((count_up_to(29)), (std::vector<int >{2, 3, 5, 7, 11, 13, 17, 19, 23}));
}
