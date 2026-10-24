// 校准样本 CAL-16：断言输入域外行为，在“域内等价、域外截断”的 eq-01 上应误报。
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
