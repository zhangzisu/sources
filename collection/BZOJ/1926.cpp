#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define GET(x, x1, y1, x2, y2, k) \
    (x[x2][y2][k] - x[x1 - 1][y2][k] - x[x2][y1 - 1][k] + x[x1 - 1][y1 - 1][k])
namespace s1 {
const int MAXN = 210;
int sum[MAXN][MAXN][1010], cnt[MAXN][MAXN][1010];
int main(int r, int c, int m) {
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++) {
            int x = $();
            for (int k = 0; k <= 1003; k++) {
                sum[i][j][k] =
                    sum[i - 1][j][k] + sum[i][j - 1][k] - sum[i - 1][j - 1][k];
                cnt[i][j][k] =
                    cnt[i - 1][j][k] + cnt[i][j - 1][k] - cnt[i - 1][j - 1][k];
                sum[i][j][k] += x >= k ? x : 0;
                cnt[i][j][k] += x >= k;
            }
        }
    while (m--) {
        int x1 = $(), y1 = $(), x2 = $(), y2 = $(), h = $();
        register int l = 1, r = 1003, ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int s0 = GET(sum, x1, y1, x2, y2, mid - 1);
            int s1 = GET(sum, x1, y1, x2, y2, mid);
            if (s1 >= h)
                ans = GET(cnt, x1, y1, x2, y2, mid), l = mid + 1;
            else if (s0 < h)
                r = mid - 1;
            else {
                ans = GET(cnt, x1, y1, x2, y2, mid);
                ans += (h - s1 - 1) / (mid - 1) + 1;
                l = mid + 1;
            }
        }
        if (!~ans)
            puts("Poor QLW");
        else
            printf("%d\n", ans);
    }
    return 0;
}
}  // namespace s1
namespace s2 {
const int MAXN = 500010;
int root[MAXN], cnt = 0, L[MAXN << 4], R[MAXN << 4];
int val[MAXN << 4], sum[MAXN << 4];
inline void pushUp(int n) {
    val[n] = sum[n] = 0;
    if (L[n]) val[n] += val[L[n]], sum[n] += sum[L[n]];
    if (R[n]) val[n] += val[R[n]], sum[n] += sum[R[n]];
}
inline void Copy(int n, int m) {
    L[n] = L[m], R[n] = R[m], val[n] = val[m], sum[n] = sum[m];
}
void Insert(int &n, int m, int l, int r, int p, int v) {
    Copy(n = ++cnt, m);
    if (l == r) return val[n]++, sum[n] += v, void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        Insert(L[n], L[m], l, mid, p, v);
    else
        Insert(R[n], R[m], mid + 1, r, p, v);
    pushUp(n);
}
int Query(int n, int m, int l, int r, int v) {
    if (l == r) {
        return (v - 1) / l + 1;
    }
    int mid = (l + r) >> 1;
    if (v <= sum[R[m]] - sum[R[n]]) return Query(R[n], R[m], mid + 1, r, v);
    return val[R[m]] - val[R[n]] +
           Query(L[n], L[m], l, mid, v - sum[R[m]] + sum[R[n]]);
}
int main(int n, int m) {
    for (int i = 1; i <= n; i++) {
        int x = $();
        Insert(root[i], root[i - 1], 1, 1003, x, x);
    }
    while (m--) {
        int x, y, h;
        $(), x = $();
        $(), y = $();
        h = $();
        if (sum[root[y]] - sum[root[x - 1]] < h)
            puts("Poor QLW");
        else
            printf("%d\n", Query(root[x - 1], root[y], 1, 1003, h));
    }
    return 0;
}
}  // namespace s2
int main() {
    int r = $(), c = $(), m = $();
    if (r != 1) return s1::main(r, c, m);
    return s2::main(c, m);
}