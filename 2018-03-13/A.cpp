#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010

int n, q, l[MAXN], r[MAXN];
namespace dier {
int m, d[MAXN];
inline int main() {
    while (q--) {
        scanf("%d", &m);
        memset(d, 0, sizeof(d));
        for (int i = 1, x; i <= m; i++) scanf("%d", &x), d[x]++;
        for (int i = 1; i <= n; i++) d[i] += d[i - 1];
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += (d[r[i]] - d[l[i] - 1]) & 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
}  // namespace dier
namespace fucker {
struct node {
    int l, r, max[2], min[2], val[2], pa, tag, sum, cnt;
    inline node(int a = 0, int b = 0) {
        max[0] = min[0] = val[0] = a;
        max[1] = min[1] = val[1] = b;
        tag = 0, sum = 0, cnt = 1, pa = 0;
    }
} p[MAXN << 1];
inline void pushUp(node &a, node &b) {
    for (int i = 0; i < 2; i++) {
        a.max[i] = std::max(a.max[i], b.max[i]);
        a.min[i] = std::min(a.min[i], b.min[i]);
    }
    a.sum += b.sum;
    a.cnt += b.cnt;
}
inline void pushDown(int n) {
    const int L = p[n].l, R = p[n].r;
    if (p[n].tag) {
        p[L].sum = p[L].cnt - p[L].sum;
        p[R].sum = p[R].cnt - p[R].sum;
        p[L].tag ^= 1, p[L].pa ^= 1;
        p[R].tag ^= 1, p[R].pa ^= 1;
        p[n].tag = 0;
    }
}
int f[MAXN], root;
int D;
inline int cmp(const int &a, const int &b) {
    return p[a].val[D] < p[b].val[D];
}
void Build(int &n, int l, int r, int d) {
    int mid = (l + r) >> 1;
    D = d;
    std::nth_element(f + l, f + mid, f + r + 1, cmp);
    n = f[mid];
    if (l < mid) Build(p[n].l, l, mid - 1, d ^ 1), pushUp(p[n], p[p[n].l]);
    if (r > mid) Build(p[n].r, mid + 1, r, d ^ 1), pushUp(p[n], p[p[n].r]);
}
inline bool in(int x, int l, int r) {
    return x >= l && x <= r;
}
void rev(int n, int l0, int l1, int r0, int r1) {
    pushDown(n);
    if (p[n].max[0] <= l1 && p[n].min[0] >= l0 && p[n].max[1] <= r1 && p[n].min[1] >= r0) {
        p[n].sum = p[n].cnt - p[n].sum;
        p[n].tag ^= 1, p[n].pa ^= 1;
        return;
    }
    if (p[n].max[0] < l0 || p[n].min[0] > l1 || p[n].max[1] < r0 || p[n].min[1] > r1) return;
    if (in(p[n].val[0], l0, l1) && in(p[n].val[1], r0, r1)) p[n].pa ^= 1;
    p[n].sum = p[n].pa, p[n].cnt = 1;
    if (p[n].l) rev(p[n].l, l0, l1, r0, r1), pushUp(p[n], p[p[n].l]);
    if (p[n].r) rev(p[n].r, l0, l1, r0, r1), pushUp(p[n], p[p[n].r]);
}
int a[MAXN], m;
inline int main() {
    for (int i = 1; i <= n; i++) p[i] = node(l[i], r[i]), f[i] = i;
    Build(root, 1, n, 0);
    while (q--) {
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= m; i++) rev(root, 1, a[i], a[i], n);
        printf("%d\n", p[root].sum);
        for (int i = 1; i <= m; i++) rev(root, 1, a[i], a[i], n);
    }
    return 0;
}
}  // namespace fucker
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]);
    scanf("%d", &q);
    if (q <= 200) return dier::main();
    return fucker::main();
}