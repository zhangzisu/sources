#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
typedef long double ld;
const lnt INFLL = (~0ULL) >> 2;
const int INF = (~0U) >> 2;

lnt n, k, t, x[MAXN], y[MAXN];
inline bool check(lnt mid) {
    for (int i = 1; i <= n; i++) y[i] = x[i] - 2 * i * mid;
    int posL = k, posR = k;
    for (int i = k - 1; i >= 1; i--)
        if (y[i] >= y[posL]) posL = i;
    for (int i = k + 1; i <= n; i++)
        if (y[i] <= y[posR]) posR = i;
    int l = k, r = k;
    while (l != posL || r != posR) {
        int L = l, R = r, flag = 0;
        while (L > posL && y[L - 1] >= y[r])
            if (y[--L] >= y[l]) break;
        if (y[L] >= y[l] && l != L) l = L, flag = 1;
        while (R < posR && y[R + 1] <= y[l])
            if (y[++R] <= y[r]) break;
        if (y[R] <= y[r] && r != R) r = R, flag = 1;
        if (!flag) break;
    }
    if (l != posL || r != posR) return 0;
    l = 1, r = n;
    if (y[l] < y[r]) return 0;
    while (l != posL || r != posR) {
        int L = l, R = r, flag = 0;
        while (L < posL && y[L + 1] >= y[r])
            if (y[++L] >= y[l]) break;
        if (y[L] >= y[l] && l != L) l = L, flag = 1;
        while (R > posR && y[R - 1] <= y[l])
            if (y[--R] <= y[r]) break;
        if (y[R] <= y[r] && r != R) r = R, flag = 1;
        if (!flag) break;
    }
    return l == posL && r == posR;
}
int main() {
    scanf("%lld%lld%lld", &n, &k, &t);
    for (lnt i = 1; i <= n; i++) scanf("%lld", &x[i]);
    lnt l = 0, r = x[n], ans = 0;
    while (l <= r) {
        lnt mid = (l + r) >> 1;
        if (check(mid * t))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}