#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int min[MAXN << 2], R[MAXN << 2], F[MAXN << 2], G[MAXN << 2];
inline void set(int x, int a, int b) {
    if (min[x] >= a) {
        min[x] = b;
        F[x] = b;
        if (!G[x]) G[x] = a;
    }
}
inline void update(int &x, int &y, int &z) {
    if (z > x)
        y = x, x = z;
    else if (z < x && z > y)
        y = z;
}

inline void pushUp(int x) {
    min[x] = R[x] = -1 << 30;
    update(min[x], R[x], min[x << 1]);
    update(min[x], R[x], R[x << 1]);
    update(min[x], R[x], min[x << 1 | 1]);
    update(min[x], R[x], R[x << 1 | 1]);
}
inline void pushDown(int x) {
    if (F[x]) {
        set(x << 1, G[x], F[x]);
        set(x << 1 | 1, G[x], F[x]);
        F[x] = 0;
        G[x] = 0;
    }
}

inline void build(int x, int l, int r) {
    if (l == r) {
        min[x] = l;
        R[x] = -1 << 30;
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    pushUp(x);
}

inline void modify(int x, int l, int r, int _l, int _r, int a, int b) {
    if (min[x] < a) return;
    if (_l <= l && r <= _r && R[x] < a) {
        set(x, a, b);
        return;
    }
    pushDown(x);
    int mid = (l + r) >> 1;
    if (_l <= mid) modify(x << 1, l, mid, _l, _r, a, b);
    if (_r > mid) modify(x << 1 | 1, mid + 1, r, _l, _r, a, b);
    pushUp(x);
}
inline int Query(int x, int l, int r, int t) {
    if (l == r) return min[x];
    pushDown(x);
    int mid = (l + r) >> 1;
    if (t <= mid)
        return Query(x << 1, l, mid, t);
    else
        return Query(x << 1 | 1, mid + 1, r, t);
}

int n, m, q, left[MAXN], ans[MAXN];
struct query {
    int l, r, id;
    inline friend bool operator<(const query &a, const query &b) {
        return a.r < b.r;
    }
} Q[MAXN];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, l, r; i <= m; i++) scanf("%d%d", &l, &r), left[r] = l;
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) scanf("%d%d", &Q[i].l, &Q[i].r), Q[i].id = i;
    std::sort(Q + 1, Q + q + 1);
    build(1, 1, n);
    for (int i = 1, cur = 1; i <= n; i++) {
        if (left[i])
            modify(1, 1, n, 1, left[i], left[i], i);
        while (cur <= q && Q[cur].r == i)
            ans[Q[cur].id] = Query(1, 1, n, Q[cur].l), cur++;
    }
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}