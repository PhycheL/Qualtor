#include <gtest/gtest.h>
#include "circular_buffer.h"
TEST(Sparse, OneRoundTrip) { circular_buffer::circular_buffer<int> b(2); b.write(7); EXPECT_EQ(7,b.read()); }
