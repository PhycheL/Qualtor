# Exiv2 PNG chunk

源码及 GPL COPYING 原样入库；依赖源文件取自上游 exiv2lib/exiv2lib_int 目标，XMP 与 NLS 功能关闭。
配置头在锁定 GCC 环境重复生成，SOURCE.json 保存全部输入、命令、版本和输出哈希。
参考测试覆盖公开 PngChunk 操作与错误输入；上游 test/data/issue_845_poc.png 原字节内嵌隐藏 poc.h，
通过 ImageFactory 内存入口回放。BugsC++ exiv2/12 的固定补丁原样保存为 buggy.patch。

真实缺陷版本 bugscpp-12：
- BugsC++ 仓库 https://github.com/Suresoft-GLaDOS/bugscpp 的固定提交 be5cc489cb2b3127ec3b73cb4adfdd290807f55b，缺陷 exiv2/12
  （Out-of-bounds Read），上游修复提交 b35c43e7c2409978a0c45f35c2ec8c7f625469df。
- buggy.patch 的 sha256：19f92060ded10421da2f3bcbf912eef4fcf4fcdbca023f1947030dbd2082d4cc。补丁删去 readRawProfile 逐位解析长度及溢出检查，
  改为 atol(startOfLength)，并要求 0 <= length。
- 回归用例：只有 PngChunk.ImageContentAndMalformedRawProfiles。长度字段为 "-1" 时，修复版本不解析负号、
  得到长度 0 并返回空结果；缺陷版本 atol 得到 -1，enforce 抛出 Exiv2::Error，EXPECT_NO_THROW 失败。
  该输入在两个版本上都是有定义行为。长度 9223372036854775808 只用于覆盖修复版本的溢出检查；它在缺陷版本上
  依赖 atol 溢出（ISO C 未定义行为，glibc 返回 LONG_MAX），检出不依赖这一输入。
- PngChunk.UpstreamIssue845 在缺陷版本上同样通过，不能检出该缺陷（0.5.0 标定
  step-c-seed-20261029-13-exiv2-pngchunk 中，缺陷版本只有上一个用例失败）。
