#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, a[MAXN], min[MAXN], max[MAXN], f[MAXN], id[MAXN];
int val[MAXN << 2];
void update(int n, int l, int r, int p, int v) {
    if (l == r) return val[n] = std::max(val[n], v), void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        update(n << 1, l, mid, p, v);
    else
        update(n << 1 | 1, mid + 1, r, p, v);
    val[n] = std::max(val[n << 1], val[n << 1 | 1]);
}
void set(int n, int l, int r, int p, int v) {
    if (l == r) return val[n] = v, void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        set(n << 1, l, mid, p, v);
    else
        set(n << 1 | 1, mid + 1, r, p, v);
    val[n] = std::max(val[n << 1], val[n << 1 | 1]);
}
int get(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return val[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return get(n << 1, l, mid, L, R);
    if (L > mid) return get(n << 1 | 1, mid + 1, r, L, R);
    return std::max(get(n << 1, l, mid, L, mid), get(n << 1 | 1, mid + 1, r, mid + 1, R));
}
void CDQ(int l, int r) {
    if (l == r) return f[l] = std::max(f[l], 1), void();
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    for (int i = l; i <= r; i++) id[i] = i;
    std::sort(id + l, id + mid + 1, [](int x, int y) { return max[x] < max[y]; });
    std::sort(id + mid + 1, id + r + 1, [](int x, int y) { return a[x] < a[y]; });
    int cur = l;
    for (int i = mid + 1; i <= r; i++) {
        while (cur <= mid && max[id[cur]] <= a[id[i]]) update(1, 1, n, a[id[cur]], f[id[cur]]), cur++;
        f[id[i]] = std::max(f[id[i]], get(1, 1, n, 1, min[id[i]]) + 1);
    }
    for (int i = l; i <= mid; i++) set(1, 1, n, a[id[i]], 0);
    CDQ(mid + 1, r);
}
int main(int argc, char const *argv[]) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        min[i] = max[i] = a[i];
    }
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);
        min[x] = std::min(min[x], y);
        max[x] = std::max(max[x], y);
    }
    CDQ(1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = std::max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}
