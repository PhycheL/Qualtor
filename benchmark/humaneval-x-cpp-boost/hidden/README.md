# humaneval-x-cpp-boost

源码为 HumanEval-X CPP/22, CPP/137 的 prompt + canonical_solution 原样拼接；
函数声明头由导入工具生成。参考测试机械转换上游 assert，并加入 step_c 中的边界测试；探针为参考副本。
CPP/137 只以 int、有限 double、可转换为有限实数的 string 调用；不支持类型和 NaN 会触发原程序未定义行为，
不作为参考输入。变异的等价与 UB 仍须逐项按 D015 复核。编译和测试仅在 Docker 标定时验证。
