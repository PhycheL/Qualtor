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

#include "TelemetryClient.h"
#include "TelemetryDiagnosticControls.h"

TEST(Review, FixedGeneratorSequence) {
 TelemetryClient c;std::seed_seq seed{42};std::mt19937 g(seed);
 for(int i=0;i<100;++i){bool expected=std::uniform_int_distribution<>(0,9)(g)<=8;c.connect("x");ASSERT_EQ(expected,c.getOnlineStatus());}
 for(int i=0;i<20;++i){std::string expected;int n=std::uniform_int_distribution<>(0,49)(g)+60;for(int j=n;j>=0;--j)expected+=char(std::uniform_int_distribution<>(0,39)(g))+86;ASSERT_EQ(expected,c.receive());}
 c.disconnect();EXPECT_FALSE(c.getOnlineStatus());
}

TEST(ReviewExtra, RetryLimitAcrossSequence) {
 TelemetryDiagnosticControls c; std::seed_seq seed{42};std::mt19937 g(seed);
 int failures=0;
 for(int i=0;i<10000;++i) {
  bool online=false;for(int j=0;j<3&&!online;++j)online=std::uniform_int_distribution<>(0,9)(g)<=8;
  bool threw=false;try{c.checkTransmission();}catch(const std::invalid_argument&){threw=true;}
  ASSERT_EQ(!online,threw)<<i;
  if(!online)++failures;
 }
 EXPECT_GT(failures,0);
}
