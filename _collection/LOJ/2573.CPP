#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 400010
int mul[MAXN], t, q, MOD;
void modify(int n, int l, int r, int p, int v) {
    if (l == r) return mul[n] = v, void();
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(n << 1, l, mid, p, v);
    else
        modify(n << 1 | 1, mid + 1, r, p, v);
    mul[n] = 1LL * mul[n << 1] * mul[n << 1 | 1] % MOD;
}
int main() {
    scanf("%d", &t);
    while (t--) {
        std::fill(mul, mul + MAXN, 1);
        scanf("%d%d", &q, &MOD);
        for (int i = 1; i <= q; i++) {
            int op, m;
            scanf("%d%d", &op, &m);
            if (op == 1) {
                modify(1, 1, q, i, m);
            } else {
                modify(1, 1, q, m, 1);
            }
            printf("%d\n", mul[1]);
        }
    }
    return 0;
}