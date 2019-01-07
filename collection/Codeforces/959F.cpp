#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define MAXN 1 << 20
#define MOD 1000000007
int n, q, now, a[MAXN], vis[MAXN], ans[MAXN];
std::vector<std::pair<int, int>> D[MAXN];
std::vector<int> S;
int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1, x, y; i <= q; i++) {
        std::cin >> x >> y;
        D[x].push_back({y, i});
    }
    S.push_back(0);
    now = vis[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[a[i]]) {
            now = 1LL * now * 2 % MOD;
        } else {
            int N = S.size();
            for (int j = 0; j < N; j++) {
                S.push_back(S[j] ^ a[i]), vis[S[j] ^ a[i]] = 1;
            }
        }
        for (auto e : D[i]) ans[e.second] = 1LL * now * vis[e.first] % MOD;
    }
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}