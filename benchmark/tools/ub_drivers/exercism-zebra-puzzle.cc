// ub_sweep.py 的驱动：在同一进程内调用两次 solve()（全局状态会保留到第二次），输出可观察结果。
#include <cstdio>

#include "zebra_puzzle.h"

int main() {
    for (int k = 0; k < 2; ++k) {
        zebra_puzzle::Solution s = zebra_puzzle::solve();
        std::printf("%s|%s\n", s.drinksWater.c_str(), s.ownsZebra.c_str());
    }
}
