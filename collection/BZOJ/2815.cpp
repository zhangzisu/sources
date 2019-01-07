#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 70000
std::vector<int> next[MAXN], pre[MAXN], tr[MAXN];
int n, x, d[MAXN], fa[MAXN][18], deep[MAXN], size[MAXN];
std::queue<int> Q;
inline int LCA(int x, int y) {
    if (deep[x] < deep[y]) std::swap(x, y);
    int delta = deep[x] - deep[y];
    for (int i = 0; i < 18; i++)
        if ((delta >> i) & 1) x = fa[x][i];
    for (int i = 17; i >= 0; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return x == y ? x : fa[x][0];
}
void dfs(int x) {
    size[x] = 1;
    for (std::vector<int>::iterator it = tr[x].begin(); it != tr[x].end(); it++)
        dfs(*it), size[x] += size[*it];
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (scanf("%d", &x); x != 0; scanf("%d", &x)) {
            next[x].push_back(i);
            pre[i].push_back(x);
        }
        if (pre[i].empty()) next[n + 1].push_back(i), pre[i].push_back(n + 1);
        d[i] = pre[i].size();
    }
    Q.push(n + 1);
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        int lca = 0;
        for (std::vector<int>::iterator it = pre[x].begin(); it != pre[x].end();
             it++) {
            lca = lca ? LCA(lca, *it) : *it;
        }
        tr[lca].push_back(x);
        deep[x] = deep[fa[x][0] = lca] + 1;
        for (int d = 1; d < 18; d++) fa[x][d] = fa[fa[x][d - 1]][d - 1];
        for (std::vector<int>::iterator it = next[x].begin();
             it != next[x].end(); it++)
            if (!--d[*it]) Q.push(*it);
    }
    dfs(n + 1);
    for (int i = 1; i <= n; i++) printf("%d\n", size[i] - 1);
    return 0;
}