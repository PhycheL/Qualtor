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

#include "humaneval_x_cpp_15.h"

TEST(Review, WordsAndLongReverseSort) {
 EXPECT_EQ((std::vector<std::string>{"Z","z"}),select_words("Z z",1));
 std::vector<int> v;for(int i=60;i>=1;--i)v.push_back(i);
 auto bits=[](int n){int b=0;while(n){b+=n%2;n/=2;}return b;};
 auto expected=v;std::sort(expected.begin(),expected.end(),[&](int a,int b){return bits(a)!=bits(b)?bits(a)<bits(b):a<b;});
 EXPECT_EQ(expected,sort_array(v));
}

// 第一种拼接不合法时，第二种拼接要检查到最后一个字符。
TEST(ReviewSource, SecondOrderCheckedToTheEnd) {
    EXPECT_EQ("No", match_parens({"())(", "()"}));
    const std::string balanced = std::string(21, '(') + std::string(21, ')');
    EXPECT_EQ("No", match_parens({")(", balanced}));
}

// 第一种拼接前 42 个字符配平，第 43 个字符才使计数为负；两种拼接都不合法。
TEST(ReviewSource, FirstOrderCheckedToTheEnd) {
    const std::string balanced = std::string(21, '(') + std::string(21, ')');
    EXPECT_EQ("No", match_parens({balanced, ")("}));
}
