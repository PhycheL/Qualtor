# Qualtor 文档索引

从 [根 README](../README.md)了解整体流程、主要目录和评测指标，再按需要阅读下表。当前实现与验证范围分别由设计、运行说明维护；历史记录不作为当前待办。

| 用途 | 文档 |
|---|---|
| 独立使用生成产品：安装、连接配置、公开任务、输出与结束状态 | [产品 README](../agents/README.md) |
| 产品实现契约：工具调用、测试快照、Docker 反馈和隔离边界 | [接口与运行边界](接口与运行边界.md) |
| 批量生成与独立评测：配置、trial、取消、成本、框架验收及证据 | [生成入口运行说明](生成入口运行说明.md) |
| 评测对象、术语、方法、指标、实现状态与后续工作 | [评测规格](评测规格.md) |
| 状态判定、指标公式、汇总与版本比较 | [评分算法](评分算法.md) |
| assessment 的结构、阶段执行、题目包与校准样本 | [评测模块与校准样本设计](评测模块与校准样本设计.md) |
| 题库建设：规模与难度分层、必须补齐的构建能力、材料来源、已建题目、单题流程与分阶段计划 | [题库构建方案](题库构建方案.md) |
| 题库 Docker 标定、真实模型验收、变异复核与准入；步骤 A/B、115 题、CAL-18–29、0.4.1 收尾补评与正式 runner 证据 | [题库验证说明](题库验证说明.md) |
| 步骤 B 的历史执行计划：D018 草案、B0–B6、12 道新题与交付清单；已完成 0.4.1 收尾，修订标准和结果见验证说明第 15 节 | [步骤 B 执行计划](步骤B执行计划.md) |
| 步骤 C（R-01 构建环境与第三方库、R-04 代码生成）的决定、配方、实施顺序、新题、校准样本与验收清单（已定稿，实施中） | [步骤 C 执行计划](步骤C执行计划.md) |
| 变异分母标定、校准、单份评测、补评与汇总命令 | [评测运行说明](评测运行说明.md) |
| GCC/gcov/GoogleTest 和 Clang/Mull 的固定版本、构建与验收、Docker Desktop 休眠时镜像名称排障 | [C++11 固定工具链](C++11固定工具链.md) |
| 设计决定及替代范围（D015 变异口径、D016 准入、D017 构建契约、D018 头文件与零变异、D019 Clang 测试编译失败） | [决策记录](决策记录.md) |
| 历次研发过程、失败与验证结果 | [研发日志](研发日志.md) |
| 开发 Agent 的按任务阅读入口、实施规则和完成标准 | [AGENTS.md](../AGENTS.md) |

校准[状态](../evaluator/assessment/calibration-status.json)和[报告](../evaluator/assessment/calibration_report.md)随评测模块入库；原始执行证据位于不入 Git 的 `runs/`，具体位置见两份运行说明。历史命令与日志保留执行时的名称和路径。

上游[需求说明](../benchmark/gildedrose-update-quality/source/GildedRoseRequirements.md)、[许可证](../benchmark/gildedrose-update-quality/source/license.txt)、[C++ 说明](../benchmark/gildedrose-update-quality/source/cpp/README.md)和来源记录随源码保留；[替换版本说明](../benchmark/gildedrose-update-quality/hidden/variants/README.md)、[解析夹具来源](../evaluator/assessment/tests/fixtures/README.md)随数据保留。这些文件用于复现与追溯，不按普通知识文档清理。
