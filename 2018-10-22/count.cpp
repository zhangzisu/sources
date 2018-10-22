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
inline void $(const char *s) {
    for (; *s; s++) pc(*s);
}
#define MAXN 100010
typedef long long lnt;
int t, n, a[MAXN], stk0[MAXN], stk1[MAXN], top0, top1;
lnt sum0, sum1, ans;
int main() {
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    for (t = $(); t; t--) {
        n = $();
        stk0[top0 = 0] = n + 1;
        stk1[top1 = 0] = n + 1;
        sum0 = sum1 = ans = 0;
        for (int i = 1; i <= n; i++) a[i] = $();
        for (int i = n; i >= 1; i--) {
            while (top0 && a[stk0[top0]] < a[i]) {
                sum0 -= 1LL * (stk0[top0 - 1] - stk0[top0]) * a[stk0[top0]];
                top0--;
            }
            stk0[++top0] = i;
            sum0 += 1LL * (stk0[top0 - 1] - stk0[top0]) * a[i];

            while (top1 && a[stk1[top1]] > a[i]) {
                sum1 -= 1LL * (stk1[top1 - 1] - stk1[top1]) * a[stk1[top1]];
                top1--;
            }
            stk1[++top1] = i;
            sum1 += 1LL * (stk1[top1 - 1] - stk1[top1]) * a[i];

            ans += sum0 - sum1;
        }
        $(ans), pc(10);
    }
    rt();
}