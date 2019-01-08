#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
#define MOD 1000000007
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, d, low, high, now, g[MAXN], f[MAXN], ans = 0;
void dp(int x, int fa) {
    if (g[x] < low || g[x] > high) return f[x] = 0, void();
    if (g[x] == high && x > now) return f[x] = 0, void();
    f[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dp(to[i], x);
        (f[x] += 1LL * f[x] * f[to[i]] % MOD) %= MOD;
    }
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &d, &n);
    for (int i = 1; i <= n; i++) scanf("%d", &g[i]);
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
    for (int i = 1; i <= n; i++) {
        low = g[i] - d, high = g[i];
        dp(now = i, 0);
        (ans += f[i]) %= MOD;
    }
    printf("%d\n", ans);
    return 0;
}