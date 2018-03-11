#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int $() {
    register int x = 0, f = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    if (!(ch ^ 45)) ch = gc(), f = 1;
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
}
#define MAXN 110000
int head[MAXN], fa[MAXN], next[MAXN << 1], to[MAXN << 1], val[MAXN << 1], tot,
    n, q;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
long long f[MAXN], deep[MAXN], ans;
long long A(int x, int y) {
    return f[x] + deep[x] * deep[x] - f[y] - deep[y] * deep[y];
}
long long B(int x, int y) { return deep[x] - deep[y]; }
int Q[MAXN];
void DP(int x, int H, int T) {
    while (H < T && A(Q[H + 1], Q[H]) <= 2 * deep[x] * B(Q[H + 1], Q[H])) H++;
    f[x] = f[Q[H]] + (deep[x] - deep[Q[H]]) * (deep[x] - deep[Q[H]]) + q;
    while (H < T &&
           A(x, Q[T]) * B(Q[T - 1], Q[T]) > A(Q[T - 1], Q[T]) * B(x, Q[T]))
        T--;
    int bak = Q[T + 1];
    Q[++T] = x;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x]) {
            fa[to[i]] = x;
            deep[to[i]] = deep[x] + val[i];
            DP(to[i], H, T);
        }
    Q[T] = bak;
    ans = std::max(f[x], ans);
}
int main() {
    int t = $();
    while (t--) {
        n = $(), q = $();
        memset(head, -1, sizeof(head));
        memset(f, 0, sizeof(head));
        tot = 0;
        for (int i = 1; i < n; i++) {
            int $1 = $(), $2 = $(), $3 = $();
            $($1, $2, $3);
        }
        deep[1] = ans = 0;
        f[Q[0] = 0] = -q;
        DP(1, 0, 0);
        printf("%lld\n", ans);
    }
    return 0;
}