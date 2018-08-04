#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 100010
#define MOD 998244353
inline int fuck(int x, int p) {
    register int y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = 1LL * y * x % MOD;
        x = 1LL * x * x % MOD;
    }
    return y;
}
int t, n, k, ans, all, size[MAXN];
int head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline void down(int &x, int y) {
    if ((x -= y) < 0) x += MOD;
}
int frc[MAXN], inv[MAXN];
inline int C(int n, int m) {
    if (m > n) return 0;
    return 1LL * frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
void prepare(int x, int fa) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        prepare(to[i], x);
        int tmp = all;
        down(tmp, C(size[to[i]], k));
        down(tmp, C(n - size[to[i]], k));
        up(ans, 2LL * val[i] * tmp % MOD);
        size[x] += size[to[i]];
    }
}
int main() {
#ifndef DEBUG
    freopen("blink.in", "r", stdin);
    freopen("blink.out", "w", stdout);
#endif
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = 1LL * frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fuck(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = 1LL * inv[i] * i % MOD;

    for (t = $(); t; t--) {
        n = $(), k = $();
        memset(head, -1, sizeof(head));
        tot = ans = 0, all = C(n, k);
        for (int i = 1, u, v, w; i < n; i++) {
            u = $(), v = $(), w = $();
            $(u, v, w);
        }
        prepare(1, 0);
        printf("%lld\n", 1LL * ans * fuck(C(n, k), MOD - 2) % MOD);
    }
    return 0;
}