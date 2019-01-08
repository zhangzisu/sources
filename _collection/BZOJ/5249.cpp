#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
int n, d[MAXN], fa[MAXN], last[MAXN], size[MAXN], ans[MAXN];
int min[MAXN << 2], tag[MAXN << 2];
inline void pushUp(int n) { min[n] = std::min(min[n << 1], min[n << 1 | 1]); }
inline void pushDown(int n) {
    if (!tag[n]) return;
    min[n << 1] += tag[n], min[n << 1 | 1] += tag[n];
    tag[n << 1] += tag[n], tag[n << 1 | 1] += tag[n];
    tag[n] = 0;
}
void build(int n, int l, int r) {
    if (l == r) return min[n] = l, void();
    int mid = (l + r) >> 1;
    build(n << 1, l, mid);
    build(n << 1 | 1, mid + 1, r);
    pushUp(n);
}
void add(int n, int l, int r, int L, int R, int v) {
    if (l == L && r == R) return min[n] += v, tag[n] += v, void();
    int mid = (l + r) >> 1;
    pushDown(n);
    if (R <= mid)
        add(n << 1, l, mid, L, R, v);
    else if (L > mid)
        add(n << 1 | 1, mid + 1, r, L, R, v);
    else
        add(n << 1, l, mid, L, mid, v), add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
    pushUp(n);
}
int qry(int n, int l, int r, int x) {
    if (l == r) return min[n] < x ? l + 1 : l;
    int mid = (l + r) >> 1;
    pushDown(n);
    if (min[n << 1 | 1] >= x) return qry(n << 1, l, mid, x);
    return qry(n << 1 | 1, mid + 1, r, x);
}
inline int cmp(int a, int b) { return a > b; }
int main() {
    scanf("%d", &n);
    double ddd;
    scanf("%lf", &ddd);
    for (int i = n; i; i--) scanf("%d", &d[i]), size[fa[i] = (int)floor(i / ddd)] += (size[i] += 1);
    // for (int i = 1; i <= n; i++) printf("NODE %d, level %d, size = %d\n", i, level[i], size[i]);
    std::sort(d + 1, d + n + 1, cmp);
    for (int i = n; i; i--) last[i] = d[i] == d[i + 1] ? last[i + 1] + 1 : 0;
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        if (fa[i] && fa[i] != fa[i - 1]) add(1, 1, n, ans[fa[i]], n, size[fa[i]] - 1);
        ans[i] = qry(1, 1, n, size[i]);
        ans[i] += last[ans[i]];
        last[ans[i]]++;
        ans[i] -= last[ans[i]] - 1;
        add(1, 1, n, ans[i], n, -size[i]);
    }
    for (int i = 1; i <= n; i++) printf("%d%c", d[ans[i]], " \n"[i == n]);
    return 0;
}