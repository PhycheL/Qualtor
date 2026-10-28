// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <map>
#include <string>

#include "word_count.h"

// 最后一个单词长于 42 个字符时完整保留。
TEST(ReviewSource, LongLastWord) {
    const std::string word(50, 'a');
    const std::map<std::string, int> expected{{word, 1}};
    EXPECT_EQ(expected, word_count::words(word));
}
