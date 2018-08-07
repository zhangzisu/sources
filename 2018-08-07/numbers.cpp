#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0, f = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    if (ch == 45) ch = gc(), f = 1;
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
}
#define MAXN 200010
#define MOD 1000000007
int n, q, p, a[MAXN], f[110][110], g[110][110][110], h[2][110];
int frc[MAXN], inv[MAXN];
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int down(int x, int m) {
    return x >= m ? x - m : x;
}
inline int C(int n, int m) {
    return n < m ? 0 : 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
int fuck(int x, int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int main() {
    n = $(), q = $();
    for (int i = 1; i <= n; i++) {
        a[i] = $();
        for (int j = 1; j <= 100; j++) f[j][((a[i] % j) + j) % j]++;
    }
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

    for (int i = 1; i <= 100; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 1; k <= f[i][j]; k++) {
                up(g[i][j][(j * k) % i], C(f[i][j], k));
            }
        }
    }
    for (int m; q; q--) {
        m = $();
        memset(h[1], 0, sizeof(h[1]));
        h[1][0] = 1;
        for (int i = 0; i < m; i++) {
            int now = i & 1, pre = now ^ 1;
            memcpy(h[now], h[pre], sizeof(h[pre]));
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < m; k++) {
                    up(h[now][(j + k) % m], 1LL * h[pre][j] * g[m][i][k] % MOD);
                }
            }
        }
        printf("%d\n", h[1 ^ (m & 1)][0]);
    }
}