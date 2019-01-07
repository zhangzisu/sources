#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 50010
#define MAXM 100010
#define MOD 1000000007
int head[MAXN], to[MAXM << 1], val[MAXM << 1], col[MAXM << 1], next[MAXM << 1], tot = 0;
inline void $(int u, int v, int w, int c) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, col[tot] = c, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, col[tot] = c, head[v] = tot++;
}
struct node {
    int u, v, c;
    inline node(int u = 0, int v = 0, int c = 0) : u(u), v(v), c(c) {}
    inline friend bool operator<(const node &a, const node &b) {
        if (a.u == b.u) return a.v == b.v ? a.c < b.c : a.v < b.v;
        return a.u < b.u;
    }
};
std::map<node, int> M;
int n, m, u, v, w, c, d[MAXN], vis[MAXN], id[MAXN], cnt, ans;
char buf[5];
inline int GetVal(node val) {
    if (M.count(val)) return M[val];
    return 0;
}
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%s", &u, &v, &w, buf);
        c = buf[0] == 'R' ? 0 : buf[0] == 'G' ? 1 : 2;
        $(u, v, w, c);
        d[u]++, d[v]++;
        (M[node(u, v, c)] += w) %= MOD;
        (M[node(v, u, c)] += w) %= MOD;
    }
    const int D = floor(sqrt(m));
    for (int i = 1; i <= n; i++)
        if (d[i] >= D) vis[id[++cnt] = i] = 1;
    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= cnt; j++)
            for (int k = 1; k <= cnt; k++)
                ans = (ans + 1LL * GetVal(node(id[i], id[j], 0)) * GetVal(node(id[j], id[k], 1)) % MOD * GetVal(node(id[k], id[i], 2)) % MOD) % MOD;
    for (int x = 1; x <= n; x++)
        if (!vis[x])
            for (int i = head[x]; ~i; i = next[i])
                if (vis[to[i]] || to[i] > x)
                    for (int j = next[i]; ~j; j = next[j])
                        if (col[j] != col[i] && (vis[to[j]] || to[j] > x))
                            ans = (ans + 1LL * GetVal(node(to[i], to[j], 3 - col[i] - col[j])) * val[i] % MOD * val[j] % MOD) % MOD;
    printf("%d\n", ans);
    return 0;
}