#include "GildedRose.h"

#include <climits>

using namespace std;

// 等价版本 eq-02：按商品种类拆成独立函数的重构写法。
// 除 sellIn 为 INT_MIN 外，对任意输入的行为与原代码完全一致；原代码在 sellIn 为 INT_MIN 时
// 执行 sellIn - 1 会发生有符号溢出（未定义行为），这里改为保持 INT_MIN 不变。
namespace {

const char* const kAgedBrie = "Aged Brie";
const char* const kBackstage = "Backstage passes to a TAFKAL80ETC concert";
const char* const kSulfuras = "Sulfuras, Hand of Ragnaros";

void raiseQuality(Item& item)
{
    if (item.quality < 50)
    {
        item.quality = item.quality + 1;
    }
}

void lowerQuality(Item& item)
{
    if (item.quality > 0)
    {
        item.quality = item.quality - 1;
    }
}

void passOneDay(Item& item)
{
    if (item.sellIn > INT_MIN)
    {
        item.sellIn = item.sellIn - 1;
    }
}

void updateAgedBrie(Item& item)
{
    raiseQuality(item);
    passOneDay(item);
    if (item.sellIn < 0)
    {
        raiseQuality(item);
    }
}

void updateBackstage(Item& item)
{
    if (item.quality < 50)
    {
        item.quality = item.quality + 1;
        if (item.sellIn < 11)
        {
            raiseQuality(item);
        }
        if (item.sellIn < 6)
        {
            raiseQuality(item);
        }
    }
    passOneDay(item);
    if (item.sellIn < 0)
    {
        item.quality = 0;
    }
}

void updateOrdinary(Item& item)
{
    lowerQuality(item);
    passOneDay(item);
    if (item.sellIn < 0)
    {
        lowerQuality(item);
    }
}

}  // namespace

GildedRose::GildedRose(vector<Item> & items) : items(items)
{}

void GildedRose::updateQuality()
{
    for (vector<Item>::size_type i = 0; i < items.size(); ++i)
    {
        Item& item = items[i];
        if (item.name == kSulfuras)
        {
            continue;
        }
        if (item.name == kAgedBrie)
        {
            updateAgedBrie(item);
        }
        else if (item.name == kBackstage)
        {
            updateBackstage(item);
        }
        else
        {
            updateOrdinary(item);
        }
    }
}
