#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
int n, a[MAXN], min, max;
lnt ans, res = (~0ULL) >> 1;
int main() {
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    for (int i = scanf("%d", &n); i <= n; i++) scanf("%d", a + i), min = std::min(min, a[i] = -a[i]);
    for (int i = 1; i <= n; i++) max = std::max(max, a[i] -= min);
    for (int i = 0; i <= 10; i++) {
        ans = 0;
        for (int i = 1; i <= n; i++) {
            int delta = max - a[i];
            ans += delta / 5;
            delta %= 5;
            ans += delta / 2;
            delta %= 2;
            ans += delta;
        }
        res = std::min(res, ans);
        max++;
    }
    printf("%lld\n", res);
    return 0;
}