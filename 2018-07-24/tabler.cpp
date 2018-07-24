#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define popcount(x) __builtin_popcount(x)
#define MAXN 1010
#define MOD 1000000007
int f[1 << 20][21], data[21][21];
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int near(int x, int y, int n) {
    return x == y || (x + 1) % n == y || (y + 1) % n == x;
}

int calc(int n, int k) {
    int start = clock();
    int m = (1 << n) - 1, ans = 0;
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (int d = 0; d < m; d++) {
        int cd = popcount(d);
        for (int i = 0; i < n; i++) {
            if ((d >> i) & 1) continue;
            int t = near(i, cd, n);
            for (int j = 0; j < n; j++) {
                up(f[d | (1 << i)][j + t], f[d][j]);
            }
        }
    }
    for (int i = k; i <= n; i++) up(ans, f[m][i]);
    printf("Time of calc(%d, %d): %lf\n", n, k, 1. * (clock() - start) / CLOCKS_PER_SEC);
    return ans;
}

int main() {
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= i; j++) data[i][j] = calc(i, j);
    }
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= i; j++) printf("%10d ", data[i][j]);
        puts("");
    }
}