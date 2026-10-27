# humaneval-x-cpp-19 隐藏材料

- 被测代码：HumanEval-X C++ 的 8 道题（CPP/146, CPP/147, CPP/148, CPP/149, CPP/150, CPP/151, CPP/152, CPP/153），每题一个源文件，内容为上游 prompt + canonical_solution。
- 参考测试：`upstream_tests.cc` 由上游 test 字段机械转换；`characterization_tests.cc` 为生成器记录的每个函数前 12 个输入的实际结果。
- 探针（探针由生成器在原代码上运行大量输入得到，并包含全部参考测试；探针也区分不出的变异列为等价候选。）：`tests/` 下为参考测试副本与 `probe_tests.cc`；各函数保留的输入数：{"specialFilter": 60, "get_matrix_triples": 60, "bf": 60, "sorted_list_sum": 60, "x_or_y": 60, "double_the_difference": 60, "compare": 60, "Strongest_Extension": 60}。
- 生成器：`equivalence_probe/generate_probe.cc` 与 `probe_prelude.h`。输入取自上游测试与题面中的字面值及其扰动；每个输入在子进程中执行，用 ASan、UBSan 与 libc++ 断言过滤未定义行为、崩溃、超时和超过 20 毫秒的输入；带 ASan 与不带 ASan 两种构建、不同栈与堆填充共跑 4 遍，只保留每遍都正常结束且结果相同的输入（读未初始化变量的输入在不同栈布局下结果不同而被淘汰）；再用 GCC 14 + libstdc++ 回放，删去结果不一致的断言。
- 重建：重新运行 `benchmark/tools/import_humaneval_x.py --force`；修改后要重新标定变异分母。
