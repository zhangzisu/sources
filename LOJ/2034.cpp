#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000001
#define MOD 1000000007
int t, n, m, f[MAXN], inv[MAXN], frc[MAXN];
inline int C(int n, int m) { return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD; }
inline int fuck(int x, int p) {
    int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}
int main() {
    f[0] = 1;
    f[1] = 0;
    for (int i = 2; i < MAXN; i++) f[i] = 1LL * (i - 1) * (f[i - 1] + f[i - 2]) % MOD;
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    for (scanf("%d", &t); t; t--) scanf("%d%d", &n, &m), printf("%lld\n", 1LL * C(n, m) * f[n - m] % MOD);
    return 0;
}