#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 160

int n, m, f[MAXN][MAXN][MAXN], ok[MAXN][MAXN], len[MAXN], ans[MAXN], bit[MAXN];
char buf[MAXN], s[MAXN][MAXN];
int main() {
    scanf("%s", buf + 1);
    n = strlen(buf + 1);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s", s[i] + 1);
        len[i] = strlen(s[i] + 1);
    }
    for (int i = 0; i < MAXN; i++) bit[i] = 1 << i;
    for (int i = n; i; i--) {
        for (int j = i; j <= n; j++) {
            if (i == j) {
                for (int k = 1; k <= m; k++) {
                    f[i][j][k] = buf[i] == s[k][1];
                    ok[i][j] |= bool(f[i][j][k] & bit[len[k] - 1]);
                }
            } else {
                for (int k = 1; k <= m; k++) {
                    for (int l = 2; l <= len[k]; l++) {
                        if ((f[i][j - 1][k] & bit[l - 2]) && (buf[j] == s[k][l]))
                            f[i][j][k] |= bit[l - 1];
                    }
                    for (int l = i; l < j; l++)
                        if (ok[l + 1][j]) f[i][j][k] |= f[i][l][k];
                    ok[i][j] |= bool(f[i][j][k] & bit[len[k] - 1]);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        ans[i] = ans[i - 1] + 1;
        for (int j = 1; j <= i; j++)
            if (ok[j][i]) ans[i] = std::min(ans[i], ans[j - 1]);
    }
    printf("%d\n", ans[n]);
    return 0;
}