#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 250010
struct Edge {
    int head[MAXN], to[MAXN << 2], len[MAXN << 2], next[MAXN << 2], tot;
    inline Edge() { memset(head, -1, sizeof(head)), tot = 0; }
    inline void operator()(int u, int v, int w = 0) { next[tot] = head[u], to[tot] = v, len[tot] = w, head[u] = tot++; }
} orn, vir;
int n, m, k, dfn[MAXN], pos[MAXN], deep[MAXN], fa[MAXN][19], tim;
long long val[MAXN];
void dfs(int x) {
    pos[dfn[x] = ++tim] = x;
    for (int i = orn.head[x]; ~i; i = orn.next[i]) {
        if (orn.to[i] == fa[x][0]) continue;
        fa[orn.to[i]][0] = x;
        deep[orn.to[i]] = deep[x] + 1;
        val[orn.to[i]] = std::min(val[x], (long long)orn.len[i]);
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
int a[MAXN], stk[MAXN], top;
inline bool cmp(const int &a, const int &b) { return dfn[a] < dfn[b]; }
long long dp(int x) {
    if (!~vir.head[x]) return val[x];
    long long sum = 0;
    for (int i = vir.head[x]; ~i; i = vir.next[i]) sum += dp(vir.to[i]);
    vir.head[x] = -1;
    return std::min(val[x], sum);
}
inline void slove() {
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) scanf("%d", &a[i]);
    std::sort(a + 1, a + k + 1, cmp);
    for (int i = top = 1; i <= k; i++)
        if (LCA(a[i], a[top]) != a[top]) a[++top] = a[i];
    k = top;
    stk[top = 1] = 1;
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
    printf("%lld\n", dp(1));
}
int main() {
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), orn(u, v, w), orn(v, u, w);
    val[1] = 0x3F3F3F3F3F3F3F3FLL, dfs(1);
    for (int d = 1; d <= 18; d++)
        for (int i = 1; i <= n; i++) fa[i][d] = fa[fa[i][d - 1]][d - 1];
    scanf("%d", &m);
    while (m--) slove();
}