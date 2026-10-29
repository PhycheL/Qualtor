目标为 core.h、checked.h、unchecked.h；cpp11.h 及其他头只作依赖。
公开自由函数模板 append、append16、replace_invalid、next、next16、peek_next、prior、advance、distance、utf16to8、utf8to16、utf32to8、utf8to32 由上游 API 与 CPP11 测试实例化（checked/unchecked 有对应 API 时分别覆盖）。两类 iterator 的全部有定义成员另以 std::string::iterator 显式实例化。core.h 中公开验证入口 find_invalid/is_valid/starts_with_bom 由上游调用；内部 helper 经公共调用实例化。
不纳入 C++17/C++20 专属重载（预处理排除）、以及没有公开入口触发的其他内部模板类型组合；每个模板定义按源码位置合并而非按类型累计。异常类的 what 与载荷访问器由补充测试覆盖。
