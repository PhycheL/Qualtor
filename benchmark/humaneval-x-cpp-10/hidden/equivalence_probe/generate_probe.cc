// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_10.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_73() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(0LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 5LL, 4LL, 7LL, 9LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 3LL, 2LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 4LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 1LL, 1LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL});
    }
    return sd;
}

static const probe::Seeds& seeds_74() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(4LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(0LL);
        sd.strs.push_back("hi");
        sd.strs.push_back("admin");
        sd.strs.push_back("hI");
        sd.strs.push_back("Hi");
        sd.strs.push_back("project");
        sd.strs.push_back("4");
        sd.strs.push_back("1");
        sd.strs.push_back("2");
        sd.strs.push_back("3");
        sd.strs.push_back("5");
        sd.strs.push_back("hii");
        sd.strs.push_back("this");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"hi", "admin"});
        sd.svecs.push_back(std::vector<std::string>{"hI", "Hi"});
        sd.svecs.push_back(std::vector<std::string>{"hi", "hi", "admin", "project"});
        sd.svecs.push_back(std::vector<std::string>{"hI", "hi", "hi"});
        sd.svecs.push_back(std::vector<std::string>{"4"});
        sd.svecs.push_back(std::vector<std::string>{"1", "2", "3", "4", "5"});
        sd.svecs.push_back(std::vector<std::string>{"hi", "hi"});
        sd.svecs.push_back(std::vector<std::string>{"hI", "hi", "hii"});
        sd.svecs.push_back(std::vector<std::string>{"this"});
    }
    return sd;
}

static const probe::Seeds& seeds_75() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(3LL);
        sd.ints.push_back(30LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(125LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(13LL);
    }
    return sd;
}

static const probe::Seeds& seeds_76() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(16LL);
        sd.ints.push_back(143214LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(24LL);
        sd.ints.push_back(128LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(6LL);
    }
    return sd;
}

static const probe::Seeds& seeds_77() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(64LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(180LL);
        sd.ints.push_back(1000LL);
        sd.ints.push_back(1729LL);
    }
    return sd;
}

static const probe::Seeds& seeds_78() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(17LL);
        sd.ints.push_back(2020LL);
        sd.ints.push_back(12LL);
        sd.strs.push_back("AB");
        sd.strs.push_back("1077E");
        sd.strs.push_back("ABED1A33");
        sd.strs.push_back("123456789ABCDEF0");
        sd.strs.push_back("2020");
        sd.strs.push_back("112233445566778899AABBCCDDEEFF00");
        sd.strs.push_back("");
    }
    return sd;
}

static const probe::Seeds& seeds_79() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(32LL);
        sd.ints.push_back(103LL);
        sd.strs.push_back("db");
        sd.strs.push_back("db1111db");
        sd.strs.push_back("db100000db");
        sd.strs.push_back("db0db");
        sd.strs.push_back("db1100111db");
    }
    return sd;
}

static const probe::Seeds& seeds_80() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(3LL);
        sd.strs.push_back("a");
        sd.strs.push_back("aa");
        sd.strs.push_back("abcd");
        sd.strs.push_back("aabb");
        sd.strs.push_back("adb");
        sd.strs.push_back("xyy");
        sd.strs.push_back("iopaxpoi");
        sd.strs.push_back("iopaxioi");
    }
    return sd;
}

// CPP/73 int smallest_change(vector<int> arr)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_73();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("smallest_change(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(smallest_change(a0)); }, result)) continue;
        probe::emit(out, "smallest_change", "int", call, result);
        ++kept;
    }
}

// CPP/74 vector<string> total_match(vector<string> lst1,vector<string> lst2)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_74();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::string> a0 = probe::gen_vec_string(rng, sd);
        std::vector<std::string> a1 = probe::gen_vec_string(rng, sd);
        std::string call = std::string("total_match(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(total_match(a0, a1)); }, result)) continue;
        probe::emit(out, "total_match", "vec_string", call, result);
        ++kept;
    }
}

// CPP/75 bool is_multiply_prime(int a)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_75();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("is_multiply_prime(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(is_multiply_prime(a0)); }, result)) continue;
        probe::emit(out, "is_multiply_prime", "bool", call, result);
        ++kept;
    }
}

// CPP/76 bool is_simple_power(int x,int n)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_76();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("is_simple_power(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(is_simple_power(a0, a1)); }, result)) continue;
        probe::emit(out, "is_simple_power", "bool", call, result);
        ++kept;
    }
}

// CPP/77 bool iscuber(int a)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_77();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("iscuber(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(iscuber(a0)); }, result)) continue;
        probe::emit(out, "iscuber", "bool", call, result);
        ++kept;
    }
}

// CPP/78 int hex_key(string num)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_78();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("hex_key(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(hex_key(a0)); }, result)) continue;
        probe::emit(out, "hex_key", "int", call, result);
        ++kept;
    }
}

// CPP/79 string decimal_to_binary(int decimal)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_79();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("decimal_to_binary(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(decimal_to_binary(a0)); }, result)) continue;
        probe::emit(out, "decimal_to_binary", "string", call, result);
        ++kept;
    }
}

// CPP/80 bool is_happy(string s)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_80();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("is_happy(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(is_happy(a0)); }, result)) continue;
        probe::emit(out, "is_happy", "bool", call, result);
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
