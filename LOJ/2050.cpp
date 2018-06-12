#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MAXM 1000010
int n, m, q;
namespace tr0 {
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int fa[MAXN][18], deep[MAXN], size[MAXN], in[MAXN], out[MAXN], pos[MAXN], dfsclk = 0;
void dfs(int x) {
    for (int i = 1; i < 18; i++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    size[x] = 1;
    pos[in[x] = ++dfsclk] = x;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
        size[x] += size[to[i]];
    }
    out[x] = dfsclk;
}
inline int lca(int x, int y) {
    if (deep[x] < deep[y]) std::swap(x, y);
    int delta = deep[x] - deep[y];
    for (int i = 17; ~i; i--)
        if ((delta >> i) & 1) x = fa[x][i];
    for (int i = 17; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return x == y ? x : fa[x][0];
}
int root[MAXN], sum[MAXM], L[MAXM], R[MAXM], cnt = 0;
void copy(int &n, int N) {
    n = ++cnt;
    sum[n] = sum[N];
    L[n] = L[N];
    R[n] = R[N];
}
void insert(int &n, int N, int l, int r, int p) {
    copy(n, N);
    sum[n]++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (p <= mid)
        insert(L[n], L[N], l, mid, p);
    else
        insert(R[n], R[N], mid + 1, r, p);
}
int query(int n, int N, int l, int r, int p) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int cL = sum[L[n]] - sum[L[N]];
    if (cL >= p) return query(L[n], L[N], l, mid, p);
    return query(R[n], R[N], mid + 1, r, p);
}
inline void build() {
    for (int i = 1; i <= n; i++) {
        // printf("insert => %d\n", pos[i]);
        insert(root[i], root[i - 1], 1, n, pos[i]);
    }
}
}  // namespace tr0
namespace tr1 {
int head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
    // printf("ADDE %d %d %d\n", u, v, w);
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int fa[MAXN][18], sum[MAXN][18], deep[MAXN];
void dfs(int x) {
    for (int i = 1; i < 18; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
        sum[x][i] = sum[sum[x][i - 1]][i - 1] + sum[x][i - 1];
    }
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        sum[to[i]][0] = val[i];
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
    }
}
inline int lca(int x, int y) {
    if (deep[x] < deep[y]) std::swap(x, y);
    int delta = deep[x] - deep[y];
    for (int i = 17; ~i; i--)
        if ((delta >> i) & 1) x = fa[x][i];
    for (int i = 17; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return x == y ? x : fa[x][0];
}
}  // namespace tr1
int sum[MAXN], L[MAXN], R[MAXN];
int posInOrigin[MAXN], sizePfx[MAXN], from[MAXN], all;
struct info {
    int subTreeID, treeID, rank;
    inline info(int subTreeID, int treeID, int rank) : subTreeID(subTreeID), treeID(treeID), rank(rank) {}
};
info getInfo(int to) {
    int pos = std::lower_bound(sizePfx + 1, sizePfx + all + 1, to) - sizePfx;
    // printf("POS : %d\n", pos);
    int ppos = to - sizePfx[pos - 1];
    // printf("PPOS : %d\n", ppos);
    // printf("pio : %d\n", posInOrigin[pos]);
    int pppos = tr0::query(
        tr0::root[tr0::out[posInOrigin[pos]]],
        tr0::root[tr0::in[posInOrigin[pos]] - 1],
        1,
        n,
        ppos);
    // printf("PPPOS : %d\n", pppos);
    return info(pos, pppos, ppos);
}
int main() {
    scanf("%d%d%d", &n, &m, &q);
    memset(tr0::head, -1, sizeof(tr0::head));
    memset(tr1::head, -1, sizeof(tr1::head));
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        tr0::$(u, v);
    }
    tr0::dfs(1);
    tr0::build();
    sizePfx[all = 1] = tr0::size[1];
    posInOrigin[1] = 1;
    for (int i = 1; i <= m; i++) {
        int x, to;
        scanf("%d%d", &x, &to);
        auto info = getInfo(to);
        // printf("BUILD : {%d, %d, %d}\n", info.subTreeID, info.treeID, info.rank);
        posInOrigin[++all] = x;
        sizePfx[all] = sizePfx[all - 1] + tr0::size[x];
        from[all] = to;
        tr1::$(info.subTreeID, all, tr0::deep[info.treeID] - tr0::deep[posInOrigin[info.subTreeID]]);
    }
    tr1::dfs(1);
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        auto iL = getInfo(l);
        auto iR = getInfo(r);
        // printf("L : {%d, %d, %d}\n", iL.subTreeID, iL.treeID, iL.rank);
        // printf("R : {%d, %d, %d}\n", iR.subTreeID, iR.treeID, iR.rank);
        int ans = 0;
        ans += tr0::deep[iL.treeID] - tr0::deep[posInOrigin[iL.subTreeID]];
        ans += tr0::deep[iR.treeID] - tr0::deep[posInOrigin[iR.subTreeID]];
        int x = iL.subTreeID, y = iR.subTreeID;
        int lca = tr1::lca(x, y);
        ans += tr1::deep[x] + tr1::deep[y] - 2 * tr1::deep[lca];
        for (int i = 17; ~i; i--)
            if (tr1::deep[tr1::fa[x][i]] < tr1::deep[lca])
                x = tr1::fa[x][i], ans += tr1::sum[x][i];
        for (int i = 17; ~i; i--)
            if (tr1::deep[tr1::fa[y][i]] < tr1::deep[lca])
                y = tr1::fa[y][i], ans += tr1::sum[y][i];
        x = getInfo(from[x]).treeID;
        y = getInfo(from[y]).treeID;
        lca = tr0::lca(x, y);
        ans += tr0::deep[x] + tr0::deep[y] - 2 * tr0::deep[lca];
        printf("%d\n", ans);
    }
    return 0;
}