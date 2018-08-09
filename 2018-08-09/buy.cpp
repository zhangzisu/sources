#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 400010
#define MAXM 5000010
int n, m, q, val[MAXN], all;
int head[MAXN], to[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int dfn[MAXN], low[MAXN], stk[MAXN], dfsclk, snt;
int u[MAXN], v[MAXN];
void tarjin(int x, int fa) {
    dfn[x] = low[x] = ++dfsclk;
    stk[++snt] = x;
    for (int i = head[x]; ~i; i = next[i]) {
        if (i == fa) continue;
        if (dfn[to[i]]) {
            low[x] = std::min(low[x], dfn[to[i]]);
        } else {
            tarjin(to[i], i ^ 1);
            low[x] = std::min(low[x], low[to[i]]);
            if (low[to[i]] >= dfn[x]) {
                int y = ++all;
                do {
                    ++m;
                    u[m] = y;
                    v[m] = stk[snt];
                } while (stk[snt--] != to[i]);
                ++m;
                u[m] = x;
                v[m] = y;
            }
        }
    }
}
int bfn[MAXN], deep[MAXN], fa[MAXN], lm[MAXN], rm[MAXN], bfsclk;
std::queue<int> Q;
inline void bfs(int s) {
    Q.push(s);
    deep[s] = 1;
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        bfn[x] = ++bfsclk;
        for (int i = head[x]; ~i; i = next[i]) {
            deep[to[i]] = deep[x] + 1;
            fa[to[i]] = x;
            Q.push(to[i]);
        }
    }
}
int size[MAXN], top[MAXN];
void dfs(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) dfs(to[i]), size[x] += size[to[i]];
}
void split(int x) {
    dfn[x] = ++dfsclk;
    if (!top[x]) top[x] = x;
    int max = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (size[to[i]] > size[max]) max = to[i];
    if (max) top[max] = top[x], split(max);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != max) split(to[i]);
}
int min[2][MAXN << 2];
inline void modify(int id, int n, int l, int r, int p, int v) {
    if (l == r) return min[id][n] = v, void();
    int mid = (l + r) >> 1;
    p <= mid ? modify(id, n << 1, l, mid, p, v) : modify(id, n << 1 | 1, mid + 1, r, p, v);
    min[id][n] = std::min(min[id][n << 1], min[id][n << 1 | 1]);
}
inline int query(int id, int n, int l, int r, int L, int R) {
    if (l == L && r == R) return min[id][n];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(id, n << 1, l, mid, L, R);
    if (L > mid) return query(id, n << 1 | 1, mid + 1, r, L, R);
    return std::min(query(id, n << 1, l, mid, L, mid), query(id, n << 1 | 1, mid + 1, r, mid + 1, R));
}
inline void changeVal(int x, int v) {
    modify(0, 1, 1, all, bfn[x], v);
    modify(1, 1, 1, all, dfn[x], v);
    if (fa[x]) {
        int u = query(0, 1, 1, all, lm[fa[x]], rm[fa[x]]);
        modify(1, 1, 1, all, dfn[fa[x]], u);
    }
}
inline int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
        u = fa[top[u]];
    }
    return deep[u] < deep[v] ? u : v;
}
inline void query(int u, int v) {
    int ans = 0x3F3F3F3F;
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
        ans = std::min(ans, query(1, 1, 1, all, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (deep[u] > deep[v]) std::swap(u, v);
    ans = std::min(ans, query(1, 1, 1, all, dfn[u], dfn[v]));
    if (u > n) {
        ans = std::min(ans, query(1, 1, 1, all, dfn[fa[u]], dfn[fa[u]]));
    }
    printf("%d\n", ans);
}
char buf[3];
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    all = n;
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (int u, v; m; m--) scanf("%d%d", &u, &v), $(u, v), $(v, u);
    tarjin(1, -1);
    memset(head, -1, sizeof(head));
    tot = dfsclk = bfsclk = 0;
    for (; m; m--) $(u[m], v[m]);
    bfs(1);
    dfs(1);
    split(1);
    for (int x = 1; x <= all; x++) {
        lm[x] = all + 1;
        rm[x] = 0;
        for (int i = head[x]; ~i; i = next[i]) {
            lm[x] = std::min(lm[x], bfn[to[i]]);
            rm[x] = std::max(rm[x], bfn[to[i]]);
        }
    }
    for (int i = 1; i <= n; i++) changeVal(i, val[i]);
    for (int x, y; q; q--) {
        scanf("%s%d%d", buf, &x, &y);
        if (buf[0] == 'C') {
            changeVal(x, y);
        } else {
            query(x, y);
        }
    }
    return 0;
}