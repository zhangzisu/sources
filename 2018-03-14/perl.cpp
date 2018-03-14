#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MOD 1000000007

#define $ long
inline $ $ fuck($ $ x, $ $ p) {
    $ $ y = 1;
    while (p) {
        if (p & 1) y = x * y % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return y;
}
$ $ n, m;
inline std::vector<std::pair<$ $, $ $> > fuck($ $ n) {
    std::vector<std::pair<$ $, $ $> > ret;
    for ($ $ i = 2; i * i <= n; i++) {
        if (n % i) continue;
        $ $ cnt = 0;
        while (!(n % i)) cnt++, n /= i;
        ret.push_back({i, cnt});
    }
    if (n != 1) ret.push_back(std::make_pair(n, 1));
    return ret;
}
inline void fuck(std::vector<std::pair<$ $, $ $> > &fucker, std::vector<std::pair<$ $, $ $> > &fucked, $ $ d, $ $ f, $ $ s) {
    if (d == ($ $)fucker.size()) return fucked.push_back({f, s});
    for ($ $ i = 0; i <= fucker[d].second; i++) {
        fuck(fucker, fucked, d + 1, f, s);
        f *= fucker[d].first;
        s *= (i == 0 ? fucker[d].first - 1 : fucker[d].first);
    }
}

inline $ $ gcd($ $ a, $ $ b) { return b ? gcd(b, a % b) : a; }
inline $ $ cao() {
    std::vector<std::pair<$ $, $ $> > _N = fuck(n), _M = fuck(m), N, M;
    fuck(_N, N, 0, 1, 1);
    fuck(_M, M, 0, 1, 1);
    // printf("%lu %lu\n", M.size(), N.size());
    $ $ ret = 0;
    for ($ $ i = 0; i < ($ $)N.size(); i++) {
        for ($ $ j = 0; j < ($ $)M.size(); j++) {
            $ $ _n = N[i].first;
            $ $ _m = M[j].first;
            long long lcm = _n / gcd(_n, _m) * _m;
            long long res = n * m / lcm;
            // printf("FUCK %lld %lld\n", lcm, res);
            $ $ d0 = (lcm / _n) & 1;
            $ $ d1 = (lcm / _m) & 1;
            if (d0 && d1) {
                res -= n / _n + m / _m - 1;
            } else if (d0) {
                res -= n / _n;
            } else if (d1) {
                res -= m / _m;
            }
            // printf("R %d\n", res);
            ret += fuck(2, res) * N[i].second % MOD * M[j].second % MOD;
            if (ret >= MOD) ret -= MOD;
            // printf("%d\n", ret);
        }
    }
    // printf("%d\n", ret);
    return ret * fuck(n * m % MOD, MOD - 2) % MOD;
}
int main() {
    freopen("perl.in" , "r", stdin );
	freopen("perl.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", cao());
    return 0;
}