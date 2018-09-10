#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 500010
int n, m, k, MOD, a[MAXN], v[MAXN];
int inv[MAXN], frc[MAXN];
inline int fuck(int x, int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
inline int C(int n, int m) {
    return n >= m ? 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD : 0;
}
inline int lucas(int n, int m) {
    if (n < m) return 0;
    if (n < MOD && m < MOD) return C(n % MOD, m % MOD);
    return 1LL * C(n % MOD, m % MOD) * lucas(n / MOD, m / MOD) % MOD;
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int sum[MAXN], res[MAXN], max, min;
int main() {
#ifndef DEBUG
    freopen("setdiff.in", "r", stdin);
    freopen("setdiff.out", "w", stdout);
#endif
    n = $(), k = $(), MOD = $();
    {
        const int limit = std::min(MOD, n + 1);
        frc[0] = 1;
        for (int i = 1; i < limit; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
        inv[limit - 1] = fuck(frc[limit - 1], MOD - 2);
        for (int i = limit - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    }
    for (int i = 1; i <= n; i++) a[i] = $();
    memcpy(v, a, sizeof(v));
    std::sort(v + 1, v + n + 1);
    m = std::unique(v + 1, v + n + 1) - v - 1;
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(v + 1, v + n + 1, a[i]) - v;
    for (int i = 1; i <= n; i++) sum[a[i]]++;
    for (int i = 1; i <= m; i++) {
        sum[i] += sum[i - 1];
        res[i] = lucas(sum[i], k);
    }
    for (int i = 1, pre = 0; i <= m; i++) {
        res[i] -= pre;
        up(max, 1LL * res[i] * v[i] % MOD);
        up(pre, res[i]);
    }
    memset(sum, 0, sizeof(sum));
    memset(res, 0, sizeof(res));
    for (int i = n; i >= 1; i--) sum[a[i]]++;
    for (int i = m; i >= 1; i--) {
        sum[i] += sum[i + 1];
        res[i] = lucas(sum[i], k);
    }
    for (int i = m, pre = 0; i >= 1; i--) {
        res[i] -= pre;
        up(min, 1LL * res[i] * v[i] % MOD);
        up(pre, res[i]);
    }
    printf("%d\n", (max - min + MOD) % MOD);
    return 0;
}