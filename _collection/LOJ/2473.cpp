#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1667
#define MOD 64123
int n, k, w, d[MAXN], v[MAXN], ans;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
inline void upd(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int f[MAXN][MAXN];
void dp(int x, int fa) {
    for (int i = 0; i <= k; i++) {
        upd(f[x][i + v[x]], f[fa][i]);
    }
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dp(to[i], x);
    }
    for (int i = 0; i <= k; i++) {
        upd(f[fa][i], f[x][i]);
    }
}
inline int dp(int x) {
    int all = 0;
    for (int i = 1; i <= n; i++) {
        all += (v[i] = (d[i] > d[x] || (d[i] == d[x] && i <= x)));
    }
    if (all < k) return 0;
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    dp(x, 0);
    return f[x][k];
}
int main() {
    scanf("%d%d%d", &n, &k, &w);
    for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        $(u, v);
    }
    for (int i = 1; i <= n; i++)
        upd(ans, dp(i) * d[i] % MOD);
    printf("%d\n", ans);
    return 0;
}