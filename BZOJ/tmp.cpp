#include <cmath>
#include <cstdio>
#include <map>
#define N 50010
#define mod 1000000007
typedef long long ll;
struct data {
    int x, y, z;
    data() {}
    data(int a, int b, int c) { x = a, y = b, z = c; }
    bool operator<(const data &a) const { return x == a.x ? y == a.y ? z < a.z : y < a.y : x < a.x; }
};
std::map<data, ll> mp;
int head[N], to[N << 2], val[N << 2], opt[N << 2], next[N << 2], cnt, d[N], id[350], tot;
char str[5];
inline void add(int x, int y, int v, int c) {
    to[++cnt] = y, val[cnt] = v, opt[cnt] = c, next[cnt] = head[x], head[x] = cnt;
}
int main() {
    int n, m, si, i, j, k, x, y, z, t;
    ll ans = 0;
    scanf("%d%d", &n, &m), si = (int)sqrt(m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d%s", &x, &y, &z, str);
        t = (str[0] == 'R' ? 1 : str[0] == 'G' ? 2 : 3);
        add(x, y, z, t), add(y, x, z, t), d[x]++, d[y]++;
        (mp[data(x, y, t)] += z) %= mod, (mp[data(y, x, t)] += z) %= mod;
    }
    for (i = 1; i <= n; i++)
        if (d[i] >= si)
            id[++tot] = i;
    for (i = 1; i <= tot; i++)
        for (j = 1; j <= tot; j++)
            for (k = 1; k <= tot; k++)
                ans = (ans + mp[data(id[i], id[j], 1)] * mp[data(id[i], id[k], 2)] % mod * mp[data(id[j], id[k], 3)]) % mod;
    for (i = 1; i <= n; i++)
        if (d[i] < si)
            for (j = head[i]; j; j = next[j])
                if (d[to[j]] >= si || to[j] > i)
                    for (k = next[j]; k; k = next[k])
                        if (opt[k] != opt[j] && (d[to[k]] >= si || to[k] > i))
                            ans = (ans + mp[data(to[j], to[k], 6 - opt[j] - opt[k])] * val[j] % mod * val[k]) % mod;
    printf("%lld\n", ans);
    return 0;
}