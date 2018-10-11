#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
int _0, _5[32];
inline char gc() {
    if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
    return _3 == _1 + _0 ? 0 : *_3++;
}
inline void pc(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void rt() { fwrite(_2, 1, _4 - _2, stdout), exit(0); }
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline void $(int x) {
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) pc(_5[_6--] ^ 48);
}
#define MAXN 100010
#define MAXM 1000010
int n, m, q;
int head[MAXN], to[MAXM << 1], next[MAXM << 1], val[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int fa[MAXN], deep[MAXN], dis[MAXN], size[MAXN], top[MAXN];
int bel[MAXN], cis[MAXN], cum[MAXN], low[MAXN], high[MAXN], cir = 0;
void dfs(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        if (!deep[to[i]]) {
            deep[to[i]] = deep[x] + 1;
            dis[to[i]] = dis[x] + val[i];
            fa[to[i]] = x;
            dfs(to[i]);
            size[x] += size[to[i]];
        } else if (deep[to[i]] < deep[x]) {
            ++cir;
            low[cir] = to[i], high[cir] = x, bel[to[i]] = cir;
            for (int y = x; y != to[i]; y = fa[y]) bel[y] = cir, cis[y] = dis[y] - dis[to[i]];
            cum[cir] = dis[x] - dis[to[i]] + val[i];
        }
    }
    if (!bel[x]) {
        low[bel[x] = ++cir] = x;
    }
}
void split(int x) {
    if (!top[x]) top[x] = x;
    int max = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (deep[to[i]] == deep[x] + 1 && size[to[i]] > size[max]) max = to[i];
    if (max) top[max] = top[x], split(max);
    for (int i = head[x]; ~i; i = next[i])
        if (deep[to[i]] == deep[x] + 1 && to[i] != max) split(to[i]);
}
inline int getCirDis(int x, int y) {
    if (cis[x] > cis[y]) std::swap(x, y);
    return std::min(cis[y] - cis[x], cum[bel[x]] - cis[y] + cis[x]);
}
inline int getLCA(int x, int y) {
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
        x = fa[top[x]];
    }
    return deep[x] < deep[y] ? x : y;
}
int main() {
    memset(head, -1, sizeof(head));
    n = $(), m = $(), q = $();
    for (int i = 1, u, v, w; i <= m; i++) u = $(), v = $(), w = $(), $(u, v, w);
    deep[1] = 1, dfs(1), split(1);
    for (int u, v; q; q--) {
        u = $(), v = $();
        if (bel[u] == bel[v]) {
            $(getCirDis(u, v)), pc(10);
        } else {
            int lca = getLCA(high[bel[u]], high[bel[v]]);
            if (bel[lca] == bel[u]) {
                int ans = dis[low[bel[v]]] - dis[lca];
                ans += getCirDis(low[bel[v]], v);
                ans += getCirDis(lca, u);
                $(ans), pc(10);
            } else if (bel[lca] == bel[v]) {
                int ans = dis[low[bel[u]]] - dis[lca];
                ans += getCirDis(low[bel[u]], u);
                ans += getCirDis(lca, v);
                $(ans), pc(10);
            } else {
                int ans = dis[low[bel[u]]] + dis[low[bel[v]]] - 2 * dis[lca];
                ans += getCirDis(low[bel[u]], u);
                ans += getCirDis(low[bel[v]], v);
                $(ans), pc(10);
            }
        }
    }
    rt();
}