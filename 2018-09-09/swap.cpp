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
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 5010
int n, a[MAXN], s[MAXN], f[MAXN][MAXN], pre[MAXN][MAXN], suf[MAXN][MAXN], ans = 0x3F3F3F3F;
inline void down(int &x, int y) {
    if (y < x) x = y;
}
int v[MAXN], m;
int main() {
#ifndef DEBUG
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);
#endif
    n = $();
    for (int i = 1; i <= n; i++) a[i] = $();
    memcpy(v, a, sizeof(v));
    std::sort(v + 1, v + n + 1);
    m = std::unique(v + 1, v + n + 1) - v - 1;
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(v + 1, v + n + 1, a[i]) - v;
    for (int i = 1; i < n; i++) s[i] = s[i - 1] + std::abs(v[a[i]] - v[a[i + 1]]);
    memset(f, 0x3F, sizeof(f));
    memset(pre, 0x3F, sizeof(pre));
    memset(suf, 0x3F, sizeof(suf));
    f[1][1] = 0;
    pre[1][a[1]] = -v[a[1]];
    suf[1][a[1]] = v[a[1]];
    for (int j = 1; j <= m; j++) pre[1][j] = std::min(pre[1][j], pre[1][j - 1]);
    for (int j = m; j >= 1; j--) suf[1][j] = std::min(suf[1][j], suf[1][j + 1]);
    for (int i = 2; i <= n; i++) {
        f[i][1] = std::abs(v[a[i]] - v[a[1]]) + s[i - 1] - s[1];
        pre[i][a[1]] = f[i][1] - v[a[1]];
        suf[i][a[1]] = f[i][1] + v[a[1]];
        for (int j = 2; j <= i; j++) {
            int delta = i == j ? 0 : std::abs(v[a[i]] - v[a[j]]) + s[i - 1] - s[j];
            int now = i == j ? a[i] : a[j + 1];
            f[i][j] = std::min(suf[j - 1][now] - v[now], pre[j - 1][now] + v[now]) + delta;
            pre[i][a[j]] = std::min(pre[i][a[j]], f[i][j] - v[a[j]]);
            suf[i][a[j]] = std::min(suf[i][a[j]], f[i][j] + v[a[j]]);
        }
        for (int j = 1; j <= m; j++) pre[i][j] = std::min(pre[i][j], pre[i][j - 1]);
        for (int j = m; j >= 1; j--) suf[i][j] = std::min(suf[i][j], suf[i][j + 1]);
    }
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= i; j++) printf("f[%d][%d] = %d\n", i, j, f[i][j]);
    // }
    for (int i = 1; i <= n; i++) down(ans, f[n][i]);
    printf("%d\n", ans);
    return 0;
}