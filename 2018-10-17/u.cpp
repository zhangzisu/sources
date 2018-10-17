#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2, _5[64];
int _0;
inline char gc() {
    if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
    return _3 == _1 + _0 ? 0 : *_3++;
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
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline void $(int x) {
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = (x % 10) ^ 48;
    while (_6) pc(_5[_6--]);
}
inline void $(long long x) {
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = (x % 10) ^ 48;
    while (_6) pc(_5[_6--]);
}
#define MAXN 1010
typedef long long lnt;
int n, q;
lnt s[MAXN][MAXN], t[MAXN][MAXN], ans;
int id[MAXN][MAXN], pos[MAXN][MAXN], len[MAXN * 2];
int main() {
    n = $(), q = $();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            id[i][j] = i - j + n;
            len[i - j + n] = pos[i][j] = pos[i - 1][j - 1] + 1;
        }
    }
    for (int x, y, z, w; q; q--) {
        x = $(), y = $(), z = $(), w = $();
        s[x][y] += w;
        if (x + z <= n) s[x + z][y] -= w;
        if (y + 1 <= n) t[x][y + 1] += w;
        if (x + z <= n && y + z + 1 <= n) t[x + z][y + z + 1] -= w;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = s[i - 1][j] + s[i][j];
            t[i][j] = t[i - 1][j - 1] + t[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = s[i][j - 1] + s[i][j] - t[i][j];
            ans ^= s[i][j];
        }
    }
    $(ans), pc(10);
    rt();
}