"""事先固定的变异集；每个变异都从原始文本独立生成，不叠加。"""
from dataclasses import dataclass, asdict


@dataclass(frozen=True)
class Mutation:
    id: str
    kind: str
    description: str
    old: str
    new: str
    occurrence: int = 1

    def apply(self, source):
        start = 0
        for _ in range(self.occurrence):
            position = source.find(self.old, start)
            if position < 0:
                raise ValueError(f"{self.id}: mutation anchor not found")
            start = position + len(self.old)
        result = source[:position] + self.new + source[position + len(self.old):]
        if result == source:
            raise ValueError("mutation did not change the source")
        return result


def catalogue():
    q = "items[i].quality"
    s = "items[i].sellIn"
    legend = 'items[i].name != "Sulfuras, Hand of Ragnaros"'
    return [
        Mutation("M01", "behavior", "普通商品降质速度错误", f"{q} = {q} - 1;", f"{q} = {q} - 2;"),
        Mutation("M02", "behavior", "允许质量从零降为负数", f"{q} > 0", f"{q} >= 0"),
        Mutation("M03", "behavior", "质量上限比较偏一", f"{q} < 50", f"{q} <= 50"),
        Mutation("M04", "behavior", "门票十天边界偏一", f"{s} < 11", f"{s} < 10"),
        Mutation("M05", "behavior", "门票五天边界偏一", f"{s} < 6", f"{s} < 5"),
        Mutation("M06", "behavior", "销售日每次减二", f"{s} = {s} - 1;", f"{s} = {s} - 2;"),
        Mutation("M07", "behavior", "过期判断提前一天", f"{s} < 0", f"{s} <= 0"),
        Mutation("M08", "behavior", "过期门票没有归零", f"{q} = {q} - {q};", f"{q} = {q} - 1;"),
        Mutation("M09", "behavior", "初始质量增长翻倍", f"{q} = {q} + 1;", f"{q} = {q} + 2;"),
        Mutation("M10", "behavior", "过期额外降质变为增质", f"{q} = {q} - 1;", f"{q} = {q} + 1;", 2),
        Mutation("M11", "behavior", "传说物品质量豁免名称拼错", legend, 'items[i].name != "Sulfuras typo"'),
        Mutation("M12", "behavior", "传说物品销售日也递减", legend, "true", 2),
        Mutation("M13", "behavior", "过期奶酪错误地停在49", f"{q} < 50", f"{q} < 49", 4),
        Mutation("M14", "behavior", "门票类型判断取反", 'items[i].name == "Backstage passes to a TAFKAL80ETC concert"',
                 'items[i].name != "Backstage passes to a TAFKAL80ETC concert"'),
        Mutation("M15", "behavior", "商品分类与运算改为或", '"Aged Brie" &&', '"Aged Brie" ||'),
        Mutation("M16", "behavior", "过期质量为1时漏降质", f"{q} > 0", f"{q} > 1", 2),
        Mutation("M17", "behavior", "十天内门票额外多加一", f"{q} = {q} + 1;", f"{q} = {q} + 2;", 2),
        Mutation("M18", "behavior", "五天内门票上限错误", f"{q} < 50", f"{q} < 49", 3),
        Mutation("M19", "behavior", "过期奶酪分支反转", 'if (items[i].name != "Aged Brie")', 'if (items[i].name == "Aged Brie")'),
        Mutation("M20", "behavior", "普通商品低质量漏降质", f"{q} > 0", f"{q} > 2"),
        Mutation("E01", "compile", "语法错误：缺少分号", f"{q} = {q} - 1;", f"{q} = {q} - 1"),
        Mutation("E02", "compile", "成员错误：不存在的字段", f"{q} = {q} - 1;", "items[i].missing_quality = 0;"),
        Mutation("E03", "compile", "类型错误：字符串赋给整数", f"{q} = {q} - 1;", f'{q} = "broken";'),
        Mutation("E04", "compile", "头文件错误：不存在的 include", '#include "GildedRose.h"', '#include "Missing_GildedRose.h"'),
        Mutation("E05", "compile", "返回类型错误：void 返回整数", "void GildedRose::updateQuality() \n{", "void GildedRose::updateQuality() \n{\n    return 42;"),
        Mutation("E06", "link", "链接错误：缺少函数实现", "using namespace std;", "using namespace std;\nextern void missing_hook();\nstruct Hook { Hook() { missing_hook(); } };\nHook hook;"),
        Mutation("C01", "equivalent_control", "等价对照：后置递增改前置递增", "i++", "++i"),
        Mutation("C02", "equivalent_control", "等价对照：自身相减改零", f"{q} = {q} - {q};", f"{q} = 0;"),
    ]


def manifest():
    return [asdict(m) for m in catalogue()]
