// 由 Qualtor 添加：上游 tennis7.cc 没有头文件，这里按其定义声明 tennis_score，供测试包含。
#ifndef TENNIS_H
#define TENNIS_H

#include <string>

std::string tennis_score(int p1Score, int p2Score);

#endif  // TENNIS_H
