#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
int n, m, v[1010], f[1010][16][3][3];
char buf[1010];

int main() {
    scanf("%d%d%s", &n, &m, buf + 1);
    for (int i = 1; i <= m; i++) v[i] = buf[i] == 'N' ? 0 : buf[i] == 'O' ? 1 : 2;
    v[m + 1] = -1;
    f[0][0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int d1 = 0; d1 < 3; d1++) {
                for (int d2 = 0; d2 < 3; d2++) {
                    if (!f[i][j][d1][d2]) continue;
                    for (int d3 = 0; d3 < 3; d3++) {
                        if (d1 == 0 && d2 == 1 && d3 == 2) continue;
                        f[i + 1][j + (v[j + 1] == d3)][d2][d3] += f[i][j][d1][d2];
                        printf("[%4d%4d%4d%4d]<=[%4d%4d%4d%4d]\n", i + 1, j + (v[j + 1] == d3), d2, d3, i, j, d1, d2);
                    }
                }
            }
        }
    }
    for (int k = 0; k <= m; k++) {
        int ans = 0;
        for (int d1 = 0; d1 < 3; d1++) {
            for (int d2 = 0; d2 < 3; d2++) {
                ans += f[n][k][d1][d2];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
