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
    inline long long getint64() {
        register long long x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
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
#define MAXN 20
#define MOD 998244353
typedef long long lnt;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
inline int lowbit(int x) { return x & -x; }
int n, m, lcm[1 << MAXN], cnt[1 << MAXN], pop[1 << MAXN], ans[MAXN + 1], all;
int main() {
    IOX io(fopen("one.in", "r"), fopen("one.out", "w"));
    n = io.getint(), m = io.getint();
    for (int i = 0; i < m; i++) lcm[1 << i] = io.getint();
    lcm[0] = 1;
    up(ans[0], 1LL * n * (1 << m) % MOD);
    for (int i = 1; i < (1 << m); i++) {
        int j = i - lowbit(i);
        pop[i] = pop[j] + 1;
        lnt tmp = 1LL * lcm[j] * lcm[lowbit(i)] / gcd(lcm[j], lcm[lowbit(i)]);
        lcm[i] = tmp > n ? n + 1 : tmp;
        cnt[i] = n / lcm[i];
        for (int j = 0; j <= pop[i]; j++) {
            int sign = ((pop[i] - j) & 1) ? MOD - 1 : 1;
            sign = 1LL * sign * (1 << (m - pop[i])) % MOD;
            up(ans[j], 1LL * cnt[i] * sign % MOD);
        }
    }
    for (int i = 0; i <= m; i += 4) up(all, ans[i]);
    io.putint(all);
    io.putchar(10);
    return 0;
}