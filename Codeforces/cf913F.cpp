#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
#define MOD 998244353
inline long long fpow(long long x, long long p) {
    register long long ret = 1;
    while (p) {
        if (p & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return ret;
}
long long n, p, _, q[MAXN][MAXN], g[MAXN], f[MAXN];
int main() {
    scanf("%lld%lld%lld", &n, &p, &_);
    p = p * fpow(_, MOD - 2) % MOD;
    q[1][0] = q[1][1] = 1;
    for (long long i = 2; i <= n; i++) {
        q[i][0] = 1;
        for (long long j = 1; j <= i; j++) {
            q[i][j] = (q[i - 1][j] * fpow((1 - p + MOD) % MOD, j) % MOD + q[i - 1][j - 1] * fpow(p, i - j)) % MOD;
        }
    }
    g[1] = 1;
    for (long long i = 2; i <= n; i++) {
        g[i] = 1;
        for (long long j = 1; j < i; j++) g[i] = (g[i] + MOD - (g[j] * q[i][j]) % MOD) % MOD;
        //printf("G[%d] = %d\n", i, g[i]);
    }
    for (long long i = 2; i <= n; i++) {
        long long temp = 0;
        for (long long j = 1; j < i; j++) temp = (temp + g[j] * q[i][j] % MOD * ((j * (i - j) % MOD + (j * (j - 1) / 2) % MOD + f[j] + f[i - j]) % MOD) % MOD) % MOD;
        temp = (temp + g[i] * q[i][i] % MOD * ((i * (i - 1) / 2) % MOD) % MOD) % MOD;
        f[i] = temp * fpow((MOD + 1 - (g[i] * q[i][i]) % MOD) % MOD, MOD - 2) % MOD;
    }
    printf("%lld\n", f[n]);
    return 0;
}