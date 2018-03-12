#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXM 500010
int sb[MAXN], n, m, q;
int head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
struct Edge {
    int u, v, w;
    inline friend bool operator<(const Edge &a, const Edge &b) {
        return a.w < b.w;
    }
} e[MAXM];
int p[MAXN], fucked[MAXM], fa[MAXN][18], ans[MAXN], deep[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

void dfs(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &sb[i]);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[i] = {u, v, std::abs(sb[u] - sb[v])};
    }
    std::sort(e + 1, e + m + 1);
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= m; i++) {
        int U = find(e[i].u), V = find(e[i].v);
        if (U == V) continue;
        $(e[i].u, e[i].v, e[i].w);
        p[U] = V, fucked[i] = 1;
    }
    for (int i = 1; i <= n; i++) p[i] = i;
    dfs(1);
    memset(ans, 0x3F, sizeof(ans));
    for (int i = 1; i <= m; i++) {
        if (fucked[i]) continue;
        int u = find(e[i].u), v = find(e[i].v);
        while (u != v) {
            if (deep[u] < deep[v]) std::swap(u, v);
            //
        }
    }
    return 0;
}