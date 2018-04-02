#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
#define MAXM 500010
int head[MAXN], to[MAXM], val[MAXM], next[MAXM], dis[MAXN], n, m, c, s, t, tot = 0;
inline void $(int u, int v, int w) { next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++; }
std::priority_queue<std::pair<int, int>> Q;
inline int dfs() {
    memset(dis, 0x3F, sizeof(dis));
    Q.push({dis[s] = 0, s});
    while (Q.size()) {
        int x = Q.top().second;
        Q.pop();
        for (int i = head[x]; ~i; i = next[i])
            if (dis[to[i]] > dis[x] + val[i])
                Q.push({-(dis[to[i]] = dis[x] + val[i]), to[i]});
        for (int i = 1; (x ^ i) <= n; i <<= 1)
            if (dis[x ^ i] > dis[x] + i * c)
                Q.push({-(dis[x ^ i] = dis[x] + i * c), x ^ i});
    }
    return dis[t];
}
int main() {
    scanf("%d%d%d", &n, &m, &c);
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v, w; i <= m; i++) scanf("%d%d%d", &u, &v, &w), $(u, v, w);
    scanf("%d%d", &s, &t);
    printf("%d\n", dfs());
    return 0;
}