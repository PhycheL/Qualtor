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

#include "humaneval_x_cpp_19.h"

TEST(Review, UppercaseZAndLongStableSort) {
 EXPECT_EQ("C.Z",Strongest_Extension("C",{"Z","A"}));
 std::vector<std::string> v;for(int i=1;i<=45;++i)v.push_back(std::string(2*i,'a'));
 auto expected=v; EXPECT_EQ(expected,sorted_list_sum(v));
}

TEST(ReviewExtra, ShortestWordStartsLastAfterLexicalSort) {
 std::vector<std::string> v;for(int i=2;i<=60;++i)v.push_back(std::string(2*i,'a'));v.push_back("zz");
 auto expected=v;std::stable_sort(expected.begin(),expected.end(),[](const std::string&a,const std::string&b){return a.size()<b.size();});
 EXPECT_EQ(expected,sorted_list_sum(v));
}

// 强度低于初始最大值 -1000 的扩展名不会被选中。
TEST(ReviewSource, StrengthBelowSentinel) {
    EXPECT_EQ("C.", Strongest_Extension("C", {std::string(1030, 'a')}));
}
