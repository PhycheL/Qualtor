// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_02.h"

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

TEST(Probe, sum_product_01) {
    EXPECT_EQ((sum_product(std::vector<int >{10, 10})), (std::vector<int >{20, 100}));
    EXPECT_EQ((sum_product(std::vector<int >{-3, 8, 0, 3, 0})), (std::vector<int >{8, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{100, 0})), (std::vector<int >{100, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{10, 24})), (std::vector<int >{34, 240}));
    EXPECT_EQ((sum_product(std::vector<int >{-5, 313, -3, 19, 0})), (std::vector<int >{324, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{3, 5, 7})), (std::vector<int >{15, 105}));
    EXPECT_EQ((sum_product(std::vector<int >{23})), (std::vector<int >{23, 23}));
    EXPECT_EQ((sum_product(std::vector<int >{0, 100})), (std::vector<int >{100, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{22, -7})), (std::vector<int >{15, -154}));
    EXPECT_EQ((sum_product(std::vector<int >{3, 1, 12345, 199, -1})), (std::vector<int >{12547, -7369965}));
    EXPECT_EQ((sum_product(std::vector<int >{3, 5, 7, 4})), (std::vector<int >{19, 420}));
    EXPECT_EQ((sum_product(std::vector<int >{7, 100, 6, 1, 6})), (std::vector<int >{120, 25200}));
    EXPECT_EQ((sum_product(std::vector<int >{10, 4})), (std::vector<int >{14, 40}));
    EXPECT_EQ((sum_product(std::vector<int >{100})), (std::vector<int >{100, 100}));
    EXPECT_EQ((sum_product(std::vector<int >{4, 300, 0, 16, 20, 12})), (std::vector<int >{352, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{0, 4, -557, 8, 1, 29, 2, 7})), (std::vector<int >{-506, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{1, 24, -9, 100, 2, 25})), (std::vector<int >{143, -1080000}));
    EXPECT_EQ((sum_product(std::vector<int >{0, 1})), (std::vector<int >{1, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{3, 7})), (std::vector<int >{10, 21}));
    EXPECT_EQ((sum_product(std::vector<int >{1, 2, 3, 4, 22})), (std::vector<int >{32, 528}));
    EXPECT_EQ((sum_product(std::vector<int >{0, 1, 0})), (std::vector<int >{1, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{26, 4, 2, -3})), (std::vector<int >{29, -624}));
    EXPECT_EQ((sum_product(std::vector<int >{10, -777})), (std::vector<int >{-767, -7770}));
    EXPECT_EQ((sum_product(std::vector<int >{10, 4, -489, 10})), (std::vector<int >{-465, -195600}));
    EXPECT_EQ((sum_product(std::vector<int >{10})), (std::vector<int >{10, 10}));
}

TEST(Probe, sum_product_02) {
    EXPECT_EQ((sum_product(std::vector<int >{3})), (std::vector<int >{3, 3}));
    EXPECT_EQ((sum_product(std::vector<int >{24, 4})), (std::vector<int >{28, 96}));
    EXPECT_EQ((sum_product(std::vector<int >{30})), (std::vector<int >{30, 30}));
    EXPECT_EQ((sum_product(std::vector<int >{4, 6, 5, 15, 15, 7})), (std::vector<int >{52, 189000}));
    EXPECT_EQ((sum_product(std::vector<int >{3, 5, 7, 2})), (std::vector<int >{17, 210}));
    EXPECT_EQ((sum_product(std::vector<int >{30, 1, 1})), (std::vector<int >{32, 30}));
    EXPECT_EQ((sum_product(std::vector<int >{100, 100})), (std::vector<int >{200, 10000}));
    EXPECT_EQ((sum_product(std::vector<int >{7, -451, 2, 832, 135, 1})), (std::vector<int >{526, -709188480}));
    EXPECT_EQ((sum_product(std::vector<int >{2})), (std::vector<int >{2, 2}));
    EXPECT_EQ((sum_product(std::vector<int >{1, 2, 6, 4})), (std::vector<int >{13, 48}));
    EXPECT_EQ((sum_product(std::vector<int >{24})), (std::vector<int >{24, 24}));
    EXPECT_EQ((sum_product(std::vector<int >{3, 2, 24, 10, 4})), (std::vector<int >{43, 5760}));
    EXPECT_EQ((sum_product(std::vector<int >{16, 1, 26, 4, 8, 0, 1, 4})), (std::vector<int >{60, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{30, -1, 21, 939, 14, 0, 3})), (std::vector<int >{1006, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{100, 0, 9})), (std::vector<int >{109, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{5})), (std::vector<int >{5, 5}));
    EXPECT_EQ((sum_product(std::vector<int >{13, 4, 5, 10})), (std::vector<int >{32, 2600}));
    EXPECT_EQ((sum_product(std::vector<int >{7, 29})), (std::vector<int >{36, 203}));
    EXPECT_EQ((sum_product(std::vector<int >{0, 1, -844})), (std::vector<int >{-843, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{15, 2, -2, 100})), (std::vector<int >{115, -6000}));
    EXPECT_EQ((sum_product(std::vector<int >{1, 1})), (std::vector<int >{2, 1}));
    EXPECT_EQ((sum_product(std::vector<int >{0, 6})), (std::vector<int >{6, 0}));
    EXPECT_EQ((sum_product(std::vector<int >{1, 1, 1, 99999})), (std::vector<int >{100002, 99999}));
}

TEST(Probe, rolling_max_01) {
    EXPECT_EQ((rolling_max(std::vector<int >{4, 3, 2, 1})), (std::vector<int >{4, 4, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, 2, 3})), (std::vector<int >{1, 2, 3}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 2, 100, 3})), (std::vector<int >{3, 3, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{190, 533, -5, 102, 25, 17, 6})), (std::vector<int >{190, 533, 533, 533, 533, 533, 533}));
    EXPECT_EQ((rolling_max(std::vector<int >{101, 102, 4})), (std::vector<int >{101, 102, 102}));
    EXPECT_EQ((rolling_max(std::vector<int >{2})), (std::vector<int >{2}));
    EXPECT_EQ((rolling_max(std::vector<int >{4, 4, 4})), (std::vector<int >{4, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{2, -5, 29, -990})), (std::vector<int >{2, 2, 29, 29}));
    EXPECT_EQ((rolling_max(std::vector<int >{489, 2, 3, 4})), (std::vector<int >{489, 489, 489, 489}));
    EXPECT_EQ((rolling_max(std::vector<int >{469, 4, 21})), (std::vector<int >{469, 469, 469}));
    EXPECT_EQ((rolling_max(std::vector<int >{846, 2, 4, 274, 235})), (std::vector<int >{846, 846, 846, 846, 846}));
    EXPECT_EQ((rolling_max(std::vector<int >{-835, 543, 100, 30})), (std::vector<int >{0, 543, 543, 543}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 2, 3, 100, -573})), (std::vector<int >{3, 3, 3, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, 2, 3, 2, 3, 4, 2})), (std::vector<int >{1, 2, 3, 3, 3, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, 2, 3, 4, -465})), (std::vector<int >{1, 2, 3, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 3, 3, 100, 100})), (std::vector<int >{3, 3, 3, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{-104, -779})), (std::vector<int >{0, 0}));
    EXPECT_EQ((rolling_max(std::vector<int >{4, 4, 4, 4})), (std::vector<int >{4, 4, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{100, -739, 29, 26, 0})), (std::vector<int >{100, 100, 100, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, 2, 3, 3, 4, 4})), (std::vector<int >{1, 2, 3, 3, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{4, 3, -7, 3, 100, 6, 26})), (std::vector<int >{4, 4, 4, 4, 100, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{610})), (std::vector<int >{610}));
    EXPECT_EQ((rolling_max(std::vector<int >{2, 2, 3, 100, 3})), (std::vector<int >{2, 2, 3, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{4, 3, 2, 1, -3})), (std::vector<int >{4, 4, 4, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 2, 3, 100, 3})), (std::vector<int >{3, 3, 3, 100, 100}));
}

TEST(Probe, rolling_max_02) {
    EXPECT_EQ((rolling_max(std::vector<int >{3, 2, 3, 9, 3})), (std::vector<int >{3, 3, 3, 9, 9}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, 2, 3, 4})), (std::vector<int >{1, 2, 3, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{20, -1, 100, 3, 3})), (std::vector<int >{20, 20, 100, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{82, 3})), (std::vector<int >{82, 82}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 3, 2, 100, 100})), (std::vector<int >{3, 3, 3, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, 2, 3, 4, 0})), (std::vector<int >{1, 2, 3, 4, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{100, 3, 3, 100, 3})), (std::vector<int >{100, 100, 100, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{4, 11})), (std::vector<int >{4, 11}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, -1, 3, 4})), (std::vector<int >{1, 1, 3, 4}));
    EXPECT_EQ((rolling_max(std::vector<int >{4, 4, 4, 22})), (std::vector<int >{4, 4, 4, 22}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 3, 100, 100})), (std::vector<int >{3, 3, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{27})), (std::vector<int >{27}));
    EXPECT_EQ((rolling_max(std::vector<int >{-571, 0, 5, 4, 11, -1})), (std::vector<int >{0, 0, 5, 5, 11, 11}));
    EXPECT_EQ((rolling_max(std::vector<int >{495, 189, 0})), (std::vector<int >{495, 495, 495}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 2, 3, 100, 3, 17})), (std::vector<int >{3, 3, 3, 100, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{22, 4, -5})), (std::vector<int >{22, 22, 22}));
    EXPECT_EQ((rolling_max(std::vector<int >{1, 2, 3, 2, 3, 4, 2, 644})), (std::vector<int >{1, 2, 3, 3, 3, 4, 4, 644}));
    EXPECT_EQ((rolling_max(std::vector<int >{27, -1, 0, -617, -2, 100, 100})), (std::vector<int >{27, 27, 27, 27, 27, 100, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{0, 1, 4, 1, 14, 19})), (std::vector<int >{0, 1, 4, 4, 14, 19}));
    EXPECT_EQ((rolling_max(std::vector<int >{19, 3, 1, 5, 4})), (std::vector<int >{19, 19, 19, 19, 19}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 157, 28})), (std::vector<int >{3, 157, 157}));
    EXPECT_EQ((rolling_max(std::vector<int >{3, 3, 3, 100})), (std::vector<int >{3, 3, 3, 100}));
    EXPECT_EQ((rolling_max(std::vector<int >{-5})), (std::vector<int >{0}));
}

TEST(Probe, is_palindrome_01) {
    EXPECT_EQ((is_palindrome(std::string("Q"))), (true));
    EXPECT_EQ((is_palindrome(std::string("cata"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xyvszx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("U8XIDbX5 f"))), (false));
    EXPECT_EQ((is_palindrome(std::string("jeFryrrej"))), (false));
    EXPECT_EQ((is_palindrome(std::string("Zu"))), (false));
    EXPECT_EQ((is_palindrome(std::string("x"))), (true));
    EXPECT_EQ((is_palindrome(std::string("catac"))), (true));
    EXPECT_EQ((is_palindrome(std::string("Tge"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xyzOgu"))), (false));
    EXPECT_EQ((is_palindrome(std::string("5vvvwY40V9n"))), (false));
    EXPECT_EQ((is_palindrome(std::string("5xyzyx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("gd"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xyx"))), (true));
    EXPECT_EQ((is_palindrome(std::string("jerryrrej"))), (true));
    EXPECT_EQ((is_palindrome(std::string("sQiyhu"))), (false));
    EXPECT_EQ((is_palindrome(std::string("w"))), (true));
    EXPECT_EQ((is_palindrome(std::string("u"))), (true));
    EXPECT_EQ((is_palindrome(std::string("uIejLGT"))), (false));
    EXPECT_EQ((is_palindrome(std::string("Kq"))), (false));
    EXPECT_EQ((is_palindrome(std::string("A"))), (true));
    EXPECT_EQ((is_palindrome(std::string("bkyz"))), (false));
    EXPECT_EQ((is_palindrome(std::string("hH4EsPIlrQno"))), (false));
    EXPECT_EQ((is_palindrome(std::string("Wg8zoNrvZ"))), (false));
    EXPECT_EQ((is_palindrome(std::string("F"))), (true));
}

TEST(Probe, is_palindrome_02) {
    EXPECT_EQ((is_palindrome(std::string("xQz"))), (false));
    EXPECT_EQ((is_palindrome(std::string("pataLc"))), (false));
    EXPECT_EQ((is_palindrome(std::string("FOKUUq"))), (false));
    EXPECT_EQ((is_palindrome(std::string("x2yUx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("ox"))), (false));
    EXPECT_EQ((is_palindrome(std::string("kyW"))), (false));
    EXPECT_EQ((is_palindrome(std::string("ca5a"))), (false));
    EXPECT_EQ((is_palindrome(std::string("X"))), (true));
    EXPECT_EQ((is_palindrome(std::string("xyz"))), (false));
    EXPECT_EQ((is_palindrome(std::string("yx"))), (false));
    EXPECT_EQ((is_palindrome(std::string("xOx"))), (true));
    EXPECT_EQ((is_palindrome(std::string("F0"))), (false));
    EXPECT_EQ((is_palindrome(std::string("cEtaSc"))), (false));
    EXPECT_EQ((is_palindrome(std::string("5ewA4"))), (false));
    EXPECT_EQ((is_palindrome(std::string("zB"))), (false));
    EXPECT_EQ((is_palindrome(std::string("ypMOVOX2oiJ"))), (false));
    EXPECT_EQ((is_palindrome(std::string("Lxw"))), (false));
    EXPECT_EQ((is_palindrome(std::string("catT"))), (false));
    EXPECT_EQ((is_palindrome(std::string("erryrarwj"))), (false));
    EXPECT_EQ((is_palindrome(std::string("TQiz6PJepi"))), (false));
    EXPECT_EQ((is_palindrome(std::string("Z"))), (true));
    EXPECT_EQ((is_palindrome(std::string("zCqrHs"))), (false));
    EXPECT_EQ((is_palindrome(std::string("jeryrrej"))), (false));
}

TEST(Probe, make_palindrome_01) {
    EXPECT_EQ((make_palindrome(std::string("jerry"))), (std::string("jerryrrej")));
    EXPECT_EQ((make_palindrome(std::string("caac"))), (std::string("caac")));
    EXPECT_EQ((make_palindrome(std::string("jer"))), (std::string("jerej")));
    EXPECT_EQ((make_palindrome(std::string("cat"))), (std::string("catac")));
    EXPECT_EQ((make_palindrome(std::string("xgcO jVmD3w"))), (std::string("xgcO jVmD3w3DmVj Ocgx")));
    EXPECT_EQ((make_palindrome(std::string("yKjq"))), (std::string("yKjqjKy")));
    EXPECT_EQ((make_palindrome(std::string("mNKEiO4T"))), (std::string("mNKEiO4T4OiEKNm")));
    EXPECT_EQ((make_palindrome(std::string("2sSqB"))), (std::string("2sSqBqSs2")));
    EXPECT_EQ((make_palindrome(std::string("jbqMcU"))), (std::string("jbqMcUcMqbj")));
    EXPECT_EQ((make_palindrome(std::string("clbUMx2wq4"))), (std::string("clbUMx2wq4qw2xMUblc")));
    EXPECT_EQ((make_palindrome(std::string("Tr8sW"))), (std::string("Tr8sWs8rT")));
    EXPECT_EQ((make_palindrome(std::string("GDB"))), (std::string("GDBDG")));
    EXPECT_EQ((make_palindrome(std::string("jerrrej"))), (std::string("jerrrej")));
    EXPECT_EQ((make_palindrome(std::string("yzyx"))), (std::string("yzyxyzy")));
    EXPECT_EQ((make_palindrome(std::string("21EN4dnXLR"))), (std::string("21EN4dnXLRLXnd4NE12")));
    EXPECT_EQ((make_palindrome(std::string("t7Wo"))), (std::string("t7WoW7t")));
    EXPECT_EQ((make_palindrome(std::string("xyx"))), (std::string("xyx")));
    EXPECT_EQ((make_palindrome(std::string("catac"))), (std::string("catac")));
    EXPECT_EQ((make_palindrome(std::string("xOyb"))), (std::string("xOybyOx")));
    EXPECT_EQ((make_palindrome(std::string("s"))), (std::string("s")));
    EXPECT_EQ((make_palindrome(std::string("jery"))), (std::string("jeryrej")));
    EXPECT_EQ((make_palindrome(std::string("7cata"))), (std::string("7catac7")));
    EXPECT_EQ((make_palindrome(std::string("ata"))), (std::string("ata")));
    EXPECT_EQ((make_palindrome(std::string("cfg"))), (std::string("cfgfc")));
    EXPECT_EQ((make_palindrome(std::string("aL"))), (std::string("aLa")));
}

TEST(Probe, make_palindrome_02) {
    EXPECT_EQ((make_palindrome(std::string("NIqmGlVazzTF"))), (std::string("NIqmGlVazzTFTzzaVlGmqIN")));
    EXPECT_EQ((make_palindrome(std::string("kV1g"))), (std::string("kV1g1Vk")));
    EXPECT_EQ((make_palindrome(std::string("jerryrnjSej"))), (std::string("jerryrnjSejeSjnryrrej")));
    EXPECT_EQ((make_palindrome(std::string("fSQVv85NT"))), (std::string("fSQVv85NTN58vVQSf")));
    EXPECT_EQ((make_palindrome(std::string("kUpkH"))), (std::string("kUpkHkpUk")));
    EXPECT_EQ((make_palindrome(std::string("j7rryrre"))), (std::string("j7rryrrerryrr7j")));
    EXPECT_EQ((make_palindrome(std::string("Qh"))), (std::string("QhQ")));
    EXPECT_EQ((make_palindrome(std::string("oto9d"))), (std::string("oto9d9oto")));
    EXPECT_EQ((make_palindrome(std::string("cAtac"))), (std::string("cAtacatAc")));
    EXPECT_EQ((make_palindrome(std::string("65GKYocv"))), (std::string("65GKYocvcoYKG56")));
    EXPECT_EQ((make_palindrome(std::string("zerry"))), (std::string("zerryrrez")));
    EXPECT_EQ((make_palindrome(std::string("jefrry"))), (std::string("jefrryrrfej")));
    EXPECT_EQ((make_palindrome(std::string("8ZraXhsVGdAh"))), (std::string("8ZraXhsVGdAhAdGVshXarZ8")));
    EXPECT_EQ((make_palindrome(std::string("W"))), (std::string("W")));
    EXPECT_EQ((make_palindrome(std::string("Q"))), (std::string("Q")));
    EXPECT_EQ((make_palindrome(std::string("caa"))), (std::string("caac")));
    EXPECT_EQ((make_palindrome(std::string("IRvPrm8FrLpg"))), (std::string("IRvPrm8FrLpgpLrF8mrPvRI")));
    EXPECT_EQ((make_palindrome(std::string("K"))), (std::string("K")));
    EXPECT_EQ((make_palindrome(std::string(" FxpQJ85ui"))), (std::string(" FxpQJ85uiu58JQpxF ")));
    EXPECT_EQ((make_palindrome(std::string("e"))), (std::string("e")));
    EXPECT_EQ((make_palindrome(std::string("TMx77PQ"))), (std::string("TMx77PQP77xMT")));
    EXPECT_EQ((make_palindrome(std::string("xzhy"))), (std::string("xzhyhzx")));
    EXPECT_EQ((make_palindrome(std::string("xy8x"))), (std::string("xy8x8yx")));
}

TEST(Probe, string_xor_01) {
    EXPECT_EQ((string_xor(std::string("s1"), std::string("100"))), (std::string("11")));
    EXPECT_EQ((string_xor(std::string("0101"), std::string("1"))), (std::string("1")));
    EXPECT_EQ((string_xor(std::string("000F0"), std::string("0000"))), (std::string("0001")));
    EXPECT_EQ((string_xor(std::string("EygnJpvwou"), std::string("100"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("010"), std::string("1010N0"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("010"), std::string(""))), (std::string("")));
    EXPECT_EQ((string_xor(std::string("111000"), std::string("010010"))), (std::string("101010")));
    EXPECT_EQ((string_xor(std::string("010"), std::string("0951R0"))), (std::string("011")));
    EXPECT_EQ((string_xor(std::string("UV"), std::string("7Mjg0tmxGO5C"))), (std::string("11")));
    EXPECT_EQ((string_xor(std::string("J0910"), std::string("101010"))), (std::string("10111")));
    EXPECT_EQ((string_xor(std::string("wjP4z2ie"), std::string("1011V0"))), (std::string("111111")));
    EXPECT_EQ((string_xor(std::string("0101"), std::string("0101"))), (std::string("0000")));
    EXPECT_EQ((string_xor(std::string("01 01"), std::string("101010"))), (std::string("11100")));
    EXPECT_EQ((string_xor(std::string("G000U"), std::string("jN8s9u"))), (std::string("11111")));
    EXPECT_EQ((string_xor(std::string("110"), std::string("zLlZvlPY0ws"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("0101"), std::string("i"))), (std::string("1")));
    EXPECT_EQ((string_xor(std::string("0m10L010"), std::string("F10"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("101010"), std::string("010"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("zd0QZJ"), std::string("111000"))), (std::string("111111")));
    EXPECT_EQ((string_xor(std::string("V"), std::string("00G0V0"))), (std::string("1")));
    EXPECT_EQ((string_xor(std::string("14rqw7"), std::string("1000"))), (std::string("0111")));
    EXPECT_EQ((string_xor(std::string("2QtjIoLkXlV"), std::string("10"))), (std::string("11")));
    EXPECT_EQ((string_xor(std::string("101010"), std::string("z"))), (std::string("1")));
    EXPECT_EQ((string_xor(std::string("010"), std::string("GNVswzPvTyb1"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("b5LmMHha"), std::string("0R1f0"))), (std::string("11111")));
}

TEST(Probe, string_xor_02) {
    EXPECT_EQ((string_xor(std::string("wzucz"), std::string("1010A10"))), (std::string("11111")));
    EXPECT_EQ((string_xor(std::string("c"), std::string("110"))), (std::string("1")));
    EXPECT_EQ((string_xor(std::string("00"), std::string("1"))), (std::string("1")));
    EXPECT_EQ((string_xor(std::string("10l10"), std::string("0"))), (std::string("1")));
    EXPECT_EQ((string_xor(std::string("1W0"), std::string("1d0101w"))), (std::string("010")));
    EXPECT_EQ((string_xor(std::string("0101"), std::string(""))), (std::string("")));
    EXPECT_EQ((string_xor(std::string("100"), std::string("5tf epLPKcUo"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("Jy04IB"), std::string("I1"))), (std::string("11")));
    EXPECT_EQ((string_xor(std::string("010"), std::string("IajI"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("b1"), std::string("0000"))), (std::string("11")));
    EXPECT_EQ((string_xor(std::string("010"), std::string("101010"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("rsD 7 "), std::string("110"))), (std::string("111")));
    EXPECT_EQ((string_xor(std::string("11000"), std::string("61x0"))), (std::string("1010")));
    EXPECT_EQ((string_xor(std::string("010010"), std::string("010010"))), (std::string("000000")));
    EXPECT_EQ((string_xor(std::string("1"), std::string("5MjRcXzHN"))), (std::string("1")));
    EXPECT_EQ((string_xor(std::string("cq"), std::string("0"))), (std::string("1")));
    EXPECT_EQ((string_xor(std::string("1100"), std::string("101010"))), (std::string("0110")));
    EXPECT_EQ((string_xor(std::string("0N10"), std::string("0110"))), (std::string("0100")));
    EXPECT_EQ((string_xor(std::string("Q01010"), std::string("y1 010"))), (std::string("111000")));
    EXPECT_EQ((string_xor(std::string("20f1"), std::string("0100b10"))), (std::string("1111")));
    EXPECT_EQ((string_xor(std::string("T4"), std::string("6g"))), (std::string("11")));
    EXPECT_EQ((string_xor(std::string("b101"), std::string("010010"))), (std::string("1001")));
    EXPECT_EQ((string_xor(std::string("d6atZs73lDfL"), std::string("0g0010"))), (std::string("111111")));
}

TEST(Probe, longest_01) {
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x")})), (std::string("x")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("cr9Opi")})), (std::string("cr9Opi")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("tw2Qw"), std::string("4r5"), std::string("zzzz"), std::string("N4Uwipz14Asm"), std::string("yt")})), (std::string("N4Uwipz14Asm")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("www"), std::string("jd"), std::string("XcbGws7OrzLI"), std::string("O"), std::string("1lu0zyXUVJV"), std::string("s"), std::string("hXpKIaF"), std::string("3W")})), (std::string("XcbGws7OrzLI")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("abc"), std::string("zzzz"), std::string("www"), std::string("kkkk"), std::string("yyy")})), (std::string("zzzz")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("b"), std::string("z"), std::string("ccc"), std::string("k85"), std::string("www"), std::string("N"), std::string("UGr6s"), std::string("")})), (std::string("UGr6s")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("a"), std::string("b"), std::string("c")})), (std::string("a")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("www")})), (std::string("www")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("a"), std::string("c")})), (std::string("a")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("a"), std::string("bb"), std::string("ccc"), std::string("")})), (std::string("ccc")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("a"), std::string("b"), std::string("a")})), (std::string("a")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("yyy"), std::string("zzzz"), std::string("www"), std::string("kkkk"), std::string("bb")})), (std::string("zzzz")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("2Wc lS"), std::string("2Py9"), std::string(" jxlyean"), std::string("b"), std::string(" b")})), (std::string(" jxlyean")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("z"), std::string("y"), std::string("x")})), (std::string("z")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("yyy"), std::string("zzzz"), std::string("ccc"), std::string("kkkk"), std::string("abc")})), (std::string("zzzz")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("yyy"), std::string("kkkk"), std::string("www"), std::string("zzzz"), std::string("abc")})), (std::string("kkkk")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("a"), std::string("ccc"), std::string("bb")})), (std::string("ccc")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("ccc"), std::string("z")})), (std::string("ccc")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("y"), std::string("En3")})), (std::string("En3")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("www"), std::string("yyy"), std::string("c")})), (std::string("www")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("yyy"), std::string("zzzz"), std::string("www"), std::string("kkkk"), std::string("abc")})), (std::string("zzzz")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("a"), std::string("bb"), std::string("ccc")})), (std::string("ccc")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string(""), std::string("0oVFuL1wMW0M"), std::string("bt"), std::string("7jPTPNjB2Zzj"), std::string("kkk"), std::string("b")})), (std::string("0oVFuL1wMW0M")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("NQw")})), (std::string("NQw")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("V")})), (std::string("V")));
}

TEST(Probe, longest_02) {
    EXPECT_EQ((longest(std::vector<std::string >{std::string("kkk")})), (std::string("kkk")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("yyy"), std::string("zzzz"), std::string("Pvb"), std::string("kkkk"), std::string("abc")})), (std::string("zzzz")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("yyy"), std::string("www"), std::string("zzzz"), std::string("kkkk"), std::string("abc")})), (std::string("zzzz")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("c"), std::string("b"), std::string("a")})), (std::string("c")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("7")})), (std::string("7")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("tvlVCbWF"), std::string("z"), std::string("x"), std::string(""), std::string("c"), std::string("b"), std::string("abc")})), (std::string("tvlVCbWF")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("z")})), (std::string("x")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("G"), std::string(""), std::string("twRYoc")})), (std::string("twRYoc")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("dkk7kLk"), std::string("y"), std::string("z")})), (std::string("dkk7kLk")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("a")})), (std::string("a")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("bb"), std::string("7yNmA5"), std::string(""), std::string("jAy"), std::string("ab"), std::string("p")})), (std::string("7yNmA5")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("a"), std::string("c"), std::string("b")})), (std::string("a")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string(""), std::string("olA1l"), std::string("1yy"), std::string("wCwl"), std::string(""), std::string("c")})), (std::string("olA1l")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("yyy"), std::string("of"), std::string("lpi1ODy5"), std::string("x"), std::string("z"), std::string("Vx")})), (std::string("lpi1ODy5")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("x"), std::string("z"), std::string("y")})), (std::string("x")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("kkkk")})), (std::string("kkkk")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("G"), std::string("b"), std::string("c")})), (std::string("G")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("y")})), (std::string("y")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("a"), std::string("bb"), std::string("ya")})), (std::string("bb")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("zzzz"), std::string("bb")})), (std::string("zzzz")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("aIMZN"), std::string("L"), std::string("PcTfcI"), std::string("8 zyvENptlL5"), std::string("b"), std::string("0tgxPaOSw"), std::string("Ny")})), (std::string("8 zyvENptlL5")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("d014adck3T9N"), std::string("b")})), (std::string("d014adck3T9N")));
    EXPECT_EQ((longest(std::vector<std::string >{std::string("T"), std::string("zzzz"), std::string("bb"), std::string("z"), std::string("www")})), (std::string("zzzz")));
}

TEST(Probe, greatest_common_divisor_01) {
    EXPECT_EQ((greatest_common_divisor(145, 23)), (1));
    EXPECT_EQ((greatest_common_divisor(16, 15)), (1));
    EXPECT_EQ((greatest_common_divisor(7, 9)), (1));
    EXPECT_EQ((greatest_common_divisor(19, 2)), (1));
    EXPECT_EQ((greatest_common_divisor(231, 17)), (1));
    EXPECT_EQ((greatest_common_divisor(1, 19)), (1));
    EXPECT_EQ((greatest_common_divisor(11, 23)), (1));
    EXPECT_EQ((greatest_common_divisor(14, 8)), (2));
    EXPECT_EQ((greatest_common_divisor(3, 14)), (1));
    EXPECT_EQ((greatest_common_divisor(47, 4)), (1));
    EXPECT_EQ((greatest_common_divisor(88, 25)), (1));
    EXPECT_EQ((greatest_common_divisor(8, 24)), (8));
    EXPECT_EQ((greatest_common_divisor(5, 14)), (1));
    EXPECT_EQ((greatest_common_divisor(4, 933)), (1));
    EXPECT_EQ((greatest_common_divisor(14, 50)), (2));
    EXPECT_EQ((greatest_common_divisor(3, 2)), (1));
    EXPECT_EQ((greatest_common_divisor(60, 17)), (1));
    EXPECT_EQ((greatest_common_divisor(10, 3)), (1));
    EXPECT_EQ((greatest_common_divisor(29, 14)), (1));
    EXPECT_EQ((greatest_common_divisor(25, 142)), (1));
    EXPECT_EQ((greatest_common_divisor(25, 1000)), (25));
    EXPECT_EQ((greatest_common_divisor(5, 60)), (5));
    EXPECT_EQ((greatest_common_divisor(1, 221)), (1));
    EXPECT_EQ((greatest_common_divisor(108, 27)), (27));
    EXPECT_EQ((greatest_common_divisor(21, 7)), (7));
}

TEST(Probe, greatest_common_divisor_02) {
    EXPECT_EQ((greatest_common_divisor(24, 5)), (1));
    EXPECT_EQ((greatest_common_divisor(20, 20)), (20));
    EXPECT_EQ((greatest_common_divisor(22, 17)), (1));
    EXPECT_EQ((greatest_common_divisor(35, 12)), (1));
    EXPECT_EQ((greatest_common_divisor(12, 20)), (4));
    EXPECT_EQ((greatest_common_divisor(-4, 0)), (-4));
    EXPECT_EQ((greatest_common_divisor(3, 26)), (1));
    EXPECT_EQ((greatest_common_divisor(72, 144)), (72));
    EXPECT_EQ((greatest_common_divisor(49, 62)), (1));
    EXPECT_EQ((greatest_common_divisor(10, 14)), (2));
    EXPECT_EQ((greatest_common_divisor(22, 3)), (1));
    EXPECT_EQ((greatest_common_divisor(148, 300)), (4));
    EXPECT_EQ((greatest_common_divisor(11, 13)), (1));
    EXPECT_EQ((greatest_common_divisor(3, 21)), (3));
    EXPECT_EQ((greatest_common_divisor(12345, 15)), (15));
    EXPECT_EQ((greatest_common_divisor(328, 51)), (1));
    EXPECT_EQ((greatest_common_divisor(144, 15)), (3));
    EXPECT_EQ((greatest_common_divisor(23, 8)), (1));
    EXPECT_EQ((greatest_common_divisor(60, 29)), (1));
    EXPECT_EQ((greatest_common_divisor(3, 49)), (1));
    EXPECT_EQ((greatest_common_divisor(9, 23)), (1));
    EXPECT_EQ((greatest_common_divisor(2, 7)), (1));
    EXPECT_EQ((greatest_common_divisor(15, 26)), (1));
}

TEST(Probe, all_prefixes_01) {
    EXPECT_EQ((all_prefixes(std::string("WWW"))), (std::vector<std::string >{std::string("W"), std::string("WW"), std::string("WWW")}));
    EXPECT_EQ((all_prefixes(std::string("a3sdfg"))), (std::vector<std::string >{std::string("a"), std::string("a3"), std::string("a3s"), std::string("a3sd"), std::string("a3sdf"), std::string("a3sdfg")}));
    EXPECT_EQ((all_prefixes(std::string("abc"))), (std::vector<std::string >{std::string("a"), std::string("ab"), std::string("abc")}));
    EXPECT_EQ((all_prefixes(std::string("xW"))), (std::vector<std::string >{std::string("x"), std::string("xW")}));
    EXPECT_EQ((all_prefixes(std::string("WW"))), (std::vector<std::string >{std::string("W"), std::string("WW")}));
    EXPECT_EQ((all_prefixes(std::string("at0sId"))), (std::vector<std::string >{std::string("a"), std::string("at"), std::string("at0"), std::string("at0s"), std::string("at0sI"), std::string("at0sId")}));
    EXPECT_EQ((all_prefixes(std::string("WW n"))), (std::vector<std::string >{std::string("W"), std::string("WW"), std::string("WW "), std::string("WW n")}));
    EXPECT_EQ((all_prefixes(std::string(""))), (std::vector<std::string >{}));
    EXPECT_EQ((all_prefixes(std::string("zZHo"))), (std::vector<std::string >{std::string("z"), std::string("zZ"), std::string("zZH"), std::string("zZHo")}));
    EXPECT_EQ((all_prefixes(std::string("pQS"))), (std::vector<std::string >{std::string("p"), std::string("pQ"), std::string("pQS")}));
    EXPECT_EQ((all_prefixes(std::string("asdf"))), (std::vector<std::string >{std::string("a"), std::string("as"), std::string("asd"), std::string("asdf")}));
    EXPECT_EQ((all_prefixes(std::string("7V"))), (std::vector<std::string >{std::string("7"), std::string("7V")}));
    EXPECT_EQ((all_prefixes(std::string("CHnkzH"))), (std::vector<std::string >{std::string("C"), std::string("CH"), std::string("CHn"), std::string("CHnk"), std::string("CHnkz"), std::string("CHnkzH")}));
    EXPECT_EQ((all_prefixes(std::string("WWsW"))), (std::vector<std::string >{std::string("W"), std::string("WW"), std::string("WWs"), std::string("WWsW")}));
    EXPECT_EQ((all_prefixes(std::string("vg"))), (std::vector<std::string >{std::string("v"), std::string("vg")}));
    EXPECT_EQ((all_prefixes(std::string("PWnW"))), (std::vector<std::string >{std::string("P"), std::string("PW"), std::string("PWn"), std::string("PWnW")}));
    EXPECT_EQ((all_prefixes(std::string("as"))), (std::vector<std::string >{std::string("a"), std::string("as")}));
    EXPECT_EQ((all_prefixes(std::string("kJa"))), (std::vector<std::string >{std::string("k"), std::string("kJ"), std::string("kJa")}));
    EXPECT_EQ((all_prefixes(std::string("lsk"))), (std::vector<std::string >{std::string("l"), std::string("ls"), std::string("lsk")}));
    EXPECT_EQ((all_prefixes(std::string("E"))), (std::vector<std::string >{std::string("E")}));
    EXPECT_EQ((all_prefixes(std::string("o3TQbRZ"))), (std::vector<std::string >{std::string("o"), std::string("o3"), std::string("o3T"), std::string("o3TQ"), std::string("o3TQb"), std::string("o3TQbR"), std::string("o3TQbRZ")}));
    EXPECT_EQ((all_prefixes(std::string("sdf9gh"))), (std::vector<std::string >{std::string("s"), std::string("sd"), std::string("sdf"), std::string("sdf9"), std::string("sdf9g"), std::string("sdf9gh")}));
    EXPECT_EQ((all_prefixes(std::string("XWW"))), (std::vector<std::string >{std::string("X"), std::string("XW"), std::string("XWW")}));
    EXPECT_EQ((all_prefixes(std::string("x7R1NQq"))), (std::vector<std::string >{std::string("x"), std::string("x7"), std::string("x7R"), std::string("x7R1"), std::string("x7R1N"), std::string("x7R1NQ"), std::string("x7R1NQq")}));
    EXPECT_EQ((all_prefixes(std::string("awnc"))), (std::vector<std::string >{std::string("a"), std::string("aw"), std::string("awn"), std::string("awnc")}));
}

TEST(Probe, all_prefixes_02) {
    EXPECT_EQ((all_prefixes(std::string("bsnfGchq"))), (std::vector<std::string >{std::string("b"), std::string("bs"), std::string("bsn"), std::string("bsnf"), std::string("bsnfG"), std::string("bsnfGc"), std::string("bsnfGch"), std::string("bsnfGchq")}));
    EXPECT_EQ((all_prefixes(std::string("dY"))), (std::vector<std::string >{std::string("d"), std::string("dY")}));
    EXPECT_EQ((all_prefixes(std::string("eMWICohv0ns"))), (std::vector<std::string >{std::string("e"), std::string("eM"), std::string("eMW"), std::string("eMWI"), std::string("eMWIC"), std::string("eMWICo"), std::string("eMWICoh"), std::string("eMWICohv"), std::string("eMWICohv0"), std::string("eMWICohv0n"), std::string("eMWICohv0ns")}));
    EXPECT_EQ((all_prefixes(std::string("Yfpi5lF4EZej"))), (std::vector<std::string >{std::string("Y"), std::string("Yf"), std::string("Yfp"), std::string("Yfpi"), std::string("Yfpi5"), std::string("Yfpi5l"), std::string("Yfpi5lF"), std::string("Yfpi5lF4"), std::string("Yfpi5lF4E"), std::string("Yfpi5lF4EZ"), std::string("Yfpi5lF4EZe"), std::string("Yfpi5lF4EZej")}));
    EXPECT_EQ((all_prefixes(std::string("a"))), (std::vector<std::string >{std::string("a")}));
    EXPECT_EQ((all_prefixes(std::string("0"))), (std::vector<std::string >{std::string("0")}));
    EXPECT_EQ((all_prefixes(std::string("sCb"))), (std::vector<std::string >{std::string("s"), std::string("sC"), std::string("sCb")}));
    EXPECT_EQ((all_prefixes(std::string("7O"))), (std::vector<std::string >{std::string("7"), std::string("7O")}));
    EXPECT_EQ((all_prefixes(std::string("aAs7df"))), (std::vector<std::string >{std::string("a"), std::string("aA"), std::string("aAs"), std::string("aAs7"), std::string("aAs7d"), std::string("aAs7df")}));
    EXPECT_EQ((all_prefixes(std::string("W"))), (std::vector<std::string >{std::string("W")}));
    EXPECT_EQ((all_prefixes(std::string("agFsd"))), (std::vector<std::string >{std::string("a"), std::string("ag"), std::string("agF"), std::string("agFs"), std::string("agFsd")}));
    EXPECT_EQ((all_prefixes(std::string("Wqc"))), (std::vector<std::string >{std::string("W"), std::string("Wq"), std::string("Wqc")}));
    EXPECT_EQ((all_prefixes(std::string("pDPqHd4mwUA5"))), (std::vector<std::string >{std::string("p"), std::string("pD"), std::string("pDP"), std::string("pDPq"), std::string("pDPqH"), std::string("pDPqHd"), std::string("pDPqHd4"), std::string("pDPqHd4m"), std::string("pDPqHd4mw"), std::string("pDPqHd4mwU"), std::string("pDPqHd4mwUA"), std::string("pDPqHd4mwUA5")}));
    EXPECT_EQ((all_prefixes(std::string("asdgh"))), (std::vector<std::string >{std::string("a"), std::string("as"), std::string("asd"), std::string("asdg"), std::string("asdgh")}));
    EXPECT_EQ((all_prefixes(std::string("WAWp"))), (std::vector<std::string >{std::string("W"), std::string("WA"), std::string("WAW"), std::string("WAWp")}));
    EXPECT_EQ((all_prefixes(std::string("3cKPDZl"))), (std::vector<std::string >{std::string("3"), std::string("3c"), std::string("3cK"), std::string("3cKP"), std::string("3cKPD"), std::string("3cKPDZ"), std::string("3cKPDZl")}));
    EXPECT_EQ((all_prefixes(std::string("0W"))), (std::vector<std::string >{std::string("0"), std::string("0W")}));
    EXPECT_EQ((all_prefixes(std::string("U"))), (std::vector<std::string >{std::string("U")}));
    EXPECT_EQ((all_prefixes(std::string("2kFYP3"))), (std::vector<std::string >{std::string("2"), std::string("2k"), std::string("2kF"), std::string("2kFY"), std::string("2kFYP"), std::string("2kFYP3")}));
    EXPECT_EQ((all_prefixes(std::string("ktM28TcX3Xp5"))), (std::vector<std::string >{std::string("k"), std::string("kt"), std::string("ktM"), std::string("ktM2"), std::string("ktM28"), std::string("ktM28T"), std::string("ktM28Tc"), std::string("ktM28TcX"), std::string("ktM28TcX3"), std::string("ktM28TcX3X"), std::string("ktM28TcX3Xp"), std::string("ktM28TcX3Xp5")}));
    EXPECT_EQ((all_prefixes(std::string("2jau655v"))), (std::vector<std::string >{std::string("2"), std::string("2j"), std::string("2ja"), std::string("2jau"), std::string("2jau6"), std::string("2jau65"), std::string("2jau655"), std::string("2jau655v")}));
    EXPECT_EQ((all_prefixes(std::string("xiRjuV8"))), (std::vector<std::string >{std::string("x"), std::string("xi"), std::string("xiR"), std::string("xiRj"), std::string("xiRju"), std::string("xiRjuV"), std::string("xiRjuV8")}));
    EXPECT_EQ((all_prefixes(std::string("1 z4JmX2"))), (std::vector<std::string >{std::string("1"), std::string("1 "), std::string("1 z"), std::string("1 z4"), std::string("1 z4J"), std::string("1 z4Jm"), std::string("1 z4JmX"), std::string("1 z4JmX2")}));
}

TEST(Probe, string_sequence_01) {
    EXPECT_EQ((string_sequence(5)), (std::string("0 1 2 3 4 5")));
    EXPECT_EQ((string_sequence(19)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19")));
    EXPECT_EQ((string_sequence(21)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21")));
    EXPECT_EQ((string_sequence(20)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20")));
    EXPECT_EQ((string_sequence(-618)), (std::string("0")));
    EXPECT_EQ((string_sequence(1)), (std::string("0 1")));
    EXPECT_EQ((string_sequence(14)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14")));
    EXPECT_EQ((string_sequence(9)), (std::string("0 1 2 3 4 5 6 7 8 9")));
    EXPECT_EQ((string_sequence(3)), (std::string("0 1 2 3")));
    EXPECT_EQ((string_sequence(713)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712 713")));
    EXPECT_EQ((string_sequence(7)), (std::string("0 1 2 3 4 5 6 7")));
    EXPECT_EQ((string_sequence(-745)), (std::string("0")));
    EXPECT_EQ((string_sequence(-895)), (std::string("0")));
    EXPECT_EQ((string_sequence(-9)), (std::string("0")));
    EXPECT_EQ((string_sequence(-602)), (std::string("0")));
    EXPECT_EQ((string_sequence(899)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712 713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729 730 731 732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750 751 752 753 754 755 756 757 758 759 760 761 762 763 764 765 766 767 768 769 770 771 772 773 774 775 776 777 778 779 780 781 782 783 784 785 786 787 788 789 790 791 792 793 794 795 796 797 798 799 800 801 802 803 804 805 806 807 808 809 810 811 812 813 814 815 816 817 818 819 820 821 822 823 824 825 826 827 828 829 830 831 832 833 834 835 836 837 838 839 840 841 842 843 844 845 846 847 848 849 850 851 852 853 854 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 873 874 875 876 877 878 879 880 881 882 883 884 885 886 887 888 889 890 891 892 893 894 895 896 897 898 899")));
    EXPECT_EQ((string_sequence(-255)), (std::string("0")));
    EXPECT_EQ((string_sequence(-28)), (std::string("0")));
    EXPECT_EQ((string_sequence(809)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712 713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729 730 731 732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750 751 752 753 754 755 756 757 758 759 760 761 762 763 764 765 766 767 768 769 770 771 772 773 774 775 776 777 778 779 780 781 782 783 784 785 786 787 788 789 790 791 792 793 794 795 796 797 798 799 800 801 802 803 804 805 806 807 808 809")));
    EXPECT_EQ((string_sequence(194)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194")));
    EXPECT_EQ((string_sequence(-3)), (std::string("0")));
    EXPECT_EQ((string_sequence(13)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13")));
    EXPECT_EQ((string_sequence(16)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16")));
    EXPECT_EQ((string_sequence(1000)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712 713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729 730 731 732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750 751 752 753 754 755 756 757 758 759 760 761 762 763 764 765 766 767 768 769 770 771 772 773 774 775 776 777 778 779 780 781 782 783 784 785 786 787 788 789 790 791 792 793 794 795 796 797 798 799 800 801 802 803 804 805 806 807 808 809 810 811 812 813 814 815 816 817 818 819 820 821 822 823 824 825 826 827 828 829 830 831 832 833 834 835 836 837 838 839 840 841 842 843 844 845 846 847 848 849 850 851 852 853 854 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 873 874 875 876 877 878 879 880 881 882 883 884 885 886 887 888 889 890 891 892 893 894 895 896 897 898 899 900 901 902 903 904 905 906 907 908 909 910 911 912 913 914 915 916 917 918 919 920 921 922 923 924 925 926 927 928 929 930 931 932 933 934 935 936 937 938 939 940 941 942 943 944 945 946 947 948 949 950 951 952 953 954 955 956 957 958 959 960 961 962 963 964 965 966 967 968 969 970 971 972 973 974 975 976 977 978 979 980 981 982 983 984 985 986 987 988 989 990 991 992 993 994 995 996 997 998 999 1000")));
    EXPECT_EQ((string_sequence(850)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712 713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729 730 731 732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750 751 752 753 754 755 756 757 758 759 760 761 762 763 764 765 766 767 768 769 770 771 772 773 774 775 776 777 778 779 780 781 782 783 784 785 786 787 788 789 790 791 792 793 794 795 796 797 798 799 800 801 802 803 804 805 806 807 808 809 810 811 812 813 814 815 816 817 818 819 820 821 822 823 824 825 826 827 828 829 830 831 832 833 834 835 836 837 838 839 840 841 842 843 844 845 846 847 848 849 850")));
}

TEST(Probe, string_sequence_02) {
    EXPECT_EQ((string_sequence(-2)), (std::string("0")));
    EXPECT_EQ((string_sequence(-8)), (std::string("0")));
    EXPECT_EQ((string_sequence(2)), (std::string("0 1 2")));
    EXPECT_EQ((string_sequence(25)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25")));
    EXPECT_EQ((string_sequence(4)), (std::string("0 1 2 3 4")));
    EXPECT_EQ((string_sequence(-10)), (std::string("0")));
    EXPECT_EQ((string_sequence(-128)), (std::string("0")));
    EXPECT_EQ((string_sequence(-49)), (std::string("0")));
    EXPECT_EQ((string_sequence(12)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12")));
    EXPECT_EQ((string_sequence(-6)), (std::string("0")));
    EXPECT_EQ((string_sequence(-466)), (std::string("0")));
    EXPECT_EQ((string_sequence(-4)), (std::string("0")));
    EXPECT_EQ((string_sequence(-126)), (std::string("0")));
    EXPECT_EQ((string_sequence(-231)), (std::string("0")));
    EXPECT_EQ((string_sequence(15)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15")));
    EXPECT_EQ((string_sequence(23)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23")));
    EXPECT_EQ((string_sequence(652)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652")));
    EXPECT_EQ((string_sequence(-654)), (std::string("0")));
    EXPECT_EQ((string_sequence(18)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18")));
    EXPECT_EQ((string_sequence(-614)), (std::string("0")));
    EXPECT_EQ((string_sequence(694)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694")));
    EXPECT_EQ((string_sequence(30)), (std::string("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30")));
}
