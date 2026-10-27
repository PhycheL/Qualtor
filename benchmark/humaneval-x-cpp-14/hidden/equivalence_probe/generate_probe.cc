// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_14.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_105() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(55LL);
        sd.ints.push_back(0LL);
        sd.strs.push_back("One");
        sd.strs.push_back("Two");
        sd.strs.push_back("Three");
        sd.strs.push_back("Four");
        sd.strs.push_back("Five");
        sd.strs.push_back("Six");
        sd.strs.push_back("Seven");
        sd.strs.push_back("Eight");
        sd.strs.push_back("Nine");
        sd.ivecs.push_back(std::vector<long long>{2LL, 1LL, 1LL, 4LL, 5LL, 8LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 2LL, 2LL, 3LL, 4LL, 5LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{8LL, 5LL, 4LL, 3LL, 2LL, 2LL, 1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL, -1LL, 55LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 1LL, 55LL});
        sd.ivecs.push_back(std::vector<long long>{55LL, 1LL, -1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, -1LL, 3LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{9LL, 4LL, 8LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{"Eight", "Five", "Four", "Three", "Two", "Two", "One", "One"});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"One"});
        sd.svecs.push_back(std::vector<std::string>{"Three", "Two", "One"});
        sd.svecs.push_back(std::vector<std::string>{"Nine", "Eight", "Four"});
    }
    return sd;
}

static const probe::Seeds& seeds_106() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(24LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(720LL);
        sd.ints.push_back(28LL);
        sd.ints.push_back(3LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 6LL, 24LL, 15LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 6LL, 24LL, 15LL, 720LL, 28LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 6LL});
    }
    return sd;
}

static const probe::Seeds& seeds_107() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(123LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(63LL);
        sd.ints.push_back(25LL);
        sd.ints.push_back(19LL);
        sd.ivecs.push_back(std::vector<long long>{8LL, 13LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL});
    }
    return sd;
}

static const probe::Seeds& seeds_108() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(-123LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(-11LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(-6LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(98LL);
        sd.ints.push_back(-7LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(23LL);
        sd.ints.push_back(34LL);
        sd.ints.push_back(-45LL);
        sd.ints.push_back(-56LL);
        sd.ints.push_back(-0LL);
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 11LL, -11LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -2LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 2LL, -2LL, 3LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 6LL, 9LL, -6LL, 0LL, 1LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 100LL, 98LL, -7LL, 1LL, -1LL});
        sd.ivecs.push_back(std::vector<long long>{12LL, 23LL, 34LL, -45LL, -56LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{-0LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_109() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(10LL);
        sd.strs.push_back("arr");
        sd.ivecs.push_back(std::vector<long long>{3LL, 4LL, 5LL, 1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 5LL, 4LL, 1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 5LL, 10LL, 1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 3LL, 1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_110() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(200LL);
        sd.strs.push_back("YES");
        sd.strs.push_back("NO");
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 5LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 1LL, 4LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 7LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 6LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 6LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL, 6LL, 1LL, 8LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 5LL, 5LL, 1LL, 1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{100LL, 200LL});
        sd.ivecs.push_back(std::vector<long long>{200LL, 200LL});
    }
    return sd;
}

static const probe::Seeds& seeds_111() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.strs.push_back("a b c");
        sd.strs.push_back("a");
        sd.strs.push_back("b");
        sd.strs.push_back("c");
        sd.strs.push_back("a b b a");
        sd.strs.push_back("a b c a b");
        sd.strs.push_back("b b b b a");
        sd.strs.push_back("");
        sd.strs.push_back("a b c d g");
        sd.strs.push_back("r t g");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_112() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.strs.push_back("True");
        sd.strs.push_back("False");
        sd.strs.push_back("abcde");
        sd.strs.push_back("ae");
        sd.strs.push_back("bcd");
        sd.strs.push_back("abcdef");
        sd.strs.push_back("b");
        sd.strs.push_back("acdef");
        sd.strs.push_back("abcdedcba");
        sd.strs.push_back("ab");
        sd.strs.push_back("cdedc");
        sd.strs.push_back("dwik");
        sd.strs.push_back("w");
        sd.strs.push_back("dik");
        sd.strs.push_back("a");
        sd.strs.push_back("");
        sd.strs.push_back("v");
        sd.strs.push_back("vabba");
        sd.strs.push_back("abba");
        sd.strs.push_back("mamma");
        sd.strs.push_back("mia");
        sd.svecs.push_back(std::vector<std::string>{"bcd", "False"});
        sd.svecs.push_back(std::vector<std::string>{"acdef", "False"});
        sd.svecs.push_back(std::vector<std::string>{"cdedc", "True"});
        sd.svecs.push_back(std::vector<std::string>{"dik", "False"});
        sd.svecs.push_back(std::vector<std::string>{"", "True"});
        sd.svecs.push_back(std::vector<std::string>{"abcdedcba", "True"});
        sd.svecs.push_back(std::vector<std::string>{"abba", "True"});
    }
    return sd;
}

// CPP/105 vector<string> by_length(vector<int> arr)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_105();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("by_length(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(by_length(a0)); }, result)) continue;
        probe::emit(out, "by_length", "vec_string", call, result);
        ++kept;
    }
}

// CPP/106 vector<int> f(int n)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_106();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("f(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(f(a0)); }, result)) continue;
        probe::emit(out, "f", "vec_int", call, result);
        ++kept;
    }
}

// CPP/107 vector<int> even_odd_palindrome(int n)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_107();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("even_odd_palindrome(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(even_odd_palindrome(a0)); }, result)) continue;
        probe::emit(out, "even_odd_palindrome", "vec_int", call, result);
        ++kept;
    }
}

// CPP/108 int count_nums(vector<int> n)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_108();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("count_nums(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(count_nums(a0)); }, result)) continue;
        probe::emit(out, "count_nums", "int", call, result);
        ++kept;
    }
}

// CPP/109 bool move_one_ball(vector<int> arr)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_109();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("move_one_ball(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(move_one_ball(a0)); }, result)) continue;
        probe::emit(out, "move_one_ball", "bool", call, result);
        ++kept;
    }
}

// CPP/110 string exchange(vector<int> lst1,vector<int> lst2)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_110();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::vector<int> a1 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("exchange(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(exchange(a0, a1)); }, result)) continue;
        probe::emit(out, "exchange", "string", call, result);
        ++kept;
    }
}

// CPP/111 map<char,int> histogram(string test)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_111();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("histogram(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(histogram(a0)); }, result)) continue;
        probe::emit(out, "histogram", "map_char_int", call, result);
        ++kept;
    }
}

// CPP/112 vector<string> reverse_delete(string s,string c)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_112();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string a1 = probe::gen_string(rng, sd);
        std::string call = std::string("reverse_delete(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(reverse_delete(a0, a1)); }, result)) continue;
        probe::emit(out, "reverse_delete", "vec_string", call, result);
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
