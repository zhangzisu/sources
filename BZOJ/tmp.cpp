#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, MOD = 1e9 + 7;
int n, K, head[N], nxt[N * 2], to[N * 2], num = 0, sz[N], f[N][105][2][2], g[105][2][2];
inline void link(int x, int y) {
    nxt[++num] = head[x];
    to[num] = y;
    head[x] = num;
}
inline void upd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline void dfs(int x) {
    sz[x] = f[x][1][1][0] = f[x][0][0][0] = 1;
    for (int P = head[x], y; P; P = nxt[P]) {
        if (sz[y = to[P]]) continue;
        dfs(y);
        memcpy(g, f[x], sizeof(g));
        memset(f[x], 0, sizeof(f[x]));
        for (int j = min(sz[x], K); j >= 0; j--)
            for (int k = min(sz[y], K - j); k >= 0; k--) {
                int sum = (0LL + f[y][k][0][0] + f[y][k][0][1] + f[y][k][1][0] + f[y][k][1][1]) % MOD;
                upd(f[x][j + k][1][0],(1ll * g[j][1][0] * (f[y][k][0][0] + f[y][k][0][1]) % MOD));
                upd(f[x][j + k][1][1],(1ll * g[j][1][1] * sum + 1ll * g[j][1][0] * (f[y][k][1][0] + f[y][k][1][1]) % MOD));
                upd(f[x][j + k][0][1],(1ll * g[j][0][0] * f[y][k][1][1] + 1ll * g[j][0][1] * (f[y][k][1][1] + f[y][k][0][1]) % MOD));
                upd(f[x][j + k][0][0],(1ll * g[j][0][0] * f[y][k][0][1] % MOD));
            }
        sz[x] += sz[y];
    }
}
int main() {
    int x, y;
    cin >> n >> K;
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        link(x, y);
        link(y, x);
    }
    dfs(1);
    printf("%d\n", (f[1][K][0][1] + f[1][K][1][1]) % MOD);
    return 0;
}