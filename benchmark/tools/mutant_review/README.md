# 变异复核结论

本目录按题目 ID 保存变异复核中已核实的结论，是建题工具的输入。内容属于隐藏材料，不能放进任何题目的可见文件。

| 文件 | 内容 | 使用方式 |
|---|---|---|
| `review_tests.cc` | 复核补充测试：用来区分等价候选的反例 | `bankutil.copy_reference_as_probe` 在建题时把它并入参考测试，随参考测试进入探针 |
| `confirmed.json` | 影响分母的复核结论，含 ID、判定和证据：`non_equivalent_verified` 为真实 Mull 反例检出；`undefined_only` 为只在未定义行为下与原代码不同（D015，原名 `non_equivalent_undefined_verified`） | `prepare_new_tasks.py` 写入分母前、`apply_review.py` 修订或核对已有分母时落实：前者从等价候选移回分母，后者从等价候选或分母移入不稳定；随后重算参考 M1 |
| `equivalent.json` | 等价候选的结论：为什么在原代码全部有定义的输入上不可区分（D011），或差异只在资源耗尽时出现（D015），附证据和结论人 | 不改变分母；`admit.py` 签署准入前核对分母中的每个等价候选都在这里有结论 |

编写补充测试的要求：

- 只断言原代码在有定义输入上的实际结果（D001），不依赖未定义行为、内存布局或架构。
- 与执行顺序无关。评测会重复、乱序并逐个单独运行测试；被测代码有进程级状态时（如 Robot Name 的名字计数器），从观察到的状态推出期望值。
- 测试套件名用 `Review`、`ReviewExtra` 或 `ReviewSource`，不与上游测试、生成的测试重名。
- 修改后用对应的导入脚本加 `--force` 重建题目。材料变化的题，原分母作废，需要在 Docker 中重新标定。

2026-10-27 首批内容的来源是逐项复核 `runs/bank-review-20261027-03/` 和冻结反例 `runs/eval-bank-followup-20261027-01/review-products*/`：

- `Review`、`ReviewExtra`：36 道题的 40 份冻结反例原样合并；Robot Name 的反例原先假定进程内第一个名字是 `AA000`，改为从观察到的名字推出后续序列。
- `ReviewSource`：26 项“源码非等价”判断中，按复核说明给出的输入为 20 项补写了反例，尚待 Docker 中的真实 Mull 核对。在本机源码副本上抽查，检出 19 项；Rail Fence 第 14 行的变异只在字符串末尾之外越界写，未检出。依赖越界读写或 ARM64 除零的 3 项、实际等价的 1 项（第 02 组 int 版 `rolling_max`）没有补写；Queen Attack 的 2 项由全棋盘反例覆盖。
- `confirmed.json`：37 道题共 121 项，其中真实 Mull 反例检出 111 项、sanitizer 证实 UB 10 项，与复核的分母修订草稿一致。

2026-10-28 已完成 Linux ARM64 Docker 重标定：40/40 题通过，111 个历史真实 Mull 确认项在合并测试中全部 Killed；20 项 ReviewSource 正式为 18 Killed、1 Timeout、1 Survived。`confirmed.json` 仍为原 37 题 121 项，本轮没有扩展注册或签署范围。详见[题库验证说明](../../../docs/题库验证说明.md)第 9 节及[逐项结果](../../../runs/eval-bank-strengthening-20261028-01/reviewsource.md)。

2026-10-28 第二批（本机完成，待 Docker 标定）：原 110 个未决候选与 26 项源码判断全部给出结论。
- `equivalent.json`：共 262 项，其中 Codex 183 项，Claude 79 项（含 Zebra 33 项）；
- `undefined_only`：共 45 项，含原 10 项改判；
- 第 07、10、15、16、18 组为“长度换成 42”的变异补长输入测试，第 03 组补 ±0 测试，这 6 道题需重新标定。

依据与证据见[题库验证说明](../../../docs/题库验证说明.md)第 10 节。

