// Tennis 探针生成器：枚举两名选手 0–15 分的全部组合，在子进程中执行 tennis_score，记录实际结果。
// 由 benchmark/tools/build_katas.py 复制到各题 hidden/equivalence_probe/generate_probe.cc 并在出题时运行。
#include "tennis.h"
#include "probe_prelude.h"

int main(int argc, char** argv) {
    if (argc != 4) return 2;
    FILE* out = fopen(argv[3], "w");
    if (!out) return 2;
    std::vector<std::pair<int, int> > inputs;
    for (int a = 0; a <= 15; ++a)
        for (int b = 0; b <= 15; ++b) inputs.push_back(std::make_pair(a, b));
    probe::Rng rng(strtoull(argv[1], 0, 10));
    for (size_t i = inputs.size(); i > 1; --i) std::swap(inputs[i - 1], inputs[rng.below(static_cast<int>(i))]);
    for (size_t i = 0; i < inputs.size(); ++i) {
        int a = inputs[i].first, b = inputs[i].second;
        std::string call = "tennis_score(" + probe::lit(a) + ", " + probe::lit(b) + ")";
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(std::string(tennis_score(a, b))); }, result)) continue;
        probe::emit(out, "tennis_score", "string", call, result);
    }
    fclose(out);
    return 0;
}
