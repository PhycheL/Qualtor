# libphonenumber lite 比较

被测 phonenumber.cc 与头文件保持上游字节；两个 resources/*.proto 按 phonenumbers/ 路径放置以保持
原始源码的生成头 include。它们原有 LITE_RUNTIME 选项保持。隐藏测试逐字段核对 presence、value、
重复字段的顺序与数量；只链接 protobuf lite，不需要 ICU 或 RE2。
