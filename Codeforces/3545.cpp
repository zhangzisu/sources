#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MAXM 500010
int n, rn, m, q, h[MAXN], g[MAXN], p[MAXN], dat[MAXM], N;
inline int GetCGC(int x) { return std::upper_bound(dat + 1, dat + N + 1, x) - dat - 1; }
inline int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
struct edge {
    int u, v, w;
    inline friend bool operator<(const edge &a, const edge &b) { return a.w < b.w; }
} e[MAXM];
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) { next[tot] = head[u], to[tot] = v, head[u] = tot++; }
int fsa[MAXN], fsb[MAXN], fa[MAXN][22], dfsclk;
int root[MAXN], L[5000010], R[5000010], sum[5000010], cnt = 0;
inline void copy(int x, int y) { L[x] = L[y], R[x] = R[y], sum[x] = sum[y]; }
void insert(int &n, int N, int l, int r, int v) {
    copy(n = ++cnt, N);
    if (l == r) return sum[n]++, void();
    int mid = (l + r) >> 1;
    if (v <= mid)
        insert(L[n], L[N], l, mid, v);
    else
        insert(R[n], R[N], mid + 1, r, v);
    sum[n] = sum[L[n]] + sum[R[n]];
}
int query(int n0, int n1, int l, int r, int k) {
    if (l == r) return l;
    int now = sum[R[n0]] - sum[R[n1]], mid = (l + r) >> 1;
    if (now >= k) return query(R[n0], R[n1], mid + 1, r, k);
    return query(L[n0], L[n1], l, mid, k - now);
}
void dfs(int x) {
    fsa[x] = ++dfsclk;
    root[dfsclk] = root[dfsclk - 1];
    if (x <= rn) insert(root[dfsclk], root[dfsclk - 1], 1, rn, GetCGC(h[x]));
    for (int i = head[x]; ~i; i = next[i]) fa[to[i]][0] = x, dfs(to[i]);
    fsb[x] = dfsclk;
}
int query(int x, int v, int k) {
    for (int d = 21; ~d; d--)
        if (g[fa[x][d]] <= v) x = fa[x][d];
    int last = root[fsb[x]], pre = root[fsa[x] - 1];
    if (sum[last] - sum[pre] < k) return 0;
    return query(last, pre, 1, rn, k);
}
int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &n, &m, &q), rn = n;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]), dat[++N] = h[i];
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    std::sort(e + 1, e + m + 1);
    std::sort(dat + 1, dat + N + 1);
    N = std::unique(dat + 1, dat + N + 1) - dat - 1;
    dat[0] = -1;
    for (int i = 1; i < MAXN; i++) p[i] = i;
    for (int i = 1; i <= m; i++) {
        int U = find(e[i].u), V = find(e[i].v);
        if (U == V) continue;
        int now = ++n;
        p[U] = p[V] = now;
        $(now, U), $(now, V);
        g[now] = e[i].w;
    }
    for (int i = 1; i <= n; i++)
        if (!fsa[i]) dfs(fa[find(i)][0] = find(i));
    for (int d = 1; d < 22; d++)
        for (int i = 1; i <= n; i++)
            fa[i][d] = fa[fa[i][d - 1]][d - 1];
    while (q--) {
        int v, x, k;
        scanf("%d%d%d", &x, &v, &k);
        printf("%d\n", dat[query(x, v, k)]);
    }
    return 0;
}