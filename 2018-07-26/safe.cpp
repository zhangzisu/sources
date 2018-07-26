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
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &pts[i].x, &pts[i].y);
    for (int i = 1; i <= n; i++) {
        int j = i == 1 ? n : i - 1;
        if (pts[i].y > 0 && pts[j].y > 0) continue;
        if (pts[i].y < 0 && pts[j].y < 0) continue;
        if (pts[i].x == pts[j].x) {
            zero.push_back(pts[i].x);
            continue;
        }
        double k = 1. * (pts[i].y - pts[j].y) / (pts[i].x - pts[j].x);
        double b = pts[i].y - k * pts[i].x;
        double p = -b / k;
        zero.push_back(p);
    }
    std::sort(zero.begin(), zero.end());
    zero.erase(std::unique(zero.begin(), zero.end()), zero.end());
    for (int i = 1; i < (int)zero.size(); i++) {
        double pos = (zero[i] + zero[i - 1]) / 2;
        double alpha = 0;
        int tmp = 0;
        fprintf(stderr, "CHECKING %f\n", pos);
        for (int i = 1; i <= n; i++) {
            int j = i == 1 ? n : i - 1;
            if (pts[i].y > 0 && pts[j].y > 0) continue;
            if (pts[i].y < 0 && pts[j].y < 0) continue;
            if (pts[i].x == pts[j].x) {
                if (fabs(pos - pts[i].x) <= EPS) goto fail;
                continue;
            }
            double k = 1. * (pts[i].y - pts[j].y) / (pts[i].x - pts[j].x);
            double b = pts[i].y - k * pts[i].x;
            if (fabs(pos - b) <= EPS) goto fail;
        }
        fprintf(stderr, "CALC %f\n", pos);
        for (int i = 1; i <= n; i++) {
            int j = i == n ? 1 : i + 1;
            double ddd = atan2(pts[i].x - pos, pts[i].y);
            double aaa = atan2(pts[j].x - pos, pts[j].y);
            double delta = aaa - ddd;
            if (alpha + delta > PI) {
                ans++;
                alpha += delta;
                alpha -= PI;
            }
            if (alpha + delta < -PI) {
                ans--;
                alpha += delta;
                alpha += PI;
            }
        }
        ans = std::max(ans, tmp);
    fail:;
    }
    printf("%d\n", ans);
    return 0;
}