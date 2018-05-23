#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 300010
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
char buf[MAXN];
int fa[MAXN][20], deep[MAXN];

void dfs(int x) {
    for (int i = 1; i < 20; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
    }
}
int LCA(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    int delta = deep[u] - deep[v];
    for (int i = 19; ~i; i--)
        if ((delta >> i) & 1) u = fa[u][i];
    for (int i = 19; ~i; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return u == v ? u : fa[u][0];
}
int q;
int s1, e1, t1, l1, len1;
int s2, e2, t2, l2, len2;
inline bool judge(int mid) {
    //
}
int main() {
    scanf("%d", &n);
    scanf("%s", buf);
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    dfs(1);
    scanf("%d", &q);
    while (q--) {
        s1, e1, s2, e2;
        scanf("%d%d%d%d", &s1, &e1, &s2, &e2);
        t1 = LCA(s1, e1), t2 = LCA(s2, e2);
        len1 = deep[s1] + deep[e1] - deep[t1] * 2 + 1;
        len2 = deep[s2] + deep[e2] - deep[t2] * 2 + 1;
        l1 = deep[s1] - deep[t1] + 1;
        l2 = deep[]
        int l = 0, r = std::min(len1, len2), ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (judge(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}