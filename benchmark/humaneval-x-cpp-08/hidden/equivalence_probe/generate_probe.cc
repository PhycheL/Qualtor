// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_08.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_57() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(60LL);
        sd.ints.push_back(9LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 4LL, 20LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 20LL, 4LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 1LL, 0LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 4LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 1LL, 1LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 2LL, 5LL, 60LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 60LL});
        sd.ivecs.push_back(std::vector<long long>{9LL, 9LL, 9LL, 9LL});
    }
    return sd;
}

static const probe::Seeds& seeds_58() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(34LL);
        sd.ints.push_back(653LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(121LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(0LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 3LL, 34LL, 653LL, 2LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 7LL, 1LL, 5LL, 9LL, 653LL, 121LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 5LL, 653LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, 2LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 3LL, 2LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_59() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(13195LL);
        sd.ints.push_back(29LL);
        sd.ints.push_back(2048LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(27LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(63LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(330LL);
        sd.ints.push_back(11LL);
    }
    return sd;
}

static const probe::Seeds& seeds_60() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(30LL);
        sd.ints.push_back(465LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(5050LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(55LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(66LL);
    }
    return sd;
}

static const probe::Seeds& seeds_61() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("(");
        sd.strs.push_back("()");
        sd.strs.push_back("(()())");
        sd.strs.push_back(")(()");
        sd.strs.push_back("()()(()())()");
        sd.strs.push_back("()()((()()())())(()()(()))");
        sd.strs.push_back("((()())))");
        sd.strs.push_back("((((");
        sd.strs.push_back(")");
        sd.strs.push_back("(()");
        sd.strs.push_back("()()(()())())(()");
        sd.strs.push_back("()()(()())()))()");
    }
    return sd;
}

static const probe::Seeds& seeds_62() {
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
        sd.ints.push_back(12LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(16LL);
        sd.reals.push_back(1e-4);
        sd.ivecs.push_back(std::vector<long long>{0LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{2LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 1LL, 2LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 12LL, 20LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL, 1LL, 0LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 2LL, 0LL, 16LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_63() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(24LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(81LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(274LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(927LL);
    }
    return sd;
}

static const probe::Seeds& seeds_64() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(1LL);
        sd.strs.push_back("abcde");
        sd.strs.push_back("ACEDY");
        sd.strs.push_back("Alone");
        sd.strs.push_back("key");
        sd.strs.push_back("bye");
        sd.strs.push_back("keY");
        sd.strs.push_back("bYe");
    }
    return sd;
}

// CPP/57 bool monotonic(vector<float> l)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_57();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("monotonic(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(monotonic(a0)); }, result)) continue;
        probe::emit(out, "monotonic", "bool", call, result);
        ++kept;
    }
}

// CPP/58 vector<int> common(vector<int> l1,vector<int> l2)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_58();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::vector<int> a1 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("common(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(common(a0, a1)); }, result)) continue;
        probe::emit(out, "common", "vec_int", call, result);
        ++kept;
    }
}

// CPP/59 int largest_prime_factor(int n)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_59();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("largest_prime_factor(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(largest_prime_factor(a0)); }, result)) continue;
        probe::emit(out, "largest_prime_factor", "int", call, result);
        ++kept;
    }
}

// CPP/60 int sum_to_n(int n)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_60();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("sum_to_n(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(sum_to_n(a0)); }, result)) continue;
        probe::emit(out, "sum_to_n", "int", call, result);
        ++kept;
    }
}

// CPP/61 bool correct_bracketing(string brackets)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_61();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("correct_bracketing(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(correct_bracketing(a0)); }, result)) continue;
        probe::emit(out, "correct_bracketing", "bool", call, result);
        ++kept;
    }
}

// CPP/62 vector<float> derivative(vector<float> xs)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_62();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("derivative(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(derivative(a0)); }, result)) continue;
        probe::emit(out, "derivative", "vec_float", call, result);
        ++kept;
    }
}

// CPP/63 int fibfib(int n)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_63();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("fibfib(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(fibfib(a0)); }, result)) continue;
        probe::emit(out, "fibfib", "int", call, result);
        ++kept;
    }
}

// CPP/64 int vowels_count(string s)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_64();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("vowels_count(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(vowels_count(a0)); }, result)) continue;
        probe::emit(out, "vowels_count", "int", call, result);
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
