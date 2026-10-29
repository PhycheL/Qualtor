目标为完整 peglib.h；这个上游提交在 C++11 下使用 peg::any。上游 test/test.cc 的 parser、Definition、SemanticValues、AST、macro 和 UTF-8 功能测试，加 api_edges 的 search、get_rule_names、enable_trace 和错误位置测试，构成分母实例化来源。

coverage_instantiation/public_api.cc 补齐 any 的四种 get 重载、SemanticValues::transform、Action 的函数指针/仿函数/nullptr 构造及赋值、Definition 的四种 parse_and_get_value 与逗号运算符、parser 的四种模板 parse/parse_n、enable_ast、AstBase 全部构造和 AstOptimizer::optimize。scope_exit 另显式实例化 std::function<void()>，把通常被复制省略隐藏的移动构造和 release 也纳入。公开 seq/cho、Sequence/PrioritizedChoice 构造及 Context::packrat 由解析器和上游用例实例化。

0.4.1 对照固定 Clang 的公开声明与 GCC 冻结位置，补入下列原先未发出覆盖记录的定义（行号指固定提交的 peglib.h）：

| 位置 | 函数 | 实例化方式 |
|---|---|---|
| 452 | SemanticValues::name() const | 对参数 values 调用 |
| 567 | call<R=any>(F,Args&&...) | 返回 any 的 lambda |
| 927 | Sequence(const Sequence&) | 复制 const Sequence |
| 946 | Sequence(vector<shared_ptr<Ope>>&&) | 临时 vector |
| 994 | PrioritizedChoice(vector<shared_ptr<Ope>>&&) | 临时 vector |
| 1028 | PrioritizedChoice::size() const | 对局部 choice 调用 |
| 1941 | Definition(Definition&&) | 移动局部 Definition |
| 1954 | Definition(const shared_ptr<Ope>&) | 使用字符算子 |
| 1989 | Definition::parse(const char*,any&,const char*) const | 携带 data 调用 |
| 2916 | udl::operator "" _(const char*,size_t) | 取函数地址再调用，避免常量折叠 |
| 3113 | parser(const char*,size_t) | 显式给出文本长度 |
| 3132 | parser::load_grammar(const char*,const Rules&) | 显式传 Rules |
| 3235 | parser::operator[](const char*) const | const parser 访问规则 |

以上调用仅在准备阶段编译，不执行，不宣称这些函数已被参考测试覆盖。逐项排除说明：Sequence(const Args&...) 的 MSVC 2013 分支（937）与 PrioritizedChoice(const Args&...) 的 MSVC 2013 分支（985）被当前 Linux C++11 预处理排除；parser()（3104）为 default 构造，固定 GCC 本轮已发出记录并纳入；Ope::parse（920）与 Ope::accept（921）为无函数体的纯虚声明。Ope::Visitor 的 visit 重载有空函数体，属于可执行定义，不能按纯虚函数排除。SemanticValues::transform(F) 为私有辅助模板且无调用者；Definition 私有复制/移动赋值仅声明、无定义，均不是遗漏的公开实现。除此之外，有定义的公开成员和自由函数均由参考测试或显式实例化纳入；用户自定义 AST 注解、语义动作类型和 Visitor 的无限类型组合按同一源码位置合并。

上游 T073–T091 的语法调试测试复制全局 Grammar，Definition 复制构造把共享 Holder::outer_ 改为副本地址，副本销毁后原语法对象留下悬空指针。转换时在这些测试中加入 GlobalGrammarScope，保存并在测试结束后恢复原指针，保留全部断言；没有修改业务源码。初次 Docker 乱序运行的崩溃记录保留在 step-b-candidates-20261029-01-cpp-peglib-parser。
