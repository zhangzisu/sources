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
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], limit[MAXN << 1], tot = 0;
inline void $(int u, int v, int w, int l) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, limit[tot] = l, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, limit[tot] = l, head[v] = tot++;
}
int n, f[MAXN][2], F[MAXN][2], g[2], G[2];
inline void up(int &x, int y) {
    if (x > y) x = y;
}
inline void up(int &f, int &F, int v, int V) {
    if (v < f) {
        f = v, F = V;
    } else if (v == f) {
        up(F, V);
    }
}
void dfs(int x, int fa, int type) {
    f[x][0] = 0;
    f[x][1] = 1;
    F[x][0] = 0;
    F[x][1] = 0;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dfs(to[i], x, limit[i] == 2 ? 2 : (val[i] == limit[i]));
        memset(g, 0x3F, sizeof(g));
        memset(G, 0x3F, sizeof(G));
        up(g[0], G[0], f[x][0] + f[to[i]][0], F[x][0] + F[to[i]][0]);
        up(g[0], G[0], f[x][0] + f[to[i]][1], F[x][0] + F[to[i]][1]);
        up(g[0], G[0], f[x][1] + f[to[i]][0], F[x][1] + F[to[i]][0]);
        up(g[0], G[0], f[x][1] + f[to[i]][1] - 1, F[x][1] + F[to[i]][1]);
        up(g[1], G[1], f[x][0] + f[to[i]][1], F[x][0] + F[to[i]][1]);
        up(g[1], G[1], f[x][1] + f[to[i]][0], F[x][1] + F[to[i]][0]);
        up(g[1], G[1], f[x][1] + f[to[i]][1], F[x][1] + F[to[i]][1]);
        memcpy(f[x], g, sizeof(g));
        memcpy(F[x], G, sizeof(G));
    }
    F[x][1]++;
    if (type == 0) {
        f[x][0] = 0x3F3F3F3F;
        F[x][0] = 0x3F3F3F3F;
    } else if (type == 1) {
        f[x][1] = 0x3F3F3F3F;
        F[x][1] = 0x3F3F3F3F;
    }
}
int main() {
    freopen("w.in", "r", stdin);
    freopen("w.out", "w", stdout);
    memset(head, -1, sizeof(head));
    n = $();
    for (int i = 1, u, v, w, l; i < n; i++) u = $(), v = $(), w = $(), l = $(), $(u, v, w, l);
    dfs(1, 0, 2);
    printf("%d %d\n", f[1][0], F[1][0]);
    return 0;
}