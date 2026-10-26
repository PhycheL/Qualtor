# Qualtor

为已有 C++11 项目自动生成 GoogleTest 测试，并通过独立评测改进 Agent。产品负责“生成 → 编译反馈 → 修复 → 冻结”，评测负责“选题 → 多次运行产品 → 独立评分 → 汇总”。断言以被测代码的实际行为为准。

**交付给用户的是整个 `agents/` 目录。pi 在宿主机运行，生成的测试在 Docker 中编译、执行；`evaluator/` 负责评价这些测试。** 产品不依赖本仓库的评测器、题库或 `.git/`。使用方法见 [产品说明](agents/README.md)，完整项目文档见 [文档索引](docs/README.md)。

```text
Qualtor/
├── agents/        # 可独立交付的单元测试生成产品
├── evaluator/     # 评测调度、评分器及评分工具链
├── benchmark/     # 题目定义、被测源码与隐藏评分材料
├── runs/          # 研发和评测证据：产物、日志、成本与评分，不入 Git
├── docs/          # 项目设计、决策、规则和研发记录
├── AGENTS.md      # 维护本项目的开发 Agent 的协作入口
└── .gitignore     # 本机凭证、依赖与运行产物的忽略规则
```

[agents/](agents/) 包含用户实际使用的全部生成能力。Python 启动宿主机 pi，提供受限文件工具和 `build_and_test`，管理修复预算、失败重试、看门狗、日志与成本。用户自己的源码通过公开任务文件指定。

```text
agents/
├── run.py                     # 产品入口：公开任务 → 冻结测试、日志和成本
├── setup.py                   # 安装宿主机 pi 依赖、构建 GCC 镜像
├── generator/                 # 生成、编译反馈、修复、冻结及错误重试
│   ├── runtime/               # 宿主机 pi 监督程序、工具门卫和编译工具扩展
│   └── build/                 # 每轮快照、Docker 编译服务和 GoogleTest 结果解析
├── common/                    # 产品自己的命令审计，不从评测目录取代码
├── toolchains/                # 产品所需的 GCC / GoogleTest 固定工具链
│   ├── docker/                # GCC 镜像定义和独立构建上下文
│   ├── cmake/                 # 普通 C++11 编译模板，不做覆盖率或变异分析
│   └── images.json            # 固定 GCC 镜像标签
├── configs/<name>/            # 可选择的模型配置
│   └── config.json            # provider、模型、思考级别、兼容参数和可选单价
├── pi/                        # pi 上游源码、来源记录、锁文件及构建产物
│   ├── packages/
│   │   ├── coding-agent/      # CLI、文件工具、会话和扩展机制
│   │   ├── agent/             # 对话、模型调用与工具执行循环
│   │   └── ai/                # provider、流式响应、用量与费用
│   ├── scripts/               # pi 自身的构建和检查脚本
│   ├── docs/                  # 随 pi 保留的上游说明
│   └── nix/                   # 构建材料及固定的模型目录版本
├── tests/                     # 产品的配置、成本、门卫、反馈和看门狗回归测试
├── docs/                      # 随产品交付的接口与运行边界说明
├── .env                       # 本机模型连接地址和密钥，不入 Git
├── .env.example               # 用户填写连接配置的示例
├── .gitignore                 # 随产品交付的凭证、依赖和产物忽略规则
├── .cache/                    # 安装缓存和宿主机搜索工具，不入 Git
└── output/                    # 独立安装时的默认证据目录，不入 Git
```

`pi/node_modules/`、`pi/**/dist/` 和 `pi/.qualtor-build.json` 由宿主机安装产生，不入 Git；换操作系统、架构或 Node 版本后重新执行 `setup.py`。模型密钥只提供给宿主机 pi，编译容器不接收密钥。

[evaluator/](evaluator/) 通过产品的公开 CLI 组织实验，然后独立评分。多题调度、K 次 trial、并发、校准门禁、评分重试和比较汇总属于评测。

```text
evaluator/
├── run.py                     # 评测入口：选题、多次生成、独立评分及汇总
├── runner/                    # 调用 agents/run.py，连接题目与评分器
│   └── tests/                 # 调度、故障取消、校准门禁及补评回归测试
├── common/                    # 评测路径、run 记录、审计、覆盖率解析和源码校验
├── toolchains/                # 两套 C++ 工具链的统一构建与验收入口
│   ├── docker/                # 评分专用 Clang/Mull 镜像定义
│   └── smoke/                 # 手写冒烟测试：检查编译、执行、gcov 和 Mull
└── scorer/                    # 独立评分、分母标定、校准、补评和比较
    ├── cmake/                 # GCC 覆盖率、Clang/Mull 和替换版本的评分构建模板
    ├── calibration/           # 检查评分器判定是否正确的已知样本
    │   └── <task-id>/CAL-XX/
    │       ├── final/tests/   # 待评分的样本测试
    │       ├── generation/    # 样本成本输入
    │       └── expected.json  # 预期判定和指标要求
    └── tests/                 # 评分规则与接线的回归测试
        └── fixtures/          # GoogleTest、gcov、Mull 的固定输出样本
```

GCC 镜像由 `agents/toolchains/` 定义，生成和评分可复用同一镜像，但分别创建容器和构建目录；Clang/Mull 只用于评分。**当前链路不使用 pi 生成镜像。** C++ 执行容器禁网，源码和测试快照只读挂载。评分不会把覆盖率、变异结果或参考测试反馈给正在生成的 Agent。

[benchmark/](benchmark/) 按“一道题一个目录”组织，当前只有 GildedRose 开发题。`task.json` 的 `set` 区分开发集与验收集；评测入口从完整题目中提取公开任务，产品只收到可见文件清单和生成参数。

```text
benchmark/
└── gildedrose-update-quality/
    ├── task.json                   # 源码、可见材料、预算及评分参数
    ├── source/                     # 上游源码快照、来源哈希、需求说明和许可证
    │   └── cpp/
    │       ├── src/                # 被测业务实现与头文件
    │       └── test/               # 上游测试示例，当前不提供给生成 Agent
    └── hidden/                     # 只供题目准备和独立评分使用
        ├── reference_tests/        # 参考强测试，验证题目与标定分母
        ├── equivalence_probe/     # 有界穷举探针及其生成程序
        │   └── tests/              # 生成后的探针测试
        ├── variants/               # 替换源码及差分检查程序
        │   ├── eq-02/              # 等价重构，用于测误报
        │   └── hw-01/              # 手写行为变异，用于测缺陷检出
        └── mutation_baseline.json  # 冻结变异集合及排除、复核记录
```

[runs/](runs/) 保存实验记录。一个评测 run 可包含多题、每题多个独立 trial。产品单独使用时通过 `--output` 指定任意新目录，不要求存在 `runs/`。

```text
runs/<run-id>/
├── run.json                             # 配置、版本、类型、时间和状态
├── evidence/                            # 宿主机命令、工具链及容器审计
├── trials/<task-id>/
│   ├── trial-<k>-request/                # 公开任务和产品调用日志
│   └── trial-<k>/                       # 产品输出，再附加评分
│       ├── generation-attempts/         # 整次生成重试，每次使用空工作区
│       │   └── attempt-<n>/             # 原始生成日志、快照和成本
│       ├── workspace/                  # 宿主机上的生成工作区
│       │   ├── project/                # 允许可见的源码副本，工具只读
│       │   ├── tests/                  # Agent 允许修改的测试
│       │   ├── feedback/               # Agent 可读的完整编译日志与报告
│       │   └── TASK.md                 # 根据公开任务生成的说明
│       ├── attempts/attempt-<n>/       # 一次 build_and_test 的记录
│       │   ├── product/tests/          # 编译前冻结、只读挂入 Docker 的快照
│       │   ├── output/                 # 编译/测试日志、退出码和测试报告
│       │   └── docker/                 # 编译容器创建、运行、清理日志
│       ├── first/                      # 首次冻结测试与 manifest.json
│       ├── final/                      # 最终冻结测试与 manifest.json
│       ├── logs/                       # pi 事件和宿主机监督日志
│       │   └── sessions/               # 成本提取所用的原始会话
│       ├── pi-state/                   # 该次生成独立的 pi 状态
│       ├── result.json                 # 产品的生成状态、重试和成本摘要
│       ├── trial.json                  # 评测追加的生成与评分摘要
│       ├── cost*.json                  # 首次、最终和重试消耗
│       └── score/<scorer-version>/     # 按评分器版本保留独立结果
│           ├── first/                  # 首次评分和各评分阶段证据
│           ├── final/                  # 最终评分，内部结构与 first/ 相同
│           ├── infra-retries/          # 评分重试的失败记录，按需出现
│           └── incomplete/             # 补评前移出的不完整结果，按需出现
├── score/<scorer-version>/              # 新评分版本的补评审计，按需出现
└── summary.json                         # 整轮评测汇总
```

`generation-attempts/` 是“整次生成重跑”，`attempts/` 是“一次生成中的编译验证”。最后一次生成结果复制到 trial 根目录，原始尝试保留。评分检查冻结文件哈希；升级评分器增加版本目录，保留原有产物和旧评分。

宿主机 pi 的限制来自工具白名单、路径检查和写入规则，**不提供针对恶意 pi 进程的操作系统沙箱**。生成的 C++ 由 Docker 隔离，源码和测试只读，编译日志位于测试进程无法写入的私有目录。具体保证见 [产品接口与边界](agents/docs/接口与运行边界.md)。

常用入口：

- [产品说明](agents/README.md)：独立安装、配置和生成命令。
- [生成入口运行说明](docs/生成入口运行说明.md)：批量评测、失败路径、成本和验证证据。
- [评分器运行说明](docs/评分器运行说明.md)：校准、评分、补评和汇总。
- [生成入口与受限工作区设计](docs/生成入口与受限工作区设计.md)：产品和评测的职责划分。
- [项目推进流程](docs/项目推进流程.md)：当前阶段及后续工作。
