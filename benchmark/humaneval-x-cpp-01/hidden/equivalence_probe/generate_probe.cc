// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_01.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_0() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.reals.push_back(1.0);
        sd.reals.push_back(2.0);
        sd.reals.push_back(3.0);
        sd.reals.push_back(0.5);
        sd.reals.push_back(2.8);
        sd.reals.push_back(4.0);
        sd.reals.push_back(5.0);
        sd.reals.push_back(0.3);
        sd.reals.push_back(3.9);
        sd.reals.push_back(2.2);
        sd.reals.push_back(0.05);
        sd.reals.push_back(5.9);
        sd.reals.push_back(0.95);
        sd.reals.push_back(0.8);
        sd.reals.push_back(1.1);
        sd.reals.push_back(3.1);
        sd.reals.push_back(4.1);
        sd.reals.push_back(5.1);
        sd.strs.push_back("failure 1");
        sd.strs.push_back("failure 2");
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.0});
        sd.fvecs.push_back(std::vector<double>{1.0, 2.8, 3.0, 4.0, 5.0, 2.0});
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.9, 4.0, 5.0, 2.2});
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 5.9, 4.0, 5.0});
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0});
        sd.fvecs.push_back(std::vector<double>{1.1, 2.2, 3.1, 4.1, 5.1});
    }
    return sd;
}

static const probe::Seeds& seeds_1() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.strs.push_back("( ) (( )) (( )( ))");
        sd.strs.push_back("()");
        sd.strs.push_back("(())");
        sd.strs.push_back("(()())");
        sd.strs.push_back("(()()) ((())) () ((())()())");
        sd.strs.push_back("((()))");
        sd.strs.push_back("((())()())");
        sd.strs.push_back("() (()) ((())) (((())))");
        sd.strs.push_back("(((())))");
        sd.strs.push_back("(()(())((())))");
        sd.svecs.push_back(std::vector<std::string>{"()", "(())", "(()())"});
        sd.svecs.push_back(std::vector<std::string>{"(()())", "((()))", "()", "((())()())"});
        sd.svecs.push_back(std::vector<std::string>{"()", "(())", "((()))", "(((())))"});
        sd.svecs.push_back(std::vector<std::string>{"(()(())((())))"});
    }
    return sd;
}

static const probe::Seeds& seeds_2() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.reals.push_back(3.5);
        sd.reals.push_back(0.5);
        sd.reals.push_back(1.33);
        sd.reals.push_back(0.33);
        sd.reals.push_back(1e-4);
        sd.reals.push_back(123.456);
        sd.reals.push_back(0.456);
    }
    return sd;
}

static const probe::Seeds& seeds_3() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(-4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(4LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, -4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, -3LL, 1LL, 2LL, -3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, -4LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, -1LL, 2LL, -2LL, 5LL, -5LL, 4LL, -4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, -1LL, 2LL, -2LL, 5LL, -5LL, 4LL, -5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, -2LL, 2LL, -2LL, 5LL, -5LL, 4LL, -4LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_4() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.reals.push_back(1.0);
        sd.reals.push_back(2.0);
        sd.reals.push_back(3.0);
        sd.reals.push_back(4.0);
        sd.reals.push_back(1e-4);
        sd.reals.push_back(5.0);
        sd.reals.push_back(6.0);
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.0, 4.0});
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.0});
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0});
    }
    return sd;
}

static const probe::Seeds& seeds_5() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(4LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(8LL);
        sd.strs.push_back("delimeter");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 2LL, 4LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 6LL, 3LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 8LL, 6LL, 8LL, 3LL, 8LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 2LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 2LL, 2LL, 2LL, 2LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_6() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(4LL);
        sd.strs.push_back("(()()) ((())) () ((())()())");
        sd.strs.push_back("() (()) ((())) (((())))");
        sd.strs.push_back("(()(())((())))");
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 1LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{4LL});
    }
    return sd;
}

static const probe::Seeds& seeds_7() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.strs.push_back("a");
        sd.strs.push_back("abc");
        sd.strs.push_back("bacd");
        sd.strs.push_back("cde");
        sd.strs.push_back("vector");
        sd.strs.push_back("john");
        sd.strs.push_back("xxx");
        sd.strs.push_back("asd");
        sd.strs.push_back("xxy");
        sd.strs.push_back("john doe");
        sd.strs.push_back("xxxAAA");
        sd.strs.push_back("aaaxxy");
        sd.strs.push_back("xx");
        sd.strs.push_back("grunt");
        sd.strs.push_back("trumpet");
        sd.strs.push_back("prune");
        sd.strs.push_back("gruesome");
        sd.strs.push_back("run");
        sd.strs.push_back("array");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"abc", "bacd", "cde", "vector"});
        sd.svecs.push_back(std::vector<std::string>{"abc", "bacd", "vector"});
        sd.svecs.push_back(std::vector<std::string>{"xxx", "asd", "xxy", "john doe", "xxxAAA", "xxx"});
        sd.svecs.push_back(std::vector<std::string>{"xxx", "xxxAAA", "xxx"});
        sd.svecs.push_back(std::vector<std::string>{"xxx", "asd", "aaaxxy", "john doe", "xxxAAA", "xxx"});
        sd.svecs.push_back(std::vector<std::string>{"xxx", "aaaxxy", "xxxAAA", "xxx"});
        sd.svecs.push_back(std::vector<std::string>{"grunt", "trumpet", "prune", "gruesome"});
        sd.svecs.push_back(std::vector<std::string>{"grunt", "prune"});
        sd.svecs.push_back(std::vector<std::string>{"abc", "bacd", "cde", "array"});
        sd.svecs.push_back(std::vector<std::string>{"abc", "bacd", "array"});
    }
    return sd;
}

// CPP/0 bool has_close_elements(vector<float> numbers, float threshold)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_0();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        float a1 = probe::gen_float(rng, sd);
        std::string call = std::string("has_close_elements(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(has_close_elements(a0, a1)); }, result)) continue;
        probe::emit(out, "has_close_elements", "bool", call, result);
        ++kept;
    }
}

// CPP/1 vector<string> separate_paren_groups(string paren_string)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_1();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("separate_paren_groups(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(separate_paren_groups(a0)); }, result)) continue;
        probe::emit(out, "separate_paren_groups", "vec_string", call, result);
        ++kept;
    }
}

// CPP/2 float truncate_number(float number)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_2();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        float a0 = probe::gen_float(rng, sd);
        std::string call = std::string("truncate_number(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(truncate_number(a0)); }, result)) continue;
        probe::emit(out, "truncate_number", "float", call, result);
        ++kept;
    }
}

// CPP/3 bool below_zero(vector<int> operations)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_3();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("below_zero(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(below_zero(a0)); }, result)) continue;
        probe::emit(out, "below_zero", "bool", call, result);
        ++kept;
    }
}

// CPP/4 float mean_absolute_deviation(vector<float> numbers)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_4();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("mean_absolute_deviation(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(mean_absolute_deviation(a0)); }, result)) continue;
        probe::emit(out, "mean_absolute_deviation", "float", call, result);
        ++kept;
    }
}

// CPP/5 vector<int> intersperse(vector<int> numbers, int delimeter)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_5();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("intersperse(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(intersperse(a0, a1)); }, result)) continue;
        probe::emit(out, "intersperse", "vec_int", call, result);
        ++kept;
    }
}

// CPP/6 vector<int> parse_nested_parens(string paren_string)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_6();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("parse_nested_parens(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(parse_nested_parens(a0)); }, result)) continue;
        probe::emit(out, "parse_nested_parens", "vec_int", call, result);
        ++kept;
    }
}

// CPP/7 vector<string> filter_by_substring(vector<string> strings, string substring)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_7();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::string> a0 = probe::gen_vec_string(rng, sd);
        std::string a1 = probe::gen_string(rng, sd);
        std::string call = std::string("filter_by_substring(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(filter_by_substring(a0, a1)); }, result)) continue;
        probe::emit(out, "filter_by_substring", "vec_string", call, result);
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
