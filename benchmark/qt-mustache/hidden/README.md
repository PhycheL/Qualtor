# Qt Mustache

上游 QtTest 机械转换为 GoogleTest；全部内嵌 JSON 规格转换为独立用例；源码不改写。
testPartialFile 使用外部可写文件路径，独立改写为 QTemporaryDir 文件用例（补充文件见参考测试）。
本题不含 Q_OBJECT；仅链接 QtCore，与 moc 题作对照。

复核补充测试：`review_tests.cc` 来自 `benchmark/tools/mutant_review/qt-mustache/`，是变异复核中区分等价候选的反例，已并入参考测试与探针。
