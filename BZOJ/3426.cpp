#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
#define MAXM 1000010
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
int head[MAXN], to[MAXM << 1], next[MAXM << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, m, k, cnt, ans[MAXN], d[MAXN];
inline void dfs(int x) {
    d[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        d[to[i]] = 1;
        for (int j = head[to[i]]; ~j; j = next[j]) {
            d[to[j]] = 1;
        }
    }
}
int main() {
    n = $(), m = $(), k = $();
    memset(head, -1, sizeof(head));
    for (register int i = 1; i <= m; i++) $($(), $());
    for (register int i = 1; i <= n; i++)
        if (!d[i]) dfs(ans[++cnt] = i);
    for (register int i = (printf("%d\n", cnt), 1); i <= cnt; i++) printf("%d%c", ans[i], " \n"[i == cnt]);
    return 0;
}