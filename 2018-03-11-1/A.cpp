#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50010
int n, m, k, q;
namespace SLOVE1 {
int sum[MAXN << 2], val[MAXN];
inline void build(int n, int l, int r) {
    if (l == r) return sum[n] = val[l], void();
    int mid = (l + r) >> 1;
    build(n << 1, l, mid);
    build(n << 1 | 1, mid + 1, r);
    sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
inline int query(int n, int l, int r, int L, int R) {
    if (L > R) return 0;
    if (l == L && r == R) return sum[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return query(n << 1, l, mid, L, R);
    if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
    return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
int x1, x2, y1, y2;
inline int main(int n, int k, int q) {
    for (int i = 1; i < n; i++) scanf("%d", &val[i]);
    build(1, 1, n - 1);
    while (q--) {
        scanf("%d", &x1);
        if (x1 == 1) {
            scanf("%d%d%d%d%*d", &x1, &y1, &x2, &y2);
            printf("%d\n", query(1, 1, n - 1, x1, x2 - 1));
        } else {
            scanf("%*d%*d");
            puts("1");
        }
    }
}
}  // namespace SLOVE1

namespace SLOVE2 {
const int INF = 0x3F3F3F3F;
struct martix {
    int $12, $13, $14, $23, $24, $34;
} val[MAXN << 2], org[MAXN];
int hds[2][MAXN], vds[MAXN];
// 1-2 1-2
// | | | |
// 3-4 3-4
inline int _(int a, int b) { return a < b ? a : b; }
inline martix Merge(const martix &a, const martix &b) {
    martix ret{INF, INF, INF, INF, INF, INF};
    ret.$13 = _(a.$13, a.$12 + b.$13 + a.$34);
    ret.$24 = _(b.$24, b.$12 + a.$24 + b.$34);

    ret.$12 = _(ret.$12, a.$12 + b.$12);
    ret.$14 = _(ret.$14, a.$12 + b.$14);
    ret.$23 = _(ret.$23, a.$23 + b.$12);
    ret.$34 = _(ret.$34, a.$23 + b.$14);

    ret.$12 = _(ret.$12, a.$14 + b.$23);
    ret.$14 = _(ret.$14, a.$14 + b.$34);
    ret.$23 = _(ret.$23, a.$34 + b.$23);
    ret.$34 = _(ret.$34, a.$34 + b.$34);

    return ret;
}
void Build(int n, int l, int r) {
    if (l == r) {
        val[n] = {
            hds[0][l],
            vds[l],
            _(hds[0][l]+vds[l+1],hds[1][l]+vds[l]),
            _(hds[0][l]+vds[l],hds[1][l]+vds[l+1]),
            vds[l+1],
            hds[1][l]
        };
        return;
    }
    int mid = (l + r) >> 1;
    Build(n << 1, l, mid);
    Build(n << 1 | 1, mid + 1, r);
    val[n] = Merge(val[n << 1], val[n << 1 | 1]);
}
martix Query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) return val[n];
    int mid = (l + r) >> 1;
    if (R <= mid) return Query(n << 1, l, mid, L, R);
    if (L > mid) return Query(n << 1 | 1, mid + 1, r, L, R);
    return Merge(Query(n << 1, l, mid, L, mid), Query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
int x1, x2, y1, y2;
inline int main(int n, int k, int q) {
    for(int i = 1;i <= n;i++)scanf("%d", &vds[i]);
    for(int i = 1;i < n;i++)scanf("%d", &hds[0][i]);
    for(int i = 1;i < n;i++)scanf("%d", &hds[1][i]);
    Build(1, 1, n - 1);
    while (q--) {
        scanf("%d", &x1);
        if (x1 == 1) {
            scanf("%d%d%d%d%*d", &x1, &y1, &x2, &y2);
            printf("%d\n", Query(1, 1, n - 1, x1, x2 - 1));
        } else {
            scanf("%*d%*d");
            puts("1");
        }
    }
    return 0;
}

inline int main(int n, int k, int q) {
    return 0;
}
}  // namespace SLOVE2
namespace SLOVE3 {
inline int main(int n, int k, int q) {
    return 0;
}
}  // namespace SLOVE3
int main() {
    scanf("%d%d%d%d", &m, &n, &k, &q);
    if (m == 1) return SLOVE1::main(n, k, q);
    if (m == 2) return SLOVE2::main(n, k, q);
    if (m == 3) return SLOVE3::main(n, k, q);
    return puts("WTF???"), 0;
}