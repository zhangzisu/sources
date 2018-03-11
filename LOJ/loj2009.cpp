#include <algorithm>
#include <cstdio>
#define MAXN 200010
int n;
long long deep[MAXN], d[MAXN], a[MAXN], f[MAXN][18], g[MAXN][18], ans;
inline long long calc(int x) {
    long long ret = g[x][1];
    for (; x != 1; x >>= 1) {
        if ((x ^ 1) > n)
            ret += a[x >> 2] * (d[x >> 1] - d[x >> 2]);
        else
            ret += a[x ^ 1] * (d[x ^ 1] - d[x >> 1]) + g[x ^ 1][2];
    }
    return ret;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    deep[1] = 1;
    for (int i = 2; i <= n; i++) {
        int x;
        scanf("%d", &x);
        deep[i] = deep[i >> 1] + 1;
        d[i] = d[i >> 1] + x;
    }
    for (int x = n; x; x--) {
        int L = x << 1, R = x << 1 | 1;
        for (int i = 1; i <= deep[x]; i++) {
            int fa = (x >> i), v = (x >> (i - 1)) ^ 1;
            if (L > n)
                f[x][i] = a[v] * (d[x] + d[v] - (d[fa] << 1));
            else if (L == n)
                f[x][i] = f[L][i + 1] + a[L] * (d[L] - d[x]);
            else
                f[x][i] =
                    std::min(a[L] * (d[L] - d[x]) + f[L][1] + f[R][i + 1],
                             a[R] * (d[R] - d[x]) + f[R][1] + f[L][i + 1]);
        }
    }
    for (int x = n; x; x--) {
        int L = x << 1, R = x << 1 | 1;
        for (int i = 1; i <= deep[x]; i++) {
            int fa = (x >> i);
            if (L > n)
                g[x][i] = a[fa] * (d[x] - d[fa]);
            else if (L == n)
                g[x][i] = g[L][i + 1] + a[L] * (d[L] - d[x]);
            else
                g[x][i] =
                    std::min(a[L] * (d[L] - d[x]) + f[L][1] + g[R][i + 1],
                             a[R] * (d[R] - d[x]) + f[R][1] + g[L][i + 1]);
        }
    }
    ans = f[1][1];
    for (int i = 2; i <= n; i++) ans = std::min(ans, calc(i));
    printf("%lld\n", ans);
    return 0;
}