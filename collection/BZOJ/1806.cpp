#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, f[2][16][16];
char buf[MAXN];
inline void up(int &x, int y) {
    if (y > x) x = y;
}
inline int calc(int pre, int now) {
    int pre1 = pre >> 2, pre2 = pre & 3, ret = 1;
    if (pre1 && pre1 != now) ret++;
    if (pre2 && pre2 != now && pre2 != pre1) ret++;
    return ret;
}
int main() {
    scanf("%d%s", &n, buf + 1);
    if (n <= 2) {
        printf("%d\n", n);
        return 0;
    }
    memset(f, -1, sizeof(f));
    f[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        const int now = i & 1, pre = now ^ 1;
        int d = buf[i] == 'M' ? 1 : (buf[i] == 'F' ? 2 : 3);
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                if (f[pre][j][k] == -1) continue;
                up(f[now][((j << 2) + d) & 15][k], f[pre][j][k] + calc(j, d));
                up(f[now][j][((k << 2) + d) & 15], f[pre][j][k] + calc(k, d));
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++) ans = std::max(ans, f[n & 1][i][j]);
    printf("%d\n", ans);
    return 0;
}