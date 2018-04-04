#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 120
const int pl[24][4] = {{1, 2, 3, 4}, {1, 2, 4, 3}, {1, 3, 2, 4}, {1, 3, 4, 2}, {1, 4, 2, 3}, {1, 4, 3, 2}, {2, 1, 3, 4}, {2, 1, 4, 3}, {2, 3, 1, 4}, {2, 3, 4, 1}, {2, 4, 1, 3}, {2, 4, 3, 1}, {3, 1, 2, 4}, {3, 1, 4, 2}, {3, 2, 1, 4}, {3, 2, 4, 1}, {3, 4, 1, 2}, {3, 4, 2, 1}, {4, 1, 2, 3}, {4, 1, 3, 2}, {4, 2, 1, 3}, {4, 2, 3, 1}, {4, 3, 1, 2}, {4, 3, 2, 1}};
const int pa = 24;
int n, col[5][MAXN][MAXN], res = 0x3F3F3F3F;
int pos(int x, int y) {
    if (x <= n) {
        return y <= n ? 1 : 2;
    } else {
        return y <= n ? 3 : 0;
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                scanf("%1d", &col[i][j][k]);
            }
        }
    }
    for (int d = 0; d < pa; d++) {
        for (int c = 0; c < 2; c++) {
            int ans = 0;
            for (int i = 1; i <= 2 * n; i++) {
                for (int j = 1; j <= 2 * n; j++) {
                    int dd = pl[d][pos(i, j)];
                    int X = i - (i > n ? n : 0);
                    int Y = j - (j > n ? n : 0);
                    if (col[dd][X][Y] != ((i ^ j ^ c)&1)) ans++;
                }
            }
            res = std::min(res, ans);
        }
    }
    printf("%d\n", res);
    return 0;
}