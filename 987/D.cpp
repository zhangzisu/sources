#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 100010
int dis[MAXN][101], n, m, k, s;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
std::vector<int> d[101];
std::queue<int> Q;
int vis[MAXN];
inline void bfs(int x) {
    memset(vis, 0, sizeof(vis));
    for (int y : d[x]) Q.push(y), vis[y] = 1, dis[y][x] = 0;
    while (Q.size()) {
        int top = Q.front();
        Q.pop();
        for (int i = head[top]; ~i; i = next[i]) {
            if (vis[to[i]]) continue;
            vis[to[i]] = 1;
            dis[to[i]][x] = dis[top][x] + 1;
            Q.push(to[i]);
        }
    }
}
int main() {
    scanf("%d%d%d%d", &n, &m, &k, &s);
    memset(head, -1, sizeof(head));
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        d[x].push_back(i);
    }
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    for (int i = 1; i <= k; i++) bfs(i);
    for (int i = 1; i <= n; i++) {
        std::sort(dis[i] + 1, dis[i] + k + 1);
        int ans = 0;
        for (int j = 1; j <= s; j++) ans += dis[i][j];
        printf("%d ", ans);
    }
    puts("");
    return 0;
}