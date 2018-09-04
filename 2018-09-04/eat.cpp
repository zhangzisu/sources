#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int MAXN = 18;
inline int lowbit(int x) { return x & -x; }
int n, m, ans, to[1 << MAXN], f[1 << MAXN];
int main() {
    freopen("eat.in", "r", stdin);
    freopen("eat.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        u--, v--;
        to[1 << u] |= 1 << v;
        to[1 << v] |= 1 << u;
    }
    for (int i = 0; i < 1 << n; i++) to[i] = to[i - lowbit(i)] | to[lowbit(i)];
    for (int i = 0; i < (1 << n); i++) {
        if (i == lowbit(i)) {
            f[i] = 1;
        } else {
            f[i] = f[i - lowbit(i)] && (!(to[i - lowbit(i)] & lowbit(i)));
        }
        if (f[i]) ans = std::max(ans, __builtin_popcount(i));
    }
    printf("%d\n", ans);
    return 0;
}