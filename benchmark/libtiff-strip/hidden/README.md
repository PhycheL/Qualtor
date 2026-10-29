# libtiff strip

被测 tif_strip.c 与依赖 C 单元保留固定上游字节，依赖列表取自上游 CMake 的 tiff 目标。
配置头由锁定 GCC 环境重复生成，关闭 jpeg/jbig/lzma，仅启用 zlib 等上游内置能力。
参考测试直接覆盖条带与扫描行计算；BugsC++ libtiff/5 的补丁去掉 td_nstrips 缓存分支，
以已缓存条带数与重新计算值不同的有定义结构状态复现。补丁与来源哈希见 buggy.patch 和 task.json。

BugsC++ 固定提交 be5cc489cb2b3127ec3b73cb4adfdd290807f55b；补丁哈希见 task.json；回归用例 Strips.ComputeAndCount。
