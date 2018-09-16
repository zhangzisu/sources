#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 400010
typedef long long lnt;
struct boat_t {
    lnt l, r;
} l[MAXN], r[MAXN];
inline lnt lowbit(lnt x) { return x & -x; }
inline void getAns(boat_t *b, lnt n, std::vector<std::pair<lnt, lnt>> &res) {
    static lnt v[MAXN], m, bit[MAXN];
    memset(bit, 0, sizeof(bit));
    m = 0;
    auto add = [](lnt x) {
        for (; x; x -= lowbit(x)) bit[x]++;
    };
    auto qry = [](lnt x) {
        lnt y = 0;
        for (; x <= m; x += lowbit(x)) y += bit[x];
        return y;
    };
    for (lnt i = 1; i <= n; i++) v[++m] = b[i].r, v[++m] = b[i].l;
    std::sort(v + 1, v + m + 1);
    m = std::unique(v + 1, v + m + 1) - v - 1;
    std::sort(b + 1, b + n + 1, [](const boat_t &a, const boat_t &b) { return a.l < b.l; });
    for (lnt i = 1, cur = 1; i <= m; i++) {
        while (cur <= n && b[cur].l <= v[i]) {
            lnt pos = std::lower_bound(v + 1, v + m + 1, b[cur].r) - v;
            add(pos);
            cur++;
        }
        lnt ans = qry(i);
        res.emplace_back(v[i], ans);
    }
}
lnt n, nl, nr;
std::vector<std::pair<lnt, lnt>> ll, rr;
int main() {
    scanf("%lld", &n);
    for (lnt i = 1, v, d; i <= n; i++) {
        boat_t b;
        scanf("%lld%lld", &b.l, &b.r);
        scanf("%lld%lld", &d, &v);
        b.l += d;
        b.r -= d;
        if (b.l < b.r) {
            i--, n--;
            continue;
        } else {
            std::swap(b.l, b.r);
        }
        if (v == -1)
            l[++nl] = b;
        else
            r[++nr] = b;
    }
    getAns(l, nl, ll);
    getAns(r, nr, rr);
    for (int i = (int)ll.size() - 1; i >= 1; i--) ll[i - 1].second = std::max(ll[i - 1].second, ll[i].second);
    lnt ans = ll.size() ? ll.front().second : 0;
    for (auto x : rr) {
        auto pos = std::lower_bound(ll.begin(), ll.end(), std::make_pair(x.first, 0LL));
        if (pos == ll.end()) {
            ans = std::max(ans, x.second);
        } else {
            ans = std::max(ans, pos->second + x.second);
        }
    }
    printf("%lld\n", ans);
    return 0;
}