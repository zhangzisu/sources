#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 51
int n, a, b, w[MAXN], m0[1010], m1[1010], all;
int min[MAXN][MAXN], max[MAXN][MAXN];
long long f[MAXN][MAXN][MAXN][MAXN], g[MAXN][MAXN];
inline void up(long long &x, long long y) {
    if (y < x) x = y;
}
inline long long calc(int min, int max) {
    min = m1[min];
    max = m1[max];
    return 1LL * (max - min) * (max - min) * b + a;
}
int main() {
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        m0[w[i]] = 1;
    }
    for (int i = 0; i <= 1010; i++)
        if (m0[i]) m1[m0[i] = ++all] = i;
    for (int i = 1; i <= n; i++) w[i] = m0[w[i]];
    for (int i = 1; i <= n; i++) {
        min[i][i] = max[i][i] = w[i];
        for (int j = i + 1; j <= n; j++) {
            min[i][j] = std::min(min[i][j - 1], w[j]);
            max[i][j] = std::max(max[i][j - 1], w[j]);
        }
    }
    memset(f, 0x3F, sizeof(f));
    for (int i = n; i; i--) {
        for (int j = i; j <= n; j++) {
            f[i][j][min[i][j]][max[i][j]] = 0;
            g[i][j] = calc(min[i][j], max[i][j]);

            if (i == j) continue;

            for (int k = 1; k <= n; k++) {
                for (int l = k; l <= n; l++) {
                    up(f[i][j][std::min(k, w[j])][std::max(l, w[j])], f[i][j - 1][k][l]);
                }
            }

            for (int mid = i; mid < j; mid++) {
                for (int k = 1; k <= n; k++) {
                    for (int l = 1; l <= n; l++) {
                        up(f[i][j][k][l], f[i][mid][k][l] + g[mid + 1][j]);
                    }
                }
            }

            for (int k = 1; k <= n; k++) {
                for (int l = k; l <= n; l++) {
                    up(g[i][j], f[i][j][k][l] + calc(k, l));
                }
            }
        }
    }

    printf("%lld\n", g[1][n]);
    return 0;
}