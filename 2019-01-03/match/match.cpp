#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
class IO {
   protected:
    static const int BSIZE = 65536;
    int is;
    char ib[BSIZE], ob[BSIZE], *ip, *op;
    FILE *in, *out;

   public:
    inline IO(FILE *in = stdin, FILE *out = stdout) {
        ip = ib + BSIZE, op = ob, is = 0;
        this->in = in;
        this->out = out;
    }
    inline ~IO() {
        fwrite(ob, 1, op - ob, out);
    }
    inline char getchar() {
        if (ip == ib + BSIZE) is = fread(ib, 1, BSIZE, in), ip = ib;
        return ip == ib + is ? 0 : *ip++;
    }
    inline void putchar(char c) {
        if (op == ob + BSIZE) fwrite(ob, 1, BSIZE, out), op = ob;
        *op++ = c;
    }
};
class IOX : public IO {
   protected:
    int tmp[64];

   public:
    inline IOX(FILE *in = stdin, FILE *out = stdout) : IO(in, out) {}
    inline int getdigit() {
        register char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        return ch ^ 48;
    }
    inline char getalpha() {
        register char ch = getchar();
        while (!isalpha(ch)) ch = getchar();
        return ch;
    }
    inline int getint() {
        register int x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned getuint() {
        register unsigned x = 0;
        register char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
        return x;
    }
    inline long long getint64() {
        register long long x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned long long getuint64() {
        register unsigned long long x = 0;
        register char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
        return x;
    }
    inline void put(int x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void put(long long x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void put(const char *s) {
        for (; *s; s++) putchar(*s);
    }
    inline void put(char c) { putchar(c); }
    template <typename T, typename... Args>
    inline void put(T first, Args... rest) { put(first), put(rest...); }
    inline void puts(const char *s) {
        put(s);
        putchar(10);
    }
} io(fopen("match.in", "r"), fopen("match.out", "w"));
#define MAXN 800010
int n = io.getint(), ans = 0, son[MAXN][26], cnt[MAXN][2], all = 1;
inline void insert(int color) {
    int p = 1;
    register char ch = io.getchar();
    while (!islower(ch)) ch = io.getchar();
    for (; islower(ch); ch = io.getchar()) {
        int &nx = son[p][ch - 'a'];
        if (!nx) nx = ++all;
        p = nx;
    }
    cnt[p][color]++;
}
std::pair<int, int> dp(int x, int deep) {
    std::pair<int, int> f(cnt[x][0], cnt[x][1]);
    for (int i = 0; i < 26; i++) {
        if (son[x][i]) {
            auto g = dp(son[x][i], deep + 1);
            int t = std::min(f.first, g.second);
            ans += t * deep;
            f.first -= t, g.second -= t;
            t = std::min(f.second, g.first);
            ans += t * deep;
            f.second -= t, g.first += t;
            f.first += g.first;
            f.second += g.second;
        }
    }
    return f;
}
int main() {
    for (int i = 1; i <= n; i++) insert(0);
    for (int i = 1; i <= n; i++) insert(1);
    dp(1, 0);
    io.put(ans, '\n');
    return 0;
}