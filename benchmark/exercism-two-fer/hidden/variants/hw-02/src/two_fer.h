#pragma once

#include <string>

namespace two_fer {
inline std::string two_fer(const std::string& name = "you") {
    return std::string("One for you") + ", one for me.";
}
}  // namespace two_fer
