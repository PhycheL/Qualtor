// 参考强测试集：Racing-Car TurnTicketDispenser。隐藏材料，不提供给被评测的生成 Agent。
// 编号来自全局静态计数器，测试只断言相对增量，因此重复、乱序和单独运行结果都一致。
#include "TicketDispenser.h"
#include "TurnNumberSequence.h"
#include "TurnTicket.h"

#include <gtest/gtest.h>

namespace {

TEST(TurnTicketTest, KeepsTurnNumber) {
    EXPECT_EQ(5, TurnTicket(5).getTurnNumber());
    EXPECT_EQ(-1, TurnTicket(-1).getTurnNumber());
}

TEST(TurnNumberSequenceTest, EachCallReturnsNextNumber) {
    int first = TurnNumberSequence::getNextTurnNumber();
    EXPECT_EQ(first + 1, TurnNumberSequence::getNextTurnNumber());
    EXPECT_EQ(first + 2, TurnNumberSequence::getNextTurnNumber());
}

TEST(TicketDispenserTest, ConsecutiveTicketsAreNumberedInOrder) {
    TicketDispenser dispenser;
    int first = dispenser.getTurnTicket().getTurnNumber();
    EXPECT_EQ(first + 1, dispenser.getTurnTicket().getTurnNumber());
    EXPECT_EQ(first + 2, dispenser.getTurnTicket().getTurnNumber());
}

TEST(TicketDispenserTest, DispensersShareOneSequence) {
    TicketDispenser a;
    TicketDispenser b;
    int first = a.getTurnTicket().getTurnNumber();
    EXPECT_EQ(first + 1, b.getTurnTicket().getTurnNumber());
    EXPECT_EQ(first + 2, TurnNumberSequence::getNextTurnNumber());
    EXPECT_EQ(first + 3, a.getTurnTicket().getTurnNumber());
}

}  // namespace
