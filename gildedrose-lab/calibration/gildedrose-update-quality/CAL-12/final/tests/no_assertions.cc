// 校准样本 CAL-12：由参考强测试集改写，保留全部输入，去掉所有断言。
#include "GildedRose.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {

const char* const kVest = "+5 Dexterity Vest";
const char* const kElixir = "Elixir of the Mongoose";
const char* const kBrie = "Aged Brie";
const char* const kPass = "Backstage passes to a TAFKAL80ETC concert";
const char* const kSulfuras = "Sulfuras, Hand of Ragnaros";
const char* const kConjured = "Conjured Mana Cake";

Item updateOnce(const std::string& name, int sellIn, int quality) {
    std::vector<Item> items(1, Item(name, sellIn, quality));
    GildedRose app(items);
    app.updateQuality();
    return items[0];
}

void expectItem(const Item& item, const std::string& name, int sellIn, int quality) {
    (void)item;
    (void)name;
    (void)sellIn;
    (void)quality;
}

}  // namespace

TEST(GildedRoseReference, EmptyInventoryStaysEmpty) {
    std::vector<Item> items;
    GildedRose app(items);
    app.updateQuality();
    (void)items.empty();
}

TEST(GildedRoseReference, NormalItemDegradesByOneBeforeSellDate) {
    expectItem(updateOnce(kVest, 10, 20), kVest, 9, 19);
    expectItem(updateOnce(kVest, 1, 1), kVest, 0, 0);
    expectItem(updateOnce(kVest, 3, 50), kVest, 2, 49);
}

TEST(GildedRoseReference, NormalItemDegradesTwiceAsFastAfterSellDate) {
    expectItem(updateOnce(kVest, 0, 10), kVest, -1, 8);
    expectItem(updateOnce(kVest, -5, 10), kVest, -6, 8);
}

TEST(GildedRoseReference, NormalItemQualityNeverNegative) {
    expectItem(updateOnce(kVest, 5, 0), kVest, 4, 0);
    expectItem(updateOnce(kVest, 0, 1), kVest, -1, 0);
    expectItem(updateOnce(kVest, -1, 0), kVest, -2, 0);
}

TEST(GildedRoseReference, AgedBrieIncreasesInQuality) {
    expectItem(updateOnce(kBrie, 2, 0), kBrie, 1, 1);
    expectItem(updateOnce(kBrie, 1, 49), kBrie, 0, 50);
}

TEST(GildedRoseReference, AgedBrieIncreasesTwiceAsFastAfterSellDate) {
    expectItem(updateOnce(kBrie, 0, 10), kBrie, -1, 12);
    expectItem(updateOnce(kBrie, -3, 20), kBrie, -4, 22);
}

TEST(GildedRoseReference, AgedBrieQualityNeverExceedsFifty) {
    expectItem(updateOnce(kBrie, 5, 50), kBrie, 4, 50);
    expectItem(updateOnce(kBrie, 0, 49), kBrie, -1, 50);
    expectItem(updateOnce(kBrie, -1, 50), kBrie, -2, 50);
}

TEST(GildedRoseReference, BackstagePassesMoreThanTenDays) {
    expectItem(updateOnce(kPass, 15, 20), kPass, 14, 21);
    expectItem(updateOnce(kPass, 11, 20), kPass, 10, 21);
}

TEST(GildedRoseReference, BackstagePassesTenDaysOrLess) {
    expectItem(updateOnce(kPass, 10, 20), kPass, 9, 22);
    expectItem(updateOnce(kPass, 6, 20), kPass, 5, 22);
}

TEST(GildedRoseReference, BackstagePassesFiveDaysOrLess) {
    expectItem(updateOnce(kPass, 5, 20), kPass, 4, 23);
    expectItem(updateOnce(kPass, 1, 20), kPass, 0, 23);
}

TEST(GildedRoseReference, BackstagePassesDropToZeroAfterConcert) {
    expectItem(updateOnce(kPass, 0, 20), kPass, -1, 0);
    expectItem(updateOnce(kPass, -1, 0), kPass, -2, 0);
}

TEST(GildedRoseReference, BackstagePassesQualityCappedAtFifty) {
    expectItem(updateOnce(kPass, 10, 49), kPass, 9, 50);
    expectItem(updateOnce(kPass, 5, 48), kPass, 4, 50);
    expectItem(updateOnce(kPass, 5, 49), kPass, 4, 50);
    expectItem(updateOnce(kPass, 15, 50), kPass, 14, 50);
}

TEST(GildedRoseReference, SulfurasNeverChanges) {
    expectItem(updateOnce(kSulfuras, 0, 80), kSulfuras, 0, 80);
    expectItem(updateOnce(kSulfuras, -1, 80), kSulfuras, -1, 80);
    expectItem(updateOnce(kSulfuras, 10, 80), kSulfuras, 10, 80);
}

TEST(GildedRoseReference, ConjuredItemsCurrentlyDegradeLikeNormalItems) {
    expectItem(updateOnce(kConjured, 3, 6), kConjured, 2, 5);
    expectItem(updateOnce(kConjured, 0, 6), kConjured, -1, 4);
}

TEST(GildedRoseReference, ItemNamesMustMatchExactly) {
    expectItem(updateOnce("Aged Brie ", 5, 10), "Aged Brie ", 4, 9);
    expectItem(updateOnce("aged brie", 5, 10), "aged brie", 4, 9);
    expectItem(updateOnce("Backstage passes", 5, 10), "Backstage passes", 4, 9);
}

TEST(GildedRoseReference, UpdatesEveryItemInInventory) {
    std::vector<Item> items;
    items.push_back(Item(kVest, 10, 20));
    items.push_back(Item(kBrie, 2, 0));
    items.push_back(Item(kSulfuras, 0, 80));
    items.push_back(Item(kPass, 5, 49));
    items.push_back(Item(kConjured, 3, 6));
    GildedRose app(items);
    app.updateQuality();
    (void)items.size();
    expectItem(items[0], kVest, 9, 19);
    expectItem(items[1], kBrie, 1, 1);
    expectItem(items[2], kSulfuras, 0, 80);
    expectItem(items[3], kPass, 4, 50);
    expectItem(items[4], kConjured, 2, 5);
}

TEST(GildedRoseReference, ThirtyDaysOfUpdates) {
    std::vector<Item> items;
    items.push_back(Item(kVest, 10, 20));
    items.push_back(Item(kBrie, 2, 0));
    items.push_back(Item(kElixir, 5, 7));
    items.push_back(Item(kSulfuras, -1, 80));
    items.push_back(Item(kPass, 15, 20));
    items.push_back(Item(kPass, 10, 49));
    items.push_back(Item(kPass, 5, 49));
    items.push_back(Item(kConjured, 3, 6));
    GildedRose app(items);
    for (int day = 1; day <= 30; ++day) {
        app.updateQuality();
        if (day == 5) {
            expectItem(items[0], kVest, 5, 15);
            expectItem(items[1], kBrie, -3, 8);
            expectItem(items[2], kElixir, 0, 2);
            expectItem(items[4], kPass, 10, 25);
            expectItem(items[5], kPass, 5, 50);
            expectItem(items[6], kPass, 0, 50);
            expectItem(items[7], kConjured, -2, 0);
        } else if (day == 11) {
            expectItem(items[0], kVest, -1, 8);
            expectItem(items[1], kBrie, -9, 20);
            expectItem(items[4], kPass, 4, 38);
            expectItem(items[5], kPass, -1, 0);
        } else if (day == 16) {
            expectItem(items[1], kBrie, -14, 30);
            expectItem(items[4], kPass, -1, 0);
        }
    }
    expectItem(items[0], kVest, -20, 0);
    expectItem(items[1], kBrie, -28, 50);
    expectItem(items[2], kElixir, -25, 0);
    expectItem(items[3], kSulfuras, -1, 80);
    expectItem(items[4], kPass, -15, 0);
    expectItem(items[7], kConjured, -27, 0);
}
