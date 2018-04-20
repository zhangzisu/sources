#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int a[60], stk[5000], n, m, ans;
int pre[60][110], tmp[110][110];
int f[60][110];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), m += a[i];
    for (int i = 1; i <= n; i++) {
        memset(tmp, 0, sizeof(tmp));
        tmp[0][0] = 1;
        for (int k = 0; k < a[i]; k++) {
            for (int l = 0; l < a[i]; l++) {
                for (int g = k + 1; g <= a[i]; g++) {
                    up(tmp[g][l + 1], 1LL * tmp[k][l] * (g - k) % MOD);
                }
            }
        }
        for (int k = 1; k <= a[i]; k++) pre[i][k] = tmp[a[i]][k];
    }
    for (int i = 1; i <= n; i++) {
        //
    }
    printf("%d\n", ans);
    return 0;
}