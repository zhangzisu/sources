#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m;
long long x;
int main() {
    scanf("%d%d", &n, &m);
    x = 1900 * m + 100 * (n - m);
    for (int i = 1; i <= m; i++) x = x * 2;
    printf("%lld\n", x);
    return 0;
}