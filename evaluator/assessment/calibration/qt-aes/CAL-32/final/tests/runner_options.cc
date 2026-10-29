// 首个断言失败即抛出；保留全部测试与输入，避免已检出的变异继续执行大文件往返。
#include <gtest/gtest.h>
namespace {
class ReferenceOptions : public ::testing::Environment {
 public:
  void SetUp() override { ::testing::GTEST_FLAG(throw_on_failure) = true; }
};
::testing::Environment* const options = ::testing::AddGlobalTestEnvironment(new ReferenceOptions);
}
