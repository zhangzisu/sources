#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
int n, m, k;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
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
int main() {
    scanf("%d%d%d", &n, &m, &k);
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
    return 0;
}