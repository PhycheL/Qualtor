// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_16.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_121() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(5LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(30LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(24LL);
        sd.ints.push_back(321LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(23LL);
        sd.ints.push_back(32LL);
        sd.ivecs.push_back(std::vector<long long>{5LL, 8LL, 7LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 3LL, 3LL, 3LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{30LL, 13LL, 24LL, 321LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{30LL, 13LL, 23LL, 32LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 13LL, 2LL, 9LL});
    }
    return sd;
}

static const probe::Seeds& seeds_122() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(111LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4000LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(24LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(41LL);
        sd.ints.push_back(57LL);
        sd.ints.push_back(76LL);
        sd.ints.push_back(87LL);
        sd.ints.push_back(88LL);
        sd.ints.push_back(99LL);
        sd.ints.push_back(-4LL);
        sd.ints.push_back(121LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(90LL);
        sd.ints.push_back(125LL);
        sd.ivecs.push_back(std::vector<long long>{111LL, 21LL, 3LL, 4000LL, 5LL, 6LL, 7LL, 8LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, -2LL, -3LL, 41LL, 57LL, 76LL, 87LL, 88LL, 99LL});
        sd.ivecs.push_back(std::vector<long long>{111LL, 121LL, 3LL, 4000LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{11LL, 21LL, 3LL, 90LL, 5LL, 6LL, 7LL, 8LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
    }
    return sd;
}

static const probe::Seeds& seeds_123() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(3LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(16LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(17LL);
        sd.ints.push_back(12LL);
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 16LL, 8LL, 4LL, 2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 5LL, 7LL, 11LL, 13LL, 17LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 5LL});
    }
    return sd;
}

static const probe::Seeds& seeds_124() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(31LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(30LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(29LL);
        sd.ints.push_back(03LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(2000LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(01LL);
        sd.ints.push_back(2012LL);
        sd.ints.push_back(04LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(2040LL);
        sd.ints.push_back(06LL);
        sd.ints.push_back(2020LL);
        sd.ints.push_back(2007LL);
        sd.ints.push_back(32LL);
        sd.ints.push_back(2011LL);
        sd.ints.push_back(3000LL);
        sd.ints.push_back(2005LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(2003LL);
        sd.ints.push_back(04122003LL);
        sd.ints.push_back(20030412LL);
        sd.strs.push_back("03-11-2000");
        sd.strs.push_back("15-01-2012");
        sd.strs.push_back("04-0-2040");
        sd.strs.push_back("06-04-2020");
        sd.strs.push_back("06/04/2020");
        sd.strs.push_back("01-01-2007");
        sd.strs.push_back("03-32-2011");
        sd.strs.push_back("");
        sd.strs.push_back("04-31-3000");
        sd.strs.push_back("06-06-2005");
        sd.strs.push_back("21-31-2000");
        sd.strs.push_back("04-12-2003");
        sd.strs.push_back("04122003");
        sd.strs.push_back("20030412");
        sd.strs.push_back("2003-04");
        sd.strs.push_back("2003-04-12");
        sd.strs.push_back("04-2003");
    }
    return sd;
}

static const probe::Seeds& seeds_125() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(25LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.strs.push_back("a");
        sd.strs.push_back("b");
        sd.strs.push_back("z");
        sd.strs.push_back("Hello world!");
        sd.strs.push_back("Hello");
        sd.strs.push_back("world!");
        sd.strs.push_back("Hello,world!");
        sd.strs.push_back("abcdef");
        sd.strs.push_back("3");
        sd.strs.push_back("Hello world,!");
        sd.strs.push_back("world,!");
        sd.strs.push_back("Hello,Hello,world !");
        sd.strs.push_back("Hello,Hello,world");
        sd.strs.push_back("!");
        sd.strs.push_back("aaabb");
        sd.strs.push_back("2");
        sd.strs.push_back("aaaBb");
        sd.strs.push_back("1");
        sd.strs.push_back("");
        sd.strs.push_back("0");
        sd.svecs.push_back(std::vector<std::string>{"Hello", "world!"});
        sd.svecs.push_back(std::vector<std::string>{"3"});
        sd.svecs.push_back(std::vector<std::string>{"Hello", "world,!"});
        sd.svecs.push_back(std::vector<std::string>{"Hello,Hello,world", "!"});
        sd.svecs.push_back(std::vector<std::string>{"2"});
        sd.svecs.push_back(std::vector<std::string>{"1"});
        sd.svecs.push_back(std::vector<std::string>{"0"});
    }
    return sd;
}

static const probe::Seeds& seeds_126() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(7LL);
        sd.ivecs.push_back(std::vector<long long>{5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 6LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 4LL, 5LL, 6LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 2LL, 3LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 2LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 3LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_127() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(-4LL);
        sd.ints.push_back(-11LL);
        sd.strs.push_back("YES");
        sd.strs.push_back("NO");
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{-3LL, -1LL});
        sd.ivecs.push_back(std::vector<long long>{-5LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{-2LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{-4LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{-11LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -1LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{-2LL, -2LL});
        sd.ivecs.push_back(std::vector<long long>{-3LL, -2LL});
    }
    return sd;
}

static const probe::Seeds& seeds_128() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-32768LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(-4LL);
        sd.ints.push_back(-9LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(20LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 2LL, -4LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 1LL, 2LL, 3LL, -1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, 1LL, 2LL, -1LL, -1LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 1LL, -1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 1LL, 1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 1LL, 1LL, 0LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

// CPP/121 int solutions(vector<int> lst)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_121();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("solutions(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(solutions(a0)); }, result)) continue;
        probe::emit(out, "solutions", "int", call, result);
        ++kept;
    }
}

// CPP/122 int add_elements(vector<int> arr,int k)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_122();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("add_elements(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(add_elements(a0, a1)); }, result)) continue;
        probe::emit(out, "add_elements", "int", call, result);
        ++kept;
    }
}

// CPP/123 vector<int> get_odd_collatz(int n)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_123();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("get_odd_collatz(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(get_odd_collatz(a0)); }, result)) continue;
        probe::emit(out, "get_odd_collatz", "vec_int", call, result);
        ++kept;
    }
}

// CPP/124 bool valid_date(string date)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_124();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("valid_date(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(valid_date(a0)); }, result)) continue;
        probe::emit(out, "valid_date", "bool", call, result);
        ++kept;
    }
}

// CPP/125 vector<string> split_words(string txt)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_125();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("split_words(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(split_words(a0)); }, result)) continue;
        probe::emit(out, "split_words", "vec_string", call, result);
        ++kept;
    }
}

// CPP/126 bool is_sorted(vector<int> lst)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_126();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("is_sorted(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(is_sorted(a0)); }, result)) continue;
        probe::emit(out, "is_sorted", "bool", call, result);
        ++kept;
    }
}

// CPP/127 string intersection(vector<int> interval1,vector<int> interval2)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_127();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::vector<int> a1 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("intersection(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(intersection(a0, a1)); }, result)) continue;
        probe::emit(out, "intersection", "string", call, result);
        ++kept;
    }
}

// CPP/128 int prod_signs(vector<int> arr)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_128();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("prod_signs(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(prod_signs(a0)); }, result)) continue;
        probe::emit(out, "prod_signs", "int", call, result);
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
