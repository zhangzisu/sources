#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1010
const double EPS = 1e-9;
const double PI = acos(-1);
int n, ans = 0;
struct point {
    int x, y;
    inline point(int x = 0, int y = 0) : x(x), y(y) {}
} pts[MAXN];
std::vector<double> zero;
inline double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}
int main() {
    // freopen("safe.in", "r", stdin);
    // freopen("safe.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &pts[i].x, &pts[i].y);
    for (int i = 1; i <= n; i++) {
        int j = i == n ? 1 : i + 1;
        if (pts[i].y != pts[j].y) {
            double p = 1. * (pts[i].y * pts[j].x - pts[i].x * pts[j].y) / (pts[i].y - pts[j].y);
            zero.push_back(p);
        }
    }
    std::sort(zero.begin(), zero.end());
    for (int i = 1; i < (int)zero.size(); i++) {
        if (zero[i] - zero[i - 1] <= EPS) continue;
        double pos = (zero[i] + zero[i - 1]) / 2;
        double alpha = 0;
        // fprintf(stderr, "CHECKING %f\n", pos);
        for (int i = 1; i <= n; i++) {
            int j = i == 1 ? n : i - 1;
            if (pts[i].y > 0 && pts[j].y > 0) continue;
            if (pts[i].y < 0 && pts[j].y < 0) continue;
            if (pts[i].y != pts[j].y) {
                double p = 1. * (pts[i].y * pts[j].x - pts[i].x * pts[j].y) / (pts[i].y - pts[j].y);
                if (fabs(p - pos) < EPS) goto fail;
            } else if (pts[i].y == 0) {
                int min = std::min(pts[i].x, pts[j].x);
                int max = std::max(pts[i].x, pts[j].x);
                if (pos + EPS > min && pos < max + EPS) goto fail;
            }
        }
        // fprintf(stderr, "CALC %f\n", pos);
        for (int i = 1; i <= n; i++) {
            int j = i == n ? 1 : i + 1;
            double ddd = atan2(pts[i].y, pts[i].x - pos);
            double aaa = atan2(pts[j].y, pts[j].x - pos);
            double delta = fabs(aaa - ddd);
            if (delta + EPS > PI) delta = 2 * PI - delta;
            if (cross(pts[i].x - pos, pts[i].y, pts[j].x - pos, pts[j].y) < EPS) delta = -delta;
            alpha += delta;
        }
        ans = std::max(ans, (int)floor(alpha / 2 / PI + EPS));
    fail:;
    }
    printf("%d\n", ans);
    return 0;
}