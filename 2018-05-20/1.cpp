#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 128
#define MOD 1000000007

int n, m, a[MAXN], f[MAXN][MAXN][MAXN], ans = 0;

int main() {
    scanf("%d", &n);
    m = (n << 1) - 1;
    for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
    std::sort(a + 1, a + m + 1);
    auto u = [](int &x, int y) {if((x+=y)>=MOD)x-=MOD; };
    f[n][a[n] != a[n - 1]][a[n] != a[n + 1]] = 1;
    for (int i = n; i > 1; i--) {
        int L = a[i - 1] != a[i - 2];
        int R = a[m - i + 2] != a[m - i + 3];
        for (int l = 0; l <= m; l++) {
            for (int r = 0; r <= m; r++) {
                int now = f[i][l][r];
                u(f[i - 1][l + L][r + R], now);
                for (int k = 0; k < l; k++) u(f[i - 1][k + L][r + R + 1], now);
                for (int k = 0; k < r; k++) u(f[i - 1][l + L + 1][k + R], now);
            }
        }
    }
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= m; j++)
            u(ans, f[1][i][j]);

    printf("%d\n", ans);
    return 0;
}