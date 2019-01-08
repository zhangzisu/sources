#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MOD 1000000007
int n, K, size[MAXN], f[MAXN][110][2][2], g[110][2][2];
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline void upd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
void dp(int x, int fa) {
    f[x][0][0][0] = f[x][1][1][0] = size[x] = 1;
    for (int i = head[x], y; ~i; i = next[i]) {
        if ((y = to[i]) == fa) continue;
        dp(y, x);
        memcpy(g, f[x], sizeof(g));
        memset(f[x], 0, sizeof(f[x]));
        for (int j = std::min(size[x], K); ~j; j--) {
            for (int k = std::min(size[y], K - j); ~k; k--) {
                int sum = (0LL + f[y][k][0][0] + f[y][k][0][1] + f[y][k][1][0] + f[y][k][1][1]) % MOD;
                upd(f[x][j + k][0][0], (1LL * g[j][0][0] * f[y][k][0][1]) % MOD);
                upd(f[x][j + k][0][1], (1LL * g[j][0][0] * f[y][k][1][1] + 1LL * g[j][0][1] * (f[y][k][1][1] + f[y][k][0][1])) % MOD);
                upd(f[x][j + k][1][0], (1LL * g[j][1][0] * (f[y][k][0][0] + f[y][k][0][1])) % MOD);
                upd(f[x][j + k][1][1], (1LL * g[j][1][1] * sum + 1LL * g[j][1][0] * (f[y][k][1][0] + f[y][k][1][1])) % MOD);
            }
        }
        size[x] += size[y];
    }
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &K);
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
    dp(1, 0);
    printf("%d\n", (f[1][K][0][1] + f[1][K][1][1]) % MOD);
    return 0;
}