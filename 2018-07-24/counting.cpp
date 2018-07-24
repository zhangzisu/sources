#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define popcount(x) __builtin_popcount(x)
#define MAXN 1010
#define MOD 1000000007
int n, m, k, f[1 << 20][21], ans;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int near(int x, int y) {
    return x == y || (x + 1) % n == y || (y + 1) % n == x;
}

int main() {
    int start = clock();
    // freopen("counting.in", "r", stdin);
    // freopen("counting.out", "w", stdout);
    scanf("%d%d", &n, &k);
    m = (1 << n) - 1;
    f[0][0] = 1;
    for (int d = 0; d < m; d++) {
        int cd = popcount(d);
        for (int i = 0; i < n; i++) {
            if ((d >> i) & 1) continue;
            int t = near(i, cd);
            for (int j = 0; j < n; j++) {
                up(f[d | (1 << i)][j + t], f[d][j]);
            }
        }
    }
    for (int i = k; i <= n; i++) up(ans, f[m][i]);
    printf("%d\n", ans);
    fprintf(stderr, "TIME SPENT: %lf ms\n", 1000. * (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}