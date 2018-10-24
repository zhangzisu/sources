#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
int _0;
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2, _5[64];
inline char gc() {
    if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
    return _3 == _1 + _0 ? 0 : *_3++;
}
inline void pc(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void rt() { fwrite(_2, 1, _4 - _2, stdout), exit(0); }
inline int $() {
    register int x = 0, f = 0;
    register char ch = gc();
    for (; !isdigit(ch); ch = gc()) f ^= ch == 45;
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
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
inline void $(const char *s) {
    for (; *s; s++) pc(*s);
}
#define MAXN 310
int T, n, a[MAXN][MAXN], c[MAXN][MAXN], s[MAXN], t[MAXN], vis[MAXN], ans[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int *bit, int x, int y) {
    for (; x <= n; x += lowbit(x)) bit[x] += y;
}
inline int qry(int *bit, int x) {
    int y = 0;
    for (; x >= 1; x -= lowbit(x)) y += bit[x];
    return y;
}
int main() {
    for (T = $(); T; T--) {
        n = $();
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j < n; j++)
                c[j][a[i][j] = $()]++;
        memset(s, 0, sizeof(s));
        memset(t, 0, sizeof(t));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++) add(s, i, 1);
        for (int x = 1; x <= n; x++) {
            if (c[1][x] >= n - x && c[1][x - 1] >= x - 1) {
                vis[ans[1] = x] = 1;
                add(s, x, -1);
                add(t, x, 1);
                break;
            }
        }
        for (int p = 2; p <= n; p++) {
            int *d = c[p - 1], y = ans[p - 1];
            d[y] -= qry(s, n) - qry(s, y);
            d[y - 1] -= qry(s, y - 1);
            for (int x = 1; x <= n; x++) {
                if (vis[x]) continue;
                if (qry(t, n) - qry(t, x) == d[x] && qry(t, x - 1) == d[x - 1]) {
                    ans[p] = x;
                    add(s, x, -1);
                    add(t, x, 1);
                    break;
                }
            }
        }
        for (int i = 1; i <= n; i++) $(ans[i]), pc(32);
        pc(10);
    }
    rt();
}