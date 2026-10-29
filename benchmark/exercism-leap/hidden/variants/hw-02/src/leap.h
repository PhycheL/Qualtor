#pragma once

namespace leap {

inline bool is_leap_year(int year) {
    return (year % 100) ? (year % 4 == 0) : false;
}

}  // namespace leap
