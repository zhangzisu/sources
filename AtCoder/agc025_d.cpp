#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 610
int n, d[2], vis[2][MAXN][MAXN], col[2][MAXN][MAXN];
std::vector<std::pair<int, int>> V[2];
inline int ok(int x, int y) { return x >= 0 && x < n && y >= 0 && y < n; }
void dfs(int x, int y, int c, int d) {
    col[d][x][y] = c;
    vis[d][x][y] = 1;
    for (auto v : V[d]) {
        int nx = x + v.first;
        int ny = y + v.second;
        if (ok(nx, ny) && !vis[d][nx][ny]) {
            dfs(nx, ny, !c, d);
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &d[0], &d[1]);
    n <<= 1;
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i <= d[k]; i++) {
            int j = (int)sqrt(d[k] - i * i);
            if (i * i + j * j == d[k]) {
                V[k].push_back({i, j});
                V[k].push_back({-i, j});
                V[k].push_back({i, -j});
                V[k].push_back({-i, -j});
            }
        }
        std::sort(V[k].begin(), V[k].end());
        V[k].erase(unique(V[k].begin(), V[k].end()), V[k].end());
    }
    for (int k = 0; k < 2; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!vis[k][i][j]) dfs(i, j, 0, k);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (col[0][i][j] == 0 && col[1][i][j] == 0) {
                printf("%d %d\n", i, j);
                if (++cnt >= (n * n / 4)) return 0;
            }
        }
    }
    return 0;
}