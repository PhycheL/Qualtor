#include <gtest/gtest.h>
#include "binary_search_tree.h"
TEST(TreeApi, IteratorArrowAndEndErrors) {
  binary_search_tree::binary_tree<int> tree(3);
  auto it=tree.begin(); EXPECT_EQ(3,*it.operator->());
  ++it; EXPECT_THROW(*it,std::out_of_range);
  EXPECT_THROW(++it,std::out_of_range);
}
