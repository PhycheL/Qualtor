// Parrot 探针生成器：枚举种类、椰子数、电压与是否被钉住，在子进程中执行 getSpeed 与 getCry，记录实际结果。
// 由 benchmark/tools/build_katas.py 复制到题目 hidden/equivalence_probe/generate_probe.cc 并在出题时运行。
#include "Parrot.h"
#include "probe_prelude.h"

int main(int argc, char** argv) {
    if (argc != 4) return 2;
    FILE* out = fopen(argv[3], "w");
    if (!out) return 2;
    static const char* const kTypes[] = {"EUROPEAN", "AFRICAN", "NORWEGIAN_BLUE"};
    static const double kVoltages[] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0};
    struct Input { int type; int coconuts; double voltage; bool nailed; };
    std::vector<Input> inputs;
    for (int t = 0; t < 3; ++t)
        for (int c = 0; c <= 5; ++c)
            for (int v = 0; v < 8; ++v)
                for (int n = 0; n < 2; ++n) {
                    Input in = {t, c, kVoltages[v], n == 1};
                    inputs.push_back(in);
                }
    probe::Rng rng(strtoull(argv[1], 0, 10));
    for (size_t i = inputs.size(); i > 1; --i) std::swap(inputs[i - 1], inputs[rng.below(static_cast<int>(i))]);
    for (size_t i = 0; i < inputs.size(); ++i) {
        const Input in = inputs[i];
        std::string ctor = std::string("Parrot(") + kTypes[in.type] + ", " + probe::lit(in.coconuts) + ", " +
                           probe::lit(in.voltage) + ", " + probe::lit(in.nailed) + ")";
        std::string result;
        if (probe::run_case([&]() {
                return probe::lit(Parrot(static_cast<ParrotType>(in.type), in.coconuts, in.voltage, in.nailed).getSpeed());
            }, result))
            probe::emit(out, "getSpeed", "double", ctor + ".getSpeed()", result);
        if (probe::run_case([&]() {
                return probe::lit(std::string(Parrot(static_cast<ParrotType>(in.type), in.coconuts, in.voltage, in.nailed).getCry()));
            }, result))
            probe::emit(out, "getCry", "string", ctor + ".getCry()", result);
    }
    fclose(out);
    return 0;
}
