#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define MAXN 100010
int n, p[MAXN], BIT[MAXN];
inline int $(int x) { return x & (-x); }
inline void $(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}
inline void add(int x, int p) {
    for (; x <= n; x += $(x)) $(BIT[x], p);
}
inline int qry(int x) {
    int ret = 0;
    for (; x; x -= $(x)) $(ret, BIT[x]);
    return ret;
}
int main() {
    scanf("%d", &n), n++;
    for (int i = 1; i < n; i++) scanf("%d", &p[i]);
    add(1, 1);
    for (int i = 2; i < n; i++) {
        if (p[i] < p[i - 1]) {
            int sum = qry(p[i]);
            memset(BIT, 0, sizeof(BIT));
            add(p[i - 1] + 1, sum);
        } else {
            int sum = qry(p[i]);
            add(p[i - 1] + 1, sum);
        }
    }
    printf("%d\n", qry(n) * 2 % MOD);
    return 0;
}