#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 410
const int INF = (~0U) >> 1;
int n, k, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int f[MAXN][MAXN], fa[MAXN], ans = INF, rt = 0;
void dp(int x) {
    f[x][0] = 1;
    f[x][1] = 0;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        dp(to[i]);
        for (int j = n; j; j--) {
            f[x][j] = f[x][j] + f[to[i]][0];
            for (int k = 1; k < j; k++) {
                if (f[x][j - k] + f[to[i]][k] < f[x][j]) {
                    f[x][j] = f[x][j - k] + f[to[i]][k];
                }
            }
        }
    }
    ans = std::min(ans, f[x][k] + (x != 1));
}
std::vector<int> g[MAXN][MAXN];
void dp1(int x, int id) {
    f[x][0] = 1;
    f[x][1] = 0;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        dp1(to[i], id);
        for (int j = n; j; j--) {
            f[x][j] = f[x][j] + f[to[i]][0];
            g[x][j].assign(g[to[i]][0].begin(), g[to[i]][0].end());
            for (int k = 1; k < j; k++) {
                if (f[x][j - k] + f[to[i]][k] < f[x][j]) {
                    f[x][j] = f[x][j - k] + f[to[i]][k];
                    g[x][j].clear();
                    g[x][j].assign(g[x][j - k].begin(), g[x][j - k].end());
                    g[x][j].assign(g[to[i]][k].begin(), g[to[i]][k].end());
                }
            }
        }
    }
    g[x][0].push_back(id);
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), $(x, y);
    memset(f, 0x3F, sizeof(f));
    dp(1);
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        if (f[i][k] + (i != 1) == ans) {
            rt = i;
            break;
        }
    int id = -1;
    for (int x = 1; x <= n; x++)
        for (int i = head[x]; ~i; i = next[i])
            if (to[i] != fa[x] && to[i] == rt) id = (i >> 1);
    dp1(rt, id);
    for (auto x : g[rt][k])
        if (~x) printf("%d ", x + 1);
    puts("");
    return 0;
}