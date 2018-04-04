#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, a[MAXN], b[MAXN], ans, sum;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        b[i] = b[i - 1] + (x ? 0 : a[i]);
        sum += (x ? a[i] : 0);
    }
    for (int i = 1; i <= n - m + 1; i++) {
        if (b[i + m - 1] - b[i - 1] > ans) ans = b[i + m - 1] - b[i - 1];
    }
    printf("%d\n", sum + ans);
    return 0;
}