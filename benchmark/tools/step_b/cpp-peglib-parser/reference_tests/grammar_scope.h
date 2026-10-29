#pragma once
#include <peglib.h>
#include <utility>
#include <vector>

// 上游语法调试测试的 Grammar 副本故意不复制语义动作，但会把共享
// Holder::outer_ 指向副本。只恢复这些测试改动的指针，不改变业务代码。
class GlobalGrammarScope : private peg::Ope::Visitor {
 public:
  GlobalGrammarScope() {
    for (auto& rule : peg::ParserGenerator::grammar()) rule.second.accept(*this);
  }
  ~GlobalGrammarScope() {
    for (const auto& saved : saved_) saved.first->outer_ = saved.second;
  }
 private:
  void visit(peg::Holder& holder) override {
    saved_.push_back(std::make_pair(&holder, holder.outer_));
  }
  std::vector<std::pair<peg::Holder*, peg::Definition*>> saved_;
};
