#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
typedef long long lnt;
int t, stk[20];
lnt l, r, f[20][4][20];
inline int trans(int p, int v) {
    if ((p == 0 || p == 1) && v == 0) return p + 1;
    if (p == 2 && v == 7) return p + 1;
    return p;
}
lnt calc(int d, int p, int g, bool flag) {
    if (d <= 0) return p == 3;
    if (!flag && f[d][p][g] != -1) return f[d][p][g];
    int limit = flag ? stk[d] : 9;
    lnt ans = 0;
    for (int i = 0; i <= limit; i++) {
        int nextp = (g || i) ? trans(p, i) : 0;
        int nextg = g ? g : i ? d : 0;
        ans += calc(d - 1, nextp, nextg, flag && i == limit);
    }
    if (!flag) f[d][p][g] = ans;
    return ans;
}
inline lnt calc(lnt limit) {
    int top = 0;
    for (; limit; limit /= 10) stk[++top] = limit % 10;
    return calc(top, 0, 0, 1);
}
int main() {
    lnt ans = 0;
    memset(f, -1, sizeof(f));
    for (scanf("%d", &t); t; t--) {
        scanf("%lld%lld", &l, &r);
        lnt tmp = calc(r) - calc(l - 1);
        // printf("// %lld\n", tmp);
        ans ^= tmp;
    }
    printf("%lld\n", ans);
}