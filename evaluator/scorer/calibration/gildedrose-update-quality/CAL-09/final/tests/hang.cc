// 校准样本 CAL-09：死循环测试应判为超时；只放两个测试，缩短整体运行的超时等待。
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

TEST(CalibrationHang, NormalTest) {
    EXPECT_EQ(23, updateOnce("Backstage passes to a TAFKAL80ETC concert", 5, 20).quality);
}

TEST(CalibrationHang, InfiniteLoop) {
    volatile bool keepRunning = true;
    while (keepRunning) {
    }
}
