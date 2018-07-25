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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int op, x, y, z, w; m; m--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &x, &y);
            t = 0;
            for(int i = x;i <= y;i++)t ^= a[i];
            printf("%d\n", t);
        } else {
            scanf("%d%d%d", &x, &y, &z);
            for(int i = x;i <= y;i++)a[i] ^= z;
        }
        if (m % 100 == 0) fprintf(stderr, "Still have %d cases rest.\n", m);
    }
}