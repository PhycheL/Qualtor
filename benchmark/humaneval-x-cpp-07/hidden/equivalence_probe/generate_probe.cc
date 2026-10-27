// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_07.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_49() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(1101LL);
        sd.ints.push_back(101LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(30LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(31LL);
    }
    return sd;
}

static const probe::Seeds& seeds_50() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(5LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(26LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(97LL);
        sd.strs.push_back("");
    }
    return sd;
}

static const probe::Seeds& seeds_51() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("");
        sd.strs.push_back("abcdef\nghijklm");
        sd.strs.push_back("bcdf\nghjklm");
        sd.strs.push_back("abcdef");
        sd.strs.push_back("bcdf");
        sd.strs.push_back("aaaaa");
        sd.strs.push_back("aaBAA");
        sd.strs.push_back("B");
        sd.strs.push_back("zbcd");
        sd.strs.push_back("fedcba");
        sd.strs.push_back("fdcb");
        sd.strs.push_back("eeeee");
        sd.strs.push_back("acBAA");
        sd.strs.push_back("cB");
        sd.strs.push_back("EcBOO");
        sd.strs.push_back("ybcd");
    }
    return sd;
}

static const probe::Seeds& seeds_52() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(22LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(11LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 4LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 20LL, 4LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 8LL, 4LL, 10LL});
    }
    return sd;
}

static const probe::Seeds& seeds_53() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(1000LL);
    }
    return sd;
}

static const probe::Seeds& seeds_54() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("eabcdzzzz");
        sd.strs.push_back("dddzzzzzzzddeddabc");
        sd.strs.push_back("abcd");
        sd.strs.push_back("dddddddabc");
        sd.strs.push_back("eabcd");
        sd.strs.push_back("dddddddabce");
        sd.strs.push_back("dddzzzzzzzddddabc");
        sd.strs.push_back("dddddddabcf");
        sd.strs.push_back("aabb");
        sd.strs.push_back("aaccc");
    }
    return sd;
}

static const probe::Seeds& seeds_55() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(10LL);
        sd.ints.push_back(55LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(89LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(144LL);
    }
    return sd;
}

static const probe::Seeds& seeds_56() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("<");
        sd.strs.push_back("<>");
        sd.strs.push_back("<<><>>");
        sd.strs.push_back("><<>");
        sd.strs.push_back("<><><<><>><>");
        sd.strs.push_back("<><><<<><><>><>><<><><<>>>");
        sd.strs.push_back("<<<><>>>>");
        sd.strs.push_back("<<<<");
        sd.strs.push_back(">");
        sd.strs.push_back("<<>");
        sd.strs.push_back("<><><<><>><>><<>");
        sd.strs.push_back("<><><<><>><>>><>");
    }
    return sd;
}

// CPP/49 int modp(int n,int p)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_49();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("modp(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(modp(a0, a1)); }, result)) continue;
        probe::emit(out, "modp", "int", call, result);
        ++kept;
    }
}

// CPP/50 string encode_shift(string s)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_50();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("encode_shift(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(encode_shift(a0)); }, result)) continue;
        probe::emit(out, "encode_shift", "string", call, result);
        ++kept;
    }
}

// CPP/50 string decode_shift(string s)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_50();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("decode_shift(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(decode_shift(a0)); }, result)) continue;
        probe::emit(out, "decode_shift", "string", call, result);
        ++kept;
    }
}

// CPP/51 string remove_vowels(string text)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_51();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("remove_vowels(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(remove_vowels(a0)); }, result)) continue;
        probe::emit(out, "remove_vowels", "string", call, result);
        ++kept;
    }
}

// CPP/52 bool below_threshold(vector<int>l, int t)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_52();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("below_threshold(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(below_threshold(a0, a1)); }, result)) continue;
        probe::emit(out, "below_threshold", "bool", call, result);
        ++kept;
    }
}

// CPP/53 int add(int x,int y)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_53();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("add(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(add(a0, a1)); }, result)) continue;
        probe::emit(out, "add", "int", call, result);
        ++kept;
    }
}

// CPP/54 bool same_chars(string s0,string s1)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_54();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string a1 = probe::gen_string(rng, sd);
        std::string call = std::string("same_chars(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(same_chars(a0, a1)); }, result)) continue;
        probe::emit(out, "same_chars", "bool", call, result);
        ++kept;
    }
}

// CPP/55 int fib(int n)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_55();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("fib(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(fib(a0)); }, result)) continue;
        probe::emit(out, "fib", "int", call, result);
        ++kept;
    }
}

// CPP/56 bool correct_bracketing(string brackets)
static void probe_8(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 8ULL);
    const probe::Seeds& sd = seeds_56();
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
