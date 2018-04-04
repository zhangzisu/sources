#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
int n, m, a[MAXN], x, ans = 0x3F3F3F3F;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d", &x), a[x]++;
    for (int i = 1; i <= n; i++) ans = std::min(ans, a[i]);
    printf("%d\n", ans);
    return 0;
}