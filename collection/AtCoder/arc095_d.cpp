#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, dis[MAXN], fa[MAXN];
std::queue<int> Q;
int bfs(int x) {
    Q.push(x);
    dis[x] = fa[x] = 0;
    int ans = x;
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; ~i; i = next[i]) {
            if (to[i] == fa[x]) continue;
            fa[to[i]] = x;
            if ((dis[to[i]] = dis[x] + 1) > dis[ans]) ans = to[i];
            Q.push(to[i]);
        }
    }
    return ans;
}
int h, t, body[MAXN], k[MAXN], p[MAXN], m;
int ans0[MAXN], ans1[MAXN];
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y);
        $(x, y);
    }
    t = bfs(h = bfs(1));
    // printf("H : %d, T : %d\n", h, t);
    for (int x = t;; x = fa[x]) {
        body[x] = 1;
        p[++m] = x;
        // printf("%d ", x);
        if (x == h) break;
    }
    // puts("");
    for (int i = 1; i <= n; i++) {
        if (!body[i]) {
            if (!body[fa[i]]) return puts("-1"), 0;
            k[fa[i]]++;
        }
    }
    for (int i = 1, x = 1; i <= m; i++) {
        for (int j = 1; j <= k[p[i]]; j++) ans0[x + j - 1] = x + j;
        ans0[x + k[p[i]]] = x;
        x += k[p[i]] + 1;
    }
    std::reverse(p + 1, p + m + 1);
    for (int i = 1, x = 1; i <= m; i++) {
        for (int j = 1; j <= k[p[i]]; j++) ans1[x + j - 1] = x + j;
        ans1[x + k[p[i]]] = x;
        x += k[p[i]] + 1;
    }
    for (int i = 1; i <= n; i++) {
        if (ans0[i] > ans1[i]) {
            std::swap(ans0, ans1);
            break;
        } else if (ans0[i] < ans1[i])
            break;
    }
    for (int i = 1; i <= n; i++) printf("%d%c", ans0[i], " \n"[i == n]);
    return 0;
}