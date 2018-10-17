#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
typedef long long lnt;
lnt f[MAXN][MAXN], g[2][MAXN][MAXN];
int h[MAXN], c, n, m;
int main() {
    freopen("construct.in", "r", stdin);
    freopen("construct.out", "w", stdout);
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; i++) scanf("%d", h + i), m = std::max(m, h[i]);
    memset(f, 0x3F, sizeof(f));
    memset(g, 0x3F, sizeof(g));
    for (int i = h[1]; i <= m; i++) f[1][i] = 1LL * (i - h[1]) * (i - h[1]);
    for (int i = 1; i <= m; i++) g[0][1][i] = std::min(g[0][1][i - 1], f[1][i] - 1LL * c * i);
    for (int i = m; i >= 1; i--) g[1][1][i] = std::min(g[1][1][i + 1], f[1][i] + 1LL * c * i);
    for (int i = 2; i <= n; i++) {
        for (int j = h[i]; j <= m; j++) {
            f[i][j] = std::min(g[1][i - 1][j] - 1LL * c * j, g[0][i - 1][j] + 1LL * c * j) + 1LL * (j - h[i]) * (j - h[i]);
        }
        for (int j = 1; j <= m; j++) g[0][i][j] = std::min(g[0][i][j - 1], f[i][j] - 1LL * c * j);
        for (int j = m; j >= 1; j--) g[1][i][j] = std::min(g[1][i][j + 1], f[i][j] + 1LL * c * j);
    }
    lnt ans = (~0ULL) >> 1;
    for (int i = 1; i <= m; i++) ans = std::min(ans, f[n][i]);
    printf("%lld\n", ans);
    return 0;
}