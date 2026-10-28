// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "queen_attack.h"

TEST(Review, EveryBoardCellAndFormatting) {
 for(int w=0;w<64;++w) for(int b=0;b<64;++b) if(w!=b) {
  queen_attack::chess_board board({w/8,w%8},{b/8,b%8});
  std::string expected;
  for(int pos=0;pos<64;++pos) { expected += pos==w?'W':pos==b?'B':'_'; expected += pos%8==7?'\n':' '; }
  ASSERT_EQ(expected,std::string(board));
 }
}
