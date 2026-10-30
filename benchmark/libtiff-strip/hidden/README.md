# libtiff strip

被测 tif_strip.c 与依赖 C 单元保留固定上游字节，依赖列表取自上游 CMake 的 tiff 目标。
配置头由锁定 GCC 环境重复生成，关闭 jpeg/jbig/lzma，仅启用 zlib 等上游内置能力。
参考测试直接覆盖条带与扫描行计算；BugsC++ libtiff/5 的补丁去掉 td_nstrips 缓存分支，
以已缓存条带数与重新计算值不同的有定义结构状态复现。补丁原样保存为 buggy.patch。

真实缺陷版本 bugscpp-5：
- BugsC++ 仓库 https://github.com/Suresoft-GLaDOS/bugscpp 的固定提交 be5cc489cb2b3127ec3b73cb4adfdd290807f55b，缺陷 libtiff/5；
  BugsC++ 标注为 CVE-2016-9273（Heap-buffer-overflow in cpStrips），上游修复提交 d651abc097d91fac57f33b5f9447d0a9183f58e7。
- buggy.patch 的 sha256：bbb7bd20308789322fd08307df6a809d53a366b0d42d530469d1c596baab4f94。
- 回归用例：Strips.ComputeAndCount。
