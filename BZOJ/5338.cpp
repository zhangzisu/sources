#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXM 5000010
int n, q, v[MAXN];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int deep[MAXN], size[MAXN], fa[MAXN], top[MAXN], dfn[MAXN], pos[MAXN], dfsclk;
void dfs0(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        dfs0(to[i]);
        size[x] += size[to[i]];
    }
}
void dfs1(int x) {
    pos[dfn[x] = ++dfsclk] = x;
    if (!top[x]) top[x] = x;
    int max = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && size[to[i]] > size[max]) max = to[i];
    if (max) top[max] = top[x], dfs1(max);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != max) dfs1(to[i]);
}
int root[MAXN], son[MAXM][2], sum[MAXM], cnt = 0;
void insert(int &n, int N, int pos, int val) {
    n = ++cnt;
    son[n][0] = son[N][0];
    son[n][1] = son[N][1];
    sum[n] = sum[N] + 1;
    if (!~pos) return;
    int rval = (val >> pos) & 1;
    insert(son[n][rval], son[N][rval], pos - 1, val);
}
int query(int n, int N, int pos, int val) {
    if (!~pos) return 0;
    int rval = (val >> pos) & 1;
    if (sum[son[n][rval ^ 1]] - sum[son[N][rval ^ 1]])
        return (1 << pos) | query(son[n][rval ^ 1], son[N][rval ^ 1], pos - 1, val);
    return query(son[n][rval], son[N][rval], pos - 1, val);
}
inline int query(int x, int val) {
    int start = dfn[x], end = dfn[x] + size[x] - 1;
    return query(root[end], root[start - 1], 31, val);
}
inline int query(int x, int y, int val) {
    int ret = 0;
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
        // printf("Query %d->%d\n", x, top[x]);
        ret = std::max(ret, query(root[dfn[top[x]] - 1], root[dfn[x]], 31, val));
        x = fa[top[x]];
    }
    if (deep[x] < deep[y]) std::swap(x, y);
    // printf("Query %d->%d\n", x, y);
    ret = std::max(ret, query(root[dfn[y] - 1], root[dfn[x]], 31, val));
    return ret;
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    dfs0(1);
    dfs1(1);
    for (int i = 1; i <= n; i++) insert(root[i], root[i - 1], 31, v[pos[i]]);
    while (q--) {
        int type, x, y, z;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d", &x, &y);
            printf("%d\n", query(x, y));
        } else {
            scanf("%d%d%d", &x, &y, &z);
            printf("%d\n", query(x, y, z));
        }
    }
    return 0;
}