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
    inline int getint() {
        register int x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned getuint() {
        register unsigned x = 0;
        register char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline void putint(int x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void putint64(long long x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void puts(const char *s) {
        for (; *s; s++) putchar(*s);
    }
};
typedef long long lnt;
#define MAXN 100010
inline int in(int l, int r, int p) { return l <= p && p <= r; }
int n, q, a[MAXN], query[MAXN];
int main() {
    IOX io = IOX(fopen("z.in", "r"), fopen("z.out", "w"));
    n = io.getint();
    q = io.getint();
    for (int i = 1; i <= n; i++) a[i] = io.getint();
    for (int i = 1; i <= q; i++) query[i] = io.getint();
    if (q == 0) return 0;
    if (n <= 1000 && q <= 1000) {
        for (int t = 1; t <= q; t++) {
            int l = 0, r = query[t], ans = 0;
            for (int i = 1; i <= n; i++) {
                if (in(l, r, a[i])) continue;
                if (a[i] > r) {
                    int delta = a[i] - r;
                    l += delta;
                    r += delta;
                    ans += delta;
                } else {
                    int delta = l - a[i];
                    l -= delta;
                    r -= delta;
                    ans += delta;
                }
            }
            io.putint(ans), io.putchar(10);
        }
    } else {
        std::sort(a + 1, a + n + 1);
        for (int t = 1; t <= q; t++) {
            if (a[1] >= 0) {
                io.putint(std::max(0, a[n] - query[t])), io.putchar(10);
            } else {
                io.putint(-a[1] + std::max(0, a[n] - query[t] - a[1])), io.putchar(10);
            }
        }
    }
    return 0;
}