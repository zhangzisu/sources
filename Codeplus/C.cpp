#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
int t, a1, a2, r1, r2;
struct color {
    double r, g, b;
};
color calc(double a, double r) {
    int h = floor(a / 60);
    double f = 1.0 * a / 60 - h;
    double R = 1.0 * r / 100;
    double p = 1 - R;
    double q = 1 - f * R;
    double t = 1 - (1 - f) * R;
    switch (h) {
        case 0:
            return {1, t, p};
        case 1:
            return {q, 1, p};
        case 2:
            return {p, 1, t};
        case 3:
            return {p, q, 1};
        case 4:
            return {t, p, 1};
        case 5:
            return {1, p, q};
    }
}
double calc(color c) {
    return c.r * 0.3 + c.g * 0.59 + c.b * 0.11;
}
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%d", &a1, &r1, &a2, &r2);
        double ans = 0;
        for (double i = a1; i <= a2; i += 0.001) {
            ans = std::max(ans, std::max(calc(calc(i, r1)), calc(calc(i, r2))));
        }
        printf("%.4lf\n", ans);
    }
    return 0;
}