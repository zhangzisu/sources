#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 510
#define EPS 1e-10
int n, m, d, v[MAXN], k, p[MAXN];
std::pair<int, int> g[MAXN], t[MAXN];
double ans;
inline int check(int x, int y) {
    int sum = x;
    for (int i = 1; sum < d * y && i <= m; sum += x) {
        while (t[i].second * y < sum && i <= m) ++i;
        if (t[i].first * y < sum && t[i].second * y > sum) return 0;
    }
    return 1;
}
int main() {
#ifndef DEBUG
    freopen("susume.in", "r", stdin);
    freopen("susume.out", "w", stdout);
#endif
    scanf("%d%d", &n, &d);
    ans = d;
    for (int i = 1; i <= n; i++) scanf("%d%d", &g[i].first, &g[i].second);
    std::sort(g + 1, g + n + 1);
    {
        register int l = g[1].first, r = g[1].second;
        for (register int i = 2; i <= n; i++) {
            if (g[i].first >= r) {
                t[++m] = std::make_pair(l, r);
                l = g[i].first;
                r = g[i].second;
            } else {
                r = std::max(r, g[i].second);
            }
        }
        t[++m] = std::make_pair(l, r);
    }
    for (int i = 1; i <= m; i++) v[++k] = t[i].first, v[++k] = t[i].second;
    std::sort(v + 1, v + k + 1);
    k = std::unique(v + 1, v + k + 1) - v - 1;
    n = 0;
    for (register int i = 1; i <= k; i++) {
        if (!v[i]) goto miyou;
        for (register int j = i + 1; j <= k; j++) {
            if (v[j] % v[i] == 0) goto miyou;
        }
        p[++n] = v[i];
    miyou:;
    }
    for (int i = n; i >= 1; i--) {
        for (register int j = (int)ceil(p[i] / ans); p[i] >= j; j++) {
            if (check(p[i], j)) {
                ans = std::min(ans, 1. * p[i] / j);
            }
        }
    }
    printf("%.10lf\n", ans);
    return 0;
}
