上游参考测试调用公开 API。类模板以 int 实例化全部有定义的公开成员，coverage_instantiation/api.cc 只在准备阶段编译、不执行；具体冻结行和函数见 coverage_baseline.json。
Node 默认构造器的内置 data 未初始化，上游 erase 对不存在元素可能读取 sentinel.data；本题不通过这种未定义行为检出手写变异，erase 变异只使用存在元素的用例。
