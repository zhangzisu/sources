#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, a[MAXN];
int main() {
#ifndef DEBUG
    freopen("energy.in", "r", stdin);
    freopen("energy.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = n - 1; i; i--) {
        a[i] = std::max(a[i], a[i + 1] + 1);
    }
    printf("%d\n", a[1]);
    return 0;
}