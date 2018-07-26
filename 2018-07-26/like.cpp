#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 310
#define MAXM 40
#define MOD 1000000007
typedef long long lnt;
int n, m, len[MAXM], f[MAXN][2], ans;
lnt str[MAXM];
char buf[MAXM];
inline void up(int& x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int main() {
    freopen("like.in", "r", stdin);
    freopen("like.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s", buf + 1);
        len[i] = strlen(buf + 1);
        for (int j = 1; j <= len[i]; j++) {
            str[i] |= ((buf[j] == '1') << (j - 1));
        }
    }
    int limit = (n + 1) / 2;
    for (int i = 0; i < (1 << limit); i++) {
        lnt val = i;
        for (int i = limit; i < n; i++) {
            val |= (((val >> (n - i - 1)) & 1) << i);
        }
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int i = 0; i < n; i++) {
            f[i][0] |= i && f[i - 1][0];
            f[i][1] |= i && f[i - 1][1];
            int llen = n - i, now = val >> i;
            for (int j = 0; j < 2; j++) {
                if (!f[i][j]) continue;
                for (int k = 1; k <= m; k++) {
                    if (len[k] > llen) continue;
                    if ((now ^ ((now >> len[k]) << len[k])) == str[k]) {
                        if (j == 1) goto fail;
                        f[i + len[k]][1] = 1;
                    }
                }
            }
        }
        up(ans, 1);
        // printf("%lld\n", val);
    fail:;
    }
    printf("%d\n", ans);
    return 0;
}