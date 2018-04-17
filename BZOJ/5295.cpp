#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 10010
#define MAXM 20010
int head[MAXN], to[MAXM << 1], next[MAXM << 1], tot;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int deep[MAXN], vis[MAXN], use[MAXM << 1], stat;
inline void init() {
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(use, 0, sizeof(use));
    memset(deep, 0, sizeof(deep));
    tot = stat = 0;
}
int n, m;
void dfs(int x) {
    if (stat) return;
    vis[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (use[i]) continue;
        use[i] = use[i ^ 1] = 1;
        if (vis[to[i]]) {
            int delta = deep[to[i]] - deep[x] + 1;
            if (delta & 1) return void(stat = 1);
        } else {
            deep[to[i]] = deep[x] + 1;
            dfs(to[i]);
        }
        if (stat) return;
    }
}
int main() {
    for (int _ = $(); _; _--) {
        init();
        n = $(), m = $();
        for (int i = 1; i <= m; i++) $($(), $());
        for (int i = 1; i <= n; i++)
            if (!vis[i]) dfs(i);
        puts(stat ? "NO" : "YES");
    }
    return 0;
}