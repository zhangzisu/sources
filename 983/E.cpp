#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define let auto
#define INF 0x3F3F3F3F
#define MAXN 200010

int n, m, q, fa[MAXN][18], l[MAXN], r[MAXN], deep[MAXN], dfsclk;
std::vector<int> next[MAXN];
void dfs(int x) {
    l[x] = ++dfsclk;
    for (int i = 1; i < 18; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (int y : next[x]) {
        if (y == fa[x][0]) continue;
        fa[y][0] = x;
        deep[y] = deep[x] + 1;
        dfs(y);
    }
    r[x] = dfsclk;
}
inline int LCA(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    int delta = deep[u] - deep[v];
    for (int i = 17; ~i; i--)
        if ((delta >> i) & 1) u = fa[u][i];
    for (int i = 17; ~i; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}
int gt[MAXN][18], vis[MAXN], ans[MAXN], bit[MAXN], delta[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x) {
    for (int i = x; i <= n; i += lowbit(i)) bit[i]++;
}
inline int qry(int x) {
    int y = 0;
    while (x) y += bit[x], x -= lowbit(x);
    return y;
}
std::vector<std::pair<int, std::pair<int, int>>> dat;

int main() {
    scanf("%d", &n);
    for (int i = 2, x; i <= n; i++) {
        scanf("%d", &x);
        next[x].push_back(i);
    }
    dfs(1);

    scanf("%d", &m);
    for (int i = 1; i <= n; i++) gt[i][0] = i;
    let upd = [](int &x, int y) {if(deep[y]<deep[x])x=y; };
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        let z = LCA(x, y);
        upd(gt[x][0], z);
        upd(gt[y][0], z);
        dat.push_back({l[x], {-INF, l[y]}});
        dat.push_back({l[y], {-INF, l[x]}});
    }
    for (int i = n; i >= 1; i--) upd(gt[fa[i][0]][0], gt[i][0]);
    for (int d = 1; d < 18; d++) {
        for (int i = 1; i <= n; i++) {
            gt[i][d] = gt[i][d - 1];
            upd(gt[i][d], gt[gt[i][d - 1]][d - 1]);
        }
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        let z = LCA(x, y);
        if (deep[gt[x][17]] > deep[z] || deep[gt[y][17]] > deep[z]) {
            ans[i] = -1;
            continue;
        }
        for (int j = 17; ~j; j--)
            if (deep[gt[x][j]] > deep[z]) {
                ans[i] += 1 << j;
                x = gt[x][j];
            }
        for (int j = 17; ~j; j--) {
            if (deep[gt[y][j]] > deep[z]) {
                ans[i] += 1 << j;
                y = gt[y][j];
            }
        }
        if (z == x || z == y) {
            ans[i]++;
            continue;
        }
        vis[i] = 1;
        dat.push_back({l[x] - 1, {i, l[y] - 1}});
        dat.push_back({l[x] - 1, {-i, r[y]}});
        dat.push_back({r[x], {i, r[y]}});
        dat.push_back({r[x], {-i, l[y] - 1}});
    }
    std::sort(dat.begin(), dat.end());
    for (let x : dat) {
        int id = x.second.first;
        int pos = x.second.second;
        if (id == -INF) {
            add(pos);
        } else {
            if (id > 0)
                delta[id] += qry(pos);
            else
                delta[-id] -= qry(pos);
        }
    }

    for (int i = 1; i <= q; i++) printf("%d\n", ans[i] + (vis[i] ? delta[i] ? 1 : 2 : 0));
    return 0;
}