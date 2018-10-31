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
        char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        return ch ^ 48;
    }
    inline int getint() {
        int x = 0;
        bool f = 0;
        char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned getuint() {
        unsigned x = 0;
        char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline long long getint64() {
        long long x = 0;
        bool f = 0;
        char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline void putint(int x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void putint64(long long x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void puts(const char *s) {
        for (; *s; s++) putchar(*s);
    }
};
#define MOD 1000000007
typedef long long lnt;
inline void up(int &x, int v) {
    if ((x += v) >= MOD) x -= MOD;
}
inline int getval(lnt x) {
    static int f[10];
    memset(f, 0, sizeof(f));
    for (int t; x; x /= 10) {
        t = x % 10;
        f[t] = std::max(f[t], (t < 9 ? f[t + 1] : 0) + 1);
        for (int i = t - 1; i >= 0; i--) f[i] = std::max(f[i], f[i + 1]);
    }
    return f[0];
}
inline int getpow(lnt x, int p) {
    if (p == 0) return 1;
    x %= MOD;
    if (p == 1) return x;
    return x * x % MOD;
}
int main() {
    IOX io = IOX(fopen("count.in", "r"), fopen("count.out", "w"));
    for (int T = io.getint(); T; T--) {
        lnt L = io.getint64(), R = io.getint64();
        int s = io.getint(), p = io.getint(), ans = 0;
        for (lnt i = L; i <= R; i++) {
            // fprintf(stderr, "gv(%lld) = %d\n", i, getval(i));
            if (getval(i) == s) {
                up(ans, getpow(i, p));
            }
        }
        io.putint(ans);
        io.putchar(10);
    }
}