// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_12.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_89() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("hi");
        sd.strs.push_back("lm");
        sd.strs.push_back("asdfghjkl");
        sd.strs.push_back("ewhjklnop");
        sd.strs.push_back("gf");
        sd.strs.push_back("kj");
        sd.strs.push_back("et");
        sd.strs.push_back("ix");
        sd.strs.push_back("faewfawefaewg");
        sd.strs.push_back("jeiajeaijeiak");
        sd.strs.push_back("hellomyfriend");
        sd.strs.push_back("lippsqcjvmirh");
        sd.strs.push_back("dxzdlmnilfuhmilufhlihufnmlimnufhlimnufhfucufh");
        sd.strs.push_back("hbdhpqrmpjylqmpyjlpmlyjrqpmqryjlpmqryjljygyjl");
        sd.strs.push_back("a");
        sd.strs.push_back("e");
    }
    return sd;
}

static const probe::Seeds& seeds_90() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(-35LL);
        sd.ints.push_back(34LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(-45LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 1LL, 4LL, 3LL, 2LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 1LL, 1LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{-35LL, 34LL, 12LL, -45LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_91() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.strs.push_back("I");
        sd.strs.push_back("Hello world");
        sd.strs.push_back("The sky is blue. The sun is shining. I love this weather");
        sd.strs.push_back("Is the sky blue?");
        sd.strs.push_back("I love It !");
        sd.strs.push_back("bIt");
        sd.strs.push_back("I feel good today. I will be productive. will kill It");
        sd.strs.push_back("You and I are going for a walk");
    }
    return sd;
}

static const probe::Seeds& seeds_92() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(-4LL);
        sd.reals.push_back(3.6);
        sd.reals.push_back(-2.2);
        sd.reals.push_back(2.5);
        sd.reals.push_back(1.5);
        sd.reals.push_back(3.5);
        sd.reals.push_back(2.2);
        sd.reals.push_back(3.01);
    }
    return sd;
}

static const probe::Seeds& seeds_93() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.strs.push_back("TGST");
        sd.strs.push_back("This is a message");
        sd.strs.push_back("TEST");
        sd.strs.push_back("tgst");
        sd.strs.push_back("Mudasir");
        sd.strs.push_back("mWDCSKR");
        sd.strs.push_back("YES");
        sd.strs.push_back("ygs");
        sd.strs.push_back("tHKS KS C MGSSCGG");
        sd.strs.push_back("I DoNt KnOw WhAt tO WrItE");
        sd.strs.push_back("k dQnT kNqW wHcT Tq wRkTg");
        sd.strs.push_back("test");
    }
    return sd;
}

static const probe::Seeds& seeds_94() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(181LL);
        sd.ints.push_back(32LL);
        sd.ints.push_back(324LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(4597LL);
        sd.ints.push_back(40LL);
        sd.ints.push_back(25LL);
        sd.ints.push_back(5107LL);
        sd.ints.push_back(34LL);
        sd.ints.push_back(83278LL);
        sd.ints.push_back(109LL);
        sd.ints.push_back(163LL);
        sd.ints.push_back(23LL);
        sd.ints.push_back(2323LL);
        sd.ints.push_back(30LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(724LL);
        sd.ints.push_back(71LL);
        sd.ints.push_back(99LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(91LL);
        sd.ints.push_back(83LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(81LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(8191LL);
        sd.ints.push_back(19LL);
        sd.ints.push_back(123456LL);
        sd.ints.push_back(127LL);
        sd.ints.push_back(97LL);
        sd.ints.push_back(8192LL);
        sd.ivecs.push_back(std::vector<long long>{0LL, 3LL, 2LL, 1LL, 3LL, 5LL, 7LL, 4LL, 5LL, 5LL, 5LL, 2LL, 181LL, 32LL, 4LL, 32LL, 3LL, 2LL, 32LL, 324LL, 4LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 0LL, 1LL, 8LL, 2LL, 4597LL, 2LL, 1LL, 3LL, 40LL, 1LL, 2LL, 1LL, 2LL, 4LL, 2LL, 5LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 1LL, 32LL, 5107LL, 34LL, 83278LL, 109LL, 163LL, 23LL, 2323LL, 32LL, 30LL, 1LL, 9LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 724LL, 32LL, 71LL, 99LL, 32LL, 6LL, 0LL, 5LL, 91LL, 83LL, 0LL, 5LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 81LL, 12LL, 3LL, 1LL, 21LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 8LL, 1LL, 2LL, 1LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{8191LL});
        sd.ivecs.push_back(std::vector<long long>{8191LL, 123456LL, 127LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{127LL, 97LL, 8192LL});
    }
    return sd;
}

static const probe::Seeds& seeds_95() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(8LL);
        sd.ints.push_back(36LL);
        sd.ints.push_back(12345LL);
        sd.ints.push_back(5LL);
        sd.strs.push_back("a");
        sd.strs.push_back("apple");
        sd.strs.push_back("b");
        sd.strs.push_back("banana");
        sd.strs.push_back("A");
        sd.strs.push_back("B");
        sd.strs.push_back("8");
        sd.strs.push_back("Name");
        sd.strs.push_back("John");
        sd.strs.push_back("Age");
        sd.strs.push_back("36");
        sd.strs.push_back("City");
        sd.strs.push_back("Houston");
        sd.strs.push_back("STATE");
        sd.strs.push_back("NC");
        sd.strs.push_back("ZIP");
        sd.strs.push_back("12345");
        sd.strs.push_back("p");
        sd.strs.push_back("pineapple");
        sd.strs.push_back("5");
        sd.strs.push_back("fruit");
        sd.strs.push_back("Orange");
        sd.strs.push_back("taste");
        sd.strs.push_back("Sweet");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{"a", "apple"});
        sd.svecs.push_back(std::vector<std::string>{"b", "banana"});
        sd.svecs.push_back(std::vector<std::string>{"A", "banana"});
        sd.svecs.push_back(std::vector<std::string>{"B", "banana"});
        sd.svecs.push_back(std::vector<std::string>{"8", "banana"});
        sd.svecs.push_back(std::vector<std::string>{"Name", "John"});
        sd.svecs.push_back(std::vector<std::string>{"Age", "36"});
        sd.svecs.push_back(std::vector<std::string>{"City", "Houston"});
        sd.svecs.push_back(std::vector<std::string>{"STATE", "NC"});
        sd.svecs.push_back(std::vector<std::string>{"ZIP", "12345"});
        sd.svecs.push_back(std::vector<std::string>{"p", "pineapple"});
        sd.svecs.push_back(std::vector<std::string>{"5", "banana"});
        sd.svecs.push_back(std::vector<std::string>{"fruit", "Orange"});
        sd.svecs.push_back(std::vector<std::string>{"taste", "Sweet"});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_96() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(5LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(17LL);
        sd.ints.push_back(19LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(18LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(22LL);
        sd.ints.push_back(47LL);
        sd.ints.push_back(23LL);
        sd.ints.push_back(29LL);
        sd.ints.push_back(31LL);
        sd.ints.push_back(37LL);
        sd.ints.push_back(41LL);
        sd.ints.push_back(43LL);
        sd.ints.push_back(101LL);
        sd.ints.push_back(53LL);
        sd.ints.push_back(59LL);
        sd.ints.push_back(61LL);
        sd.ints.push_back(67LL);
        sd.ints.push_back(71LL);
        sd.ints.push_back(73LL);
        sd.ints.push_back(79LL);
        sd.ints.push_back(83LL);
        sd.ints.push_back(89LL);
        sd.ints.push_back(97LL);
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 5LL, 7LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL, 41LL, 43LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL, 41LL, 43LL, 47LL, 53LL, 59LL, 61LL, 67LL, 71LL, 73LL, 79LL, 83LL, 89LL, 97LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

// CPP/89 string encrypt(string s)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_89();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("encrypt(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(encrypt(a0)); }, result)) continue;
        probe::emit(out, "encrypt", "string", call, result);
        ++kept;
    }
}

// CPP/90 int next_smallest(vector<int> lst)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_90();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("next_smallest(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(next_smallest(a0)); }, result)) continue;
        probe::emit(out, "next_smallest", "int", call, result);
        ++kept;
    }
}

// CPP/91 int is_bored(string S)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_91();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("is_bored(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(is_bored(a0)); }, result)) continue;
        probe::emit(out, "is_bored", "int", call, result);
        ++kept;
    }
}

// CPP/92 bool any_int(float a,float b,float c)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_92();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        float a0 = probe::gen_float(rng, sd);
        float a1 = probe::gen_float(rng, sd);
        float a2 = probe::gen_float(rng, sd);
        std::string call = std::string("any_int(") + probe::lit(a0) + ", " + probe::lit(a1) + ", " + probe::lit(a2) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(any_int(a0, a1, a2)); }, result)) continue;
        probe::emit(out, "any_int", "bool", call, result);
        ++kept;
    }
}

// CPP/93 string encode(string message)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_93();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("encode(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(encode(a0)); }, result)) continue;
        probe::emit(out, "encode", "string", call, result);
        ++kept;
    }
}

// CPP/94 int skjkasdkd(vector<int> lst)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_94();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("skjkasdkd(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(skjkasdkd(a0)); }, result)) continue;
        probe::emit(out, "skjkasdkd", "int", call, result);
        ++kept;
    }
}

// CPP/95 bool check_dict_case(map<string,string> dict)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_95();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::map<std::string, std::string> a0 = probe::gen_map_ss(rng, sd);
        std::string call = std::string("check_dict_case(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(check_dict_case(a0)); }, result)) continue;
        probe::emit(out, "check_dict_case", "bool", call, result);
        ++kept;
    }
}

// CPP/96 vector<int> count_up_to(int n)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_96();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("count_up_to(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(count_up_to(a0)); }, result)) continue;
        probe::emit(out, "count_up_to", "vec_int", call, result);
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
