#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int a[50], stk[5000], n, m, ans;
void dfs(int deep) {
    if (deep >= m) {
        int len = 1, tmp = 1;
        for (int i = 1; i < deep; i++) {
            if (stk[i] != stk[i - 1]) {
                tmp = 1LL * tmp * len % MOD;
                len = 1;
            } else {
                len++;
            }
        }
        tmp = 1LL * tmp * len % MOD;
        up(ans, tmp);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!a[i]) continue;
        a[i]--;
        stk[deep] = i;
        dfs(deep + 1);
        a[i]++;
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]), m += a[i];
    dfs(0);
    printf("%d\n", ans);
    return 0;
}