#include <algorithm>
#include <cstdio>
#include <cstring>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], deep[MAXN], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int dfn[MAXN], low[MAXN], stk[MAXN], ins[MAXN], bel[MAXN], pfx[MAXN][2];
int tim, dcc, top, u[MAXN], v[MAXN], fa[MAXN][18], n, m, p;
void Tarjin(int x, int fa) {
    dfn[x] = low[x] = ++tim;
    ins[stk[++top] = x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (i == fa) continue;
        if (dfn[to[i]]) {
            if (ins[to[i]]) low[x] = std::min(low[x], dfn[to[i]]);
        } else {
            Tarjin(to[i], i ^ 1), low[x] = std::min(low[x], low[to[i]]);
        }
    }
    if (low[x] == dfn[x]) {
        dcc++;
        do {
            ins[stk[top]] = 0;
            bel[stk[top]] = dcc;
        } while (stk[top--] != x);
    }
}
void prepare(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        prepare(to[i]);
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
int Q[MAXN], qnt, root[MAXN], rnt;
void dfs(int x) {
    Q[++qnt] = x;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x][0]) dfs(to[i]);
}
int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u[i], &v[i]);
        $(u[i], v[i]);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) Tarjin(root[++rnt] = i, -1);
    tot = 0;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++)
        if (bel[u[i]] != bel[v[i]]) $(bel[u[i]], bel[v[i]]);
    for (int i = 1; i <= rnt; i++) prepare(bel[root[i]]);
    for (int d = 1; d < 18; d++)
        for (int i = 1; i <= dcc; i++) fa[i][d] = fa[fa[i][d - 1]][d - 1];
    scanf("%d", &p);
    while (p--) {
        int u, v, l;
        scanf("%d%d", &u, &v);
        u = bel[u], v = bel[v];
        l = lca(u, v);
        pfx[l][0]--, pfx[u][0]++;
        pfx[l][1]--, pfx[v][1]++;
    }
    for (int i = 1; i <= rnt; i++) dfs(bel[root[i]]);
    for (int i = qnt; i; i--) {
        pfx[fa[Q[i]][0]][0] += pfx[Q[i]][0];
        pfx[fa[Q[i]][0]][1] += pfx[Q[i]][1];
    }
    for (int i = 1; i <= m; i++) {
        if (bel[u[i]] == bel[v[i]]) {
            putchar('B');
        } else if (deep[bel[u[i]]] > deep[bel[v[i]]]) {
            if (pfx[bel[u[i]]][0] && !pfx[bel[u[i]]][1])
                putchar('R');
            else if (!pfx[bel[u[i]]][0] && pfx[bel[u[i]]][1])
                putchar('L');
            else
                putchar('B');
        } else {
            if (pfx[bel[v[i]]][0] && !pfx[bel[v[i]]][1])
                putchar('L');
            else if (!pfx[bel[v[i]]][0] && pfx[bel[v[i]]][1])
                putchar('R');
            else
                putchar('B');
        }
    }
    puts("");
    return 0;
}