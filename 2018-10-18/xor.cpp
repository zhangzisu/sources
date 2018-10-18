#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int T, n, m, k, a[110], b[110], c[2048], d[3000];
int main() {
    for (scanf("%d", &T); T; T--) {
        for (int i = scanf("%d", &n); i <= n; i++) scanf("%d", a + i);
        for (int i = scanf("%d", &m); i <= m; i++) scanf("%d", b + i);
        memset(c, 0, sizeof(c));
        k = 0;
        for (int i = 1; i <= n; i++) {
            for (int t = 0, j = i; j <= n; j++) {
                t ^= a[j];
                c[t] = std::max(c[t], j - i + 1);
            }
        }
        for (int i = 0; i < 2048; i++)
            if (c[i]) d[++k] = i;
        d[0] = -0x3F3F3F3F;
        d[k + 1] = 0x3F3F3F3F;
        for (int i = 1; i <= m; i++) {
            int p = std::lower_bound(d + 1, d + k + 1, b[i]) - d;
            if (d[p] == b[i]) {
                printf("%d\n", c[b[i]]);
            } else {
                if (d[p] - b[i] < b[i] - d[p - 1]) {
                    printf("%d\n", c[d[p]]);
                } else if (d[p] - b[i] > b[i] - d[p - 1]) {
                    printf("%d\n", c[d[p - 1]]);
                } else {
                    printf("%d\n", std::max(c[d[p - 1]], c[d[p]]));
                }
            }
        }
    }
    return 0;
}