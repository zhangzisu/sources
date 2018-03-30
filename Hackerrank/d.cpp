#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
int t, n, m, f[MAXN][MAXN];
char a[MAXN], b[MAXN];
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%s%s", a + 1, b + 1);
        n = strlen(a + 1);
        m = strlen(b + 1);
        memset(f, 0x80, sizeof(f));
        for (int i = 0; i <= n; i++)
            if (!i || islower(a[i])) f[i][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (islower(a[i])) {
                    f[i][j] = f[i - 1][j];
                    if (a[i] - 'a' + 'A' == b[j]) f[i][j] = std::max(f[i][j], f[i - 1][j - 1] + 1);
                } else {
                    if (a[i] == b[j]) f[i][j] = std::max(f[i][j], f[i - 1][j - 1] + 1);
                }
            }
        }
        puts(f[n][m] == m ? "YES" : "NO");
    }
    return 0;
}
