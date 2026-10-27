// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_06.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_41() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(16LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(64LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(100LL);
    }
    return sd;
}

static const probe::Seeds& seeds_42() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(123LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(124LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, 5LL, 2LL, 3LL, 3LL, 9LL, 0LL, 123LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 4LL, 6LL, 3LL, 4LL, 4LL, 10LL, 1LL, 124LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 3LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 2LL, 5LL, 2LL, 3LL, 3LL, 9LL, 0LL, 123LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 3LL, 6LL, 3LL, 4LL, 4LL, 10LL, 1LL, 124LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_43() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(30LL);
        sd.ints.push_back(31LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 5LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, -2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, -5LL, 3LL, 5LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{-3LL, 9LL, -1LL, 3LL, 2LL, 30LL});
        sd.ivecs.push_back(std::vector<long long>{-3LL, 9LL, -1LL, 3LL, 2LL, 31LL});
        sd.ivecs.push_back(std::vector<long long>{-3LL, 9LL, -1LL, 4LL, 2LL, 30LL});
        sd.ivecs.push_back(std::vector<long long>{-3LL, 9LL, -1LL, 4LL, 2LL, 31LL});
    }
    return sd;
}

static const probe::Seeds& seeds_44() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(8LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(22LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(1000LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(111LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(234LL);
        sd.ints.push_back(11101010LL);
        sd.ints.push_back(16LL);
        sd.ints.push_back(10000LL);
        sd.ints.push_back(1LL);
        sd.strs.push_back("22");
        sd.strs.push_back("1000");
        sd.strs.push_back("111");
        sd.strs.push_back("100");
        sd.strs.push_back("11101010");
        sd.strs.push_back("10000");
    }
    return sd;
}

static const probe::Seeds& seeds_45() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(5LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(8LL);
        sd.reals.push_back(7.5);
        sd.reals.push_back(1e-4);
        sd.reals.push_back(2.0);
        sd.reals.push_back(40.0);
    }
    return sd;
}

static const probe::Seeds& seeds_46() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(28LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(104LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(386LL);
    }
    return sd;
}

static const probe::Seeds& seeds_47() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(3LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(1000LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(7LL);
        sd.reals.push_back(15.0);
        sd.reals.push_back(1e-4);
        sd.reals.push_back(-8.0);
        sd.reals.push_back(5.5);
        sd.ivecs.push_back(std::vector<long long>{3LL, 1LL, 2LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{-10LL, 4LL, 6LL, 1000LL, 10LL, 20LL});
        sd.ivecs.push_back(std::vector<long long>{5LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{8LL, 1LL, 3LL, 9LL, 9LL, 2LL, 7LL});
    }
    return sd;
}

static const probe::Seeds& seeds_48() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("");
        sd.strs.push_back("aba");
        sd.strs.push_back("aaaaa");
        sd.strs.push_back("zbcd");
        sd.strs.push_back("xywyx");
        sd.strs.push_back("xywyz");
        sd.strs.push_back("xywzx");
    }
    return sd;
}

// CPP/41 int car_race_collision(int n)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_41();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("car_race_collision(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(car_race_collision(a0)); }, result)) continue;
        probe::emit(out, "car_race_collision", "int", call, result);
        ++kept;
    }
}

// CPP/42 vector<int> incr_list(vector<int> l)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_42();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("incr_list(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(incr_list(a0)); }, result)) continue;
        probe::emit(out, "incr_list", "vec_int", call, result);
        ++kept;
    }
}

// CPP/43 bool pairs_sum_to_zero(vector<int> l)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_43();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("pairs_sum_to_zero(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(pairs_sum_to_zero(a0)); }, result)) continue;
        probe::emit(out, "pairs_sum_to_zero", "bool", call, result);
        ++kept;
    }
}

// CPP/44 string change_base(int x,int base)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_44();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("change_base(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(change_base(a0, a1)); }, result)) continue;
        probe::emit(out, "change_base", "string", call, result);
        ++kept;
    }
}

// CPP/45 float triangle_area(float a,float h)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_45();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        float a0 = probe::gen_float(rng, sd);
        float a1 = probe::gen_float(rng, sd);
        std::string call = std::string("triangle_area(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(triangle_area(a0, a1)); }, result)) continue;
        probe::emit(out, "triangle_area", "float", call, result);
        ++kept;
    }
}

// CPP/46 int fib4(int n)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_46();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("fib4(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(fib4(a0)); }, result)) continue;
        probe::emit(out, "fib4", "int", call, result);
        ++kept;
    }
}

// CPP/47 float median(vector<float> l)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_47();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("median(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(median(a0)); }, result)) continue;
        probe::emit(out, "median", "float", call, result);
        ++kept;
    }
}

// CPP/48 bool is_palindrome(string text)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_48();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("is_palindrome(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(is_palindrome(a0)); }, result)) continue;
        probe::emit(out, "is_palindrome", "bool", call, result);
        ++kept;
    }
}

int main(int argc, char** argv) {
    if (argc != 4) return 2;
    unsigned long long seed = strtoull(argv[1], 0, 10);
    int limit = atoi(argv[2]);
    FILE* out = fopen(argv[3], "w");
    if (!out) return 2;
    probe_0(seed, limit, out);
    probe_1(seed, limit, out);
    probe_2(seed, limit, out);
    probe_3(seed, limit, out);
    probe_4(seed, limit, out);
    probe_5(seed, limit, out);
    probe_6(seed, limit, out);
    probe_7(seed, limit, out);
    fclose(out);
    return 0;
}
