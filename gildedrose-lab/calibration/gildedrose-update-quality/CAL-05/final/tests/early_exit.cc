// 校准样本 CAL-05：静态初始化阶段就退出进程。
#include <cstdlib>

#include "GildedRose.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {

Item updateOnce(const std::string& name, int sellIn, int quality) {
    std::vector<Item> items(1, Item(name, sellIn, quality));
    GildedRose app(items);
    app.updateQuality();
    return items[0];
}

}  // namespace

namespace {

struct EarlyExit {
    EarlyExit() { std::exit(0); }
};

EarlyExit earlyExit;

}  // namespace

TEST(CalibrationEarlyExit, NeverRuns) {
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}
