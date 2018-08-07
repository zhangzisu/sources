#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 100010
#define MOD 1000000007
typedef long long lnt;
lnt m, k, id[MAXN], delta[MAXN];
struct path_t {
    lnt sx, sy, tx, ty;
    inline friend bool operator<(const path_t &a, const path_t &b) {
        return a.tx < b.tx;
    }
} p[MAXN];
inline lnt fuck(lnt x, lnt p) {
    lnt y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = y * x % MOD;
        x = x * x % MOD;
    }
    return y;
}
long long n;
inline void up(lnt &x, lnt y) {
    if ((x += y) >= MOD) x -= MOD;
}
std::vector<lnt> xv, yv;
lnt bit[MAXN], cx, cy;
inline lnt lowbit(lnt x) { return x & -x; }
inline void add(lnt x, lnt y) {
    for (; x <= cx; x += lowbit(x)) up(bit[x], y);
}
inline lnt qry(lnt x) {
    lnt y = 0;
    for (; x; x -= lowbit(x)) up(y, bit[x]);
    return y;
}
lnt pool_size, pool[MAXN];
std::map<std::pair<lnt, lnt>, lnt> M;
int main() {
    freopen("paths.in", "r", stdin);
    freopen("paths.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    for (lnt i = 1; i <= k; i++) {
        scanf("%lld%lld%lld%lld", &p[i].sx, &p[i].sy, &p[i].tx, &p[i].ty);
        xv.push_back(p[i].sx);
        yv.push_back(p[i].sy);
        xv.push_back(p[i].tx);
        yv.push_back(p[i].ty);
    }
    xv.push_back(-1);
    yv.push_back(-1);
    std::sort(xv.begin(), xv.end());
    xv.erase(std::unique(xv.begin(), xv.end()), xv.end());
    cx = xv.size();
    std::sort(yv.begin(), yv.end());
    yv.erase(std::unique(yv.begin(), yv.end()), yv.end());
    cy = yv.size();
    for (lnt i = 1; i <= k; i++) {
        p[i].sx = std::lower_bound(xv.begin(), xv.end(), p[i].sx) - xv.begin();
        p[i].sy = std::lower_bound(yv.begin(), yv.end(), p[i].sy) - yv.begin();
        p[i].tx = std::lower_bound(xv.begin(), xv.end(), p[i].tx) - xv.begin();
        p[i].ty = std::lower_bound(yv.begin(), yv.end(), p[i].ty) - yv.begin();
    }
    std::sort(p + 1, p + k + 1);
    for (lnt i = 1; i <= k; i++) {
        lnt count = (xv[p[i].sx] == 0) ? 1 : fuck(m, xv[p[i].sx] - 1);
        if (M.count(std::make_pair(p[i].sx, p[i].sy)))
            up(count, pool[M[std::make_pair(p[i].sx, p[i].sy)]]);
        lnt tmp = qry(p[i].sx - 1);
        up(count, tmp * fuck(m, xv[p[i].sx]) % MOD);
        delta[i] = count;
        add(p[i].tx, delta[i] * fuck(fuck(m, xv[p[i].tx] + 1), MOD - 2) % MOD);
        lnt &pos = M[std::make_pair(p[i].tx, p[i].ty)];
        if (!pos) pos = ++pool_size;
        up(pool[pos], delta[i]);
    }
    lnt ans = fuck(m, n);
    for (lnt i = 1; i <= k; i++) {
        lnt dis = n + 1 - xv[p[i].tx];
        if (!dis) {
            up(ans, delta[i]);
        } else {
            up(ans, delta[i] * fuck(m, dis - 1) % MOD);
        }
    }
    printf("%lld\n", ans);
    return 0;
}