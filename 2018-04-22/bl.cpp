#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#define MAXN 500010
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
int n = $(), a = $(), b = $(), c = $();
long long ans = 0, tmp;
struct node {
    int x, y;
    inline friend bool operator<(const node &a, const node &b) {
        return a.y < b.y;
    }
};
std::set<node> s;
std::vector<node> v[MAXN];
int main() {
    for (int i = 1; i <= n; i++) {
        int x = $(), y = $(), z = $();
        v[c].push_back({x, y});
        v[z].push_back({a, y});
        v[z].push_back({x, b});
    }
    tmp = 1LL * a * b;
    s.insert({0, b + 1});
    s.insert({a + 1, 0});
    for (int i = c; i >= 1; i--) {
        for (auto &x : v[i]) {
            auto y = *s.lower_bound(x);
            if (y.x >= x.x) continue;
            int lx = -1, ly = -1, t = y.x;
            while (1) {
                auto u = *--s.upper_bound(x);
                if (lx > 0) tmp += 1LL * (lx - t) * (ly - u.y);
                lx = u.x, ly = u.y;
                if (u.x > x.x) break;
                s.erase(u);
            }
            tmp -= 1LL * (x.x - t) * (x.y - ly);
            s.insert(x);
        }
        ans += tmp;
    }
    printf("%lld\n", ans);
    return 0;
}