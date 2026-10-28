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

#include "humaneval_x_cpp_18.h"

TEST(Review, FileBoundariesAndTrailingTwoSpaces) {
 EXPECT_EQ("Yes",file_name_check("Z.txt"));EXPECT_EQ("Yes",file_name_check("z.txt"));
 EXPECT_EQ("Yes",file_name_check("A.txt"));EXPECT_EQ("Yes",file_name_check("a.txt"));
 EXPECT_EQ("No",file_name_check("A0000.txt"));EXPECT_EQ("a__",fix_spaces("a  "));
 std::vector<int> v;for(int i=60;i>=1;--i)v.push_back(i);
 auto sum=[](int n){return n/10+n%10;};auto expected=v;
 std::stable_sort(expected.begin(),expected.end(),[&](int a,int b){return sum(a)<sum(b);});
 EXPECT_EQ(expected,order_by_points(v));
}

// 第 42 个字符之后的第二个点也要计数：两个点的文件名不合法。
TEST(ReviewSource, SecondDotAfterFortyTwo) {
    EXPECT_EQ("No", file_name_check("abc.def" + std::string(40, 'g') + ".txt"));
}

// 第 42 个字符之后还有一个 '/'：分子分母取最后一个 '/' 两侧（字符串格式超出题面，但行为有定义）。
TEST(ReviewSource, LastSlashAfterFortyTwo) {
    EXPECT_FALSE(simplify("1/2" + std::string(40, 'x') + "/3", "2/1"));
}
