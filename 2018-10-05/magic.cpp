#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
int n, m, a[MAXN][MAXN], b[MAXN];
double f[MAXN][MAXN], g[MAXN][MAXN], ans;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            b[i] += a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            double p = 1. * a[i][j] / b[i];
            f[j][i] = f[j][i - 1] + p;
            g[j][i] = g[j][i - 1] + (2 * f[j][i - 1] + 1) * p;
        }
    }
    for (int i = 1; i <= m; i++) ans += g[i][n];
    printf("%.2f\n", ans);
    return 0;
}