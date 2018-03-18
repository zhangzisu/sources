#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 5010
#define _ long long
_ n, m, k, MOD, a[MAXN], C[MAXN], ans;
_ Matrix[MAXN][MAXN];
void prepare(_ m) {
    if (!m) {
        memset(C, 0, sizeof(C));
        C[0] = 1;
    } else {
        if ((m & 1) == 1) {
            prepare(m - 1);
            for (int i = k; i; i--) {
                (C[i] += C[i - 1]) %= MOD;
            }
        } else {
            prepare(m >> 1);
            for (int i = k; i; i--) {
                for (int j = 0; j < i; j++) {
                    (C[i] += C[i - j] * C[j] % MOD) %= MOD;
                }
            }
        }
    }
}

int main() {
#ifndef DEBUG
    freopen("tencent.in", "r", stdin);
    freopen("tencent.out", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &MOD);
    for (_ i = 1; i <= n; i++) scanf("%lld", &a[i]), k = std::max(k, a[i] << 1);
    prepare(m);

	// for(int i = 0;i < 10;i++)printf("%lld ", C[i]);

    for (_ i = 1; i <= n; i++)
        for (_ j = 1; j <= n; j++)
            Matrix[i][j] = C[a[i] + a[n - j + 1]];

    _ ans = 1;
    for (_ i = 1; i <= n; i++) {
        for (_ j = i + 1; j <= n; j++) {
            while (Matrix[j][i] != 0) {
                _ delta = Matrix[i][i] / Matrix[j][i];
                for (_ k = 1; k <= n; k++) {
                    ((Matrix[i][k] -= Matrix[j][k] * delta % MOD) += MOD) %= MOD;
                    std::swap(Matrix[i][k], Matrix[j][k]);
                }
                ans = MOD - ans;
            }
        }
        (ans *= Matrix[i][i]) %= MOD;
    }

    printf("%lld\n", ans);
#ifndef DEBUG
    fclose(stdin);
    fclose(stdout);
#endif
}
