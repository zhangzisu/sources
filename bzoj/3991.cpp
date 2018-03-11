#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int n, m, fa[MAXN][19], deep[MAXN], dfn[MAXN], pos[MAXN], vis[MAXN], tim;
long long dis[MAXN], ans = 0, tmp;
void dfs(int x) {
    pos[dfn[x] = ++tim] = x;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        dis[to[i]] = dis[x] + val[i];
        dfs(to[i]);
    }
}
inline int lca(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    int delta = deep[u] - deep[v];
    for (int i = 18; ~i; i--)
        if ((delta >> i) & 1) u = fa[u][i];
    for (int i = 18; ~i; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}
inline long long calc(int u, int v) { return dis[u] + dis[v] - (dis[lca(u, v)] << 1); }
std::set<int> S;
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), $(u, v, w);
    dfs(1);
    for (int d = 1; d <= 18; d++)
        for (int i = 1; i <= n; i++) fa[i][d] = fa[fa[i][d - 1]][d - 1];
    S.insert(0);
    S.insert(n + 1);
    while (m--) {
        int x;
        scanf("%d", &x);
        if (vis[x]) {
            vis[x] = 0;
            S.erase(dfn[x]);
            int l = *--S.lower_bound(dfn[x]), r = *S.upper_bound(dfn[x]);
            if (l != 0) ans -= calc(pos[l], x);
            if (r != n + 1) ans -= calc(x, pos[r]);
            if (l != 0 && r != n + 1) ans += calc(pos[l], pos[r]);
            if (S.size() > 2)
                tmp = calc(pos[*++S.begin()], pos[*++S.rbegin()]);
            else
                tmp = 0;
            printf("%lld\n", ans + tmp);
        } else {
            vis[x] = 1;
            S.insert(dfn[x]);
            int l = *--S.lower_bound(dfn[x]), r = *S.upper_bound(dfn[x]);
            if (l != 0) ans += calc(pos[l], x);
            if (r != n + 1) ans += calc(x, pos[r]);
            if (l != 0 && r != n + 1) ans -= calc(pos[l], pos[r]);
            if (S.size() > 2)
                tmp = calc(pos[*++S.begin()], pos[*++S.rbegin()]);
            else
                tmp = 0;
            printf("%lld\n", ans + tmp);
        }
    }
}