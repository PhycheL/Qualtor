#include "peglib.h"

namespace {
int value_action(peg::SemanticValues&) { return 1; }
int const_action(const peg::SemanticValues&) { return 1; }
int data_action(peg::SemanticValues&, peg::any&) { return 1; }
int const_data_action(const peg::SemanticValues&, peg::any&) { return 1; }
struct MutableAction { int operator()(peg::SemanticValues&) { return 1; } };
struct MutableConstAction { int operator()(const peg::SemanticValues&) { return 1; } };
struct MutableDataAction { int operator()(peg::SemanticValues&, peg::any&) { return 1; } };
struct MutableConstDataAction { int operator()(const peg::SemanticValues&, peg::any&) { return 1; } };
}

// 仅准备阶段编译，不执行；按源码位置冻结公开模板重载。
void instantiate_peglib_public_api(peg::parser& parser, peg::Definition& rule,
                                   peg::SemanticValues& values, peg::Context& context) {
  peg::any data(1);
  const peg::any& const_data=data;
  (void)data.get<int>(); (void)data.get<peg::any>();
  (void)const_data.get<int>(); (void)const_data.get<peg::any>();
  (void)values.transform<int>();
  peg::Action action(value_action), empty(nullptr);
  action=value_action; action=const_action; action=data_action; action=const_data_action;
  action=MutableAction(); action=MutableConstAction();
  action=MutableDataAction(); action=MutableConstDataAction();
  action=[](peg::SemanticValues&){return 1;};
  action=[](const peg::SemanticValues&){return 1;};
  action=[](peg::SemanticValues&,peg::any&){return 1;};
  action=[](const peg::SemanticValues&,peg::any&){return 1;};
  action=nullptr;
  int value=0;
  rule.parse_and_get_value("a",1,value);
  rule.parse_and_get_value("a",value);
  rule.parse_and_get_value("a",1,data,value);
  rule.parse_and_get_value("a",data,value);
  (rule,value_action);
  parser.parse_n("a",1,value); parser.parse("a",value);
  parser.parse_n("a",1,data,value); parser.parse("a",data,value);
  parser.enable_ast<peg::Ast>();
  std::shared_ptr<peg::Ast> ast;
  (void)peg::ast_to_s(ast);
  (void)peg::AstOptimizer(true).optimize(ast);
  (void)context;
  (void)values.name();
  // 上游未引用的公开构造/重载；此函数不执行，避免改变参考测试行为。
  const std::vector<std::shared_ptr<peg::Ope>> operators{peg::chr('a')};
  const peg::Sequence sequence(operators);
  peg::Sequence copied_sequence(sequence);
  peg::Sequence moved_sequence{std::vector<std::shared_ptr<peg::Ope>>(operators)};
  peg::PrioritizedChoice choice{std::vector<std::shared_ptr<peg::Ope>>(operators)};
  (void)choice.size();
  peg::Definition definition(operators.front());
  peg::Definition moved_definition(std::move(definition));
  (void)rule.parse("a", data);
  peg::parser sized_parser("S <- 'a'", 8);
  (void)parser.load_grammar("S <- 'a'", peg::Rules());
  (void)static_cast<const peg::parser&>(parser)["S"];
  (void)peg::call<peg::any>([](){ return peg::any(1); });
  // 取地址，避免 constexpr 调用被折叠而没有 gcov 函数记录。
  unsigned int (*tag)(const char*, size_t) = &peg::udl::operator "" _;
  (void)tag("S", 1);
}

template struct peg::AstBase<peg::EmptyType>;
template struct peg::scope_exit<std::function<void()>>;
