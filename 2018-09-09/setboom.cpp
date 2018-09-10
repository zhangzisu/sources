#include <algorithm>
#include <cstdio>
int n, k, p, a[20], ans, max, min;
int main() {
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < (1 << n); i++) {
        if (__builtin_popcount(i) == k) {
            int min = 0x3F3F3F3F;
            int max = 0;
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1) {
                    min = std::min(min, a[j]);
                    max = std::max(max, a[j]);
                }
            }
            ans += max;
            ans -= min;
            ::max += max;
            ::min += min;
        }
    }
    printf("%d %d\n", max, min);
    printf("%d\n", ans);
    return n;
}