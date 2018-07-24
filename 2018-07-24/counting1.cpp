#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define popcount(x) __builtin_popcount(x)
#define MAXN 1010
#define MOD 1000000007
int n, m, k, f[MAXN][MAXN][2][2][2][2], g[MAXN], frc[MAXN], inv[MAXN], ans;
inline int fuck(int x, int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int C(int n, int m) {
    return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
int main() {
    scanf("%d%d", &n, &k);
    frc[0] = 1;
    for (int i = 1; i <= n; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[n] = fuck(frc[n], MOD - 2);
    for (int i = n; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    f[1][0][0][0][0][0] = 1;
    f[1][1][1][0][1][0] = 1;
    f[1][1][0][1][0][0] = 1;
    f[1][1][0][0][0][1] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k0 = 0; k0 < 2; k0++) {
                for (int k1 = 0; k1 < 2; k1++) {
                    for (int op = 0; op < 2; op++) {
                        for (int ed = 0; ed < 2; ed++) {
                            int now = f[i][j][k0][k1][op][ed];
                            if (!now) continue;
                            up(f[i + 1][j][k1][0][op][ed], now);
                            if (k0 == 0) {
                                int npos = i;
                                if ((npos != 1 || !op) && (npos != n || !ed))
                                    up(f[i + 1][j + 1][k1][0][op || npos == 1][ed || npos == n], now);
                            }
                            if (k1 == 0) {
                                int npos = i % n + 1;
                                if ((npos != 1 || !op) && (npos != n || !ed))
                                    up(f[i + 1][j + 1][1][0][op || npos == 1][ed || npos == n], now);
                            }
                            int npos = (i + 1) % n + 1;
                            if ((npos != 1 || !op) && (npos != n || !ed))
                                up(f[i + 1][j + 1][k1][1][op || npos == 1][ed || npos == n], now);
                        }
                    }
                }
            }
        }
    }
    for (int j = k; j <= n; j++) {
        for (int k0 = 0; k0 < 2; k0++) {
            for (int k1 = 0; k1 < 2; k1++) {
                for (int op = 0; op < 2; op++) {
                    for (int ed = 0; ed < 2; ed++) {
                        int now = f[n][j][k0][k1][op][ed];
                        up(g[j], 1LL * frc[n - j] * now % MOD);
                    }
                }
            }
        }
    }
    for (int i = n; i >= k; i--) {
        for (int j = i + 1; j <= n; j++) {
            g[i] = g[i] - 1LL * g[j] * C(j, i) % MOD;
            if (g[i] < 0) g[i] += MOD;
        }
        up(ans, g[i]);
    }
    printf("%d\n", ans);
    return 0;
}