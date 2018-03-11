#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#define MAXN 200010
struct Operation {
    int k, x, rx, y, p;
} opt[MAXN];
inline int cmp(const Operation& a, const Operation& b) { return a.x < b.x; }
inline int CMP(const Operation& a, const Operation& b) { return a.p < b.p; }
int n, m, real[MAXN], val[MAXN << 2];
std::set<int> Y[MAXN];
inline void Build(int n, int l, int r) {
    val[n] = -1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    Build(n << 1, l, mid);
    Build(n << 1 | 1, mid + 1, r);
}
void Modify(int n, int l, int r, int p) {
    if (l == r) {
        val[n] = Y[l].size() ? *Y[l].rbegin() : -1;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        Modify(n << 1, l, mid, p);
    else
        Modify(n << 1 | 1, mid + 1, r, p);
    val[n] = std::max(val[n << 1], val[n << 1 | 1]);
}
inline std::pair<int, int> Query(int n, int l, int r, int L, int R, int y) {
    if (L > R) return std::make_pair(-1, -1);
    if (val[n] <= y) return std::make_pair(-1, -1);
    if (l == r) return std::make_pair(l, *Y[l].upper_bound(y));
    int mid = (l + r) >> 1;
    if (R <= mid)
        return Query(n << 1, l, mid, L, R, y);
    else if (L > mid)
        return Query(n << 1 | 1, mid + 1, r, L, R, y);
    auto lans = Query(n << 1, l, mid, L, mid, y);
    return ~lans.first ? lans : Query(n << 1 | 1, mid + 1, r, mid + 1, R, y);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string buf;
        std::cin >> buf >> opt[i].x >> opt[i].y;
        if (buf[0] == 'a')
            opt[i].k = 0;
        else if (buf[0] == 'r')
            opt[i].k = 1;
        else
            opt[i].k = 2;
        opt[i].p = i;
        opt[i].rx = opt[i].x;
    }
    std::sort(opt + 1, opt + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        if (i == 1 || opt[i].rx != opt[i - 1].rx) real[++m] = opt[i].x;
        opt[i].x = m;
    }
    std::sort(opt + 1, opt + n + 1, CMP);
    Build(1, 1, m);
    for (int i = 1; i <= n; i++) {
        if (opt[i].k == 0) {
            // insert
            Y[opt[i].x].insert(opt[i].y);
            Modify(1, 1, m, opt[i].x);
        } else if (opt[i].k == 1) {
            // Remove
            Y[opt[i].x].erase(opt[i].y);
            Modify(1, 1, m, opt[i].x);
        } else {
            auto x = Query(1, 1, m, opt[i].x + 1, m, opt[i].y);
            if (~x.first)
                std::cout << real[x.first] << ' ' << x.second << std::endl;
            else
                std::cout << -1 << std::endl;
        }
    }
    return 0;
}