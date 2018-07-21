#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 210
#define MOD 1000000007
int n, m, a[MAXN], f[MAXN][MAXN][1010], ans;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    std::sort(a + 1, a + n + 1);
    f[1][1][0] = f[1][0][0] = 1;
    for (int i = 1; i < n; i++) {
        int delta = a[i + 1] - a[i], next;
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= m; k++) {
                if ((next = k + j * delta) > m) continue;
                if (!f[i][j][k]) continue;
                if (j > 0)
                    up(f[i + 1][j - 1][next], 1LL * f[i][j][k] * j % MOD);
                up(f[i + 1][j][next], 1LL * f[i][j][k] * (j + 1) % MOD);
                up(f[i + 1][j + 1][next], f[i][j][k]);
            }
        }
    }
    for (int i = 0; i <= m; i++) up(ans, f[n][0][i]);
    printf("%d\n", ans);
    return 0;
}