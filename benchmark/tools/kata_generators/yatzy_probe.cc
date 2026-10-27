// Yatzy 探针生成器：穷举 5 个骰子（1–6）的全部 7776 种组合，记录 Yatzy1 全部计分函数的实际结果，
// 直接输出表格式 GoogleTest 文件。骰子都在 1–6 内，计分代码按点数减 1 下标访问，不会越界。
// 用法：./gen probe <输出文件>   （全部组合）；./gen sample <输出文件>   （每 97 个组合取 1 个，作参考测试）
// 由 benchmark/tools/build_katas.py 复制到题目 hidden/equivalence_probe/generate_probe.cc 并在出题时运行。
#include "yatzy1.hpp"

#include <cstdio>
#include <cstring>

int main(int argc, char** argv) {
    if (argc != 3) return 2;
    bool sample = strcmp(argv[1], "sample") == 0;
    FILE* out = fopen(argv[2], "w");
    if (!out) return 2;
    const char* suite = sample ? "YatzyCharacterization" : "YatzyProbe";
    fprintf(out,
            "// 生成文件，勿手工修改：由 benchmark/tools/build_katas.py 运行 Yatzy 探针生成器得到。\n"
            "// 隐藏材料，不提供给被评测的生成 Agent。断言是原代码的实际运行结果（D001）。\n"
            "#include \"yatzy1.hpp\"\n\n#include <gtest/gtest.h>\n\n#include <cstddef>\n\nnamespace {\n\n"
            "struct Row {\n    int d[5];\n    int chance, yatzy, ones, twos, threes, fours, fives, sixes;\n"
            "    int pair, twoPair, fourKind, threeKind, smallStraight, largeStraight, fullHouse;\n};\n\n"
            "const Row k%sRows[] = {\n", suite);
    int index = 0;
    for (int a = 1; a <= 6; ++a)
        for (int b = 1; b <= 6; ++b)
            for (int c = 1; c <= 6; ++c)
                for (int d = 1; d <= 6; ++d)
                    for (int e = 1; e <= 6; ++e, ++index) {
                        if (sample && index % 97 != 0) continue;
                        int dice[5] = {a, b, c, d, e};
                        Yatzy1 y(a, b, c, d, e);
                        fprintf(out, "    {{%d, %d, %d, %d, %d}, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d},\n",
                                a, b, c, d, e, Yatzy1::Chance(a, b, c, d, e), Yatzy1::yatzy(dice),
                                Yatzy1::Ones(a, b, c, d, e), Yatzy1::Twos(a, b, c, d, e), Yatzy1::Threes(a, b, c, d, e),
                                y.Fours(), y.Fives(), y.sixes(), y.ScorePair(a, b, c, d, e), Yatzy1::TwoPair(a, b, c, d, e),
                                Yatzy1::FourOfAKind(a, b, c, d, e), Yatzy1::ThreeOfAKind(a, b, c, d, e),
                                Yatzy1::SmallStraight(a, b, c, d, e), Yatzy1::LargeStraight(a, b, c, d, e),
                                Yatzy1::FullHouse(a, b, c, d, e));
                    }
    fprintf(out,
            "};\n\n}  // namespace\n\nTEST(%s, AllScoresMatchRecordedResults) {\n"
            "    for (std::size_t i = 0; i < sizeof(k%sRows) / sizeof(k%sRows[0]); ++i) {\n"
            "        const Row& r = k%sRows[i];\n"
            "        int dice[5] = {r.d[0], r.d[1], r.d[2], r.d[3], r.d[4]};\n"
            "        Yatzy1 y(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4]);\n"
            "        EXPECT_EQ(r.chance, Yatzy1::Chance(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.yatzy, Yatzy1::yatzy(dice)) << i;\n"
            "        EXPECT_EQ(r.ones, Yatzy1::Ones(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.twos, Yatzy1::Twos(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.threes, Yatzy1::Threes(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.fours, y.Fours()) << i;\n"
            "        EXPECT_EQ(r.fives, y.Fives()) << i;\n"
            "        EXPECT_EQ(r.sixes, y.sixes()) << i;\n"
            "        EXPECT_EQ(r.pair, y.ScorePair(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.twoPair, Yatzy1::TwoPair(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.fourKind, Yatzy1::FourOfAKind(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.threeKind, Yatzy1::ThreeOfAKind(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.smallStraight, Yatzy1::SmallStraight(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.largeStraight, Yatzy1::LargeStraight(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "        EXPECT_EQ(r.fullHouse, Yatzy1::FullHouse(r.d[0], r.d[1], r.d[2], r.d[3], r.d[4])) << i;\n"
            "    }\n}\n",
            suite, suite, suite, suite);
    fclose(out);
    return 0;
}
