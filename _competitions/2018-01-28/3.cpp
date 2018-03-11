#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, fa[MAXN], deep[MAXN], last[MAXN], x, y, t;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
long long a[MAXN], b[MAXN], ans = 0, gg;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
void dfs(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        deep[to[i]] = deep[x] + 1, fa[to[i]] = x;
        dfs(to[i]);
    }
}
long long sqr[141422];
inline long long calc(long long x) {
    int pos = std::lower_bound(sqr, sqr + 141422, x) - sqr;
    while (pos && x % sqr[pos]) pos--;
    return sqr[pos];
}
int main() {
    for (int i = 0; i < 141422; i++) sqr[i] = 1LL * i * i;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    dfs(1);
    while (m--) {
        scanf("%d%d%d", &x, &y, &t);
        while (x != y) {
            if (deep[x] < deep[y]) std::swap(x, y);
            gg = std::min((t - last[x]) * a[x], b[x]);
            last[x] = t;
            ans += calc(gg);
            x = fa[x];
        }
        gg = std::min((t - last[x]) * a[x], b[x]);
        last[x] = t;
        ans += calc(gg);
        x = fa[x];
    }
    printf("%lld\n", ans);
    return 0;
}