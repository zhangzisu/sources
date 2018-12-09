#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
int n, m, k;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
namespace GCC {
int ans, all, U[17], V[17], e = 0, G[7][7], p[7];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
inline int calc() {
    for (int k = 1; k <= all; k++)
        for (int i = 1; i <= all; i++)
            for (int j = 1; j <= all; j++) G[i][j] |= G[i][k] && G[k][j];
    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= all; j++)
            if (G[i][j] && G[j][i]) return 0;
    for (int i = 1; i <= all; i++) p[i] = i;
    int cnt = m;
    for (int i = n + 1; i <= all; i++)
        for (int j = i + 1; j <= all; j++)
            if (G[i][j] && G[j][i]) {
                int I = find(i), J = find(j);
                if (I != J) p[I] = J, cnt--;
            }
    return cnt;
}
inline int main() {
    all = n + m;
    for (int i = 1; i <= all; i++)
        for (int j = i + 1; j <= all; j++, e++) U[e] = i, V[e] = j;
    for (int d = 0; d < (1 << e); d++) {
        memset(G, 0, sizeof(G));
        for (int i = 0; i < e; i++) {
            int u = U[i], v = V[i];
            if ((d >> i) & 1) std::swap(u, v);
            G[u][v] = 1;
        }
        if (calc() == k) up(ans, 1);
    }
    printf("%d\n", ans);
    return 0;
}
}  // namespace GCC
namespace HAHA {
const int MAXN = 100010;
int frc[MAXN], inv[MAXN], F[MAXN];
inline int fuck(int x, int y) {
    int z = 1;
    for (; y; y >>= 1) {
        if (y & 1) z = 1LL * z * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return z;
}
inline int C(int m, int n) {
    return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
int a[MAXN];
inline int main() {
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;
    for (int i = 1; i < MAXN; i++) F[i] = fuck(2, i * (i - 1) / 2);
    a[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        a[i] = F[i];
        for (int j = 1; j < i; j++) {
            up(a[i], MOD - 1LL * a[j] * (1LL * F[i - j] * C(j, i) % MOD) % MOD);
        }
    }
    printf("%d\n", a[m]);
    return 0;
}
}  // namespace HAHA
int main() {
    scanf("%d%d%d", &n, &m, &k);
    if (n == 0 && k == 1) return HAHA::main();
    GCC::main();
    return 0;
}