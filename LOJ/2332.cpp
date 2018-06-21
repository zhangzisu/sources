#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
typedef long long lnt;
inline lnt $() {
    register lnt x = 0, f = 1;
    register char ch = getchar();
    while (!isdigit(ch) && (ch != 45)) ch = getchar();
    if (ch == 45) f = -1, ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f * x;
}
lnt n, q, s, t, diff[MAXN], ans;
inline lnt calc(lnt x) { return -(x >= 0 ? s : t) * x; }
int main() {
    n = $(), q = $(), s = $(), t = $();
    for (lnt i = 1, x, y = $(); i <= n; i++) {
        x = $();
        ans += calc(diff[i] = x - y);
        y = x;
    }

    while (q--) {
        lnt l = $(), r = $(), x = $();
        ans -= calc(diff[l]);
        if (r < n) ans -= calc(diff[r + 1]);
        diff[l] += x;
        if (r < n) diff[r + 1] -= x;
        ans += calc(diff[l]);
        if (r < n) ans += calc(diff[r + 1]);
        printf("%lld\n", ans);
    }
    return 0;
}