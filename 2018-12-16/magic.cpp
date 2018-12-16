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
#define MOD 998244353
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int fuck(int x, int p) {
    int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int **table[500];
inline void declare(int **&t, int n) {
    t = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) t[i] = (int *)calloc(n, sizeof(int));
    int x, y;
    t[x = 0][y = n / 2] = 1;
    for (int i = 2; i <= n * n; i++) {
        if (x == 0) {
            if (y == n - 1) {
                t[++x][y] = i;
            } else {
                t[x = n - 1][++y] = i;
            }
        } else {
            if (y == n - 1) {
                t[--x][y = 0] = i;
            } else {
                if (!t[x - 1][y + 1]) {
                    t[--x][++y] = i;
                } else {
                    t[++x][y] = i;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i) up(t[i][j], t[i - 1][j]);
            if (j) up(t[i][j], t[i][j - 1]);
            if (i && j) up(t[i][j], MOD - t[i - 1][j - 1]);
        }
    }
}
int main() {
    for (int i = 1; i <= 500; i += 2) declare(table[i], i);
    IOX io = IOX(fopen("magic.in", "r"), fopen("magic.out", "w"));
    for (int T = io.getint(); T; T--) {
        int n = io.getint(), x1 = io.getint() - 1, y1 = io.getint() - 1, x2 = io.getint() - 1, y2 = io.getint() - 1;
        if (x1 == 0 && x2 == n - 1 && y1 == 0 && y2 == n - 1) {
            io.putint(int(499122177LL * (1LL * n * n % MOD) % MOD * (1LL * n * n % MOD + 1) % MOD));
            io.putchar(10);
            continue;
        }
        int ans = table[n][x2][y2];
        if (x1) up(ans, MOD - table[n][x1 - 1][y2]);
        if (y1) up(ans, MOD - table[n][x2][y1 - 1]);
        if (x1 && y1) up(ans, table[n][x1 - 1][y1 - 1]);
        io.putint(ans);
        io.putchar(10);
    }
    return 0;
}