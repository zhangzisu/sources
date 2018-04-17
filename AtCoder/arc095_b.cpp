#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, ans, a[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    std::sort(a + 1, a + n + 1);
    m = a[n] >> 1;
    ans = -1;
    int pos = std::lower_bound(a + 1, a + n, m) - a;
    if (pos < n && std::abs(a[pos] - m) < std::abs(ans - m)) ans = a[pos];
    pos--;
    if (pos > 0 && std::abs(a[pos] - m) < std::abs(ans - m)) ans = a[pos];
    printf("%d %d\n", a[n], ans);
    return 0;
}