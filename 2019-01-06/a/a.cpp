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
} io(fopen("a.in", "r"), fopen("a.out", "w"));
using lnt = long long;
lnt n, m, k, ans;
inline int fuck(int v, lnt *x) {
    if (*x % v == 0) {
        *x /= v;
        return 1;
    }
    return 0;
}
template <typename T, typename... Args>
inline int fuck(int v, T x, Args... rest) {
    if (*x % v == 0) {
        *x /= v;
        return 1;
    }
    return fuck(v, rest...);
}
inline lnt fuck0(lnt x) {
    return x;
}
inline lnt fuck1(lnt x) {
    lnt a = x, b = x + 1;
    fuck(2, &a, &b);
    return a * b % m;
}
inline lnt fuck2(lnt x) {
    lnt a = x, b = x + 1, c = 2 * x + 1;
    fuck(2, &a, &b, &c);
    fuck(3, &a, &b, &c);
    return a * b % m * c % m;
}
inline lnt fuck3(lnt x) {
    return fuck1(x) * fuck1(x) % m;
}
inline lnt fuck4(lnt x) {
    lnt a = x, b = x + 1, c = 2 * x + 1;
    fuck(2, &a, &b, &c);
    fuck(3, &a, &b, &c);
    if (fuck(5, &a, &b, &c)) {
        return a * b % m * c % m * (3 * x % m * x % m + 3 * x % m - 1 + m) % m;
    } else {
        lnt d = 3 * x + 1, e = x - 1;
        fuck(5, &d, &e);
        return a * b % m * c % m * (x + d * e % m) % m;
    }
}
int main() {
    for (int _ = io.getint(); _; _--) {
        n = io.getint64(), m = io.getint64(), k = io.getint64(), ans = 0;
        for (lnt i = 1, j; i <= n; i = j + 1) {
            j = std::min(n, n / (n / i));
            lnt tmp = 0;
            switch (k) {
                case 4:
                    tmp = (tmp + m + fuck4(j) - fuck4(i - 1)) % m;
                case 3:
                    tmp = (tmp + m + fuck3(j) - fuck3(i - 1)) % m;
                case 2:
                    tmp = (tmp + m + fuck2(j) - fuck2(i - 1)) % m;
                case 1:
                    tmp = (tmp + m + fuck1(j) - fuck1(i - 1)) % m;
                case 0:
                    tmp = (tmp + m + fuck0(j) - fuck0(i - 1)) % m;
            }
            tmp = tmp * (n / i) % m;
            ans = (ans + tmp) % m;
        }
        io.put(ans, '\n');
    }
    return 0;
}