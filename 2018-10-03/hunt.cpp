#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#include <queue>
#define MAXN 1000010
int head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int n, m, opt, vis[MAXN];
std::queue<int> Q;
inline void d(int s) {
    vis[s] = 1;
    Q.push(s);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = head[x]; ~i; i = next[i]) {
            if (vis[to[i]]) continue;
            vis[to[i]] = 1;
            Q.push(to[i]);
        }
    }
}
int main() {
    freopen("hunt.in", "r", stdin);
    freopen("hunt.out", "w", stdout);

    memset(head, -1, sizeof(head));
    n = $(), m = $(), opt = $();
    for (int u, v; m; m--) u = $(), v = $(), $(v, u);
    d($());
    int c = 0;
    for (int i = 1; i <= n; i++) c += vis[i];
    int g = gcd(c, n);
    printf("%d/%d\n", c / g, n / g);
    if (opt) {
        for (int i = 1; i <= n; i++)
            if (vis[i]) printf("%d ", i);
        puts("");
    }
    return 0;
}