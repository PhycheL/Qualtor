// 探针生成器的公共部分：随机输入、C++ 字面值输出、隔离执行。由 import_humaneval_x.py 复制进各题的生成器目录。
// 生成器只在出题时运行；每个输入在 fork 出的子进程里执行，崩溃、超时、触发 ASan/UBSan 或超过 20 毫秒的输入全部丢弃。
#pragma once

#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace probe {

struct Rng {
    unsigned long long state;
    explicit Rng(unsigned long long seed) : state(seed * 6364136223846793005ULL + 1442695040888963407ULL) {}
    unsigned long long next() {
        state ^= state >> 12;
        state ^= state << 25;
        state ^= state >> 27;
        return state * 2685821657736338717ULL;
    }
    int below(int n) { return n <= 0 ? 0 : static_cast<int>(next() % static_cast<unsigned long long>(n)); }
    int range(int lo, int hi) { return lo + below(hi - lo + 1); }
    bool chance(int percent) { return below(100) < percent; }
};

struct Seeds {
    std::vector<long long> ints;
    std::vector<double> reals;
    std::vector<std::string> strs;
    std::vector<std::vector<long long> > ivecs;
    std::vector<std::vector<double> > fvecs;
    std::vector<std::vector<std::string> > svecs;
};

// ---- C++ 字面值 ----

inline std::string lit(int v) {
    if (v == INT_MIN) return "(-2147483647 - 1)";
    char b[32];
    snprintf(b, sizeof b, "%d", v);
    return b;
}
inline std::string lit(long long v) {
    if (v == LLONG_MIN) return "(-9223372036854775807LL - 1)";
    char b[48];
    snprintf(b, sizeof b, "%lldLL", v);
    return b;
}
inline std::string lit(bool v) { return v ? "true" : "false"; }
inline std::string real_text(double v, int digits) {
    char b[64];
    snprintf(b, sizeof b, "%.*g", digits, v);
    std::string s = b;
    if (s.find_first_of(".eEn") == std::string::npos) s += ".0";
    return s;
}
inline std::string lit(float v) { return real_text(v, 9) + "f"; }
inline std::string lit(double v) { return real_text(v, 17); }
inline std::string escape(const std::string& s, char quote) {
    std::string o;
    for (size_t i = 0; i < s.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if (c == static_cast<unsigned char>(quote) || c == '\\') {
            o += '\\';
            o += static_cast<char>(c);
        } else if (c == '?') {
            o += "\\?";  // 避免 C++11 三字符组
        } else if (c >= 32 && c < 127) {
            o += static_cast<char>(c);
        } else {
            char b[8];
            snprintf(b, sizeof b, "\\%03o", c);
            o += b;
        }
    }
    return o;
}
inline std::string lit(char c) { return "'" + escape(std::string(1, c), '\'') + "'"; }
inline std::string lit(const std::string& s) {
    if (s.find('\0') != std::string::npos) {
        char b[32];
        snprintf(b, sizeof b, ", %lu)", static_cast<unsigned long>(s.size()));
        return "std::string(\"" + escape(s, '"') + "\"" + b;
    }
    return "std::string(\"" + escape(s, '"') + "\")";
}
inline std::string type_name(int) { return "int"; }
inline std::string type_name(long long) { return "long long"; }
inline std::string type_name(float) { return "float"; }
inline std::string type_name(double) { return "double"; }
inline std::string type_name(const std::string&) { return "std::string"; }
template <class T>
std::string type_name(const std::vector<T>&) { return "std::vector<" + type_name(T()) + " >"; }
template <class T>
std::string lit(const std::vector<T>& v) {
    std::string o = type_name(v) + "{";
    for (size_t i = 0; i < v.size(); ++i) o += (i ? ", " : "") + lit(v[i]);
    return o + "}";
}
template <class K, class V>
std::string lit(const std::map<K, V>& m) {
    std::string o = "std::map<" + std::string(sizeof(K) == 1 ? "char" : "std::string") + ", " +
                    (sizeof(V) == sizeof(int) ? "int" : "std::string") + " >{";
    bool first = true;
    for (typename std::map<K, V>::const_iterator it = m.begin(); it != m.end(); ++it) {
        o += (first ? "{" : ", {") + lit(it->first) + ", " + lit(it->second) + "}";
        first = false;
    }
    return o + "}";
}

// ---- 随机输入 ----

inline int fit_int(long long v) { return v > INT_MAX ? INT_MAX : (v < INT_MIN ? INT_MIN : static_cast<int>(v)); }
inline long long gen_ll(Rng& r, const Seeds& sd) {
    int roll = r.below(100);
    if (roll < 40 && !sd.ints.empty()) {
        long long v = sd.ints[r.below(static_cast<int>(sd.ints.size()))];
        return r.chance(35) ? v + r.range(-2, 2) : v;
    }
    if (roll < 80) return r.range(-10, 30);
    if (roll < 95) return r.range(-1000, 1000);
    static const long long special[] = {0, 1, 2, -1, 10, 100, 1000, 12345, 99999};
    return special[r.below(9)];
}
inline int gen_int(Rng& r, const Seeds& sd) { return fit_int(gen_ll(r, sd)); }
inline double gen_double(Rng& r, const Seeds& sd) {
    int roll = r.below(100);
    if (roll < 40 && !sd.reals.empty()) {
        double v = sd.reals[r.below(static_cast<int>(sd.reals.size()))];
        return r.chance(35) ? v + r.range(-20, 20) / 10.0 : v;
    }
    if (roll < 55 && !sd.ints.empty()) return static_cast<double>(sd.ints[r.below(static_cast<int>(sd.ints.size()))]);
    if (roll < 90) return r.range(-200, 200) / 10.0;
    return r.range(-1000, 1000) / 100.0;
}
inline float gen_float(Rng& r, const Seeds& sd) { return static_cast<float>(gen_double(r, sd)); }
inline std::string charset(const Seeds& sd) {
    std::string cs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    for (size_t i = 0; i < sd.strs.size(); ++i)
        for (size_t j = 0; j < sd.strs[i].size(); ++j)
            if (cs.find(sd.strs[i][j]) == std::string::npos) cs += sd.strs[i][j];
    return cs;
}
inline std::string gen_string(Rng& r, const Seeds& sd) {
    const std::string cs = charset(sd);
    int roll = r.below(100);
    std::string s;
    if (roll < 70 && !sd.strs.empty()) {
        s = sd.strs[r.below(static_cast<int>(sd.strs.size()))];
        if (roll >= 35) {
            int edits = r.range(1, 3);
            for (int i = 0; i < edits; ++i) {
                int op = r.below(3);
                char c = cs[r.below(static_cast<int>(cs.size()))];
                size_t pos = s.empty() ? 0 : static_cast<size_t>(r.below(static_cast<int>(s.size())));
                if (op == 0 || s.empty()) s.insert(s.begin() + pos, c);
                else if (op == 1) s[pos] = c;
                else s.erase(s.begin() + pos);
            }
        }
        return s;
    }
    int len = r.range(0, 12);
    for (int i = 0; i < len; ++i) s += cs[r.below(static_cast<int>(cs.size()))];
    return s;
}
template <class T, class Gen>
std::vector<T> mutate_vec(Rng& r, std::vector<T> v, Gen gen) {
    int op = r.below(4);
    if (op == 0 || v.empty()) v.push_back(gen());
    else if (op == 1) v[r.below(static_cast<int>(v.size()))] = gen();
    else if (op == 2) v.erase(v.begin() + r.below(static_cast<int>(v.size())));
    else std::swap(v[r.below(static_cast<int>(v.size()))], v[r.below(static_cast<int>(v.size()))]);
    return v;
}
struct IntGen { Rng* r; const Seeds* sd; int operator()() const { return gen_int(*r, *sd); } };
struct LlGen { Rng* r; const Seeds* sd; long long operator()() const { return gen_ll(*r, *sd); } };
struct FloatGen { Rng* r; const Seeds* sd; float operator()() const { return gen_float(*r, *sd); } };
struct DoubleGen { Rng* r; const Seeds* sd; double operator()() const { return gen_double(*r, *sd); } };
struct StringGen { Rng* r; const Seeds* sd; std::string operator()() const { return gen_string(*r, *sd); } };

template <class T, class Gen, class Seed>
std::vector<T> gen_vec(Rng& r, const std::vector<std::vector<Seed> >& seeds, Gen gen) {
    int roll = r.below(100);
    std::vector<T> v;
    if (roll < 65 && !seeds.empty()) {
        const std::vector<Seed>& s = seeds[r.below(static_cast<int>(seeds.size()))];
        for (size_t i = 0; i < s.size(); ++i) v.push_back(static_cast<T>(s[i]));
        return roll < 30 ? v : mutate_vec(r, v, gen);
    }
    int len = r.range(0, 8);
    for (int i = 0; i < len; ++i) v.push_back(gen());
    return v;
}
inline std::vector<int> gen_vec_int(Rng& r, const Seeds& sd) {
    std::vector<int> v = gen_vec<int>(r, sd.ivecs, IntGen{&r, &sd});
    for (size_t i = 0; i < v.size(); ++i) v[i] = fit_int(v[i]);
    return v;
}
inline std::vector<long long> gen_vec_ll(Rng& r, const Seeds& sd) { return gen_vec<long long>(r, sd.ivecs, LlGen{&r, &sd}); }
inline std::vector<float> gen_vec_float(Rng& r, const Seeds& sd) {
    return sd.fvecs.empty() ? gen_vec<float>(r, sd.ivecs, FloatGen{&r, &sd}) : gen_vec<float>(r, sd.fvecs, FloatGen{&r, &sd});
}
inline std::vector<double> gen_vec_double(Rng& r, const Seeds& sd) {
    return sd.fvecs.empty() ? gen_vec<double>(r, sd.ivecs, DoubleGen{&r, &sd}) : gen_vec<double>(r, sd.fvecs, DoubleGen{&r, &sd});
}
inline std::vector<std::string> gen_vec_string(Rng& r, const Seeds& sd) { return gen_vec<std::string>(r, sd.svecs, StringGen{&r, &sd}); }
inline std::vector<std::vector<int> > gen_vec_vec_int(Rng& r, const Seeds& sd) {
    std::vector<std::vector<int> > grid;
    int rows = r.range(0, 4), cols = r.range(0, 4);
    bool binary = r.chance(50);
    for (int i = 0; i < rows; ++i) {
        std::vector<int> row;
        int width = r.chance(80) ? cols : r.range(0, 4);
        for (int j = 0; j < width; ++j) row.push_back(binary ? r.below(2) : gen_int(r, sd));
        grid.push_back(row);
    }
    return grid;
}
inline std::map<std::string, std::string> gen_map_ss(Rng& r, const Seeds& sd) {
    std::map<std::string, std::string> m;
    int n = r.range(0, 3);
    for (int i = 0; i < n; ++i) {
        std::string key = gen_string(r, sd);
        if (r.chance(30))
            for (size_t j = 0; j < key.size(); ++j) key[j] = static_cast<char>(r.chance(50) ? toupper(key[j]) : tolower(key[j]));
        m[key] = gen_string(r, sd);
    }
    return m;
}

// ---- 隔离执行 ----

inline void dirty_stack(int byte) {
    volatile unsigned char block[65536];
    for (size_t i = 0; i < sizeof block; ++i) block[i] = static_cast<unsigned char>(byte);
}

template <class F>
bool run_case(F f, std::string& out) {
    fflush(0);  // fork 前清空缓冲，避免子进程退出时把父进程未写出的内容再写一遍
    int fds[2];
    if (pipe(fds) != 0) return false;
    pid_t pid = fork();
    if (pid < 0) return false;
    if (pid == 0) {
        close(fds[0]);
        int null_fd = open("/dev/null", O_WRONLY);
        if (null_fd >= 0) {
            dup2(null_fd, 1);
            dup2(null_fd, 2);
        }
        struct itimerval timer;
        memset(&timer, 0, sizeof timer);
        timer.it_value.tv_usec = 300000;
        setitimer(ITIMER_REAL, &timer, 0);
        const char* dirt = getenv("QUALTOR_PROBE_DIRT");
        dirty_stack(dirt ? atoi(dirt) : 0);
        struct timeval begin, end;
        gettimeofday(&begin, 0);
        std::string text = f();
        gettimeofday(&end, 0);
        long micros = (end.tv_sec - begin.tv_sec) * 1000000L + (end.tv_usec - begin.tv_usec);
        if (micros > 20000) _exit(3);
        size_t done = 0;
        while (done < text.size()) {
            ssize_t n = write(fds[1], text.data() + done, text.size() - done);
            if (n <= 0) _exit(4);
            done += static_cast<size_t>(n);
        }
        _exit(0);
    }
    close(fds[1]);
    out.clear();
    char buffer[4096];
    ssize_t n;
    while ((n = read(fds[0], buffer, sizeof buffer)) > 0) out.append(buffer, static_cast<size_t>(n));
    close(fds[0]);
    int status = 0;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) && WEXITSTATUS(status) == 0 && !out.empty();
}

inline bool finite_text(const std::string& text) {
    return text.find("nan") == std::string::npos && text.find("inf") == std::string::npos;
}

inline void emit(FILE* out, const char* function, const char* kind, const std::string& call, const std::string& result) {
    bool real = strstr(kind, "float") != 0 || strstr(kind, "double") != 0;
    if (real && !finite_text(result)) return;  // 非有限浮点结果无法写成字面值，丢弃
    fprintf(out, "%s\t%s\t%s\t%s\n", function, kind, call.c_str(), result.c_str());
}

}  // namespace probe
