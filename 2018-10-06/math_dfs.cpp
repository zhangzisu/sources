#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long lnt;
int a, n, k, ans;
void dfs(int d, lnt now, int vis) {
    if (d <= 0) {
        ans += (now % k == 0);
        return;
    }
    if (!vis) dfs(d - 1, 0, 0);
    for (int i = !vis; i < a; i++) {
        if ((vis >> i) & 1) continue;
        dfs(d - 1, now * a + i, vis | (1 << i));
    }
}
int main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);

    scanf("%d%d%d", &a, &n, &k);
    if (!n) return printf("%d\n", k == 1), 0;
    if (n == 1) {
        for (int i = 1; i <= a; i++)
            if (i % k == 0) ans++;
        printf("%d\n", ans);
        return 0;
    }
    n = std::min(n, a);
    dfs(n, 0, 0);
    printf("%d\n", ans - 1);
    return 0;
}