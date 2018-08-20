#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 40
const int INF = 0x3F3F3F3F;
int t, n, m, ans, a[MAXN], table[2000][2000];
char buf[MAXN];
inline void up(int &x, int y) {
    if (x > y) x = y;
}
inline int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
// out -> [1, 10, diff]
inline void gl(int *a, int len) {
    for (int d = 0; d < (1 << len); d++) {
        int f = 1, g = 0, k = 0;
        for (int j = 0; j < len; j++) {
            k += a[j] != ((d >> j) & 1);
            if ((d >> j) & 1) {
                f += g + 1;
            } else {
                g += f;
            }
        }
        up(table[f][g + 1], k);
    }
}
// out -> [0, 10, diff]
inline void gr(int *a, int len) {
    for (int d = 0; d < (1 << len); d++) {
        int f = 1, g = 0, k = 0;
        for (int j = len - 1; ~j; j--) {
            k += a[j] != ((d >> j) & 1);
            if ((d >> j) & 1) {
                g += f;
            } else {
                f += g + 1;
            }
        }
        int x, y, z = exgcd(f, g + 1, x, y);
        if (m % z) continue;
        x = 1LL * x * m % (g + 1) / z;
        if (x < 0) x += g + 1;
        for (; x < 2000; x += (g + 1) / z) {
            if ((m - x * f) / (g + 1) < 2000)
                up(ans, k + table[x][(m - x * f) / (g + 1)]);
        }
    }
}
int main() {
    for (scanf("%d", &t); t; t--) {
        memset(table, 0x3F, sizeof(table));
        scanf("%s", buf + 1);
        n = strlen(buf + 1);
        scanf("%d", &m);
        m++;
        for (int i = 1; i <= n; i++) a[i] = buf[i] == '1';
        ans = INF;
        gl(a + 2, n / 2 - 1);
        gr(a + n / 2 + 1, n - n / 2 - 1);
        if (ans == INF) {
            puts("NO");
        } else {
            puts("YES");
            printf("%d\n", ans);
        }
    }
    return 0;
}