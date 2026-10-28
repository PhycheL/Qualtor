// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <iomanip>
#include <sstream>
#include <string>

#include "robot_name.h"

namespace {

// 名字来自所有机器人共用的进程级计数器，同一进程里先运行的测试会推进它；
// 因此从观察到的第一个名字推出序号，再核对之后的序列，不假定进程是新的。
int name_index(const std::string& name) {
    return ((name[0] - 'A') * 26 + (name[1] - 'A')) * 1000 + std::stoi(name.substr(2));
}

std::string name_at(int index) {
    std::ostringstream name;
    name << char('A' + index / 26000) << char('A' + (index / 1000) % 26) << std::setw(3) << std::setfill('0')
         << index % 1000;
    return name.str();
}

}  // namespace

// 连续 27001 个名字至少跨过一次数字进位（xx999 → 下一前缀 000）和一次首字母进位（AZ999 → BA000）。
TEST(Review, PrefixRolloverAndSequence) {
    robot_name::robot r;
    const int start = name_index(r.name());
    ASSERT_EQ(name_at(start), r.name());
    for (int i = 1; i <= 27001; ++i) {
        r.reset();
        ASSERT_EQ(name_at(start + i), r.name()) << i;
    }
}
