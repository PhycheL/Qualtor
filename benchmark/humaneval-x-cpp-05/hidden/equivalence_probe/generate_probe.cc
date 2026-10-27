// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_05.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_33() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(123LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(-12LL);
        sd.ints.push_back(23LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(12LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 6LL, 3LL, 4LL, 8LL, 9LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 6LL, 3LL, 4LL, 8LL, 9LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, -5LL, 2LL, -3LL, 3LL, 9LL, 0LL, 123LL, 1LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 8LL, -12LL, 4LL, 23LL, 2LL, 3LL, 11LL, 12LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 8LL, 3LL, 4LL, 6LL, 9LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 8LL, 3LL, 4LL, 6LL, 9LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 6LL, 9LL, 4LL, 8LL, 3LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 6LL, 9LL, 4LL, 8LL, 3LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 6LL, 3LL, 4LL, 8LL, 9LL, 2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 6LL, 3LL, 4LL, 8LL, 9LL, 5LL, 1LL});
    }
    return sd;
}

static const probe::Seeds& seeds_34() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(5LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(123LL);
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, 5LL, 2LL, 3LL, 3LL, 9LL, 0LL, 123LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 2LL, 3LL, 5LL, 9LL, 123LL});
    }
    return sd;
}

static const probe::Seeds& seeds_35() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(123LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(124LL);
        sd.reals.push_back(1e-4);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, -5LL, 2LL, -3LL, 3LL, 9LL, 0LL, 123LL, 1LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, -5LL, 2LL, -3LL, 3LL, 9LL, 0LL, 124LL, 1LL, -10LL});
    }
    return sd;
}

static const probe::Seeds& seeds_36() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(7LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(50LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(78LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(79LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(200LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(4000LL);
        sd.ints.push_back(192LL);
        sd.ints.push_back(10000LL);
        sd.ints.push_back(639LL);
        sd.ints.push_back(100000LL);
        sd.ints.push_back(8026LL);
    }
    return sd;
}

static const probe::Seeds& seeds_37() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(123LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(-12LL);
        sd.ints.push_back(23LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(12LL);
        sd.reals.push_back(1e-4);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 6LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 6LL, 5LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, -5LL, 2LL, -3LL, 3LL, 9LL, 0LL, 123LL, 1LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{-10LL, 3LL, -5LL, 2LL, -3LL, 3LL, 5LL, 0LL, 9LL, 1LL, 123LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 8LL, -12LL, 4LL, 23LL, 2LL, 3LL, 11LL, 12LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{-12LL, 8LL, 3LL, 4LL, 5LL, 2LL, 12LL, 11LL, 23LL, -10LL});
    }
    return sd;
}

static const probe::Seeds& seeds_38() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(97LL);
        sd.ints.push_back(26LL);
        sd.strs.push_back("");
    }
    return sd;
}

static const probe::Seeds& seeds_39() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(89LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(233LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(1597LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(28657LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(514229LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(433494437LL);
    }
    return sd;
}

static const probe::Seeds& seeds_40() {
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
        sd.ints.push_back(9LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-100LL);
        sd.ints.push_back(100LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 5LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, -2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, -5LL, 3LL, 9LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 5LL, -1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 5LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 5LL, -100LL});
        sd.ivecs.push_back(std::vector<long long>{100LL, 3LL, 5LL, -100LL});
    }
    return sd;
}

// CPP/33 vector<int> sort_third(vector<int> l)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_33();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("sort_third(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(sort_third(a0)); }, result)) continue;
        probe::emit(out, "sort_third", "vec_int", call, result);
        ++kept;
    }
}

// CPP/34 vector<int> unique(vector<int> l)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_34();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("unique(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(unique(a0)); }, result)) continue;
        probe::emit(out, "unique", "vec_int", call, result);
        ++kept;
    }
}

// CPP/35 float max_element(vector<float> l)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_35();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("max_element(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(max_element(a0)); }, result)) continue;
        probe::emit(out, "max_element", "float", call, result);
        ++kept;
    }
}

// CPP/36 int fizz_buzz(int n)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_36();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("fizz_buzz(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(fizz_buzz(a0)); }, result)) continue;
        probe::emit(out, "fizz_buzz", "int", call, result);
        ++kept;
    }
}

// CPP/37 vector<float> sort_even(vector<float> l)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_37();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("sort_even(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(sort_even(a0)); }, result)) continue;
        probe::emit(out, "sort_even", "vec_float", call, result);
        ++kept;
    }
}

// CPP/38 string encode_cyclic(string s)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_38();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("encode_cyclic(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(encode_cyclic(a0)); }, result)) continue;
        probe::emit(out, "encode_cyclic", "string", call, result);
        ++kept;
    }
}

// CPP/38 string decode_cyclic(string s)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_38();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("decode_cyclic(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(decode_cyclic(a0)); }, result)) continue;
        probe::emit(out, "decode_cyclic", "string", call, result);
        ++kept;
    }
}

// CPP/39 int prime_fib(int n)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_39();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("prime_fib(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(prime_fib(a0)); }, result)) continue;
        probe::emit(out, "prime_fib", "int", call, result);
        ++kept;
    }
}

// CPP/40 bool triples_sum_to_zero(vector<int> l)
static void probe_8(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 8ULL);
    const probe::Seeds& sd = seeds_40();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("triples_sum_to_zero(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(triples_sum_to_zero(a0)); }, result)) continue;
        probe::emit(out, "triples_sum_to_zero", "bool", call, result);
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
    probe_8(seed, limit, out);
    fclose(out);
    return 0;
}
