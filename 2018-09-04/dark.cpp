#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <set>
#include <vector>
#define MAXN 200010
typedef long long lnt;
int n, m, fa[MAXN], val[MAXN];
lnt f[MAXN], g[MAXN];
int id[MAXN], ban[MAXN], bfsclk;
std::queue<int> Q;
std::vector<int> next[MAXN];
inline void change(int x) {
    if (ban[x]) {
        ban[x] = 0;
        g[fa[x]] -= f[x];
        f[x] = std::max(g[x] + val[x], 0LL);
        g[fa[x]] += f[x];
        for (x = fa[x]; x && !ban[x]; x = fa[x]) {
            g[fa[x]] -= f[x];
            f[x] = std::max(g[x] + val[x], 0LL);
            g[fa[x]] += f[x];
        }
    } else {
        ban[x] = 1;
        g[fa[x]] -= f[x];
        f[x] = 0;
        g[fa[x]] += f[x];
        for (x = fa[x]; x && !ban[x]; x = fa[x]) {
            g[fa[x]] -= f[x];
            f[x] = std::max(g[x] + val[x], 0LL);
            g[fa[x]] += f[x];
        }
    }
}
lnt pre[MAXN];
std::set<int> s;
int main() {
    freopen("dark.in", "r", stdin);
    freopen("dark.out", "w", stdout);
    scanf("%d%d", &n, &m);
    bool flag = 1;
    for (int i = 2; i <= n; i++) {
        scanf("%d", &fa[i]);
        next[fa[i]].push_back(i);
        flag &= fa[i] == i - 1;
    }
    Q.push(1);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        id[++bfsclk] = x;
        for (int i = 0; i < (int)next[x].size(); i++) Q.push(next[x][i]);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]), f[i] = val[i];
    if (flag) {
        for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + val[i];
        for (int i = 1; i <= n; i++) pre[i] = std::max(pre[i - 1], pre[i]);
        s.insert(n + 1);
        for (int x; m; m--) {
            scanf("%d", &x);
            s.count(x) ? (void)s.erase(x) : (void)s.insert(x);
            printf("%lld\n", pre[*s.begin() - 1]);
        }
        return 0;
    }
    for (int i = n; i >= 1; i--) {
        f[i] = std::max(g[i] + val[i], 0LL);
        if (fa[i]) g[fa[i]] += f[i];
    }
    for (int x; m; m--) scanf("%d", &x), change(x), printf("%lld\n", f[1]);
    return 0;
}
