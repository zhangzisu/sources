#include <cstdio>
int n, x, y, map[100][100];
int main() {
    scanf("%d", &n);
    map[x = 1][y = n / 2 + 1] = 1;
    for (int i = 2; i <= n * n; i++) {
        if (x == 1) {
            if (y == n) {
                map[++x][y] = i;
            } else {
                map[x = n][++y] = i;
            }
        } else {
            if (y == n) {
                map[--x][y = 1] = i;
            } else {
                if (!map[x - 1][y + 1]) {
                    map[--x][++y] = i;
                } else {
                    map[++x][y] = i;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d%c", map[i][j], "\t\n"[j == n]);
        }
    }
}