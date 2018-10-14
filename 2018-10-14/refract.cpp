#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 4010
#define MOD 1000000007
int n, m, v[MAXN];
struct point {
    int x, y;
    inline bool friend operator<(point a, point b) {
        return a.y > b.y;
    }
} p[MAXN];
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int f[MAXN][MAXN], ans;
int main() {
    freopen("refract.in", "r", stdin);
    freopen("refract.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y), v[i] = p[i].x;
    std::sort(v + 1, v + n + 1);
    m = std::unique(v + 1, v + n + 1) - v - 1;
    std::sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; i++) {
        p[i].x = std::lower_bound(v + 1, v + m + 1, p[i].x) - v;
        for (int j = 1; j < i; j++) {
            if (p[j].y <= p[i].y) break;
            if (p[j].x == p[i].x) continue;
            if (p[j].x < p[i].x) {
                up(f[i][p[j].x], f[j][m]);
                up(f[i][p[j].x], MOD - f[j][p[i].x]);
            } else {
                up(f[i][p[j].x], f[j][p[i].x - 1]);
            }
            up(f[i][p[j].x], 1);
        }
        for (int j = 1; j <= m; j++) up(f[i][j], f[i][j - 1]);
        up(ans, f[i][m]);
    }
    up(ans, n);
    printf("%d\n", ans);
    return 0;
}