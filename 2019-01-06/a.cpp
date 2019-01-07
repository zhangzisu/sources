#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
} io;
using lnt = long long;
lnt n;
int m, k;
inline void trim(int &x) { x -= m, x += (x >> 31) & m; }
inline void up(int &x, int y) { trim(x += y); }
inline int fuck(lnt v) {
    int a1 = v % m;
    int ret = 60LL * a1 % m;
    if (k >= 1) {
        int a2 = 1LL * a1 * a1 % m;
        up(ret, 30LL * a1 % m);
        up(ret, 30LL * a2 % m);
        if (k >= 2) {
            int a3 = 1LL * a2 * a1 % m;
            up(ret, 10LL * a1 % m);
            up(ret, 30LL * a2 % m);
            up(ret, 20LL * a3 % m);
            if (k >= 3) {
                int a4 = 1LL * a3 * a1 % m;
                up(ret, 15LL * a2 % m);
                up(ret, 30LL * a3 % m);
                up(ret, 15LL * a4 % m);
                if (k >= 4) {
                    int a5 = 1LL * a4 * a1 % m;
                    up(ret, m - 2LL * a1 % m);
                    up(ret, 20LL * a3 % m);
                    up(ret, 30LL * a4 % m);
                    up(ret, 12LL * a5 % m);
                }
            }
        }
    }
    return ret;
}
int main() {
    for (int _ = io.getint(); _; _--) {
        n = io.getint64(), m = io.getint() * 60, k = io.getint();
        int ans = 0, last = 0;
        for (lnt i = 1, j; i <= n; i = j + 1) {
            j = n / (n / i);
            int cur = fuck(j);
            up(ans, 1LL * (n / i) % m * (m + cur - last) % m);
            last = cur;
        }
        io.put(ans / 60, '\n');
    }
    return 0;
}