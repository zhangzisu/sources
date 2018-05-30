#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int n, m, usd[1 << 22], vis[1 << 22][2], t, ans;
std::pair<int, int> Q[1 << 23];
inline void add(int x) {
    if (!vis[x][1]) vis[x][1] = 1, Q[++t] = {x, 1};
    if (!vis[x][0] && usd[x]) vis[x][0] = 1, Q[++t] = {x, 0};
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, x; i <= m; i++) scanf("%d", &x), usd[x] = 1;
    for (int i = 0; i < (1 << n); i++) {
        if (!vis[i][0] && usd[i]) {
            Q[t = 1] = {i, (vis[i][0] = 1, 0)};
            for (int j = 1; j <= t; j++) {
                auto _ = Q[j];
                if (_.second) {
                    for (int k = 0; k < n; k++)
                        if ((_.first >> k) & 1) add(_.first ^ (1 << k));
                } else {
                    add((1 << n) - 1 - _.first);
                }
            }
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}