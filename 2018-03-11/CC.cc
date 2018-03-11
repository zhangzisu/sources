#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MAXM 5010
int head[MAXN], to[MAXM << 1], val[MAXM << 1], next[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int n, m, q, w[MAXN], min = 0x7FFFFFFF, max = 0;

int vis[MAXN], fa[MAXN];
void dfs(int x) {
    vis[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (!vis[to[i]]) {
            dfs(to[i]);
            fa[to[i]] = x;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        $(u, v, std::abs(w[u] - w[v]));
        min = std::min(min, std::abs(w[u] - w[v]));
        max = std::max(max, std::abs(w[u] - w[v]));
    }
    for (int i = 1; i <= q; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        register int l = min, r = max, ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (judge(u, v, mid))
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        if (!~ans)
            puts("infinitely");
        else
            printf("%d\n", ans);
    }
    return 0;
}