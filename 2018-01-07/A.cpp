#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 60
char map[MAXN][MAXN];
int n, m, dx, dy, dis[MAXN][MAXN], vis[MAXN][MAXN], cnt[MAXN][MAXN];
int Q[MAXN * MAXN][2], ans = 0x3F3F3F3F;
inline bool ok(int x, int y) { return x && x <= n && y && y <= m && map[x][y] != 'X'; }
inline int cast(int x1, int y1, int x2, int y2) {
    if (x1 > x2) std::swap(x1, x2), std::swap(y1, y2);
    if (dy > std::min(y1, y2)) return 0;
    if (dx <= x1 || dx > x2) return 0;
    return 1;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", map[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (map[i][j] == '*')
                Q[0][0] = i, Q[0][1] = j, vis[i][j] = 1;
            else if (map[i][j] == 'X')
                dx = i, dy = j;
        }
    }
    int H = 0, T = 0;
    while (H <= T) {
        int x = Q[H][0], y = Q[H++][1];
        for (int i = -1, nx, ny, nf; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                if ((i || j) && ok(nx = x + i, ny = y + j)) {
                    nf = cnt[x][y] ^ cast(x, y, x + i, y + j);
                    if (!vis[nx][ny]) {
                        vis[nx][ny] = 1;
                        dis[nx][ny] = dis[x][y] + 1;
                        cnt[nx][ny] = nf;
                        Q[++T][0] = nx;
                        Q[T][1] = ny;
                    } else {
                        if ((cnt[nx][ny] + nf) & 1) ans = std::min(ans, dis[x][y] + dis[nx][ny]);
                    }
                }
    }
    printf("%d\n", ans + 1);
    return 0;
}