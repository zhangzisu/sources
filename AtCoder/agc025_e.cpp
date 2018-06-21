#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 2010
int n, m, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
std::pair<int, int> path[MAXN];
std::vector<int> paths[MAXN], edges[MAXN];
bool dfs(int x, int y, int fa, int id) {
    if (x == y) return 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        if (dfs(to[i], y, x, id)) {
            paths[i >> 1].push_back(id);
            edges[id].push_back(i);
            return 1;
        }
    }
    return 0;
}
int cnt[MAXN], vis[MAXN], have[MAXN << 1];
int main(int argc, char const *argv[]) {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &path[i].first, &path[i].second);
        dfs(path[i].first, path[i].second, 0, i);
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        cnt[i] = paths[i].size();
        ans += std::min(2, cnt[i]);
    }
    for (int p, rev;;) {
        for (p = 0; p < n - 1; p++)
            if (cnt[p] == 1 && (have[p << 1] ^ have[p << 1 | 1])) break;
        if (p == n - 1) {
            for (p = 0; p < n - 1; p++)
                if (cnt[p]) break;
            if (p == n - 1) break;
        }
        while (vis[paths[p].back()]) paths[p].pop_back();
        int x = paths[p].back();
        rev = 0;
        for (auto y : edges[x]) {
            if ((y >> 1) == p) {
                if (have[y]) {
                    rev = 1;
                    std::swap(path[x].first, path[x].second);
                }
            }
        }
        for (auto y : edges[x]) {
            have[y ^ rev] = 1;
            cnt[y >> 1]--;
        }
        vis[x] = 1;
    }
    printf("%d\n", ans);
    for (int i = 1; i <= m; i++) printf("%d %d\n", path[i].first, path[i].second);
    return 0;
}
