#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 401
const int INF = (~0U) >> 1;
int n, k, f[MAXN][MAXN], fa[MAXN], id[MAXN][MAXN];
short g[MAXN][MAXN][MAXN];
std::vector<int> next[MAXN];
void dp(int x) {
    f[x][0] = 1;
    f[x][1] = 0;
    for (int y : next[x]) {
        if (y == fa[x]) continue;
        fa[y] = x;
        dp(y);
        for (int j = n; j; j--) {
            f[x][j] = f[x][j] + f[y][0];
            for (int k = 1; k < j; k++) {
                if (f[x][j - k] + f[y][k] < f[x][j]) {
                    f[x][j] = f[x][j - k] + f[y][k];
                    g[x][y][j] = k;
                }
            }
        }
    }
}
void out(int x, int k) {
    std::reverse(next[x].begin(), next[x].end());
    for (int y : next[x]) {
        if (y == fa[x]) continue;
        if (g[x][y][k])
            out(y, g[x][y][k]);
        else
            printf("%d ", id[x][y]);
        k -= g[x][y][k];
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y);
        id[x][y] = id[y][x] = i;
        next[x].push_back(y);
        next[y].push_back(x);
    }
    memset(f, 0x3F, sizeof(f));
    dp(1);
    int ans = f[1][k], rt = 1;
    for (int i = 2; i <= n; i++)
        if (f[i][k] + 1 < ans) ans = f[i][k] + 1, rt = i;
    printf("%d\n", ans);
    if (rt != 1) printf("%d ", id[rt][fa[rt]]);
    out(rt, k);
    puts("");
    return 0;
}