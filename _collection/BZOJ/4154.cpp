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
#define MAXN 100010
int t, n, q, size[MAXN], dfn[MAXN], deep[MAXN], tim;
int head[MAXN], to[MAXN], next[MAXN], tot;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
void dfs(int x) {
    size[x] = 1;
    dfn[x] = ++tim;
    for (int i = head[x]; ~i; i = next[i]) {
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
        size[x] += size[to[i]];
    }
}
struct node {
    int key[2], min[2], max[2], l, r, dat, tag;
    inline node(int dat = 0, int a = 0, int b = 0) {
        key[0] = min[0] = max[0] = a;
        key[1] = min[1] = max[1] = b;
        this->dat = dat;
        l = r = 0;
    }
} d[MAXN];
inline void pushUp(node &a, const node &b) {
    a.min[0] = std::min(a.min[0], b.min[0]);
    a.max[0] = std::max(a.max[0], b.max[0]);
    a.min[1] = std::min(a.min[1], b.min[1]);
    a.max[1] = std::max(a.max[1], b.max[1]);
}
inline void pushDown(node &a) {
    if (!a.tag) return;
    if (a.l) d[a.l].dat = d[a.l].tag = a.tag;
    if (a.r) d[a.r].dat = d[a.r].tag = a.tag;
    a.tag = 0;
}
int f[MAXN], D, root;
inline int cmp(const int &a, const int &b) { return d[a].key[D] < d[b].key[D]; }
void Build(int &n, int l, int r, int deep) {
    D = deep;
    int mid = (l + r) >> 1;
    std::nth_element(f + l, f + mid, f + r + 1, cmp);
    n = f[mid];
    if (l < mid) Build(d[n].l, l, mid - 1, !deep), pushUp(d[n], d[d[n].l]);
    if (r > mid) Build(d[n].r, mid + 1, r, !deep), pushUp(d[n], d[d[n].r]);
}
void Modify(int n, int l0, int r0, int l1, int r1, int c) {
    if (!n) return;
    if (d[n].max[0] < l0 || d[n].min[0] > r0 || d[n].max[1] < l1 ||
        d[n].min[1] > r1)
        return;
    pushDown(d[n]);
    if (d[n].max[0] <= r0 && d[n].min[0] >= l0 && d[n].max[1] <= r1 &&
        d[n].min[1] >= l1) {
        d[n].dat = d[n].tag = c;
        return;
    }
    if (d[n].key[0] >= l0 && d[n].key[0] <= r0 && d[n].key[1] >= l1 &&
        d[n].key[1] <= r1)
        d[n].dat = c;
    Modify(d[n].l, l0, r0, l1, r1, c);
    Modify(d[n].r, l0, r0, l1, r1, c);
}
int Query(int n, int v0, int v1, int deep) {
    if (!n) return -1;
    if (d[n].max[0] < v0 || d[n].min[0] > v0 || d[n].max[1] < v1 ||
        d[n].min[1] > v1)
        return -1;
    if (d[n].key[0] == v0 && d[n].key[1] == v1) return d[n].dat;
    pushDown(d[n]);
    if (deep) {
        if (v1 < d[n].key[1])
            return Query(d[n].l, v0, v1, !deep);
        else if (v1 > d[n].key[1])
            return Query(d[n].r, v0, v1, !deep);
        else {
            int l = Query(d[n].l, v0, v1, !deep);
            if (~l) return l;
            return Query(d[n].r, v0, v1, !deep);
        }
    } else {
        if (v0 < d[n].key[0])
            return Query(d[n].l, v0, v1, !deep);
        else if (v0 > d[n].key[0])
            return Query(d[n].r, v0, v1, !deep);
        else {
            int l = Query(d[n].l, v0, v1, !deep);
            if (~l) return l;
            return Query(d[n].r, v0, v1, !deep);
        }
    }
}
long long ans;
int main() {
    t = $();
    while (t--) {
        tot = tim = ans = 0;
        memset(head, -1, sizeof(head));
        n = $();
        $();
        q = $();
        for (int i = 2; i <= n; i++) $($(), i);
        dfs(1);
        for (int i = 1; i <= n; i++) d[i] = node(1, dfn[i], deep[i]), f[i] = i;
        Build(root, 1, n, 0);
        for (int i = 1; i <= q; i++) {
            int a = $(), l = $(), c = $();
            if (c) {
                Modify(root, dfn[a], dfn[a] + size[a] - 1, deep[a], deep[a] + l,
                       c);
            } else {
                (ans += ((long long)Query(root, dfn[a], deep[a], 0) * i)) %=
                    1000000007;
                // printf("OUTPUT::%d\n", Query(root, dfn[a], deep[a], 0));
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}