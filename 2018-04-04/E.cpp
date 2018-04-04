#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 400010
#define MAXM 5000010
int n, root[MAXN], L[MAXM], R[MAXM], sum[MAXM], tot = 0;
void insert(int &n, int N, int l, int r, int p) {
    n = ++tot;
    L[n] = L[N], R[n] = R[N], sum[n] = sum[N];
    if (l == r) return sum[n]++, void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        insert(L[n], L[N], l, mid, p);
    else
        insert(R[n], R[N], mid + 1, r, p);
    sum[n] = sum[L[n]] + sum[R[n]];
}
int query(int ln, int rn, int l, int r, int _l, int _r) {
    if (l == _l && r == _r) return sum[rn] - sum[ln];
    int mid = (l + r) >> 1;
    if (_r <= mid) return query(L[ln], L[rn], l, mid, _l, _r);
    if (_l > mid) return query(R[ln], R[rn], mid + 1, r, _l, _r);
    return query(L[ln], L[rn], l, mid, _l, mid) + query(R[ln], R[rn], mid + 1, r, mid + 1, _r);
}
int a[MAXN], b[MAXN], m;
inline int val(int x) {
    return std::lower_bound(b + 1, b + m + 1, x) - b;
}
long long ans = 0;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[++m] = a[i], b[++m] = i;
    std::sort(b + 1, b + m + 1);
    m = std::unique(b + 1, b + m + 1) - b - 1;
    for (int i = 1; i <= n; i++) insert(root[i], root[i - 1], 1, m, val(a[i]));
    for (int i = 1; i <= n; i++) {
        int L = i + 1;
        int R = std::min(val(a[i]), n);
        if (L <= R) ans += query(root[L - 1], root[R], 1, m, i, m);
    }
    printf("%lld\n", ans);
    return 0;
}