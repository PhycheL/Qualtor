// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_19.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_146() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(10LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(-73LL);
        sd.ints.push_back(14LL);
        sd.ints.push_back(-15LL);
        sd.ints.push_back(33LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(45LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(109LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(43LL);
        sd.ints.push_back(-12LL);
        sd.ints.push_back(93LL);
        sd.ints.push_back(125LL);
        sd.ints.push_back(121LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(71LL);
        sd.ints.push_back(-33LL);
        sd.ints.push_back(75LL);
        sd.ints.push_back(19LL);
        sd.ivecs.push_back(std::vector<long long>{15LL, -73LL, 14LL, -15LL});
        sd.ivecs.push_back(std::vector<long long>{33LL, -2LL, -3LL, 45LL, 21LL, 109LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, -2LL, 1LL, -5LL});
        sd.ivecs.push_back(std::vector<long long>{43LL, -12LL, 93LL, 125LL, 121LL, 109LL});
        sd.ivecs.push_back(std::vector<long long>{71LL, -2LL, -33LL, 75LL, 21LL, 19LL});
        sd.ivecs.push_back(std::vector<long long>{1LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_147() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(21LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(36LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(53361LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 7LL, 13LL, 21LL});
    }
    return sd;
}

static const probe::Seeds& seeds_148() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.strs.push_back("Jupiter");
        sd.strs.push_back("Neptune");
        sd.strs.push_back("Saturn");
        sd.strs.push_back("Uranus");
        sd.strs.push_back("Earth");
        sd.strs.push_back("Mercury");
        sd.strs.push_back("Venus");
        sd.strs.push_back("Mars");
        sd.strs.push_back("Makemake");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{"Saturn", "Uranus"});
        sd.svecs.push_back(std::vector<std::string>{"Venus"});
        sd.svecs.push_back(std::vector<std::string>{"Venus", "Earth", "Mars", "Jupiter", "Saturn"});
        sd.svecs.push_back(std::vector<std::string>{"Earth", "Mars", "Jupiter", "Saturn", "Uranus"});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_149() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.strs.push_back("aa");
        sd.strs.push_back("a");
        sd.strs.push_back("aaa");
        sd.strs.push_back("ab");
        sd.strs.push_back("cd");
        sd.strs.push_back("school");
        sd.strs.push_back("AI");
        sd.strs.push_back("asdf");
        sd.strs.push_back("b");
        sd.strs.push_back("d");
        sd.strs.push_back("c");
        sd.strs.push_back("dcba");
        sd.strs.push_back("abcd");
        sd.strs.push_back("ai");
        sd.strs.push_back("au");
        sd.strs.push_back("aaaa");
        sd.strs.push_back("bbbb");
        sd.strs.push_back("dd");
        sd.strs.push_back("cc");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{"aa", "a", "aaa"});
        sd.svecs.push_back(std::vector<std::string>{"aa"});
        sd.svecs.push_back(std::vector<std::string>{"ab", "a", "aaa", "cd"});
        sd.svecs.push_back(std::vector<std::string>{"ab", "cd"});
        sd.svecs.push_back(std::vector<std::string>{"school", "AI", "asdf", "b"});
        sd.svecs.push_back(std::vector<std::string>{"AI", "asdf", "school"});
        sd.svecs.push_back(std::vector<std::string>{"d", "b", "c", "a"});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"d", "dcba", "abcd", "a"});
        sd.svecs.push_back(std::vector<std::string>{"abcd", "dcba"});
        sd.svecs.push_back(std::vector<std::string>{"AI", "ai", "au"});
        sd.svecs.push_back(std::vector<std::string>{"a", "b", "b", "c", "c", "a"});
        sd.svecs.push_back(std::vector<std::string>{"aaaa", "bbbb", "dd", "cc"});
        sd.svecs.push_back(std::vector<std::string>{"cc", "dd", "aaaa", "bbbb"});
    }
    return sd;
}

static const probe::Seeds& seeds_150() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(7LL);
        sd.ints.push_back(34LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(33LL);
        sd.ints.push_back(5212LL);
        sd.ints.push_back(1259LL);
        sd.ints.push_back(52LL);
        sd.ints.push_back(7919LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(3609LL);
        sd.ints.push_back(1245LL);
        sd.ints.push_back(583LL);
        sd.ints.push_back(91LL);
        sd.ints.push_back(56LL);
        sd.ints.push_back(129LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(1234LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(0LL);
    }
    return sd;
}

static const probe::Seeds& seeds_151() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(9LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(81LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(25LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(-20LL);
        sd.ints.push_back(-30LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(34LL);
        sd.ints.push_back(-99LL);
        sd.ints.push_back(100LL);
        sd.reals.push_back(0.1);
        sd.reals.push_back(0.2);
        sd.reals.push_back(0.3);
        sd.reals.push_back(0.0);
        sd.ivecs.push_back(std::vector<long long>{1LL, 3LL, 2LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -2LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{9LL, -2LL});
        sd.ivecs.push_back(std::vector<long long>{0LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{5LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{-10LL, -20LL, -30LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -2LL, 8LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.fvecs.push_back(std::vector<double>{0.1, 0.2, 0.3});
        sd.fvecs.push_back(std::vector<double>{0.2, 3, 5});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_152() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-3LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 2LL, -2LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 0LL, 0LL, 0LL, 3LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 5LL, 0LL, 0LL, 0LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 1LL, 1LL, 0LL, 0LL, -2LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 4LL, 1LL, 0LL, 0LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -2LL, -3LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, 6LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 0LL, 0LL, 1LL});
    }
    return sd;
}

static const probe::Seeds& seeds_153() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(-1LL);
        sd.ints.push_back(123LL);
        sd.ints.push_back(781345LL);
        sd.ints.push_back(91245LL);
        sd.ints.push_back(671235LL);
        sd.strs.push_back("Slices");
        sd.strs.push_back("SErviNGSliCes");
        sd.strs.push_back("Cheese");
        sd.strs.push_back("StuFfed");
        sd.strs.push_back("Slices.SErviNGSliCes");
        sd.strs.push_back("my_class");
        sd.strs.push_back("AA");
        sd.strs.push_back("Be");
        sd.strs.push_back("CC");
        sd.strs.push_back("my_class.AA");
        sd.strs.push_back("Watashi");
        sd.strs.push_back("tEN");
        sd.strs.push_back("niNE");
        sd.strs.push_back("eIGHt8OKe");
        sd.strs.push_back("Watashi.eIGHt8OKe");
        sd.strs.push_back("Boku123");
        sd.strs.push_back("nani");
        sd.strs.push_back("NazeDa");
        sd.strs.push_back("YEs.WeCaNe");
        sd.strs.push_back("32145tggg");
        sd.strs.push_back("Boku123.YEs.WeCaNe");
        sd.strs.push_back("__YESIMHERE");
        sd.strs.push_back("t");
        sd.strs.push_back("eMptY");
        sd.strs.push_back("(nothing");
        sd.strs.push_back("zeR00");
        sd.strs.push_back("NuLl__");
        sd.strs.push_back("123NoooneB321");
        sd.strs.push_back("__YESIMHERE.NuLl__");
        sd.strs.push_back("K");
        sd.strs.push_back("Ta");
        sd.strs.push_back("TAR");
        sd.strs.push_back("t234An");
        sd.strs.push_back("cosSo");
        sd.strs.push_back("K.TAR");
        sd.strs.push_back("__HAHA");
        sd.strs.push_back("Tab");
        sd.strs.push_back("123");
        sd.strs.push_back("781345");
        sd.strs.push_back("-_-");
        sd.strs.push_back("__HAHA.123");
        sd.strs.push_back("YameRore");
        sd.strs.push_back("HhAas");
        sd.strs.push_back("okIWILL123");
        sd.strs.push_back("WorkOut");
        sd.strs.push_back("Fails");
        sd.strs.push_back("YameRore.okIWILL123");
        sd.strs.push_back("finNNalLLly");
        sd.strs.push_back("Die");
        sd.strs.push_back("NowW");
        sd.strs.push_back("Wow");
        sd.strs.push_back("WoW");
        sd.strs.push_back("finNNalLLly.WoW");
        sd.strs.push_back("_");
        sd.strs.push_back("Bb");
        sd.strs.push_back("91245");
        sd.strs.push_back("_.Bb");
        sd.strs.push_back("Sp");
        sd.strs.push_back("671235");
        sd.strs.push_back("Sp.671235");
        sd.svecs.push_back(std::vector<std::string>{"SErviNGSliCes", "Cheese", "StuFfed"});
        sd.svecs.push_back(std::vector<std::string>{"AA", "Be", "CC"});
        sd.svecs.push_back(std::vector<std::string>{"tEN", "niNE", "eIGHt8OKe"});
        sd.svecs.push_back(std::vector<std::string>{"nani", "NazeDa", "YEs.WeCaNe", "32145tggg"});
        sd.svecs.push_back(std::vector<std::string>{"t", "eMptY", "(nothing", "zeR00", "NuLl__", "123NoooneB321"});
        sd.svecs.push_back(std::vector<std::string>{"Ta", "TAR", "t234An", "cosSo"});
        sd.svecs.push_back(std::vector<std::string>{"Tab", "123", "781345", "-_-"});
        sd.svecs.push_back(std::vector<std::string>{"HhAas", "okIWILL123", "WorkOut", "Fails", "-_-"});
        sd.svecs.push_back(std::vector<std::string>{"Die", "NowW", "Wow", "WoW"});
        sd.svecs.push_back(std::vector<std::string>{"Bb", "91245"});
        sd.svecs.push_back(std::vector<std::string>{"671235", "Bb"});
    }
    return sd;
}

// CPP/146 int specialFilter(vector<int> nums)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_146();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("specialFilter(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(specialFilter(a0)); }, result)) continue;
        probe::emit(out, "specialFilter", "int", call, result);
        ++kept;
    }
}

// CPP/147 int get_matrix_triples(int n)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_147();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        std::string call = std::string("get_matrix_triples(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(get_matrix_triples(a0)); }, result)) continue;
        probe::emit(out, "get_matrix_triples", "int", call, result);
        ++kept;
    }
}

// CPP/148 vector<string> bf(string planet1,string planet2)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_148();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string a1 = probe::gen_string(rng, sd);
        std::string call = std::string("bf(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(bf(a0, a1)); }, result)) continue;
        probe::emit(out, "bf", "vec_string", call, result);
        ++kept;
    }
}

// CPP/149 vector<string> sorted_list_sum(vector<string> lst)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_149();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::string> a0 = probe::gen_vec_string(rng, sd);
        std::string call = std::string("sorted_list_sum(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(sorted_list_sum(a0)); }, result)) continue;
        probe::emit(out, "sorted_list_sum", "vec_string", call, result);
        ++kept;
    }
}

// CPP/150 int x_or_y(int n,int x,int y)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_150();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        int a0 = probe::gen_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        int a2 = probe::gen_int(rng, sd);
        std::string call = std::string("x_or_y(") + probe::lit(a0) + ", " + probe::lit(a1) + ", " + probe::lit(a2) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(x_or_y(a0, a1, a2)); }, result)) continue;
        probe::emit(out, "x_or_y", "int", call, result);
        ++kept;
    }
}

// CPP/151 long long double_the_difference(vector<float> lst)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_151();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<float> a0 = probe::gen_vec_float(rng, sd);
        std::string call = std::string("double_the_difference(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(double_the_difference(a0)); }, result)) continue;
        probe::emit(out, "double_the_difference", "ll", call, result);
        ++kept;
    }
}

// CPP/152 vector<int> compare(vector<int> game,vector<int> guess)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_152();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        std::vector<int> a1 = probe::gen_vec_int(rng, sd);
        std::string call = std::string("compare(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(compare(a0, a1)); }, result)) continue;
        probe::emit(out, "compare", "vec_int", call, result);
        ++kept;
    }
}

// CPP/153 string Strongest_Extension(string class_name,vector<string> extensions)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_153();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::vector<std::string> a1 = probe::gen_vec_string(rng, sd);
        std::string call = std::string("Strongest_Extension(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(Strongest_Extension(a0, a1)); }, result)) continue;
        probe::emit(out, "Strongest_Extension", "string", call, result);
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
