目标为 core.h、checked.h、unchecked.h；cpp11.h 及其他头只作依赖。
上游 API 与 CPP11 测试实例化 append、append16、next、next16、peek_next、prior、advance、distance、utf16to8、utf8to16、utf32to8、utf8to32 以及 checked::replace_invalid。两类 iterator 的全部有定义成员另以 std::string::iterator 显式实例化。core.h 中公开验证入口 find_invalid/is_valid/starts_with_bom 由上游调用；内部 helper 经公共调用实例化。

0.4.0 的 unchecked::replace_invalid 说明不准确。0.4.1 在 coverage_instantiation/api.cc 加入两种 string 调用，连带实例化迭代器重载，逐项纳入：

| unchecked.h 定义位置 | 函数 | 分母来源 |
|---|---|---|
| 50 | replace_invalid(start,end,out,replacement) | 原已冻结；string 的四参数委托调用 |
| 83 | replace_invalid(start,end,out) | 默认替换字符的委托调用 |
| 89 | replace_invalid(const string&,replacement) | 准备阶段显式调用 |
| 96 | replace_invalid(const string&) | 准备阶段显式调用 |

这些调用仅编译、不执行，新增行在参考测试未执行时仍留在分母，不能算已覆盖。三个被测头内没有另行排除的有定义公开函数；cpp17.h/cpp20.h 不属于被测文件，不是分母内函数的例外。每个模板定义按源码位置合并而非按无限类型组合累计。异常类的 what 与载荷访问器由补充测试覆盖。
