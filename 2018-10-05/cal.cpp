#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
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
inline void pi(int x) {
    static int _5[32];
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) pc(_5[_6--] ^ 48);
}
#include <map>
#define MAXN 2010
#define MAXM 10000010
#define MOD 1000000007
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline int mum(int x, int y) {
    return x + y >= MOD ? x + y - MOD : x + y;
}
namespace tr_1 {
int L[MAXM], R[MAXM], sum[MAXM], tot = 0;
inline void add(int &n, int l, int r, int p, int v) {
    if (!n) n = ++tot;
    up(sum[n], v);
    if (l == r) return;
    int mid = (l + r) >> 1;
    p <= mid ? add(L[n], l, mid, p, v) : add(R[n], mid + 1, r, p, v);
}
inline int qry(int n, int l, int r, int _l, int _r) {
    if (!n) return 0;
    if (l == _l && r == _r) return sum[n];
    int mid = (l + r) >> 1;
    if (_r <= mid) return qry(L[n], l, mid, _l, _r);
    if (_l > mid) return qry(R[n], mid + 1, r, _l, _r);
    return mum(qry(L[n], l, mid, _l, mid), qry(R[n], mid + 1, r, mid + 1, _r));
}
}  // namespace tr_1
namespace tr_2 {
int L[MAXM], R[MAXM], root[MAXM], tot = 0;
inline void add(int &n, int l, int r, int x, int y, int v) {
    if (!n) n = ++tot;
    tr_1::add(root[n], 1, 1000000000, y, v);
    if (l == r) return;
    int mid = (l + r) >> 1;
    x <= mid ? add(L[n], l, mid, x, y, v) : add(R[n], mid + 1, r, x, y, v);
}
inline int qry(int n, int l, int r, int _l, int _r, int __l, int __r) {
    if (!n) return 0;
    if (l == _l && r == _r) return tr_1::qry(root[n], 1, 1000000000, __l, __r);
    int mid = (l + r) >> 1;
    if (_r <= mid) return qry(L[n], l, mid, _l, _r, __l, __r);
    if (_l > mid) return qry(R[n], mid + 1, r, _l, _r, __l, __r);
    return mum(qry(L[n], l, mid, _l, mid, __l, __r), qry(R[n], mid + 1, r, mid + 1, _r, __l, __r));
}
}  // namespace tr_2
inline int fuck(int x, int p) {
    int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int n, m, a, b, c, d, q, root;
inline int trim(int x) {
    return x >= MOD ? x - MOD : x;
}
inline int T(int a, int n) {
    if (a == 1) {
        return n + 1;
    } else {
        return 1LL * trim(fuck(a, n + 1) + MOD - 1) * fuck(a - 1, MOD - 2) % MOD;
    }
}
inline int S(int a, int n) {
    if (n == 1) return 1;
    if (a == 1) {
        return 1LL * (1 + n) * n / 2 % MOD;
    } else {
        int inv = fuck(a - 1, MOD - 2);
        return trim(1LL * inv * trim(1LL * trim(fuck(a, n + 1) - fuck(a, 2) + MOD) * inv % MOD - n + 1 + MOD) + 1);
    }
}
std::map<std::pair<int, int>, int> M;
int main() {
    freopen("cal.in", "r", stdin);
    freopen("cal.out", "w", stdout);

    n = $(), m = $(), a = $(), b = $(), c = $(), d = $(), q = $();
    for (int op, x1, y1, x2, y2; q; q--) {
        op = $();
        if (op == 1) {
            x1 = $(), y1 = $(), x2 = $();
            int origin;
            if (M.count(std::make_pair(x1, y1))) {
                origin = M[std::make_pair(x1, y1)];
            } else {
                origin = 1LL * b * T(a, x1 - 1) % MOD * d % MOD * T(c, y1 - 1) % MOD;
            }
            M[std::make_pair(x1, y1)] = x2;
            // int prt = tr_1::tot;
            tr_2::add(root, 1, 1000000000, x1, y1, MOD - origin);
            tr_2::add(root, 1, 1000000000, x1, y1, x2);
            // fprintf(stderr, "DELTA: %d\n", tr_1::tot - prt);
        } else {
            x1 = $(), y1 = $(), x2 = $(), y2 = $();
            int origin = 1LL * trim(S(a, x2) - S(a, x1 - 1) + MOD) * b % MOD * trim(S(c, y2) - S(c, y1 - 1) + MOD) * d % MOD;
            int delta = tr_2::qry(root, 1, 1000000000, x1, x2, y1, y2);
            printf("%d\n", trim(origin + delta));
        }
    }
    // fprintf(stderr, "%d\n", tr_1::tot);
    // fprintf(stderr, "%d\n", tr_2::tot);
    return 0;
}