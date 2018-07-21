#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return b ? gcd(b, a % b) : a;
}
int n, m, a[MAXN];
int val[MAXN << 2], tag[MAXN << 2], ans[MAXN << 2];
void build(int n, int l, int r) {
    if (l == r) {
        val[n] = a[l];
        ans[n] = a[l] - a[l - 1];
        return;
    }
    int mid = (l + r) >> 1;
    build(n << 1, l, mid);
    build(n << 1 | 1, mid + 1, r);
    ans[n] = gcd(ans[n << 1], ans[n << 1 | 1]);
}
void modify(int n, int l, int r, int p, int v) {
    if (l == r) {
        ans[n] += v;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(n << 1, l, mid, p, v);
    else
        modify(n << 1 | 1, mid + 1, r, p, v);
    ans[n] = gcd(ans[n << 1], ans[n << 1 | 1]);
}
void add(int n, int l, int r, int L, int R, int v) {
    if (l == L && r == R) {
        tag[n] += v;
        val[n] += v;
        return;
    }
    int mid = (l + r) >> 1;
    if (R <= mid)
        return add(n << 1, l, mid, L, R, v);
    else if (L > mid)
        return add(n << 1 | 1, mid + 1, r, L, R, v);
    add(n << 1, l, mid, L, mid, v);
    add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
}
inline void pushDown(int n) {
    if (tag[n]) {
        tag[n << 1] += tag[n];
        tag[n << 1 | 1] += tag[n];
        val[n << 1] += tag[n];
        val[n << 1 | 1] += tag[n];
        tag[n] = 0;
    }
}
int get(int n, int l, int r, int p) {
    if (l == r) return val[n];
    int mid = (l + r) >> 1;
    pushDown(n);
    if (p <= mid) return get(n << 1, l, mid, p);
    return get(n << 1 | 1, mid + 1, r, p);
}
int query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return ans[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(n << 1, l, mid, L, R);
    if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
    return gcd(query(n << 1, l, mid, L, mid), query(n << 1 | 1, mid + 1, r, mid + 1, R));
}

int main() {
    // freopen("bucket.in", "r", stdin);
    // freopen("bucket.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    build(1, 1, n);
    while (m--) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (l > r) std::swap(l, r);
        if (op == 1) {
            scanf("%d", &op);
            add(1, 1, n, l, r, op);
            modify(1, 1, n, l, op);
            if (r < n) modify(1, 1, n, r + 1, -op);
        } else {
            if (l == r) {
                printf("%d\n", get(1, 1, n, l));
                continue;
            }
            printf("%d\n", gcd(query(1, 1, n, l + 1, r), get(1, 1, n, r)));
        }
    }
    return 0;
}