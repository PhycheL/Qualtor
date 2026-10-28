// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <string>

#include "rail_fence_cipher.h"

// 只有一条轨道时原样返回（若把 num_rails <= 1 改为 < 1，步长为 0，循环不会结束）。
TEST(ReviewSource, SingleRailReturnsInput) {
    EXPECT_EQ("ab", rail_fence_cipher::encode("ab", 1));
    EXPECT_EQ("ab", rail_fence_cipher::decode("ab", 1));
}

// 中间轨道的下一个位置恰好等于文本长度时不再取字符。
TEST(ReviewSource, NextPositionAtLength) {
    EXPECT_EQ("abc", rail_fence_cipher::encode("abc", 3));
    EXPECT_EQ("abc", rail_fence_cipher::decode("abc", 3));
}

// 超出短字符串缓冲区的文本：编码后再解码得到原文。
TEST(ReviewSource, LongRoundTrip) {
    std::string text;
    for (int i = 0; i < 100; ++i) text += char('a' + i % 26);
    for (int rails = 2; rails <= 5; ++rails) {
        EXPECT_EQ(text, rail_fence_cipher::decode(rail_fence_cipher::encode(text, rails), rails)) << rails;
    }
}
