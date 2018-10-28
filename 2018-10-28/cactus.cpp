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
#define MAXN 5010
#define MAXM 10010
#define MOD 1000000007
#define INV 500000004
typedef long long lnt;
int head[MAXN], to[MAXM << 1], next[MAXM << 1], d[MAXN], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
    d[u]++, d[v]++;
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int n, m, p, ans = 0, deep[MAXN], fa[MAXN], prf[MAXN], spc[MAXN];
void dfs(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (!deep[to[i]]) {
            deep[to[i]] = deep[x] + 1;
            fa[to[i]] = fa[x];
            dfs(to[i]);
        } else if (deep[to[i]] < deep[x] - 1) {
            spc[to[i]] = 1;
            for (int y = x; y != to[i]; y = fa[y]) prf[fa[y]] = y;
        }
    }
}
int f[MAXN][40], g[MAXN][40], h[40], q[MAXN];
int pre[MAXN][40], suf[MAXN][40];
void dp(int x) {
    f[x][1] = g[x][1] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (deep[to[i]] == deep[x] + 1) {
            dp(to[i]);
            memset(h, 0, sizeof(h));
            for (int j = 1; j <= p; j++) {
                for (int k = 0; k <= p - j; k++) {
                    up(h[j + k], 1LL * f[x][j] * f[to[i]][k] % MOD);
                }
            }
            memcpy(f[x], h, sizeof(h));
            if (to[i] == prf[x]) continue;
            memset(h, 0, sizeof(h));
            for (int j = 1; j <= p; j++) {
                for (int k = 0; k <= p - j; k++) {
                    up(h[j + k], 1LL * g[x][j] * g[to[i]][k] % MOD);
                }
            }
            memcpy(g[x], h, sizeof(h));
        }
    }
    f[x][0] = 1;
    g[x][0] = 1;
    if (spc[x]) {
        int tmp = 0;
        for (int y = x; y; y = prf[y]) q[++tmp] = y;
        for (int i = 1; i <= tmp; i++) {
            memset(sum[next], 0, sizeof(sum[next]));
            //
        }
    }
}
int main() {
    IOX io = IOX();
    n = io.getint(), m = io.getint(), p = io.getint();
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) {
        int u = io.getint(), v = io.getint();
        $(u, v);
    }
    deep[1] = 1;
    dfs(1, 0);
    dp(1);
    io.putint64(ans);
    io.putchar(10);
    return 0;
}