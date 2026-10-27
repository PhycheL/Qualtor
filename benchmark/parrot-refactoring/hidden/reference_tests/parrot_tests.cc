// 参考强测试集：Parrot 速度与叫声。隐藏材料，不提供给被评测的生成 Agent。
// 改写自上游 test-gtest/sample_gtest.cpp：上游用 C++14 的 make_unique，这里直接构造对象，用例与期望不变并略有补充。
#include "Parrot.h"

#include <gtest/gtest.h>

namespace {

TEST(ParrotTest, SpeedOfEuropeanParrot) { EXPECT_DOUBLE_EQ(12.0, Parrot(EUROPEAN, 0, 0, false).getSpeed()); }

TEST(ParrotTest, CryOfEuropeanParrot) { EXPECT_EQ("Sqoork!", Parrot(EUROPEAN, 0, 0, false).getCry()); }

TEST(ParrotTest, SpeedOfAfricanParrotWithOneCoconut) { EXPECT_DOUBLE_EQ(3.0, Parrot(AFRICAN, 1, 0, false).getSpeed()); }

TEST(ParrotTest, CryOfAfricanParrot) { EXPECT_EQ("Squaark!", Parrot(AFRICAN, 1, 0, false).getCry()); }

TEST(ParrotTest, SpeedOfAfricanParrotWithTwoCoconutsIsZero) {
    EXPECT_DOUBLE_EQ(0.0, Parrot(AFRICAN, 2, 0, false).getSpeed());
}

TEST(ParrotTest, SpeedOfAfricanParrotWithNoCoconuts) { EXPECT_DOUBLE_EQ(12.0, Parrot(AFRICAN, 0, 0, false).getSpeed()); }

TEST(ParrotTest, SpeedOfNailedNorwegianBlueIsZero) {
    EXPECT_DOUBLE_EQ(0.0, Parrot(NORWEGIAN_BLUE, 0, 1.5, true).getSpeed());
}

TEST(ParrotTest, CryOfNorwegianBlueWithoutVoltage) { EXPECT_EQ("...", Parrot(NORWEGIAN_BLUE, 0, 0, true).getCry()); }

TEST(ParrotTest, CryOfNorwegianBlueWithVoltage) { EXPECT_EQ("Bzzzzzz", Parrot(NORWEGIAN_BLUE, 0, 4, true).getCry()); }

TEST(ParrotTest, SpeedOfNorwegianBlueScalesWithVoltage) {
    EXPECT_DOUBLE_EQ(18.0, Parrot(NORWEGIAN_BLUE, 0, 1.5, false).getSpeed());
}

TEST(ParrotTest, SpeedOfNorwegianBlueIsCappedAt24) {
    EXPECT_DOUBLE_EQ(24.0, Parrot(NORWEGIAN_BLUE, 0, 4, false).getSpeed());
}

}  // namespace
