#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
#define MOD 1000000007
int t, n, f[MAXN][2][2][2][2];
char buf[MAXN];
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int main() {
#ifndef DEBUG
    freopen("mine.in", "r", stdin);
    freopen("mine.out", "w", stdout);
#endif
    for (scanf("%d", &t); t; t--) {
        scanf("%s", buf + 1);
        n = strlen(buf + 1);
        memset(f, 0, sizeof(f));
        f[1][0][0][0][0] = f[1][0][1][0][0] = f[1][0][0][0][1] = f[1][0][1][0][1] = 1;
        for (int i = 1; i < n; i++) {
            int cur = buf[i] ^ 48;
            for (int i0 = 0; i0 < 2; i0++) {
                for (int i1 = 0; i1 < 2; i1++) {
                    for (int j0 = 0; j0 < 2; j0++) {
                        for (int j1 = 0; j1 < 2; j1++) {
                            int &F = f[i][i0][i1][j0][j1];
                            if (!F) continue;
                            int nxt = cur - i0 - i1 - j0 - j1;
                            switch (nxt) {
                                case 0:
                                    up(f[i + 1][i1][0][j1][0], F);
                                    break;
                                case 1:
                                    up(f[i + 1][i1][1][j1][0], F);
                                    up(f[i + 1][i1][0][j1][1], F);
                                    break;
                                case 2:
                                    up(f[i + 1][i1][1][j1][1], F);
                                    break;
                            }
                        }
                    }
                }
            }
        }
        int ans = 0, last = buf[n] ^ 48;
        for (int i0 = 0; i0 < 2; i0++) {
            for (int i1 = 0; i1 < 2; i1++) {
                for (int j0 = 0; j0 < 2; j0++) {
                    for (int j1 = 0; j1 < 2; j1++) {
                        if (i0 + j0 + i1 + j1 == last) up(ans, f[n][i0][i1][j0][j1]);
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}