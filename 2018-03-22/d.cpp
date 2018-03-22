#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 1010
int n, m, s, t, map[MAXN][MAXN];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int disS[MAXN], disT[MAXN];
struct node {
    int x, dis;
    inline friend bool operator<(const node &a, const node &b) {
        return a.dis > b.dis;
    }
};
std::priority_queue<node> Q;
inline void Dinic(int s, int *dis) {
    memset(dis, 0x3F, sizeof(int) * MAXN);
    dis[s] = 0;
    Q.push({s, 0});
    while (Q.size()) {
        auto top = Q.top().x;
        Q.pop();
        for (int i = head[top]; ~i; i = next[i]) {
            if (dis[to[i]] > dis[top]) {
                dis[to[i]] = dis[top] + 1;
                Q.push({to[i], dis[to[i]]});
            }
        }
    }
}
int cnt[MAXN], ans;
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        $(u, v);
        map[u][v] = map[v][u] = 1;
    }
    Dinic(s, disS);
    Dinic(t, disT);
    int maxFlow = disS[t];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j || map[i][j]) continue;
            if (std::min(disS[i] + disT[j] + 1, disS[j] + disT[i] + 1) >= maxFlow) {
                ans++;
                //printf("D ! %d %d\n", i, j);
            }
        }
    }
    printf("%d\n", ans / 2);
    return 0;
}