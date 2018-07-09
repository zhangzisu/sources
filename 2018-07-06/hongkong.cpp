#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
inline int getInt() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 200010
#define MAXK 41
#define MOD 1000000007

int n, m, k, op, x, y;
int tmp[MAXK][MAXN];
inline void up(int& x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

int BIT[MAXK][MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int k, int x, int v) {
    for (; x <= n; x += lowbit(x)) up(BIT[k][x], v);
}
inline int qry(int k, int x) {
    register int v = 0;
    for (; x; x -= lowbit(x)) up(v, BIT[k][x]);
    return v;
}
int inv[MAXN], frc[MAXN];
inline int C(int n, int m) {
    if (n >= m) return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
    if (n < 0) return ((m & 1 ? -1LL : 1LL) * frc[m - n - 1] * inv[-n - 1] % MOD * inv[m] % MOD + MOD) % MOD;
    if (n < m) return 0;
}
inline int fuck(int x, int p) {
    int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}

int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

    n = getInt();
    m = getInt();
    k = getInt();

    while (m--) {
        int op, x, y = 0;
        if (scanf("%d", &op) && op) {
            scanf("%d", &x);
            for (int j = 0; j <= k; j++) {
                up(y, 1LL * C(x, j) * qry(k - j, x) % MOD);
            }
            printf("%d\n", y);
        } else {
            scanf("%d%d", &x, &y);
            for (int j = 0; j <= k; j++) {
                add(k - j, x, 1LL * C(k - x - 1, k - j - 1) * y % MOD);
            }
        }
    }
    return 0;
}