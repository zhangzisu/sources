#include <algorithm>
#include <cctype>
#include <cstdio>
#define $ long
inline $ $ _() {
    register $ $ x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline $ $ gcd($ $ a, $ $ b) {
    return b ? gcd(b, a % b) : a;
}
$ $ m, k;
inline $ $ calc($ $ l, $ $ k) {
    auto d = gcd(k, m);
    if (d == 1 || l <= k / d) return l;
    if ((k + m - 1) / m <= (k - l)) return k / d;
    return m / d * (k - l) + calc((k - m * (k - l)) / d, k / d);
}
int main() {
    register int t = _();
    while (t--) {
        m = _();
        k = _();
        printf("%lld\n", calc(k - 1, k) + 1);
    }
    return 0;
}