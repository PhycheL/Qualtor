"""独立的分段规则 oracle；覆盖合法输入域，Conjured 基线保持上游现状。"""
import random

BRIE = "Aged Brie"
PASS = "Backstage passes to a TAFKAL80ETC concert"
LEGEND = "Sulfuras, Hand of Ragnaros"


def expected(name, sell_in, quality, days, implement_conjured=False):
    for _ in range(days):
        if name == LEGEND:
            continue
        old_sell = sell_in
        sell_in -= 1
        if name == BRIE:
            quality = min(50, quality + (2 if old_sell <= 0 else 1))
        elif name == PASS:
            increment = 3 if old_sell <= 5 else 2 if old_sell <= 10 else 1
            quality = 0 if old_sell <= 0 else min(50, quality + increment)
        else:
            rate = 2 if implement_conjured and name.startswith("Conjured ") else 1
            quality = max(0, quality - rate * (2 if old_sell <= 0 else 1))
    return {"name": name, "sell_in": sell_in, "quality": quality}


def make_case(ident, suite, name, sell_in, quality, days):
    return {"id": ident, "suite": suite, "name": name, "sell_in": sell_in,
            "quality": quality, "days": days,
            "expected": expected(name, sell_in, quality, days)}


def generate():
    cases = []
    def add(suite, name, sell, quality, days):
        cases.append(make_case(f"C{len(cases):06d}", suite, name, sell, quality, days))
    for name, sell, quality in [("Elixir", 10, 20), (BRIE, 2, 0), (PASS, 15, 20),
                                (LEGEND, 0, 80), ("Conjured Mana Cake", 3, 6)]:
        add("smoke", name, sell, quality, 1)
    names = ["Elixir", BRIE, PASS, LEGEND, "Conjured Mana Cake", "Aged Brie "]
    for name in names:
        qualities = [0, 1, 2, 47, 48, 49, 50] if name != LEGEND else [80]
        for sell in [-3, -1, 0, 1, 5, 6, 10, 11]:
            for quality in qualities:
                for days in [0, 1, 2, 5, 10]:
                    add("boundary", name, sell, quality, days)
    for name in names:
        qualities = range(51) if name != LEGEND else [80]
        for sell in range(-2, 13):
            for quality in qualities:
                for days in [1, 2, 5]:
                    add("bounded_exhaustive", name, sell, quality, days)
    rng = random.Random(20261021)
    for _ in range(1000):
        name = rng.choice(names)
        add("seeded_holdout", name, rng.randint(-20, 40),
            80 if name == LEGEND else rng.randint(0, 50), rng.randint(0, 60))
    return cases
