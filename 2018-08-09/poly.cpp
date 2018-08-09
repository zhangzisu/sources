#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
inline int fuck(int x, int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int n, m, a, ans, b[110];
const int inv2 = fuck(2, MOD - 2);
const int inv6 = fuck(6, MOD - 2);
int main() {
    scanf("%d%d%d", &n, &m, &a);
    for (int i = 0; i <= m; i++) scanf("%d", &b[i]);
    if (a == 1) {
        if (0 <= m) up(ans, 1LL * b[0] * (n + 1) % MOD);
        if (1 <= m) up(ans, 1LL * b[1] * n % MOD * (n + 1) % MOD * inv2 % MOD);
        if (2 <= m) up(ans, 1LL * b[2] * n % MOD * (n + 1) % MOD * (2 * n + 1) % MOD * inv6 % MOD);
        printf("%d\n", ans);
        return;
    }
    for (int k = 0; k <= n; k++) {
        int t = fuck(a, k), g = 0;
        for (int i = 0, j = 1; i <= m; i++, j = 1LL * j * k % MOD) {
            up(g, 1LL * j * b[i] % MOD);
        }
        up(ans, 1LL * t * g % MOD);
    }
    printf("%d\n", ans);
}