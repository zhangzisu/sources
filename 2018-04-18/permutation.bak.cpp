#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, ans;
int vis[10], stk[10];
void dfs(int x) {
    if (x > n) {
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                if (stk[i] > j && stk[j] > i) return;

        //for (int i = 1; i <= n; i++) printf("%d%c", stk[i], " \n"[i == n]);
        ans++;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vis[i] = 1;
        stk[x] = i;
        dfs(x + 1);
        vis[i] = 0;
    }
}
inline int frac(int x) {
    int y = 1;
    for (int i = 2; i <= x; i++) y *= i;
    return y;
}
int main() {
    scanf("%d", &n);
    dfs(1);
    //printf("TOTAL BAD   : %d\n", ans);
    printf("TOTAL GOOD  : %d\n", frac(n) - ans);
    return 0;
}

//0,0,1,12,91,650,4871,39912,361895,