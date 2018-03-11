#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define MAXN 200010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], d[MAXN], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
    d[u]++, d[v]++;
}
int n, dis[MAXN];
std::queue<int> Q;
inline int fF(int s) {
    memset(dis, -1, sizeof(dis));
    dis[s] = 0;
    register int ret = s;
    Q.push(s);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        if (dis[x] > dis[ret]) ret = x;
        for (int i = head[x]; ~i; i = next[i]) {
            if (!~dis[to[i]]) {
                dis[to[i]] = dis[x] + 1;
                Q.push(to[i]);
            }
        }
    }
    return ret;
}
int u, v, spc[MAXN], fa[MAXN][18], deep[MAXN];
int fill(int x, int fa) {
    if (x == v) return spc[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        if (fill(to[i], x)) return spc[x] = 1;
    }
    return 0;
}
void gf(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        gf(to[i]);
    }
}
inline int lca(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    int delta = deep[u] - deep[v];
    for (int i = 0; i < 18; i++)
        if ((delta >> i) & 1) u = fa[u][i];
    for (int i = 17; i >= 0; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}
inline int ddd(int u, int v) {
    int l = lca(u, v);
    return deep[u] + deep[v] - (deep[l] << 1);
}
long long ans = 0;
std::vector<int> a, b, c;
inline void shabi() {
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        ans += std::max(ddd(x, u), ddd(x, v));
        a.push_back(x);
        b.push_back(ddd(x, u) < ddd(x, v) ? v : u);
        c.push_back(x);
        for (int i = head[x]; ~i; i = next[i])
            if (!spc[to[i]] && --d[to[i]] == 1) Q.push(to[i]);
    }
}
void dfs(int x) {
    if (x == v) return;
    a.push_back(x);
    b.push_back(v);
    c.push_back(x);
    ans += ddd(x, v);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x][0] && spc[to[i]]) dfs(to[i]);
}
int main() {
    memset(head, -1, sizeof(head));
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        $(u, v);
    }
    v = fF(u = fF(1));
    fill(u, 0);
    gf(u);
    for (int d = 1; d < 18; d++)
        for (int i = 1; i <= n; i++) fa[i][d] = fa[fa[i][d - 1]][d - 1];
    for (int i = 1; i <= n; i++)
        if (d[i] == 1 && !spc[i]) {
            Q.push(i);
        }
    shabi();
    dfs(u);
    std::cout << ans << std::endl;
    for (unsigned i = 0; i < a.size(); i++) {
        std::cout << a[i] << ' ' << b[i] << ' ' << c[i] << std::endl;
    }
    return 0;
}