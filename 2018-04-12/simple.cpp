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
int dd[MAXN];
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i <= m; i++)
        $(u = $(), v = $()), d[u]++, d[v]++;
    std::fill(dd + 1, dd + n + 1, 1);
    for (int i = 1; i <= n; i++)
        if (d[i] == n - 1) {
            vis[i] = 1;
            ans[i] = 1;
            for (int j = head[i]; ~j; j = next[j]) {
                boom[j] = boom[j ^ 1] = 1;
                d[to[j]]--;
            }
            break;
        }
    d[0] = -1;
    for (int _ = 2; _ <= n; _++) {
        int max = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[i] || _ % dd[i]) continue;
            if (d[i] > d[max]) max = i;
        }
        assert(max);
        ans[max] = _;
        vis[max] = 1;
        for (int i = head[max]; ~i; i = next[i]) {
            if (boom[i]) continue;
            boom[i] = boom[i ^ 1] = 1;
            d[to[i]]--;
            dd[to[i]] = gcd(_, dd[to[i]]) * dd[to[i]];
        }
    }

    for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
    return 0;
}