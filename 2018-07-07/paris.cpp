#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
typedef long long lnt;
inline lnt fuck(lnt x, lnt p) {
    lnt y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
lnt n, m;
inline lnt get(lnt val, lnt x, lnt y) {
    return (val >> (x * m + y)) & 1;
}
inline bool ok(lnt x) {
    for (lnt i = 0; i < n; i++) {
        lnt tmp = 0;
        for (lnt j = 0; j < m; j++) {
            tmp ^= get(x, i, j);
        }
        if (tmp) return 0;
    }
    for (lnt i = 0; i < m; i++) {
        lnt tmp = 0;
        for (lnt j = 0; j < n; j++) {
            tmp ^= get(x, j, i);
        }
        if (tmp) return 0;
    }
    return 1;
}
inline lnt offset(lnt val, lnt x, lnt y) {
    lnt tmp = 0;
    for (lnt i = 0; i < n; i++) {
        for (lnt j = 0; j < m; j++) {
            lnt dx = (i + x) % n;
            lnt dy = (j + y) % m;
            tmp |= get(val, i, j) << (dx * m + dy);
        }
    }
    return tmp;
}
lnt vis[1 << 16], ans;
int main() {
    freopen("paris.in", "r", stdin);
    freopen("paris.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    if (n * m <= 16) {
        for (lnt d = 0; d < 1 << (n * m); d++) {
            if (ok(d)) {
                if (vis[d]) continue;
                for (lnt i = 0; i < n; i++) {
                    for (lnt j = 0; j < m; j++) {
                        vis[offset(d, i, j)] = 1;
                    }
                }
                ans++;
            }
        }
        printf("%lld\n", ans);
        return 0;
    }
    if ((n & 1) && (m & 1)) {
        printf("%lld\n", fuck(n * m % MOD, MOD - 2) * (fuck(2, (n - 1) * (m - 1)) + (n * m - 1)) % MOD);
        return 0;
    }
    // for (lnt d = 0; d < 1 << (n * m); d++) {
    //     if (vis[d]) {
    //         printf(" > %d\n", d);
    //         for (lnt i = 0; i < n; i++) {
    //             for (lnt j = 0; j < m; j++) printf("%1d", get(d, i, j));
    //             puts("");
    //         }
    //     }
    // }
    return 0;
}