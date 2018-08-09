#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 510
int n, k, a[MAXN], f[MAXN][MAXN];
int main(int argc, char const *argv[]) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    std::sort(a + 1, a + n + 1);
    memset(f, 0x3F, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int l = 0; l < i; l++) {
                f[i][j] = std::min(f[i][j], f[l][j - 1] + (a[i] - a[l + 1]) * (a[i] - a[l + 1]));
            }
        }
    }
    printf("%d\n", f[n][k]);
    return 0;
}
