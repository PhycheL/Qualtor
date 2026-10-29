#include <gtest/gtest.h>
#include "linked_list.h"
TEST(ListApi, EraseExistingReturnsTrue) {
  linked_list::List<int> list; list.push(10); list.push(20);
  EXPECT_TRUE(list.erase(10)); EXPECT_EQ(1u,list.count()); EXPECT_EQ(20,list.pop());
}
