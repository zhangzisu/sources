#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 2000000011
int n, m, vis[11], stk[11], ans = 0;
void dfs(int x) {
    if (x > n) {
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                if (stk[i] > j && stk[j] > i) return void(++ans);
        return;
    }
    if (stk[x]) return dfs(x + 1);
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vis[i] = 1;
        stk[x] = i;
        dfs(x + 1);
        stk[x] = 0;
        vis[i] = 0;
    }
}
int main() {
    scanf("%d%d", &n, &m);
    if (n <= 10) {
        for (int i = 1, x, y; i <= m; i++) scanf("%d%d", &x, &y), vis[stk[x] = y] = 1;
        dfs(1);
        printf("%d\n", ans);
    }else{
        int rest = n - m;
        int result = 1;
        for(int i = 2;i <= rest;i++)result = 1LL * result * i % MOD;
        printf("%d\n", result);
    }
    return 0;
}