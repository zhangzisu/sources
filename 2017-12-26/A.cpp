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
#define MAXN 200020
#define MOD 1000000007
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
long long frc[MAXN], inv[MAXN];
long long f[MAXN], ans = 0;
inline long long fpow(long long x, int p) {
    register long long ret = 1;
    while (p) {
        if (p & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return ret;
}
inline long long C(int n, int m) {
    return frc[n] * inv[m] % MOD * inv[n - m] % MOD;
}
inline long long insert(int x, int y) { return C(x + y, y); }
int size[MAXN];
void DP(int x, int fa) {
    f[x] = 1;
    size[x] = 0;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        DP(to[i], x);
        (f[x] *= insert(size[x], size[to[i]]) * f[to[i]] % MOD) %= MOD;
        size[x] += size[to[i]];
    }
    size[x]++;
}
void dp(int x, int fa) {
    (ans += f[x]) %= MOD;
    long long F = f[x], S = size[x], FF, SS;
    for (int i = head[x]; ~i; i = next[i]) {
        FF = f[to[i]];
        SS = size[to[i]];
        if (to[i] == fa) continue;
        (f[x] *=
         fpow(insert(size[x] - size[to[i]] - 1, size[to[i]]) * f[to[i]] % MOD,
              MOD - 2)) %= MOD;
        size[x] -= size[to[i]];
        (f[to[i]] *= insert(size[to[i]] - 1, size[x]) * f[x] % MOD) %= MOD;
        size[to[i]] += size[x];
        dp(to[i], x);
        f[to[i]] = FF;
        size[to[i]] = SS;
        f[x] = F;
        size[x] = S;
    }
}
int n = $();
int main() {
    memset(head, -1, sizeof(head));
    frc[0] = 1;
    for (int i = 1; i < MAXN; i++) frc[i] = frc[i - 1] * i % MOD;
    inv[MAXN - 1] = fpow(frc[MAXN - 1], MOD - 2);
    for (int i = MAXN - 1; i; i--) inv[i - 1] = inv[i] * i % MOD;
    for (int i = 1; i < n; i++) $($(), $());
    DP(1, 0);
    dp(1, 0);
    printf("%lld\n", ans);
    return 0;
}