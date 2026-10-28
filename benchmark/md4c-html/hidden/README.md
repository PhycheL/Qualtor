# md4c HTML 渲染

源码取 release-0.4.8 `c3340b480e5232711858108be07460a9836c8ab5`，原文件未改。被测 `src/md4c-html.c`；解析器与实体表为依赖源文件。
参考测试由 11 份上游 `test/*.txt` 转为 770 个 GoogleTest 用例，保留全部输入及各扩展开关，测试许可证见 `TEST_LICENSE`。
上游比较归一化 HTML；本题按 D001 使用固定 GCC 原程序的逐字节输出，记录在 `benchmark/tools/step_a/md4c_actual.json`。全部 770 个输入保留，128 项输出格式差异证据见 `runs/step-a-md4c-capture-20261028-01/`。
探针为参考测试副本；测试未人工审阅，等价候选逐项复核。

复核补充测试：`step_a_boundaries.cc` 来自 `benchmark/tools/mutant_review/md4c-html/`，是变异复核中区分等价候选的反例，已并入参考测试与探针。
