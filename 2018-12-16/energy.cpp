#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MOD 998244353
const int MAXN = 20;
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int n, a[MAXN];
std::map<int, int> f[1 << MAXN];
int main() {
    freopen("energy.in", "r", stdin);
    freopen("energy.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    f[0][0] = 1;
    for (int i = 0; i < (1 << n); i++) {
        int d = __builtin_popcount(i);
        for (auto v : f[i]) {
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1) continue;
                up(f[i | (1 << j)][std::max(v.first, a[j + 1] + d)], v.second);
            }
        }
    }
    int ans = 0;
    for (auto v : f[(1 << n) - 1]) up(ans, 1LL * v.second * v.first % MOD);
    printf("%d\n", ans);
    return 0;
}