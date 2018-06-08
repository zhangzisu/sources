#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, q;
namespace tr0 {
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot;
inline void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int fa[MAXN][18], deep[MAXN], size[MAXN];
void dfs(int x) {
    for (int i = 1; i < 18; i++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
        size[x] += size[to[i]];
    }
}
inline int lca(int x, int y) {
    if (deep[x] < deep[y]) std::swap(deep[x], deep[y]);
    int delta = deep[x] - deep[y];
    for (int i = 17; ~i; i--)
        if ((delta >> i) & 1) x = fa[x][i];
    for (int i = 17; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return x == y ? x : fa[x][0];
}
}  // namespace tr0
int sum[MAXN], L[MAXN], R[MAXN];

int main() {
    scanf("%d%d%d", &n, &m, &q);
    tr0::init();
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        tr0::$(u, v);
    }
    tr0::dfs(1);
    for(int i = 1;i <= m;i++){
        //
    }
    return 0;
}