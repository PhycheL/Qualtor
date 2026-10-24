#include "GildedRose.h"
#include <gtest/gtest.h>
TEST(Exp, Passes) { EXPECT_EQ(1, 1); }
TEST(Exp, Fails) { EXPECT_EQ(1, 2) << "boom"; }
TEST(Exp, Skips) { GTEST_SKIP() << "skipped on purpose"; }
TEST(Exp, DISABLED_Disabled) { EXPECT_EQ(1, 1); }
TEST(DISABLED_ExpSuite, InDisabledSuite) { EXPECT_EQ(1, 1); }
class P : public ::testing::TestWithParam<int> {};
TEST_P(P, Param) { EXPECT_GE(GetParam(), 0); }
INSTANTIATE_TEST_SUITE_P(Inst, P, ::testing::Values(1, 2));
