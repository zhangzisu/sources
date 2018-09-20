#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define MAXN 100010
#define MAXM 500010
int n, a[MAXN], s[MAXN], ans = 1;
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
    freopen("qiang.in", "r", stdin);
    freopen("qiang.out", "w", stdout);
    frc[0] = 1;
    for (int i = 1; i < MAXM; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXM - 1] = fuck(frc[MAXM - 1], MOD - 2);
    for (int i = MAXM - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
    for (int i = 1; i <= n; i++) ans = 1LL * ans * C(s[i] - 1, a[i] - 1) % MOD;
    printf("%d\n", ans);
    return 0;
}