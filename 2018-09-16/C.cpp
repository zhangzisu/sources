#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define MOD 1000000009
const int MAXN = 14;
inline int lowbit(int x) { return x & -x; }
inline int trim(int x) { return x >= MOD ? x - MOD : x; }
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int n, m, K;
int next[MAXN][MAXN], bin[1 << MAXN], cnt[1 << MAXN], s[1 << MAXN], g[1 << MAXN], f[1 << MAXN][MAXN + 1], log_2[1 << MAXN];
inline int calc(int d, int lb) {
    int ret = 0;
    lb = log_2[lb];
    for (int i = 0; i < n; i++)
        if ((d >> i) & 1) ret += next[i][lb];
    return ret;
}
int main() {
    scanf("%d%d%d", &n, &m, &K);
    bin[0] = 1;
    for (int i = 1; i < (1 << n); i++) bin[i] = (bin[i - 1] << 1) % MOD;
    log_2[1] = 0;
    for (int i = 2; i <= (1 << n); i++) log_2[i] = log_2[i >> 1] + 1;
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v), u--, v--;
        next[u][v] = next[v][u] = 1;
    }
    for (int i = 1; i < bin[n]; i++) {
        cnt[i] = cnt[i - lowbit(i)] + calc(i, lowbit(i));
    }
    for (int i = 1; i < bin[n]; i++) {
        for (int j = i; j; j = (j - 1) & i) {
            if (j & lowbit(i)) up(s[i], 1LL * g[j] * bin[cnt[i - j]] % MOD);
        }
        g[i] = trim(bin[cnt[i]] - s[i] + MOD);
    }
    f[0][0] = 1;
    for (int i = 1; i < bin[n]; i++) {
        for (int k = 1; k <= K; k++) {
            for (int j = i; j; j = (j - 1) & i) {
                if (j & lowbit(i)) up(f[i][k], 1LL * f[i - j][k - 1] * g[j] % MOD);
            }
        }
    }
    printf("%d\n", f[bin[n] - 1][K]);
}
