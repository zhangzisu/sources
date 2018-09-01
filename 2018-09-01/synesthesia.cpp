#include <algorithm>
#include <cassert>
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
const int INF = (~0U) >> 1;
int n, m, l, a[MAXN], p[MAXN], s[MAXN], ans = INF;

int main() {
    // freopen("synesthesia.in", "r", stdin);
    // freopen("synesthesia.out", "w", stdout);
    n = $();
    for (int i = 1; i <= n; i++) {
        p[a[i] = $()] = i;
        if (a[i] > m) {
            m = a[i];
            s[i] = 1;
        }
        s[i] += s[i - 1];
    }
    assert(n == m);
    for (int r = 1; r <= n; r++) {
        if (!l) l = r;
        if (p[r + 1] < p[r]) {
            ans = std::min(ans, 2 * (n - r) + l - 1 - s[p[l] - 1]);
            l = 0;
        }
    }
    printf("%d\n", ans);
    return 0;
}