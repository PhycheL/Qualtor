#include "reverse_string.h"

namespace reverse_string {

std::string reverse_string(const std::string& text) {
    return text.empty() ? text : std::string(text.rbegin() + 1, text.rend());
}

}  // namespace reverse_string
