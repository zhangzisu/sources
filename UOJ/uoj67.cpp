#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], d[MAXN], tot, n, m;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
    d[u]++, d[v]++;
}
int low[MAXN], dfn[MAXN], sb[MAXN], ans[MAXN], p, tim;
void Tarjin(int x, int fa) {
    low[x] = dfn[x] = ++tim;
    int count = 0;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        if (!dfn[to[i]]) {
            count++;
            Tarjin(to[i], x);
            low[x] = std::min(low[x], low[to[i]]);
            if (low[to[i]] >= dfn[x]) sb[x] = 1;
        } else {
            low[x] = std::min(low[x], dfn[to[i]]);
        }
    }
    if (!~fa && count == 1) sb[x] = 0;
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    Tarjin(1, -1);
    for (int i = 1; i <= n; i++)
        if (!sb[i] && d[i] == (m - n + 2)) {
            ans[++p] = i;
        }
    printf("%d\n", p);
    for (int i = 1; i <= p; i++) printf("%d ", ans[i]);
    return 0;
}