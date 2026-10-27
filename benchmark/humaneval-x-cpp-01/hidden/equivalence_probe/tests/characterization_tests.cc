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

TEST(Characterization, has_close_elements_01) {
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}, -12.1000004f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.9000001f, 4.0f, 5.0f, 2.20000005f}, 2.20000005f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.10000002f, 2.20000005f, 3.0999999f, 4.0999999f, 5.0999999f}, -5.5999999f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 3.0f, 2.0f}, 0.0500000007f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{5.96999979f, -6.01999998f, 4.69999981f, -0.170000002f, -10.8000002f, 15.3999996f, 1.0f, 4.5999999f}, 3.9000001f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, -0.800000012f, 3.0f}, 5.9000001f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 4.0f, 5.0f}, 3.9000001f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.10000002f, 2.20000005f, 3.0999999f, 4.0999999f, 5.0999999f, 0.800000012f}, 0.800000012f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.79999995f, 3.0f, 4.0f, 5.0f}, 0.5f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 3.0f, -1.15999997f}, 0.300000012f)), (false));
    EXPECT_EQ((has_close_elements(std::vector<float >{1.0f, 2.0f, 4.0f, 3.9000001f, 5.0f, 2.20000005f}, 1.0f)), (true));
    EXPECT_EQ((has_close_elements(std::vector<float >{0.899999976f, 7.19999981f, 2.0f, -18.6000004f, 2.57999992f}, 2.0f)), (true));
}

TEST(Characterization, separate_paren_groups_01) {
    EXPECT_EQ((separate_paren_groups(std::string("(l)))"))), (std::vector<std::string >{std::string("()")}));
    EXPECT_EQ((separate_paren_groups(std::string("D)"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("(()2))"))), (std::vector<std::string >{std::string("(())")}));
    EXPECT_EQ((separate_paren_groups(std::string("((()))"))), (std::vector<std::string >{std::string("((()))")}));
    EXPECT_EQ((separate_paren_groups(std::string("ipUjmw"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("B(()(r)"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string(")l6l1APG)wnS"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("()"))), (std::vector<std::string >{std::string("()")}));
    EXPECT_EQ((separate_paren_groups(std::string("hEKnQ"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string(" zq3p"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("pLS3iM"))), (std::vector<std::string >{}));
    EXPECT_EQ((separate_paren_groups(std::string("((M)"))), (std::vector<std::string >{}));
}

TEST(Characterization, truncate_number_01) {
    ExpectNearScalar(truncate_number(1.0f), 0.0f, 1e-5);
    ExpectNearScalar(truncate_number(9.99999975e-05f), 9.99999975e-05f, 1e-5);
    ExpectNearScalar(truncate_number(5.71000004f), 0.710000038f, 1e-5);
    ExpectNearScalar(truncate_number(-12.3999996f), -0.399999619f, 1e-5);
    ExpectNearScalar(truncate_number(122.155998f), 0.15599823f, 1e-5);
    ExpectNearScalar(truncate_number(-10.3000002f), -0.300000191f, 1e-5);
    ExpectNearScalar(truncate_number(17.3999996f), 0.399999619f, 1e-5);
    ExpectNearScalar(truncate_number(-12.1000004f), -0.100000381f, 1e-5);
    ExpectNearScalar(truncate_number(-1.44400001f), -0.444000006f, 1e-5);
    ExpectNearScalar(truncate_number(0.899999976f), 0.899999976f, 1e-5);
    ExpectNearScalar(truncate_number(3.5f), 0.5f, 1e-5);
    ExpectNearScalar(truncate_number(11.8999996f), 0.899999619f, 1e-5);
}

TEST(Characterization, below_zero_01) {
    EXPECT_EQ((below_zero(std::vector<int >{1, -2, 2, -2, 5, -5, 4, -4})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{15, 2, -3, 1, 2, -3})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{2, 12, 1000})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, -3, 1, 2, -3})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, 3})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, -4, 5, 6, -221})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{26, 2, -4, 5, 6})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, -1, 2, -2, 5, -5, 4, -5})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{})), (false));
    EXPECT_EQ((below_zero(std::vector<int >{1, 28, 4, -921, -4})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, 2, -4, 5})), (true));
    EXPECT_EQ((below_zero(std::vector<int >{1, -1, 2, -2, 5, -5, -4, 4})), (true));
}

TEST(Characterization, mean_absolute_deviation_01) {
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{6.0999999f, 1.0f, 6.0f}), 2.24444437f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 7.4000001f}), 2.0250001f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f}), 0.666666687f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{2.9000001f}), 0.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{19.5f, 6.9000001f}), 6.30000019f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f}), 1.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{9.99999975e-05f}), 0.0f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{-19.2999992f, 11.1000004f, 9.60000038f, -19.2000008f, 12.3000002f}), 14.5199995f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{9.19999981f, 9.60000038f, -15.3000002f}), 10.9777784f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, -1.49989998f}), 1.74998331f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, -2.31999993f}), 1.75680006f, 1e-5);
    ExpectNearScalar(mean_absolute_deviation(std::vector<float >{1.0f, 2.0f, 3.0f, 18.2000008f}), 6.07500029f, 1e-5);
}

TEST(Characterization, intersperse_01) {
    EXPECT_EQ((intersperse(std::vector<int >{2, 2, 6}, 7)), (std::vector<int >{2, 7, 2, 7, 6}));
    EXPECT_EQ((intersperse(std::vector<int >{3, 507, 6, 1}, 26)), (std::vector<int >{3, 26, 507, 26, 6, 26, 1}));
    EXPECT_EQ((intersperse(std::vector<int >{2, 5, 2}, 0)), (std::vector<int >{2, 0, 5, 0, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{}, 7)), (std::vector<int >{}));
    EXPECT_EQ((intersperse(std::vector<int >{5, 8, 6, 8, 3, 8, 2}, 7)), (std::vector<int >{5, 7, 8, 7, 6, 7, 8, 7, 3, 7, 8, 7, 2}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 2, 3, 4}, 4)), (std::vector<int >{1, 4, 2, 4, 3, 4, 4}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 2, 3}, 1)), (std::vector<int >{1, 1, 2, 1, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{2}, 15)), (std::vector<int >{2}));
    EXPECT_EQ((intersperse(std::vector<int >{1, 5, 2, 3, -656, 3}, 7)), (std::vector<int >{1, 7, 5, 7, 2, 7, 3, 7, -656, 7, 3}));
    EXPECT_EQ((intersperse(std::vector<int >{1}, 248)), (std::vector<int >{1}));
    EXPECT_EQ((intersperse(std::vector<int >{30, -1, -606}, 100)), (std::vector<int >{30, 100, -1, 100, -606}));
    EXPECT_EQ((intersperse(std::vector<int >{3}, 58)), (std::vector<int >{3}));
}

TEST(Characterization, parse_nested_parens_01) {
    EXPECT_EQ((parse_nested_parens(std::string("RhrP"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("(()(())((())))"))), (std::vector<int >{4}));
    EXPECT_EQ((parse_nested_parens(std::string("Ry50nqxN"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("1y85r9CqgeR"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("wn"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("V"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string(" 7mzQ3"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("WN1fdu2Y"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("ZGvrTnXYJT("))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("72j1YJDOy"))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string(""))), (std::vector<int >{}));
    EXPECT_EQ((parse_nested_parens(std::string("() (()) ((())) (((())))"))), (std::vector<int >{1, 2, 3, 4}));
}

TEST(Characterization, filter_by_substring_01) {
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("FqmSZzml"), std::string("vector"), std::string("X"), std::string("psd"), std::string("cde")}, std::string("Ic3MCh0j"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("grunt"), std::string("trumpet"), std::string("prune"), std::string("gruesome")}, std::string("john"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxxAAA"), std::string("xxx"), std::string("xxx")}, std::string("asd"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd"), std::string("array")}, std::string("Ny1oAh9bXH"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd"), std::string("cde"), std::string("vector")}, std::string("ab3c"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("grunt"), std::string("prune"), std::string("gruesome")}, std::string("grxnt"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd")}, std::string("xQx5IAj0IKt"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("asd"), std::string("aaaxxy"), std::string("john doe"), std::string("xxxAAA"), std::string("gruesm")}, std::string("vecor"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd"), std::string("vector")}, std::string("6SGvector"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("abc"), std::string("bacd"), std::string("cde"), std::string("vector")}, std::string("Ust9T7n6"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("grunt"), std::string("prune"), std::string("aaaxxy")}, std::string("hxHx"))), (std::vector<std::string >{}));
    EXPECT_EQ((filter_by_substring(std::vector<std::string >{std::string("xxx"), std::string("xxxAAA")}, std::string("tbagcd"))), (std::vector<std::string >{}));
}
