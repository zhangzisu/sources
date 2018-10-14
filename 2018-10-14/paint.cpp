#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <set>
#define MAXN 50
typedef int arr[MAXN][MAXN];
int n, m, cnt, ans, x[MAXN * MAXN], y[MAXN * MAXN];
arr g, id, vis;
void init(int x, int y, int z) {
    id[x][y] = z;
    if (x > 0 && g[x - 1][y] == g[x][y] && !id[x - 1][y]) init(x - 1, y, z);
    if (x < n - 1 && g[x + 1][y] == g[x][y] && !id[x + 1][y]) init(x + 1, y, z);
    if (y > 0 && g[x][y - 1] == g[x][y] && !id[x][y - 1]) init(x, y - 1, z);
    if (y < m - 1 && g[x][y + 1] == g[x][y] && !id[x][y + 1]) init(x, y + 1, z);
}
int head[MAXN * MAXN], next[MAXN * MAXN * MAXN * MAXN], to[MAXN * MAXN * MAXN * MAXN], tot = 0;
inline void $(int u, int v) { next[tot] = head[u], to[tot] = v, head[u] = tot++; }
std::set<int> S;
void dfs(int x, int y, int z) {
    if (vis[x][y]) return;
    vis[x][y] = 1;
    if (x > 0) {
        id[x - 1][y] == z ? dfs(x - 1, y, z) : (void)S.insert(id[x - 1][y]);
    }
    if (x < n - 1) {
        id[x + 1][y] == z ? dfs(x + 1, y, z) : (void)S.insert(id[x + 1][y]);
    }
    if (y > 0) {
        id[x][y - 1] == z ? dfs(x, y - 1, z) : (void)S.insert(id[x][y - 1]);
    }
    if (y < m - 1) {
        id[x][y + 1] == z ? dfs(x, y + 1, z) : (void)S.insert(id[x][y + 1]);
    }
}
int dis[MAXN * MAXN];
std::queue<int> Q;
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%1d", &g[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!id[i][j]) {
                init(i, j, ++cnt);
                x[cnt] = i;
                y[cnt] = j;
            }
        }
    }
    for (int i = 1; i <= cnt; i++) {
        S.clear();
        dfs(x[i], y[i], i);
        for (auto j : S) $(i, j);
    }
    int ans = 0x3F3F3F3F;
    for (int i = 1; i <= cnt; i++) {
        memset(dis, -1, sizeof(dis));
        dis[i] = 0;
        Q.push(i);
        int tmp = 0;
        while (Q.size()) {
            int u = Q.front();
            Q.pop();
            tmp = std::max(tmp, dis[u] + g[x[u]][y[u]]);
            for (int i = head[u]; ~i; i = next[i]) {
                if (dis[to[i]] != -1) continue;
                dis[to[i]] = dis[u] + 1;
                Q.push(to[i]);
            }
        }
        ans = std::min(ans, tmp);
    }
    printf("%d\n", ans);
    return 0;
}