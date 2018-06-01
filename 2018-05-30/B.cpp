#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
typedef long long lnt;
int t, n, m, k, q, ban[MAXN][MAXN];
lnt sum[MAXN][MAXN];
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%d", &n, &m, &k, &q);
        memset(ban, 0, sizeof(ban));
        for (int i = 1, x, y; i <= k; i++) {
            scanf("%d%d", &x, &y);
            ban[x][y] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum[i][j] = sum[i][j - 1] + ban[i][j];
            }
        }
        for (int _ = 1, x, y; _ <= q; _++) {
            scanf("%d%d", &x, &y);
            if (ban[x][y]) {
                puts("0");
                continue;
            }
            int upper = y, lower = y;
            while (upper < m && !ban[x][upper + 1]) upper++;
            while (lower > 1 && !ban[x][lower - 1]) lower--;
            int cur0 = upper, cur1 = lower;
            lnt ans = upper - lower + 1;
            for (int i = x - 1; i >= 1; i--) {
                while (sum[i][cur0] - sum[i][y - 1]) cur0--;
                if (cur0 < y) break;
                while (sum[i][y] - sum[i][cur1 - 1]) cur1++;
                if (cur1 > y) break;
                if (cur0 < cur1) break;
                ans += cur0 - cur1 + 1;
            }
            cur0 = upper, cur1 = lower;
            for (int i = x + 1; i <= n; i++) {
                while (sum[i][cur0] - sum[i][y - 1]) cur0--;
                if (cur0 < y) break;
                while (sum[i][y] - sum[i][cur1 - 1]) cur1++;
                if (cur1 > y) break;
                if (cur0 < cur1) break;
                ans += cur0 - cur1 + 1;
            }
            printf("%lld\n", ans);
        }
    }
}