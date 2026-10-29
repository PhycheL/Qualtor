#pragma once

namespace leap {

inline bool is_leap_year(int year) {
    return year % 4 == 0;
}

}  // namespace leap
