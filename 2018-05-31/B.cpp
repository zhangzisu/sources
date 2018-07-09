#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 55
#define MAXK 25
typedef long long lnt;
const int MIN = -((~0u) >> 1);
lnt f[MAXN][MAXN][MAXK][MAXK], tmp[MAXN];
lnt a[MAXN][MAXN], b[MAXN * MAXN];
lnt t, n, m, nm, k;
inline void up(lnt &x, lnt y) {
    if (y > x) x = y;
}
int main() {
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld%lld", &n, &m, &k);
        nm = n * m;
        for (lnt i = 1; i <= n; i++) {
            for (lnt j = 1; j <= m; j++) {
                scanf("%lld", &a[i][j]);
                b[(i - 1) * m + j] = a[i][j];
            }
        }
        for (lnt i = 1; i <= n; i++)
            for (lnt j = 1; j <= m; j++)
                for (lnt ii = 0; ii <= k; ii++)
                    for (lnt jj = 0; jj <= k; jj++)
                        f[i][j][ii][jj] = MIN;

        f[1][1][0][0] = a[1][1];
        f[1][1][1][0] = 0;

        for (lnt i = 1; i <= n; i++) {
            for (lnt j = 1; j <= m; j++) {
                if (j != m) {
                    for (lnt ii = 0; ii <= k; ii++) {
                        for (lnt jj = 0; jj <= k; jj++) {
                            up(f[i][j + 1][ii][jj], f[i][j][ii][jj] + a[i][j + 1]);
                            up(f[i][j + 1][ii + 1][jj], f[i][j][ii][jj]);
                        }
                    }
                }
                if (i != n) {
                    lnt start = (i - 1) * m + j + 1;
                    lnt end = i * m + j - 1;
                    lnt len = end - start + 1;
                    memcpy(tmp + 1, b + start, sizeof(lnt) * len);
                    std::sort(tmp + 1, tmp + len + 1, [](lnt a, lnt b) { return a > b; });
                    for (lnt ii = 0; ii <= k; ii++) {
                        for (lnt jj = 0; jj <= k; jj++) {
                            for (lnt kk = 0, sum = 0; jj + kk <= k;) {
                                up(f[i + 1][j][ii][jj + kk], f[i][j][ii][jj] + sum + a[i + 1][j]);
                                up(f[i + 1][j][ii + 1][jj + kk], f[i][j][ii][jj] + sum);
                                sum += tmp[++kk];
                            }
                        }
                    }
                }
            }
        }
        lnt ans = 0;
        for (int i = 0; i <= k; i++) up(ans, f[n][m][i][i]);
        printf("%lld\n", ans);
    }
    return 0;
}