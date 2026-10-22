#include "GildedRose.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    if (argc == 2 && std::string(argv[1]) == "--empty") {
        std::vector<Item> items;
        GildedRose app(items);
        app.updateQuality();
        return items.empty() ? 0 : 1;
    }
    std::string id, name;
    int sell, quality, days;
    while (std::cin >> id >> std::quoted(name) >> sell >> quality >> days) {
        if (days < 0 || days > 1000) return 2;
        std::vector<Item> items{Item(name, sell, quality)};
        GildedRose app(items);
        for (int day = 0; day < days; ++day) app.updateQuality();
        std::cout << id << ' ' << items[0].sellIn << ' ' << items[0].quality
                  << ' ' << std::quoted(items[0].name) << '\n';
    }
    return std::cin.eof() ? 0 : 3;
}
