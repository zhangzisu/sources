#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 10010
#define MAXM 100010
typedef long long lnt;
const lnt INF = 2000000000LL;
int n, m, s, t, all;
int a[MAXN], b[MAXN], c[MAXN], l[MAXN], r[MAXN];
int head[MAXN], cur[MAXN], to[MAXM], next[MAXM], tot;
lnt cap[MAXM];
inline void $(int u, int v, lnt w) {
    fprintf(stderr, "%d %d %lld\n", u, v, w);
    next[tot] = head[u], to[tot] = v, cap[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
}
std::vector<int> pt[MAXN];
int level[MAXN];
std::queue<int> Q;
inline bool BFS() {
    memset(level, 0, sizeof(level));
    memcpy(cur, head, sizeof(cur));
    level[s] = 1;
    Q.push(s);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; ~i; i = next[i]) {
            if (!level[to[i]] && cap[i]) {
                level[to[i]] = level[x] + 1;
                Q.push(to[i]);
            }
        }
    }
    return level[t];
}
inline lnt DFS(int x, lnt flow) {
    if (!flow || x == t) return flow;
    lnt ret = 0;
    for (int& i = cur[x]; ~i; i = next[i]) {
        if (level[to[i]] == level[x] + 1 && cap[i]) {
            lnt tmp = DFS(to[i], std::min(flow, cap[i]));
            flow -= tmp;
            ret += tmp;
            cap[i] -= tmp;
            cap[i ^ 1] += tmp;
            if (!flow) return ret;
        }
    }
    return ret;
}
inline lnt Dinic() {
    lnt ret = 0;
    while (BFS()) ret += DFS(s, INF);
    return ret;
}
int main() {
    scanf("%d%d", &n, &m);
    s = ++all;
    t = ++all;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i], &b[i], &c[i]);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &l[i], &r[i]);
        pt[i].push_back(++all);
        $(s, pt[i].front(), INF * 2);
        for (int j = l[i]; j <= r[i]; j++) {
            lnt val = j * j * a[i] + j * b[i] + c[i];
            int tmp = ++all;
            $(pt[i].back(), tmp, INF - val);
            pt[i].push_back(tmp);
        }
        $(pt[i].back(), t, INF * 2);
    }
    for (int i = 1, u, v, d; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &d);
        for (int i = l[v]; i <= r[v]; i++) {
            int j = i + d;
            if (j >= r[u]) continue;
            $(pt[u][std::max(j - l[u] + 1, 0)], pt[v][i - l[v] + 1], INF * 2);
        }
    }
    printf("%lld\n", INF * n - Dinic());
    return 0;
}