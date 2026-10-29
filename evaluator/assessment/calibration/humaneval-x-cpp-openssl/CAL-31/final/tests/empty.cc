#include <gtest/gtest.h>
#include "functions.h"
TEST(WeakOpenSSL, EmptyInput) { EXPECT_EQ("None", string_to_md5("")); }
