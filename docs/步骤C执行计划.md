# 步骤 C 执行计划：第三方库与代码生成（R-01、R-04）

> **已定稿，进入实施（2026-10-29）。** 基点为 `a273de2`（基点工作区干净）：评测模块 0.4.1，`step-b-closeout-calibration-20261029-01` 校准 passed，115 题准入有效。本文供执行方逐步实施，完成后交开发 Agent 按第 10 节验收。实施结果写入[题库验证说明](题库验证说明.md)新增的第 16 节和[研发日志](研发日志.md)，本文不追记执行结果。
>
> 依据：
> - [题库构建方案](题库构建方案.md)第 1.4、2、7 节（链接第三方库开发集至少 5 道、代码生成至少 3 道，现有均为 0）；
> - [决策记录](决策记录.md) D013、D017–D019；
> - 2026-10-29 对镜像与构建链路、依赖可行性和候选题的只读调研。依赖版本取自快照 `20261021T000000Z` 的软件包索引；候选题没有在 Docker 中编译过，变异数为估算。

## 0. 目标与完成标准

评测模块和独立产品要支持两项新能力：

- 题目可以链接锁定版本的第三方库（R-01），这些库装在叠加于固定工具链之上的“构建环境”镜像里，运行时仍然禁网；
- 题目可以在构建中运行白名单内的代码生成器（R-04）：moc 和 protoc；构建前只需生成一次的配置头，随源码入库。

在此基础上建成覆盖这两项能力的新题，把评测模块升到 0.5.0，并在 Linux ARM64 Docker 完成校准、标定、准入和正式路径验收。

全部满足以下条件，步骤 C 才算完成：

1. **构建环境**：公共环境 `bank-20261021` 按同一份配方，在 GCC、Clang 两个固定镜像上各生成一个派生镜像；如果按第 11 节拆成多个环境，下列要求对每个环境都适用。验证要求：
   - 第 4 节的冒烟测试在两个镜像中都通过，且在禁网、只读根、非 root 的容器内运行；
   - 安装前后的包清单只增不改，`gcc-14`、`libstdc++6`、`clang-19` 的版本不变；
   - 包清单和镜像 ID 都已记录。
2. **校准**：0.5.0 完整校准 passed，全部样本各两轮；CAL-30–35 的全部验证目的和适用断言按第 6 节的编号映射验收，合并编号不再要求独立存在。
3. **新题**：第 5.1 节的 6 项必选能力，每项都有签署准入的题覆盖。优先用首选题；需要换用替补题时，只能按第 5.3 节的规则进行，并记录原因。应选题纳入，或按第 5.3 节记录未纳入的原因。开发集中“链接第三方库”至少 5 道、“代码生成”至少 3 道。
4. **旧 115 题不受影响**，以下各项全部成立：
   - `task.json` 和 `hidden/` 都没有改动；
   - 题目指纹和准入不变，不需要重签；
   - `mull_config_text()` 输出逐字节不变；
   - 产品生成的 TASK.md 逐字节不变；
   - 评分仍使用两个基础镜像，结果中不出现环境字段。
5. **回归补评**：步骤 A、B 正式 runner 的 16 份冻结产物在 0.5.0 下补评，要求：
   - 构建产物和编译命令与 0.4.1 逐字节相同，判分交叉重放一致；
   - 变异状态的差异只出现在第 8 节列出的已知波动变异上，或经重放证实的新波动变异上；
   - 没有 `infra_error`。
6. **正式 runner**：用干净提交跑 `evaluator/run.py`，对第 7 节第 9 步确定的 4 道不同的已准入题各生成 1 次，覆盖链接库、moc、protoc 和“环境＋纯头文件”。候选题 ID 重复时，从其他已准入题补足第四道，并保留四项能力覆盖。要求：
   - 没有 `infra_error`；
   - 产物 invalid 时，原因必须属于产物本身（例如首个快照编译失败）；
   - 产品与评测记录的环境 GCC 镜像 ID 一致。
7. **记录与证据**：D020 写入决策记录，第 9 节列出的文档全部同步，每条实验命令都有 Audit 记录，全部步骤 C 运行目录都做过密钥扫描。
8. **没有未解决的阻塞**：第 5.3 节和第 11 节中标为“阻塞”的情形一旦出现，必须先记录诊断证据，再通过新增决策修订 D020 或本计划，之后重新满足以上各条。不能靠缩小范围（例如暂缓某项必选能力）宣布完成。

## 1. 范围

**本步骤要做：**

- 构建环境：配方格式、两份派生镜像的构建与冒烟验证、镜像与包清单的记录。
- R-01：`build.environment`、`build.link_libraries`，按题选择镜像，以及结果、校准、指纹中的环境记录。
- R-04：`build.codegen`（moc、protoc）、生成单元的编译命令核对、预生成配置头的出题流程。
- 产品：按题使用环境镜像，支持用户按同一格式编写自己的环境配方。
- 新题见第 5 节，校准样本见第 6 节，评测模块版本升为 0.5.0。
- 可选：用 D015 的工具核查 TinyExpr `tinyexpr.c:743` 的波动变异（150 次重放中 139 次检出）是否由未定义行为引起。

**本步骤不做：**

| 事项 | 原因或归属 |
|---|---|
| AMD64 验证 | 单独验证。已知 Qt5 在 AMD64 上要求包含 Qt 头文件的编译单元都带 `-fPIC`，ARM64 没有这个要求 |
| 用户自带任意 Dockerfile 的构建环境 | 可复现性和安全性无法保证；本步骤只支持同格式的配方 |
| uic、rcc 以及 Qt Widgets 等其他模块 | 本步骤的题目只用 QtCore；生成器白名单只有 moc 和 protoc |
| Boost、OpenSSL、zlib、protobuf、Qt5 之外的库 | 按需在后续步骤扩充配方 |
| FetchContent 或任何构建时联网 | 违反禁网要求，模板和契约都不提供入口 |
| 重建两个基础工具链镜像 | 基础镜像 ID 不变 |
| 混合题、验收集、阶段 6 噪声、Q-03 | 后续工作 |

## 2. 开工前的决定（D020 草案）

执行第一步把本节原样写入决策记录。措辞可以调整，决定的内容不能改。

**AGENTS.md 规则调整（用户已于 2026-10-29 同意）：** 把“镜像只安装工具链，不打包项目源码”改为“镜像只安装工具链和构建环境配方中锁定版本的依赖，不打包项目源码”；在“工具版本以 GCC 定义和 Clang/Mull 定义为准”之后补充“第三方依赖以构建环境配方为准”。这项修改在 C0 与 D020 一起提交。

**D020-1 构建环境**
- 构建环境由配方定义，一份配方生成两个派生镜像：
  - GCC 版：以固定 GCC 镜像（按 ID）为基础；
  - Clang 版：以固定 Clang/Mull 镜像（按 ID）为基础。
- 配方的内容：
  - 只能使用基础镜像已配置的同一快照 `20261021T000000Z`；
  - 顶层包写精确版本，安装时带 `--no-install-recommends`，传递依赖由快照固定；
  - 不允许执行脚本、下载源码或改动已安装的包。
- 存放与构建：
  - 配方放在 `agents/toolchains/environments/<名称>.json`，产品是独立交付物，需要持有这份配方；
  - 评测侧的 `evaluator/toolchains/toolchains.py` 读取同一个文件，与它读取 `agents/toolchains/images.json` 的做法相同；
  - 两个构建上下文各有一个只放行自身 Dockerfile 的 `Dockerfile.environment`：GCC 版在 `agents/toolchains/docker/`，Clang 版在 `evaluator/toolchains/docker/`。基础镜像和包列表通过构建参数传入。
- 镜像命名：`docker.io/library/qualtor-env-<名称>-gcc:<配方 sha256 前 12 位>`，Clang 版把 `-gcc` 换成 `-clang`。
- 每种架构都要保存：完整包清单（`dpkg-query`）、镜像 ID、冒烟测试输出。

**D020-2 题目字段（两份契约同步修改，保持逐字节相同）**
- `build.environment`：环境名，必须有对应的配方。
- `build.link_libraries`：CMake 导入目标的列表，例如 `OpenSSL::Crypto`、`ZLIB::ZLIB`、`protobuf::libprotobuf`、`Qt5::Core`、`Boost::headers`。只能取配方中声明的目标。只用 Boost 头文件时写 `Boost::headers`。
- `build.codegen`：对象列表，每项的写法如下：
  - `{"tool": "moc"}`：对整个测试可执行文件开启 AUTOMOC，被测、依赖和测试编译单元都会生效；
  - `{"tool": "protoc", "inputs": [".proto 路径"], "import_dirs": [目录]}`。
  - 写了 `codegen` 的题，必须同时声明环境，并链接对应的库。
- 不提供自由的头文件目录、链接参数或 CMake 片段。第三方头文件只能来自系统路径或导入目标。
- 有构建环境的题，不允许使用 `-fsigned-char`、`-funsigned-char`：预编译库按平台默认的 char 符号编译，改了会不一致。
- `.proto` 等生成器输入必须可见，并在 `source.files` 中登记。后缀白名单只为生成器输入增加 `.proto`，它不作为编译单元。
- 没有这几个字段的题，语义和编译命令完全不变。

**D020-3 生成单元与预生成文件**
- 生成器的输出只写到构建目录。
- 编译命令核对新增一类“生成单元”，按题目声明推出期望集合：
  - moc：AUTOMOC 的产物；
  - protoc：每个输入对应的 `<名称>.pb.cc`。
- 生成单元必须与其他单元一致的项：语言标准、断言头、宏、选项。
- 生成单元不能有的项：
  - 不加载 Mull 插件，不进入覆盖率统计或变异范围；
  - 不加覆盖率插桩。纯头文件题按 D018-2 给全部单元插桩时例外，但统计时仍会被过滤掉。
- 导入目标会自动带来一些编译选项，例如 `QT_CORE_LIB`、`QT_NO_DEBUG`、系统头文件目录，AMD64 上的 Qt 还会带来 `-fPIC`。核对时接受这些选项，但要和配方中登记的一致。
- 预生成配置头：
  - 用途：构建前只需生成一次的配置头，例如 ORC 的 `orc-config.hh`、libtiff 的 `tif_config.h`；
  - 生成：出题时在环境的 GCC 镜像中，用记录下来的命令生成，然后入库到 `source/`；
  - 登记：在 `SOURCE.json` 的 `generated` 中写明命令、工具版本、输入哈希和输出哈希；
  - 对 Agent 而言，它们就是普通的可见头文件。它们不属于修改业务源码。

**D020-4 镜像与记录**
- `executor.images` 仍只记录两个基础镜像，旧题的结果、补评判断和校准比较都不变。
- 环境镜像按题按需加载。评分时所有阶段都使用该题环境的派生镜像，包括构建、运行、Mull 和替换版本；运行阶段也必须用派生镜像，因为动态库只在派生镜像里。
- 记录与核对：
  - **结果**：新增 `environment: {name, recipe_sha256, images: {gcc, clang}}`。
  - **补评**：判断是否跳过时，要同时比较环境记录。
  - **校准状态**：新增 `environments`，记录校准题用到的环境。配方哈希或环境镜像 ID 变化时，校准变为 stale。
  - **题目指纹**：有环境的题，分母实质内容加入配方哈希；配方升级后准入自动失效。没有环境的题，指纹不变。
  - **变异分母**：记录环境；评分时如果环境不一致，判为分母过期。
- runner 对产品与评测侧的 GCC 镜像 ID 一致性检查，改为比较该题环境的 GCC 派生镜像。
- Mull：Debian 的库都在 `/usr/lib/<multiarch>`，现有的 `--ld-search-path` 够用。将来配方把库装到其他目录时，要由配方声明附加路径。

**D020-5 产品**
- 产品按公开任务里的 `build.environment` 选择本机的环境镜像，并在 `toolchain.json` 中记录环境名、配方哈希和镜像 ID。
- `agents/setup.py` 增加 `--environment <名称或配方路径>`，用来构建环境的 GCC 镜像。
- 启动时先检查环境是否可用：镜像是否存在、配方声明的 CMake 包能否找到。不可用时直接以明确的错误退出，不能把它当作 `build_failed` 反馈给 Agent，否则会误导模型。
- 只有带环境的题才在 TASK.md 中增加两行：可用的库目标和生成器。旧题的 TASK.md 逐字节不变。
- 用户自己的构建环境：按同一配方格式编写（同一快照、精确版本），产品负责构建和验证，不支持任意 Dockerfile。

**D020-6 与 D019 的关系**
- 下面两种 Clang 失败，判定时仍按基础设施错误处理：
  - moc 或 protoc 的生成单元编译失败；
  - 错误位置在库头文件里的失败。

  这是保守做法，D019 的归因规则不变。
- 本步骤内出现这类 `infra_error` 时，无论出现在参考测试、校准样本还是正式 runner 中，都必须在本步骤内查清原因，再按原因处理：
  - 真正的基础设施缺陷（环境、模板或工具链的问题）：修复实现。评测代码有变化时重新校准，再补评受影响的产物；
  - 参考测试自身的问题：按第 5.3 节修正参考测试；
  - 证据表明失败来自生成的产物，并且能可靠归因（例如所有错误都能经实例化链追到冻结的测试文件）：新增决策修订 D019 的归因规则，补充校准样本，重新校准并补评；
  - 原因不能确定：按**阻塞**处理。
- 还有未处理的 `infra_error` 时，步骤 C 不能完成。

**D020-7 版本与兼容**
- 评测模块升为 0.5.0：新增环境、生成单元和环境记录。
- 验收标准沿用步骤 B 修订后的口径：
  - 首次产物允许因产物自身原因 invalid；
  - 回归比较时排除已证实的 Mull 波动变异；
  - 不允许出现 `infra_error`。

## 3. 实施顺序

每个阶段结束时，四组单元测试都要通过：

```bash
python3 -B -m unittest discover -s evaluator/assessment/tests -p "test_*.py"
python3 -B -m unittest discover -s evaluator/runner/tests -p "test_*.py"
python3 -B -m unittest discover -s benchmark/tools/tests -p "test_*.py"
python3 -B -m unittest discover -s agents/tests -p "test_*.py"
```

建议每个阶段单独提交。下表的行号以 `a273de2` 为准，实施时以函数名为准。

### C0 决策与金标准（只改文档和测试夹具）

1. 把 D020 写入决策记录，按第 2 节已确认的措辞修改 AGENTS.md，两者一起单独提交。
2. 用 `a273de2` 的代码生成三份金标准，存为测试夹具，C4 中用作回归断言。必须在修改产品之前生成：
   - 115 道现有题的 TASK.md sha256；
   - `mull_config_text()` 的 sha256；
   - `task_sha256` 的值。
3. 在题库构建方案第 2 节，把 R-01、R-04 标为进行中。

### C1 构建环境

| 改动 | 位置 | 验证 |
|---|---|---|
| 配方文件与校验（字段、快照一致、精确版本、导入目标白名单、生成器） | `agents/toolchains/environments/bank-20261021.json`；校验函数放进共享契约，两份同步 | 单元测试：缺版本号、快照不一致、未知导入目标都被拒绝 |
| 两个 `Dockerfile.environment` | `agents/toolchains/docker/`、`evaluator/toolchains/docker/`；`.dockerignore` 只放行 Dockerfile | 构建时只传入基础镜像 ID 和包列表 |
| 构建与冒烟 | `evaluator/toolchains/toolchains.py` 增加 `--environment`，构建并检查两个派生镜像；`evaluator/toolchains/check_toolchain.py` 增加第 4 节的冒烟用例 | 两个编译器、两种运行条件（禁网、只读根、非 root）都通过，包清单只增不改 |
| 产品安装 | `agents/setup.py` 增加 `--environment` | 产品单独复制出来后，仍能构建并检查环境的 GCC 镜像 |

### C2 R-01：按题环境与链接库（评测侧）

**契约**
- 文件：两份构建契约。
- `BUILD_FIELDS` 增加 `environment`、`link_libraries`、`codegen`，`validate_build` 按 D020-2 校验。
- `test_build_contract.py:46` 原来把 `{"link_libraries": []}` 当作必须拒绝的输入，改为按新规则测试。

**CMake 模板**（两套同步）
- 有环境时，按配方的声明执行 `find_package(... REQUIRED)`，再 `target_link_libraries(scored_tests PRIVATE ...)`。
- 没有环境时，生成的构建完全不变。

**选择镜像**
- `docker_runner.py`：镜像的键由 `toolchain` 改为 `(environment, toolchain)`；环境镜像按需检查，没用到的环境不检查。
- `pipeline.py`：全部 6 个阶段都按题选择镜像，即第 129、145、213、228、270、279 行附近对 `"gcc"`、`"clang"` 的调用。

**记录与核对**
- 修改的函数：`common.py` 的 `calibration_status`、`calibrate.py` 的 `run_calibration`、`evaluate.py` 的 `pending_jobs`、`prepare_task.py` 的 `build_baseline`、`common.task_sha256`，内容按 D020-4。
- runner：`runner/host.py` 第 130、155–156 行的 GCC 镜像 ID 检查，改为比较该题环境的派生镜像。

**单元测试**
- 有环境的题选到派生镜像；
- 旧题的镜像、结果字段和校准比较不变；
- 配方哈希变化后，校准、准入和分母分别变为 stale；
- 有环境的题，char 符号选项被拒绝。

### C3 R-04：生成器与生成单元

1. 两套 CMake 模板：
   - moc：`set_target_properties(scored_tests PROPERTIES AUTOMOC ON)`；
   - protoc：`protobuf_generate(TARGET scored_tests ...)`，输出写到构建目录。
2. `compile_command_problems` 增加 `generated` 参数，按题目声明推出期望的生成单元，规则按 D020-3。共有两处调用：评测侧 `container_steps.py` 和产品侧 `container_build.py`。
3. 覆盖率和 Mull 不改代码，用测试确认：
   - 覆盖率文件里只有被测文件；
   - Mull 的变异都来自被测文件；
   - `mull_config_text` 不变。
4. 替换版本复制源码树时，`.proto` 等登记过的输入随之复制。用测试确认，替换被测源文件不会影响生成单元。
5. 预生成配置头：新增 `benchmark/tools/pregenerate.py`。它在环境的 GCC 镜像中运行登记的命令，写入 `source/` 并更新 `SOURCE.json` 的 `generated`。重新运行时，输出必须逐字节一致。

### C4 产品与 runner

**产品**
- `agents/generator/build/docker.py`、`service.py`、`container_build.py`：
  - 按题选择环境镜像，在 `toolchain.json` 中记录环境；
  - 去掉 `CMAKE_PREFIX_PATH` 的写死值，改为基础值加上配方的声明；
  - 启动时先检查环境是否可用。
- `agents/generator/task.py` 的 `task_text`：只有带环境的题才增加两行。用 C0 的金标准断言 115 道旧题的 TASK.md 不变。
- 产品 README：说明构建环境、配方格式、`--environment` 和用户自建环境的规则。同时删去“额外链接库尚未接入”这句话（约第 41 行）。
- `evaluator/runner/verify_delivery.py`：增加带环境的交付验收用例。

**runner**
- 新字段都放在 `build` 里，`public_task` 本来就会投影 `build`，不需要另改。
- 只需用测试确认：投影后的公开任务产品能加载，并且不含隐藏字段。

### C5 建题工具

**`import_humaneval_x.py`**
- 新增两组题：
  - `humaneval-x-cpp-boost`：CPP/22、137；
  - `humaneval-x-cpp-openssl`：CPP/162。
- 公共头文件补上 Boost 头文件和 typedef。这只改导入脚本，不改业务代码。
- 现有的输入生成器不支持 `boost::any`，需要扩展生成器，或补手写测试。
- CPP/137 结尾缺少 return，输入为 NaN 等情况时变量未初始化，有关的变异按 D015 复核。

**`import_exercism.py`**
- 导入 meetup：`example.h` 作为被测头文件（R-06），环境中只用 Boost 头文件。
- 配至少 5 个手写变异。

**新增 `import_step_c.py`**
- 导入 Qt、protobuf 和 BugsC++ 的题。
- 用 `pregenerate.py` 生成配置头。
- 源码按上游原样入库。

**其他工具**
- `bankutil.py`、`admit.py`、`prepare_new_tasks.py`：支持带环境的题，准入报告中列出环境和配方哈希。

### C6 题目与校准样本

1. 按第 5 节导入新题。
2. 新增 `evaluator/assessment/calibration/build_step_c_samples.py`，生成覆盖 CAL-30–35 验证目的的样本，规格见第 6 节；登记原 ID 到保留 ID 的映射，按映射核对全部适用断言及关系引用。

## 4. 构建环境配方 `bank-20261021`

版本取自快照 `20261021T000000Z`，ARM64 与 AMD64 的顶层版本相同。只锁定下表的顶层包：Qt 的部分传递依赖在两种架构上的版本或包名不同，只能由快照固定。

| 依赖 | 顶层包与版本 | CMake 导入目标 | 说明 |
|---|---|---|---|
| Boost 1.83 | `libboost1.83-dev`、`libboost-date-time1.83-dev`：`1.83.0-4.2` | `Boost::headers` | 用到的 any、date_time、algorithm 的最低标准都是 C++03。date_time 从 1.73 起只需头文件 |
| OpenSSL 3.5 | `libssl-dev`：`3.5.7-1~deb13u3`（来自 security） | `OpenSSL::Crypto` | `MD5_*` 已标为弃用，仍可使用。可以用 `OPENSSL_API_COMPAT=0x10101000L` 宏消除警告，符合 R-03 的宏规则 |
| zlib 1.3.1 | `zlib1g-dev`：`1:1.3.dfsg+really1.3.1-1+b1` | `ZLIB::ZLIB` | — |
| protobuf 3.21.12 | `libprotobuf-dev`、`protobuf-compiler`：`3.21.12-11+deb13u1` | `protobuf::libprotobuf`、`protobuf::libprotobuf-lite`；生成器 protoc | 3.21 是最后一个支持 C++11 的系列，v22.0 已放弃 C++11。不得从 backports 取新版 |
| Qt 5.15.15 | `qtbase5-dev`、`qtbase5-dev-tools`：`5.15.15+dfsg-6+deb13u1` | `Qt5::Core`；生成器 moc（`/usr/lib/qt5/bin`） | Qt 6 要求 C++17，不能用。qtbase5-dev 会带进 GL/X11 依赖 |

两个派生镜像约各增加 610 MB，其中 Qt 占大头。全部库链接同一份 `libstdc++6 14.2.0-19`，没有标准库混用的问题。

**冒烟测试**：每项都在 GCC、Clang 下各跑一遍，用 `-std=c++11` 加 cxx11_guard，并在禁网、只读根、非 root 的容器内运行。

| 依赖 | 检查内容 |
|---|---|
| Boost | `any_cast`；gregorian 日期计算与解析；`BOOST_VERSION == 108300` |
| OpenSSL | `MD5("Hello world")` 等于 `3e25960a79dbc69b674cd4ec67a72c62`；头文件版本与运行时版本一致 |
| zlib | 压缩后解压的往返；`zlibVersion()` 为 `1.3.1` |
| protobuf | `protoc --version` 为 3.21.12；用含 `map<string, ...>` 和 `oneof` 的 `.proto` 生成代码并编译；序列化往返和反射都可用 |
| Qt5 | AUTOMOC 的信号与槽；`QDate`、`QRegularExpression`；`qVersion()` |

**公共检查**：
- 镜像里只有一份 `libstdc++.so.6`；
- 静态断言 `_GLIBCXX_USE_CXX11_ABI == 1`，并实际链接一个带 `[abi:cxx11]` 的库符号；
- `ldd` 没有 `not found`；
- mull-runner 没有 “Could not find dynamic library” 告警；
- 变异只来自被测文件，且至少检出一个；
- 覆盖率只统计被测文件。

## 5. 新题

### 5.1 必选能力与题目清单

下面 6 项是必选能力，每项都要有签署准入的题覆盖。首选题不能准入时，按第 5.3 节先定位原因，再决定是否按顺序换用替补题。

| 必选能力 | 首选题 | 同能力替补（按顺序） |
|---|---|---|
| 链接系统库 | `humaneval-x-cpp-openssl` | `gzip-hpp`、`libphonenumber-lite` |
| 只用环境中的第三方头文件 | `humaneval-x-cpp-boost` | `exercism-meetup` |
| moc | `qt-aes` | KDToolBox 的 KDSignalThrottler（测试需要重写） |
| protoc | `orc-bloom-filter` | `prometheus-cpp-text`、`libphonenumber-lite` |
| 预生成配置头 | `orc-bloom-filter` | `exiv2-pngchunk`、`libtiff-strip` |
| 环境＋纯头文件（R-01 加 R-06） | `exercism-meetup` | `gzip-hpp` |

候选题来自只读调研：没有编译验证，C++11 结论只依据构建文件和语法，变异数是估算。以 Docker 标定为准。

| 优先级 | 题目 ID（建议） | 来源与提交 | 被测 | 依赖与生成器 | 验证的能力 | 层级 |
|---|---|---|---|---|---|---|
| 必选 | `humaneval-x-cpp-openssl` | HumanEval-X C++（CodeGeeX `2838420b`），CPP/162 | `cpp_162.cc` | `OpenSSL::Crypto` | R-01 链接库 | 入门 |
| 必选 | `humaneval-x-cpp-boost` | 同上，CPP/22、137 | 两个源文件 | `Boost::headers` | R-01 环境中的第三方头文件 | 入门 |
| 必选 | `qt-aes` | bricke/Qt-AES `fe02771d`（Unlicense） | `qaesencryption.cpp`（有效行约 371，类带 `Q_OBJECT`） | `Qt5::Core`；moc | R-01 Qt 链接，R-04 moc（不运行 moc 就链接不过） | 中等 |
| 必选 | `orc-bloom-filter` | apache/orc v1.8.10 `bf5f7434`（1.9 起要求 C++17） | `BloomFilter.cc`（约 167 行） | `protobuf::libprotobuf`；protoc；预生成 `Adaptor.hh`、`orc-config.hh` | R-04 protoc 与预生成配置头 | 中等 |
| 必选（可由 gzip-hpp 替补） | `exercism-meetup` | Exercism `7315f0f` | `meetup.h`（R-06 纯头文件） | `Boost::headers`（date_time 只需头文件） | R-01 加 R-06 | 中等 |
| 应选 | `gzip-hpp` | mapbox/gzip-hpp `7546b35a`（BSD-2） | 头文件 | `ZLIB::ZLIB` | zlib 链接（头文件中调用） | 入门 |
| 应选 | `qt-mustache` | qt-mustache `79f65c08`（BSD-2） | 渲染器源文件（约 355 行，无 `Q_OBJECT`） | `Qt5::Core` | Qt 链接；和 qt-aes 对照，能区分是链接问题还是 moc 问题 | 中等 |
| 应选 | `prometheus-cpp-text` | prometheus-cpp `a97127c9` | 文本序列化与各类指标（约 246 行） | `protobuf::libprotobuf`；protoc | 再补一道 protoc 题 | 中等 |
| 应选 | `libphonenumber-lite` | libphonenumber v8.12.39 `b4e9b737` | 约 110 行（LITE_RUNTIME，不需要 ICU、RE2） | `protobuf::libprotobuf-lite`；protoc | protoc 的 lite 运行时 | 入门 |
| 应选 | `exiv2-pngchunk` | BugsC++ exiv2/12，修复提交 `b35c43e7`（GPL-2.0+） | `pngchunk_int.cpp`（748 行） | `ZLIB::ZLIB`；关闭 XMP，不需要 expat；预生成 2 个头文件 | 真实缺陷加 zlib 加预生成配置头 | 困难 |
| 应选 | `libtiff-strip` | BugsC++ libtiff/5，修复提交 `d651abc0` | `tif_strip.c`（C，398 行） | zlib 经依赖源文件使用；预生成 2 个头文件 | C 语言真实缺陷加环境 | 困难 |

全部完成后，开发集共 126 题。“链接第三方库”9 道：OpenSSL 1、zlib 3、protobuf 3、Qt 2。“代码生成”4 道：moc 1、protoc 3。层级以实际导入为准。

### 5.2 出题注意

**通用要求**
- 源码按上游原样入库，保留许可证。exiv2 是 GPL-2.0+，要随源码保留 COPYING。
- 真实缺陷版本由 BugsC++ 的 buggy.patch 作用在修复提交上得到，在 `hidden/README.md` 中记录：
  - BugsC++ 的提交号；
  - patch 的哈希；
  - 回归用例。
- HumanEval-X 的新题单独成组，不并入 01–20，否则会改动已签署题目的源码和分母。
- 所有题都用环境 `bank-20261021`。变异数超过 500 的题，按方案第 4 节拆题，或只列出需要考的文件。

**逐题要求**
- **qt-aes**：
  - 去掉 PBKDF2 那个 50 万次迭代的用例，避免超时；
  - 导入目标会带来 `QT_NO_DEBUG`，两套构建要保持一致。
- **orc-bloom-filter**：大端分支在 ARM64 和 AMD64 上都执行不到，约 25 个变异，复核时按“平台不可达”写进等价结论。
- **exiv2-pngchunk**：上游测试是用 Python 驱动命令行跑 PoC 图片，要改写成 GoogleTest，PoC 字节内嵌在隐藏的参考测试中。

### 5.3 替换与淘汰规则

**必选能力的首选题不能准入时，先定位原因，再按原因处理：**
- 实现缺陷（评测、产品或构建环境的问题）：修复实现后重试，不换题。
- 题目自身的原因：先补强参考测试或预生成配置；仍不行，按 5.1 节的顺序换用同能力的替补题，并在验证说明中写明原因和证据。题目自身的原因包括：
  - 上游代码在固定环境中不能按 C++11 编译；
  - 缺陷不能确定性复现；
  - 参考测试不足，补强后仍达不到准入阈值；
  - 变异数严重超出范围。
- 原因暂时无法确定：按**阻塞**处理，保存诊断证据，不换题，也不宣布完成。
- 某项能力的首选题和全部替补都不能准入：按**阻塞**处理，补充候选并修订本计划。

**应选题**达不到准入时，同样先定位原因。属于题目自身原因的，可以不纳入，或换用下列备选，并在验证说明中写明原因：
- Qt：KDToolBox 的 KDSignalThrottler（测试依赖计时、用了 C++14，需要重写）、qtcsv v1.6；
- protobuf：sentencepiece v0.1.96；
- 真实缺陷：exiv2/17、exiv2/6、exiv2/8。

## 6. 校准样本

样本 ID 全局唯一，现有的最大编号是 CAL-29。下表按首选题写出。样本放在各项必选能力实际采用的题上；首选题被替补时，按替补题重写样本，规则如下：

- 保持每个样本的验证目的，以及强样本与弱样本之间的强弱关系。
- 替补题是纯头文件题时（gzip-hpp、meetup），M1_e2e 和 M1_valid 断言为 `na`、原因 header_only，改用 M2 等适用的指标验证检出能力。例如弱样本的 M2 要低于强样本。
- 同一道题同时承担两项能力时，验证目的相同的样本可以合并，但须保留双方全部适用断言，在样本说明中登记原 ID 到保留 ID 的映射（未合并的映射到自身），同步更新 CAL-31 等关系引用。例如 CAL-30 与 CAL-35 合并时仍须验证环境配方/镜像一致、M1 的 header_only 不适用、冻结覆盖及 M2 强度；弱样本仍须形成真实的强弱关系。
- 所有期望都在正式校准前写定并冻结，之后不得为了通过而修改。

| 样本 | 题目 | 内容 | 期望（hard 和 relations） |
|---|---|---|---|
| CAL-30 | humaneval-x-cpp-openssl | 参考测试原样复制 | scored；全部 valid；M1_e2e ≥ 0.8；结果中有 `environment`，配方哈希与镜像 ID 与校准记录一致 |
| CAL-31 | humaneval-x-cpp-openssl | 去掉对非空输入断言 MD5 值的测试 | 全部 valid；M1_e2e < CAL-30 |
| CAL-32 | qt-aes | 参考测试原样复制 | scored；全部 valid；M1_e2e ≥ 0.8；覆盖率文件只有被测文件；变异只来自被测文件，不含 moc 生成单元 |
| CAL-33 | orc-bloom-filter | 参考测试原样复制 | scored；全部 valid；M1_e2e ≥ 0.8；覆盖率和变异都不含 `.pb.cc` |
| CAL-34 | humaneval-x-cpp-boost | 参考测试原样复制 | scored；全部 valid；M1_e2e ≥ 0.8 |
| CAL-35 | 环境＋纯头文件题（首选 exercism-meetup，替补 gzip-hpp） | 参考测试原样复制 | scored；全部 valid；M1_e2e、M1_valid 断言为 `na`、原因 header_only；C1 等于冻结分母上的参考值；M2 == 1；结果中有 `environment` |

CAL-01–29 不改，作为旧题型（含 D018、D019）的回归断言。CAL-18–20 中与 0.3.0 实测值的精确相等断言继续保留。

## 7. Docker 执行顺序（Linux ARM64）

**通用规则**
- 每条命令都经 Audit 执行，保存命令、时间、退出码、stdout 和 stderr。
- run-id 用 `step-c-<用途>-YYYYMMDD-NN`。失败保留，重试换新的 run-id。
- 正式 runner 必须在已提交的干净工作区上运行。
- 构建镜像时需要联网，只用于从快照下载软件包，这一步和运行时禁网分开配置。

| 序号 | 步骤 | 命令或要点 | 通过标准 |
|---|---|---|---|
| 1 | 预检 | 按完整名称检查两个基础镜像的 ID | 等于 `bd01e6e4…`、`013ac35a…`，不变 |
| 2 | 构建环境 | `python3 -B evaluator/toolchains/toolchains.py --environment bank-20261021`（C1 新增的参数，以实现为准）；产品侧执行 `python3 -B agents/setup.py --environment bank-20261021` | 两个派生镜像构建成功；冒烟测试全部通过；包清单只增不改；记录镜像 ID |
| 3 | 校准题的种子分母 | `python3 -B evaluator/assessment/prepare_task.py baseline --task <题目> --write`，对第 6 节各样本所在的题各执行一次，默认为 humaneval-x-cpp-openssl、humaneval-x-cpp-boost、qt-aes、orc-bloom-filter、exercism-meetup | 解开校准依赖 |
| 4 | 完整校准 | `python3 -B evaluator/assessment/calibrate.py --jobs 2 --run-id step-c-calibration-YYYYMMDD-01` | 全部样本各两轮 passed；状态版本为 0.5.0，并记录环境 |
| 5 | 正式标定 | `python3 -B benchmark/tools/prepare_new_tasks.py --tasks <新题…> --write --jobs 2 --run-id step-c-formal-YYYYMMDD-01` | 全部写入；分母中记录了环境 |
| 6 | 复核与签署 | `mutant_report.py` 逐题复核；`admit.py --tasks <新题…> --by <复核人> --write` | 新题 admitted；旧 115 题不需要重签 |
| 7 | 回归补评 | `evaluate.py --rescore` 依次补评 `step-a-runner-20261028-02`、`step-b-runner-20261029-01`、`step-b-runner-20261029-02` | 满足第 0 节第 5 条 |
| 8 | 提交 | 提交实现与新题 | `git status` 干净 |
| 9 | 正式 runner | `python3 -B evaluator/run.py --config default --tasks <链接库题> <moc 题> <protoc 题> <环境＋纯头文件题> --trials 1 --run-id step-c-runner-YYYYMMDD-01`。四个位置取 5.1 节中各能力实际准入的题，默认为 `humaneval-x-cpp-openssl qt-aes orc-bloom-filter exercism-meetup`；meetup 被替补时换成 `gzip-hpp`。去重后须有四道不同题；若同题同时覆盖链接库与环境＋纯头文件，则从其他已准入题补足第四道，保留四项能力覆盖，各题仅生成一次 | 满足第 0 节第 6 条 |
| 10 | 收尾核对 | `final_checks.py` 生成 `final-checks.json` 和 `summary.md` | 第 10 节各项都有机器核对结果 |

## 8. 回归与兼容性检查

**本机即可完成（不需要 Docker）**
- 四组单元测试；
- 用 `admit.py` 核对，不加 `--write`；
- 用 `apply_review.py` 核对；
- `calibration_status` 重算为 passed；
- 两份契约文件逐字节相同；
- 旧 115 题：`git diff a273de2 -- benchmark/<旧题>/` 为空，题目指纹与 `admission.json` 的登记一致，`mull_config_text`、TASK.md 和 `task_sha256` 都与 C0 金标准一致。

**需要 Docker**
- CAL-01–29 在 0.5.0 下仍然通过。
- 第 7 节第 7 步的补评。比较时排除以下 4 个已知波动变异（验证说明第 15 节）：
  - `md4c-html.c:256:19` 的 `cxx_init_const`；
  - `tinyexpr.c:743:10` 的 `cxx_replace_scalar_call`；
  - `singledocparser.cpp:271:20` 的 `cxx_eq_to_ne`；
  - `singledocparser.cpp:331:29` 的 `cxx_ne_to_eq`。

  其他变异的状态如有差异，要先用原二进制重放证实是波动，否则按回归处理。
- 环境镜像的冒烟测试，以及产品侧的交付验收：`verify_delivery.py` 中带环境的用例。

## 9. 文档同步

| 文档 | 内容 |
|---|---|
| [AGENTS.md](../AGENTS.md) | 镜像规则的措辞，已确认（第 2 节），在 C0 与 D020 一起提交 |
| [决策记录](决策记录.md) | D020；文件开头的现行口径说明加入 D020 |
| [C++11 固定工具链](C++11固定工具链.md) | 构建环境：配方、构建命令、冒烟测试、镜像命名与 ID 记录 |
| [评测规格](评测规格.md) | 第 6 节的实现状态；第 7 节的后续工作（AMD64 上的 `-fPIC`、uic/rcc、更多依赖） |
| [评测模块与校准样本设计](评测模块与校准样本设计.md) | 题目包新增 build 字段、预生成文件、环境记录；样本表按第 6 节映射加入 CAL-30–35 的全部验证目的、适用断言与关系引用 |
| [评分算法](评分算法.md) | 确认指标公式不变；写明生成单元不计覆盖率、不进变异分母 |
| [题库构建方案](题库构建方案.md) | R-01、R-04 的状态；第 1.3、1.4 节的题数；第 5 节的新题；第 7 节步骤 C 的状态；附录 A 模板中加入新字段 |
| [题库验证说明](题库验证说明.md) | 新增第 16 节，记录执行顺序、结果、证据表和未验证范围 |
| [评测运行说明](评测运行说明.md) | 环境镜像的构建与检查，带环境的题的标定与补评 |
| [产品 README](../agents/README.md)、[接口与运行边界](接口与运行边界.md) | 构建环境、配方格式、`--environment`、公开任务字段，以及 TASK.md 中新增的两行 |
| [研发日志](研发日志.md) | 本轮过程与失败记录 |
| [文档索引](README.md) | 更新相关行；本计划完成后标为历史计划 |

## 10. 交付与验收

**交付时请提供：**
- 提交范围：先是 D020 的独立提交，然后是各阶段的提交；
- 本轮全部 run-id 清单；
- `summary.md`：每条结论都对应证据路径，失败与重试保留；
- `final-checks.json`；
- 两种编译器下的环境包清单和冒烟测试输出；
- 未纳入题目的清单及原因；
- 校准样本原 ID 到保留 ID 的映射及完整断言清单；正式 runner 的四个互异题目 ID 与能力覆盖。

**我会逐项验收：**

1. **代码审查**
   - D020 的每一条都有对应实现，没有超出范围的改动；
   - 两份契约逐字节相同；
   - 旧题的代码路径行为不变（镜像选择、编译命令、Mull 配置、记录字段）；
   - 评测侧运行时没有导入产品的私有实现；
   - 配方中不含脚本，也不会改动已安装的包。
2. **本机复算**：第 8 节中本机能做的全部项目；另外独立复算：
   - 新题的指纹包含配方哈希；
   - 预生成文件的登记与哈希；
   - 隐藏材料没有出现在可见文件中（按文件内容核对）。
3. **环境证据**：两份派生镜像的包清单前后差异、冒烟测试输出、镜像 ID，以及产品侧和评测侧 GCC 派生镜像 ID 一致。
4. **校准证据**：全部样本两轮结果都是 0.5.0；环境记录一致；按第 6 节的原 ID 到保留 ID 映射核对全部适用断言和强弱关系；CAL-32、CAL-33 对应样本中生成单元不进覆盖率和变异，能在原始结果中找到。
5. **标定与准入**：新题的分母、环境记录和预生成登记；`admission.json` 中旧题的记录不变。
6. **回归补评**：16 份产物按第 8 节的规则比对。
7. **正式 runner**：
   - 启动审计的参数，以及运行时工作区是否干净；
   - 公开任务的投影；
   - 产品与评测侧的环境记录是否一致；
   - 结果状态和失败原因；
   - 密钥扫描是否覆盖全部步骤 C 的运行目录。
8. **文档**：第 9 节全部同步，链接有效；已实现、已验证、待实现区分清楚；不把 AI 复核写成人工审阅。

## 11. 风险与预案

标为**阻塞**的情形按第 0 节第 8 条处理：先记录证据并修订决定，不能据此缩小范围后宣布完成。

| 风险 | 预案 |
|---|---|
| Qt5 依赖重，每个派生镜像约增加 610 MB，GCC 镜像还会多装一份 libllvm19 | 先接受。体积不可接受时，把 Qt 拆成单独的环境 `bank-qt5-20261021`，其他题用更轻的环境。这属于配方调整，仍在 D020 的规则之内：在 D020 中登记环境清单，第 0 节第 1 条对每个环境都适用 |
| 预编译库按 C++17 构建，题目代码是 C++11，头文件会按特性宏走不同的内联分支 | 冒烟测试覆盖 protobuf 的反射、Arena 和 Qt 的信号与槽。发现问题时按**阻塞**处理，保存证据。D020-1 不允许下载源码或在配方中执行脚本，如果要改用源码构建依赖，必须先新增决策修订 D020-1（写明源码包与 sha256，构建脚本纳入审计和校准范围），然后再继续 |
| protobuf 3.21 生成的代码在两种编译器下的 C++11 兼容性还没有实测 | 冒烟测试的 `.proto` 要包含 map、oneof 和嵌套消息。不通过时按**阻塞**处理：保存证据，修订决定（例如更换 protobuf 的来源）后再继续。不能暂缓 protoc 题后宣布完成：protoc 是必选能力，没有它“代码生成”也凑不够 3 道 |
| Clang 编译 Qt 或 protobuf 头文件时出现 GCC 不报的错误 | 会判为基础设施错误。无论出现在参考测试、校准样本还是正式 runner 中，都按 D020-6 在本步骤内查清原因再处理：基础设施缺陷就修实现，并重新校准、补评；参考测试自身的问题按 5.3 节修正；能可靠归因于生成产物的，才新增决策修订归因规则，并补校准、补评；原因不明按**阻塞**处理 |
| 快照站点暂时不可用（调研时遇到过一次 404） | 构建步骤重试；连续失败时记录下来，择时再构建，不改用其他软件源 |
| AMD64 上 Qt 需要 `-fPIC` | 不在本步骤验证；在文档和 AMD64 待办中写明，契约核对要接受导入目标带来的这个选项 |
| 真实缺陷题的上游测试需要改写（exiv2 的 PoC），或规模偏大 | 作为应选题，按 5.3 节处理；它们同时是“预生成配置头”的替补，被用作替补时按必选能力的规则处理 |
| HumanEval-X CPP/22 只有 3–6 个变异 | 入门题允许较少的变异；如果参考检出率达不到阈值，补强参考测试 |
