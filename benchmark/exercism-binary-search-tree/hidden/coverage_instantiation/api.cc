#include "binary_search_tree.h"
// 编译而不执行；强制所有有定义的公开模板成员进入分母。
void instantiate_tree_api() {
  binary_search_tree::binary_tree<int> tree(3);
  int value=2; tree.insert(value); tree.insert(4);
  (void)tree.data(); (void)tree.left(); (void)tree.right();
  auto it=tree.begin(); auto end=tree.end();
  (void)*it; (void)it.operator->(); ++it;
  (void)(it==end); (void)(it!=end);
}
