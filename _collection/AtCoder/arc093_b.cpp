#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int a, b, n = 100, m = 100;
char buf[110][110];
int main() {
    memset(buf, '\0', sizeof(buf));
    scanf("%d%d", &a, &b);
    a--, b--;
    for (int i = 1; i <= n; i++) {
        buf[i][1] = '#';
        for (int j = 2; j < m; j++) {
            buf[i][j] = i & 1 ? '.' : '#';
        }
        buf[i][m] = '.';
    }
    for (int i = 1; i <= n; i += 2) {
        for (int j = 3; j < m; j += 2) {
            if (a) buf[i][j] = '#', a--;
        }
    }
    for (int i = n; i >= 1; i -= 2) {
        for (int j = m - 2; j > 1; j -= 2) {
            if (b) buf[i][j] = '.', b--;
        }
    }
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++) puts(buf[i] + 1);
    return 0;
}