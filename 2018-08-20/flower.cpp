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
    register int x = 0, f = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    if (!(ch ^ 45)) ch = gc(), f = 1;
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
}
#define MAXN 100010
typedef long long lnt;
int n, k, m, b[MAXN], min[MAXN << 2];
inline void up(int &x, int y) {
    if (y < x) x = y;
}
inline void pushDown(int n) {
    up(min[n << 1], min[n]);
    up(min[n << 1 | 1], min[n]);
}
void gao(int n, int l, int r, int L, int R, int v) {
    if (l == L && r == R) return up(min[n], v);
    int mid = (l + r) >> 1;
    pushDown(n);
    if (R <= mid) return gao(n << 1, l, mid, L, R, v);
    if (L > mid) return gao(n << 1 | 1, mid + 1, r, L, R, v);
    gao(n << 1, l, mid, L, mid, v);
    gao(n << 1 | 1, mid + 1, r, mid + 1, R, v);
}
int cao(int n, int l, int r, int p) {
    if (l == r) return min[n];
    int mid = (l + r) >> 1;
    pushDown(n);
    return p <= mid ? cao(n << 1, l, mid, p) : cao(n << 1 | 1, mid + 1, r, p);
}
lnt ans, tmp, f[MAXN];
std::pair<int, int> q[MAXN];
int main() {
    n = $(), k = $(), m = $();
    for (int i = 1; i <= n; i++) b[i] = $();
    memset(min, 0x3F, sizeof(min));
    for (int l, r, c; m; m--) {
        l = $(), r = $(), c = $();
        gao(1, 1, n, l, r, c);
    }
    for (int i = 1; i <= n; i++) {
        ans += b[i];
        if (b[i] < 0) {
            int x = cao(1, 1, n, i);
            if (x <= k) q[++m] = std::make_pair(-b[i], x);
        }
    }
    memset(f, 0x80, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = k; j >= q[i].second; j--) {
            f[j] = std::max(f[j], f[j - q[i].second] + q[i].first);
        }
    }
    for (int i = 0; i <= k; i++) tmp = std::max(tmp, f[i]);
    printf("%lld\n", ans + tmp);
    return 0;
}