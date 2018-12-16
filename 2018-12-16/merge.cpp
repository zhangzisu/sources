#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <map>
#define MAXN 65
#define MOD 998244353
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int T, n, m, a[MAXN];
std::map<std::deque<int>, int> f1, f2, g;
int main() {
    for (scanf("%d", &T); T; T--) {
        scanf("%d", &n);
        m = n / 2;
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        f1.clear();
        f1[{}] = 1;
        for (int i = 1; i <= m; i++) {
            std::swap(f1, g);
            f1.clear();
            for (const auto &v : g) {
                if (v.first.empty()) {
                    up(f1[{a[i]}], v.second);
                } else if (a[i] == v.first.front()) {
                    auto x(v.first);
                    x.pop_front();
                    up(f1[x], v.second);
                }
                auto x(v.first);
                x.push_back(a[i]);
                up(f1[x], v.second);
            }
        }
        f2.clear();
        f2[{}] = 1;
        for (int i = n; i >= m + 1; i--) {
            std::swap(f2, g);
            f2.clear();
            for (const auto &v : g) {
                if (v.first.empty()) {
                    up(f2[{a[i]}], v.second);
                } else if (a[i] == v.first.back()) {
                    auto x(v.first);
                    x.pop_back();
                    up(f2[x], v.second);
                }
                auto x(v.first);
                x.push_front(a[i]);
                up(f2[x], v.second);
            }
        }
        auto it = f2.begin();
        int ans = 0;
        for (const auto &v : f1) {
            while (it != f2.end() && it->first < v.first) it++;
            if (it == f2.end()) break;
            if (it->first == v.first) up(ans, 1LL * v.second * it->second % MOD);
        }
        up(ans, 1LL * f1[{}] * f2[{}] % MOD);
        printf("%d\n", int(499122177LL * ans % MOD));
    }
    return 0;
}