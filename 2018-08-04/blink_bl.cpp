#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MOD 998244353
inline int fuck(int x, int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int t, n, k, ans, sum;
int f[MAXN][MAXN], g[MAXN][MAXN], size[MAXN];
int head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline void down(int &x, int y) {
    if ((x -= y) < 0) x += MOD;
}
void dfs(int x, int fa) {
    f[x][0] = f[x][1] = size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dfs(to[i], x);
        for (int j = std::min(size[x], ::k); ~j; j--) {
            for (int k = std::min(size[to[i]], ::k - j); k; k--) {
                int delta = 1LL * f[x][j] * f[to[i]][k] % MOD;
                up(f[x][j + k], delta);
                up(g[x][j + k], (g[x][j] + g[to[i]][k] + 2LL * val[i] % MOD * delta % MOD) % MOD);
            }
        }
        size[x] += size[to[i]];
    }
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        for (int k = std::min(size[to[i]], ::k); k; k--) {
            down(f[x][k], f[to[i]][k]);
            down(g[x][k], g[to[i]][k]);
        }
    }
    up(ans, g[x][k]);
}
int frc[MAXN], inv[MAXN];
inline int C(int n, int m) {
    return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

    for (scanf("%d", &t); t; t--) {
        scanf("%d%d", &n, &k);
        memset(head, -1, sizeof(head));
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        ans = sum = 0;
        for (int i = 1, u, v, w; i < n; i++) {
            scanf("%d%d%d", &u, &v, &w);
            $(u, v, w);
            sum += w;
        }
        if (n == k) {
            printf("%lld\n", 2LL * sum % MOD);
            continue;
        }
        dfs(1, 0);
        printf("%lld\n", 1LL * ans * fuck(C(n, k), MOD - 2) % MOD);
    }
    return 0;
}