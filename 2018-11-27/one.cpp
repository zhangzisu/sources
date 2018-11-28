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
inline lnt gcd(lnt a, lnt b) { return b ? gcd(b, a % b) : a; }
inline lnt lowbit(lnt x) { return x & -x; }
lnt n, m, lcm[1 << MAXN], cnt[1 << MAXN], pop[1 << MAXN], ans[MAXN + 1], all;
int main() {
    IOX io;
    n = io.getint64(), m = io.getint64();
    for (lnt i = 0; i < m; i++) lcm[1 << i] = io.getint64();
    lcm[0] = 1LL;
    ans[0] = n * (1LL << m) % MOD;
    for (lnt i = 1LL; i < (1LL << m); i++) {
        lnt j = i - lowbit(i);
        pop[i] = pop[j] + 1LL;
        lnt tmp = 1LL * lcm[j] * lcm[lowbit(i)] / gcd(lcm[j], lcm[lowbit(i)]);
        lcm[i] = tmp > n ? n + 1LL : tmp;
        cnt[i] = n / lcm[i];
        // printf("%d -> %d\n", i, lcm[i]);
        for (lnt j = 0; j <= pop[i]; j++) {
            lnt sign = ((pop[i] - j) & 1LL) ? MOD - 1LL : 1LL;
            sign = sign * (1LL << (m - pop[i])) % MOD;
            (ans[j] += cnt[i] * sign % MOD) %= MOD;
        }
    }
    for (lnt i = 0; i <= m; i += 4) (all += ans[i]) %= MOD;
    io.putint64(all);
    io.putchar(10);
    return 0;
}