#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
inline int fuck(int x, int p) {
    int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}
#define MAXN 200010
int frc[MAXN], inv[MAXN], n, k, ans;
inline int S(int n, int k) {
    int ret = 0;
    for (int j = 1; j <= k; j++) {
        ret += ((k - j) & 1 ? -1LL : 1LL) * frc[k] % MOD * inv[j] % MOD * inv[k - j] % MOD * fuck(j, n) % MOD;
        if (ret < 0) ret += MOD;
        if (ret >= MOD) ret -= MOD;
    }
    return 1LL * ret * inv[k] % MOD;
}
int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    for (int j, i = (scanf("%d%d", &n, &k), 1); i <= n; i++, ans -= (ans >= MOD) ? MOD : 0) scanf("%d", &j), ans += j;
    printf("%lld\n", 1LL * ans * (S(n, k) + 1LL * S(n - 1, k) * (n - 1) % MOD) % MOD);
    return 0;
}