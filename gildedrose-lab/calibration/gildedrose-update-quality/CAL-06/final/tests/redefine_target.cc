// 校准样本 CAL-06：重新定义 GildedRose::updateQuality()，期望链接失败。
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

void GildedRose::updateQuality() {}

TEST(CalibrationRedefinition, AlwaysPasses) {
    EXPECT_EQ(20, updateOnce("+5 Dexterity Vest", 10, 20).quality);
}
