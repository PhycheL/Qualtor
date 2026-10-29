#include <nlohmann/detail/conversions/to_chars.hpp>
// 显式通过公开入口实例化 IEEE-754 float 和 double；不执行。
void instantiate_to_chars(char* first, const char* last) {
  nlohmann::detail::to_chars(first,last,1.0f);
  nlohmann::detail::to_chars(first,last,1.0);
}
