#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 353448299
typedef long long lnt;
lnt n, a, b, t, ans;

inline lnt ddd(lnt x, lnt p) {
    lnt ret = 1;
    while (p) {
        if (p & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return ret;
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        t = 1, ans = 0;
        scanf("%lld%lld%lld", &n, &a, &b);
        if (n <= 100000) {
            __int128 real = 0, rest = 1;
            for (int i = 0; i <= n; i++) {
                real += rest / b;
                rest = rest % b;
                real %= MOD;
                (ans += real) %= MOD;
                real = real * (a % MOD);
                real %= MOD;
                rest *= a;
            }
            printf("%lld\n", ans);
        } else if (a == b - 1) {
            
        } else {
            //
        }
    }
    return 0;
}