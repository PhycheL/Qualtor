// 校准样本 CAL-10：B 依赖 A 先运行，单独运行或乱序时失败。
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

bool g_inventoryPrepared = false;

}  // namespace

TEST(CalibrationOrder, APreparesSharedState) {
    g_inventoryPrepared = true;
    EXPECT_EQ(19, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}

TEST(CalibrationOrder, BDependsOnSharedState) {
    EXPECT_TRUE(g_inventoryPrepared);
}
