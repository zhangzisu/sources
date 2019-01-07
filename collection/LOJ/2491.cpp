#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 300010
#define MOD 998244353
int n, m, deep[MAXN], s[MAXN][51], fa[MAXN][20];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
void d(int x) {
    for (int i = 1, j = deep[x]; i <= 50; i++) {
        s[x][i] = (0LL + s[fa[x][0]][i] + j) % MOD;
        j = 1LL * j * deep[x] % MOD;
    }
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        d(to[i]);
    }
}
inline int LCA(int x, int y) {
    if (deep[x] < deep[y]) std::swap(x, y);
    int delta = deep[x] - deep[y];
    for (int i = 19; ~i; i--)
        if ((delta >> i) & 1) x = fa[x][i];
    for (int i = 19; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return x == y ? x : fa[x][0];
}
int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y);
        $(x, y);
    }
    d(1);
    for (int d = 1; d < 20; d++)
        for (int i = 1; i <= n; i++) fa[i][d] = fa[fa[i][d - 1]][d - 1];
    scanf("%d", &m);
    while (m--) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        int lca = LCA(x, y);
        printf("%lld\n", ((0LL + s[x][k] + s[y][k] - s[lca][k] - s[fa[lca][0]][k]) % MOD + MOD) % MOD);
    }
    return 0;
}