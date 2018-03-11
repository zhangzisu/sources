#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 500010
std::map<int, int> M, W;

int n, m, q;
int h[MAXN], f[MAXN];
inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
struct Modify {
    int u, v, w;
    inline friend bool operator<(const Modify &a, const Modify &b) {
        return a.w < b.w;
    }
} a[MAXN];
struct Query {
    int v, x, k, d;
    inline friend bool operator<(const Query &a, const Query &b) {
        return a.x < b.x;
    }
} b[MAXN];
struct node {
    int l, r, s;
    inline node() : l(0), r(0), s(0) {}
} p[MAXN << 2];
int root[MAXN], cnt = 0;
inline void build(int &n, int l, int r, int v) {
    n = ++cnt;
    if (l == r) return void(p[n].s = 1);
    int mid = (l + r) >> 1;
    if (v <= mid)
        build(p[n].l, l, mid, v);
    else
        build(p[n].r, mid + 1, r, v);
    p[n].s = 1;
}
inline void Merge(int &n1, int &n2, int l, int r) {
    if (!n2) return;
    if (!n1) return void(n1 = n2);
    if (l == r) return void(p[n1].s += p[n2].s);
    int mid = (l + r) >> 1;
    Merge(p[n1].l, p[n2].l, l, mid);
    Merge(p[n1].r, p[n2].r, mid + 1, r);
    p[n1].s = p[p[n1].l].s + p[p[n1].r].s;
}
inline int Ask(int n, int l, int r, int v) {
    if (!n || p[n].s < v) return -1;
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (p[p[n].r].s >= v) return Ask(p[n].r, mid + 1, r, v);
    return Ask(p[n].l, l, mid, v - p[p[n].r].s);
}

int ans[MAXN];
int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
        M[h[i]] = 1;
    }
    int tp = 0;
    for (std::map<int, int>::iterator it = M.begin(); it != M.end(); it++) W[it->second = ++tp] = it->first;
    W[-1] = -1;
    for (int i = 1; i <= n; i++) build(root[f[i] = i], 1, n, h[i] = M[h[i]]);
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    std::sort(a + 1, a + m + 1);
    for (int i = 1; i <= q; i++) scanf("%d%d%d", &b[i].v, &b[i].x, &b[i].k), b[i].d = i;
    std::sort(b + 1, b + q + 1);
    tp = 1;
    for (int i = 1; i <= q; i++) {
        while (tp <= m && a[tp].w <= b[i].x) {
            int U = find(a[tp].u), V = find(a[tp].v);
            if (U != V) {
                f[U] = V;
                Merge(root[V], root[U], 1, n);
            }
            tp++;
        }
        ans[b[i].d] = Ask(root[find(b[i].v)], 1, n, b[i].k);
    }
    for (int i = 1; i <= q; i++) printf("%d\n", W[ans[i]]);
}