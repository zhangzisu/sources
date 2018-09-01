#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 200010
#define MAXM 800010
int n, q, left[MAXN], right[MAXN], color[MAXN];
int head[MAXN], to[MAXM], next[MAXM], val[MAXM], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int dis[MAXN], dist[MAXN][5];
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
inline void smin(int &x, int y) {
    if (x > y) x = y;
}
char buf[MAXN];
int main() {
    freopen("nostalgia.in", "r", stdin);
    freopen("nostalgia.out", "w", stdout);
    scanf("%d%d%s", &n, &q, buf + 1);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        left[i] = left[i - 1];
        if (isalpha(buf[i])) left[i] = i;
    }
    for (int i = n; i >= 1; i--) {
        right[i] = right[i + 1];
        if (isalpha(buf[i])) right[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (i != n) $(i, i + 1, 2);
    }
    for (int i = 1; i <= n; i++) {
        if (left[i] == i) {
            color[i] = buf[i] - 'A' + 1;
            $(i, n + color[i], 1);
        }
    }
    for (int i = 1; i <= 4; i++) {
        d(n + i);
        for (int j = 1; j <= n; j++) dist[j][i] = dis[j];
    }
    for (int u, v, ans; q; q--) {
        scanf("%d%d", &u, &v);
        if (u > v) std::swap(u, v);
        ans = v - u;
        for (int i = 1; i <= 4; i++) smin(ans, (dist[u][i] + dist[v][i]) / 2);
        printf("%d\n", ans);
    }
    return 0;
}