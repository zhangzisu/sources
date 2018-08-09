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
inline int Gauss(int n) {
    int ret = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (x[i][j] < 0) x[i][j] += MOD;
    for (int i = 0; i < n; i++) {
        int p = i;
        while (p < n && !x[p][i]) p++;
        if (p >= n) return 0;
        if (p != i) {
            for (int j = i; j < n; j++) std::swap(x[i][j], x[p][j]);
            ret = MOD - ret;
        }
        ret = 1LL * ret * x[i][i] % MOD;
        int inv = fuck(x[i][i], MOD - 2);
        for (p = i + 1; p < n; p++) {
            if (!x[p][i]) continue;
            int tmp = 1LL * x[p][i] * inv % MOD;
            for (int j = i; j < n; j++)
                x[p][j] = (MOD - 1LL * x[i][j] * tmp % MOD + x[p][j]) % MOD;
        }
    }
    return ret;
}
int n;
int main(int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        int tmp = 0;
        for (int j = 0, t = 1; j <= n; j++, t = 1LL * t * i % MOD) {
            x[i][j] = t;
            (tmp += fuck(j, i)) %= MOD;
        }
        x[i][n + 1] = tmp;
    }
    Gauss(n + 1);
    //
    return 0;
}
