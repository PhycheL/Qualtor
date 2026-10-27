// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_01.h"

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

TEST(Probe, has_close_elements_01) {
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}, 4.5999999f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{2.79999995f, 1.0f, 3.9000001f, 2.5f}, -11.1000004f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{2.20000005f, 2.0f}, 1.10000002f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 4.0f, 3.0f, 2.79999995f, 5.0f, 2.0f}, 0.0500000007f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.10000002f, 2.20000005f, 3.0999999f, 4.0999999f, 5.0999999f}, 2.70000005f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 3.0f, 2.79999995f, 4.0f, 5.0f, 2.0f}, 2.79999995f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f}, 7.53000021f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{0.300000012f, 2.0f, 3.0f, 4.0f, 5.0f}, 4.9000001f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f}, 2.5f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 5.0f, 5.9000001f, 4.0f, 2.0f}, 6.5f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{5.0999999f, 2.20000005f, 3.0999999f, 4.0999999f, 1.10000002f}, 3.9000001f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}, 1.5f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{8.56999969f, 4.5999999f, 5.9000001f}, 2.0f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{2.0f, 3.0f, 4.0f, 5.0f}, 2.4000001f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{2.0f, -1.0f}, 1.0f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f, 2.0f}, -3.5f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.10000002f, 2.20000005f, 0.75f, 4.0999999f, 5.0999999f}, 6.44000006f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{5.0f, 2.0f, 5.9000001f, 4.0f, 1.0f}, -9.89999962f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{7.19000006f, 2.5f, -14.6000004f, 4.30000019f, 9.69999981f, -5.4000001f, 4.0999999f, 17.2000008f}, 5.0f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.79999995f, 3.0f, 4.0f, 5.0f, 2.0f}, 1.0f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.10000002f, 2.20000005f, 3.0999999f, 4.0999999f, 5.0999999f}, -11.1000004f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}, 4.0999999f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, -16.0f, 2.20000005f}, -4.0f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f}, 2.79999995f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 1.0f, 3.9000001f, 2.0f, 10.6000004f, 5.30000019f, -6.69999981f, 5.4000001f}, 3.0f)), (true));
}

TEST(Probe, has_close_elements_02) {
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f}, 5.5999999f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{-16.6000004f, 6.34000015f, 1.0f, 5.0999999f, -8.39999962f}, 5.0999999f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.79999995f, 3.0f, 4.0f, 5.0f, 2.0f, 4.0f}, 2.20000005f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 5.0f, 2.20000005f}, 8.94999981f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{2.79999995f, 5.0f, 2.5999999f, 0.300000012f, 9.89999962f, 0.400000006f, 1.0f}, 2.79999995f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{-14.1999998f}, 3.04999995f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f}, -12.8000002f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{2.0f, -7.5999999f, -4.4000001f, 1.0f, 7.5f}, 2.20000005f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 5.0f, 4.0f}, 3.0f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}, 4.21000004f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{}, 1.10000002f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.79999995f, 3.0f, 2.0f, 5.0f, 2.0f}, 1.0f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f}, 15.8999996f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{}, 0.0500000007f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.35000002f, 0.5f, 1.75f, -4.80000019f, 7.48000002f, -15.1000004f, -7.19999981f, 5.0999999f}, -18.0f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.10000002f, 2.20000005f, 3.0999999f, 4.0999999f, 5.0999999f, 1.0f}, 5.0999999f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{-0.200000003f}, 2.0f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 5.0f}, 16.3999996f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f}, 1.0f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{5.0999999f, 2.0f, 1.10000002f, 1.5f, 5.30000019f}, 2.9000001f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}, -13.0f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 5.9000001f, 4.0f, 0.5f}, 3.0f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 5.9000001f, 4.0f, 5.0f}, 9.68999958f)), (true));
}

TEST(Probe, separate_paren_groups_01) {
    EXPECT_EQ((separate_paren_groups(std::string("( ) (( )) (( )( ))"))), (std::vector<std::string >{std::string("()"), std::string("(())"), std::string("(()())")}));
    EXPECT_EQ((separate_paren_groups(std::string("( ) (( )C (( ())"))), (std::vector<std::string >{std::string("()")}));
    EXPECT_EQ((separate_paren_groups(std::string("() (()) ((())) (((())))"))), (std::vector<std::string >{std::string("()"), std::string("(())"), std::string("((()))"), std::string("(((())))")}));
    EXPECT_EQ((separate_paren_groups(std::string("X)"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("gHHTkt"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("( ) (( ))(( )( ))"))), (std::vector<std::string >{std::string("()"), std::string("(())"), std::string("(()())")}));
    EXPECT_EQ((separate_paren_groups(std::string("Em)dU6u"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("(i))()())"))), (std::vector<std::string >{std::string("()")}));
    EXPECT_EQ((separate_paren_groups(std::string("3"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("5(Ld"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("4HblA"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("(()(())((())))"))), (std::vector<std::string >{std::string("(()(())((())))")}));
    EXPECT_EQ((separate_paren_groups(std::string("pz0z"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("T A"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("(()()) ((())) () ((())()())"))), (std::vector<std::string >{std::string("(()())"), std::string("((()))"), std::string("()"), std::string("((())()())")}));
    EXPECT_EQ((separate_paren_groups(std::string("(()()) ((())) () (w())()())"))), (std::vector<std::string >{std::string("(()())"), std::string("((()))"), std::string("()"), std::string("(())"), std::string("()"), std::string("()")}));
    EXPECT_EQ((separate_paren_groups(std::string("((G()))"))), (std::vector<std::string >{std::string("((()))")}));
    EXPECT_EQ((separate_paren_groups(std::string("((())()())"))), (std::vector<std::string >{std::string("((())()())")}));
    EXPECT_EQ((separate_paren_groups(std::string("wIiiSjh9()f"))), (std::vector<std::string >{std::string("()")}));
    EXPECT_EQ((separate_paren_groups(std::string("(())"))), (std::vector<std::string >{std::string("(())")}));
    EXPECT_EQ((separate_paren_groups(std::string("iNWwRhnj"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("( ) ( )) (( )( ))"))), (std::vector<std::string >{std::string("()"), std::string("()"), std::string(")(()"), std::string("()")}));
    EXPECT_EQ((separate_paren_groups(std::string("(()())"))), (std::vector<std::string >{std::string("(()())")}));
    EXPECT_EQ((separate_paren_groups(std::string("(ipb"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("( ) (()) (( )( ))"))), (std::vector<std::string >{std::string("()"), std::string("(())"), std::string("(()())")}));
}

TEST(Probe, separate_paren_groups_02) {
    EXPECT_EQ((separate_paren_groups(std::string("("))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("a((()()0))"))), (std::vector<std::string >{std::string("((()()))")}));
    EXPECT_EQ((separate_paren_groups(std::string("qQv)qbq(8)"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("((()z))"))), (std::vector<std::string >{std::string("((()))")}));
    EXPECT_EQ((separate_paren_groups(std::string("(k)((w))((())))"))), (std::vector<std::string >{std::string("()"), std::string("(())"), std::string("((()))")}));
    EXPECT_EQ((separate_paren_groups(std::string("AcZ"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("nwSNJcyKb"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("W)()"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("X"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("(((m))y(())))"))), (std::vector<std::string >{std::string("((())(()))")}));
    EXPECT_EQ((separate_paren_groups(std::string("(f()))"))), (std::vector<std::string >{std::string("(())")}));
    EXPECT_EQ((separate_paren_groups(std::string("o((K)"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("f7Qj"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("qD9pW2ittw9"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("OAJL"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("4djTXhF"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("((())))"))), (std::vector<std::string >{std::string("((()))")}));
    EXPECT_EQ((separate_paren_groups(std::string("(E())()()E"))), (std::vector<std::string >{std::string("(())"), std::string("()"), std::string("()")}));
    EXPECT_EQ((separate_paren_groups(std::string("quabk6VQMy"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("k"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("(()"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("(Q())"))), (std::vector<std::string >{std::string("(())")}));
    EXPECT_EQ((separate_paren_groups(std::string("fWnDCsHH"))), (std::vector<std::string >{}));
}

TEST(Probe, truncate_number_01) {
    ExpectNearScalar(truncate_number(11.6999998f), 0.699999809f, 1e-5);
    ExpectNearScalar(truncate_number(0.200100005f), 0.200100005f, 1e-5);
    ExpectNearScalar(truncate_number(1.28999996f), 0.289999962f, 1e-5);
    ExpectNearScalar(truncate_number(-7.30000019f), -0.300000191f, 1e-5);
    ExpectNearScalar(truncate_number(7.30000019f), 0.300000191f, 1e-5);
    ExpectNearScalar(truncate_number(2.29999995f), 0.299999952f, 1e-5);
    ExpectNearScalar(truncate_number(1.75f), 0.75f, 1e-5);
    ExpectNearScalar(truncate_number(3.79999995f), 0.799999952f, 1e-5);
    ExpectNearScalar(truncate_number(5.80000019f), 0.800000191f, 1e-5);
    ExpectNearScalar(truncate_number(123.456001f), 0.456001282f, 1e-5);
    ExpectNearScalar(truncate_number(-10.0f), 0.0f, 1e-5);
    ExpectNearScalar(truncate_number(0.219999999f), 0.219999999f, 1e-5);
    ExpectNearScalar(truncate_number(-5.9000001f), -0.900000095f, 1e-5);
    ExpectNearScalar(truncate_number(-8.72000027f), -0.720000267f, 1e-5);
    ExpectNearScalar(truncate_number(-5.51000023f), -0.510000229f, 1e-5);
    ExpectNearScalar(truncate_number(-2.5f), -0.5f, 1e-5);
    ExpectNearScalar(truncate_number(-7.19999981f), -0.199999809f, 1e-5);
    ExpectNearScalar(truncate_number(5.69999981f), 0.699999809f, 1e-5);
    ExpectNearScalar(truncate_number(121.755997f), 0.755996704f, 1e-5);
    ExpectNearScalar(truncate_number(-7.0999999f), -0.0999999046f, 1e-5);
    ExpectNearScalar(truncate_number(7.19999981f), 0.199999809f, 1e-5);
    ExpectNearScalar(truncate_number(-16.5f), -0.5f, 1e-5);
    ExpectNearScalar(truncate_number(-1.16999996f), -0.169999957f, 1e-5);
    ExpectNearScalar(truncate_number(2.42000008f), 0.420000076f, 1e-5);
    ExpectNearScalar(truncate_number(-0.399899989f), -0.399899989f, 1e-5);
}

TEST(Probe, truncate_number_02) {
    ExpectNearScalar(truncate_number(0.5f), 0.5f, 1e-5);
    ExpectNearScalar(truncate_number(-2.29999995f), -0.299999952f, 1e-5);
    ExpectNearScalar(truncate_number(2.9000001f), 0.900000095f, 1e-5);
    ExpectNearScalar(truncate_number(3.66000009f), 0.660000086f, 1e-5);
    ExpectNearScalar(truncate_number(-3.55999994f), -0.559999943f, 1e-5);
    ExpectNearScalar(truncate_number(1.10010004f), 0.10010004f, 1e-5);
    ExpectNearScalar(truncate_number(4.0999999f), 0.0999999046f, 1e-5);
    ExpectNearScalar(truncate_number(1.33000004f), 0.330000043f, 1e-5);
    ExpectNearScalar(truncate_number(-11.1999998f), -0.199999809f, 1e-5);
    ExpectNearScalar(truncate_number(0.200000003f), 0.200000003f, 1e-5);
    ExpectNearScalar(truncate_number(19.8999996f), 0.899999619f, 1e-5);
    ExpectNearScalar(truncate_number(10.1999998f), 0.199999809f, 1e-5);
    ExpectNearScalar(truncate_number(-4.98000002f), -0.980000019f, 1e-5);
    ExpectNearScalar(truncate_number(-14.3999996f), -0.399999619f, 1e-5);
    ExpectNearScalar(truncate_number(1.39999998f), 0.399999976f, 1e-5);
    ExpectNearScalar(truncate_number(10.8999996f), 0.899999619f, 1e-5);
    ExpectNearScalar(truncate_number(-12.5f), -0.5f, 1e-5);
    ExpectNearScalar(truncate_number(-3.82999992f), -0.829999924f, 1e-5);
    ExpectNearScalar(truncate_number(18.7999992f), 0.799999237f, 1e-5);
    ExpectNearScalar(truncate_number(0.456f), 0.456f, 1e-5);
    ExpectNearScalar(truncate_number(-12.1999998f), -0.199999809f, 1e-5);
    ExpectNearScalar(truncate_number(5.30000019f), 0.300000191f, 1e-5);
    ExpectNearScalar(truncate_number(-1.99989998f), -0.999899983f, 1e-5);
}

TEST(Probe, below_zero_01) {
    EXPECT_EQ((below_zero(std::vector<int >{-370, 760, 1, 173})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{7, -4, 1, -591, 12})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, 5, -4})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{2, 4})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, -2, 5, -5, 4, -4})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, 6, 5, -4})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{-919, 3})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{13, 6, -9, -3, 146, 14, 1, 100})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, -1, 2, -2, 5, -5, 4, -4})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{-1})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, -1, 6, -2, 5, -5, 4, -5})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{-3, -1, 2, 346, 370, -9})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{4, 1, 235})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, 3, -5})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, -1, 2, -2, 5, -5, 4, -5, 22})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{-670, -2, 6, -5})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, 10, 3})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, -4, 5, 6, -1})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, -1, 2, -2, 5, -5, 4, -4, 751})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{-3, -179, -6, 802})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, -4, 5, 6})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{23, -77, -4, 5, 3, 456, 25, -4})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{-3})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, -2, 2, -2, 5, -5, 4, -4, -1})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{6, 1, 99999, -1, -1, -5, 1000, -3})), (false));
}

TEST(Probe, below_zero_02) {
    EXPECT_EQ((below_zero(std::vector<int >{3})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{6, -5, -4, -3, -1})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{6, 895, 6, -8, -5, 1})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{-1, -4, 96, 99999, 812, -857})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{2, 4, 190})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{-9, -5, 2})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{-1, 443, 4, -9, -1, -4})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{3, -846})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, -4, -427, 6})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, -6})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, -1, 2, -2, 5, -5, 4, -4, 3})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{-1, 14, 4, -4, -2, 7})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{-3, 2, -3, 1, 2, 1})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, -2, 2, -2, 5, -5, 4, -4, 455})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{-835, 24, 5, -628, 1, 8})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, 3})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{0, -2, -653})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, -5, 5, 6})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{3, 19, 1, 2})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{632, 1})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{-63, 19, 667, -1})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, -2, 2, -2, 5, 4, -4})), (true));
}

TEST(Probe, mean_absolute_deviation_01) {
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f}), 1.20000005f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{4.0f, 2.0f, 3.0f, 1.0f}), 1.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{3.0f, 2.0f, 1.0f}), 0.666666687f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-3.29999995f, -5.0f, 6.0f}), 4.51111078f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 0.409999996f}), 0.897500038f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, -14.1000004f}), 5.31200027f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{6.0f, 3.0f, 3.20000005f, 2.0f}), 1.2249999f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 8.69999981f, 3.0f, 4.0f}), 2.26250005f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, -6.5999999f}), 2.79999995f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{9.80000019f, 2.0f, 3.0f, 4.0f}), 2.54999995f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-8.30000019f, -1.79990005f, 1.0f, 2.79999995f, -4.5999999f, -12.6000004f, 6.0f}), 5.142869f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{13.5f, 0.300000012f, -13.5f, 12.8000002f, 1.67999995f, 17.2999992f}), 9.18666744f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-7.9000001f, -1.89999998f, 5.0f}), 4.4000001f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{7.30000019f, -6.0999999f, -0.349999994f}), 4.67777777f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-16.8999996f, -14.8999996f, -15.3000002f, 19.7000008f, 14.6999998f, 4.5999999f, 8.69999981f}), 13.530612f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-15.3999996f, 5.59000015f, -0.300000012f, -1.0f, 1.89999998f, 1.5f, 1.90009999f}), 4.21143627f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{2.0f, 3.0f}), 0.5f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 6.0f, 5.0f}), 1.67999995f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 5.0f, 4.0f, 3.0f}), 1.20000005f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{5.0f}), 0.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 3.5f}), 0.960000038f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-2.0999999f, -1.70000005f, 7.5999999f, -6.5f, 4.0f, 3.5f, 17.7000008f}), 5.69795942f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 3.0f, 2.0f, 4.0f}), 1.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 4.0f, 3.0f, 5.0f}), 1.20000005f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 4.0f, 5.0f}), 1.5f, 1e-5);
}

TEST(Probe, mean_absolute_deviation_02) {
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{4.0f, 3.5999999f}), 0.200000048f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, -13.0f, 4.19999981f, 6.69999981f, -1.39999998f, 18.3999996f, 2.0f}), 6.17959166f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f}), 0.5f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{2.0f, 3.0f, 4.0f, 5.0f}), 1.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{9.39999962f, 3.0f, -6.9000001f}), 5.82222223f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-5.19999981f, -13.3999996f, 1.29999995f, -15.0f, 4.0f, -4.5999999f, 2.9000001f, 7.69000006f}), 6.7612505f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{9.99999975e-05f, 6.0f, 5.0f, 1.70009995f, -17.8999996f, 2.71000004f}), 5.82834435f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-0.200000003f}), 0.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-0.199900001f, -6.69999981f, 1.64999998f, 8.10000038f, -10.0f, 5.30000019f, 6.0f}), 5.33671856f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 5.0f}), 1.25f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 2.0f}), 0.879999995f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{14.1000004f}), 0.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-5.0999999f, 3.0f, 3.0f, -0.100000001f, 7.4000001f}), 3.39199972f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-17.7999992f, 2.0f, -4.30000019f}), 7.39999962f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{6.44000006f, 0.5f, 9.99999975e-05f, 5.69999981f, -2.20000005f, -0.300000012f, 9.60000038f, 12.6000004f}), 4.54248762f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{6.0f, 6.0f}), 0.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, -3.4000001f, 5.0f}), 2.17600012f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, -16.6000004f}), 6.11200047f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{3.0f, 1.89999998f}), 0.550000012f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 4.69999981f}), 1.15199995f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, -6.51999998f, 9.99999975e-05f}), 3.12002206f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-18.3999996f, -1.60000002f, -17.7999992f, 12.6999998f, 1.70000005f}), 10.7359982f, 1e-5);
}

TEST(Probe, intersperse_01) {
    EXPECT_EQ((intersperse(std::vector<int >{5, 3, 6, 8, 3, 8, 2}, 27)), (std::vector<int >{5, 27, 3, 27, 6, 27, 8, 27, 3, 27, 8, 27, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{4, 8, 3, -1}, 7)), (std::vector<int >{4, 7, 8, 7, 3, 7, -1}));
    EXPECT_EQ((intersperse(std::vector<int >{7}, 2)), (std::vector<int >{7}));
    EXPECT_EQ((intersperse(std::vector<int >{-2, 4, -626, -5, 254}, 5)), (std::vector<int >{-2, 5, 4, 5, -626, 5, -5, 5, 254}));
    EXPECT_EQ((intersperse(std::vector<int >{-356, 15, -2}, -1)), (std::vector<int >{-356, -1, 15, -1, -2}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 6, 8, 8, 3, 8, 2}, 7)), (std::vector<int >{5, 7, 6, 7, 8, 7, 8, 7, 3, 7, 8, 7, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 4, 2, 4, 3, 7}, 22)), (std::vector<int >{1, 22, 4, 22, 2, 22, 4, 22, 3, 22, 7}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 4, 2, 4, 3}, -3)), (std::vector<int >{1, -3, 4, -3, 2, -3, 4, -3, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{15, 669, -5, 1, 2, 3}, 1)), (std::vector<int >{15, 1, 669, 1, -5, 1, 1, 1, 2, 1, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{3, 6, 5, 2}, 1000)), (std::vector<int >{3, 1000, 6, 1000, 5, 1000, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{}, 10)), (std::vector<int >{}));
    EXPECT_EQ((intersperse(std::vector<int >{2, 2, 3}, -988)), (std::vector<int >{2, -988, 2, -988, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{99999, 2, 2}, 5)), (std::vector<int >{99999, 5, 2, 5, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 6, 3, 2}, 1)), (std::vector<int >{5, 1, 6, 1, 3, 1, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{2, 2, 2}, 14)), (std::vector<int >{2, 14, 2, 14, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 8, 6, 8, 3, 8, 2}, 0)), (std::vector<int >{5, 0, 8, 0, 6, 0, 8, 0, 3, 0, 8, 0, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 8, 6, 7, 3, 8, 2}, 1)), (std::vector<int >{5, 1, 8, 1, 6, 1, 7, 1, 3, 1, 8, 1, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 2, 4, 3}, -646)), (std::vector<int >{1, -646, 2, -646, 4, -646, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 8, 6, 8, 3, 8, 2}, 14)), (std::vector<int >{5, 14, 8, 14, 6, 14, 8, 14, 3, 14, 8, 14, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{2, 2, 2}, 30)), (std::vector<int >{2, 30, 2, 30, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{7, 381, -3, 6, 1, 7, 6}, 2)), (std::vector<int >{7, 2, 381, 2, -3, 2, 6, 2, 1, 2, 7, 2, 6}));
    EXPECT_EQ((intersperse(std::vector<int >{6, 8, 1, 5, 23, 25, -3, 3}, 3)), (std::vector<int >{6, 3, 8, 3, 1, 3, 5, 3, 23, 3, 25, 3, -3, 3, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{}, 6)), (std::vector<int >{}));
    EXPECT_EQ((intersperse(std::vector<int >{0, 21, 5, 920, 14}, -777)), (std::vector<int >{0, -777, 21, -777, 5, -777, 920, -777, 14}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 8, 6, 8, 3, 8, 2}, 27)), (std::vector<int >{5, 27, 8, 27, 6, 27, 8, 27, 3, 27, 8, 27, 2}));
}

TEST(Probe, intersperse_02) {
    EXPECT_EQ((intersperse(std::vector<int >{5, 6, 3, 0}, 5)), (std::vector<int >{5, 5, 6, 5, 3, 5, 0}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 2, 3}, 2)), (std::vector<int >{1, 2, 2, 2, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{12, -881, 26, 892}, 6)), (std::vector<int >{12, 6, -881, 6, 26, 6, 892}));
    EXPECT_EQ((intersperse(std::vector<int >{2, 2, 2, 2}, 9)), (std::vector<int >{2, 9, 2, 9, 2, 9, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 8, 6, 8, 3, 2}, 12345)), (std::vector<int >{5, 12345, 8, 12345, 6, 12345, 8, 12345, 3, 12345, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{2, 2, 2, 2, 2, 2}, -8)), (std::vector<int >{2, -8, 2, -8, 2, -8, 2, -8, 2, -8, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{6, 3, 7, 27, -8}, 21)), (std::vector<int >{6, 21, 3, 21, 7, 21, 27, 21, -8}));
    EXPECT_EQ((intersperse(std::vector<int >{7}, 343)), (std::vector<int >{7}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 2, 3}, 5)), (std::vector<int >{1, 5, 2, 5, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{-3, 20, 3, 1, 4, 290, -2}, 5)), (std::vector<int >{-3, 5, 20, 5, 3, 5, 1, 5, 4, 5, 290, 5, -2}));
    EXPECT_EQ((intersperse(std::vector<int >{6, 8, 6, 8, 3, 8, 2}, 7)), (std::vector<int >{6, 7, 8, 7, 6, 7, 8, 7, 3, 7, 8, 7, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 4, 2, 4, 3}, -853)), (std::vector<int >{1, -853, 4, -853, 2, -853, 4, -853, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 4, 2, 10, 3}, 25)), (std::vector<int >{1, 25, 4, 25, 2, 25, 10, 25, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 1, 4}, 4)), (std::vector<int >{5, 4, 1, 4, 4}));
    EXPECT_EQ((intersperse(std::vector<int >{11, 6, 1, 5}, 1)), (std::vector<int >{11, 1, 6, 1, 1, 1, 5}));
    EXPECT_EQ((intersperse(std::vector<int >{6, 6}, 1)), (std::vector<int >{6, 1, 6}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 2, 3}, 11)), (std::vector<int >{1, 11, 2, 11, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 6, 3, 2}, 7)), (std::vector<int >{5, 7, 6, 7, 3, 7, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{4, 6, 6, -4, -165}, 6)), (std::vector<int >{4, 6, 6, 6, 6, 6, -4, 6, -165}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 8, 6, 8, 3, 8, 2}, 4)), (std::vector<int >{5, 4, 8, 4, 6, 4, 8, 4, 3, 4, 8, 4, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 8, 6, 8, 3, 8, 2}, 6)), (std::vector<int >{5, 6, 8, 6, 6, 6, 8, 6, 3, 6, 8, 6, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{2, 2, 2}, -1)), (std::vector<int >{2, -1, 2, -1, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 2, 3}, 8)), (std::vector<int >{1, 8, 2, 8, 3}));
}

TEST(Probe, parse_nested_parens_01) {
    EXPECT_EQ((parse_nested_parens(std::string("(()())((())))"))), (std::vector<int >{2, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("(()()) ((())) () ((())()())"))), (std::vector<int >{2, 3, 1, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("(()(())((()o0))"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("(()()) ((())) () ((())()))"))), (std::vector<int >{2, 3, 1, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("mz3"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("(()()) (((U))) () ((()C()()"))), (std::vector<int >{2, 3, 1}));
    EXPECT_EQ((parse_nested_parens(std::string("()((W)(())))"))), (std::vector<int >{1, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("() (v())F (())) (((())))"))), (std::vector<int >{1, 2, 2, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("() ((m) ((3))) ((q())))"))), (std::vector<int >{1, 3, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("4jAFoiWF5Aw"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("(()())((())m)"))), (std::vector<int >{2, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("(()()) (()))()(((())()())"))), (std::vector<int >{2, 2, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("(()((A)((())))"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("L3x5"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("L"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("g"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("0kdZ"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("oYCVJo0yU2"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("(()2h)) ((())E () ((())()())"))), (std::vector<int >{2, 2, 1, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("7PuF0Sj6Zx"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("() (()) ((()) (r(())))"))), (std::vector<int >{1, 2, 4}));
    EXPECT_EQ((parse_nested_parens(std::string("WIJDK"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("() (()) ((())) (((())2)"))), (std::vector<int >{1, 2, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("iUB"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("(()(())(((e))))"))), (std::vector<int >{4}));
}

TEST(Probe, parse_nested_parens_02) {
    EXPECT_EQ((parse_nested_parens(std::string("Zq7lp"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("() i()) ((())) (((())))"))), (std::vector<int >{1, 1, 2, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("(()()) ((()))X (N ((Q())()())"))), (std::vector<int >{2, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("(()()) ((())) () (())()())"))), (std::vector<int >{2, 3, 1, 2, 1, 1}));
    EXPECT_EQ((parse_nested_parens(std::string("WF17JPN"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("E5OzUy9q"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("HuosFg"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("q(()j((U))((())))"))), (std::vector<int >{4}));
    EXPECT_EQ((parse_nested_parens(std::string("c()(()P((()))"))), (std::vector<int >{1}));
    EXPECT_EQ((parse_nested_parens(std::string("(()) ((())) () ((())()())"))), (std::vector<int >{2, 3, 1, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("()(())((())))"))), (std::vector<int >{1, 2, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("fqwYqhy)0u"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("()QY(()l ((())) (((())))"))), (std::vector<int >{1}));
    EXPECT_EQ((parse_nested_parens(std::string("kwQ(g s"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("qFabr0YfWLn"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("B"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("gjRPI0"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("(()()) ((i(K))) () ((())()())"))), (std::vector<int >{2, 3, 1, 3}));
    EXPECT_EQ((parse_nested_parens(std::string("DSLFaSaT"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("()())((()))"))), (std::vector<int >{1, 1, 2}));
    EXPECT_EQ((parse_nested_parens(std::string("ho4bb5IqC(rM"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("x12OSDhWkdd "))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("(()()) ((())) ) ((()J()())"))), (std::vector<int >{2, 3, 2}));
}

TEST(Probe, filter_by_substring_01) {
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("aaaxxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("Px "))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd"), std::string("cde"), std::string("vector")}, std::string("rluIe"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd"), std::string("grunt"), std::string("vector")}, std::string("b2ac1"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{}, std::string("run"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{}, std::string("a"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd"), std::string("array"), std::string("cde")}, std::string("puv"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("qgrunt"), std::string("grueMme"), std::string("aO")}, std::string("gkrunt"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx")}, std::string("nxy"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("p"), std::string("a"), std::string("aZsd"), std::string("de"), std::string("cde"), std::string("ZHCm0"), std::string("OzFBwFg7e5A"), std::string("qvx")}, std::string("john do"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("john doe"), std::string("bacd"), std::string("vector")}, std::string("a"))), (std::vector<std::string >{std::string("bacd")}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("vector"), std::string("bacd")}, std::string("trumpet"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("HAnt"), std::string("trumpe"), std::string("run"), std::string("john doe"), std::string("Axp"), std::string("3cKPDZl")}, std::string(""))), (std::vector<std::string >{std::string("HAnt"), std::string("trumpe"), std::string("run"), std::string("john doe"), std::string("Axp"), std::string("3cKPDZl")}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("0array"), std::string("xxxAAA"), std::string("asd"), std::string("cde"), std::string("U"), std::string("aaaxxy")}, std::string("2kFYP3"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("gruesome"), std::string("bacd"), std::string("xx")}, std::string("jop2n"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("a"), std::string("4reome"), std::string("xxxAAA"), std::string("ja"), std::string("ecto1j"), std::string("john doe"), std::string("xxxAAA"), std::string("john doe")}, std::string("gruesome"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("asd"), std::string("run"), std::string("xxxAAd"), std::string("bacd")}, std::string("aaaxKy"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("john")}, std::string("xA"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("OF"), std::string("bfcd"), std::string("run"), std::string("Lrunt")}, std::string("YyZd"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("Ec"), std::string("1G "), std::string("EzBS0sE"), std::string("john"), std::string("VhVTi5"), std::string("xxxAAA"), std::string("xx")}, std::string("Qa6gGZl07kuw"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("grRnt"), std::string("E"), std::string("trumpet"), std::string("mcde"), std::string("BSbgdOO"), std::string("xx")}, std::string("VDhn"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{}, std::string("Mxx"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd"), std::string("cde"), std::string("array")}, std::string("vgrsOrPJH"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("trumpet"), std::string("jon"), std::string("xxxAAA"), std::string("john doe"), std::string("y"), std::string("5nmf8"), std::string("lbacebd"), std::string("xxx")}, std::string("aaaMexy"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("1e0R6GUlEaHB"), std::string("ipKBp3LZbgZ"), std::string("3a"), std::string("zehp0kZOxM"), std::string("OfzDpxD8")}, std::string("abc"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("aaaxxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx"), std::string("aaaxxy")}, std::string("aahxxZ"))), (std::vector<std::string >{}));
}

TEST(Probe, filter_by_substring_02) {
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("Wws"), std::string(" v64"), std::string("EQaK")}, std::string("a"))), (std::vector<std::string >{std::string("EQaK")}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("psfHFGtwfz"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("xxx"))), (std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx")}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("bacd"), std::string("aaaxxy"), std::string("gruesome"), std::string(""), std::string("run"), std::string("array"), std::string("asd"), std::string("array")}, std::string("gruesome"))), (std::vector<std::string >{std::string("gruesome")}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxxAAA"), std::string("a"), std::string("3AAyEKqvgxxU"), std::string("vector"), std::string("aaaxxy"), std::string("vector"), std::string("bacd")}, std::string("3FVId2YUe"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{}, std::string("bacd"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("prune")}, std::string("xxy"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("cde"), std::string("array")}, std::string("runzt"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd"), std::string("array"), std::string("0yCX")}, std::string("xxxAAA"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("aaaxxy"), std::string("xxxAAA"), std::string("xxx"), std::string("asd")}, std::string("trump"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("Dpue"), std::string("us"), std::string("OQMd1Qi"), std::string("oDCsbspzM40"), std::string("gbBNXJ"), std::string("grusome")}, std::string("34e"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("s"), std::string("xxAAA"), std::string("aBbc")}, std::string("abc"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("grunt"), std::string("uun")}, std::string("john doe"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("VWsJM"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("ne"), std::string("p7Lrue"), std::string("nv"), std::string("trumpet")}, std::string("ab1"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx")}, std::string("xx"))), (std::vector<std::string >{std::string("xxx"), std::string("xxxAAA"), std::string("xxx")}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("aa4xUy")}, std::string("c"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("s"))), (std::vector<std::string >{std::string("asd")}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("cde"), std::string("xxx"), std::string("aGdVMllU2")}, std::string("vMctor"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("grunt"), std::string("prune")}, std::string("CFIPGJcuO"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("cde"), std::string("bacd"), std::string("cde"), std::string("vector")}, std::string("a"))), (std::vector<std::string >{std::string("bacd")}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("asd"), std::string("Nad"), std::string("xx"), std::string("abc"), std::string("MWMeBrboO"), std::string("john"), std::string("asd")}, std::string("Q8"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("xxy"), std::string("john doe"), std::string("xxxAAA"), std::string("xxx")}, std::string("3X"))), (std::vector<std::string >{}));
}
