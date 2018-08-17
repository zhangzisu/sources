#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MAXM 5000010
typedef long long lnt;
int n, m, q, b[MAXN], a[MAXN], v[MAXN], root[MAXN], L[MAXM], R[MAXM], sum[MAXM], all;
inline void insert(int &n, int m, int l, int r, int p) {
    n = ++all;
    L[n] = L[m], R[n] = R[m], sum[n] = sum[m] + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    p <= mid ? insert(L[n], L[m], l, mid, p) : insert(R[n], R[m], mid + 1, r, p);
}
inline int query(int n, int m, int l, int r, int _l, int _r) {
    if (_l > _r) return 0;
    if (l == _l && r == _r) return sum[n] - sum[m];
    int mid = (l + r) >> 1;
    if (_r <= mid) return query(L[n], L[m], l, mid, _l, _r);
    if (_l > mid) return query(R[n], R[m], mid + 1, r, _l, _r);
    return query(L[n], L[m], l, mid, _l, mid) + query(R[n], R[m], mid + 1, r, mid + 1, _r);
}
inline int lowbit(int x) { return x & -x; }
lnt ans = 0, tmp;
int main() {
    freopen("inversions.in", "r", stdin);
    freopen("inversions.out", "w", stdout);
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), v[++m] = a[i];
    std::sort(v + 1, v + m + 1);
    m = std::unique(v + 1, v + m + 1) - v - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = std::lower_bound(v + 1, v + m + 1, a[i]) - v;
        insert(root[i], root[i - 1], 1, m, a[i]);
        for (int x = a[i] + 1; x <= m; x += lowbit(x)) ans += b[x];
        for (int x = a[i]; x >= 1; x -= lowbit(x)) b[x]++;
    }
    for (int x, y; q; q--) {
        scanf("%d%d", &x, &y);
        if (x > y) std::swap(x, y);
        if (x == y) {
            printf("%lld\n", ans);
        } else {
            tmp = ans;
            tmp -= query(root[y - 1], root[x], 1, m, 1, a[x] - 1);
            tmp -= query(root[y - 1], root[x], 1, m, a[y] + 1, m);
            tmp += query(root[y - 1], root[x], 1, m, a[x] + 1, m);
            tmp += query(root[y - 1], root[x], 1, m, 1, a[y] - 1);
            if (a[x] > a[y]) tmp--;
            if (a[x] < a[y]) tmp++;
            printf("%lld\n", tmp);
        }
    }
    return 0;
}