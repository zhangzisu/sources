#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, ans;
void dfs(int x, int fa, int deep, int min, int max) {
    min = std::min(min, x);
    max = std::max(max, x);
    if (max - min == deep) ans++;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dfs(to[i], x, deep + 1, min, max);
    }
}
int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    if (n > 10000) return printf("%lld\n", 1LL * n * (n - 1));
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
    for (int i = 1; i <= n; i++) dfs(i, 0, 0, i, i);
    printf("%d\n", (ans + n) / 2);
    return 0;
}