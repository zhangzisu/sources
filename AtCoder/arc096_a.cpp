#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int a, b, c, x, y;
long long ans = 0, res = 0;
int main() {
    scanf("%d%d%d%d%d", &a, &b, &c, &x, &y);
    res = 2LL * c * std::max(x, y);
    if (x > y) {
        ans += 1LL * (x - y) * a;
        x = y;
    }
    if (x < y) {
        ans += 1LL * (y - x) * b;
        y = x;
    }
    ans += std::min(2LL * x * c, 1LL * (a + b) * x);
    printf("%lld\n", std::min(ans, res));
    return 0;
}