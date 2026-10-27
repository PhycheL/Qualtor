// 探针生成器（由 benchmark/tools/import_humaneval_x.py 生成）：在原代码上执行随机输入，按行输出
// “函数\t结果类型\t调用表达式\t结果字面值”。构建与运行方式见同目录上级的 README.md。
#include "humaneval_x_cpp_15.h"
#include "probe_prelude.h"

static const probe::Seeds& seeds_113() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1234567LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(11111111LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(271LL);
        sd.ints.push_back(137LL);
        sd.ints.push_back(314LL);
        sd.ints.push_back(2LL);
        sd.strs.push_back("1234567");
        sd.strs.push_back("3");
        sd.strs.push_back("11111111");
        sd.strs.push_back("the number of odd elements 4n the str4ng 4 of the 4nput.");
        sd.strs.push_back("the number of odd elements 1n the str1ng 1 of the 1nput.");
        sd.strs.push_back("the number of odd elements 8n the str8ng 8 of the 8nput.");
        sd.strs.push_back("271");
        sd.strs.push_back("137");
        sd.strs.push_back("314");
        sd.strs.push_back("the number of odd elements 2n the str2ng 2 of the 2nput.");
        sd.strs.push_back("the number of odd elements 3n the str3ng 3 of the 3nput.");
        sd.svecs.push_back(std::vector<std::string>{"1234567"});
        sd.svecs.push_back(std::vector<std::string>{"3", "11111111"});
        sd.svecs.push_back(std::vector<std::string>{"the number of odd elements 4n the str4ng 4 of the 4nput."});
        sd.svecs.push_back(std::vector<std::string>{"the number of odd elements 1n the str1ng 1 of the 1nput.", "the number of odd elements 8n the str8ng 8 of the 8nput."});
        sd.svecs.push_back(std::vector<std::string>{"271", "137", "314"});
        sd.svecs.push_back(std::vector<std::string>{"the number of odd elements 2n the str2ng 2 of the 2nput.", "the number of odd elements 3n the str3ng 3 of the 3nput.", "the number of odd elements 2n the str2ng 2 of the 2nput."});
    }
    return sd;
}

static const probe::Seeds& seeds_114() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(1LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(-6LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(-14LL);
        sd.ints.push_back(-9999999999999999LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(1000000LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(100LL);
        sd.ints.push_back(11LL);
        sd.ints.push_back(13LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(-33LL);
        sd.ints.push_back(32LL);
        sd.ints.push_back(7LL);
        sd.ivecs.push_back(std::vector<long long>{2LL, 3LL, 4LL, 1LL, 2LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -2LL, -3LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -2LL, -3LL, 2LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{-9999999999999999LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 10LL, 20LL, 1000000LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, -2LL, -3LL, 10LL, -5LL});
        sd.ivecs.push_back(std::vector<long long>{100LL, -1LL, -2LL, -3LL, 10LL, -5LL});
        sd.ivecs.push_back(std::vector<long long>{10LL, 11LL, 13LL, 8LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{100LL, -33LL, 32LL, -1LL, 0LL, -2LL});
        sd.ivecs.push_back(std::vector<long long>{-10LL});
        sd.ivecs.push_back(std::vector<long long>{7LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, -1LL});
    }
    return sd;
}

static const probe::Seeds& seeds_115() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(9LL);
        sd.ivecs.push_back(std::vector<long long>{0LL, 0LL, 1LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL, 0LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1LL, 1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 0LL, 1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 0LL, 0LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL, 1LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 0LL, 0LL});
    }
    return sd;
}

static const probe::Seeds& seeds_116() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(-4LL);
        sd.ints.push_back(-5LL);
        sd.ints.push_back(-6LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(77LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(6LL);
        sd.ints.push_back(44LL);
        sd.ints.push_back(12LL);
        sd.ints.push_back(32LL);
        sd.ints.push_back(8LL);
        sd.ints.push_back(16LL);
        sd.ivecs.push_back(std::vector<long long>{1LL, 5LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{-2LL, -3LL, -4LL, -5LL, -6LL});
        sd.ivecs.push_back(std::vector<long long>{-6LL, -5LL, -4LL, -3LL, -2LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 0LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 4LL, 3LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{-4LL, -2LL, -6LL, -5LL, -3LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL, 2LL, 4LL, 3LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.ivecs.push_back(std::vector<long long>{2LL, 5LL, 77LL, 4LL, 5LL, 3LL, 5LL, 7LL, 2LL, 3LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 2LL, 4LL, 4LL, 3LL, 3LL, 5LL, 5LL, 5LL, 7LL, 77LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 6LL, 44LL, 12LL, 32LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{32LL, 3LL, 5LL, 6LL, 12LL, 44LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 4LL, 8LL, 16LL, 32LL});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

static const probe::Seeds& seeds_117() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(4LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(1LL);
        sd.strs.push_back("Mary had a little lamb");
        sd.strs.push_back("little");
        sd.strs.push_back("Mary");
        sd.strs.push_back("lamb");
        sd.strs.push_back("Hello world");
        sd.strs.push_back("world");
        sd.strs.push_back("Uncle sam");
        sd.strs.push_back("Uncle");
        sd.strs.push_back("simple white space");
        sd.strs.push_back("");
        sd.strs.push_back("a b c d e f");
        sd.strs.push_back("b");
        sd.strs.push_back("c");
        sd.strs.push_back("d");
        sd.strs.push_back("f");
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{"little"});
        sd.svecs.push_back(std::vector<std::string>{"Mary", "lamb"});
        sd.svecs.push_back(std::vector<std::string>{});
        sd.svecs.push_back(std::vector<std::string>{"world"});
        sd.svecs.push_back(std::vector<std::string>{"Uncle"});
        sd.svecs.push_back(std::vector<std::string>{"b", "c", "d", "f"});
    }
    return sd;
}

static const probe::Seeds& seeds_118() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("yogurt");
        sd.strs.push_back("u");
        sd.strs.push_back("FULL");
        sd.strs.push_back("U");
        sd.strs.push_back("quick");
        sd.strs.push_back("");
        sd.strs.push_back("ab");
        sd.strs.push_back("full");
        sd.strs.push_back("easy");
        sd.strs.push_back("eAsy");
        sd.strs.push_back("ali");
        sd.strs.push_back("bad");
        sd.strs.push_back("a");
        sd.strs.push_back("most");
        sd.strs.push_back("o");
        sd.strs.push_back("ba");
        sd.strs.push_back("anime");
        sd.strs.push_back("i");
        sd.strs.push_back("Asia");
        sd.strs.push_back("Above");
    }
    return sd;
}

static const probe::Seeds& seeds_119() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.strs.push_back("(())()");
        sd.strs.push_back("())");
        sd.strs.push_back("Yes");
        sd.strs.push_back("No");
        sd.strs.push_back("()(");
        sd.strs.push_back(")");
        sd.strs.push_back("(()(())");
        sd.strs.push_back("())())");
        sd.strs.push_back(")())");
        sd.strs.push_back("(()()(");
        sd.strs.push_back("(())))");
        sd.strs.push_back("(()())((");
        sd.strs.push_back("()");
        sd.strs.push_back("(()(");
        sd.strs.push_back("()))()");
        sd.strs.push_back("((((");
        sd.strs.push_back("((())");
        sd.strs.push_back(")(()");
        sd.strs.push_back(")(");
        sd.strs.push_back("(");
        sd.svecs.push_back(std::vector<std::string>{"()(", ")"});
        sd.svecs.push_back(std::vector<std::string>{")", ")"});
        sd.svecs.push_back(std::vector<std::string>{"(()(())", "())())"});
        sd.svecs.push_back(std::vector<std::string>{")())", "(()()("});
        sd.svecs.push_back(std::vector<std::string>{"(())))", "(()())(("});
        sd.svecs.push_back(std::vector<std::string>{"()", "())"});
        sd.svecs.push_back(std::vector<std::string>{"(()(", "()))()"});
        sd.svecs.push_back(std::vector<std::string>{"((((", "((())"});
        sd.svecs.push_back(std::vector<std::string>{")(()", "(()("});
        sd.svecs.push_back(std::vector<std::string>{")(", ")("});
        sd.svecs.push_back(std::vector<std::string>{"(", ")"});
        sd.svecs.push_back(std::vector<std::string>{")", "("});
    }
    return sd;
}

static const probe::Seeds& seeds_120() {
    static probe::Seeds sd;
    static bool ready = false;
    if (!ready) {
        ready = true;
        sd.ints.push_back(1LL);
        sd.ints.push_back(-3LL);
        sd.ints.push_back(-4LL);
        sd.ints.push_back(5LL);
        sd.ints.push_back(3LL);
        sd.ints.push_back(2LL);
        sd.ints.push_back(4LL);
        sd.ints.push_back(-1LL);
        sd.ints.push_back(-2LL);
        sd.ints.push_back(1000LL);
        sd.ints.push_back(-1000LL);
        sd.ints.push_back(0LL);
        sd.ints.push_back(123LL);
        sd.ints.push_back(-123LL);
        sd.ints.push_back(20LL);
        sd.ints.push_back(15LL);
        sd.ints.push_back(-13LL);
        sd.ints.push_back(-8LL);
        sd.ints.push_back(7LL);
        sd.ints.push_back(-10LL);
        sd.ints.push_back(-7LL);
        sd.ints.push_back(10LL);
        sd.ints.push_back(-23LL);
        sd.ints.push_back(243LL);
        sd.ints.push_back(-400LL);
        sd.ivecs.push_back(std::vector<long long>{-3LL, -4LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{-4LL, -3LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, -4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{-3LL, 2LL, 1LL, 2LL, -1LL, -2LL, 1LL});
        sd.ivecs.push_back(std::vector<long long>{2LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 1000LL});
        sd.ivecs.push_back(std::vector<long long>{-1000LL, 1000LL});
        sd.ivecs.push_back(std::vector<long long>{123LL, -123LL, 20LL, 0LL, 1LL, 2LL, -3LL});
        sd.ivecs.push_back(std::vector<long long>{2LL, 20LL, 123LL});
        sd.ivecs.push_back(std::vector<long long>{-123LL, 20LL, 0LL, 1LL, 2LL, -3LL});
        sd.ivecs.push_back(std::vector<long long>{0LL, 1LL, 2LL, 20LL});
        sd.ivecs.push_back(std::vector<long long>{5LL, 15LL, 0LL, 3LL, -13LL, -8LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{-13LL, -8LL, 0LL, 0LL, 3LL, 5LL, 15LL});
        sd.ivecs.push_back(std::vector<long long>{-1LL, 0LL, 2LL, 5LL, 3LL, -10LL});
        sd.ivecs.push_back(std::vector<long long>{3LL, 5LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 0LL, 5LL, -7LL});
        sd.ivecs.push_back(std::vector<long long>{5LL});
        sd.ivecs.push_back(std::vector<long long>{4LL, -4LL});
        sd.ivecs.push_back(std::vector<long long>{-4LL, 4LL});
        sd.ivecs.push_back(std::vector<long long>{-10LL, 10LL});
        sd.ivecs.push_back(std::vector<long long>{1LL, 2LL, 3LL, -23LL, 243LL, -400LL, 0LL});
        sd.ivecs.push_back(std::vector<long long>{});
        sd.fvecs.push_back(std::vector<double>{});
        sd.svecs.push_back(std::vector<std::string>{});
    }
    return sd;
}

// CPP/113 vector<string> odd_count(vector<string> lst)
static void probe_0(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 0ULL);
    const probe::Seeds& sd = seeds_113();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::string> a0 = probe::gen_vec_string(rng, sd);
        std::string call = std::string("odd_count(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(odd_count(a0)); }, result)) continue;
        probe::emit(out, "odd_count", "vec_string", call, result);
        ++kept;
    }
}

// CPP/114 long long minSubArraySum(vector<long long> nums)
static void probe_1(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 1ULL);
    const probe::Seeds& sd = seeds_114();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<long long> a0 = probe::gen_vec_ll(rng, sd);
        std::string call = std::string("minSubArraySum(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(minSubArraySum(a0)); }, result)) continue;
        probe::emit(out, "minSubArraySum", "ll", call, result);
        ++kept;
    }
}

// CPP/115 int max_fill(vector<vector<int>> grid,int capacity)
static void probe_2(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 2ULL);
    const probe::Seeds& sd = seeds_115();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::vector<int> > a0 = probe::gen_vec_vec_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("max_fill(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(max_fill(a0, a1)); }, result)) continue;
        probe::emit(out, "max_fill", "int", call, result);
        ++kept;
    }
}

// CPP/116 vector<int> sort_array(vector<int> arr)
static void probe_3(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 3ULL);
    const probe::Seeds& sd = seeds_116();
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

// CPP/117 vector<string> select_words(string s,int n)
static void probe_4(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 4ULL);
    const probe::Seeds& sd = seeds_117();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("select_words(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(select_words(a0, a1)); }, result)) continue;
        probe::emit(out, "select_words", "vec_string", call, result);
        ++kept;
    }
}

// CPP/118 string get_closest_vowel(string word)
static void probe_5(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 5ULL);
    const probe::Seeds& sd = seeds_118();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::string a0 = probe::gen_string(rng, sd);
        std::string call = std::string("get_closest_vowel(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(get_closest_vowel(a0)); }, result)) continue;
        probe::emit(out, "get_closest_vowel", "string", call, result);
        ++kept;
    }
}

// CPP/119 string match_parens(vector<string> lst)
static void probe_6(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 6ULL);
    const probe::Seeds& sd = seeds_119();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<std::string> a0 = probe::gen_vec_string(rng, sd);
        std::string call = std::string("match_parens(") + probe::lit(a0) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(match_parens(a0)); }, result)) continue;
        probe::emit(out, "match_parens", "string", call, result);
        ++kept;
    }
}

// CPP/120 vector<int> maximum(vector<int> arr,int k)
static void probe_7(unsigned long long seed, int limit, FILE* out) {
    probe::Rng rng(seed * 1000003ULL + 7ULL);
    const probe::Seeds& sd = seeds_120();
    std::set<std::string> seen;
    int kept = 0;
    for (int attempt = 0; attempt < limit * 30 && kept < limit; ++attempt) {
        std::vector<int> a0 = probe::gen_vec_int(rng, sd);
        int a1 = probe::gen_int(rng, sd);
        std::string call = std::string("maximum(") + probe::lit(a0) + ", " + probe::lit(a1) + ")";
        if (!seen.insert(call).second) continue;
        std::string result;
        if (!probe::run_case([&]() { return probe::lit(maximum(a0, a1)); }, result)) continue;
        probe::emit(out, "maximum", "vec_int", call, result);
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
