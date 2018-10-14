#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m, a[100010];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    while (m--) {
        int l, r, k, ans = 0;
        scanf("%d%d%d", &l, &r, &k);
        for (int i = l; i <= r; i++) ans = std::max(ans, a[i] % k);
        printf("%d\n", ans);
    }
}