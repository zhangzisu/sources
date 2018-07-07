#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 10
#define MAXM 1000
#define MOD 1000000007

inline int fuck(int x, int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}

inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}

int n, m, all;
int f[MAXN][1 << MAXN][1 << MAXN], g[MAXN][1 << MAXN][1 << MAXN], c[1 << MAXN][1 << MAXN], s[1 << MAXN][1 << MAXN];
struct edge {
    int u, v, w;
    inline edge(int u, int v, int w) : u(u), v(v), w(w) {}
};
std::vector<edge> e;
int d[MAXN], D[MAXN], ans;

int main() {
    scanf("%d%d", &n, &m);
    all = (1 << n) - 1;
    for (int i = 0, u, v, w; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        e.emplace_back(u - 1, v - 1, w);
        e.emplace_back(v - 1, u - 1, w);
    }
    for (int i = 1; i < (1 << n); i++) {
        int rest = all ^ i;
        for (int j = rest; j; j = (j - 1) & rest) {
            memset(d, 0, sizeof(d));
            for (auto k : e) {
                if (((i >> k.u) & 1) && ((j >> k.v) & 1)) d[k.v]++;
            }
            int count = 1;
            for (int k = 0; k < n; k++) {
                if ((j >> k) & 1) count = 1LL * count * d[k] % MOD;
                D[k] = fuck(d[k], MOD - 2);
            }
            c[i][j] = count;
            for (auto k : e) {
                if (((i >> k.u) & 1) && ((j >> k.v) & 1)) {
                    up(s[i][j], 1LL * count * D[k.v] % MOD * k.w % MOD);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) f[0][0][1 << i] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            int rest = all ^ j;
            for (int k = rest; k; k = (k - 1) & rest) {
                if (!f[i][j][k]) continue;
                int rrest = all ^ (j | k);
                for (int w = rrest; w; w = (w - 1) & rrest) {
                    up(f[i + 1][j | k][w], 1LL * f[i][j][k] * c[k][w] % MOD);
                    up(g[i + 1][j | k][w], (1LL * g[i][j][k] * c[k][w] % MOD + 1LL * (i + 1) * f[i][j][k] % MOD * s[k][w] % MOD) % MOD);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            up(ans, g[i][j][all ^ j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}