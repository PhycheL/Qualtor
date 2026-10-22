# GildedRose Docker 自动化实验

在 Docker 中使用 Python 标准库驱动 CMake、GCC、CTest 和 gcov，测试代码通过宿主机只读 bind mount 引入。镜像只安装工具链，Dockerfile 没有 `COPY` / `ADD` 仓库代码的步骤。

[详尽执行报告](deliverables/执行报告.md) · [全量过程索引](deliverables/全量执行过程.md) · [仅保留 cpp 后的实测结果](runs/cpp-only-20261021/summary.json)

上游源码仅保留 [`cpp/` 文件夹](external/GildedRose-Refactoring-Kata/cpp/)，其余语言目录已移除。业务测试目标是 `cpp/src/GildedRose.cc`；上游的 `.cc` 同样是 C++。从最初实验起就只编译这一 C++ 版本，详见本轮 [实际编译范围](runs/cpp-only-20261021/source_scope.json)。

13,965 指同一份 C++ 实现的输入组合记录：5条冒烟 + 1,440条边界 + 11,520条有界穷举 + 1,000条固定随机输入。它不是文件数，也不是所有语言的测试总数；互异输入为13,187个。清理其他语言目录后，这个 C++ 测试矩阵保持不变。

运行前需要 Docker 已启动、宿主机 Python 3.9+ 和 Git。首次构建需要联网；实验容器本身禁网。宿主机为 macOS / Linux，Windows 可在 WSL 中使用。实际验证平台是 macOS ARM64 + Docker Linux ARM64。

在当前项目根目录执行：

```bash
python3 gildedrose-lab/run.py
```

工具链镜像已存在时：

```bash
python3 gildedrose-lab/run.py --skip-build
```

每次自动生成不同的运行目录，不覆盖历史证据。也可传 `--run-id my-experiment`，但该 ID 对应的产物目录必须不存在。全新目录会克隆仓库、固定提交，并仅检出 `cpp/`；已有仓库若有改动或提交不匹配，脚本会停止并保留它。脚本创建本任务独立的 Docker 客户端配置，保留插件路径，不改用户的 Docker 配置。

交付 ZIP 仅包含上游 `cpp/` 的20个文件及 `external/source_manifest.json` 提交/文件哈希清单，不包含 `.git` 或其他语言源码。解压后入口可使用无 Git 元数据的快照，编译前后核对完整文件清单和哈希。本机隐藏 `.git` 仅用于 Git 溯源；许可证和需求说明保存在 `notes/upstream/`。

流水线依次生成 13,965 个测试用例和 CMake 包装项目，编译原始代码、运行 CTest、核对 gcov 文本与 JSON、构建并测试 28 个独立变异，再编译复杂分支题目并核对已冻结的模型答案。结果写入 `runs/<run-id>/summary.json`，宿主机命令写入 `artifacts/host/`。

模型答案来自 2026-10-21 当前对话模型的单次盲测，记录在 `benchmark/predictions.json`。重跑自动化只重放这份冻结答案，**不会发起新的大模型调用**。如需新一轮模型评测，须在新的题目目录生成题目、先让待测模型提交答案并冻结哈希，再运行评分；不能查看标准答案后修改原答案。

| 路径 | 内容 |
|---|---|
| `docker/` | 仅 Dockerfile 与构建上下文过滤规则 |
| `external/GildedRose-Refactoring-Kata/cpp/` | 宿主机上游 C++ 源码与构建配置，仅保留此目录 |
| `external/source_manifest.json` | 固定上游提交、cpp范围与20个文件的 SHA-256 |
| `scripts/` | Python 调度、记录、oracle、覆盖解析、变异与评分 |
| `templates/` | 自动生成项目所用 CMake 与 C++ 探针模板 |
| `benchmark/` | 题目、协议、预测、冻结时间及哈希 |
| `runs/cpp-only-20261021/` | 仅保留 cpp 后的最新成功复跑，含实际编译范围证明 |
| `runs/verified-20261021/` | 上一轮成功 C++ 实验的完整历史证据 |
| `runs/acceptance-20261021/` | 首次执行的原始失败证据，不作为成功结果 |
| `artifacts/` | 下载与构建日志、容器/镜像元数据、环境证据 |
| `deliverables/` | 报告、过程索引、变异明细、文件哈希清单 |

gcov 百分比只统计目标源码，不把 C++ 标准库混入业务覆盖率。20 个行为 Bug 的检出率和 6 个构建错误的捕获率分别计算；2 个等价改动是对照。上游尚未实现的 Conjured 需求用独立探针记录，不混入注入 Bug 的分母。

正常结果是 `status: passed`。原有 GoogleTest/Catch2 单测中的 `fixme` 占位断言不在本实验的通过声明范围内；包装项目关闭四个外部测试框架选项，复用上游 CMake 库和文本测试，再增加本实验的断言测试，因而实验容器无需下载依赖。
