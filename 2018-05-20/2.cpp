#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 210
#define EPS 1e-5
const double PI = acos(-1);
int n, m, k, r, _x[MAXN], _y[MAXN], x_[MAXN], y_[MAXN];
double ans, rd;
inline double S(double x) { return x * x * PI; }
inline double sqr(int x) { return 1. * x * x; }
inline double dist(int x0, int y0, int x1, int y1) { return sqrt(sqr(x0 - x1) + sqr(y0 - y1)); }
std::pair<double, std::pair<int, int>> dt[MAXN * MAXN];
int match[MAXN], vis[MAXN], skip[MAXN], ban[MAXN][MAXN];
bool _(int x) {
    for (int i = 1; i <= m; i++) {
        if (ban[x][i]) continue;
        if (vis[i]) continue;
        vis[i] = 1;
        if (!match[i] || _(match[i])) return match[i] = x, 1;
    }
    return 0;
}
int main() {
    scanf("%d%d%d", &n, &m, &r);
    for (int i = 1; i <= n; i++) scanf("%d", &_x[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &_y[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &x_[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &y_[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            double d = dist(_x[i], _y[i], x_[j], y_[j]) / 2;
            if (d < r + EPS) dt[++k] = {d, {i, j}};
        }
    }
    dt[++k] = {r, {0, 0}};
    std::sort(dt + 1, dt + k + 1);
    memset(ban, 1, sizeof(ban));
    int cnt = 0;
    for (int i = 1; i <= k; i++) {
        memset(skip, 0, sizeof(skip));
        for (int i = 1; i <= m; i++) skip[match[i]] = 1;
        for (int i = 1; i <= n; i++)
            if (!skip[i] && (memset(vis, 0, sizeof(vis)), _(i))) cnt++;
        int res = n + m - cnt;
        // printf("Radius %lf: count %d, ans %lf\n", dt[i].first, res, S(dt[i].first) * res);
        ans = std::max(ans, S(dt[i].first) * res);
        ban[dt[i].second.first][dt[i].second.second] = 0;
    }
    printf("%.4lf\n", ans);
    return 0;
}