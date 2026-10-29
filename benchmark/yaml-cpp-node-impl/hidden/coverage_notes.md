目标仅 include/yaml-cpp/node/impl.h。全部依赖与测试单元插桩，统计仅目标头。
公开模板成员 Node(T)、operator=(T)、as<T>、as<T,S>、push_back<T>、operator[]<Key>（const/非 const）、remove<Key>、force_insert<Key,Value> 用 int、std::string、char 数组及 char* 补齐；支持源文件及上游参考测试同时覆盖 Node 非模板成员。
0.4.1 补入 Node(const detail::iterator_value&)（impl.h:39，以 *cn.begin() 构造）、detail::to_value_t<const char*>::to_value_t（331）和 operator()（335，以 const char* 键调用 operator[]）。原来的 char* 与数组调用不能实例化 const char* 特化，旧说明已纠正。

显式实例化只在准备阶段编译，不执行；新函数即使未被参考测试运行仍留在分母。冻结按源码位置合并实例，不按任意用户自定义 convert<T> 类型累计。Node(const Node&)（45）与 ~Node()（56）虽为 default 定义，固定 GCC 本轮均产生了覆盖记录，已纳入冻结集合。没有另行排除有定义的公开成员。
