// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_11.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_81() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.reals.push_back(4.0);
        sd.reals.push_back(3.7);
        sd.reals.push_back(3.3);
        sd.reals.push_back(3.0);
        sd.reals.push_back(2.7);
        sd.reals.push_back(2.3);
        sd.reals.push_back(2.0);
        sd.reals.push_back(1.7);
        sd.reals.push_back(1.3);
        sd.reals.push_back(1.0);
        sd.reals.push_back(0.7);
        sd.reals.push_back(0.0);
        sd.reals.push_back(3.5);
        sd.reals.push_back(1.2);
        sd.reals.push_back(0.5);
        sd.reals.push_back(0.3);
        sd.reals.push_back(1.5);
        sd.reals.push_back(2.8);
        sd.strs.push_back("A+");
        sd.strs.push_back("B");
        sd.strs.push_back("C-");
        sd.strs.push_back("C");
        sd.strs.push_back("A-");
        sd.strs.push_back("D+");
        sd.strs.push_back("D-");
        sd.strs.push_back("E");
        sd.strs.push_back("D");
        sd.strs.push_back("B+");
        sd.fvecs.push_back(std::vector<double>{4.0, 3, 1.7, 2, 3.5});
        sd.fvecs.push_back(std::vector<double>{1.2});
        sd.fvecs.push_back(std::vector<double>{0.5});
        sd.fvecs.push_back(std::vector<double>{0.0});
        sd.fvecs.push_back(std::vector<double>{1, 0.3, 1.5, 2.8, 3.3});
        sd.fvecs.push_back(std::vector<double>{0, 0.7});
        sd.svecs.push_back(std::vector<std::string>{"A+", "B", "C-", "C", "A-"});
        sd.svecs.push_back(std::vector<std::string>{"D+"});
        sd.svecs.push_back(std::vector<std::string>{"D-"});
        sd.svecs.push_back(std::vector<std::string>{"E"});
        sd.svecs.push_back(std::vector<std::string>{"D", "D-", "C-", "B", "B+"});
        sd.svecs.push_back(std::vector<std::string>{"E", "D-"});
    }
    return sd;
}

static const probe::Seeds& seeds_82() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.strs.push_back("Hello");
        sd.strs.push_back("abcdcba");
        sd.strs.push_back("kittens");
        sd.strs.push_back("orange");
        sd.strs.push_back("wow");
        sd.strs.push_back("world");
        sd.strs.push_back("MadaM");
        sd.strs.push_back("Wow");
        sd.strs.push_back("");
        sd.strs.push_back("HI");
        sd.strs.push_back("go");
        sd.strs.push_back("gogo");
        sd.strs.push_back("aaaaaaaaaaaaaaa");
        sd.strs.push_back("Madam");
        sd.strs.push_back("M");
        sd.strs.push_back("0");
    }
    return sd;
}

static const probe::Seeds& seeds_83() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(18LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(180LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(1800LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(18000LL);
    }
    return sd;
}

static const probe::Seeds& seeds_84() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1000LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(150LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(110LL);
        sd.ints.push_back(147LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(1100LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(333LL);
        sd.ints.push_back(1001LL);
        sd.ints.push_back(963LL);
        sd.ints.push_back(10010LL);
        sd.strs.push_back("1");
        sd.strs.push_back("110");
        sd.strs.push_back("1100");
        sd.strs.push_back("1001");
        sd.strs.push_back("10010");
    }
    return sd;
}

static const probe::Seeds& seeds_85() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(4LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(88LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(122LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(12LL);
        sd.ivecs.push_back(std::vector<long long>{4LL, 2LL, 6LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 88LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 5LL, 6LL, 7LL, 2LL, 122LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 0LL, 6LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 4LL, 6LL, 8LL});
    }
    return sd;
}

static const probe::Seeds& seeds_86() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("Hi");
        sd.strs.push_back("hello");
        sd.strs.push_back("ehllo");
        sd.strs.push_back("Hello World!!!");
        sd.strs.push_back("Hello !!!Wdlor");
        sd.strs.push_back("number");
        sd.strs.push_back("bemnru");
        sd.strs.push_back("abcd");
        sd.strs.push_back("");
        sd.strs.push_back("Hi. My name is Mister Robot. How are you?");
        sd.strs.push_back(".Hi My aemn is Meirst .Rboot How aer ?ouy");
    }
    return sd;
}

static const probe::Seeds& seeds_87() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(0LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 1LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 3LL, 4LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 1LL, 4LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 1LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 0LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_88() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(5LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(42LL);
        sd.ints.push_back(87LL);
        sd.ints.push_back(32LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(23LL);
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{5LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, 3LL, 0LL, 1LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL, 2LL, 3LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, 3LL, 0LL, 1LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 5LL, 4LL, 3LL, 2LL, 1LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{15LL, 42LL, 87LL, 32LL, 11LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 11LL, 15LL, 32LL, 42LL, 87LL});
        sd.ivecs.push_back(std::vector<long long>{21LL, 14LL, 23LL, 11LL});
        sd.ivecs.push_back(std::vector<long long>{23LL, 21LL, 14LL, 11LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

// CPP/81 vector<string> numerical_letter_grade(vector<float> grades)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_81();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("numerical_letter_grade(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(numerical_letter_grade(a0)); }, result)) continue;
        probe::emit(out, "numerical_letter_grade", "vec_string", call, result);
        ++kept;
    }
}

// CPP/82 bool prime_length(string str)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_82();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("prime_length(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(prime_length(a0)); }, result)) continue;
        probe::emit(out, "prime_length", "bool", call, result);
        ++kept;
    }
}

// CPP/83 int starts_one_ends(int n)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_83();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("starts_one_ends(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(starts_one_ends(a0)); }, result)) continue;
        probe::emit(out, "starts_one_ends", "int", call, result);
        ++kept;
    }
}

// CPP/84 string solve(int N)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_84();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("solve(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(solve(a0)); }, result)) continue;
        probe::emit(out, "solve", "string", call, result);
        ++kept;
    }
}

// CPP/85 int add(vector<int> lst)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_85();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("add(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(add(a0)); }, result)) continue;
        probe::emit(out, "add", "int", call, result);
        ++kept;
    }
}

// CPP/86 string anti_shuffle(string s)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_86();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("anti_shuffle(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(anti_shuffle(a0)); }, result)) continue;
        probe::emit(out, "anti_shuffle", "string", call, result);
        ++kept;
    }
}

// CPP/87 vector<vector<int>> get_row(vector<vector<int>> lst, int x)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_87();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::vector<int> > a0 = probe::gen_vec_vec_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("get_row(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(get_row(a0, a1)); }, result)) continue;
        probe::emit(out, "get_row", "vec_vec_int", call, result);
        ++kept;
    }
}

// CPP/88 vector<int> sort_array(vector<int> array)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_88();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("sort_array(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(sort_array(a0)); }, result)) continue;
        probe::emit(out, "sort_array", "vec_int", call, result);
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
