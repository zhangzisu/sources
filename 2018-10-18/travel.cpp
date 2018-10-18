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
#define MAXN 100010
#define SQRT 320
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int stk[MAXN], stop, top[MAXN], deep[MAXN];
int pa[MAXN][SQRT][18], fa[MAXN], size[MAXN];
void dfs(int x, int len) {
    for (int i = 1; i <= len; i++) stk[++stop] = x;
    size[x] = 1;
    for (int i = 2; i < SQRT; i++) {
        if (stop - i - 1 <= 0) break;
        pa[x][i][0] = stk[stop - i];
        for (int j = 1; j < 18; j++) {
            pa[x][i][j] = pa[pa[x][i][j - 1]][i][j - 1];
            if (!pa[x][i][j]) break;
        }
    }
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i], val[i]);
        size[x] += size[to[i]];
    }
    stop -= len;
}
void split(int x) {
    if (!top[x]) top[x] = x;
    int max = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && size[to[i]] > size[max]) max = to[i];
    if (max) top[max] = top[x], split(max);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != max) split(to[i]);
}
inline int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
        u = fa[top[u]];
    }
    return deep[u] < deep[v] ? u : v;
}
int n, m;
int main() {
    n = $();
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v, w; i < n; i++) u = $(), v = $(), w = $(), $(u, v, w);
    dfs(1, 1);
    split(1);
    m = $();
    for (int u, v, p; m; m--) {
        u = $(), v = $(), p = $();
        int l = lca(u, v);
        if (p >= SQRT) {
            //
        } else {
            //
        }
    }
    return 0;
}