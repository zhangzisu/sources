#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 60
#define EPS 1e-5
const double PI = acos(-1);
int n, m, r, _x[MAXN], _y[MAXN], x_[MAXN], y_[MAXN];
double ans, rd;
inline double S(double x) { return x * x * PI; }
inline double sqr(int x) { return 1. * x * x; }
inline double dist(int x0, int y0, int x1, int y1) { return sqrt(sqr(x0 - x1) + sqr(y0 - y1)); }

int main() {
    scanf("%d%d%d", &n, &m, &r);
    assert(n <= 10);
    assert(m <= 10);
    for (int i = 0; i < n; i++) scanf("%d", &_x[i]);
    for (int i = 0; i < n; i++) scanf("%d", &_y[i]);
    for (int i = 0; i < m; i++) scanf("%d", &x_[i]);
    for (int i = 0; i < m; i++) scanf("%d", &y_[i]);

    for (int d0 = 0; d0 < (1 << n); d0++) {
        for (int d1 = 0; d1 < (1 << m); d1++) {
            if (d0 || d1) {
                rd = r;
                for (int i = 0; i < n; i++)
                    if ((d0 >> i) & 1)
                        for (int j = 0; j < m; j++)
                            if ((d1 >> j) & 1)
                                rd = std::min(rd, dist(_x[i], _y[i], x_[j], y_[j]) / 2);
                ans = std::max(ans, (__builtin_popcount(d0) + __builtin_popcount(d1)) * S(rd));
            }
        }
    }
    printf("%.4lf\n", ans);
    return 0;
}