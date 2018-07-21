#include <cstdio>
int n, m, a[100010];
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    while (m--) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            scanf("%d", &op);
            for (int i = l; i <= r; i++) a[i] += op;
        } else {
            int ans = a[l];
            for (int i = l + 1; i <= r; i++) ans = gcd(ans, a[i]);
            printf("%d\n", ans);
        }
    }
}