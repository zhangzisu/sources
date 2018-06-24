#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010

int n, k, q, x[MAXN], l[MAXN][18], r[MAXN][18];
int stk[MAXN], top;

int main() {
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
    stk[top = 0] = 1;
    for (int i = 1; i <= n; i++) {
        while (top && x[stk[top]] < x[i]) top--;
        l[i][0] = stk[top];
        stk[++top] = i;
    }
    stk[top = 0] = n;
    for (int i = n; i >= 1; i--) {
        while (top && x[stk[top]] < x[i]) top--;
        r[i][0] = stk[top];
        stk[++top] = i;
    }
    for (int d = 1; d < 18; d++)
        for (int i = 1; i <= n; i++) {
            l[i][d] = std::min(l[l[i][d - 1]][d - 1], l[r[i][d - 1]][d - 1]);
            r[i][d] = std::max(r[r[i][d - 1]][d - 1], r[l[i][d - 1]][d - 1]);
        }
    // for (int i = 1; i <= n; i++) printf("%d\t%d\n", l[i][0], r[i][0]);
    while (q--) {
        int x, y, L, R, ans = 0;
        scanf("%d%d", &x, &y);
        if (x > y) std::swap(x, y);
        L = R = x;
        for (int i = 17; ~i; i--) {
            int ll = std::min(l[L][i], l[R][i]);
            int rr = std::max(r[L][i], r[R][i]);
            if (rr < y) L = ll, R = rr, ans += 1 << i;
        }
        x = R;
        L = R = y;
        for (int i = 17; ~i; i--) {
            int ll = std::min(l[L][i], l[R][i]);
            int rr = std::max(r[L][i], r[R][i]);
            if (ll > x) L = ll, R = rr, ans += 1 << i;
        }
        printf("%d\n", ans);
    }
    return 0;
}
