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
#define MAXN 1000010
typedef long long lnt;
int n, q, a[MAXN], b[MAXN], bit[MAXN];
lnt ans = 0;
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int v) {
    for (; x <= 2 * n; x += lowbit(x)) bit[x] += v;
}
inline int qry(int x) {
    int v = 0;
    for (; x; x -= lowbit(x)) v += bit[x];
    return v;
}
int main() {
    n = $();
    for (int i = 1; i <= 2 * n; i++) {
        a[i] = $();
        if (b[a[i]]) {
            ans += std::min(i - b[a[i]], 2 * n + b[a[i]] - i) - 1;
            add(b[a[i]], -1);
            ans -= qry(2 * n);
            ans += qry(b[a[i]]);
        } else {
            add(i, 1);
            b[a[i]] = i;
        }
    }
    printf("%lld\n", ans);
    return 0;
}