#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, L[MAXN], R[MAXN], stk[MAXN], top;
int st[MAXN][17], BLOCK, _2[MAXN];
long long sl[MAXN], sr[MAXN], res[MAXN], a[MAXN];
struct Query {
    int l, r, id;
    inline Query(int l = 0, int r = 0, int id = 0) : l(l), r(r), id(id) {}
    inline friend bool operator<(const Query& a, const Query& b) {
        return a.l / BLOCK == b.l / BLOCK ? a.r < b.r : a.l < b.l;
    }
} q[MAXN];
inline int qmin(int l, int r) {
    int d = _2[r - l + 1];
    return a[st[l][d]] < a[st[r - (1 << d) + 1][d]] ? st[l][d]
                                                    : st[r - (1 << d) + 1][d];
}
int main() {
    scanf("%d%d", &n, &m);
    _2[1] = 0;
    for (int i = 2; i <= n; i++) _2[i] = _2[i >> 1] + 1;
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), st[i][0] = i;
    stk[top = 0] = 0;
    a[0] = 0x7FFFFFFF;
    for (int i = 1; i <= n; i++) {
        while (top && a[stk[top]] > a[i]) R[stk[top--]] = i;
        L[i] = stk[top];
        stk[++top] = i;
    }
    while (top) R[stk[top--]] = n + 1;
    for (int d = 1; d < 17; d++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1 << (d - 1)) <= n) {
                st[i][d] = a[st[i][d - 1]] < a[st[i + (1 << (d - 1))][d - 1]]
                               ? st[i][d - 1]
                               : st[i + (1 << (d - 1))][d - 1];
            }
        }
    }
    for (int i = 1; i <= n; i++) sl[i] = sl[L[i]] + a[i] * (i - L[i]);
    for (int i = n; i >= 1; i--) sr[i] = sr[R[i]] + a[i] * (R[i] - i);
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = Query(l, r, i);
    }
    BLOCK = sqrt(n);
    std::sort(q + 1, q + 1 + m);
    register int l = 1, r = 0;
    register long long ans = 0;
    for (int i = 1; i <= m; i++) {
        while (r < q[i].r) {
            r++;
            int min = qmin(l, r);
            ans += sl[r] - sl[min] + a[min] * (min - l + 1);
        }
        while (l > q[i].l) {
            l--;
            int min = qmin(l, r);
            ans += sr[l] - sr[min] + a[min] * (r - min + 1);
        }
        while (l < q[i].l) {
            int min = qmin(l, r);
            ans -= sr[l] - sr[min] + a[min] * (r - min + 1);
            l++;
        }
        while (r > q[i].r) {
            int min = qmin(l, r);
            ans -= sl[r] - sl[min] + a[min] * (min - l + 1);
            r--;
        }
        res[q[i].id] = ans;
    }
    for (int i = 1; i <= m; i++) printf("%lld\n", res[i]);
    return 0;
}