// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_09.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_65() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(12LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(001LL);
        sd.ints.push_back(97LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(79LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(101LL);
        sd.strs.push_back("21");
        sd.strs.push_back("12");
        sd.strs.push_back("001");
        sd.strs.push_back("79");
        sd.strs.push_back("11");
    }
    return sd;
}

static const probe::Seeds& seeds_66() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(131LL);
        sd.ints.push_back(67LL);
        sd.ints.push_back(69LL);
        sd.ints.push_back(153LL);
        sd.ints.push_back(151LL);
        sd.ints.push_back(327LL);
        sd.strs.push_back("");
        sd.strs.push_back("abAB");
        sd.strs.push_back("abcCd");
        sd.strs.push_back("helloE");
        sd.strs.push_back("woArBld");
        sd.strs.push_back("aAaaaXa");
        sd.strs.push_back(" How are yOu?");
        sd.strs.push_back("You arE Very Smart");
    }
    return sd;
}

static const probe::Seeds& seeds_67() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(19LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(95LL);
        sd.ints.push_back(120LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(10LL);
        sd.strs.push_back("5 apples and 6 oranges");
        sd.strs.push_back("0 apples and 1 oranges");
        sd.strs.push_back("2 apples and 3 oranges");
        sd.strs.push_back("100 apples and 1 oranges");
        sd.strs.push_back("1 apples and 0 oranges");
        sd.strs.push_back("1 apples and 100 oranges");
    }
    return sd;
}

static const probe::Seeds& seeds_68() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(10000LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(9LL);
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{4LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 0LL, 3LL, 0LL, 4LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 0LL, 5LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 4LL, 8LL, 4LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{7LL, 6LL, 7LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{7LL, 9LL, 7LL, 1LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_69() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(4LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(10LL);
        sd.ivecs.push_back(std::vector<long long>{4LL, 1LL, 2LL, 2LL, 3LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 2LL, 3LL, 3LL, 3LL, 4LL, 4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 5LL, 4LL, 4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 5LL, 5LL, 5LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 1LL, 4LL, 1LL, 4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{8LL, 8LL, 8LL, 8LL, 8LL, 8LL, 8LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 3LL, 2LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 7LL, 8LL, 8LL, 4LL, 8LL, 7LL, 3LL, 9LL, 6LL, 5LL, 10LL, 4LL, 3LL, 6LL, 7LL, 1LL, 7LL, 4LL, 10LL, 8LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL, 8LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 7LL, 1LL, 8LL, 8LL, 10LL, 5LL, 8LL, 5LL, 3LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{8LL, 8LL, 3LL, 6LL, 5LL, 6LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 9LL, 6LL, 7LL, 1LL, 4LL, 7LL, 1LL, 8LL, 8LL, 9LL, 8LL, 10LL, 10LL, 8LL, 4LL, 10LL, 4LL, 10LL, 1LL, 2LL, 9LL, 5LL, 7LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 9LL, 10LL, 1LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 9LL, 7LL, 5LL, 8LL, 7LL, 5LL, 3LL, 7LL, 5LL, 10LL, 10LL, 3LL, 6LL, 10LL, 2LL, 8LL, 6LL, 5LL, 4LL, 9LL, 5LL, 3LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{8LL, 8LL, 10LL, 6LL, 4LL, 3LL, 5LL, 8LL, 2LL, 4LL, 2LL, 8LL, 4LL, 6LL, 10LL, 4LL, 2LL, 1LL, 10LL, 2LL, 1LL, 1LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 10LL, 4LL, 8LL, 2LL, 10LL, 5LL, 1LL, 2LL, 9LL, 5LL, 5LL, 6LL, 3LL, 8LL, 6LL, 4LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 6LL, 10LL, 1LL, 6LL, 9LL, 10LL, 8LL, 6LL, 8LL, 7LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{9LL, 2LL, 4LL, 1LL, 5LL, 1LL, 5LL, 2LL, 5LL, 7LL, 7LL, 7LL, 3LL, 10LL, 1LL, 5LL, 4LL, 2LL, 8LL, 4LL, 1LL, 9LL, 10LL, 7LL, 10LL, 2LL, 8LL, 10LL, 9LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 6LL, 4LL, 2LL, 8LL, 7LL, 5LL, 6LL, 4LL, 10LL, 4LL, 6LL, 3LL, 7LL, 8LL, 8LL, 3LL, 1LL, 4LL, 2LL, 2LL, 10LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{9LL, 8LL, 6LL, 10LL, 2LL, 6LL, 10LL, 2LL, 7LL, 8LL, 10LL, 3LL, 8LL, 2LL, 6LL, 2LL, 3LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 5LL, 3LL, 9LL, 5LL, 6LL, 3LL, 2LL, 8LL, 5LL, 6LL, 10LL, 10LL, 6LL, 8LL, 4LL, 10LL, 7LL, 7LL, 10LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{10LL});
        sd.ivecs.push_back(std::vector<long long>{9LL, 7LL, 7LL, 2LL, 4LL, 7LL, 2LL, 10LL, 9LL, 7LL, 5LL, 7LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 4LL, 10LL, 2LL, 1LL, 1LL, 10LL, 3LL, 6LL, 1LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{7LL, 9LL, 9LL, 9LL, 3LL, 4LL, 1LL, 5LL, 9LL, 1LL, 2LL, 1LL, 1LL, 10LL, 7LL, 5LL, 6LL, 7LL, 6LL, 7LL, 7LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 10LL, 10LL, 9LL, 2LL});
    }
    return sd;
}

static const probe::Seeds& seeds_70() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(111111LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 5LL, 5LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{5LL, 6LL, 7LL, 8LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 9LL, 6LL, 8LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 5LL, 2LL, 4LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 6LL, 7LL, 8LL, 9LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 9LL, 5LL, 8LL, 6LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 6LL, 7LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 8LL, 2LL, 7LL, 3LL, 6LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 2LL, 2LL, 2LL, 5LL, 5LL, -5LL, -5LL});
        sd.ivecs.push_back(std::vector<long long>{-5LL, 5LL, -5LL, 5LL, 0LL, 2LL, 2LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{111111LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_71() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(6LL);
        sd.reals.push_back(6.00);
        sd.reals.push_back(-6.00);
        sd.reals.push_back(0.01);
        sd.reals.push_back(-8.18);
        sd.reals.push_back(-1.73);
        sd.reals.push_back(16.25);
        sd.reals.push_back(-0.43);
    }
    return sd;
}

static const probe::Seeds& seeds_72() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(6LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL});
    }
    return sd;
}

// CPP/65 string circular_shift(int x,int shift)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_65();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("circular_shift(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(circular_shift(a0, a1)); }, result)) continue;
        probe::emit(out, "circular_shift", "string", call, result);
        ++kept;
    }
}

// CPP/66 int digitSum(string s)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_66();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("digitSum(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(digitSum(a0)); }, result)) continue;
        probe::emit(out, "digitSum", "int", call, result);
        ++kept;
    }
}

// CPP/67 int fruit_distribution(string s,int n)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_67();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("fruit_distribution(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(fruit_distribution(a0, a1)); }, result)) continue;
        probe::emit(out, "fruit_distribution", "int", call, result);
        ++kept;
    }
}

// CPP/68 vector<int> pluck(vector<int> arr)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_68();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("pluck(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(pluck(a0)); }, result)) continue;
        probe::emit(out, "pluck", "vec_int", call, result);
        ++kept;
    }
}

// CPP/69 int search(vector<int> lst)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_69();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("search(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(search(a0)); }, result)) continue;
        probe::emit(out, "search", "int", call, result);
        ++kept;
    }
}

// CPP/70 vector<int> strange_sort_list(vector<int> lst)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_70();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("strange_sort_list(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(strange_sort_list(a0)); }, result)) continue;
        probe::emit(out, "strange_sort_list", "vec_int", call, result);
        ++kept;
    }
}

// CPP/71 float triangle_area(float a,float b,float c)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_71();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        float a0 = probe::gen_float(rng, sd);
        float a1 = probe::gen_float(rng, sd);
        float a2 = probe::gen_float(rng, sd);
        std::string call = std::string("triangle_area(") + probe::lit(a0) + ", " + probe::lit(a1) + ", " + probe::lit(a2) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(triangle_area(a0, a1, a2)); }, result)) continue;
        probe::emit(out, "triangle_area", "float", call, result);
        ++kept;
    }
}

// CPP/72 bool will_it_fly(vector<int> q,int w)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_72();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("will_it_fly(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(will_it_fly(a0, a1)); }, result)) continue;
        probe::emit(out, "will_it_fly", "bool", call, result);
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
