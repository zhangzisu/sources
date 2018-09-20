#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define MAXN 1010
#define MAXM 5010
int n, a[MAXN], s[MAXN], f[2][MAXM], g[2][MAXM];
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int fuck(int x, int p) {
    int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int frc[MAXM], inv[MAXM];
inline int C(int n, int m) { return n >= m ? 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD : 0; }
int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXM; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXM - 1] = fuck(frc[MAXM - 1], MOD - 2);
    for (int i = MAXM - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
    for (int i = 0; i <= s[n]; i++) g[0][i] = 1;
    for (int i = 1; i <= n; i++) {
        int now = i & 1, pre = now ^ 1;
        memset(f[now], 0, sizeof(f[now]));
        memset(g[now], 0, sizeof(g[now]));
        for (int j = 1; j <= s[n]; j++) {
            f[now][j] = 1LL * g[pre][j - 1] * C(j - s[i - 1] - 1, a[i] - 1) % MOD;
            g[now][j] = g[now][j - 1];
            up(g[now][j], f[now][j]);
        }
    }
    printf("%d\n", f[n & 1][s[n]]);
    return 0;
}