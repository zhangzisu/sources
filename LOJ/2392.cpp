#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
typedef long double ld;

lnt n, k, t, x[MAXN];
inline bool dd(lnt mid) {
    return (x[k] - x[1] <= mid * t) && (x[n] - x[k - 1] <= mid * t * 2);
}
inline bool DD(lnt mid) {
    return (x[n] - x[k] <= mid * t) && (x[k + 1] - x[1] <= mid * t * 2);
}
int main() {
    scanf("%lld%lld%lld", &n, &k, &t);
    for (lnt i = 1; i <= n; i++) scanf("%lld", &x[i]);
    if (k == 1 || k == n) {
        printf("%lld\n", (lnt)(ceil(.5 * (x[n] - x[1]) / t)));
        return 0;
    }
    lnt l = 0, r = 1000000000, ans = -1;
    while (l <= r) {
        lnt mid = (l + r) >> 1;
        if (dd(mid * 2) || DD(mid * 2))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}