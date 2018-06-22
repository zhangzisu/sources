#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAXN 510
typedef long double ld;
const ld EPS = 1e-6;
const ld INF = 1. / 0.;

int n, m, a[MAXN], b[MAXN], id[MAXN], pos[MAXN];
ld f[MAXN][MAXN], c[MAXN];
long long sa, sb;

bool check(ld mid) {
    for (int i = 1; i <= n; i++)
        c[i] = c[i - 1] + a[id[i]] - b[id[i]] * mid;

    for (int i = 0; i <= n; i++) f[0][i] = INF;
    f[0][pos[1] - 1] = c[pos[1] - 1];

    for (int i = 1; i < m; i++) {
        int s = pos[i + 1] - pos[i];
        for (int j = 0; j <= n; j++) {
            f[i][j] = INF;
            for (int k = 0; k <= s; k++) {
                if ((s - k > j + s - 2 * k) || (j + s - 2 * k > n)) continue;
                f[i][j] = std::min(f[i][j], f[i - 1][j + s - 2 * k] + c[pos[i] + k - 1] - c[pos[i] - 1]);
            }
        }
    }

    ld ans = INF;
    for (int i = 0; i <= n; i++) ans = std::min(ans, f[m - 1][i]);
    return ans <= EPS;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sa += a[i];
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]), sb += b[i];
    for (int i = 1; i <= n; i++) id[i] = i;
    std::sort(id + 1, id + n + 1, [](int x, int y) { return a[x] == a[y] ? b[x] > b[y] : a[x] > a[y]; });
    for (int i = 1; i <= n; i++)
        if (a[id[i]] != a[id[i - 1]]) pos[m++] = i;
    pos[m] = n + 1;
    long long l = 0, r = 1000. * sa / sb, ans;
    while (l <= r) {
        long long m = l + ((r - l) / 2);
        if (check(m / 1000.)) {
            r = m - 1;
            ans = m;
        } else
            l = m + 1;
    }
    printf("%lld\n", ans);
}