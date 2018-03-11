#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
inline long long $$() {
    register long long x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 200010
#include <vector>
struct liner_base {
    long long base[61];
    inline liner_base() { memset(base, 0, sizeof(base)); }
    inline liner_base(const liner_base &o) {
        memcpy(base, o.base, sizeof(base));
    }
    inline void insert(long long x) {
        for (int i = 60; i >= 0; i--)
            if ((x >> i) & 1) {
                if (base[i]) {
                    x ^= base[i];
                } else {
                    base[i] = x;
                    break;
                }
            }
    }
    inline void insert(const liner_base &b) {
        for (int i = 0; i <= 60; i++) insert(b.base[i]);
    }
    inline long long max() {
        register long long ans = 0;
        for (register int i = 60; i >= 0; i--)
            if ((ans ^ base[i]) > ans) ans = ans ^ base[i];
        return ans;
    }
} val[MAXN];
int size[MAXN], vis[MAXN], sf[MAXN], head[MAXN], to[MAXN << 1], next[MAXN << 1],
    bel[MAXN], tot = 0, all, root, n = $(), q = $();
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
long long w[MAXN], ans[MAXN];
struct query {
    int u, v, p;
    inline query(int u, int v, int p) : u(u), v(v), p(p) {}
};
std::vector<query> V[MAXN], tmp;
void s(int x, int fa) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i])
        if (!vis[to[i]] && to[i] != fa) s(to[i], x), size[x] += size[to[i]];
}
void g(int x, int fa) {
    sf[x] = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (!vis[to[i]] && to[i] != fa)
            g(to[i], x), sf[x] = std::max(sf[x], size[to[i]]);
    sf[x] = std::max(sf[x], all - size[x]);
    if (sf[x] < sf[root]) root = x;
}
void dfs(int x, int fa, int yy) {
    bel[x] = yy;
    val[x] = liner_base(val[fa]);
    val[x].insert(w[x]);
    for (int i = head[x]; ~i; i = next[i])
        if (!vis[to[i]] && to[i] != fa) dfs(to[i], x, yy);
}
void slove(int x) {
    if (V[x].empty()) return;
    root = 0;
    s(x, 0), g(x, 0), s(root, 0);
    vis[root] = 1;
    val[root] = liner_base();
    val[root].insert(w[root]);
    bel[root] = root;
    for (int i = head[root]; ~i; i = next[i])
        if (!vis[to[i]]) dfs(to[i], root, to[i]);
    tmp.clear();
    for (auto i : V[x]) {
        if (bel[i.u] == bel[i.v]) {
            if (bel[i.u] == x) {
                tmp.push_back(i);
            } else {
                V[bel[i.u]].push_back(i);
            }
        } else {
            liner_base a(val[i.u]);
            a.insert(val[i.v]);
            ans[i.p] = a.max();
        }
    }
    V[x].clear();
    V[x].assign(tmp.begin(), tmp.end());
    for (int i = head[root]; ~i; i = next[i])
        if (!vis[to[i]]) all = size[to[i]], slove(to[i]);
}
int main() {
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) w[i] = $$();
    for (int i = 1; i < n; i++) $($(), $());
    for (int i = 1; i <= q; i++) {
        int u = $(), v = $();
        if (u == v)
            ans[i] = w[u];
        else
            V[1].push_back(query(u, v, i));
    }
    sf[root = 0] = all = n;
    slove(1);
    for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
    return 0;
}