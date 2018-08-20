#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 100010
#define MAXM 300010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, m, q, p[MAXN], u[MAXM], v[MAXM], c[MAXM];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int fa[MAXN], deep[MAXN], top[MAXN], size[MAXN], dfn[MAXN], dfsclk;
void dfs(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
        size[x] += size[to[i]];
    }
}
void split(int x) {
    dfn[x] = ++dfsclk;
    if (!top[x]) top[x] = x;
    int max = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && size[to[i]] > size[max]) max = to[i];
    if (max) {
        top[max] = top[x];
        split(max);
    }
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != max) split(to[i]);
}
std::vector<int> Val[MAXN];
inline void umax(int& x, int y) {
    if (x < y) x = y;
}
struct gcc_t {
    int key[2][2], val[2][2];
    inline gcc_t() {
        memset(key, 0, sizeof(key));
        memset(val, 0, sizeof(val));
    }
    inline gcc_t& operator=(gcc_t x) {
        memcpy(key, x.key, sizeof(key));
        memcpy(val, x.val, sizeof(val));
        return *this;
    }
    inline gcc_t friend operator+(gcc_t a, gcc_t b) {
        gcc_t c;
        memcpy(c.key[0], a.key[0], sizeof(int) * 2);
        memcpy(c.key[1], b.key[1], sizeof(int) * 2);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int l = 0; l < 2; l++) {
                        umax(c.val[i][l], a.val[i][j] + b.val[k][l] + (a.key[1][j] != b.key[0][k]));
                    }
                }
            }
        }
        return c;
    }
} val[MAXN << 2];
void modify(int n, int l, int r, int p, gcc_t v) {
    if (l == r) return val[n] = v, void();
    int mid = (l + r) >> 1;
    p <= mid ? modify(n << 1, l, mid, p, v) : modify(n << 1 | 1, mid + 1, r, p, v);
    val[n] = val[n << 1] + val[n << 1 | 1];
}
gcc_t query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return val[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(n << 1, l, mid, L, R);
    if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
    return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
inline int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
        u = fa[top[u]];
    }
    return deep[u] < deep[v] ? u : v;
}
std::vector<std::pair<int, int>> rl, rr;
inline void solve() {
    int u = $();
    int v = $();
    if (u == v) return (void)puts("0");
    int l = lca(u, v);
    if (l == u) {
        rr.clear();
        while (top[v] != top[l]) rr.emplace_back(dfn[top[v]], dfn[v]), v = fa[top[v]];
        if (v != l) rr.emplace_back(dfn[l] + 1, dfn[v]);
        std::reverse(rr.begin(), rr.end());
        gcc_t ans = query(1, 1, n, rr.front().first, rr.front().second);
        for (int i = 1; i < (int)rr.size(); i++) ans = ans + query(1, 1, n, rr[i].first, rr[i].second);
        int res = 0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++) umax(res, ans.val[i][j]);
        printf("%d\n", res);
        return;
    }
    if (l == v) {
        rl.clear();
        while (top[u] != top[l]) rl.emplace_back(dfn[top[u]], dfn[u]), u = fa[top[u]];
        if (u != l) rl.emplace_back(dfn[l] + 1, dfn[u]);
        std::reverse(rl.begin(), rl.end());
        gcc_t ans = query(1, 1, n, rl.front().first, rl.front().second);
        for (int i = 1; i < (int)rl.size(); i++) ans = ans + query(1, 1, n, rl[i].first, rl[i].second);
        int res = 0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++) umax(res, ans.val[i][j]);
        printf("%d\n", res);
        return;
    }
    rl.clear();
    while (top[u] != top[l]) rl.emplace_back(dfn[top[u]], dfn[u]), u = fa[top[u]];
    if (u != l) rl.emplace_back(dfn[l] + 1, dfn[u]);
    std::reverse(rl.begin(), rl.end());
    gcc_t ansL = query(1, 1, n, rl.front().first, rl.front().second);
    for (int i = 1; i < (int)rl.size(); i++) ansL = ansL + query(1, 1, n, rl[i].first, rl[i].second);
    rr.clear();
    while (top[v] != top[l]) rr.emplace_back(dfn[top[v]], dfn[v]), v = fa[top[v]];
    if (v != l) rr.emplace_back(dfn[l] + 1, dfn[v]);
    std::reverse(rr.begin(), rr.end());
    gcc_t ansR = query(1, 1, n, rr.front().first, rr.front().second);
    for (int i = 1; i < (int)rr.size(); i++) ansR = ansR + query(1, 1, n, rr[i].first, rr[i].second);
    int ans = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    umax(ans, ansL.val[i][j] + ansR.val[k][l] + (ansL.key[0][i] != ansR.key[0][k]));
                }
            }
        }
    }
    printf("%d\n", ans);
}
int main() {
    memset(head, -1, sizeof(head));
    n = $(), m = $();
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= m; i++) {
        u[i] = $(), v[i] = $(), c[i] = $();
        if (find(u[i]) != find(v[i])) {
            $(u[i], v[i]);
            p[find(u[i])] = find(v[i]);
        }
    }
    dfs(1);
    split(1);
    for (int i = 1; i <= m; i++) {
        if (deep[u[i]] > deep[v[i]]) std::swap(deep[u[i]], deep[v[i]]);
        Val[v[i]].push_back(c[i]);
    }
    for (int i = 2, x = 0; i <= n; i++) {
        std::sort(Val[i].begin(), Val[i].end());
        Val[i].erase(std::unique(Val[i].begin(), Val[i].end()), Val[i].end());
        int count = (int)Val[i].size();
        gcc_t v;
        if (count > 2) {
            v.key[0][0] = v.key[0][1] = v.key[1][0] = v.key[1][1] = --x;
        } else if (count == 2) {
            v.key[0][0] = v.key[1][0] = Val[i][0];
            v.key[0][1] = v.key[1][1] = Val[i][1];
        } else {
            v.key[0][0] = v.key[0][1] = v.key[1][0] = v.key[1][1] = Val[i][0];
        }
        modify(1, 1, n, i, v);
    }
    for (q = $(); q; q--) solve();
    return 0;
}