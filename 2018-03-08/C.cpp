#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 210
#define MAXM 40010
#define INF 0x3F3F3F3F
std::vector<int> next[MAXN], u, v;
int n, m, k;
int vis[MAXN], dis[MAXN], p[MAXN], perfer[MAXN];
void dfs(int x) {
    if (vis[x]) return;
    vis[x] = 1;
    dis[x] = x <= m ? INF >> 1 : 0;
    if (next[x].empty()) return (dis[x] = x <= m ? INF : -INF), void();
    for (int i = 0; i < (int)next[x].size(); i++) {
        int y = next[x][i];
        dfs(y);
        dis[x] = std::min(dis[x], dis[y] + 1);
        if (dis[y] < dis[perfer[x]]) perfer[x] = y;
    }
}

int main() {
    dis[0] = INF + 1;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            scanf("%1d", &x);
            if (x) {
                next[i].push_back(j);
                u.push_back(i);
                v.push_back(j);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i);
    for (int i = 1; i <= k; i++) scanf("%d", &p[i]);
    for (int t = 0;; t++) {
        for (int i = 1; i <= k; i++)
            if (p[i] > m) goto fail;
        return printf("%d\n", t), 0;
    fail:
        for (int i = 1; i <= k; i++) {
            if (next[p[i]].empty()) {
                if (p[i] > m) return puts("-1"), 0;
            } else {
                p[i] = perfer[p[i]];
            }
        }
    }
    return 0;
}