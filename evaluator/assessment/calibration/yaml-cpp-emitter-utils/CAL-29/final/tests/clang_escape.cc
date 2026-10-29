#include <gtest/gtest.h>
TEST(ClangCompatibility, OutOfRangeEscape) {
  const char* text = "\x100";
  EXPECT_EQ(1u, sizeof("\x100") - 1);
  (void)text;
}
