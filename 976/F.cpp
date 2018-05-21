#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 4010
#define MAXM 24010
#define INF 0x3F3F3F3F
int n, m, e, s, t;
int head[MAXN << 1], cur[MAXN << 1], to[MAXM], next[MAXM], cap[MAXM], tot = 0;
inline void $(int u, int v, int c) {
    next[tot] = head[u], to[tot] = v, cap[tot] = c, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, cap[tot] = 0, head[v] = tot++;
    // printf("%d %d %d\n", u, v, c);
}
int u[MAXN], v[MAXN], id[MAXN], d[MAXN << 1], deg;
int level[MAXN];
std::queue<int> Q;
inline int BFS() {
    Q.push(s);
    memset(level, 0, sizeof(level));
    memcpy(cur, head, sizeof(head));
    level[s] = 1;
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; ~i; i = next[i]) {
            if (!cap[i]) continue;
            if (!level[to[i]]) {
                level[to[i]] = level[x] + 1;
                Q.push(to[i]);
            }
        }
    }
    return level[t];
}
int DFS(int x, int flow) {
    if (x == t||!flow) return flow;
    int ret = 0, tmp;
    for (int &i = cur[x]; ~i; i = next[i]) {
        if (cap[i] && level[to[i]] == level[x] + 1) {
            tmp = DFS(to[i], std::min(flow, cap[i]));
            cap[i] -= tmp;
            cap[i ^ 1] += tmp;
            ret += tmp;
            flow -= tmp;
            if (!flow) return ret;
        }
    }
    return ret;
}
inline int Dinic() {
    int ret = 0;
    while (BFS()) ret += DFS(s, INF);
    return ret;
}

std::vector<int> ans[MAXN];
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &e);
    s = n + m + 1;
    t = n + m + 2;
    for (int i = 1; i <= e; i++) {
        scanf("%d%d", &u[i], &v[i]);
        d[u[i]]++;
        d[v[i] + n]++;
    }
    deg = INF;
    for (int i = 1; i <= n + m; i++) deg = std::min(deg, d[i]);
    //printf("DEG : %d\n", deg);
    for (int i = 1; i <= n; i++) $(s, i, d[i] - deg);
    for (int i = 1; i <= m; i++) $(i + n, t, d[i + n] - deg);
    int top = tot;
    for (int i = 1; i <= e; i++) $(u[i], v[i] + n, 1), id[i] = tot - 2;
    for (int i = deg; i >= 1; i--) {
        Dinic();
        for (int j = 1; j <= e; j++)
            if (cap[id[j]]) ans[i].push_back(j);
        for (int j = 0; j < top; j += 2) cap[j]++;
    }
    puts("0");
    for (int i = 1; i <= deg; i++) {
        printf("%lu", ans[i].size());
        for (int x : ans[i]) printf(" %d", x);
        puts("");
    }
    return 0;
}