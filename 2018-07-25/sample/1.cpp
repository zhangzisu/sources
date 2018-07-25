#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#define MAXN 100010
int n, m, a[MAXN], b[MAXN], p, t;
inline int fuck(int x, int y) {
    register int z = 1;
    for (; y; y >>= 1) {
        if (y & 1) z = 1LL * z * x % p;
        x = 1LL * x * x % p;
    }
    return z;
}
int main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 0; i <= n; i++) scanf("%d", &a[i]);
    for (int op, x, y, z, w; m; m--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &x);
            t = 0;
            for (int i = 0; i <= n; i++) {
                (t += 1LL * a[i] * fuck(x, i) % p) %= p;
            }
            printf("%d\n", t);
        } else {
            scanf("%d%d", &x, &y);
            a[x] = y;
        }
        if (m % 100 == 0) fprintf(stderr, "Still have %d cases rest.\n", m);
    }
}