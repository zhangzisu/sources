#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
int n, d[51], sum[51];
long long f[51][51][51], g[51][51];
long long calc(int x2, int x3, int next) {
    if (x2 < 0 || x3 < 0) return 0;
    if (!x2 && !x3 && !next) return 1;
    if (~f[x2][x3][next]) return f[x2][x3][next];
    if (next)
        return f[x2][x3][next] = (x2 * calc(x2 - 1, x3, next - 1) % MOD +
                                  x3 * calc(x2 + 1, x3 - 1, next - 1) % MOD) %
                                 MOD;
    if (x2)
        return f[x2][x3][next] = (((x2 - 1) * calc(x2 - 2, x3, next) % MOD +
                                   x3 * calc(x2, x3 - 1, next)) %
                                  MOD) %
                                 MOD;
    return f[x2][x3][next] =
               ((x3 - 1) * (x3 - 2) / 2) * calc(x2 + 2, x3 - 3, next) % MOD;
}
long long slove(int x, int next) {
    if (x == n && !next) return 1;
    if (!next) return 0;
    if (~g[x][next]) return g[x][next];
    long long ret = 0;
    int x3 = sum[x + next] - sum[x], x2 = next - x3;
    for (int i = n - (x + next); ~i; i--) {
        (ret += calc(x2, x3, i) * slove(x + next, i) % MOD) %= MOD;
    }
    return g[x][next] = ret;
}
int main() {
    memset(f, -1, sizeof(f));
    memset(g, -1, sizeof(g));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &d[i]), sum[i] = sum[i - 1] + (d[i] == 3);
    printf("%lld\n", slove(1, d[1]));
    return 0;
}