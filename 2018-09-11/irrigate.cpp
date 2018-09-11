#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 310
#define MAXM 100010
int n, m, ans, p[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
struct edge {
    int u, v, w;
    inline edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
    inline int friend operator<(const edge &a, const edge &b) {
        return a.w < b.w;
    }
} e[MAXM];
int main() {
    freopen("irrigate.in", "r", stdin);
    freopen("irrigate.out", "w", stdout);
    n = $();
    for (int i = 1; i <= n; i++) p[i] = i, e[++m] = edge(i, 0, $());
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            e[++m] = edge(i, j, $());
    std::sort(e + 1, e + m + 1);
    for (int i = 1; i <= m; i++) {
        int U = find(e[i].u), V = find(e[i].v);
        if (U == V) continue;
        p[U] = V;
        ans += e[i].w;
    }
    printf("%d\n", ans);
    return 0;
}