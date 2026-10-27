// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_18.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_138() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(4LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(16LL);
    }
    return sd;
}

static const probe::Seeds& seeds_139() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(288LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(34560LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(125411328000LL);
    }
    return sd;
}

static const probe::Seeds& seeds_140() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.strs.push_back("Example");
        sd.strs.push_back("Example 1");
        sd.strs.push_back("Example_1");
        sd.strs.push_back(" Example 2");
        sd.strs.push_back("_Example_2");
        sd.strs.push_back(" Example   3");
        sd.strs.push_back("_Example-3");
        sd.strs.push_back("Mudasir Hanif ");
        sd.strs.push_back("Mudasir_Hanif_");
        sd.strs.push_back("Yellow Yellow  Dirty  Fellow");
        sd.strs.push_back("Yellow_Yellow__Dirty__Fellow");
        sd.strs.push_back("Exa   mple");
        sd.strs.push_back("Exa-mple");
        sd.strs.push_back("   Exa 1 2 2 mple");
        sd.strs.push_back("-Exa_1_2_2_mple");
    }
    return sd;
}

static const probe::Seeds& seeds_141() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(9LL);
        sd.strs.push_back("Yes");
        sd.strs.push_back("No");
        sd.strs.push_back(".");
        sd.strs.push_back(", ");
        sd.strs.push_back("example.txt");
        sd.strs.push_back("1example.dll");
        sd.strs.push_back("s1sdf3.asd");
        sd.strs.push_back("K.dll");
        sd.strs.push_back("MY16FILE3.exe");
        sd.strs.push_back("His12FILE94.exe");
        sd.strs.push_back("_Y.txt");
        sd.strs.push_back("?aREYA.exe");
        sd.strs.push_back("/this_is_valid.dll");
        sd.strs.push_back("this_is_valid.wow");
        sd.strs.push_back("this_is_valid.txt");
        sd.strs.push_back("this_is_valid.txtexe");
        sd.strs.push_back("#this2_i4s_5valid.ten");
        sd.strs.push_back("@this1_is6_valid.exe");
        sd.strs.push_back("this_is_12valid.6exe4.txt");
        sd.strs.push_back("all.exe.txt");
        sd.strs.push_back("I563_No.exe");
        sd.strs.push_back("Is3youfault.txt");
        sd.strs.push_back("no_one#knows.dll");
        sd.strs.push_back("1I563_Yes3.exe");
        sd.strs.push_back("I563_Yes3.txtt");
        sd.strs.push_back("final..txt");
        sd.strs.push_back("final132");
        sd.strs.push_back("_f4indsartal132.");
        sd.strs.push_back(".txt");
        sd.strs.push_back("s.");
    }
    return sd;
}

static const probe::Seeds& seeds_142() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(-126LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(-56LL);
        sd.ints.push_back(-99LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(3030LL);
        sd.ints.push_back(-16LL);
        sd.ints.push_back(-9LL);
        sd.ints.push_back(36LL);
        sd.ints.push_back(26LL);
        sd.ints.push_back(-20LL);
        sd.ints.push_back(25LL);
        sd.ints.push_back(-40LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(-4LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(-26LL);
        sd.ints.push_back(35LL);
        sd.ints.push_back(37LL);
        sd.ints.push_back(-14196LL);
        sd.ints.push_back(17LL);
        sd.ints.push_back(-15LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(-14LL);
        sd.ints.push_back(-12LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(16LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(-1448LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -5LL, 2LL, -1LL, -5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 1LL, 1LL, 1LL, 1LL, 1LL, 1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -1LL, -1LL, -1LL, -1LL, -1LL, -1LL, -1LL, -1LL});
        sd.ivecs.push_back(std::vector<long long>{0LL});
        sd.ivecs.push_back(std::vector<long long>{-56LL, -99LL, 1LL, 0LL, -2LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, -1LL});
        sd.ivecs.push_back(std::vector<long long>{-16LL, -9LL, -2LL, 36LL, 36LL, 26LL, -20LL, 25LL, -40LL, 20LL, -4LL, 12LL, -26LL, 35LL, 37LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -3LL, 17LL, -1LL, -15LL, 13LL, -1LL, 14LL, -14LL, -12LL, -5LL, 14LL, -14LL, 6LL, 13LL, 11LL, 16LL, 16LL, 4LL, 10LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_143() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(100LL);
        sd.strs.push_back("This is a test");
        sd.strs.push_back("is");
        sd.strs.push_back("lets go for swimming");
        sd.strs.push_back("go for");
        sd.strs.push_back("there is no place available here");
        sd.strs.push_back("there is no place");
        sd.strs.push_back("Hi I am Hussein");
        sd.strs.push_back("Hi am Hussein");
        sd.strs.push_back("go for it");
        sd.strs.push_back("here");
        sd.strs.push_back("");
        sd.strs.push_back("here is");
    }
    return sd;
}

static const probe::Seeds& seeds_144() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(50LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(8LL);
        sd.strs.push_back("1/5");
        sd.strs.push_back("5/1");
        sd.strs.push_back("1/6");
        sd.strs.push_back("2/1");
        sd.strs.push_back("7/10");
        sd.strs.push_back("10/2");
        sd.strs.push_back("3/1");
        sd.strs.push_back("2/10");
        sd.strs.push_back("50/10");
        sd.strs.push_back("7/2");
        sd.strs.push_back("4/2");
        sd.strs.push_back("11/6");
        sd.strs.push_back("6/1");
        sd.strs.push_back("2/3");
        sd.strs.push_back("5/2");
        sd.strs.push_back("3/5");
        sd.strs.push_back("2/4");
        sd.strs.push_back("8/4");
    }
    return sd;
}

static const probe::Seeds& seeds_145() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-11LL);
        sd.ints.push_back(-12LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(1234LL);
        sd.ints.push_back(423LL);
        sd.ints.push_back(463LL);
        sd.ints.push_back(145LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(53LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(37LL);
        sd.ints.push_back(3457LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(56LL);
        sd.ints.push_back(46LL);
        sd.ints.push_back(-32LL);
        sd.ints.push_back(43LL);
        sd.ints.push_back(54LL);
        sd.ints.push_back(-98LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(-76LL);
        sd.ints.push_back(-21LL);
        sd.ints.push_back(23LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 11LL, -1LL, -11LL, -12LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -11LL, 1LL, -12LL, 11LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1234LL, 423LL, 463LL, 145LL, 2LL, 423LL, 423LL, 53LL, 6LL, 37LL, 3457LL, 3LL, 56LL, 0LL, 46LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 2LL, 3LL, 6LL, 53LL, 423LL, 423LL, 423LL, 1234LL, 145LL, 37LL, 46LL, 56LL, 463LL, 3457LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, -11LL, -32LL, 43LL, 54LL, -98LL, 2LL, -3LL});
        sd.ivecs.push_back(std::vector<long long>{-3LL, -32LL, -98LL, -11LL, 1LL, 2LL, 43LL, 54LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 6LL, 7LL, 8LL, 9LL, 10LL, 11LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 10LL, 2LL, 11LL, 3LL, 4LL, 5LL, 6LL, 7LL, 8LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 6LL, 6LL, -76LL, -21LL, 23LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{-76LL, -21LL, 0LL, 4LL, 23LL, 6LL, 6LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

// CPP/138 bool is_equal_to_sum_even(int n)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_138();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("is_equal_to_sum_even(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(is_equal_to_sum_even(a0)); }, result)) continue;
        probe::emit(out, "is_equal_to_sum_even", "bool", call, result);
        ++kept;
    }
}

// CPP/139 long long special_factorial(int n)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_139();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("special_factorial(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(special_factorial(a0)); }, result)) continue;
        probe::emit(out, "special_factorial", "ll", call, result);
        ++kept;
    }
}

// CPP/140 string fix_spaces(string text)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_140();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("fix_spaces(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(fix_spaces(a0)); }, result)) continue;
        probe::emit(out, "fix_spaces", "string", call, result);
        ++kept;
    }
}

// CPP/141 string file_name_check(string file_name)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_141();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("file_name_check(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(file_name_check(a0)); }, result)) continue;
        probe::emit(out, "file_name_check", "string", call, result);
        ++kept;
    }
}

// CPP/142 int sum_squares(vector<int> lst)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_142();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("sum_squares(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(sum_squares(a0)); }, result)) continue;
        probe::emit(out, "sum_squares", "int", call, result);
        ++kept;
    }
}

// CPP/143 string words_in_sentence(string sentence)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_143();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("words_in_sentence(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(words_in_sentence(a0)); }, result)) continue;
        probe::emit(out, "words_in_sentence", "string", call, result);
        ++kept;
    }
}

// CPP/144 bool simplify(string x,string n)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_144();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string a1 = probe::gen_string(rng, sd);
        std::string call = std::string("simplify(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(simplify(a0, a1)); }, result)) continue;
        probe::emit(out, "simplify", "bool", call, result);
        ++kept;
    }
}

// CPP/145 vector<int> order_by_points(vector<int> nums)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_145();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("order_by_points(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(order_by_points(a0)); }, result)) continue;
        probe::emit(out, "order_by_points", "vec_int", call, result);
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
