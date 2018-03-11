#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
struct node {
    int l, r, sum;
    inline node() : l(0), r(0), sum(0) {}
} p[MAXN << 6];
int root[MAXN], cnt, n, m;
inline void Insert(int &n, int N, int l, int r, int v) {
    p[n = ++cnt] = p[N];
    if (l == r) {
        p[n].sum++;
        return;
    }
    int mid = (l + r) >> 1;
    if (v <= mid)
        Insert(p[n].l, p[N].l, l, mid, v);
    else if (v > mid)
        Insert(p[n].r, p[N].r, mid + 1, r, v);
    p[n].sum = p[p[n].l].sum + p[p[n].r].sum;
}
inline int Query(int n, int l, int r, int L, int R) {
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
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        Insert(root[i], root[i - 1], 1, MAXN, x + 1);
    }
    while (m--) {
        int b, d, l, r, now = 0, ans = 0;
        scanf("%d%d%d%d", &b, &d, &l, &r);
        for (int i = 20; i >= 0; i--) {
            int x = 1 << i;
            if (b & x) {
                if (Query(root[r], 1, MAXN, now - d + 1, now + x - d) -
                    Query(root[l - 1], 1, MAXN, now - d + 1, now + x - d)) {
                    ans |= x;
                } else {
                    now |= x;
                }
            } else {
                if (Query(root[r], 1, MAXN, now - d + x + 1, now - d + x + x) -
                    Query(root[l - 1], 1, MAXN, now - d + x + 1,
                          now - d + x + x)) {
                    ans |= x;
                    now |= x;
                }
            }
        }
        printf("%d\n", ans);
    }
}