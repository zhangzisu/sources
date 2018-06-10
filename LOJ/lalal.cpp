#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long int64;
char ch;
bool ok;
void read(int &x) {
    ok = 0;
    for (ch = getchar(); !isdigit(ch); ch = getchar())
        if (ch == '-') ok = 1;
    for (x = 0; isdigit(ch); x = x * 10 + ch - '0', ch = getchar())
        ;
    if (ok) x = -x;
}
void read(int64 &x) {
    ok = 0;
    for (ch = getchar(); !isdigit(ch); ch = getchar())
        if (ch == '-') ok = 1;
    for (x = 0; isdigit(ch); x = x * 10 + ch - '0', ch = getchar())
        ;
    if (ok) x = -x;
}
const int maxn = 100000 + 5;
const int maxm = maxn * 2;
int n, m, q, idx;
int64 N, a, b, list[maxn];
int root[maxn], from[maxn];
struct Seg {
    int tot, siz[maxn * 18], son[maxn * 18][2], root[maxn];
    void insert(int &k, int p, int l, int r, int v) {
        k = ++tot, siz[k] = siz[p] + 1;
        if (l == r) return;
        int m = (l + r) >> 1;
        if (v <= m)
            son[k][1] = son[p][1], insert(son[k][0], son[p][0], l, m, v);
        else
            son[k][0] = son[p][0], insert(son[k][1], son[p][1], m + 1, r, v);
    }
    void insert(int idx, int v) { insert(root[idx], root[idx - 1], 1, n, v); }
    int calc(int x, int y, int k) {
        x = root[x - 1], y = root[y];
        int l = 1, r = n, m;
        while (l < r) {
            m = (l + r) >> 1;
            if (siz[son[y][0]] - siz[son[x][0]] >= k)
                r = m, y = son[y][0], x = son[x][0];
            else
                l = m + 1, k -= siz[son[y][0]] - siz[son[x][0]], y = son[y][1], x = son[x][1];
        }
        return l;
    }
} T;
int dfn[maxn], last[maxn], siz[maxn];
struct Graph2 {
    int tot, now[maxn], son[maxm], pre[maxm], fa[maxn][18], dep[maxn];
    int64 val[maxm], dis[maxn];
    void put(int a, int b, int64 c) { pre[++tot] = now[a], now[a] = tot, son[tot] = b, val[tot] = c; }
    void add(int a, int b, int64 c) { put(a, b, c), put(b, a, c); }
    void dfs(int u) {
        for (int i = 0; fa[u][i]; i++) fa[u][i + 1] = fa[fa[u][i]][i];
        for (int p = now[u], v = son[p]; p; p = pre[p], v = son[p])
            if (v != fa[u][0])
                fa[v][0] = u, dep[v] = dep[u] + 1, dis[v] = dis[u] + val[p], dfs(v);
    }
    void dfs2(int u) {
        siz[u] = 1, dfn[u] = ++idx, T.insert(idx, u);
        for (int p = now[u], v = son[p]; p; p = pre[p], v = son[p])
            if (v != fa[u][0]) dfs2(v), siz[u] += siz[v];
        last[u] = idx;
    }
    void prepare() { dfs(1), dfs2(1); }
    void swim(int &u, int h) {
        for (int i = 17; h; i--)
            if (h >= (1 << i)) h -= (1 << i), u = fa[u][i];
    }
    int get_lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        swim(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (int i = 17; i >= 0; i--)
            if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
    }
    int64 get_dist(int u, int v) { return dis[u] + dis[v] - 2 * dis[get_lca(u, v)]; }
    int find(int u, int v) {
        swim(u, dep[u] - dep[v] - 1);
        return u;
    }
} G[2];
int calc(int64 x) { return lower_bound(list + 1, list + idx + 1, x) - list; }
int main() {
    read(n), read(m), read(q);
    for (int i = 1; i < n; i++) read(a), read(b), G[0].add(a, b, 1);
    G[0].prepare(), N = n, idx = 1, root[1] = 1, list[1] = N;
    for (int i = 1; i <= m; i++) {
        read(a), read(b);
        int t = calc(b), r = root[t], bb = T.calc(dfn[r], last[r], b - list[t - 1]);
        G[1].add(idx + 1, t, G[0].dis[bb] - G[0].dis[r] + 1);
        N += siz[a], list[++idx] = N, root[idx] = a, from[idx] = bb;
    }
    G[1].dfs(1);
    for (int i = 1; i <= q; i++) {
        read(a), read(b);
        int ta = calc(a), ra = root[ta], aa = T.calc(dfn[ra], last[ra], a - list[ta - 1]);
        int tb = calc(b), rb = root[tb], bb = T.calc(dfn[rb], last[rb], b - list[tb - 1]);
        printf("{%d, %d}\n", ta, aa);
        printf("{%d, %d}\n", tb, bb);
        int lca = G[1].get_lca(ta, tb);
        int64 res = G[0].dis[aa] - G[0].dis[ra] + G[0].dis[bb] - G[0].dis[rb] + G[1].get_dist(ta, tb);
        if (ta == tb)
            printf("%lld\n", G[0].get_dist(aa, bb));
        else if (ta == lca) {
            int frb = from[G[1].find(tb, lca)];
            printf("%lld\n", res - (G[0].dis[aa] + G[0].dis[frb] - G[0].get_dist(aa, frb) - 2 * G[0].dis[ra]));
        } else if (tb == lca) {
            int fra = from[G[1].find(ta, lca)];
            printf("%lld\n", res - (G[0].dis[bb] + G[0].dis[fra] - G[0].get_dist(bb, fra) - 2 * G[0].dis[rb]));
        } else {
            int fra = from[G[1].find(ta, lca)];
            int frb = from[G[1].find(tb, lca)];
            printf("%lld\n", res - (G[0].dis[fra] + G[0].dis[frb] - G[0].get_dist(fra, frb) - 2 * G[0].dis[root[lca]]));
        }
    }
    return 0;
}