# cpp-peglib-parser 隐藏材料

来源：https://github.com/yhirose/cpp-peglib，提交 `2d276c8cd9a64800587172b40b8cb74e273a4f88`。source/ 中业务文件未改动，保留许可证。
被测头文件：peglib.h。其余头文件只作可见依赖，不进入覆盖率分母。
参考测试从 test/test.cc 机械转换：utfcpp 只替换 ftest include；其他库沿用 Catch 断言兼容层，TEST_CASE 改为 GoogleTest，SECTION 独立作用域按顺序执行，CAPTURE 仅去除诊断输出。
手写变异源文件与说明：benchmark/tools/handwritten_variants/cpp-peglib-parser/；参考测试尚未人工审阅。
冻结范围及未实例化成员见 coverage_notes.md（若有）；缺陷、覆盖率和变异检出结论以 Docker 标定为准。
