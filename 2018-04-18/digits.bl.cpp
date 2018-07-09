#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
int T, b, n, m, t[50], x[50], y[50], z[50], l, r, ans;
int vis[50], f[50][50], frc[50], inv[50];
inline int fuck(int x, int p) {
    int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
        p >>= 1;
    }
    return y;
}
inline int judge(int x) {
    static int tmp[50];
    memset(tmp, 0, sizeof(tmp));
    while (x) tmp[x % b]++, x /= b;
    for (int i = 0; i < b; i++)
        if (tmp[i] == t[i]) return 0;
    return 1;
}
int dfs(int x, bool d) {
    if (x < 0) return 1;
    if (!d) return f[x][x];
    int ret = 0;
    for (int i = 0; i <= z[x]; i++) {
        if (vis[i]) continue;
        vis[i] = 1;
        ret = (ret + dfs(x - 1, d && i == z[x])) % MOD;
        vis[i] = 0;
    }
    return ret;
}
inline int C(int n, int m) { return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD; }
int main() {
    scanf("%d", &T);
    frc[0] = 1;
    for (int i = 1; i <= 30; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[30] = fuck(frc[30], MOD - 2);
    for (int i = 30; i >= 1; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    for (int i = 1; i <= 30; i++) {
        for (int j = i; j <= 30; j++) {
            f[i][j] = fuck(i, j);
            for (int k = 1; k < i; k++) {
                f[i][j] -= 1LL * C(i, k) * f[k][j] % MOD;
                if (f[i][j] < 0) f[i][j] += MOD;
            }
        }
    }
    while (T--) {
        scanf("%d%d%d", &b, &n, &m);
        for (int i = 0; i < b; i++) scanf("%d", &t[i]);
        for (int i = 0; i < n; i++) scanf("%d", &x[i]);
        for (int i = 0; i < m; i++) scanf("%d", &y[i]);
        if (m <= 7) {
            l = r = ans = 0;
            for (int i = n - 1; ~i; i--) l = l * b + x[i];
            for (int i = m - 1; ~i; i--) r = r * b + y[i];
            printf("L : %d\nR : %d\n", l, r);
            for (int i = l; i <= r; i++) ans += judge(i);
            printf("%d\n", ans);
        } else {
            memcpy(z, x, sizeof(z));
            int ans0 = dfs(m - 1, 1);
            memcpy(z, y, sizeof(z));
            int ans1 = dfs(m - 1, 1);
            printf("%d\n", (ans1 - ans0 + MOD) % MOD);
        }
    }
    return 0;
}