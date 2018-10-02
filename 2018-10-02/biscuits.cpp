#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define MAXN 10000010
typedef long long lnt;
int n, a, b, ans, frc[MAXN], ifrc[MAXN], inv[MAXN], p4[MAXN];
lnt k;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int C(int n, int m) {
    return 1LL * frc[n] * ifrc[m] % MOD * ifrc[n - m] % MOD;
}
int main() {
    frc[0] = frc[1] = ifrc[0] = ifrc[1] = inv[1] = 1;
    p4[0] = 1, p4[1] = 4;
    for (int i = 2; i < MAXN; i++) {
        inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
        frc[i] = 1LL * frc[i - 1] * i % MOD;
        ifrc[i] = 1LL * ifrc[i - 1] * inv[i] % MOD;
        p4[i] = 1LL * p4[i - 1] * 4 % MOD;
    }
    scanf("%d%d%d%lld", &n, &a, &b, &k);
    if (a == 0 && b == 0) {
        printf("%d\n", k ? 0 : p4[n]);
    } else {
        if (!b) std::swap(a, b);
        for (int i = 0; i <= n; i++) {
            if (1LL * i * a > k) break;
            lnt rest = k - 1LL * i * a;
            if (rest % b) continue;
            if (rest / b > n) continue;
            int j = rest / b;
            up(ans, 1LL * C(n, i) * C(n, j) % MOD);
        }
        printf("%d\n", ans);
    }
    return 0;
}