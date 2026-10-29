目标仅 detail/conversions/to_chars.hpp；可见的完整 include 树满足 json.hpp 测试依赖，其他头不计覆盖。
公开入口 to_chars<FloatType> 和内部 grisu2<FloatType>/compute_boundaries<FloatType> 以 IEEE-754 float/double 实例化，复用上游单精度、双精度和格式化测试。没有类模板公开成员遗漏；long double 不属于该实现接受的 IEEE-754 32/64 位类型，故不实例化。内部 reinterpret_bits 的实际类型组合来自这两类入口，分母按源码位置合并。
