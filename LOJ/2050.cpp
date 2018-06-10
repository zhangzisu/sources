#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MAXM 5000010
typedef long long lnt;
lnt n, m, q;
namespace tr0 {
lnt head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(lnt u, lnt v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
lnt fa[MAXN][18], deep[MAXN], size[MAXN], in[MAXN], out[MAXN], pos[MAXN], dfsclk = 0;
void dfs(lnt x) {
    for (lnt i = 1; i < 18; i++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    size[x] = 1;
    pos[in[x] = ++dfsclk] = x;
    for (lnt i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
        size[x] += size[to[i]];
    }
    out[x] = dfsclk;
}
inline lnt lca(lnt x, lnt y) {
    if (deep[x] < deep[y]) std::swap(x, y);
    lnt delta = deep[x] - deep[y];
    for (lnt i = 17; ~i; i--)
        if ((delta >> i) & 1) x = fa[x][i];
    for (lnt i = 17; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return x == y ? x : fa[x][0];
}
lnt root[MAXN], sum[MAXM], L[MAXM], R[MAXM], cnt = 0;
void copy(lnt &n, lnt N) {
    n = ++cnt;
    sum[n] = sum[N];
    L[n] = L[N];
    R[n] = R[N];
}
void insert(lnt &n, lnt N, lnt l, lnt r, lnt p) {
    copy(n, N);
    sum[n]++;
    if (l == r) return;
    lnt mid = (l + r) >> 1;
    if (p <= mid)
        insert(L[n], L[N], l, mid, p);
    else
        insert(R[n], R[N], mid + 1, r, p);
}
lnt query(lnt n, lnt N, lnt l, lnt r, lnt p) {
    if (l == r) return l;
    lnt mid = (l + r) >> 1;
    lnt cL = sum[L[n]] - sum[L[N]];
    if (cL >= p) return query(L[n], L[N], l, mid, p);
    return query(R[n], R[N], mid + 1, r, p - cL);
}
inline void build() {
    for (lnt i = 1; i <= n; i++) {
        // printf("insert => %lld\n", pos[i]);
        insert(root[i], root[i - 1], 1, n, pos[i]);
    }
}
}  // namespace tr0
namespace tr1 {
lnt head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(lnt u, lnt v, lnt w) {
    // printf("ADDE %lld %lld %lld\n", u, v, w);
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
lnt fa[MAXN][18], sum[MAXN][18], deep[MAXN];
void dfs(lnt x) {
    for (lnt i = 1; i < 18; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
        sum[x][i] = sum[fa[x][i - 1]][i - 1] + sum[x][i - 1];
    }
    for (lnt i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        sum[to[i]][0] = val[i];
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
    }
}
inline lnt lca(lnt x, lnt y) {
    if (deep[x] < deep[y]) std::swap(x, y);
    lnt delta = deep[x] - deep[y];
    for (lnt i = 17; ~i; i--)
        if ((delta >> i) & 1) x = fa[x][i];
    for (lnt i = 17; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return x == y ? x : fa[x][0];
}
}  // namespace tr1
lnt posInOrigin[MAXN], sizePfx[MAXN], from[MAXN], all;
struct info {
    lnt subTreeID, treeID, rank;
    inline info(lnt subTreeID, lnt treeID, lnt rank) : subTreeID(subTreeID), treeID(treeID), rank(rank) {}
};
info getInfo(lnt to) {
    lnt pos = std::lower_bound(sizePfx + 1, sizePfx + all + 1, to) - sizePfx;
    lnt ppos = to - sizePfx[pos - 1];
    lnt pppos = tr0::query(
        tr0::root[tr0::out[posInOrigin[pos]]],
        tr0::root[tr0::in[posInOrigin[pos]] - 1],
        1,
        n,
        ppos);
    return info(pos, pppos, ppos);
}
int main() {
    scanf("%lld%lld%lld", &n, &m, &q);
    memset(tr0::head, -1, sizeof(tr0::head));
    memset(tr1::head, -1, sizeof(tr1::head));
    for (lnt i = 1, u, v; i < n; i++) {
        scanf("%lld%lld", &u, &v);
        tr0::$(u, v);
    }
    tr0::dfs(1);
    tr0::build();
    sizePfx[all = 1] = tr0::size[1];
    posInOrigin[1] = 1;
    for (lnt i = 1; i <= m; i++) {
        lnt x, to;
        scanf("%lld%lld", &x, &to);
        auto info = getInfo(to);
        posInOrigin[++all] = x;
        sizePfx[all] = sizePfx[all - 1] + tr0::size[x];
        from[all] = to;
        tr1::$(info.subTreeID, all, tr0::deep[info.treeID] - tr0::deep[posInOrigin[info.subTreeID]]);
    }
    tr1::dfs(1);
    while (q--) {
        lnt l, r;
        scanf("%lld%lld", &l, &r);
        auto iL = getInfo(l);
        auto iR = getInfo(r);
        lnt x = iL.subTreeID, y = iR.subTreeID;
        lnt lca = tr1::lca(x, y);
        lnt ans = 0;
        if (x == y) {
            x = iL.treeID;
            y = iR.treeID;
            lca = tr0::lca(x, y);
            ans += tr0::deep[x] + tr0::deep[y] - 2 * tr0::deep[lca];
        } else if (x == lca) {
            ans += tr0::deep[iR.treeID] - tr0::deep[posInOrigin[iR.subTreeID]];
            ans += tr1::deep[y] - tr1::deep[x];
            for (lnt i = 17; ~i; i--)
                if (tr1::deep[tr1::fa[y][i]] > tr1::deep[lca])
                    ans += tr1::sum[y][i], y = tr1::fa[y][i];
            x = iL.treeID;
            y = getInfo(from[y]).treeID;
            lca = tr0::lca(x, y);
            ans += tr0::deep[x] + tr0::deep[y] - 2 * tr0::deep[lca];
        } else if (y == lca) {
            ans += tr0::deep[iL.treeID] - tr0::deep[posInOrigin[iL.subTreeID]];
            ans += tr1::deep[x] - tr1::deep[y];
            for (lnt i = 17; ~i; i--)
                if (tr1::deep[tr1::fa[x][i]] > tr1::deep[lca])
                    ans += tr1::sum[x][i], x = tr1::fa[x][i];
            x = getInfo(from[x]).treeID;
            y = iR.treeID;
            lca = tr0::lca(x, y);
            ans += tr0::deep[x] + tr0::deep[y] - 2 * tr0::deep[lca];
        } else {
            ans += tr0::deep[iL.treeID] - tr0::deep[posInOrigin[iL.subTreeID]];
            ans += tr0::deep[iR.treeID] - tr0::deep[posInOrigin[iR.subTreeID]];
            ans += tr1::deep[x] + tr1::deep[y] - 2 * tr1::deep[lca];
            for (lnt i = 17; ~i; i--)
                if (tr1::deep[tr1::fa[x][i]] > tr1::deep[lca])
                    ans += tr1::sum[x][i], x = tr1::fa[x][i];
            for (lnt i = 17; ~i; i--)
                if (tr1::deep[tr1::fa[y][i]] > tr1::deep[lca])
                    ans += tr1::sum[y][i], y = tr1::fa[y][i];
            x = getInfo(from[x]).treeID;
            y = getInfo(from[y]).treeID;
            lca = tr0::lca(x, y);
            ans += tr0::deep[x] + tr0::deep[y] - 2 * tr0::deep[lca];
        }
        printf("%lld\n", ans);
    }
    return 0;
}