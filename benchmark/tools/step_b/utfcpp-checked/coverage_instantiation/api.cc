#include "utf8.h"
#include <string>
template class utf8::iterator<std::string::iterator>;
template class utf8::unchecked::iterator<std::string::iterator>;
// 自由函数模板由上游 checked/unchecked API 测试及 CPP11 测试实例化。
