#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
struct node {
    int l, r, sum;
    inline node() : l(0), r(0), sum(0) {}
} p[MAXN * 200];
int root[MAXN], tot = 0, n, q, a[MAXN];
inline void Modify(int &n, int l, int r, int pos, int val) {
    if (!n) n = ++tot;
    if (l == r) {
        p[n].sum += val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        Modify(p[n].l, l, mid, pos, val);
    else
        Modify(p[n].r, mid + 1, r, pos, val);
    p[n].sum = p[p[n].l].sum + p[p[n].r].sum;
}
inline int Query(int &n, int l, int r, int L, int R) {
    if (!n) return 0;
    if (l == L && r == R) return p[n].sum;
    int mid = (l + r) >> 1;
    if (R <= mid)
        return Query(p[n].l, l, mid, L, R);
    else if (L > mid)
        return Query(p[n].r, mid + 1, r, L, R);
    else
        return Query(p[n].l, l, mid, L, mid) +
               Query(p[n].r, mid + 1, r, mid + 1, R);
}
inline int lowbit(int x) { return x & -x; }
inline void modify(int p, int num, int val) {
    while (p <= n) {
        Modify(root[p], 1, n, num, val);
        p += lowbit(p);
    }
}
inline int query(int p, int l, int r) {
    register int ret = 0;
    while (p) {
        ret += Query(root[p], 1, n, l, r);
        p -= lowbit(p);
    }
    return ret;
}
long long ans = 0;
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        a[i] = i;
        ans += query(i, a[i] + 1, n);
        modify(i, a[i], 1);
    }
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        ans -= query(l, a[l] + 1, n) + query(n, 1, a[l] - 1) -
               query(l, 1, a[l] - 1);
        modify(l, a[l], -1);
        ans -= query(r, a[r] + 1, n) + query(n, 1, a[r] - 1) -
               query(r, 1, a[r] - 1);
        modify(r, a[r], -1);
        std::swap(a[l], a[r]);
        modify(l, a[l], 1);
        ans += query(l, a[l] + 1, n) + query(n, 1, a[l] - 1) -
               query(l, 1, a[l] - 1);
        modify(r, a[r], 1);
        ans += query(r, a[r] + 1, n) + query(n, 1, a[r] - 1) -
               query(r, 1, a[r] - 1);
        printf("%lld\n", ans);
    }
    return 0;
}