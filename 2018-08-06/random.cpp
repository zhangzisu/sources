#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
#define MAXM 10010
#define EPS 1e-9
int t, n, k, a[MAXN];
double F[MAXN][MAXM], g[MAXN][MAXM], p[MAXN][MAXM], P[MAXN][MAXM];
int main() {
    p[1][0] = 1;
    for (int i = 1; i < MAXN; i++) {
        for (int j = 0; j <= i * (i - 1) / 2; j++) {
            for (int k = 0; k <= i; k++) {
                p[i + 1][j + k] += p[i][j] / (i + 1);
            }
        }
    }
    for (int i = 1; i < MAXN; i++) {
        for (int j = 0; j <= i * (i - 1) / 2; j++) {
            F[i][j] = F[i][j - 1] + p[i][j] * j;
            P[i][j] = P[i][j - 1] + p[i][j];
        }
    }
    for (int i = 1; i < MAXN; i++) {
        g[i][0] = F[i][i * (i - 1) / 2];
        for (int j = 1; j <= i * (i - 1) / 2; j++) {
            int s = std::min((int)floor(j + g[i][j - 1]), i * (i - 1) / 2);
            g[i][j] += F[i][s] - F[i][j];
            g[i][j] -= j * (P[i][s] - P[i][j]);
            g[i][j] += g[i][j - 1] * (P[i][i * (i - 1) / 2] - P[i][s]);
        }
    }
    for (scanf("%d", &t); t; t--) {
        scanf("%d%d", &n, &k);
        int tot = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            for (int j = 1; j < i; j++) tot += (a[j] > a[i]);
        }
        printf("%f\n", std::min(1. * std::max(tot - k, 0), g[n][std::min(k - 1, n * (n - 1) / 2)]));
    }
    return 0;
}