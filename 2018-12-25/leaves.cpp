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
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned getuint() {
        register unsigned x = 0;
        register char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline long long getint64() {
        register long long x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned long long getuint64() {
        register unsigned long long x = 0;
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
    inline void print(const char *s) {
        for (; *s; s++) putchar(*s);
    }
    inline void puts(const char *s) {
        print(s);
        putchar(10);
    }
} io(fopen("leaves.in", "r"), fopen("leaves.out", "w"));
#define MAXN 500010
typedef long long lnt;
struct edge_t {
    int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot;
    inline edge_t() { memset(head, -1, sizeof(head)), tot = 0; }
    inline void operator()(int u, int v) {
        next[tot] = head[u], to[tot] = v, head[u] = tot++;
        next[tot] = head[v], to[tot] = u, head[v] = tot++;
        // fprintf(stderr, "CONNECT %d with %d\n", u, v);
    }
} orn, vir;
int n, m, k, dfn[MAXN], pos[MAXN], deep[MAXN], fa[MAXN][19], dd[MAXN][19], dfsclk;
void dfs(int x) {
    pos[dfn[x] = ++dfsclk] = x;
    for (int i = orn.head[x]; ~i; i = orn.next[i]) {
        if (orn.to[i] == fa[x][0]) continue;
        fa[orn.to[i]][0] = x;
        deep[orn.to[i]] = deep[x] + 1;
        dfs(orn.to[i]);
    }
}
inline int LCA(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    int delta = deep[u] - deep[v];
    for (int i = 18; ~i; i--)
        if ((delta >> i) & 1) u = fa[u][i];
    for (int i = 18; ~i; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}
inline int VAL(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    u = fa[u][0];
    int ret = 0;
    for (int i = 18; ~i; i--) {
        if (deep[fa[u][i]] >= deep[v]) {
            ret = std::max(ret, dd[u][i]);
            u = fa[u][i];
        }
    }
    return ret;
}
int a[MAXN], stk[MAXN], vis[MAXN], top;
inline bool cmp(const int &a, const int &b) { return dfn[a] < dfn[b]; }
void clear(int x, int fa) {
    for (int i = vir.head[x]; ~i; i = vir.next[i]) {
        if (vir.to[i] == fa) continue;
        clear(vir.to[i], x);
    }
    vir.head[x] = -1;
}
int dfs(int x, int fa) {
    int has = 0, full = 1, count = 0, all = 0;
    for (int i = vir.head[x]; ~i; i = vir.next[i]) {
        if (vir.to[i] == fa) continue;
        int y = dfs(vir.to[i], x);
        if (!y) return 0;
        if (y == 3 && VAL(x, vir.to[i]) > 2) y = 2;
        full &= y == 3;
        has |= y != 1;
        count += y == 2;
        all++;
    }
    if (!all) return vis[x] ? 3 : 1;
    if (count > 2) return 0;
    return full && all + 1 == dd[x][0] ? 3 : has ? 2 : 1;
}
inline void slove() {
    // fprintf(stderr, "DDDDDDDDDDDDD\n");
    int root = io.getint(), k = io.getint();
    for (int i = 1; i <= k; i++) vis[a[i] = io.getint()] = 1;
    a[++k] = root;
    std::sort(a + 1, a + k + 1, cmp);
    k = std::unique(a + 1, a + k + 1) - a - 1;
    stk[top = 1] = 0;
    // memset(vir.head, -1, sizeof(vir.head));
    for (int i = 1, lca; i <= k; i++) {
        if ((lca = LCA(a[i], stk[top])) == stk[top]) {
            stk[++top] = a[i];
        } else {
            while (top > 1 && deep[stk[top - 1]] >= deep[lca]) vir(stk[top - 1], stk[top]), top--;
            if (stk[top] != lca) {
                vir(lca, stk[top--]);
                stk[++top] = lca;
            }
            stk[++top] = a[i];
        }
    }
    while (top > 1) vir(stk[top - 1], stk[top]), top--;
    io.puts(dfs(root, -1) ? "YES" : "NO");
    clear(root, -1);
    vir.tot = 0;
    for (int i = 1; i <= k; i++) vis[a[i]] = 0;
}
int main() {
    n = io.getint(), m = io.getint();
    for (int i = 1; i < n; i++) {
        int u = io.getint(), v = io.getint();
        orn(u, v);
        dd[u][0]++, dd[v][0]++;
    }
    dfs(1), deep[0] = -1;
    for (int d = 1; d <= 18; d++) {
        for (int i = 1; i <= n; i++) {
            fa[i][d] = fa[fa[i][d - 1]][d - 1];
            dd[i][d] = std::min(dd[i][d - 1], dd[fa[i][d - 1]][d - 1]);
        }
    }
    while (m--) slove();
    return 0;
}