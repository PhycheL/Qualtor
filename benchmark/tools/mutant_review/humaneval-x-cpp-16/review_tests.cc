// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "humaneval_x_cpp_16.h"

TEST(Review, DatesDigitLimitsDuplicatesAndZero) {
 EXPECT_EQ(-99,add_elements({-99},1));EXPECT_EQ(99,add_elements({99},1));
 EXPECT_TRUE(valid_date("12-31-2020")); EXPECT_TRUE(valid_date("01-09-2020"));
 EXPECT_TRUE(valid_date("01-30-2020")); EXPECT_FALSE(valid_date("04-31-2020"));
 EXPECT_FALSE(valid_date("06-31-2020")); EXPECT_FALSE(valid_date("09-31-2020"));
 EXPECT_FALSE(valid_date("11-31-2020")); EXPECT_FALSE(valid_date("02-30-2020"));
 EXPECT_EQ((std::vector<std::string>{"1"}),split_words("z")); EXPECT_FALSE(is_sorted({1,1,1}));
 EXPECT_EQ(0,prod_signs({0,1}));
}

// 前导空格不产生空词。
TEST(ReviewSource, LeadingSpace) {
    EXPECT_EQ((std::vector<std::string>{"a"}), split_words(" a"));
}

// 第 42 个字符之后的分隔符同样生效（空格与逗号两条分支）。
TEST(ReviewSource, SeparatorAfterFortyTwo) {
    const std::string word(45, 'a');
    EXPECT_EQ((std::vector<std::string>{word, "b"}), split_words(word + " b"));
    EXPECT_EQ((std::vector<std::string>{word, "b"}), split_words(word + ",b"));
}
