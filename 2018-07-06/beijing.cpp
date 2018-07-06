#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
#define MAXN 500010
int n, x, y, p;
inline int fuck(int x, int p) {
    int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}
int inv[MAXN], frc[MAXN];
inline int C(int n, int m) { return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD; }
int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

    scanf("%d", &n);
    x = y = n;
    p = fuck(2, MOD - 2);
    while (x && y) {
        int delta = 1LL * C(x + y - 2, x - 1) * fuck(fuck(2, x + y - 2), MOD - 2) % MOD * fuck(2, MOD - 2) % MOD;
        printf("%lld\n", 2LL * delta * fuck(2, 2 * n - 1) % MOD);
        scanf("%d", &p);
        (p == 1 ? x : y)--;
    }
    return 0;
}