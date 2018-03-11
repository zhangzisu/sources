#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 510
const int prm[8] = {2, 3, 5, 7, 11, 13, 17, 19};
struct shabi {
    int a, b;
    inline shabi() { a = b = 0; }
    inline shabi(int x) {
        a = b = 0;
        for (int i = 0; i < 8; i++) {
            if (!(x % prm[i])) {
                a |= 1 << i;
                while (!(x % prm[i])) x /= prm[i];
            }
        }
        b = x;
    }
    inline friend bool operator<(const shabi& a, const shabi& b) { return a.b < b.b; }
} dt[MAXN];
int n, k, MOD, ans, f[1 << 8][1 << 8], f1[1 << 8][1 << 8], f2[1 << 8][1 << 8];
int main() {
    scanf("%d%d", &n, &MOD);
    for (int i = 2; i <= n; i++) dt[++k] = shabi(i);
    std::sort(dt + 1, dt + k + 1);
    f[0][0] = 1;
    register int p = 1;
    while (p <= k) {
        for (int d1 = 0; d1 < (1 << 8); d1++)
            for (int d2 = 0; d2 < (1 << 8); d2++) f1[d1][d2] = f2[d1][d2] = f[d1][d2];

        int now = dt[p].b;
        while (p <= k && dt[p].b == now) {
            for (int d1 = (1 << 8) - 1; ~d1; d1--)
                for (int d2 = (1 << 8) - 1; ~d2; d2--) {
                    if (!(d2 & dt[p].a)) (f1[d1 | dt[p].a][d2] += f1[d1][d2]) %= MOD;
                    if (!(d1 & dt[p].a)) (f2[d1][d2 | dt[p].a] += f2[d1][d2]) %= MOD;
                }
            p++;
            if (now == 1) break;
        }

        for (int d1 = 0; d1 < (1 << 8); d1++)
            for (int d2 = 0; d2 < (1 << 8); d2++) {
                f[d1][d2] = f1[d1][d2] + f2[d1][d2] - f[d1][d2];
                if (f[d1][d2] >= MOD) f[d1][d2] -= MOD;
                if (f[d1][d2] < 0) f[d1][d2] += MOD;
            }
    }
    for (int d1 = 0; d1 < (1 << 8); d1++)
        for (int d2 = 0; d2 < (1 << 8); d2++) (ans += f[d1][d2]) %= MOD;
    printf("%d\n", ans);
    return 0;
}