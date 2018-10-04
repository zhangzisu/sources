#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline void pc(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void rt() {
    fwrite(_2, 1, _4 - _2, stdout);
    exit(0);
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline char _() {
    register char ch = gc();
    while (!isalpha(ch)) ch = gc();
    return ch;
}
inline void ps(const char *s) {
    for (; *s; s++) pc(*s);
    pc(10);
}
inline void $(int x) {
    static int _5[65];
    if (x == 0) return pc(48);
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) pc(_5[_6--] ^ 48);
}
#define MAXN 301
int a[MAXN][MAXN], b[MAXN][MAXN][MAXN];
int n, m, q;
int main() {
    freopen("yy.in", "r", stdin);
    freopen("yy.out", "w", stdout);

    n = $(), m = $();
    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j <= m; j++) {
            a[i][j] = $();
        }
    };
    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j <= m; j++) {
            b[j][j][i] = a[i][j];
            for (register int k = j + 1; k <= m; k++) b[j][k][i] = std::max(a[i][k], b[j][k - 1][i]);
        }
    }
    q = $();
    for (int r1, c1, r2, c2, ans; q; q--) {
        r1 = $(), c1 = $(), r2 = $(), c2 = $(), ans = 0;
        int *t = b[c1][c2];
        for (register int i = r1; i <= r2; i++) ans = std::max(ans, t[i]);
        $(ans), pc(10);
    }
    rt();
}