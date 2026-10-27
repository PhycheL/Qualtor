# humaneval-x-cpp-07 隐藏材料

- 被测代码：HumanEval-X C++ 的 8 道题（CPP/49, CPP/50, CPP/51, CPP/52, CPP/53, CPP/54, CPP/55, CPP/56），每题一个源文件，内容为上游 prompt + canonical_solution。
- 参考测试：`upstream_tests.cc` 由上游 test 字段机械转换；`characterization_tests.cc` 为生成器记录的每个函数前 12 个输入的实际结果。
- 探针（探针由生成器在原代码上运行大量输入得到，并包含全部参考测试；探针也区分不出的变异列为等价候选。）：`tests/` 下为参考测试副本与 `probe_tests.cc`；各函数保留的输入数：{"modp": 60, "encode_shift": 60, "decode_shift": 60, "remove_vowels": 60, "below_threshold": 60, "add": 60, "same_chars": 60, "fib": 32, "correct_bracketing": 60}。
- 生成器：`equivalence_probe/generate_probe.cc` 与 `probe_prelude.h`。输入取自上游测试与题面中的字面值及其扰动；每个输入在子进程中执行，用 ASan、UBSan 与 libc++ 断言过滤未定义行为、崩溃、超时和超过 20 毫秒的输入；带 ASan 与不带 ASan 两种构建、不同栈与堆填充共跑 4 遍，只保留每遍都正常结束且结果相同的输入（读未初始化变量的输入在不同栈布局下结果不同而被淘汰）；再用 GCC 14 + libstdc++ 回放，删去结果不一致的断言。
- 重建：重新运行 `benchmark/tools/import_humaneval_x.py --force`；修改后要重新标定变异分母。
