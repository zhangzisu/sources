#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 2010
#define MAXM 5010
int head[MAXN], to[MAXM << 1], next[MAXM << 1], tot;
inline void register_edge() {
    memset(head, -1, sizeof(head));
    tot = 0;
}
inline void add_edge(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int dfn[MAXN], low[MAXN], stk[MAXN], ins[MAXN], ecc[MAXN], dfsclk, cnt, top;
inline void register_tj() {
    memset(dfn, 0, sizeof(dfn));
    memset(ins, 0, sizeof(ins));
    memset(ecc, 0, sizeof(ecc));
    dfsclk = cnt = top = 0;
}
void tarjan(int x, int fa) {
    dfn[stk[++top] = x] = low[x] = ++dfsclk;
    ins[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (i == (fa ^ 1)) continue;
        if (dfn[to[i]]) {
            if (ins[to[i]]) low[x] = std::min(low[x], dfn[to[i]]);
        } else {
            tarjan(to[i], i);
            low[x] = std::min(low[x], low[to[i]]);
        }
    }
    if (low[x] >= dfn[x]) {
        ++cnt;
        do {
            ecc[stk[top]] = cnt;
            ins[stk[top]] = 0;
        } while (stk[top--] != x);
    }
}
int n, m, u[MAXM], v[MAXM], ans[MAXM];
std::set<int> s;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d%d", &u[i], &v[i]);
    for (int i = 1; i <= m; i++) {
        register_edge();
        register_tj();
        for (int j = i; j <= m; j++) {
            s.insert(j);
            if (!ecc[u[j]] || !ecc[v[j]] || ecc[u[j]] != ecc[v[j]]) {
                add_edge(u[j], v[j]);
                register_tj();
                for (int k = 1; k <= n; k++)
                    if (!dfn[k]) tarjan(k, -1);
                for (std::set<int>::iterator it = s.begin(); it != s.end();)
                    if (ecc[u[*it]] == ecc[v[*it]]) {
                        ans[*it] += (m - j + 1);
                        s.erase(it++);
                    } else {
                        it++;
                    }
            }
            s.clear();
        }
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}