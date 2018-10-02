#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MAXK 3010
#define MOD 998244353
int n, a, b, k;
int f[MAXN][MAXK];
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int main() {
    scanf("%d%d%d%d", &n, &a, &b, &k);
    f[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (!f[i][j]) continue;
            up(f[i + 1][j], f[i][j]);
            if (j + a <= k) up(f[i + 1][j + a], f[i][j]);
            if (j + b <= k) up(f[i + 1][j + b], f[i][j]);
            if (j + a + b <= k) up(f[i + 1][j + a + b], f[i][j]);
        }
    }
    printf("%d\n", f[n][k]);
    return 0;
}