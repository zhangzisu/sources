#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010

#define MOD 6
inline int fuck(int x, int p) {
    register int y = 1;
    while (p) {
        if (p & 1) y = y * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return y;
}
int t, n, m;
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) { next[tot] = head[u], to[tot] = v, head[u] = tot++; }
int vis[MAXN], deep[MAXN], flag = 0, len = -1;
void dfs(int x, int fa) {
    vis[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        if (vis[to[i]]) {
            len = deep[x] - deep[to[i]] + 1;
            flag = 1;
            return;
        }
        deep[to[i]] = deep[x] + 1;
        dfs(to[i], x);
        if (flag) return;
    }
}
int pag = 0;
inline void reset() {
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    tot = flag = pag = 0;
}
bool ddd(int x, int fa, int col) {
    if (vis[x]) return vis[x] == col;
    vis[x] = col;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        if (ddd(to[i], x, col)) return 1;
    }
    return 0;
}
inline bool judge() {
    for (int i = 1; i <= n; i++) {
        if (!vis[i] && ddd(i, 0, ++pag)) return 0;
    }
    return 1;
}
int u[MAXN], v[MAXN];
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        if (m == n - 1) {
            for (int i = 1; i <= m; i++) scanf("%*d%*d");
            printf("%d\n", fuck(2, m));
            continue;
        } else if (m == n) {
            for (int i = 1, u, v; i <= m; i++) {
                scanf("%d%d", &u, &v);
                $(u, v);
                $(v, u);
            }
            deep[1] = 0;
            dfs(1, 0);
            printf("%d\n", ((fuck(2, m) - fuck(2, n - len) * 2) % 6 + 6) % 6);
        } else {
            for (int i = 1; i <= m; i++) scanf("%d%d", &u[i], &v[i]);
            int ans = 0;
            for (int i = 0; i < (1 << m); i++) {
                reset();
                for (int j = 1; j <= m; j++) {
                    if ((i >> (j - 1)) & 1)
                        $(u[j], v[j]);
                    else
                        $(v[j], u[j]);
                }
                if (judge()) ans++;
                if (ans >= 6) ans = 0;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}