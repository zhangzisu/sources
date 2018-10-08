#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
int n, m, a[500][500], b[500], p[500], ans = 0;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int f[500][2][2], g[500][2][2];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%1d", &a[i][j]);
            if (!b[j] && a[i][j]) b[j] = i;
        }
    }
    p[0] = 1;
    for (int i = 1; i <= m; i++) p[i] = p[i - 1], up(p[i], p[i - 1]);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            memcpy(g, f, sizeof(g));
            for (int k = 1; k <= m; k++) {
                for (int d0 = 0; d0 < 2; d0++) {
                    for(int d1 = 0;d1 < 2;d1++){
                        // f[k][d0][d1] |= f[k][d0^a[]]
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}