#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2010
#define MOD 1000000007
int n, f[MAXN], g[MAXN][MAXN];
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int fuck(int x, int p) {
    int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int main() {
    scanf("%d", &n);
    g[1][1] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= i; j++) {
            up(g[i + 1][j], g[i][j]);
            up(g[i + 1][j + 1], 1LL * j * g[i][j] % MOD);
            up(g[i + 1][j + 2], 1LL * (i - j) * g[i][j] % MOD);
        }
    }
    f[1] = 0;
    for (int i = 2; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= i; j++) up(sum, g[i][j]);
        int inv = fuck(sum, MOD - 2);
        int right = 0;
        for (int j = 2; j < i; j++) up(right, 1LL * g[i][j] * (f[j] + 1) % MOD);
        up(right, g[i][i]);
        right = 1LL * right * inv % MOD;
        f[i] = 1LL * right * fuck(1 - 1LL * g[i][i] * inv % MOD + MOD, MOD - 2) % MOD;
    }
    printf("%d\n", f[n]);
    return 0;
}