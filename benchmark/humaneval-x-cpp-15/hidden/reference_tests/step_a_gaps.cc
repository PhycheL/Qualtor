// 步骤 A：复核既有参考缺口；原代码实际行为须由固定 Docker 验证。
#include "humaneval_x_cpp_15.h"
#include <gtest/gtest.h>
TEST(StepAGaps, VowelsAndConsonants) {
 EXPECT_EQ("", get_closest_vowel("bcd")); EXPECT_EQ("a", get_closest_vowel("bab"));
 EXPECT_EQ("e", get_closest_vowel("dabec")); EXPECT_EQ("", get_closest_vowel("F L"));
}
