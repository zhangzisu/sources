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
#include<map>
#define MOD 1000000007
typedef long long lnt;
lnt pow11[10];
inline void up(int &x, int v) {
    if ((x += v) >= MOD) x -= MOD;
}
inline int get(lnt v, int p) {
    return v / pow11[p] % 11;
}
inline lnt set(lnt v, int p, int w) {
    lnt ret = v / pow11[p + 1] * pow11[p + 1];
    ret += w * pow11[p];
    if (p) ret += v % pow11[p - 1];
    return ret;
}
std::map<lnt, int> f[20][3];
inline int getval(lnt x) {
    lnt f = 0;
    for (int t; x; x /= 10) {
        t = x % 10;
        int w = std::max(get(f, t), (t < 9 ? get(f, t + 1) : 0) + 1);
        f = set(f, t, w);
        for (int i = t - 1; i >= 0; i--) {
            f[i] = std::max(f[i], f[i + 1]);
            f = set()
        }
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
    pow11[0] = 1;
    for (int i = 1; i < 10; i++) pow11[i] = pow11[i - 1] * 11;
    //
    for(int i = 2;i <= 18;i++){
        //
    }
    IOX io = IOX();
    for (int T = io.getint(); T; T--) {
        lnt L = io.getint64(), R = io.getint64();
        int s = io.getint(), p = io.getint(), ans = 0;
        if (R - L <= 1000) {
            for (lnt i = L; i <= R; i++) {
                // fprintf(stderr, "gv(%lld) = %d\n", i, getval(i));
                if (getval(i) == s) {
                    up(ans, getpow(i, p));
                }
            }
            io.putint(ans);
            io.putchar(10);
            continue;
        }
    }
}