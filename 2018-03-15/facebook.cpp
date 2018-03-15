#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MOD 1000000007
#define MAXN 500010

long long n, m;
inline long long fuck(long long x, long long p) {
    long long y = 1;
    x %= MOD;
    while (p) {
        if (p & 1) y = y * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return y;
}
long long head[MAXN], to[MAXN << 3], next[MAXN << 3], d[MAXN], tot = 0;
inline void $(long long u, long long v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
    d[u]++, d[v]++;
}

std::vector<long long> cao;
long long dfn[MAXN], deep[MAXN], dfsclk;
void dfs(long long x, long long fa) {
    dfn[x] = ++dfsclk;
    for (long long i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        if (dfn[to[i]]) {
            if (deep[to[i]] < deep[x])
                cao.push_back(deep[x] - deep[to[i]] + 1);
            continue;
        }
        deep[to[i]] = deep[x] + 1;
        dfs(to[i], x);
    }
}

int main() {
#ifndef DEBUG
    freopen("facebook.in", "r", stdin);
    freopen("facebook.out", "w", stdout);
#endif
    memset(head, -1, sizeof(head));
    scanf("%lld%lld", &n, &m);
    for (long long i = 1; i <= m; i++) {
        long long u, v;
        scanf("%lld%lld", &u, &v);
        $(u, v);
    }

    for (long long i = 1; i <= n; i++)
        if (!dfn[i]) dfs(i, 0);

    long long ans = n * fuck(2, m) % MOD;
    (((ans -= m * fuck(2, m - 1) % MOD) %= MOD) += MOD) %= MOD;
    for(int i = 0;i < (int)cao.size();i++)
        (ans += fuck(2, m - cao[i])) %= MOD;
    for(int i = 1;i <= n;i++)
        (((ans -= fuck(2, m - d[i])) %= MOD) += MOD) %= MOD;

    printf("%lld\n", ans);
#ifndef DEBUG
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
