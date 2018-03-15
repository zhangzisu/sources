#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
#define MOD 1000000007
int n, m, k, a[MAXN], f[MAXN], g[MAXN], mu[MAXN];

int main() {
    freopen("google.in", "r", stdin);
    freopen("google.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), m = std::max(m, a[i]);
    for (int i = 1; i <= k; i++) mu[i] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 2; i * j <= m; j++) {
            (((mu[i * j] -= mu[i]) %= MOD) += MOD) %= MOD;
        }
    }
    for (int i = 1; i <= a[1]; i++) f[i] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= a[i - 1]; j++) g[j] = 0;
        for (int j = 1; j <= a[i - 1]; j++) {
            for (int k = 1; j * k <= a[i - 1]; k++) {
                (g[j] += f[j * k]) %= MOD;
            }
        }
        for (int j = 1; j <= a[i]; j++) f[j] = 0;
        for (int j = 1; j <= a[i - 1]; j++) {
            for (int k = 1; j * k <= a[i]; k++) {
                (f[j * k] += 1LL * g[j] * mu[j] % MOD) %= MOD;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= a[n]; i++) (ans += f[i]) %= MOD;
    printf("%d\n", ans);
    return 0;
}