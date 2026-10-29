目标为完整 peglib.h；这个上游提交在 C++11 下使用 peg::any。上游 test/test.cc 的 parser、Definition、SemanticValues、AST、macro 和 UTF-8 功能测试，加 api_edges 的 search、get_rule_names、enable_trace 和错误位置测试，构成分母实例化来源。

coverage_instantiation/public_api.cc 补齐 any 的四种 get 重载、SemanticValues::transform、Action 的函数指针/仿函数/nullptr 构造及赋值、Definition 的四种 parse_and_get_value 与逗号运算符、parser 的四种模板 parse/parse_n、enable_ast、AstBase 全部构造和 AstOptimizer::optimize。scope_exit 另显式实例化 std::function<void()>，把通常被复制省略隐藏的移动构造和 release 也纳入。公开 seq/cho、Sequence/PrioritizedChoice 构造及 Context::packrat 由解析器和上游用例实例化。

预处理排除的 MSVC 2013 专用构造不进入分母；私有 SemanticValues::transform(F) 没有调用者，不显式实例化；Definition 的私有复制/移动赋值只有声明，没有定义。其他内部模板 helper 经公开入口实例化。用户自定义 AST 注解、语义动作返回类型和 Visitor 的无限类型组合不逐一枚举；同一源码位置合并。冻结集合之外的行只诊断、不计分。

上游 T073–T091 的语法调试测试复制全局 Grammar，Definition 复制构造把共享 Holder::outer_ 改为副本地址，副本销毁后原语法对象留下悬空指针。转换时在这些测试中加入 GlobalGrammarScope，保存并在测试结束后恢复原指针，保留全部断言；没有修改业务源码。初次 Docker 乱序运行的崩溃记录保留在 step-b-candidates-20261029-01-cpp-peglib-parser。
