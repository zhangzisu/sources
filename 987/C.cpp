#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXN 3010
int n, a[MAXN], b[MAXN], ans = 0x3F3F3F3F;

int f[MAXN][3];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);

    a[0] = 0x80000000;
    memset(f, 0x3F, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 3; j++) {
            for (int k = 0; k < i; k++) {
                if (a[k] >= a[i]) continue;
                f[i][j] = std::min(f[i][j], f[k][j - 1] + b[i]);
            }
        }
    }
    for (int i = 1; i <= n; i++) ans = std::min(ans, f[i][3]);
    printf("%d\n", ans > 300000001 ? -1 : ans);
    return 0;
}