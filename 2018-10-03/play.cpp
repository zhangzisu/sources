#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#include <queue>
#define MAXN 1010
#define MAXM 2510
const int INF = 0x3F3F3F3F;
int head[MAXN], to[MAXM], val[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
}
int n, m, k, u[MAXM], v[MAXM], w[MAXM];
int dfn[MAXN], low[MAXN], stk[MAXN], ins[MAXN], bel[MAXN], scc, dfsclk, top;
void tarjan(int x) {
    dfn[x] = low[x] = ++dfsclk;
    ins[stk[++top] = x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (dfn[to[i]]) {
            if (ins[to[i]]) low[x] = std::min(low[x], dfn[to[i]]);
        } else {
            tarjan(to[i]);
            low[x] = std::min(low[x], low[to[i]]);
        }
    }
    if (low[x] >= dfn[x]) {
        scc++;
        do {
            ins[stk[top]] = 0;
            bel[stk[top]] = scc;
        } while (stk[top--] != x);
    }
}
int g[MAXN][MAXN];
inline void up(int &x, int y) {
    if (y < x) x = y;
}
int dis[MAXN];
std::priority_queue<std::pair<int, int>> Q;
inline void d(int s) {
    memset(dis, 0x3F, sizeof(dis));
    dis[s] = 0;
    Q.emplace(0, s);
    while (Q.size()) {
        auto t = Q.top();
        Q.pop();
        if (dis[t.second] != -t.first) continue;
        for (int i = head[t.second]; ~i; i = next[i]) {
            if (dis[to[i]] > val[i] - t.first) {
                Q.emplace(-(dis[to[i]] = val[i] - t.first), to[i]);
            }
        }
    }
}
int main() {
    memset(head, -1, sizeof(head));
    memset(g, 0x3F, sizeof(g));
    n = $(), m = $(), k = $();
    for (int i = 1; i <= m; i++) u[i] = $(), v[i] = $(), w[i] = $(), $(u[i], v[i], w[i]);
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    memset(head, -1, sizeof(head));
    tot = 0;
    for (int i = 1; i <= m; i++) {
        if (bel[u[i]] == bel[v[i]]) continue;
        $(bel[u[i]], bel[v[i]], w[i]);
    }
    for (int u, v; k; k--) {
        u = $(), v = $();
        memset(dis, 0x3F, sizeof(dis));
        d(bel[u]);
        if (dis[bel[v]] == INF) {
            puts("No");
        } else {
            printf("%d\n", dis[bel[v]]);
        }
    }
    return 0;
}