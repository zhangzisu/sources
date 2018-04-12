#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 100010
#define MAXM 1000010
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
int n = $(), m = $(), boom[MAXM];
int d[MAXN], ans[MAXN], vis[MAXN], head[MAXN], to[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int pri[MAXN], isp[MAXN], pnt;
inline void shai() {
    for (int i = 2; i <= n; i++) {
        if (!isp[i]) pri[++pnt] = i;
        for (int j = 1; j <= pnt; j++) {
            if (i * pri[j] > n) break;
            isp[i * pri[j]] = 1;
            if (!(i % pri[j])) continue;
        }
    }
}
int main() {
    shai();
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i <= m; i++)
        $(u = $(), v = $()), d[u]++, d[v]++;
    std::fill(ans + 1, ans + n + 1, 1);
    for (int i = 1; i <= n; i++)
        if (d[i] == n - 1) {
            vis[i] = 1;
            for (int j = head[i]; ~j; j = next[j]) boom[j] = boom[j ^ 1] = 1;
            break;
        }
    for (int _ = 1; _ <= pnt; _++) {
        int now = pri[_];
        int max = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) continue;
            if (d[i] > d[max]) max = i;
        }
        assert(max);
        ans[max] = now;
        vis[max] = 1;
        for (int i = head[max]; ~i; i = next[i]) {
            if (boom[i]) continue;
            boom[i] = boom[i ^ 1] = 1;
            vis[to[i]] = 1;
            ans[to[i]] *= now;
        }
    }

    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}