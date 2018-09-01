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
#define MAXN 100010
int n, ans, f[90][90][4], g[90][90][4], s[90][90];
inline void umax(int &x, int y) {
    if (x < y) x = y;
}
int main() {
    freopen("euphoria.in", "r", stdin);
    freopen("euphoria.out", "w", stdout);
    n = $();
    memset(f, 0x80, sizeof(f));
    memset(g, 0x80, sizeof(g));
    memset(s, 0x80, sizeof(s));
    for (int i = 1, x; i <= n; i++) {
        x = $();
        umax(g[x][0][0], ans + 1);
        for (int j = 1; j <= 88; j++) {
            if (x > j) umax(g[x][j][1], f[j][0][0] + 1);
            if (x < j) umax(g[x][j][2], s[j][x - 1] + 1);
            if (x < j) umax(g[x][j][2], f[j][x][3] + 1);
            if (x > j) umax(g[x][j][3], f[j][x][2] + 1);
        }
        f[x][0][0] = g[x][0][0];
        for (int j = 1; j <= 88; j++) {
            f[x][j][1] = g[x][j][1];
            f[x][j][2] = g[x][j][2];
            umax(ans, f[x][j][3] = g[x][j][3]);
            umax(s[x][j], s[x][j - 1]);
            umax(s[x][j], f[x][j][1]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
