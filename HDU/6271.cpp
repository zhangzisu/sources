#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 10010
#define SQRT 100
int n, m, p[MAXN], size[MAXN], top;
std::pair<int*, int> stk[MAXN << 2];
int find(int x) { return x == p[x] ? x : find(p[x]); }
inline void uni(int x, int y) {
    int u = find(x), v = find(y);
    if (u == v) return;
    if (size[u] < size[v]) std::swap(u, v);
    stk[++top] = {&size[u], size[u]};
    stk[++top] = {&p[v], p[v]};
    size[u] += size[v];
    p[v] = u;
}
inline void fb(int t) {
    while (top > t) {
        auto x = stk[top--];
        (*x.first) = x.second;
    }
}
int ans[MAXN], dfn[MAXN], dep[MAXN], dfsclk = 0;
struct Tree {
    std::vector<int> next[MAXN];
    std::pair<int, int> info[MAXN];
    int fa[MAXN];
} _0, _1;
void ddd(int x, int rt) {
    int top = ::top;
    uni(_1.info[x].first, _1.info[x].second);
    if (!~ans[x] && dfn[rt] <= dfn[x]) {
        int tt = ::top, t = x;
        while (t != rt) uni(_0.info[t].first, _0.info[t].second), t = _0.fa[t];
        ans[x] = m - (::top / 2);
        fb(tt);
    }
    for (auto y : _1.next[x]) ddd(y, rt);
    fb(top);
}
void dfs(int x) {
    int top = ::top;
    uni(_0.info[x].first, _0.info[x].second);
    dfn[x] = ++dfsclk;
    dep[x] = 1;
    for (int y : _0.next[x]) {
        dfs(y);
        dep[x] = std::max(dep[x], dep[y] + 1);
    }
    ans[x] = -1;
    if (x == 1 || dep[x] == SQRT) {
        ddd(1, x);
        dep[x] = 0;
    }
    fb(top);
}
int t;
inline void reset_env() {
    memset(p, 0, sizeof(p));
    memset(size, 0, sizeof(size));
    n = m = top = dfsclk = 0;
    memset(stk, 0, sizeof(stk));
    memset(ans, 0, sizeof(ans));
    memset(dfn, 0, sizeof(dfn));
    memset(dep, 0, sizeof(dep));
}
int main() {
    scanf("%d", &t);
    while (t--) {
        reset_env();
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++) p[i] = i, size[i] = 1;
        for (int i = 1; i <= n; i++) {
            _0.next[i].clear();
            _1.next[i].clear();
        }
        for (int i = 1; i <= n; i++) scanf("%d%d", &_0.info[i].first, &_0.info[i].second);
        for (int i = 1, u, v; i < n; i++) {
            scanf("%d%d", &u, &v);
            _0.next[u].push_back(v);
            _0.fa[v] = u;
        }
        for (int i = 1; i <= n; i++) scanf("%d%d", &_1.info[i].first, &_1.info[i].second);
        for (int i = 1, u, v; i < n; i++) {
            scanf("%d%d", &u, &v);
            _1.next[u].push_back(v);
            _1.fa[v] = u;
        }
        dfs(1);
        for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    }
    return 0;
}