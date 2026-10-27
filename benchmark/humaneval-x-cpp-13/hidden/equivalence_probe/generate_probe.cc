// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_13.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_97() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(148LL);
        sd.ints.push_back(412LL);
        sd.ints.push_back(19LL);
        sd.ints.push_back(28LL);
        sd.ints.push_back(2020LL);
        sd.ints.push_back(1851LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(-15LL);
        sd.ints.push_back(16LL);
        sd.ints.push_back(72LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(76LL);
        sd.ints.push_back(67LL);
        sd.ints.push_back(42LL);
        sd.ints.push_back(17LL);
        sd.ints.push_back(27LL);
        sd.ints.push_back(49LL);
        sd.ints.push_back(1LL);
    }
    return sd;
}

static const probe::Seeds& seeds_98() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(2LL);
        sd.strs.push_back("aBCdEf");
        sd.strs.push_back("abcdefg");
        sd.strs.push_back("dBBE");
        sd.strs.push_back("B");
        sd.strs.push_back("U");
        sd.strs.push_back("");
        sd.strs.push_back("EEEE");
    }
    return sd;
}

static const probe::Seeds& seeds_99() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(10LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(-16LL);
        sd.ints.push_back(0LL);
        sd.reals.push_back(15.3);
        sd.reals.push_back(14.5);
        sd.reals.push_back(-14.5);
        sd.reals.push_back(-15.5);
        sd.strs.push_back("10");
        sd.strs.push_back("15.3");
        sd.strs.push_back("14.5");
        sd.strs.push_back("-14.5");
        sd.strs.push_back("-15.5");
        sd.strs.push_back("0");
    }
    return sd;
}

static const probe::Seeds& seeds_100() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(16LL);
        sd.ints.push_back(18LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(22LL);
        sd.ivecs.push_back(std::vector<long long>{3LL, 5LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 6LL, 8LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 7LL, 9LL, 11LL, 13LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 8LL, 10LL, 12LL, 14LL, 16LL});
        sd.ivecs.push_back(std::vector<long long>{8LL, 10LL, 12LL, 14LL, 16LL, 18LL, 20LL, 22LL});
    }
    return sd;
}

static const probe::Seeds& seeds_101() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.strs.push_back("Hi, my name is John");
        sd.strs.push_back("Hi");
        sd.strs.push_back("my");
        sd.strs.push_back("name");
        sd.strs.push_back("is");
        sd.strs.push_back("John");
        sd.strs.push_back("One, two, three, four, five, six");
        sd.strs.push_back("One");
        sd.strs.push_back(", 'three");
        sd.strs.push_back("four");
        sd.strs.push_back("five");
        sd.strs.push_back("two");
        sd.strs.push_back("three");
        sd.strs.push_back("six");
        sd.strs.push_back("Hi, my name");
        sd.strs.push_back("One,, two, three, four, five, six,");
        sd.strs.push_back("");
        sd.strs.push_back("ahmed     , gamal");
        sd.strs.push_back("ahmed");
        sd.strs.push_back("gamal");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{"Hi", "my", "name", "is", "John"});
        sd.svecs.push_back(std::vector<std::string>{"One", "two", "three", "four", "five", "six"});
        sd.svecs.push_back(std::vector<std::string>{"Hi", "my", "name"});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"ahmed", "gamal"});
    }
    return sd;
}

static const probe::Seeds& seeds_102() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(12LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(33LL);
        sd.ints.push_back(12354LL);
        sd.ints.push_back(5234LL);
        sd.ints.push_back(5233LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(29LL);
        sd.ints.push_back(28LL);
        sd.ints.push_back(27LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(546LL);
    }
    return sd;
}

static const probe::Seeds& seeds_103() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(-1LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(1111LL);
        sd.ints.push_back(33LL);
        sd.ints.push_back(11010LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(1010LL);
        sd.ints.push_back(964LL);
        sd.ints.push_back(977LL);
        sd.ints.push_back(1111001010LL);
        sd.ints.push_back(996LL);
        sd.ints.push_back(997LL);
        sd.ints.push_back(1111100100LL);
        sd.ints.push_back(560LL);
        sd.ints.push_back(851LL);
        sd.ints.push_back(1011000001LL);
        sd.ints.push_back(185LL);
        sd.ints.push_back(546LL);
        sd.ints.push_back(101101101LL);
        sd.ints.push_back(362LL);
        sd.ints.push_back(496LL);
        sd.ints.push_back(110101101LL);
        sd.ints.push_back(350LL);
        sd.ints.push_back(902LL);
        sd.ints.push_back(1001110010LL);
        sd.ints.push_back(197LL);
        sd.ints.push_back(233LL);
        sd.ints.push_back(11010111LL);
        sd.ints.push_back(101LL);
        sd.strs.push_back("-1");
        sd.strs.push_back("11");
        sd.strs.push_back("1111");
        sd.strs.push_back("11010");
        sd.strs.push_back("1010");
        sd.strs.push_back("1111001010");
        sd.strs.push_back("1111100100");
        sd.strs.push_back("1011000001");
        sd.strs.push_back("101101101");
        sd.strs.push_back("110101101");
        sd.strs.push_back("1001110010");
        sd.strs.push_back("11010111");
        sd.strs.push_back("101");
    }
    return sd;
}

static const probe::Seeds& seeds_104() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(15LL);
        sd.ints.push_back(33LL);
        sd.ints.push_back(1422LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(152LL);
        sd.ints.push_back(323LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(12345LL);
        sd.ints.push_back(2033LL);
        sd.ints.push_back(111LL);
        sd.ints.push_back(151LL);
        sd.ints.push_back(135LL);
        sd.ints.push_back(103LL);
        sd.ints.push_back(31LL);
        sd.ivecs.push_back(std::vector<long long>{15LL, 33LL, 1422LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 15LL, 33LL});
        sd.ivecs.push_back(std::vector<long long>{152LL, 323LL, 1422LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{12345LL, 2033LL, 111LL, 151LL});
        sd.ivecs.push_back(std::vector<long long>{111LL, 151LL});
        sd.ivecs.push_back(std::vector<long long>{135LL, 103LL, 31LL});
        sd.ivecs.push_back(std::vector<long long>{31LL, 135LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

// CPP/97 int multiply(int a,int b)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_97();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("multiply(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(multiply(a0, a1)); }, result)) continue;
        probe::emit(out, "multiply", "int", call, result);
        ++kept;
    }
}

// CPP/98 int count_upper(string s)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_98();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("count_upper(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(count_upper(a0)); }, result)) continue;
        probe::emit(out, "count_upper", "int", call, result);
        ++kept;
    }
}

// CPP/99 int closest_integer(string value)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_99();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("closest_integer(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(closest_integer(a0)); }, result)) continue;
        probe::emit(out, "closest_integer", "int", call, result);
        ++kept;
    }
}

// CPP/100 vector<int> make_a_pile(int n)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_100();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("make_a_pile(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(make_a_pile(a0)); }, result)) continue;
        probe::emit(out, "make_a_pile", "vec_int", call, result);
        ++kept;
    }
}

// CPP/101 vector<string> words_string(string s)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_101();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("words_string(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(words_string(a0)); }, result)) continue;
        probe::emit(out, "words_string", "vec_string", call, result);
        ++kept;
    }
}

// CPP/102 int choose_num(int x,int y)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_102();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("choose_num(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(choose_num(a0, a1)); }, result)) continue;
        probe::emit(out, "choose_num", "int", call, result);
        ++kept;
    }
}

// CPP/103 string rounded_avg(int n,int m)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_103();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("rounded_avg(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(rounded_avg(a0, a1)); }, result)) continue;
        probe::emit(out, "rounded_avg", "string", call, result);
        ++kept;
    }
}

// CPP/104 vector<int> unique_digits(vector<int> x)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_104();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("unique_digits(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(unique_digits(a0)); }, result)) continue;
        probe::emit(out, "unique_digits", "vec_int", call, result);
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
