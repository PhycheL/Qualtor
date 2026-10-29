#include "utf8.h"
#include <string>
template class utf8::iterator<std::string::iterator>;
template class utf8::unchecked::iterator<std::string::iterator>;
// 仅准备阶段编译；把上游测试未引用的 unchecked 重载也纳入冻结分母。
void instantiate_unchecked_replacement(const std::string& input) {
  (void)utf8::unchecked::replace_invalid(input);
  (void)utf8::unchecked::replace_invalid(input, 0xfffd);
}
