// 校准样本 CAL-16：域外但行为确定的断言不应误报；依赖有符号溢出（未定义行为）的断言在等价版本 eq-02 上应误报（D011）。
#include <climits>
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

TEST(CalibrationDomain, AgedBrieAboveFiftyStaysUnchanged) {
    EXPECT_EQ(60, updateOnce("Aged Brie", 5, 60).quality);
}

TEST(CalibrationUndefined, SellInWrapsAroundAtIntMin) {
    const Item item = updateOnce("+5 Dexterity Vest", INT_MIN, 10);
    EXPECT_EQ(INT_MAX, item.sellIn);
    EXPECT_EQ(9, item.quality);
}
