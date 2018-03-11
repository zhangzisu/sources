#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000003
#define MAXN 1100000
int n, m, k;
long long frc[MAXN], inv[MAXN];
inline long long fpow(long long x, int p) {
    long long ret = 1;
    while (p) {
        if (p & 1) (ret *= x) %= MOD;
        (x *= x) %= MOD;
        p >>= 1;
    }
    return ret;
}
inline long long C(int n, int m) { return n < m ? 0 : frc[n] * inv[m] % MOD * inv[n - m] % MOD; }
inline long long lucas(int n, int m) {
    if (n < m) return 0;
    if(n < MOD && m < MOD)return C(n % MOD, m % MOD);
    return (long long)C(n % MOD, m % MOD) * lucas(n / MOD, m / MOD) % MOD;
}
std::pair<int, int> p[MAXN];
long long f[MAXN], ans;
int main() {
    scanf("%d%d%d", &n, &m, &k);
    frc[0] = 1;
    for (int i = 1; i < MOD; i++) frc[i] = frc[i - 1] * i % MOD;
    inv[MOD - 1] = fpow(frc[MOD - 1], MOD - 2);
    for (int i = MOD - 1; i; i--) inv[i - 1] = inv[i] * i % MOD;
    for (int i = 1, x, y; i <= k; i++) {
        scanf("%d%d", &x, &y);
        p[i] = std::make_pair(x, y);
    }
    if (k == 0) return printf("%lld\n", lucas(m, n)), 0;
    std::sort(p + 1, p + k + 1);
    p[++k] = std::make_pair(n + 1, m + 1);
    for (int i = 1; i <= k; i++) f[i] = lucas(p[i].second - 1, p[i].first - 1);
    for (int i = 1; i <= k; i++) {
    	f[i] = lucas(p[i].second - 1, p[i].first - 1);
    	for(int j = 1;j < k;j++){
    		if(p[j].first < p[i].first && p[j].second < p[i].second)
    			f[i] = (MOD + f[i] - lucas(p[i].second - p[j].second - 1, p[i].first - p[j].first - 1) * f[j] % MOD) % MOD;
		}
    }
    printf("%lld\n", f[k]);
    return 0;
}
