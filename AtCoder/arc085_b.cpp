#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, a[2010], w;
int main() {
    scanf("%d%*d%d", &n, &w);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    if (n == 1)
        printf("%d\n", std::abs(w - a[n]));
    else
        printf("%d\n", std::max(std::abs(w - a[n]), std::abs(a[n - 1] - a[n])));
    return 0;
}