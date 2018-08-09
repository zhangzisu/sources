#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
#define MAXN 100
inline int fuck(int x, int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int x[MAXN][MAXN];
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline void Gauss(int n) {
    for (int i = 0; i < n; i++) {
        int p = i;
        while (p < n && !x[p][i]) p++;
        if (p != i) {
            for (int j = i; j <= n; j++) std::swap(x[i][j], x[p][j]);
        }
        int inv = fuck(x[i][i], MOD - 2);
        for (p = i + 1; p < n; p++) {
            if (!x[p][i]) continue;
            int tmp = 1LL * x[p][i] * inv % MOD;
            for (int j = i; j <= n; j++)
                x[p][j] = (MOD - 1LL * x[i][j] * tmp % MOD + x[p][j]) % MOD;
        }
    }
}
int n;
int main(int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) x[i][j] = fuck(i, j);
        for (int j = 1; j <= i; j++) up(x[i][n + 1], fuck(j, n));
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n + 1; j++) printf("%d ", x[i][j]);
        puts("");
    }
    Gauss(n + 1);
    puts("---");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n + 1; j++) printf("%d ", x[i][j]);
        puts("");
    }
    for (int i = 0; i <= n; i++) printf("%lld\n", 1LL * x[i][n + 1] * fuck(x[i][i], MOD - 2) % MOD);
    return 0;
}
