#include <algorithm>
#include <cstdio>
#define MAXN 50
int n, m, l[MAXN], r[MAXN], a[MAXN], b[MAXN], c[MAXN], ans, tmp[MAXN];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d%d", l + i, r + i);
    for (int i = 1; i <= m; i++) scanf("%d%d%d", a + i, b + i, c + i);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = std::max(ans, (std::min(r[i], b[j]) - std::max(l[i], a[j])) * c[j]);
            tmp[j] = std::max(tmp[j], (std::min(r[i], b[j]) - std::max(l[i], a[j])) * c[j]);
        }
    }
    printf("%d\n", ans);
    for (int i = 1; i <= m; i++) printf("%d: %d\n", i, tmp[i]);
}