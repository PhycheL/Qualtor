# 替换版本

| 版本 | 类型 | 期望 | 说明 |
|---|---|---|---|
| `eq-02` | 等价版本 | 测试应全部通过 | 按商品种类拆成独立函数的重构。除 `sellIn == INT_MIN` 外，对任意输入（含 0–50 以外的质量）与原代码行为完全一致；原代码在该输入上执行 `sellIn - 1` 会有符号溢出，属于未定义行为（D011） |
| `hw-01` | 手写变异 | 测试应失败 | 门票“5 天以内再加 1”的边界由 `sellIn < 6` 改成 `sellIn < 5` |

`eq-01`（把质量截断到 0–50）已按 D011 删除：它只在评分输入域内与原代码一致，会把断言域外真实行为的正确测试判为误报。

## 等价性检查

`differential_check.cc` 与一份 `GildedRose.cc` 一起编译，在固定输入网格上连续更新 3 天，输出结果数量和哈希。原代码与 `eq-02` 的两行输出必须完全相同。从仓库根目录执行：

```bash
docker run --rm --network none \
  -v "$PWD/benchmark/gildedrose-update-quality:/task:ro" \
  qualtor-gcc:14.2.0-gtest1.12.1-cxx11 sh -c '
for src in source/cpp/src hidden/variants/eq-02/cpp/src; do
  g++-14 -std=c++11 -O0 -I/task/source/cpp/src /task/hidden/variants/differential_check.cc "/task/$src/GildedRose.cc" -o /tmp/check
  echo "$src: $(/tmp/check)"
done'
```
