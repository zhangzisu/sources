#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 10010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, m, q, p[MAXN], u[MAXN], v[MAXN], c[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int fa[MAXN], deep[MAXN];
void dfs(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
    }
}
std::vector<int> val[MAXN], tmp0, tmp1, f[MAXN];
int count[MAXN], pos[MAXN];
inline void solve() {
    int u, v, k = 0;
    scanf("%d%d", &u, &v);
    if (u == v) return puts("0"), void();
    tmp0.clear();
    tmp1.clear();
    while (deep[u] > deep[v]) tmp0.push_back(u), u = fa[u];
    while (deep[v] > deep[u]) tmp1.push_back(v), v = fa[v];
    while (u != v) tmp0.push_back(u), u = fa[u], tmp1.push_back(v), v = fa[v];
    std::reverse(tmp1.begin(), tmp1.end());
    for (int i = 0; i < (int)tmp0.size(); i++) pos[++k] = tmp0[i];
    for (int i = 0; i < (int)tmp1.size(); i++) pos[++k] = tmp1[i];
    for (int i = 0; i < count[pos[1]]; i++) f[1].push_back(0);
    for (int i = 2; i <= k; i++) {
        for (int now = 0; now < count[pos[i]]; now++) {
            f[i].push_back(0);
            for (int pre = 0; pre < count[pos[i - 1]]; pre++) {
                f[i][now] = std::max(f[i][now], f[i - 1][pre] + (val[pos[i - 1]][pre] != val[pos[i]][now]));
            }
        }
    }
    int tmp = 0;
    for (int i = 0; i < count[pos[k]]; i++) tmp = std::max(tmp, f[k][i]);
    for (int i = 1; i <= k; i++) f[i].clear();
    printf("%d\n", tmp);
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", u + i, v + i, c + i);
        if (find(u[i]) != find(v[i])) {
            $(u[i], v[i]);
            p[find(u[i])] = find(v[i]);
        }
    }
    dfs(1);
    for (int i = 1; i <= m; i++) {
        if (deep[u[i]] > deep[v[i]]) std::swap(deep[u[i]], deep[v[i]]);
        val[v[i]].push_back(c[i]);
    }
    for (int i = 1; i <= n; i++) {
        std::sort(val[i].begin(), val[i].end());
        val[i].erase(std::unique(val[i].begin(), val[i].end()), val[i].end());
        count[i] = (int)val[i].size();
    }
    for (scanf("%d", &q); q; q--) solve();
    return 0;
}