#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 20000
int n, L[MAXN], R[MAXN], a[MAXN], b[MAXN], c[MAXN];
long long f[MAXN][40][40];
inline long long F(int x, int i, int j) {
    if (x < n) return f[x][i][j];
    return 1LL * c[x - n] * (a[x - n] + i) * (b[x - n] + j);
}
void dp(int x) {
    if (x > n) return;
    dp(L[x]);
    dp(R[x]);
    for (int i = 0; i < 40; i++)
        for (int j = 0; j < 40; j++)
            f[x][i][j] = std::min(F(L[x], i + 1, j) + F(R[x], i, j), F(L[x], i, j) + F(R[x], i, j + 1));
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &L[i], &R[i]);
        if (L[i] < 0) L[i] = n - L[i];
        if (R[i] < 0) R[i] = n - R[i];
    }
    for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i], &b[i], &c[i]);
    memset(f, 0x3F, sizeof(f));
    dp(1);
    printf("%lld\n", f[1][0][0]);
    return 0;
}