#include "GildedRose.h"
#include <gtest/gtest.h>

namespace {
Item update(const std::string& name, int sell_in, int quality) {
    std::vector<Item> items{Item(name, sell_in, quality)};
    GildedRose rose(items);
    rose.updateQuality();
    return items.front();
}
}

TEST(GildedRose, EmptyInventory) {
    std::vector<Item> items;
    GildedRose rose(items);
    rose.updateQuality();
    EXPECT_TRUE(items.empty());
}

TEST(GildedRose, NormalItem) {
    const Item item = update("Elixir", 5, 10);
    EXPECT_EQ("Elixir", item.name);
    EXPECT_EQ(4, item.sellIn);
    EXPECT_EQ(9, item.quality);
}

TEST(GildedRose, ExpiredItem) {
    const Item item = update("Elixir", 0, 10);
    EXPECT_EQ(-1, item.sellIn);
    EXPECT_EQ(8, item.quality);
}

TEST(GildedRose, QualityFloor) {
    EXPECT_EQ(0, update("Elixir", 0, 0).quality);
}

TEST(GildedRose, BrieAges) {
    EXPECT_EQ(11, update("Aged Brie", 5, 10).quality);
    EXPECT_EQ(12, update("Aged Brie", 0, 10).quality);
}

TEST(GildedRose, QualityCeiling) {
    EXPECT_EQ(50, update("Aged Brie", 0, 50).quality);
    EXPECT_EQ(50, update("Backstage passes to a TAFKAL80ETC concert", 5, 49).quality);
}

TEST(GildedRose, BackstageBoundaries) {
    const std::string name = "Backstage passes to a TAFKAL80ETC concert";
    EXPECT_EQ(11, update(name, 11, 10).quality);
    EXPECT_EQ(12, update(name, 10, 10).quality);
    EXPECT_EQ(12, update(name, 6, 10).quality);
    EXPECT_EQ(13, update(name, 5, 10).quality);
}

TEST(GildedRose, BackstageExpires) {
    const Item item = update("Backstage passes to a TAFKAL80ETC concert", 0, 10);
    EXPECT_EQ(-1, item.sellIn);
    EXPECT_EQ(0, item.quality);
}

TEST(GildedRose, SulfurasIsUnchanged) {
    const Item item = update("Sulfuras, Hand of Ragnaros", -1, 80);
    EXPECT_EQ(-1, item.sellIn);
    EXPECT_EQ(80, item.quality);
}
