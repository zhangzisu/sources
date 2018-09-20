#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char _$() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int __ = 0;
    register char _ = _$();
    while (!isdigit(_)) _ = _$();
    for (; isdigit(_); _ = _$()) __ = ((__ << 3) + (__ << 1)) + (_ ^ 48);
    return __;
}
inline void _$(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void $(int x) {
    if (x == 0) return _$('0');
    static int _5[32];
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) _$(_5[_6--] ^ 48);
}
inline void $(long long x) {
    if (x == 0) return _$('0');
    static int _5[64];
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) _$(_5[_6--] ^ 48);
}
inline void $_() { fwrite(_2, 1, _4 - _2, stdout); }
#define MAXN 100010
#define SQRT 320
#define MAXB 320
typedef long long lnt;
int n, m, q, a[MAXN], l[MAXN], r[MAXN];
int val[MAXB][MAXN], L[MAXB], R[MAXB];
lnt sum[MAXB], bit[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, lnt y) {
    for (; x <= n; x += lowbit(x)) bit[x] += y;
}
inline lnt qry(int x) {
    lnt y = 0;
    for (; x; x -= lowbit(x)) y += bit[x];
    return y;
}
inline lnt inlineQuery(int b, int s, int t) {
    lnt ans = 0;
    if (t - s + 1 >= SQRT / 2) {
        ans = sum[b];
        for (int i = L[b]; i < s; i++) ans -= qry(r[i]) - qry(l[i] - 1);
        for (int i = R[b]; i > t; i--) ans -= qry(r[i]) - qry(l[i] - 1);
    } else {
        for (int i = s; i <= t; i++) ans += qry(r[i]) - qry(l[i] - 1);
    }
    return ans;
}
int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    n = $();
    for (int i = 1; i <= n; i++) add(i, a[i] = $());
    for (int i = 1; i <= n; i++) l[i] = $(), r[i] = $();
    for (; R[m] != n;) {
        ++m;
        L[m] = R[m - 1] + 1;
        R[m] = std::min(L[m] + SQRT - 1, n);
        for (int i = L[m]; i <= R[m]; i++) val[m][l[i]]++, val[m][r[i] + 1]--;
        for (int i = 1; i <= n; i++) {
            val[m][i] += val[m][i - 1];
            sum[m] += 1LL * val[m][i] * a[i];
        }
    }
    q = $();
    for (int op, x, y; q; q--) {
        op = $(), x = $(), y = $();
        if (op == 1) {
            for (int i = 1; i <= m; i++) {
                sum[i] -= 1LL * a[x] * val[i][x];
                sum[i] += 1LL * y * val[i][x];
            }
            add(x, -a[x]);
            add(x, a[x] = y);
        } else {
            int bl = (x + SQRT - 1) / SQRT;
            int br = (y + SQRT - 1) / SQRT;
            lnt ans = 0;
            if (bl == br) {
                ans = inlineQuery(bl, x, y);
            } else {
                ans = inlineQuery(bl, x, R[bl]) + inlineQuery(br, L[br], y);
                for (int i = bl + 1; i < br; i++) ans += sum[i];
            }
            $(ans);
            _$(10);
        }
    }
    $_();
}