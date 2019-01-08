#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, a[100010];
long long ans = 0;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    a[0] = a[n + 1] = 0;
    for (int i = 1; i <= n + 1; i++) ans += std::abs(a[i] - a[i - 1]);
    for (int i = 1; i <= n; i++) {
        printf("%lld\n", ans - std::abs(a[i] - a[i - 1]) - std::abs(a[i] - a[i + 1]) + std::abs(a[i - 1] - a[i + 1]));
    }
    return 0;
}