#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
int t, n, g, a[MAXN], f[1 << 5][50];
int main() {
    for (scanf("%d", &t); t; t--) {
        scanf("%d%d", &n, &g);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        int tot = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (a[i] > a[j]) tot++;
            }
        }
        if (tot <= g || n * (n - 1) / 2 <= (g - 1)) {
            puts("0");
            continue;
        }
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        int max = n * (n - 1) / 2;
        for (int i = 0; i < (1 << n); i++) {
            for (int j = 0; j <= max; j++) {
                if (!f[i][j]) continue;
                for (int k = 0; k < n; k++) {
                    if ((i >> k) & 1) continue;
                    int tmp = __builtin_popcount(i >> k);
                    if (j + tmp <= max) f[i | (1 << k)][j + tmp] += f[i][j];
                }
            }
        }
        double ans = 0, frc = 1;
        for (int i = 1; i <= n; i++) frc *= i;
        for (int i = 0; i <= max; i++) {
            ans += f[(1 << n) - 1][i] / frc * std::max(i - g + 1, 0);
            // printf("f[%d] = %f\n", i, 1. * f[(1 << n) - 1][i] / frc);
        }
        printf("%f\n", std::min(ans, 1. * (tot - g)));
    }
    return 0;
}