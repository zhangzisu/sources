#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
int T, b, n, m, t[50], x[50], y[50], z[50], l, r, ans;
inline int judge(int x) {
    static int tmp[50];
    memset(tmp, 0, sizeof(tmp));
    while (x) tmp[x % b]++, x /= b;
    for (int i = 0; i < b; i++)
        if (tmp[i] == t[i]) return 0;
    return 1;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &b, &n, &m);
        for (int i = 0; i < b; i++) scanf("%d", &t[i]);
        for (int i = 0; i < n; i++) scanf("%d", &x[i]);
        for (int i = 0; i < m; i++) scanf("%d", &y[i]);
            l = r = ans = 0;
            for (int i = n - 1; ~i; i--) l = l * b + x[i];
            for (int i = m - 1; ~i; i--) r = r * b + y[i];
            for (int i = l; i <= r; i++) ans += judge(i);
            printf("%d\n", ans);
    }
    return 0;
}