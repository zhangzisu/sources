#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#define MAXN 65
#define MOD 998244353
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
std::set<int> S;
int T, n, m, a[MAXN];
int stk[MAXN];
std::map<int, int> store;
int dfs(int l, int r) {
    if (l == r && store.count(l)) return store[l];
    if (l >= m && r >= m) return 1;
    int cur = l + r + 1, ret = 0;
    if (l < m && (l + 1 > r || a[cur] == stk[l + 1])) {
        stk[l + 1] = a[cur];
        up(ret, dfs(l + 1, r));
    }
    if (r < m && (r + 1 > l || a[cur] == stk[r + 1])) {
        stk[r + 1] = a[cur];
        up(ret, dfs(l, r + 1));
    }
    if (l == r) store[l] = ret;
    return ret;
}
// int fsd(int l, int r) {
//     if (l >= m && r >= m) return 1;
//     int cur = l + r + 1;
//     if (l < m && (l + 1 > r || a[cur] == stk[l + 1])) {
//         stk[l + 1] = a[cur];
//         if (fsd(l + 1, r)) return 1;
//     }
//     if (r < m && (r + 1 > l || a[cur] == stk[r + 1])) {
//         stk[r + 1] = a[cur];
//         if (fsd(l, r + 1)) return 1;
//     }
//     return 0;
// }
// int f[MAXN][MAXN][MAXN];
int main() {
    freopen("merge.in", "r", stdin);
    freopen("merge.out", "w", stdout);
    for (scanf("%d", &T); T; T--) {
        scanf("%d", &n);
        m = 0;
        S.clear();
        store.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            if (S.count(a[i])) {
                S.erase(a[i]);
            } else {
                ++m;
                S.insert(a[i]);
            }
        }
        if (m * 2 != n) {
            puts("0");
            continue;
        }
        // if (n <= 60) {
        printf("%d\n", dfs(0, 0));
        // } else {
        //     if (!fsd(0, 0)) {
        //         puts("0");
        //         continue;
        //     }
        //     memset(f, 0, sizeof(f));
        //     f[0][0][0] = 1;
        //     for (int i = 0; i < n; i++) {
        //         for (int j = 0; j <= m; j++) {
        //             for (int k = 0; k <= m; k++) {
        //                 int &x = f[i][j][k];
        //                 if (!x) continue;
        //                 if (j < m && a[i + 1] == stk[j + 1]) up(f[i + 1][j + 1][k], x);
        //                 if (k < m && a[i + 1] == stk[k + 1]) up(f[i + 1][j][k + 1], x);
        //             }
        //         }
        //     }
        //     if (f[n][m][m]) {
        //         printf("%d\n", f[n][m][m]);
        //         continue;
        //     }
        // }
    }
    return 0;
}