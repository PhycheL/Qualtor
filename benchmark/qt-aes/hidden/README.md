# Qt AES 隐藏材料

上游 QtTest 机械转换为 GoogleTest；QObject 测试夹具换为 Test，断言保持；每个用例独立初始化。
按执行计划不注册含 500000 次 PBKDF2 的 GenerateKeyIterationCapExceeded。
四个文件往返用例保留全部原始字节，以 Qt qUncompress 解开隐藏头中的压缩输入，不要求 rcc 或额外挂载。
与既有 YAML 题相同，首个断言失败即抛出并结束本次运行，避免已检出的变异继续做大文件往返。
AES-NI 和 constant-time S-box 的条件编译测试沿用上游宏，本题不启用这些可选特性。

Mull 原始全套预热实测 16.32 秒，故本题显式设置 --timeout=30000；独立用例有效性超时不变。证据：runs/step-c-aes-diagnosis-20261029-01。
