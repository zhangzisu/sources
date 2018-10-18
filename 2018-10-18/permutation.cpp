#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000010
#define MOD 1000000007
int T, n, m, frc[MAXN];
inline int fuck(int x, int p) {
    int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    for (scanf("%d", &T); T; T--) {
        scanf("%d%d", &n, &m);
        if (n == 1) {
            puts("1");
            continue;
        }
        if (m < n + 1) {
            puts("0");
            continue;
        }
        m = std::min(m, n * 2 - 1) - n;
        int base = frc[m + 1], delta = n - m - 1;
        int c0 = (delta + 1) / 2, c1 = delta - c0;
        base = 1LL * base * fuck(m, c0) % MOD * fuck(m + 1, c1) % MOD;
        printf("%d\n", base);
    }
    return 0;
}