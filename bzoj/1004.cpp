#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 61
int r, b, g, n, m, p, d[MAXN], ans;
int f[MAXN][MAXN][MAXN], vis[MAXN], len[MAXN], tot;
inline int calc() {
    memset(f, 0, sizeof(f));
    memset(vis, 0, sizeof(vis));
    tot = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            len[++tot] = 0;
            for (int j = i; !vis[j]; j = d[j]) len[tot]++, vis[j] = 1;
        }
    f[0][0][0] = 1;
    for (int i = 1; i <= tot; i++)
        for (int $1 = r; $1 >= 0; $1--)
            for (int $2 = g; $2 >= 0; $2--)
                for (int $3 = b; $3 >= 0; $3--) {
                    if ($1 - len[i] >= 0)
                        (f[$1][$2][$3] += f[$1 - len[i]][$2][$3]) %= p;
                    if ($2 - len[i] >= 0)
                        (f[$1][$2][$3] += f[$1][$2 - len[i]][$3]) %= p;
                    if ($3 - len[i] >= 0)
                        (f[$1][$2][$3] += f[$1][$2][$3 - len[i]]) %= p;
                }
    return f[r][g][b];
}
inline int fpow(int x, int f) {
    register int ret = 1;
    while (f) {
        if (f & 1) (ret *= x) %= p;
        (x *= x) %= p;
        f >>= 1;
    }
    return ret;
}
int main() {
    scanf("%d%d%d%d%d", &r, &b, &g, &m, &p);
    n = r + b + g;
    for (int i = 1; i <= n; i++) d[i] = i;
    (ans += calc()) %= p;
    for (int i = 0; i < m; i++) {
        for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
        (ans += calc()) %= p;
    }
    printf("%d\n", (ans * fpow(m + 1, p - 2)) % p);
    return 0;
}