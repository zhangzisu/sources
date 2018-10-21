#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
#define MOD 1000000007
inline int fuck(int x, int p) {
    int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int frc[MAXN], inv[MAXN];
inline int C(int n, int m) {
    return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int a, b, n, ans;
inline bool valid(int sum) {
    for (; sum; sum /= 10)
        if ((sum % 10 != a) && (sum % 10 != b)) return 0;
    return 1;
}
int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    scanf("%d%d%d", &a, &b, &n);
    for (int i = 0; i <= n; i++) {
        if (valid(i * a + (n - i) * b)) up(ans, C(n, i));
    }
    printf("%d\n", ans);
    return 0;
}