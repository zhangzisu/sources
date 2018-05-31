#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXN 30
#define MAXM 50

int n, m, head[MAXN], next[MAXN << 1], to[MAXN << 1], tot;
inline void $(int u, int v) {
    next[tot] = head[u];
    to[tot] = v;
    head[u] = tot++;
    next[tot] = head[v];
    to[tot] = u;
    head[v] = tot++;
}
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
std::bitset<MAXM> ans, res;
int w[MAXN];

void fuck(int x, int fa) {
    std::bitset<MAXM> ret(ans);
    ans <<= w[x];
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa || vis[to[i]]) continue;
        fuck(to[i], x);
    }
    ans |= ret;
    return;
}
void slove(int x) {
    gs(x, 0);
    vis[x] = 1;
    ans = std::bitset<MAXM>();
    ans[0] = 1;
    fuck(x, 0);
    res |= ans;
    for (int i = head[x]; ~i; i = next[i]) {
        if (vis[to[i]]) continue;
        root = 0;
        all = size[to[i]];
        gg(to[i], 0);
        slove(root);
    }
}
inline void init() {
    memset(head, -1, sizeof(head));
    res = std::bitset<MAXM>();
    tot = 0;
    memset(vis, 0, sizeof(vis));
    memset(size, 0, sizeof(size));
    memset(f, 0, sizeof(f));
    f[root = all = 0] = 0x3F3F3F3F;
}
int t;
int main() {
    scanf("%d", &t);
    while (t--) {
        init();
        scanf("%d%d", &n, &m);
        for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), $(u, v);
        for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
        all = n;
        gg(1, 0);
        slove(root);
        for (int i = 1; i <= m; i++) putchar(res[i] ? '1' : '0');
        putchar(10);
    }
    return 0;
}