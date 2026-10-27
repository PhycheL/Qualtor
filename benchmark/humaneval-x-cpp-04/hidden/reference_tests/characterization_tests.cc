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

TEST(Characterization, factorize_01) {
    EXPECT_EQ((factorize(8)), (std::vector<int >{2, 2, 2}));
    EXPECT_EQ((factorize(26)), (std::vector<int >{2, 13}));
    EXPECT_EQ((factorize(29)), (std::vector<int >{29}));
    EXPECT_EQ((factorize(7)), (std::vector<int >{7}));
    EXPECT_EQ((factorize(28)), (std::vector<int >{2, 2, 7}));
    EXPECT_EQ((factorize(4)), (std::vector<int >{2, 2}));
    EXPECT_EQ((factorize(903)), (std::vector<int >{3, 7, 43}));
    EXPECT_EQ((factorize(0)), (std::vector<int >{0}));
    EXPECT_EQ((factorize(-1)), (std::vector<int >{-1}));
    EXPECT_EQ((factorize(-2)), (std::vector<int >{-2}));
    EXPECT_EQ((factorize(23)), (std::vector<int >{23}));
    EXPECT_EQ((factorize(19)), (std::vector<int >{19}));
}

TEST(Characterization, remove_duplicates_01) {
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 5, 4})), (std::vector<int >{1, 5, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{-8, 0, 1, -272})), (std::vector<int >{-8, 0, 1, -272}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 3, 2, 4})), (std::vector<int >{1, 3, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 3, 4, 3})), (std::vector<int >{1, 2, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 3, 4})), (std::vector<int >{1, 2, 3, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{1, 2, 275, 2, 4, 3, 5})), (std::vector<int >{1, 275, 4, 3, 5}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{5, -10, -8, -4, 28})), (std::vector<int >{5, -10, -8, -4, 28}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{5, 28, 4, 4, 3})), (std::vector<int >{5, 28, 3}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{212, 28})), (std::vector<int >{212, 28}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{2, 3, 4})), (std::vector<int >{2, 3, 4}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{3, 28})), (std::vector<int >{3, 28}));
    EXPECT_EQ((remove_duplicates(std::vector<int >{4, 2, 3, 4})), (std::vector<int >{2, 3}));
}

TEST(Characterization, filp_case_01) {
    EXPECT_EQ((filp_case(std::string(""))), (std::string("")));
    EXPECT_EQ((filp_case(std::string("hELLO!"))), (std::string("Hello!")));
    EXPECT_EQ((filp_case(std::string("tHESEVIOEENT DELIGHS HAVE VIOLENT ENDS"))), (std::string("Thesevioeent delighs have violent ends")));
    EXPECT_EQ((filp_case(std::string("7"))), (std::string("7")));
    EXPECT_EQ((filp_case(std::string("tHESE VIOLENT DELIGHTS HAVE VIOLENT ENDS"))), (std::string("These violent delights have violent ends")));
    EXPECT_EQ((filp_case(std::string("hELLO"))), (std::string("Hello")));
    EXPECT_EQ((filp_case(std::string("eELLh"))), (std::string("EellH")));
    EXPECT_EQ((filp_case(std::string("d5 tLp"))), (std::string("D5 TlP")));
    EXPECT_EQ((filp_case(std::string("Hello"))), (std::string("hELLO")));
    EXPECT_EQ((filp_case(std::string("E5LqO"))), (std::string("e5lQo")));
    EXPECT_EQ((filp_case(std::string("HeE1o!"))), (std::string("hEe1O!")));
    EXPECT_EQ((filp_case(std::string("Heljlo"))), (std::string("hELJLO")));
}

TEST(Characterization, concatenate_01) {
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z"), std::string("w"), std::string("k")})), (std::string("xyzwk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string(""), std::string("w"), std::string("k")})), (std::string("xywk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z"), std::string("w"), std::string("y")})), (std::string("xyzwy")));
    EXPECT_EQ((concatenate(std::vector<std::string >{})), (std::string("")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("kdjbR2")})), (std::string("kdjbR2")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("z")})), (std::string("xyz")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("w"), std::string("xyz"), std::string(""), std::string("abR"), std::string("y")})), (std::string("wxyzabRy")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("x"), std::string("y"), std::string("w"), std::string("k")})), (std::string("xywk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("H7 IE2fplY"), std::string("a"), std::string(""), std::string("xAzwk")})), (std::string("H7 IE2fplYaxAzwk")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("a"), std::string("b"), std::string("c")})), (std::string("abc")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("w"), std::string("yKjq"), std::string("mNKEiO4T"), std::string("k"), std::string("2sSqB"), std::string("jbqMcU"), std::string("clbUMx2wq4")})), (std::string("wyKjqmNKEiO4Tk2sSqBjbqMcUclbUMx2wq4")));
    EXPECT_EQ((concatenate(std::vector<std::string >{std::string("Wb")})), (std::string("Wb")));
}

TEST(Characterization, filter_by_prefix_01) {
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("L"), std::string("0xPyx"), std::string("rD0JRj5B9C")}, std::string("bcd"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx")}, std::string("xZx"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("vecxor"), std::string("array"), std::string("4vector"), std::string("ohn dCe"), std::string("bcd")}, std::string("J8zisg4882pt"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("W15tic N1Rp"), std::string("byheHqPpa1"), std::string("em3o"), std::string("john doe"), std::string("ftDFppRvUTHf"), std::string("john")}, std::string(""))), (std::vector<std::string >{std::string("W15tic N1Rp"), std::string("byheHqPpa1"), std::string("em3o"), std::string("john doe"), std::string("ftDFppRvUTHf"), std::string("john")}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("cde")}, std::string("V81uUhOVH"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("array"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("scd"), std::string("xxxAAA"), std::string("xxx")}, std::string("xxxAAA"))), (std::vector<std::string >{std::string("xxxAAA")}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc"), std::string("cde"), std::string("bcd"), std::string("vector")}, std::string("h8x"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{}, std::string("UL21O5"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("j9oRhn doe"), std::string("xxxAUAV")}, std::string("7Mjg0tmxGO5C"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("J"), std::string("9Is6SzwjP4z2"), std::string("4 4Z0RD")}, std::string("UVXiBpnjiy"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_prefix(std::vector<std::string >{std::string("abc")}, std::string("bL"))), (std::vector<std::string >{}));
}

TEST(Characterization, get_positive_01) {
    ExpectNearVec(get_positive(std::vector<float >{9.99999975e-05f}), std::vector<float >{9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{5.0f, -3.99000001f, 9.99999975e-05f}), std::vector<float >{5.0f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{3.0f}), std::vector<float >{3.0f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-1.89989996f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.99999975e-05f, 2.0000999f, 9.99999975e-05f, 9.99999975e-05f, -18.2999992f, 5.0f, -1.09990001f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 2.0000999f, 9.99999975e-05f, 9.99999975e-05f, 5.0f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.60000038f}), std::vector<float >{9.60000038f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-13.1999998f, 6.71000004f, 1.79999995f, 9.99999975e-05f, -8.14999962f, 9.99999975e-05f, -2.5f, 0.400099993f}), std::vector<float >{6.71000004f, 1.79999995f, 9.99999975e-05f, 9.99999975e-05f, 0.400099993f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{9.99999975e-05f, 16.8999996f}), std::vector<float >{9.99999975e-05f, 16.8999996f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-9.39999962f}), std::vector<float >{}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{-0.0998999998f, 14.3999996f}), std::vector<float >{14.3999996f}, 1e-5);
    ExpectNearVec(get_positive(std::vector<float >{10.3999996f, 9.99999975e-05f, 9.99999975e-05f}), std::vector<float >{10.3999996f, 9.99999975e-05f, 9.99999975e-05f}, 1e-5);
}

TEST(Characterization, is_prime_01) {
    EXPECT_EQ((is_prime(8LL)), (false));
    EXPECT_EQ((is_prime(-8LL)), (false));
    EXPECT_EQ((is_prime(15LL)), (false));
    EXPECT_EQ((is_prime(574LL)), (false));
    EXPECT_EQ((is_prime(17LL)), (true));
    EXPECT_EQ((is_prime(16LL)), (false));
    EXPECT_EQ((is_prime(-2LL)), (false));
    EXPECT_EQ((is_prime(-955LL)), (false));
    EXPECT_EQ((is_prime(-609LL)), (false));
    EXPECT_EQ((is_prime(19LL)), (true));
    EXPECT_EQ((is_prime(12LL)), (false));
    EXPECT_EQ((is_prime(61LL)), (true));
}

TEST(Characterization, poly_01) {
    ExpectNearScalar(poly(std::vector<double >{-18.699999999999999, -5.7000000000000002, -1.1990000000000001, 1.0, -0.5}, -4.0), -207.084, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.19999999999999996}, -7.79), 0.19999999999999996, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{6.7999999999999998}, -2.0), 6.7999999999999998, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 2.0), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{-0.59989999999999999}, 0.001), -0.59989999999999999, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 0.0), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.001, 4.2199999999999998, -0.5, 0.001, 100.0, -1.9990000000000001, 7.2000000000000002, 19.0}, -10.0), -181600193.199, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{0.001}, -1.0), 0.001, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 9.3399999999999999), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{16.300000000000001}, 20.0), 16.300000000000001, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 1.2000999999999999), 0.0, 1e-9);
    ExpectNearScalar(poly(std::vector<double >{}, 0.001), 0.0, 1e-9);
}

TEST(Characterization, find_zero_01) {
    ExpectNearScalar(find_zero(std::vector<double >{19.899999999999999, 10.0, -1.0, 0.0001, 3.5, 4.0, -6.8799999999999999, 0.001}), -1.0243467777324609, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.8009999999999999, 0.001, 0.001, -2.1000000000000001}), 0.95041598375298086, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{}), 0.0, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-14.0, -1.0, 0.5, -6.1799999999999997}), -1.2467386875937396, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{1.0, 1.2}), -0.83333333333333337, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.0001, -7.4500000000000002, -17.0, -15.4, -6.0, -11.699999999999999, 1.0}), 1.3422818791946309e-05, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.5, 0.001}), -500.0, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{17.399999999999999, 8.0899999999999999, 1.0, 17.899999999999999, 6.0, -1.0990000000000002, -10.0}), -0.85186378438077193, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{10.0, -18.800000000000001, 1.0, 0.0001, 8.5199999999999996}), 0.61866529254535874, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{0.5, 4.0, -7.4000000000000004, -0.39900000000000002, 10.1}), -0.10501902996523724, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-4.7400000000000002, 3.0, -0.69999999999999996, 0.001}), 695.69757491966413, 1e-9);
    ExpectNearScalar(find_zero(std::vector<double >{-12.5, 0.30099999999999999, -9.3499999999999996, 0.59999999999999998, 0.0001, 0.001, -0.5, -9.3000000000000007}), -1.1698923382437358, 1e-9);
}
