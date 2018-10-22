#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2, _5[64];
int _0;
inline char gc() {
    if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
    return _3 == _1 + _0 ? 0 : *_3++;
}
inline void pc(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void rt() {
    fwrite(_2, 1, _4 - _2, stdout);
    exit(0);
}
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
    for (_6 = 0; x; x /= 10) _5[++_6] = (x % 10) ^ 48;
    while (_6) pc(_5[_6--]);
}
inline void $(long long x) {
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = (x % 10) ^ 48;
    while (_6) pc(_5[_6--]);
}
inline void $(const char *s) {
    for (; *s; s++) pc(*s);
}
#define MAXN 100010
int t, n, m, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int size[MAXN], deep[MAXN], fa[MAXN], top[MAXN];
void pre(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        pre(to[i]);
        size[x] += size[to[i]];
    }
}
void split(int x) {
    if (!~top[x]) top[x] = x;
    int max = -1;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && (!~max || size[to[i]] > size[max])) max = to[i];
    if (~max) top[max] = top[x], split(max);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != max) split(to[i]);
}
inline int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
        x = fa[top[x]];
    }
    return deep[x] < deep[y] ? x : y;
}
inline int on(int x, int y, int z) {
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
        if (top[z] == top[x] && deep[z] <= deep[x]) return 1;
        x = fa[top[x]];
    }
    if (deep[x] < deep[y]) std::swap(x, y);
    return top[z] == top[x] && deep[z] <= deep[x] && deep[z] >= deep[y];
}
int main() {
    freopen("railway.in", "r", stdin);
    freopen("railway.out", "w", stdout);
    for (t = $(); t; t--) {
        n = $(), m = $();
        memset(head, -1, sizeof(head));
        memset(top, -1, sizeof(top));
        tot = 0;
        for (int i = 1; i < n; i++) $($(), $());
        pre(1), split(1);
        for (int x1, y1, x2, y2; m; m--) {
            x1 = $(), y1 = $(), x2 = $(), y2 = $();
            $(on(x1, y1, lca(x2, y2)) || on(x2, y2, lca(x1, y1)) ? "YES\n" : "NO\n");
        }
    }
    rt();
}