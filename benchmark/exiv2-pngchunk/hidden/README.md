# Exiv2 PNG chunk

源码及 GPL COPYING 原样入库；依赖源文件取自上游 exiv2lib/exiv2lib_int 目标，XMP 与 NLS 功能关闭。
配置头在锁定 GCC 环境重复生成，SOURCE.json 保存全部输入、命令、版本和输出哈希。
参考测试覆盖公开 PngChunk 操作与错误输入；上游 test/data/issue_845_poc.png 原字节内嵌隐藏 poc.h，
通过 ImageFactory 内存入口回放。BugsC++ exiv2/12 的固定补丁保存为 buggy.patch。
BugsC++ 提交 be5cc489cb2b3127ec3b73cb4adfdd290807f55b；补丁哈希见 task.json；
回归用例 PngChunk.ImageContentAndMalformedRawProfiles 与 PngChunk.UpstreamIssue845。
