#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1000010
inline int $() {
    register char ch = getchar();
    register int x = 0;
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}

int n, q, c[MAXN], p[MAXN], x, y;
std::vector<int> d[MAXN];
inline bool in(int x, int l, int r) {
    return *std::lower_bound(d[x].begin(), d[x].end(), l) <= r;
}
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
bool vis[MAXN];
std::pair<int, int> G[MAXN];
std::pair<int, std::pair<int, int>> dfs(int x) {
    if (vis[x]) return {x, {x, x}};
    if (G[x].first) return {0, G[x]};
    if (find(x) != x) return dfs(find(x));
    vis[x] = 1;
    int l = x, r = x;
    for (;;) {
        if (l > 1 && in(c[l - 1], l, r)) {
            auto t = dfs(l - 1);
            l = std::min(l, t.second.first);
            r = std::max(r, t.second.second);
            if (t.first && t.first != x) {
                int X = find(t.first), Y = find(x);
                p[Y] = X;
                vis[x] = 0;
                return {t.first, {l, r}};
            }
            continue;
        }
        if (r < n && in(c[r], l, r)) {
            auto t = dfs(r + 1);
            l = std::min(l, t.second.first);
            r = std::max(r, t.second.second);
            if (t.first && t.first != x) {
                int X = find(t.first), Y = find(x);
                p[Y] = X;
                vis[x] = 0;
                return {t.first, {l, r}};
            }
            continue;
        }
        break;
    }
    vis[x] = 0;
    return {0, G[x] = {l, r}};
}

int main() {
    n = $();
    int m = $();
    q = $();
    for (int i = 1; i < n; i++) c[i] = n + 1;
    for (int i = 1; i <= m; i++) {
        x = $(), y = $();
        c[x] = x;
        d[x].push_back(y);
    }
    for (int i = 1; i <= n; i++) d[n + 1].push_back(i);
    for (int i = 1; i <= n + 1; i++) d[i].push_back(n + 1), p[i] = i;

    for (int i = 1; i <= n; i++) dfs(i);
    for (int i = 1; i <= n; i++)
        if (find(i) != i) G[i] = G[find(i)];
    while (q--) {
        x = $(), y = $();
        puts(y >= G[x].first && y <= G[x].second ? "YES" : "NO");
    }
    return 0;
}