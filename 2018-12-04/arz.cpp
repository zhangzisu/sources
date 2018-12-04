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
#define MAXN 110
const int INF = 0x3F3F3F3F;
const int primes[17] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
int n, a[MAXN], pre[60], f[MAXN][1 << 17];
inline void up(int &x, int y) {
    if (y < x) x = y;
}
int main() {
    IOX io = IOX(fopen("arz.in", "r"), fopen("arz.out", "w"));
    for (int x = 1; x < 60; x++) {
        for (int i = 0; i < 17; i++) {
            if (x % primes[i] == 0) pre[x] |= 1 << i;
        }
    }
    n = io.getint();
    memset(f, 0x3F, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = io.getint();
        for (int d = 0; d < (1 << 17); d++) {
            if (f[i - 1][d] == INF) continue;
            for (int j = 1; j < 60; j++) {
                if (d & pre[j]) continue;
                up(f[i][d | pre[j]], f[i - 1][d] + std::abs(a[i] - j));
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < (1 << 17); i++) up(ans, f[n][i]);
    io.putint(ans);
    io.putchar(10);
    return 0;
}