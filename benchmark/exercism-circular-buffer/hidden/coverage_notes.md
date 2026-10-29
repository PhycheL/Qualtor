上游参考测试调用公开 API。类模板以 int 实例化全部有定义的公开成员，coverage_instantiation/api.cc 只在准备阶段编译、不执行；具体冻结行和函数见 coverage_baseline.json。
没有遗漏的公开成员；隐式析构由 GCC 实际产生的记录决定。
