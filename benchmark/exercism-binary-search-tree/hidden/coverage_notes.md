上游参考测试调用公开 API。类模板以 int 实例化全部有定义的公开成员，coverage_instantiation/api.cc 只在准备阶段编译、不执行；具体冻结行和函数见 coverage_baseline.json。
不进入分母的声明：copy_branch_iter 只有私有声明，没有函数定义；显式删除的复制/移动成员无可执行实现；默认析构/移动操作仅在 GCC 产生覆盖率记录时纳入。
