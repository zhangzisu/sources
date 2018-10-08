#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define BUF 1048576
#define MOD 1000000007
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
inline long long $$() {
    register long long x = 0;
    register char ch = gc();
    while (!isdigit(ch)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 100010
#define MAXM 400010
int head[MAXN], to[MAXM], next[MAXM], tot = 0, cnt = 0;
long long val[MAXM], dis[MAXN], cir[3000000], base[70], p2[70], ans = 0, cn1;
bool vis[MAXN];
int stk[MAXN], top;
void dfs(int x, int fa, long long now) {
    if (vis[x]) return void(cir[++cnt] = dis[x] ^ now);
    vis[x] = 1;
    dis[x] = now;
    stk[++top] = x;
    for (int i = head[x]; ~i; i = next[i])
        if (i != (fa ^ 1)) dfs(to[i], i, now ^ val[i]);
}
inline void $(int u, int v, long long w) { next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++, next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++; }
inline void insert(long long x) {
    for (int i = 62; ~i; i--) {
        if (!(x >> i)) continue;
        if (!base[i]) {
            base[i] = x;
            break;

        } else {
            x ^= base[i];
        }
    }
}
inline void liner_base() {
    memset(base, 0, sizeof(base));
    cn1 = 0;
    for (int i = 1; i <= cnt; i++) {
        insert(cir[i]);
    }
    for (int i = 0; i <= 62; i++)
        if (base[i]) cn1++;
}
inline long long calc() {
    liner_base();
    long long ret = 0, c1, c0;
    for (int d = 0; d <= 62; d++) {
        bool sb = 1;
        for (int i = 0; i <= 62; i++)
            if ((base[i] >> d) & 1) {
                sb = 0;
                break;
            }
        c0 = c1 = 0;
        for (int i = 1; i <= top; i++)
            if ((dis[stk[i]] >> d) & 1)
                c1++;
            else
                c0++;
        long long now = (c1 * (c1 - 1) / 2 % MOD + c0 * (c0 - 1) / 2 % MOD) % MOD;
        if (!sb) {
            if (cn1) (now *= p2[cn1 - 1]) %= MOD;
            (now *= p2[d]) %= MOD;
            (ret += now) %= MOD;
        }
        now = c1 * c0 % MOD;
        if (sb) {
            (now *= p2[cn1]) %= MOD;

        } else {
            if (cn1) (now *= p2[cn1 - 1]) %= MOD;
        }
        (now *= p2[d]) %= MOD;
        (ret += now) %= MOD;
    }
    return ret;
}
int main() {
    p2[0] = 1;
    for (int i = 1; i <= 62; i++) p2[i] = (p2[i - 1] << 1) % MOD;
    int n = $(), m = $();
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) {
        int u = $(), v = $();
        long long w = $$();
        $(u, v, w);
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        cnt = top = 0;
        dfs(i, -1, 0);
        (ans += calc()) %= MOD;
    }
    printf("%lld\n", ans);
    return 0;
}