#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MOD 1000000007
int n, m, a[MAXN], b[MAXN], p[MAXN], f[MAXN], ans;
int main() {
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);

    scanf("%d%d", &n, &m);
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = (p[i - 1] << 1) % MOD;
        scanf("%d", &a[i]);
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j) continue;
            b[j]++;
            if (j * j != a[i]) b[a[i] / j]++;
        }
    }
    for (int i = 1; i <= m; i++) f[i] = (p[b[i]] + MOD - 1) % MOD;
    for (int i = m; i >= 1; i--) {
        for (int j = i + i; j <= m; j += i) f[i] = (f[i] + MOD - f[j]) % MOD;
    }
    for (int i = 1; i <= m; i++) ans = (ans + 1LL * i * f[i] % MOD) % MOD;
    printf("%d\n", ans);
    return 0;
}