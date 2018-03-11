#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
long long val[MAXN << 1], f[MAXN], p[MAXN], q[MAXN], l[MAXN], d[MAXN];
inline void $(int u, int v, long long w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int n, fa[MAXN], size[MAXN], sf[MAXN], vis[MAXN], root, all;
void ddd(int x, int fa) {
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa) d[to[i]] = d[x] + val[i], ddd(to[i], x);
}
void G(int x, int fa) {
    size[x] = 1, sf[x] = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (!vis[to[i]] && to[i] != fa)
            G(to[i], x), size[x] += size[to[i]],
                sf[x] = std::max(sf[x], size[to[i]]);
    sf[x] = std::max(sf[x], all - size[x]);
    if (sf[x] < sf[root]) root = x;
}
void S(int x, int fa) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i])
        if (!vis[to[i]] && to[i] != fa) S(to[i], x), size[x] += size[to[i]];
}
int stk[MAXN], top, cvx[MAXN], cvt;
void D(int x, int fa) {
    stk[++top] = x;
    for (int i = head[x]; ~i; i = next[i])
        if (!vis[to[i]] && to[i] != fa) D(to[i], x);
}
inline int cmp(const int &u, const int &v) { return d[u] - l[u] > d[v] - l[v]; }
inline double slope(int i, int j) {
    return (double)(f[i] - f[j]) / (d[i] - d[j]);
}
void slove(int x, int source) {
    vis[x] = 1;
    S(x, 0);
    if (!vis[fa[x]])
        root = 0, all = size[fa[x]], G(fa[x], 0), slove(root, source);
    top = cvt = 0;
    D(x, fa[x]);
    std::sort(stk + 1, stk + top + 1, cmp);
    for (int i = 1, u = fa[x]; i <= top; i++) {
        while (u != fa[source] && d[stk[i]] - l[stk[i]] <= d[u]) {
            while (cvt > 1 &&
                   slope(cvx[cvt - 1], cvx[cvt]) <= slope(cvx[cvt], u))
                cvt--;
            cvx[++cvt] = u;
            u = fa[u];
        }
        if (!cvt) continue;
        register int l = 1, r = cvt;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (slope(cvx[mid], cvx[mid + 1]) < p[stk[i]])
                r = mid;
            else
                l = mid + 1;
        }
        f[stk[i]] = std::min(
            f[stk[i]],
            f[cvx[l]] + (d[stk[i]] - d[cvx[l]]) * p[stk[i]] + q[stk[i]]);
    }
    for (int i = 1; i <= top; i++)
        if (stk[i] != x && d[stk[i]] - l[stk[i]] <= d[x])
            f[stk[i]] = std::min(
                f[stk[i]], f[x] + (d[stk[i]] - d[x]) * p[stk[i]] + q[stk[i]]);
    for (int i = head[x]; ~i; i = next[i]) {
        if (!vis[to[i]] && to[i] != fa[x])
            root = 0, all = size[to[i]], G(to[i], 0), slove(root, to[i]);
    }
}
int main() {
    scanf("%d%*d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 2; i <= n; i++) {
        long long x;
        scanf("%d%lld", &fa[i], &x);
        $(fa[i], i, x);
        scanf("%lld%lld%lld", &p[i], &q[i], &l[i]);
    }
    ddd(1, 0);
    memset(f, 0x3F, sizeof(f));
    f[0] = f[1] = 0;
    vis[0] = 1;
    sf[root = 0] = n + 1;
    all = n;
    G(1, 0);
    slove(root, 1);
    for (int i = 2; i <= n; i++) printf("%lld\n", f[i]);
    return 0;
}