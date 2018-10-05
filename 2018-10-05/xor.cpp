#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
int n, m, a[500][500], b[500], p[500], ans = 0;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
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
        if (b[i]) {
            int count = 0;
            for (int j = 1; j <= m; j++) {
                if (j == i) continue;
                for (int k = 1; k <= n; k++) {
                    if (k == b[i]) continue;
                    if (a[k][j]) {
                        count++;
                        break;
                    }
                }
            }
            up(ans, 1LL * p[count] * p[m - i]);
        }
    }
    printf("%d\n", ans);
    return 0;
}