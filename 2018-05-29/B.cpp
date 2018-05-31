#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define MAXN 20
int n, m, qu, ans = 0x80000000, val[1 << MAXN];
inline void FMT(int *f) {
    for (int i = 0; i < n; i++) {
        int l = 1 << i;
        for (int j = 0; j < m; j += (l << 1)) {
            for (int k = 0; k < l; k++) {
                f[j + k + l] += f[j + k];
            }
        }
    }
}
int main() {
    scanf("%d", &n);
    m = 1 << n;
    for (int i = 0; i < m; i++) scanf("%d", &val[i]);
    FMT(val);
    for (int x = 0; x < m; x++) {
        int res = val[x];
        if (res > ans) {
            ans = res;
            qu = x;
        }
    }
    printf("%d\n", ans);
    for (int i = 0; i < n; i++)
        printf("%d ", bool((qu >> i) & 1));
    puts("");
    return 0;
}