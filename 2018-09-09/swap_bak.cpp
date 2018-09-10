#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
int n, a[MAXN], s[MAXN], f[MAXN][MAXN], ans = 0x3F3F3F3F;
inline void down(int &x, int y) {
    if (y < x) x = y;
}
int main() {
#ifndef DEBUG
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i < n; i++) s[i] = s[i - 1] + std::abs(a[i] - a[i + 1]);
    memset(f, 0x3F, sizeof(f));
    f[1][1] = 0;
    for (int i = 2; i <= n; i++) f[1][i] = s[i - 1] - s[1] + std::abs(a[1] - a[i]);
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= (n - i + 1); j++) {
            int now = a[i - j + 1];
            down(f[i + 1][1], f[i][j] + std::abs(a[i + 1] - now));
            for (int k = 2; k <= (n - i + 1); k++) {
                down(f[i + k][k], f[i][j] + std::abs(a[i + k] - now) + s[i + k - 1] - s[i + 1] + std::abs(a[i + 1] - a[i + k]));
            }
        }
    }
    for (int i = 1; i <= n; i++) down(ans, f[n][i]);
    printf("%d\n", ans);
    return 0;
}