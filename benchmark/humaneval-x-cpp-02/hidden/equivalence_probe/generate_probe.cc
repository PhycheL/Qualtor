// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_02.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_8() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(24LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{100LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 5LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{10LL});
        sd.ivecs.push_back(std::vector<long long>{10LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{10LL, 24LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_9() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(100LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 2LL, 3LL, 4LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 3LL, 3LL, 4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 3LL, 2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 4LL, 4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL, 3LL, 100LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 3LL, 3LL, 100LL, 100LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_10() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("");
        sd.strs.push_back("cat");
        sd.strs.push_back("catac");
        sd.strs.push_back("cata");
        sd.strs.push_back("x");
        sd.strs.push_back("xyz");
        sd.strs.push_back("xyzyx");
        sd.strs.push_back("xyx");
        sd.strs.push_back("jerry");
        sd.strs.push_back("jerryrrej");
    }
    return sd;
}

static const probe::Seeds& seeds_11() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(010LL);
        sd.ints.push_back(110LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(111000LL);
        sd.ints.push_back(101010LL);
        sd.ints.push_back(010010LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(0101LL);
        sd.ints.push_back(0000LL);
        sd.strs.push_back("010");
        sd.strs.push_back("110");
        sd.strs.push_back("100");
        sd.strs.push_back("111000");
        sd.strs.push_back("101010");
        sd.strs.push_back("010010");
        sd.strs.push_back("1");
        sd.strs.push_back("0");
        sd.strs.push_back("0101");
        sd.strs.push_back("0000");
    }
    return sd;
}

static const probe::Seeds& seeds_12() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("a");
        sd.strs.push_back("b");
        sd.strs.push_back("c");
        sd.strs.push_back("bb");
        sd.strs.push_back("ccc");
        sd.strs.push_back("");
        sd.strs.push_back("x");
        sd.strs.push_back("y");
        sd.strs.push_back("z");
        sd.strs.push_back("yyy");
        sd.strs.push_back("zzzz");
        sd.strs.push_back("www");
        sd.strs.push_back("kkkk");
        sd.strs.push_back("abc");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"a", "b", "c"});
        sd.svecs.push_back(std::vector<std::string>{"a", "bb", "ccc"});
        sd.svecs.push_back(std::vector<std::string>{"x", "y", "z"});
        sd.svecs.push_back(std::vector<std::string>{"x", "yyy", "zzzz", "www", "kkkk", "abc"});
    }
    return sd;
}

static const probe::Seeds& seeds_13() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(25LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(49LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(144LL);
        sd.ints.push_back(60LL);
        sd.ints.push_back(12LL);
    }
    return sd;
}

static const probe::Seeds& seeds_14() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.strs.push_back("abc");
        sd.strs.push_back("a");
        sd.strs.push_back("ab");
        sd.strs.push_back("");
        sd.strs.push_back("asdfgh");
        sd.strs.push_back("as");
        sd.strs.push_back("asd");
        sd.strs.push_back("asdf");
        sd.strs.push_back("asdfg");
        sd.strs.push_back("WWW");
        sd.strs.push_back("W");
        sd.strs.push_back("WW");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{"a", "ab", "abc"});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"a", "as", "asd", "asdf", "asdfg", "asdfgh"});
        sd.svecs.push_back(std::vector<std::string>{"W", "WW", "WWW"});
    }
    return sd;
}

static const probe::Seeds& seeds_15() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.strs.push_back("0");
        sd.strs.push_back("0 1 2 3 4 5");
        sd.strs.push_back("0 1 2 3");
        sd.strs.push_back("0 1 2 3 4 5 6 7 8 9 10");
    }
    return sd;
}

// CPP/8 vector<int> sum_product(vector<int> numbers)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_8();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("sum_product(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(sum_product(a0)); }, result)) continue;
        probe::emit(out, "sum_product", "vec_int", call, result);
        ++kept;
    }
}

// CPP/9 vector<int> rolling_max(vector<int> numbers)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_9();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("rolling_max(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(rolling_max(a0)); }, result)) continue;
        probe::emit(out, "rolling_max", "vec_int", call, result);
        ++kept;
    }
}

// CPP/10 bool is_palindrome(string str)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_10();
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

// CPP/10 string make_palindrome(string str)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_10();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("make_palindrome(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(make_palindrome(a0)); }, result)) continue;
        probe::emit(out, "make_palindrome", "string", call, result);
        ++kept;
    }
}

// CPP/11 string string_xor(string a,string b)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_11();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string a1 = probe::gen_string(rng, sd);
        std::string call = std::string("string_xor(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(string_xor(a0, a1)); }, result)) continue;
        probe::emit(out, "string_xor", "string", call, result);
        ++kept;
    }
}

// CPP/12 string longest(vector<string> strings)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_12();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::string> a0 = probe::gen_vec_string(rng, sd);
        std::string call = std::string("longest(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(longest(a0)); }, result)) continue;
        probe::emit(out, "longest", "string", call, result);
        ++kept;
    }
}

// CPP/13 int greatest_common_divisor(int a, int b)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_13();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("greatest_common_divisor(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(greatest_common_divisor(a0, a1)); }, result)) continue;
        probe::emit(out, "greatest_common_divisor", "int", call, result);
        ++kept;
    }
}

// CPP/14 vector<string> all_prefixes(string str)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_14();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("all_prefixes(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(all_prefixes(a0)); }, result)) continue;
        probe::emit(out, "all_prefixes", "vec_string", call, result);
        ++kept;
    }
}

// CPP/15 string string_sequence(int n)
static void probe_8(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 8ULL);
    const probe::Seeds& sd = seeds_15();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("string_sequence(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(string_sequence(a0)); }, result)) continue;
        probe::emit(out, "string_sequence", "string", call, result);
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
