#include <cstdio>
int vis[1010][1010], n, ans;
void fill(int x, int y) {
    if (vis[x][y]) return;
    vis[x][y] = 1;
    if (x > 1) fill(x - 1, y);
    if (x < n) fill(x + 1, y);
    if (y > 1) fill(x, y - 1);
    if (y < n) fill(x, y + 1);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &vis[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (vis[i][j]) continue;
            ans++;
            fprintf(stderr, "(%d, %d)\n", i - 1, j - 1);
            fill(i, j);
        }
    }
    printf("%d\n", ans);
    return 0;
}