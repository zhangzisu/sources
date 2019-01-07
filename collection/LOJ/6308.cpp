#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m;
long long sum[MAXN << 2], max[MAXN << 2], a[MAXN];
void build(int n, int l, int r) {
    if (l == r) return sum[n] = max[n] = a[l], void();
    int mid = (l + r) >> 1;
    build(n << 1, l, mid);
    build(n << 1 | 1, mid + 1, r);
    sum[n] = sum[n << 1] + sum[n << 1 | 1];
    max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
long long query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return sum[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(n << 1, l, mid, L, R);
    if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
    return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
void modify(int n, int l, int r, int L, int R, long long v) {
    if (max[n] < v) return;
    if (l == r) return sum[n] %= v, max[n] %= v, void();
    int mid = (l + r) >> 1;
    if (R <= mid)
        modify(n << 1, l, mid, L, R, v);
    else if (L > mid)
        modify(n << 1 | 1, mid + 1, r, L, R, v);
    else
        modify(n << 1, l, mid, L, mid, v), modify(n << 1 | 1, mid + 1, r, mid + 1, R, v);
    sum[n] = sum[n << 1] + sum[n << 1 | 1];
    max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
void replace(int n, int l, int r, int p, long long v) {
    if (l == r) return sum[n] = max[n] = v, void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        replace(n << 1, l, mid, p, v);
    else
        replace(n << 1 | 1, mid + 1, r, p, v);
    sum[n] = sum[n << 1] + sum[n << 1 | 1];
    max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    build(1, 1, n);
    while (m--) {
        int l, r;
        long long x;
        scanf("%d", &l);
        if (l == 1) {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(1, 1, n, l, r));
        } else if (l == 2) {
            scanf("%d%d%lld", &l, &r, &x);
            modify(1, 1, n, l, r, x);
        } else {
            scanf("%d%lld", &l, &x);
            replace(1, 1, n, l, x);
        }
    }
    return 0;
}