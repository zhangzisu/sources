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
#define MOD 998244353
inline int fpow(int x, int p) {
    register int ret = 1;
    while (p) {
        if (p & 1) ret = (long long)ret * x % MOD;
        x = (long long)x * x % MOD;
        p >>= 1;
    }
    return ret;
}
int val[50000000], ls[50000000], rs[50000000], cnt = 0;
inline int mul(int a, int b) { return ((long long)a * b % MOD + (long long)(MOD + 1 - a) * (MOD + 1 - b) % MOD) % MOD; }
void insert0(int &N, int l, int r, int L, int R, int v) {
    if (!N) val[N = ++cnt] = 1;
    if (l == L && r == R) return (void)(val[N] = mul(val[N], v));
    int mid = (l + r) >> 1;
    if (R <= mid) return insert0(ls[N], l, mid, L, R, v);
    if (L > mid) return insert0(rs[N], mid + 1, r, L, R, v);
    insert0(ls[N], l, mid, L, mid, v), insert0(rs[N], mid + 1, r, mid + 1, R, v);
}
int query0(int N, int l, int r, int p) {
    if (!N) return 1;
    int ret = val[N];
    if (l == r) return ret;
    int mid = (l + r) >> 1;
    if (p <= mid) return mul(ret, query0(ls[N], l, mid, p));
    return mul(ret, query0(rs[N], mid + 1, r, p));
}
int root[MAXN << 2], n, m;
void insert1(int N, int l, int r, int L, int R, int _l, int _r, int v) {
    if (l == L && r == R) return insert0(root[N], 1, n, _l, _r, v);
    int mid = (l + r) >> 1;
    if (R <= mid) return insert1(N << 1, l, mid, L, R, _l, _r, v);
    if (L > mid) return insert1(N << 1 | 1, mid + 1, r, L, R, _l, _r, v);
    insert1(N << 1, l, mid, L, mid, _l, _r, v), insert1(N << 1 | 1, mid + 1, r, mid + 1, R, _l, _r, v);
}
int query1(int N, int l, int r, int p, int _p) {
    int ret = query0(root[N], 1, n, _p);
    if (l == r) return ret;
    int mid = (l + r) >> 1;
    if (p <= mid) return mul(ret, query1(N << 1, l, mid, p, _p));
    return mul(ret, query1(N << 1 | 1, mid + 1, r, p, _p));
}
int main() {
    n = $(), m = $();
    while (m--) {
        register int op = $(), l = $(), r = $();
        if (op == 1) {
            int p = fpow(r - l + 1, MOD - 2), iv = (1 + MOD - p) % MOD;
            if (l > 1) insert1(1, 0, n, 1, l - 1, l, r, iv);
            if (r < n) insert1(1, 0, n, l, r, r + 1, n, iv);
            insert1(1, 0, n, l, r, l, r, (1 - (long long)p * 2 % MOD + MOD) % MOD);
            if (l > 1) insert1(1, 0, n, 0, 0, 1, l - 1, 0);
            if (r < n) insert1(1, 0, n, 0, 0, r + 1, n, 0);
            insert1(1, 0, n, 0, 0, l, r, p);
        } else {
            printf("%d\n", query1(1, 0, n, l - 1, r));
        }
    }
    return 0;
}