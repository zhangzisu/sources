#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define MAXN 10000010
typedef long long lnt;
lnt n, a, b, k;
int frc[MAXN], inv[MAXN];
int main() {
    scanf("%lld%lld%lld%lld", &n, &a, &b, &k);
    for (lnt i = 0; i <= n; i++) {
        lnt rest = k - 1LL * i * a;
        if (rest % b) continue;
        lnt j = rest / b;
        lnt max = std::min(i, j);
        if (i + j - max > n) continue;
        lnt min = std::max(i + j - n, 0LL);
        for(lnt k = min;k <= max;k++){
            //
        }
    }
    return 0;
}