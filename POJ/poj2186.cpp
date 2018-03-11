#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50010
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int dfn[MAXN], low[MAXN], stk[MAXN], ins[MAXN], bel[MAXN], scs[MAXN];
int top, tim, scc, cnt, ans, n, m, u[MAXN], v[MAXN], d[MAXN];
void Tarjin(int x) {
    dfn[x] = low[x] = ++tim;
    ins[stk[++top] = x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (dfn[to[i]]) {
            if (ins[to[i]]) low[x] = std::min(low[x], dfn[to[i]]);
        } else {
            Tarjin(to[i]), low[x] = std::min(low[x], low[to[i]]);
        }
    }
    if (dfn[x] == low[x]) {
        scc++;
        do {
            ins[stk[top]] = 0;
            bel[stk[top]] = scc;
            scs[scc]++;
        } while (stk[top--] != x);
    }
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u[i], &v[i]);
        $(u[i], v[i]);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) Tarjin(i);
    for (int i = 1; i <= m; i++)
        if (bel[u[i]] != bel[v[i]]) d[bel[u[i]]]++;
    for (int i = 1; i <= scc; i++)
        if (!d[i]) cnt++, ans = scs[i];
    if (cnt > 1) ans = 0;
    printf("%d\n", ans);
    return 0;
}