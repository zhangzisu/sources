#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 510
int m, n, v[MAXN], vis[MAXN], match[MAXN];
bool can[MAXN][MAXN];
inline bool dfs(int x, int mid) {
    for (int i = 1; i <= n; i++) {
        if (!vis[i] && can[x][i] && v[i] < mid) {
            vis[i] = 1;
            if (!match[i] || dfs(match[i], mid)) {
                match[i] = x;
                return 1;
            }
        }
    }
    return 0;
}
inline bool check(int mid) {
    int sum = 0, all = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n; i++)
        if (v[i] < mid) {
            all++;
            memset(vis, 0, sizeof(vis));
            sum += dfs(i, mid);
        }
    return all - sum <= m + 1;
}
int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1, t; i <= n; i++) {
        scanf("%d", &v[i]);
        scanf("%d", &t);
        for (int j = 1, x; j <= t; j++) {
            scanf("%d", &x);
            can[i][x] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                can[i][j] |= can[i][k] && can[k][j];
    int l = 0, r = 1000000001, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    if (ans == 1000000001) return puts("AK"), 0;
    printf("%d\n", ans);
    return 0;
}