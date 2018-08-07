#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0, f = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    if (ch == 45) ch = gc(), f = 1;
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
}
#define MAXN 100010

typedef long long lnt;
const lnt INF = (~0ULL) >> 2;
lnt n, m, q, d[MAXN], head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(lnt u, lnt v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
lnt in[MAXN], out[MAXN], fa[MAXN], dfsclk;
void dfs(lnt x) {
    in[x] = ++dfsclk;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        dfs(to[i]);
    }
    out[x] = dfsclk;
}
struct modify_t {
    lnt x, v, t;
} modify[MAXN];
struct query_t {
    lnt x, t;
} query[MAXN];
lnt tag[MAXN][30], vis[MAXN], snt = 0;
inline void fuck(lnt id) {
    if (vis[id]) {
        for (int x = modify[id].x, v = modify[id].v; x && v; x = fa[x], v >>= 1) {
            for (int tmp = v, i = 0; tmp; tmp >>= 1, i++) {
                tag[x][i] -= tmp;
            }
        }
        vis[id] = 0;
    } else {
        for (int x = modify[id].x, v = modify[id].v; x && v; x = fa[x], v >>= 1) {
            for (int tmp = v, i = 0; tmp; tmp >>= 1, i++) {
                tag[x][i] += tmp;
            }
        }
        vis[id] = 1;
    }
}
inline lnt cao(lnt x) {
    lnt ret = 0;
    for (int i = 0, y = 0; i <= 18 && x; i++, x = fa[x]) {
        ret += tag[x][i];
        if (y) ret -= tag[y][i + 1];
        y = x;
    }
    return ret;
}
lnt point[MAXN], tmp[MAXN], kill[MAXN];
void solve(lnt l, lnt r, lnt L, lnt R) {
    if (l > r) return;
    if (L > R) return;
    lnt mid = (l + r) >> 1;
    while (snt < mid) fuck(++snt);
    while (snt > mid) fuck(snt--);
    lnt left = L, right = R;
    for (int i = L; i <= R; i++) {
        lnt ret = cao(point[i]);
        if (ret >= d[point[i]]) {
            tmp[left++] = point[i];
            kill[point[i]] = modify[mid].t;
        } else {
            tmp[right--] = point[i];
        }
    }
    for (int i = L; i <= R; i++) point[i] = tmp[i];
    if (l == r) return;
    solve(l, mid, L, left - 1);
    solve(mid + 1, r, right + 1, R);
}
inline lnt lowbit(lnt x) { return x & -x; }
lnt BIT[MAXN];
inline void add(lnt x) {
    for (; x <= n; x += lowbit(x)) BIT[x]++;
}
inline lnt qry(lnt x) {
    register lnt y = 0;
    for (; x; x -= lowbit(x)) y += BIT[x];
    return y;
}
int main() {
    memset(head, -1, sizeof(head));
    n = $();
    for (int i = 1; i <= n; i++) d[i] = $();
    for (int i = 1; i < n; i++) $($(), $());
    for (int i = 1; i <= n; i++) point[i] = i;
    dfs(1);
    for (int t = $(), T = 0; t; t--) {
        if ($() == 1) {
            modify[++m].t = ++T;
            modify[m].x = $();
            modify[m].v = $();
        } else {
            query[++q].t = T;
            query[q].x = $();
        }
    }
    memset(kill, 0x3F, sizeof(kill));
    solve(1, m, 1, n);
    lnt g = 1;
    for (int i = 1; i <= q; i++) {
        while (g <= n && kill[point[g]] <= query[i].t) add(in[point[g++]]);
        printf("%lld\n", qry(out[query[i].x]) - qry(in[query[i].x] - 1));
    }
    return 0;
}