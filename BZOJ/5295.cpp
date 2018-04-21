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
int head[MAXN], u[MAXM], v[MAXM], to[MAXM << 1], next[MAXM << 1], tot;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int deep[MAXN], vis[MAXN], size[MAXN], use[MAXM << 1], stat, cnt;
inline void init() {
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(use, 0, sizeof(use));
    memset(deep, 0, sizeof(deep));
    memset(size, 0, sizeof(size));
    tot = stat = cnt = 0;
}
int n, m;
void dfs(int x) {
    if (stat) return;
    vis[x] = cnt;
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
        for (int i = 1; i <= m; i++) $(u[i] = $(), v[i] = $());
        for (int i = 1; i <= n; i++)
            if (!vis[i]) ++cnt, dfs(i);
        for (int i = 1; i <= n; i++) size[vis[i]]--;
        for (int i = 1; i <= m; i++) size[vis[u[i]]]++;
        for (int i = 1; i <= cnt; i++)
            if (size[i] >= 2) {
                stat = 1;
                break;
            }
        puts(stat ? "NO" : "YES");
    }
    return 0;
}