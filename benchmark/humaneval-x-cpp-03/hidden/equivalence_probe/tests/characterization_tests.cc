// 生成文件，勿手工修改：由 benchmark/tools/import_humaneval_x.py 在原代码上运行探针生成器得到（种子 20261027）。
// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。
#include "humaneval_x_cpp_03.h"

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

TEST(Characterization, count_distinct_characters_01) {
    EXPECT_EQ((count_distinct_characters(std::string("abcdecadeCADE"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("tDF"))), (3));
    EXPECT_EQ((count_distinct_characters(std::string("xyzXYZ"))), (3));
    EXPECT_EQ((count_distinct_characters(std::string("Jerry"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("S"))), (1));
    EXPECT_EQ((count_distinct_characters(std::string("C34m"))), (4));
    EXPECT_EQ((count_distinct_characters(std::string("xyXYA"))), (3));
    EXPECT_EQ((count_distinct_characters(std::string(" 4D40szbAm2"))), (10));
    EXPECT_EQ((count_distinct_characters(std::string("aaaaAAAAaaaa"))), (1));
    EXPECT_EQ((count_distinct_characters(std::string("abcdecadTCADE"))), (6));
    EXPECT_EQ((count_distinct_characters(std::string("Jerry jERRY JeRRRY"))), (5));
    EXPECT_EQ((count_distinct_characters(std::string("abmcde"))), (6));
}

TEST(Characterization, parse_music_01) {
    EXPECT_EQ((parse_music(std::string("l"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("o oM .| o| o| .| .| .| | o Do"))), (std::vector<int >{4, 1, 2, 2, 1, 1, 1, 4}));
    EXPECT_EQ((parse_music(std::string("o o o2o"))), (std::vector<int >{4, 4}));
    EXPECT_EQ((parse_music(std::string("o o o o"))), (std::vector<int >{4, 4, 4, 4}));
    EXPECT_EQ((parse_music(std::string("ipUjmw"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("rBo"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string(".l6l1APG.wnS"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string(".|"))), (std::vector<int >{1}));
    EXPECT_EQ((parse_music(std::string("hEKnQ"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string(" zq3p"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("pLS3iM"))), (std::vector<int >{}));
    EXPECT_EQ((parse_music(std::string("M|"))), (std::vector<int >{}));
}

TEST(Characterization, how_many_times_01) {
    EXPECT_EQ((how_many_times(std::string(""), std::string("aa"))), (0));
    EXPECT_EQ((how_many_times(std::string("Q0UPUfYhv"), std::string("acacacs"))), (0));
    EXPECT_EQ((how_many_times(std::string("ZKNpJ7SPbP"), std::string("H ci wExwZ"))), (0));
    EXPECT_EQ((how_many_times(std::string("caFacacac"), std::string("john"))), (0));
    EXPECT_EQ((how_many_times(std::string(""), std::string("gjehTn"))), (0));
    EXPECT_EQ((how_many_times(std::string("caca5cacac"), std::string("gd"))), (0));
    EXPECT_EQ((how_many_times(std::string("cac"), std::string("cac"))), (1));
    EXPECT_EQ((how_many_times(std::string("aaaa"), std::string("aaa"))), (2));
    EXPECT_EQ((how_many_times(std::string("john dwe"), std::string("Za"))), (0));
    EXPECT_EQ((how_many_times(std::string("wuIejLGT4nKq"), std::string("A"))), (0));
    EXPECT_EQ((how_many_times(std::string("bkohn"), std::string("aaa"))), (0));
    EXPECT_EQ((how_many_times(std::string("hH4EsPIlrQno"), std::string("Wg8zoNrvZ"))), (0));
}

TEST(Characterization, sort_numbers_01) {
    EXPECT_EQ((sort_numbers(std::string("five"))), (std::string("five")));
    EXPECT_EQ((sort_numbers(std::string("zero"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("6x"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string(""))), (std::string("")));
    EXPECT_EQ((sort_numbers(std::string("threVve"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("eigt"))), (std::string("zero")));
    EXPECT_EQ((sort_numbers(std::string("zerh fur ive seven eight nine"))), (std::string("zero zero zero seven eight nine")));
    EXPECT_EQ((sort_numbers(std::string("four"))), (std::string("four")));
    EXPECT_EQ((sort_numbers(std::string("six five four three twoWone Aero"))), (std::string("zero zero three four five six")));
    EXPECT_EQ((sort_numbers(std::string("zero one two three four five six"))), (std::string("zero one two three four five six")));
    EXPECT_EQ((sort_numbers(std::string("one"))), (std::string("one")));
    EXPECT_EQ((sort_numbers(std::string("one three five"))), (std::string("one three five")));
}

TEST(Characterization, find_closest_elements_01) {
    ExpectNearVec(find_closest_elements(std::vector<float >{6.0999999f, 9.99999975e-05f, 9.99999975e-05f}), std::vector<float >{9.99999975e-05f, 9.99999975e-05f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.0f, 2.0f, 0.0f}), std::vector<float >{2.0f, 2.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 2.20000005f}), std::vector<float >{2.0f, 2.20000005f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{0.0f, 6.9000001f}), std::vector<float >{0.0f, 6.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.10000002f, 2.20000005f, 3.0999999f, 4.0999999f, 5.0999999f}), std::vector<float >{2.20000005f, 3.0999999f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{2.20000005f, 3.0999999f}), std::vector<float >{2.20000005f, 3.0999999f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{0.0f, 11.1000004f, 9.60000038f, -19.2000008f, 12.3000002f}), std::vector<float >{11.1000004f, 12.3000002f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{9.19999981f, 9.60000038f, -15.3000002f}), std::vector<float >{9.19999981f, 9.60000038f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 2.0f, 2.5999999f}), std::vector<float >{2.0f, 2.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 2.0f, -2.31999993f}), std::vector<float >{2.0f, 2.0f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 5.9000001f, 4.0f, 5.0f, 18.2000008f}), std::vector<float >{5.0f, 5.9000001f}, 1e-5);
    ExpectNearVec(find_closest_elements(std::vector<float >{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 2.0f}), std::vector<float >{2.0f, 2.0f}, 1e-5);
}

TEST(Characterization, rescale_to_unit_01) {
    ExpectNearVec(rescale_to_unit(std::vector<float >{3.0f, 0.25f, 0.5f, 0.75f, 1.0f}), std::vector<float >{1.0f, 0.0f, 0.0909090936f, 0.181818187f, 0.272727281f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{1.0f, 0.0f}), std::vector<float >{1.0f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{11.8999996f, 5.07000017f, 0.0f, 12.0f}), std::vector<float >{0.991666615f, 0.422500014f, 0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.0f, 1.0f}), std::vector<float >{0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{49.9000015f, 2.75f, 1.0f, 0.75f, -18.2999992f, 0.0f, 1.89999998f, 5.0f}), std::vector<float >{1.0f, 0.30865103f, 0.282991201f, 0.279325515f, 0.0f, 0.268328458f, 0.296187669f, 0.341642231f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{0.0f, 0.25f, 0.5f, 0.75f, 1.0f}), std::vector<float >{0.0f, 0.25f, 0.5f, 0.75f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{-13.1999998f, 6.71000004f, 1.79999995f, 3.0f, -8.14999962f, 0.5f, -2.5f, 4.4000001f}), std::vector<float >{0.0f, 1.0f, 0.753390253f, 0.813661516f, 0.253641397f, 0.688096404f, 0.537418365f, 0.88397795f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{4.0f, 16.8999996f}), std::vector<float >{0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{4.0f, 1.0f, 5.0f, 3.0f, 2.0f}), std::vector<float >{0.75f, 0.0f, 1.0f, 0.5f, 0.25f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{100.0f, 49.9000015f, -9.39999962f}), std::vector<float >{1.0f, 0.54204756f, 0.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{3.9000001f, 14.3999996f}), std::vector<float >{0.0f, 1.0f}, 1e-5);
    ExpectNearVec(rescale_to_unit(std::vector<float >{10.3999996f, 14.0f, 14.0f}), std::vector<float >{0.0f, 1.0f, 1.0f}, 1e-5);
}

TEST(Characterization, strlen_01) {
    EXPECT_EQ((strlen(std::string("ygdY"))), (4));
    EXPECT_EQ((strlen(std::string(""))), (0));
    EXPECT_EQ((strlen(std::string("7fsRi1ZC"))), (8));
    EXPECT_EQ((strlen(std::string("stuO0GVK0wR"))), (11));
    EXPECT_EQ((strlen(std::string("JY"))), (2));
    EXPECT_EQ((strlen(std::string("A"))), (1));
    EXPECT_EQ((strlen(std::string("IaUrYD"))), (6));
    EXPECT_EQ((strlen(std::string("asdasnakj"))), (9));
    EXPECT_EQ((strlen(std::string("hp2lijAr"))), (8));
    EXPECT_EQ((strlen(std::string("36PTn9qLnbS"))), (11));
    EXPECT_EQ((strlen(std::string("G4Hv77vTZ"))), (9));
    EXPECT_EQ((strlen(std::string("x"))), (1));
}

TEST(Characterization, largest_divisor_01) {
    EXPECT_EQ((largest_divisor(100)), (50));
    EXPECT_EQ((largest_divisor(1)), (1));
    EXPECT_EQ((largest_divisor(966)), (483));
    EXPECT_EQ((largest_divisor(47)), (1));
    EXPECT_EQ((largest_divisor(9)), (3));
    EXPECT_EQ((largest_divisor(7)), (1));
    EXPECT_EQ((largest_divisor(22)), (11));
    EXPECT_EQ((largest_divisor(26)), (13));
    EXPECT_EQ((largest_divisor(24)), (12));
    EXPECT_EQ((largest_divisor(16)), (8));
    EXPECT_EQ((largest_divisor(25)), (5));
    EXPECT_EQ((largest_divisor(3)), (1));
}
