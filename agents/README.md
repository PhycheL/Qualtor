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

GCC 镜像引用配置在 `toolchains/images.json`，使用完整名称 `docker.io/library/qualtor-gcc:14.2.0-gtest1.12.1-cxx11`；安装和生成共用该配置，查询后按返回的镜像 ID 创建编译容器。完整名称用于避开 Docker Desktop 休眠时短名称查询误报 `No such image` 的缓存路径；已有本地镜像可直接按完整名称查询，无需因此重新构建。

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

`source_root` 相对于任务文件，也可使用绝对路径；其他文件路径相对于源码目录。上述九个字段必填，另可添加可选字段 `build`、`target_headers`，未知字段仍拒绝；目标源文件必须出现在可见文件清单中，可见文件须为普通文件，禁止越界和符号链接。修复轮数为非负整数，单测超时为有限正数。支持 C/C++ 业务源码和 C++11 GoogleTest 测试；自定义构建步骤、额外链接库尚未接入。

`target_headers` 声明被测头文件（`.h`、`.hh`、`.hpp`、`.hxx`、`.inl`），必须可见、位于源码目录且不经过符号链接。纯头文件题用 `"target_sources": []` 与非空 `target_headers`；暂不支持同时指定被测源文件和被测头文件。两种被测文件均与依赖源文件互斥。纯头文件任务的 TASK.md 列出“被测头文件”，并说明被测代码全部位于其中；普通源文件任务的提示词保持不变。

可选构建配置示例（路径须同时加入 `visible_files`）：

```json
{"build": {"support_sources": ["src/helper.c"], "c_standard": "c11",
           "defines": ["FEATURE_ENABLED", "LIMIT=8"], "compile_options": ["-fno-strict-aliasing"]}}
```

`build` 只接受这四个子字段。三个列表缺省为空；依赖文件与被测文件互斥，参与编译链接。编译宏采用 `NAME` 或 `NAME=value`，值限单个标识符或数值，不接受字符串、路径或表达式；宏名称不能重复。宏名和标识符形式的宏值不得以 `__` 或下划线加大写字母开头，也不得为 C99/C11/C++11 关键字、替代记号或 `defined`。选项白名单为 `-fno-strict-aliasing`、`-fwrapv`、`-fsigned-char`、`-funsigned-char`，后两项不能同时使用。宏和选项作用于被测、依赖、测试全部编译单元。

源文件支持 `.c`、`.cc`、`.cpp`、`.cxx`。含 `.c` 时必须声明 `c99` 或 `c11`；C++ 固定为 C++11，C/C++ 均关闭语言扩展。C++11 断言头只作用于 C++。每次配置后核对并保留 `compile_commands.json`，确认语言标准、宏、选项和编译单元。

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

产品只生成和编译验证测试；测试质量由独立评测系统评价。查看最近一次 `attempts/*/result.json` 可确认编译和测试结果；如果 Agent 在该次编译后继续修改文件，最终快照可能尚未经过编译。未配置单价时 USD 为 `null`，token、调用次数、时间和修复轮次仍会记录。

## 工具与运行边界

`build_and_test` 是 TypeScript 扩展注册给 pi 的工具，由模型主动调用；Hook 负责启用、检查调用与记录事件。工具通过本地 Unix socket 请求宿主机 Python 编译服务，服务保存本轮测试快照、启动 GCC 容器、收集输出，再返回摘要、完整反馈文件路径和剩余修复轮次。预算用完后拒绝新的编译请求，等待 Agent 结束或触发无响应终止。

Agent 只有 `read`、`write`、`edit`、`grep`、`find`、`ls`、`build_and_test` 七个工具；文件工具仅访问本次工作区，只能写任务允许的测试文件，测试总量上限为 64 MiB。工作区含只读源码、任务说明、测试和只读反馈。pi 不自动加载宿主机的扩展、MCP、skill、上下文与提示词模板；凭证只传给选中的宿主机 pi，不进入编译容器或输出产物。连接文件按字面值读取，不执行 shell、不做变量插值，也不回退读取旧环境变量。

每次编译使用独立 GCC 容器，源码和测试快照只读挂载，禁网，限制 2 CPU、2 GiB 内存和 256 个进程。可信监督程序管理降权与日志，编译器和测试以非 root 身份执行。配置、编译分别限制 300、900 秒，单测使用任务超时，容器另有 1800 秒故障上限。完整反馈保存在文件中，返回的错误详情摘要最多 8000 字符，失败测试名单完整保留。

文件工具限制模型的读写操作；pi 本身以宿主机用户身份运行，不构成恶意 pi/扩展的操作系统沙箱。

## 结束状态与故障处理

| `result.json` 状态 | 含义与处理 |
|---|---|
| `finished` | Agent 正常结束；检查编译反馈与最终测试内容 |
| `budget_exhausted` | 首次编译及所有修复次数已用完；保留最终测试 |
| `never_built` | 未调用编译工具；输出测试尚未验证 |
| `generation_stalled` | 默认连续 900 秒无进展；保留已有测试，编译期间暂停看门狗 |
| `agent_error` | pi、API 或编译基础设施错误；默认最多三次完整生成尝试 |
| `cancelled` | 用户发送 SIGINT / SIGTERM；保留已有产物与已记录成本，不重试 |

编译错误和断言失败会反馈给 Agent 修复，不触发从头生成。`--attempts 1` 可关闭完整生成重试。CLI 正常结束返回 0，`agent_error` 返回 1，输入或启动检查失败返回 2；正常退出时仍需读取上述状态。

Ctrl+C 或 SIGTERM 会回收 pi 和正在执行的编译容器，保存已有测试、日志及已记录的成本，分别返回 130、143。强制 SIGKILL 或宿主机故障无法执行这条清理路径。根目录结果反映整个产品调用，`generation-attempts/` 中的原始记录保留每次监督进程结束时的状态。

`python3 run.py --describe --config default` 可查看接口版本、无密钥配置、产品指纹及 pi 安装记录；当前公开接口与结果的 `schema` 为 1。`--scenario` 是框架验收入口，使用真实 pi 的本地剧本 provider，不调用付费模型。
