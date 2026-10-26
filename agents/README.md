# Qualtor 测试生成产品

整个目录可以独立交付。pi 在宿主机生成 C++11 / GoogleTest 测试，通过 Docker 编译、运行并读取反馈，自行修复后输出测试快照。产品不依赖 Qualtor 的评测器、题库或 Git 仓库。

## 安装

宿主机需要 Python 3.9+、Node 23.6+、npm 和 Docker；推荐 Node 24 或更新版本。当前验证环境为 macOS ARM64、Node 26.12.0 与 Linux ARM64 Docker。安装时需要联网；生成时需要模型 API，编译容器禁网。

在此目录执行：

```bash
python3 setup.py
cp .env.example .env
chmod 600 .env
```

填写 `.env` 的 API 地址与密钥；已有配置时直接编辑，不要再次复制覆盖。模型设置在 `configs/default/config.json`。入口默认从本产品目录读取 `.env`，也可用 `--env-file /path/to/connection.env` 指定，不需要 `export`。

`setup.py --pi-only` 只安装、构建宿主机 pi，`--gcc-only` 只构建 GCC 镜像。源码、固定依赖锁和模型目录保留在 `pi/`。换操作系统、架构或 Node 版本后重新运行安装；安装器会检查缓存的搜索工具，不能在当前宿主机执行时重新获取。安装日志默认保存在 `output/setup-<时间>/`。

## 公开任务和生成

准备任务文件，例如 `/path/to/task.json`：

```json
{
  "id": "my-project",
  "title": "为已有代码生成单元测试",
  "source_root": "my-project",
  "target_sources": ["src/calculator.cc"],
  "include_dirs": ["src"],
  "visible_files": ["src/calculator.cc", "src/calculator.h"],
  "allowed_test_files": ["tests/*.cc", "tests/*.h"],
  "budget": {"repair_rounds": 3},
  "test_timeout_seconds": 5
}
```

`source_root` 相对于任务文件，也可使用绝对路径；其他文件路径相对于源码目录。目标源文件必须出现在可见文件清单中。当前接入 C++11 源码、头文件和 GoogleTest，不支持任意项目的自定义构建步骤、额外链接库或多语言测试。

```bash
python3 run.py --task /path/to/task.json --output /path/to/new-result --config default
```

输出目录必须尚不存在。Agent 仅修改 `tests/` 中允许的文件。每次编译前保存本轮测试快照、记录文件哈希，并将快照与可见源码只读挂入 Docker。第 1 次快照同时保存在 `first/`，随后最多消耗 3 轮修复；完整反馈文件的位置返回给 Agent，Agent 结束时另存最终测试快照到 `final/`。从未编译时，首次和最终快照都取结束时的测试。API 或进程错误最多重新生成两次，每次使用空工作区，所有重试成本都会计入。

```text
new-result/
├── first/tests/                # 首次测试快照，通常取首次编译前的测试
├── final/tests/                # 最终测试快照，可交付或继续独立评分
├── first/manifest.json         # 首次文件哈希；final/ 同样包含清单
├── workspace/                  # 可见源码、测试和可读取的反馈
├── attempts/                   # 每次编译的只读快照、完整日志和测试报告
├── generation-attempts/        # 包含错误重试的原始生成记录
├── logs/                       # pi 事件、原始会话和监督日志
├── result.json                 # 生成状态、编译次数、重试和成本摘要
└── cost.json                   # 首次/最终成本，包含错误重试消耗
```

`finished` 表示 Agent 正常结束，测试是否通过应查看 `attempts/*/result.json`；未编译时记为 `never_built`。修复预算用完、无响应和基础设施错误分别单列。未配置单价时 USD 为 `null`，token、调用次数、时间和修复轮次仍会记录。

Ctrl+C 或 SIGTERM 会停止生成、回收 pi 和正在执行的编译容器，保存已有测试、日志及已记录的成本，状态为 `cancelled`，不重新生成。CLI 分别返回 130 或 143。

详细字段、结束状态和隔离保证见 [接口与运行边界](docs/接口与运行边界.md)。产品只生成和验证测试；测试质量评分由独立评测系统完成。

工具的注册与调用时机、宿主机编译服务和反馈流程见 [编译工具与调用流程](docs/接口与运行边界.md#编译工具与调用流程)。
