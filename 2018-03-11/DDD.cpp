#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
using std::stack;
#define MAXN 100000
#define MAXE 400000
int head[MAXN], next[MAXE], to[MAXE], tot;
inline void addEdge(int u, int v) {
    next[tot] = head[u];
    to[tot] = v;
    head[u] = tot++;
    next[tot] = head[v];
    to[tot] = u;
    head[v] = tot++;
}
int dfn[MAXN], low[MAXN], ins[MAXN], idx;
stack<int> s;
int dcc[MAXN], cnt;
inline void Tarjin(int x, int fa) {
    dfn[x] = low[x] = idx++;
    s.push(x);
    ins[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (i == (fa ^ 1)) continue;
        if (dfn[to[i]]) {
            if (ins[to[i]]) low[x] = std::min(low[x], dfn[to[i]]);
        } else {
            Tarjin(to[i], i);
            low[x] = std::min(low[x], low[to[i]]);
        }
    }
    if (low[x] == dfn[x]) {
        int t;
        do {
            t = s.top();
            s.pop();
            ins[t] = 0;
            dcc[t] = cnt;
        } while (t != x);
        cnt++;
    }
}
int fa[MAXN], dp[MAXN], bc, bg[MAXN];
inline int query(int x, int y) {
    while (dp[x] > dp[y]) {
        if (!bg[x]) {
            bg[x] = 1;
            bc--;
        }
        x = fa[x];
    }
    while (dp[x] < dp[y]) {
        if (!bg[y]) {
            bg[y] = 1;
            bc--;
        }
        y = fa[y];
    }
    while (x != y) {
        if (dp[x] == dp[y]) {
            if (!bg[x]) {
                bg[x] = 1;
                bc--;
            }
            x = fa[x];
            if (!bg[y]) {
                bg[y] = 1;
                bc--;
            }
            y = fa[y];
        } else {
            while (dp[x] > dp[y]) {
                if (!bg[x]) {
                    bg[x] = 1;
                    bc--;
                }
                x = fa[x];
            }
            while (dp[x] < dp[y]) {
                if (!bg[y]) {
                    bg[y] = 1;
                    bc--;
                }
                y = fa[y];
            }
        }
    }
    return bc;
}
int vst[MAXN];
inline void dfs(int x) {
    vst[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (vst[to[i]]) continue;
        if (dcc[x] != dcc[to[i]]) {
            fa[dcc[to[i]]] = dcc[x];
            dp[dcc[to[i]]] = dp[dcc[x]] + 1;
        }
        dfs(to[i]);
    }
}
int n, m, q, u, v, ___ = 0;
int main() {
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        memset(head, -1, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(ins, 0, sizeof(ins));
        memset(dcc, -1, sizeof(dcc));
        memset(vst, 0, sizeof(vst));
        memset(bg, 0, sizeof(bg));
        memset(fa, 0, sizeof(fa));
        memset(dp, 0, sizeof(dp));
        cnt = tot = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            addEdge(u - 1, v - 1);
        }
        idx = 1;
        for (int i = 0; i < n; i++)
            if (!dfn[i]) Tarjin(i, -1);
        fa[dcc[0]] = -1;
        dp[dcc[0]] = 0;
        bc = cnt - 1;
        dfs(0);
        scanf("%d", &q);
        printf("Case %d:\n", ++___);
        while (q--) {
            scanf("%d%d", &u, &v);
            printf("%d\n", query(dcc[u - 1], dcc[v - 1]));
        }
        printf("\n");
    }
    return 0;
}