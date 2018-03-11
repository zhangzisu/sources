#include <algorithm>
#include <cstdio>
#define MAXN 1010
int r[MAXN], c[MAXN], n, ans = -1;
char buf[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf + 1);
        for (int j = 1; j <= n; j++) {
            if (buf[j] == '#') r[i]++, c[j]++, ans = MAXN;
        }
    }
    if (!~ans) return puts("-1"), 0;
    for (int i = 1; i <= n; i++) ans = std::min(ans, n - r[i] + (c[i] == 0));
    for (int i = 1; i <= n; i++) ans += (c[i] != n);
    printf("%d\n", ans);
    return 0;
}