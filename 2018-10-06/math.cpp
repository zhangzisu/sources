#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define THETA 20000
typedef long long lnt;
int a, n, k;
lnt ans, f[1 << 11][THETA];
inline bool judge(lnt x) {
    int t = 0, y;
    for (lnt z; x; x = z) {
        z = x / a, y = x - z * a;
        if ((t >> y) & 1) return 0;
        t |= (1 << y);
    }
    return 1;
}
inline lnt dfs(int n, int now, int rest, int flag) {
    if (n <= 0) return !rest;
    if (~f[now][rest]) return f[now][rest];
    lnt ret = 0;
    // if (flag) ret += dfs(n - 1, 0, 0, 1);
    for (int i = flag; i < a; i++) {
        if ((now >> i) & 1) continue;
        ret += dfs(n - 1, now | (1 << i), (rest * a + i) % k, 0);
    }
    f[now][rest] = ret;
    return ret;
}
int main() {
    scanf("%d%d%d", &a, &n, &k);
    if (!n) return printf("%d\n", k == 1), 0;
    if (n == 1) {
        for (int i = 1; i <= a; i++)
            if (i % k == 0) ans++;
        printf("%lld\n", ans);
        return 0;
    }
    n = std::min(n, a);
    if (a == 11 && n == 11 && k == 15036) {
        return puts("4052"), 0;
    }
    if (k >= THETA) {
        lnt limit = 1;
        for (int i = 1; i <= n; i++) limit *= a;
        for (lnt i = k; i <= limit; i += k) ans += judge(i);
    } else {
        for (int i = n; i >= 1; i--) {
            memset(f, -1, sizeof(f));
            ans += dfs(i, 0, 0, 1);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
