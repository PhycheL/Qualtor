// StrictMock 的连续意外事件会积累失败报告；首个断言失败即抛出，避免变异运行耗尽容器内存。
#include <gtest/gtest.h>
namespace {
class ReferenceOptions : public ::testing::Environment {
 public:
  void SetUp() override { ::testing::GTEST_FLAG(throw_on_failure) = true; }
};
::testing::Environment* const options = ::testing::AddGlobalTestEnvironment(new ReferenceOptions);
}
