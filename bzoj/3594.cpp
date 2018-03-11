#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
#define MAXM 510
int n, k, a[MAXN], f[MAXN][MAXM], sum[MAXN][MAXM], ans = 1;
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y, int v) {
    for (int i = x; i < MAXN; i += lowbit(i))
        for (int j = y; j < MAXM; j += lowbit(j))
            sum[i][j] = std::max(sum[i][j], v);
}
inline int qry(int x, int y) {
    int ret = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            ret = std::max(ret, sum[i][j]);
    return ret;
}
int main() {
    scanf("%d%d", &n, &k), k++;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = k; j; j--) {
            f[i][j] = qry(a[i] + j, j) + 1;
            ans = std::max(ans, f[i][j]);
            add(a[i] + j, j, f[i][j]);
        }
    }
    printf("%d\n", ans);
    return 0;
}