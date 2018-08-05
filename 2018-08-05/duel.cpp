#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 510
double p[MAXN][MAXN][2], s[MAXN][MAXN][2];
int t, n0, n1, l0, l1, r0, r1;
inline double get0(int x, int l, int r) {
    if (r <= 0) return 0;
    if (l <= 0) return s[r][x][0];
    return s[r][x][0] - s[l - 1][x][0];
}
inline double get1(int x, int l, int r) {
    if (r <= 0) return r - l + 1;
    if (l <= 0) return s[x][r][1] + (1 - l);
    return s[x][r][1] - s[x][l - 1][1];
}
int main() {
#ifndef DEBUG
    freopen("duel.in", "r", stdin);
    freopen("duel.out", "w", stdout);
#endif
    for (scanf("%d", &t); t; t--) {
        scanf("%d%d%d%d%d%d", &n0, &l0, &r0, &n1, &l1, &r1);
        for (int i = 1; i <= n0; i++) {
            for (int j = 1; j <= n1; j++) {
                // for (int k = l0; k <= r0; k++)
                //     p[i][j][0] += (j - k > 0) ? p[i][j - k][1] : 1;
                // for (int k = l1; k <= r1; k++)
                //     p[i][j][1] += (i - k > 0) ? p[i - k][j][0] : 0;
                p[i][j][0] = get1(i, j - r0, j - l0) / (r0 - l0 + 1);
                p[i][j][1] = get0(j, i - r1, i - l1) / (r1 - l1 + 1);

                s[i][j][0] = s[i - 1][j][0] + p[i][j][0];
                s[i][j][1] = s[i][j - 1][1] + p[i][j][1];
            }
        }
        printf("%.3f\n", p[n0][n1][0]);
    }
}