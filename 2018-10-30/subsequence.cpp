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
        int x = 0, f = 0;
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
#define MAXN 300010
#define MOD 1000000007
int n, a[MAXN], f[MAXN][2], g[MAXN][2], ans, sum;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int add(int x, int y) {
    return (x + y >= MOD) ? x + y - MOD : x + y;
}
int F[2][MAXN << 2], G[2][MAXN << 2];
void dp(int n, int l, int r, int L, int R, int *F, int *G, int &f, int &g) {
    if (L > R) return;
    if (l == L && r == R) {
        if (F[n] + 1 > f) {
            f = F[n] + 1;
            g = G[n];
        } else if (F[n] + 1 == f) {
            up(g, G[n]);
        }
        return;
    }
    int mid = (l + r) >> 1;
    if (R <= mid) return dp(n << 1, l, mid, L, R, F, G, f, g);
    if (L > mid) return dp(n << 1 | 1, mid + 1, r, L, R, F, G, f, g);
    dp(n << 1, l, mid, L, mid, F, G, f, g);
    dp(n << 1 | 1, mid + 1, r, mid + 1, R, F, G, f, g);
}
void save(int n, int l, int r, int p, int *F, int *G, int f, int g) {
    if (l == r) {
        if (f > F[n]) {
            F[n] = f;
            G[n] = g;
        } else if (f == F[n]) {
            up(G[n], g);
        }
        return;
    }
    int mid = (l + r) >> 1;
    p <= mid ? save(n << 1, l, mid, p, F, G, f, g) : save(n << 1 | 1, mid + 1, r, p, F, G, f, g);
    if (F[n << 1] > F[n << 1 | 1]) {
        F[n] = F[n << 1];
        G[n] = G[n << 1];
    } else if (F[n << 1] < F[n << 1 | 1]) {
        F[n] = F[n << 1 | 1];
        G[n] = G[n << 1 | 1];
    } else {
        F[n] = F[n << 1];
        G[n] = add(G[n << 1], G[n << 1 | 1]);
    }
}
int main() {
    IOX io = IOX(fopen("subsequence.in", "r"), fopen("subsequence.out", "w"));
    n = io.getint();
    for (int i = 1; i <= n; i++) a[i] = io.getint();
    for (int i = 1; i <= n; i++) {
        f[i][0] = f[i][1] = g[i][0] = g[i][1] = 1;
        dp(1, 1, n, 1, a[i] - 1, F[1], G[1], f[i][0], g[i][0]);
        dp(1, 1, n, a[i] + 1, n, F[0], G[0], f[i][1], g[i][1]);
        save(1, 1, n, a[i], F[0], G[0], f[i][0], g[i][0]);
        save(1, 1, n, a[i], F[1], G[1], f[i][1], g[i][1]);
        ans = std::max(ans, f[i][0]);
        ans = std::max(ans, f[i][1]);
    }
    for (int i = 1; i <= n; i++) {
        if (f[i][0] == ans) up(sum, g[i][0]);
        if (f[i][1] == ans) up(sum, g[i][1]);
    }
    io.putint(ans);
    io.putchar(32);
    io.putint(sum);
    io.putchar(10);
    return 0;
}