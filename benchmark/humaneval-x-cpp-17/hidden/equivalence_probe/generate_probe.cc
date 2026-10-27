// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_17.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_129() {
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
        sd.ints.push_back(7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(16LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{7LL, 8LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 9LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 1LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{7LL, 8LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 6LL, 7LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{9LL, 10LL, 11LL, 12LL});
        sd.ivecs.push_back(std::vector<long long>{13LL, 14LL, 15LL, 16LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 4LL, 13LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 7LL, 12LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 16LL, 11LL, 15LL});
        sd.ivecs.push_back(std::vector<long long>{8LL, 14LL, 9LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 10LL, 1LL, 10LL, 1LL, 10LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 4LL, 13LL, 15LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 7LL, 1LL, 12LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 10LL, 11LL, 16LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 7LL, 1LL, 7LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{11LL, 8LL, 7LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 16LL, 14LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{9LL, 3LL, 15LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{12LL, 13LL, 10LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 6LL, 1LL, 6LL, 1LL, 6LL, 1LL, 6LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 6LL, 1LL, 6LL, 1LL, 6LL, 1LL, 6LL, 1LL, 6LL, 1LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 7LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 1LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 8LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 1LL, 3LL, 1LL, 3LL, 1LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{6LL, 1LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 8LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 5LL, 1LL, 5LL, 1LL, 5LL, 1LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 1LL, 2LL, 1LL, 2LL, 1LL, 2LL, 1LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 2LL});
    }
    return sd;
}

static const probe::Seeds& seeds_130() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(24LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(35LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(48LL);
        sd.ints.push_back(63LL);
        sd.ints.push_back(80LL);
        sd.ints.push_back(99LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(120LL);
        sd.ints.push_back(11LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 8LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 8LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 8LL, 3LL, 15LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 8LL, 3LL, 15LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 8LL, 3LL, 15LL, 4LL, 24LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 8LL, 3LL, 15LL, 4LL, 24LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 8LL, 3LL, 15LL, 4LL, 24LL, 5LL, 35LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 8LL, 3LL, 15LL, 4LL, 24LL, 5LL, 35LL, 6LL, 48LL, 7LL, 63LL, 8LL, 80LL, 9LL, 99LL, 10LL, 120LL, 11LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL});
    }
    return sd;
}

static const probe::Seeds& seeds_131() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(235LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(54LL);
        sd.ints.push_back(120LL);
        sd.ints.push_back(5014LL);
        sd.ints.push_back(98765LL);
        sd.ints.push_back(315LL);
        sd.ints.push_back(5576543LL);
        sd.ints.push_back(2625LL);
        sd.ints.push_back(2468LL);
    }
    return sd;
}

static const probe::Seeds& seeds_132() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("[[]]");
        sd.strs.push_back("[]]]]]]][[[[[]");
        sd.strs.push_back("[][]");
        sd.strs.push_back("[]");
        sd.strs.push_back("[[][]]");
        sd.strs.push_back("[[]][[");
        sd.strs.push_back("[[[[]]]]");
        sd.strs.push_back("[]]]]]]]]]]");
        sd.strs.push_back("[][][[]]");
        sd.strs.push_back("[[]");
        sd.strs.push_back("[]]");
        sd.strs.push_back("");
        sd.strs.push_back("[[[[[[[[");
        sd.strs.push_back("]]]]]]]]");
    }
    return sd;
}

static const probe::Seeds& seeds_133() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(98LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(84LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(29LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(10230LL);
        sd.ints.push_back(10000LL);
        sd.ints.push_back(200000000LL);
        sd.ints.push_back(75LL);
        sd.ints.push_back(1086LL);
        sd.ints.push_back(-1LL);
        sd.reals.push_back(1.4);
        sd.reals.push_back(4.2);
        sd.reals.push_back(-2.4);
        sd.reals.push_back(1.0);
        sd.reals.push_back(-1.4);
        sd.reals.push_back(4.6);
        sd.reals.push_back(6.3);
        sd.reals.push_back(17.9);
        sd.reals.push_back(18.9);
        sd.reals.push_back(19.9);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 9LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 5LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{100LL, 1LL, 15LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{10000LL, 10000LL});
        sd.ivecs.push_back(std::vector<long long>{0LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 1LL, 0LL});
        sd.fvecs.push_back(std::vector<double>{1.4, 4.2, 0});
        sd.fvecs.push_back(std::vector<double>{-2.4, 1, 1});
        sd.fvecs.push_back(std::vector<double>{1.0, 2, 3});
        sd.fvecs.push_back(std::vector<double>{-1.4, 4.6, 6.3});
        sd.fvecs.push_back(std::vector<double>{-1.4, 17.9, 18.9, 19.9});
    }
    return sd;
}

static const probe::Seeds& seeds_134() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.strs.push_back("word");
        sd.strs.push_back("apple pie");
        sd.strs.push_back("apple pi e");
        sd.strs.push_back("apple pi e ");
        sd.strs.push_back("");
        sd.strs.push_back("apple");
        sd.strs.push_back("eeeee");
        sd.strs.push_back("A");
        sd.strs.push_back("Pumpkin pie ");
        sd.strs.push_back("Pumpkin pie 1");
        sd.strs.push_back("eeeee e ");
    }
    return sd;
}

static const probe::Seeds& seeds_135() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(10LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 4LL, 3LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 4LL, 2LL, 5LL, 6LL, 7LL, 8LL, 9LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 8LL, 5LL, 7LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_136() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(-7LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(-9LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(-6LL);
        sd.ints.push_back(-4LL);
        sd.ints.push_back(-100LL);
        sd.strs.push_back("a");
        sd.strs.push_back("b");
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, 1LL, 3LL, 5LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{0LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{0LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, 1LL, 3LL, 5LL, 7LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 4LL, 5LL, 6LL, -2LL});
        sd.ivecs.push_back(std::vector<long long>{-2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 5LL, 3LL, 6LL, 2LL, 7LL, -7LL});
        sd.ivecs.push_back(std::vector<long long>{-7LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{7LL, 3LL, 8LL, 4LL, 9LL, 2LL, 5LL, -9LL});
        sd.ivecs.push_back(std::vector<long long>{-9LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -3LL, -5LL, -6LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -3LL, -5LL, -6LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{-6LL, -4LL, -4LL, -3LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{-3LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{-6LL, -4LL, -4LL, -3LL, -100LL, 1LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

// CPP/129 vector<int> minPath(vector<vector<int>> grid, int k)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_129();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::vector<int> > a0 = probe::gen_vec_vec_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("minPath(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(minPath(a0, a1)); }, result)) continue;
        probe::emit(out, "minPath", "vec_int", call, result);
        ++kept;
    }
}

// CPP/130 vector<int> tri(int n)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_130();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("tri(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(tri(a0)); }, result)) continue;
        probe::emit(out, "tri", "vec_int", call, result);
        ++kept;
    }
}

// CPP/131 int digits(int n)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_131();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("digits(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(digits(a0)); }, result)) continue;
        probe::emit(out, "digits", "int", call, result);
        ++kept;
    }
}

// CPP/132 bool is_nested(string str)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_132();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("is_nested(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(is_nested(a0)); }, result)) continue;
        probe::emit(out, "is_nested", "bool", call, result);
        ++kept;
    }
}

// CPP/133 int sum_squares(vector<float> lst)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_133();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("sum_squares(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(sum_squares(a0)); }, result)) continue;
        probe::emit(out, "sum_squares", "int", call, result);
        ++kept;
    }
}

// CPP/134 bool check_if_last_char_is_a_letter(string txt)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_134();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("check_if_last_char_is_a_letter(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(check_if_last_char_is_a_letter(a0)); }, result)) continue;
        probe::emit(out, "check_if_last_char_is_a_letter", "bool", call, result);
        ++kept;
    }
}

// CPP/135 int can_arrange(vector<int> arr)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_135();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("can_arrange(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(can_arrange(a0)); }, result)) continue;
        probe::emit(out, "can_arrange", "int", call, result);
        ++kept;
    }
}

// CPP/136 vector<int> largest_smallest_integers(vector<int> lst)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_136();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("largest_smallest_integers(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(largest_smallest_integers(a0)); }, result)) continue;
        probe::emit(out, "largest_smallest_integers", "vec_int", call, result);
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
