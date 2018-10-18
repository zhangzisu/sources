#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
#define MAXN 200010
#define SQRT 350
#define LOGN 20
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int fa[MAXN][LOGN], deep[MAXN], son[MAXN], n;
int pa[MAXN][LOGN], stk[MAXN], stp = 0;
void dfs(int x) {
    for (int i = 1; i < LOGN; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
        if (!fa[x][i]) break;
    }
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        fa[to[i]][0] = x;
        deep[to[i]] = deep[x] + 1;
        son[x] = to[i];
        dfs(to[i]);
    }
}
void pre(int x, int b) {
    stk[++stp] = x;
    if (x <= n) {
        if (stp - b > 0) {
            pa[x][0] = stk[stp - b] <= n ? stk[stp - b] : son[stk[stp - b]];
            for (int i = 1; i < LOGN; i++) {
                pa[x][i] = pa[pa[x][i - 1]][i - 1];
            }
        } else {
            memset(pa[x], 0, sizeof(pa[x]));
        }
    }
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x][0]) continue;
        pre(to[i], b);
    }
    --stp;
}
inline int lca(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    int delta = deep[u] - deep[v];
    for (int i = LOGN - 1; ~i; i--)
        if ((delta >> i) & 1) u = fa[u][i];
    if (u == v) return u;
    for (int i = LOGN - 1; ~i; i--)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
inline int kfa(int u, int k) {
    for (int i = LOGN - 1; ~i; i--)
        if ((k >> i) & 1) u = fa[u][i];
    return u;
}
int m, k, tmp1[MAXN], tmp2[MAXN], ans[MAXN];
struct query_t {
    int u, v, w, id;
    inline int friend operator<(const query_t& a, const query_t& b) {
        return a.w < b.w;
    }
} query[MAXN];
int main() {
    k = n = $();
    memset(head, -1, sizeof(head));
    for (int i = n - 1, u, v, w; i; i--) {
        u = $(), v = $(), w = $();
        if (w == 1) {
            $(u, v);
        } else {
            ++k, $(u, k), $(v, k);
        }
    }
    deep[1] = 1, dfs(1);
    m = $();
    for (int i = 1; i <= m; i++) query[i].u = $(), query[i].v = $(), query[i].w = $(), query[i].id = i;
    std::sort(query + 1, query + m + 1);
    for (int i = 1, last = 0; i <= m; i++) {
        int &u = query[i].u, &v = query[i].v, &p = query[i].w;
        int l = lca(u, v), res = 0;
        if (p < SQRT) {
            if (last != p) pre(1, p);
            last = p;
            for (int i = LOGN - 1; ~i; i--) {
                if (deep[pa[u][i]] > deep[l]) {
                    res += 1 << i;
                    u = pa[u][i];
                }
                if (deep[pa[v][i]] > deep[l]) {
                    res += 1 << i;
                    v = pa[v][i];
                }
            }
        } else {
            for (int x = kfa(u, p); deep[x] >= deep[l]; u = (x <= n ? x : son[x]), x = kfa(u, p)) res++;
            for (int x = kfa(v, p); deep[x] >= deep[l]; v = (x <= n ? x : son[x]), x = kfa(v, p)) res++;
        }
        int rest = deep[u] + deep[v] - deep[l] * 2;
        if (rest) ++res;
        if (rest > p) ++res;
        ans[query[i].id] = res;
    }
    for (int i = 1; i <= m; i++) $(ans[i]), pc(10);
    rt();
}