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
const int INF = 0x3F3F3F3F;
int n, m, a[MAXN];
inline bool judge(int delta) {
    int c = 0;
    for (int i = 1, pre = -INF; i <= n; i++) {
        if (a[i] - pre >= delta) c++, pre = a[i];
    }
    return c >= m;
}
int main() {
    freopen("margin.in", "r", stdin);
    freopen("margin.out", "w", stdout);

    n = $(), m = $();
    for (int i = 1; i <= n; i++) a[i] = $();
    std::sort(a + 1, a + n + 1);
    int l = 1, r = INF, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (judge(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}