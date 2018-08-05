#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 5000010
#define MAXM 8000010
#define MAXV 10000010
int pri[664580], pnt = 0;
std::bitset<MAXV> vis;
inline void shai() {
    for (int i = 2; i < MAXV; i++) {
        if (!vis[i]) pri[++pnt] = i;
        for (int j = 1; j <= pnt; j++) {
            if (i * pri[j] >= MAXV) break;
            vis.set(i * pri[j]);
            if (i % pri[j] == 0) break;
        }
    }
}
int t, n, m, a[MAXN], arb[MAXN];
int max = 0, mmax = 0, mpos = 0;
std::vector<std::pair<int, int>> val[MAXN];
std::map<std::pair<int, int>, int> M;
int HEAD[MAXN], TO[MAXN << 1], NEXT[MAXN << 1], TOT;
inline void ADD(int u, int v) {
    NEXT[TOT] = HEAD[u], TO[TOT] = v, HEAD[u] = TOT++;
}
int ha[MAXN], min;
void solve(int x) {
    if (x <= n) ha[x] = 1;
    int max = 0;
    for (int i = HEAD[x]; ~i; i = NEXT[i]) {
        solve(TO[i]);
        ha[x] += ha[TO[i]];
        max = std::max(max, ha[TO[i]]);
    }
    if (x <= n) {
        max = std::max(max, ::max - ha[x]);
        min = std::min(min, max);
    }
}

int head[MAXN], to[MAXM], next[MAXM], tot;
inline void add(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int fill(int x) {
    int ret = (x <= n);
    arb[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (!arb[to[i]]) ret += fill(to[i]);
    }
    return ret;
}
int dfn[MAXN], low[MAXN], stk[MAXN], top, dfsclk;
inline void tarjin(int s, int f) {
    dfn[s] = low[s] = ++dfsclk;
    stk[++top] = s;
    for (int i = head[s]; ~i; i = next[i]) {
        if (i == f) continue;
        if (dfn[to[i]]) {
            low[s] = std::min(low[s], dfn[to[i]]);
        } else {
            tarjin(to[i], i ^ 1);
            low[s] = std::min(low[s], low[to[i]]);
            if (low[to[i]] >= dfn[s]) {
                int z = ++m;
                while (stk[top] != s) {
                    ADD(z, stk[top--]);
                }
                ADD(s, z);
            }
        }
    }
}
int main() {
    shai();
    for (scanf("%d", &t); t; t--) {
        scanf("%d", &n);
        m = n;
        M.clear();
        memset(head, -1, sizeof(head));
        memset(HEAD, -1, sizeof(HEAD));
        memset(ha, 0, sizeof(ha));
        memset(dfn, 0, sizeof(dfn));
        memset(arb, 0, sizeof(arb));
        tot = TOT = dfsclk = top = 0;
        max = 0, mmax = 0, mpos = 0;

        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            val[i].clear();
            for (int j = 1; j <= pnt && a[i] && a[i] != 1; j++) {
                int cnt = 0;
                while (a[i] % pri[j] == 0) cnt++, a[i] /= pri[j];
                if (cnt) {
                    val[i].emplace_back(j, cnt > 1);
                }
            }
        }

        fprintf(stderr, "M: %d\n", m);

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < (int)val[i].size(); j++) {
                if (val[i][j].second) {
                    int u = i;
                    int v = M[std::make_pair(val[i][j].first, val[i][j].first)];
                    if (!v) v = M[std::make_pair(val[i][j].first, val[i][j].first)] = ++m;
                    add(u, v);
                }
                for (int k = j + 1; k < (int)val[i].size(); k++) {
                    int u = i;
                    int v = M[std::make_pair(val[i][j].first, val[i][k].first)];
                    if (!v) v = M[std::make_pair(val[i][j].first, val[i][k].first)] = ++m;
                    add(u, v);
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (!arb[i]) {
                int size = fill(i);
                if (size > max) {
                    mpos = i;
                    max = size;
                } else if (size > mmax) {
                    mmax = size;
                }
            }
        }

        min = max;
        tarjin(mpos, -1);
        solve(mpos);
        fprintf(stderr, "> %d %d %d %d\n", max, mmax, mpos, min);
        printf("%d\n", std::max(min, mmax));
    }
    return 0;
}