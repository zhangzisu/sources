#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 100010
int n, MOD, k, K, r, w[MAXN];
inline int fuck(int x, int p) {
    int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int head[MAXN], next[MAXN << 1], to[MAXN << 1], tot = 0;
inline void addEdge(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int end[MAXN], start[MAXN];
void dfs(int x, int fa, int deep, int val0, int val1) {
    val0 = (val0 + 1LL * w[x] * fuck(k, deep)) % MOD;
    val1 = (val1 + 1LL * w[x] * fuck(K, deep)) % MOD;
    if (val0 == r) end[x]++;
    if (1LL * val1 * fuck(k, deep) % MOD == r) start[x]++;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dfs(to[i], x, deep + 1, val0, val1);
    }
}
namespace K1 {
int vis[MAXN], size[MAXN], f[MAXN], root, all;
void gs(int x, int fa) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (vis[to[i]] || to[i] == fa) continue;
        gs(to[i], x);
        size[x] += size[to[i]];
    }
}
void gg(int x, int fa) {
    size[x] = 1;
    f[x] = 0;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa || vis[to[i]]) continue;
        gg(to[i], x);
        size[x] += size[to[i]];
        f[x] = std::max(f[x], size[to[i]]);
    }
    f[x] = std::max(f[x], all - size[x]);
    if (f[x] < f[root]) root = x;
}
std::map<int, int> M[MAXN];
int ddd[MAXN];
void dfs(int x, int fa, int val, int deep, int origin) {
    val = (val + w[x]) % MOD;
    M[0][val]++;
    M[origin][val]++;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa || vis[to[i]]) continue;
        dfs(to[i], x, val, deep + 1, origin);
    }
}
void fsd(int x, int fa, int val, int deep, int origin) {
    val = (val + w[x]) % MOD;
    ddd[x] += M[0][(r - val + MOD) % MOD] - M[origin][(r - val + MOD) % MOD];
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa || vis[to[i]]) continue;
        fsd(to[i], x, val, deep + 1, origin);
    }
}
void slove(int x) {
    gs(x, 0);
    vis[x] = 1;
    M[0].clear();
    M[0][w[x]] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (vis[to[i]]) continue;
        M[to[i]].clear();
        dfs(to[i], x, w[x], 1, to[i]);
    }
    ddd[x] += M[0][r];
    for (int i = head[x]; ~i; i = next[i]) {
        if (vis[to[i]]) continue;
        fsd(to[i], x, 0, 1, to[i]);
    }
    for (int i = head[x]; ~i; i = next[i]) {
        if (vis[to[i]]) continue;
        root = 0;
        all = size[to[i]];
        gg(to[i], 0);
        slove(root);
    }
}
void solve() {
    f[0] = 0x7FFFFFFF;
    all = n;
    gs(1, 0);
    gg(1, 0);
    slove(root);
    long long ans = 1LL * n * n * n;
    for (int i = 1; i <= n; i++) ans -= 1LL * ddd[i] * n * 3;
    for (int i = 1; i <= n; i++) ans += 1LL * ddd[i] * ddd[i] * 3;
    printf("%lld\n", ans);
}
}  // namespace K1
int main() {
    freopen("gu.in", "r", stdin);
    freopen("gu.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &MOD, &k, &r);
    K = fuck(k, MOD - 2);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        addEdge(u, v);
    }
    if (k == 1) return K1::solve(), 0;
    for (int i = 1; i <= n; i++) dfs(i, 0, 0, 0, 0);
    // for (int i = 1; i <= n; i++) printf("%d %d\n", start[i], end[i]);
    // puts("");
    long long ans = 1LL * n * n * n;
    for (int i = 1; i <= n; i++) ans -= 1LL * end[i] * n * 3;
    for (int i = 1; i <= n; i++) ans += 1LL * start[i] * start[i];
    for (int i = 1; i <= n; i++) ans += 1LL * end[i] * end[i];
    for (int i = 1; i <= n; i++) ans += 1LL * end[i] * start[i];
    printf("%lld\n", ans);
}