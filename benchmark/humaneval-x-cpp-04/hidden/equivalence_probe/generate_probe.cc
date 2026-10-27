// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_04.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_25() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(8LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(25LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(70LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(19LL);
        sd.ivecs.push_back(std::vector<long long>{2LL, 2LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 5LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{2LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 19LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 3LL, 19LL, 19LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 3LL, 3LL, 19LL, 19LL, 19LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 19LL, 19LL, 19LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 3LL});
    }
    return sd;
}

static const probe::Seeds& seeds_26() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(5LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 2LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 2LL, 4LL, 3LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 5LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_27() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("Hello");
        sd.strs.push_back("hELLO");
        sd.strs.push_back("");
        sd.strs.push_back("Hello!");
        sd.strs.push_back("hELLO!");
        sd.strs.push_back("These violent delights have violent ends");
        sd.strs.push_back("tHESE VIOLENT DELIGHTS HAVE VIOLENT ENDS");
    }
    return sd;
}

static const probe::Seeds& seeds_28() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("");
        sd.strs.push_back("a");
        sd.strs.push_back("b");
        sd.strs.push_back("c");
        sd.strs.push_back("abc");
        sd.strs.push_back("x");
        sd.strs.push_back("y");
        sd.strs.push_back("z");
        sd.strs.push_back("xyz");
        sd.strs.push_back("w");
        sd.strs.push_back("k");
        sd.strs.push_back("xyzwk");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"a", "b", "c"});
        sd.svecs.push_back(std::vector<std::string>{"x", "y", "z"});
        sd.svecs.push_back(std::vector<std::string>{"x", "y", "z", "w", "k"});
    }
    return sd;
}

static const probe::Seeds& seeds_29() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.strs.push_back("a");
        sd.strs.push_back("abc");
        sd.strs.push_back("bcd");
        sd.strs.push_back("cde");
        sd.strs.push_back("vector");
        sd.strs.push_back("john");
        sd.strs.push_back("xxx");
        sd.strs.push_back("asd");
        sd.strs.push_back("xxy");
        sd.strs.push_back("john doe");
        sd.strs.push_back("xxxAAA");
        sd.strs.push_back("array");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"abc", "bcd", "cde", "vector"});
        sd.svecs.push_back(std::vector<std::string>{"abc", "vector"});
        sd.svecs.push_back(std::vector<std::string>{"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"});
        sd.svecs.push_back(std::vector<std::string>{"xxx", "xxxAAA", "xxx"});
        sd.svecs.push_back(std::vector<std::string>{"abc", "bcd", "cde", "array"});
        sd.svecs.push_back(std::vector<std::string>{"abc", "array"});
    }
    return sd;
}

static const probe::Seeds& seeds_30() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(-1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(-4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(123LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(4LL);
        sd.reals.push_back(1e-4);
        sd.ivecs.push_back(std::vector<long long>{-1LL, 2LL, -4LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, -5LL, 2LL, -3LL, 3LL, 9LL, 0LL, 123LL, 1LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, 2LL, 3LL, 9LL, 123LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -2LL, 4LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, -5LL, 2LL, 3LL, 3LL, 9LL, 0LL, 123LL, 1LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 3LL, 2LL, 3LL, 3LL, 9LL, 123LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -2LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_31() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(6LL);
        sd.ints.push_back(101LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(13441LL);
        sd.ints.push_back(61LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(17LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(19LL);
    }
    return sd;
}

static const probe::Seeds& seeds_32() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(-6LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(-1LL);
        sd.reals.push_back(-0.5);
        sd.reals.push_back(1.0);
        sd.reals.push_back(1e-3);
        sd.reals.push_back(0.5);
        sd.reals.push_back(1e-4);
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{-6LL, 11LL, -6LL, 1LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

// CPP/25 vector<int> factorize(int n)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_25();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("factorize(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(factorize(a0)); }, result)) continue;
        probe::emit(out, "factorize", "vec_int", call, result);
        ++kept;
    }
}

// CPP/26 vector<int> remove_duplicates(vector<int> numbers)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_26();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("remove_duplicates(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(remove_duplicates(a0)); }, result)) continue;
        probe::emit(out, "remove_duplicates", "vec_int", call, result);
        ++kept;
    }
}

// CPP/27 string filp_case(string str)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_27();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("filp_case(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(filp_case(a0)); }, result)) continue;
        probe::emit(out, "filp_case", "string", call, result);
        ++kept;
    }
}

// CPP/28 string concatenate(vector<string> strings)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_28();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::string> a0 = probe::gen_vec_string(rng, sd);
        std::string call = std::string("concatenate(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(concatenate(a0)); }, result)) continue;
        probe::emit(out, "concatenate", "string", call, result);
        ++kept;
    }
}

// CPP/29 vector<string> filter_by_prefix(vector<string> strings, string prefix)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_29();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::string> a0 = probe::gen_vec_string(rng, sd);
        std::string a1 = probe::gen_string(rng, sd);
        std::string call = std::string("filter_by_prefix(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(filter_by_prefix(a0, a1)); }, result)) continue;
        probe::emit(out, "filter_by_prefix", "vec_string", call, result);
        ++kept;
    }
}

// CPP/30 vector<float> get_positive(vector<float> l)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_30();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("get_positive(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(get_positive(a0)); }, result)) continue;
        probe::emit(out, "get_positive", "vec_float", call, result);
        ++kept;
    }
}

// CPP/31 bool is_prime(long long n)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_31();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        long long a0 = probe::gen_ll(rng, sd);
        std::string call = std::string("is_prime(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(is_prime(a0)); }, result)) continue;
        probe::emit(out, "is_prime", "bool", call, result);
        ++kept;
    }
}

// CPP/32 double poly(vector<double> xs, double x)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_32();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<double> a0 = probe::gen_vec_double(rng, sd);
        double a1 = probe::gen_double(rng, sd);
        std::string call = std::string("poly(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(poly(a0, a1)); }, result)) continue;
        probe::emit(out, "poly", "double", call, result);
        ++kept;
    }
}

// CPP/32 double find_zero(vector<double> xs)
static void probe_8(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 8ULL);
    const probe::Seeds& sd = seeds_32();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<double> a0 = probe::gen_vec_double(rng, sd);
        std::string call = std::string("find_zero(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(find_zero(a0)); }, result)) continue;
        probe::emit(out, "find_zero", "double", call, result);
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
