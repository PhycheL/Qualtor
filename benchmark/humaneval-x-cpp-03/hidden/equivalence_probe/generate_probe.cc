// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_03.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_16() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(1LL);
        sd.strs.push_back("xyzXYZ");
        sd.strs.push_back("Jerry");
        sd.strs.push_back("");
        sd.strs.push_back("abcde");
        sd.strs.push_back("abcdecadeCADE");
        sd.strs.push_back("aaaaAAAAaaaa");
        sd.strs.push_back("Jerry jERRY JeRRRY");
    }
    return sd;
}

static const probe::Seeds& seeds_17() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(4LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(0LL);
        sd.strs.push_back("o");
        sd.strs.push_back("o|");
        sd.strs.push_back(".|");
        sd.strs.push_back("o o| .| o| o| .| .| .| .| o o");
        sd.strs.push_back("");
        sd.strs.push_back("o o o o");
        sd.strs.push_back(".| .| .| .|");
        sd.strs.push_back("o| o| .| .| o o o o");
        sd.strs.push_back("o| .| o| .| o o| o o|");
        sd.ivecs.push_back(std::vector<long long>{4LL, 2LL, 1LL, 2LL, 2LL, 1LL, 1LL, 1LL, 1LL, 4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{4LL, 4LL, 4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 2LL, 1LL, 1LL, 4LL, 4LL, 4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 1LL, 2LL, 1LL, 4LL, 2LL, 4LL, 2LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_18() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(1LL);
        sd.strs.push_back("");
        sd.strs.push_back("a");
        sd.strs.push_back("aaa");
        sd.strs.push_back("aaaa");
        sd.strs.push_back("aa");
        sd.strs.push_back("x");
        sd.strs.push_back("xyxyxyx");
        sd.strs.push_back("cacacacac");
        sd.strs.push_back("cac");
        sd.strs.push_back("john doe");
        sd.strs.push_back("john");
    }
    return sd;
}

static const probe::Seeds& seeds_19() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("zero");
        sd.strs.push_back("nine");
        sd.strs.push_back("one");
        sd.strs.push_back(", 'three");
        sd.strs.push_back("four");
        sd.strs.push_back("five");
        sd.strs.push_back(", 'seven");
        sd.strs.push_back("eight");
        sd.strs.push_back("one three five");
        sd.strs.push_back("");
        sd.strs.push_back("three");
        sd.strs.push_back("three five nine");
        sd.strs.push_back("five zero four seven nine eight");
        sd.strs.push_back("zero four five seven eight nine");
        sd.strs.push_back("six five four three two one zero");
        sd.strs.push_back("zero one two three four five six");
        sd.strs.push_back("three one five");
    }
    return sd;
}

static const probe::Seeds& seeds_20() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.reals.push_back(1.0);
        sd.reals.push_back(2.0);
        sd.reals.push_back(3.0);
        sd.reals.push_back(4.0);
        sd.reals.push_back(5.0);
        sd.reals.push_back(2.2);
        sd.reals.push_back(1e-4);
        sd.reals.push_back(3.9);
        sd.reals.push_back(5.9);
        sd.reals.push_back(1.1);
        sd.reals.push_back(3.1);
        sd.reals.push_back(4.1);
        sd.reals.push_back(5.1);
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 2.2});
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 2.0});
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.9, 4.0, 5.0, 2.2});
        sd.fvecs.push_back(std::vector<double>{3.9, 4.0});
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 5.9, 4.0, 5.0});
        sd.fvecs.push_back(std::vector<double>{5.0, 5.9});
        sd.fvecs.push_back(std::vector<double>{2.0, 2.2});
        sd.fvecs.push_back(std::vector<double>{2.0, 2.0});
        sd.fvecs.push_back(std::vector<double>{1.1, 2.2, 3.1, 4.1, 5.1});
        sd.fvecs.push_back(std::vector<double>{2.2, 3.1});
    }
    return sd;
}

static const probe::Seeds& seeds_21() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.reals.push_back(1.0);
        sd.reals.push_back(2.0);
        sd.reals.push_back(3.0);
        sd.reals.push_back(4.0);
        sd.reals.push_back(5.0);
        sd.reals.push_back(0.0);
        sd.reals.push_back(0.25);
        sd.reals.push_back(0.5);
        sd.reals.push_back(0.75);
        sd.reals.push_back(1e-4);
        sd.reals.push_back(49.9);
        sd.reals.push_back(100.0);
        sd.reals.push_back(12.0);
        sd.reals.push_back(11.0);
        sd.reals.push_back(15.0);
        sd.reals.push_back(13.0);
        sd.reals.push_back(14.0);
        sd.fvecs.push_back(std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0});
        sd.fvecs.push_back(std::vector<double>{0.0, 0.25, 0.5, 0.75, 1.0});
        sd.fvecs.push_back(std::vector<double>{2.0, 49.9});
        sd.fvecs.push_back(std::vector<double>{0.0, 1.0});
        sd.fvecs.push_back(std::vector<double>{100.0, 49.9});
        sd.fvecs.push_back(std::vector<double>{1.0, 0.0});
        sd.fvecs.push_back(std::vector<double>{2.0, 1.0, 5.0, 3.0, 4.0});
        sd.fvecs.push_back(std::vector<double>{0.25, 0.0, 1.0, 0.5, 0.75});
        sd.fvecs.push_back(std::vector<double>{12.0, 11.0, 15.0, 13.0, 14.0});
    }
    return sd;
}

static const probe::Seeds& seeds_23() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(9LL);
        sd.strs.push_back("");
        sd.strs.push_back("abc");
        sd.strs.push_back("x");
        sd.strs.push_back("asdasnakj");
    }
    return sd;
}

static const probe::Seeds& seeds_24() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(15LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(50LL);
        sd.ints.push_back(49LL);
    }
    return sd;
}

// CPP/16 int count_distinct_characters(string str)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_16();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("count_distinct_characters(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(count_distinct_characters(a0)); }, result)) continue;
        probe::emit(out, "count_distinct_characters", "int", call, result);
        ++kept;
    }
}

// CPP/17 vector<int> parse_music(string music_string)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_17();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("parse_music(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(parse_music(a0)); }, result)) continue;
        probe::emit(out, "parse_music", "vec_int", call, result);
        ++kept;
    }
}

// CPP/18 int how_many_times(string str,string substring)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_18();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string a1 = probe::gen_string(rng, sd);
        std::string call = std::string("how_many_times(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(how_many_times(a0, a1)); }, result)) continue;
        probe::emit(out, "how_many_times", "int", call, result);
        ++kept;
    }
}

// CPP/19 string sort_numbers(string numbers)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_19();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("sort_numbers(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(sort_numbers(a0)); }, result)) continue;
        probe::emit(out, "sort_numbers", "string", call, result);
        ++kept;
    }
}

// CPP/20 vector<float> find_closest_elements(vector<float> numbers)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_20();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("find_closest_elements(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(find_closest_elements(a0)); }, result)) continue;
        probe::emit(out, "find_closest_elements", "vec_float", call, result);
        ++kept;
    }
}

// CPP/21 vector<float> rescale_to_unit(vector<float> numbers)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_21();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("rescale_to_unit(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(rescale_to_unit(a0)); }, result)) continue;
        probe::emit(out, "rescale_to_unit", "vec_float", call, result);
        ++kept;
    }
}

// CPP/23 int strlen(string str)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_23();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("strlen(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(strlen(a0)); }, result)) continue;
        probe::emit(out, "strlen", "int", call, result);
        ++kept;
    }
}

// CPP/24 int largest_divisor(int n)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_24();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("largest_divisor(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(largest_divisor(a0)); }, result)) continue;
        probe::emit(out, "largest_divisor", "int", call, result);
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
