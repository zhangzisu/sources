#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MAXM 2010
#define MOD 1000000007
#define $ long long
inline $ fuck($ x, $ p) {
    $ y = 1;
    while (p) {
        if (p & 1) y = y * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return y;
}
$ n, m, x, t, ans, head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void _($ u, $ v, $ w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
struct edge {
    $ u, v, w;
    inline friend bool operator<(const edge &a, const edge &b) {
        return a.w < b.w;
    }
} e[MAXM];
$ p[MAXN], deep[MAXN], qd[MAXM], fa[MAXN][20], max[MAXN][20];
inline $ find($ x) { return x == p[x] ? x : p[x] = find(p[x]); }
$ dis[MAXN][MAXN], eq, up;
$ dfs($ *dis, $ x, $ fa, $ nowans) {
    dis[x] = nowans;
    for ($ tmp, i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        if (~(tmp = dfs(dis, to[i], x, std::max(nowans, val[i])))) return tmp;
    }
    return -1;
}
int main() {
    scanf("%lld%lld%lld", &n, &m, &x);
    for ($ i = 1; i <= m; i++) scanf("%lld%lld%lld", &e[i].u, &e[i].v, &e[i].w);
    memset(head, -1, sizeof(head));
    std::sort(e + 1, e + m + 1);
    for ($ i = 1; i <= n; i++) p[i] = i;
    for ($ i = 1; i <= m; i++) {
        $ U = find(e[i].u), V = find(e[i].v);
        if (U == V) continue;
        p[U] = V, t += e[i].w, qd[i] = 1;
        _(e[i].u, e[i].v, e[i].w);
    }
    if ((t = x - t) < 0) return puts("0"), 0;
    for (int i = 1; i <= n; i++)
        dfs(dis[i], i, 0, 0);
    for ($ i = 1; i <= m; i++) {
        if (qd[i]) continue;
        $ delta = e[i].w - dis[e[i].u][e[i].v] - t;
        if (delta > 0)
            up++;
        else if (delta == 0)
            eq++;
    }
    ans = 2LL * (fuck(2, eq) - 1) % MOD * fuck(2, up) % MOD;
    if (!t) ans = (ans + (fuck(2, n - 1) - 2) * fuck(2, m - n + 1) % MOD) % MOD;
    printf("%lld\n", ans);
    return 0;
}