#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
#define MOD 1000000007
int a[MAXN], b[MAXN], c[MAXN], k[MAXN], e[MAXN], n, m;
inline void fuck(int a[], int b[]) {
    memset(e, 0, sizeof(e));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            (e[i + j] += 1LL * a[i] * b[j] % MOD) %= MOD;
        }
    }
    for (int i = (m << 1) - 2; i >= m; i--) {
        for (int j = 1; j <= m; j++) {
            (e[i - j] += 1LL * e[i] * k[j] % MOD) %= MOD;
        }
    }
    memcpy(a, e, sizeof(int) * m);
}
int main() {
    scanf("%d%d", &n, &m);
    a[0] = b[1] = k[1] = c[0] = 1;
    for (int i = 1; i < m - 1; i++) {
        k[i + 1] = 1LL * k[i] * i % MOD;
    }
    for (int i = 1; i < m; i++) {
        k[i] = 1LL * k[i] * (m - i) % MOD;
        c[i] = 1LL * c[i - 1] * m % MOD;
    }
    while (n) {
        if (n & 1) fuck(a, b);
        fuck(b, b);
        n >>= 1;
    }
	// for(int i = 0;i < m;i++)printf("DBG :: %d\n", a[i]);
    int ans = 0;
    for (int i = 0; i < m; i++) (ans += 1LL * a[i] * c[i] % MOD) %= MOD;
    printf("%d\n", ans);
    return 0;
}