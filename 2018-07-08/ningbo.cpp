#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int n, m, p, f[12];
inline void up(int &x, int y) {
    if ((x += y) >= p) x -= p;
}
int main() {
    scanf("%d%d%d", &n, &m, &p);
    f[1] = 1;
    for (register int i = 1; i < n; i++) {
        for (register int j = m; j >= 1; j--) {
            if (!f[j]) continue;
            up(f[j + 1], 1LL * f[j] * (i + 1 - 2 * j) % p);
            f[j] = 2LL * f[j] * j % p;
        }
    }
    printf("%d\n", f[m]);
    return 0;
}