#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, a[MAXN], b[MAXN], c[MAXN], f[MAXN][4], table[4][4][4];
inline void init() {
    table[0][0][0] = 0;
    table[0][1][0] = 1;
    table[0][2][0] = 2;
    table[0][3][0] = 3;
    table[0][0][1] = 1;
    table[0][1][1] = 1;
    table[0][2][1] = 2;
    table[0][3][1] = 3;
    table[0][0][2] = 2;
    table[0][1][2] = 2;
    table[0][2][2] = 2;
    table[0][3][2] = 3;
    table[0][0][3] = 3;
    table[0][1][3] = 3;
    table[0][2][3] = 3;
    table[0][3][3] = 3;

    table[1][0][0] = 0;
    table[1][1][0] = 0;
    table[1][2][0] = 1;
    table[1][3][0] = 2;
    table[1][0][1] = 1;
    table[1][1][1] = 0;
    table[1][2][1] = 1;
    table[1][3][1] = 2;
    table[1][0][2] = 2;
    table[1][1][2] = 1;
    table[1][2][2] = 1;
    table[1][3][2] = 2;
    table[1][0][3] = 3;
    table[1][1][3] = 2;
    table[1][2][3] = 2;
    table[1][3][3] = 2;

    table[2][0][0] = 0;
    table[2][1][0] = 0;
    table[2][2][0] = 0;
    table[2][3][0] = 1;
    table[2][0][1] = 1;
    table[2][1][1] = 0;
    table[2][2][1] = 0;
    table[2][3][1] = 1;
    table[2][0][2] = 2;
    table[2][1][2] = 1;
    table[2][2][2] = 0;
    table[2][3][2] = 1;
    table[2][0][3] = 2;
    table[2][1][3] = 2;
    table[2][2][3] = 1;
    table[2][3][3] = 1;

    table[3][0][0] = 0;
    table[3][1][0] = 0;
    table[3][2][0] = 0;
    table[3][3][0] = 0;
    table[3][0][1] = 1;
    table[3][1][1] = 0;
    table[3][2][1] = 0;
    table[3][3][1] = 0;
    table[3][0][2] = 1;
    table[3][1][2] = 1;
    table[3][2][2] = 0;
    table[3][3][2] = 0;
    table[3][0][3] = 1;
    table[3][1][3] = 2;
    table[3][2][3] = 1;
    table[3][3][3] = 0;
}
inline int calc(int x, int y, int z) {
    return table[x][y][z];
}
int main() {
    freopen("rotate.in", "r", stdin);
    freopen("rotate.out", "w", stdout);
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++) c[i] = (b[i] - a[i] + 4) % 4;
    memset(f, 0x3F, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                f[i][j] = std::min(f[i][j], f[i - 1][k] + calc(k, c[i], j));
            }
        }
    }
    printf("%d\n", std::min(std::min(f[n][0], f[n][1]), std::min(f[n][2], f[n][3])));
    return 0;
}