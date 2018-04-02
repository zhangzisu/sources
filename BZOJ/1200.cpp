#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define $ long long
$ n, sum, ans, a[MAXN], val[MAXN][15], cnt[MAXN], f[MAXN][2][15];
inline void up($ &x, $ y) { x = x < y ? y : x; }
int main() {
    scanf("%lld", &n);
    for ($ i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        sum += a[i];
        for ($ j = a[i] - 1; j <= a[i] + 1; j++) {
            for ($ k = i - 2; k <= i + 2; k++) {
                if (k >= 1 && k <= n) val[k][cnt[k]++] = j;
            }
        }
    }
    for ($ i = 1; i <= n; i++) {
        std::sort(val[i], val[i] + cnt[i]);
        cnt[i] = std::unique(val[i], val[i] + cnt[i]) - val[i] - 1;
        while (cnt[i] && val[i][cnt[i] - 1] > a[i]) cnt[i]--;
        // printf("D ➜ ");
        // for ($ j = 0; j < cnt[i]; j++) printf("%lld ", val[i][j]);
        // puts("");
    }
    memset(f, 0x80, sizeof(f));
    for ($ i = 0; i < cnt[1]; i++) f[1][0][i] = f[1][1][i] = val[1][i];
    for ($ i = 2; i <= n; i++) {
        for ($ j = 0; j < cnt[i - 1]; j++) {
            for ($ k = 0; k < cnt[i]; k++) {
                if (val[i - 1][j] < val[i][k]) {
                    up(f[i][0][k], f[i - 1][1][j] + val[i][k]);
                } else if (val[i - 1][j] > val[i][k]) {
                    up(f[i][1][k], f[i - 1][0][j] + val[i][k]);
                } else {
                    up(f[i][0][k], f[i - 1][0][j] + val[i][k]);
                    up(f[i][1][k], f[i - 1][1][j] + val[i][k]);
                }
            }
        }
    }
    for ($ i = 0; i < cnt[n]; i++) up(ans, f[n][0][i]), up(ans, f[n][1][i]);
    printf("%lld\n", sum - ans);
    return 0;
}