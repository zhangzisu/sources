#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define MOD 1000000007
inline int fuck(int x, int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
inline void up(int &x, int y) {
    x %= MOD;
    y %= MOD;
    x += y;
    if (x >= MOD) x -= MOD;
    if (x < 0) x += MOD;
}
int x[550][550], y[550];
inline void Gauss(int n) {
    for (int i = 0; i < n; i++) {
        int p = i;
        while (p < n && !x[p][i]) p++;
        if (p != i) {
            for (int j = i; j <= n; j++) std::swap(x[i][j], x[p][j]);
        }
        int inv = fuck(x[i][i], MOD - 2);
        for (p = 0; p < n; p++) {
            if (i == p) continue;
            int tmp = 1LL * x[p][i] * inv % MOD;
            for (int j = i; j <= n; j++)
                x[p][j] = (MOD - 1LL * x[i][j] * tmp % MOD + x[p][j]) % MOD;
        }
    }
}
void solve(int n) {
    n += 1;
    memset(x, 0, sizeof(x));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) x[i][j] = fuck(i, j);
        for (int j = 1; j <= i; j++) up(x[i][n + 1], fuck(j, n - 1));
    }
    Gauss(n + 1);
    for (int i = 0; i <= n; i++) y[i] = 1LL * x[i][n + 1] * fuck(x[i][i], MOD - 2) % MOD;
}
int n, m, a, ans, b[550], f[550], C[550][550];
int main() {
    C[0][0] = 1;
    for (int i = 1; i < 550; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
    scanf("%d%d%d", &n, &m, &a);
    for (int i = 0; i <= m; i++) scanf("%d", &b[i]);
    if (a == 1) {
        solve(m);
        for (int i = 0; i <= m; i++) {
            int tmp = 0;
            for (int j = 0, t = 1; j < 60; j++, t = 1LL * t * n % MOD) {
                up(tmp, 1LL * t * y[j] % MOD);
            }
            up(ans, 1LL * tmp * b[i] % MOD);
        }
        printf("%d\n", (ans + b[0]) % MOD);
        return 0;
    }
    f[0] = 1LL * (fuck(a, n + 1) - a + MOD) % MOD * fuck(a - 1, MOD - 2) % MOD;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= i; j++) {
            up(f[i], (j & 1 ? 1LL : -1LL) * C[i][j] % MOD * f[i - j] % MOD);
        }
        up(f[i], -1LL * fuck(a, n + 1) * fuck(n, i) % MOD);
        f[i] = 1LL * f[i] * fuck(((1 - a) % MOD + MOD) % MOD, MOD - 2) % MOD;
    }
    ans = b[0];
    for (int i = 0; i <= m; i++) up(ans, 1LL * b[i] * f[i] % MOD);
    printf("%d\n", ans);
}