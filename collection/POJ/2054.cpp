#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 500010
int n, vis[MAXN], fa[MAXN], head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
long long ans, c[MAXN], d[MAXN];
struct node {
    long long c, d;
    int id;
    inline friend bool operator<(const node &a, const node &b) {
        return a.c * b.d == a.d * b.c ? a.id < b.id : a.c * b.d < a.d * b.c;
    }
};
std::set<node> s;
int g[MAXN];
void dfs(int x) {
    if (g[x]) puts("-1"), exit(0);
    g[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) dfs(to[i]);
}

inline int find(int x) { return vis[x] ? fa[x] = find(fa[x]) : x; }
int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    c[0] = 0, d[0] = 1;
    for (int i = 1; i <= n; i++) scanf("%d", &fa[i]), $(fa[i], i);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        s.insert({c[i] = -x, d[i] = 1, i});
        ans += x;
    }
    for (int i = 0; i <= n; i++)
        if (!g[i]) dfs(i);
    for (int i = 1; i <= n; i++) {
        auto x = *s.rbegin();
        s.erase(x);
        vis[x.id] = 1;
        int y = find(x.id);
        ans += d[y] * c[x.id];
        if (y) s.erase({c[y], d[y], y});
        c[y] += c[x.id];
        d[y] += d[x.id];
        if (y) s.insert({c[y], d[y], y});
    }
    ans += c[0];
    printf("%lld\n", -ans);
    return 0;
}