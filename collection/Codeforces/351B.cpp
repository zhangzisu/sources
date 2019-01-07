#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 3010
int n, m, a[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (a[j] < a[i]) m++;
    printf("%f\n", 1. * (m >> 1) * 4 + (m & 1));
    return 0;
}