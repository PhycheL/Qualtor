目标仅 include/yaml-cpp/node/impl.h。全部依赖与测试单元插桩，统计仅目标头。
公开模板成员 Node(T)、operator=(T)、as<T>、as<T,S>、push_back<T>、operator[]<Key>（const/非 const）、remove<Key>、force_insert<Key,Value> 用 int、std::string、char 数组及 char* 补齐；支持源文件及上游参考测试同时覆盖 Node 非模板成员。
显式实例化只在准备阶段编译。无定义的声明、编译器未产生覆盖率记录的 default 成员不计分；未支持任意用户自定义 convert<T> 的无限类型组合，冻结按源码位置合并实例。模板 helper 的 char*、const char* 与数组特化由上述调用触发。
