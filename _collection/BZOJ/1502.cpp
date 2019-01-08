#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 510
const double EPS = 1e-6;
int n, m;
double alpha, h, tmp, L, R;
struct point {
    double x, y;
    inline point(double x = 0, double y = 0) : x(x), y(y) {}
};
struct circle {
    double x, r;
    inline circle(double x = 0, double r = 0) : x(x), r(r) {}
    inline double operator()(double X) {
        return sqrt(r * r - (x - X) * (x - X));
    }
    inline bool operator[](double X) { return fabs(X - x) <= r; }
} cir[MAXN];
struct function {
    double k, b, l, r;
    inline function(double k = 0, double b = 0, double l = 0, double r = 0)
        : k(k), b(b), l(l), r(r) {}
    inline function(const point &a, const point &b) {
        this->k = (a.y - b.y) / (a.x - b.x);
        this->b = a.y - a.x * k;
        this->l = a.x;
        this->r = b.x;
    }
    inline double operator()(double x) { return k * x + b; }
    inline bool operator[](double x) { return x >= l && x <= r; }
} F[MAXN];
double f(double x) {
    double ret = 0;
    for (int i = 1; i <= m; i++)
        if (F[i][x]) ret = std::max(ret, F[i](x));
    for (int i = 1; i <= n; i++)
        if (cir[i][x]) ret = std::max(ret, cir[i](x));
    return ret;
}
double simpuson(double l, double r) {
    return (f(l) + f(r) + f((l + r) / 2) * 4) * (r - l) / 6;
}
double simpson(double l, double r) {
    double mid = (l + r) / 2;
    if (fabs(simpuson(l, r) - simpuson(l, mid) - simpuson(mid, r)) < EPS)
        return simpuson(l, mid) + simpuson(mid, r);
    return simpson(l, mid) + simpson(mid, r);
}
int main() {
    scanf("%d%lf", &n, &alpha), n++;
    scanf("%lf", &h);
    for (int i = 1; i < n; i++) {
        scanf("%lf", &tmp);
        cir[i].x = h / tan(alpha);
        h += tmp;
    }
    cir[n].x = h / tan(alpha);
    for (int i = 1; i < n; i++) scanf("%lf", &cir[i].r);
    cir[n].r = 0;
    L = cir[1].x - cir[1].r;
    R = cir[1].x + cir[1].r;
    for (int i = 2; i <= n; i++) {
        circle &a = cir[i - 1], &b = cir[i];
        L = std::min(L, b.x - b.r);
        R = std::max(R, b.x + b.r);
        if (b.x - a.x - fabs(b.r - a.r) > EPS) {
            double k = (b.r - a.r) / (b.x - a.x);
            F[++m] =
                function(point(a.x - k * a.r, sqrt(a.r * a.r * (1 - k * k))),
                         point(b.x - k * b.r, sqrt(b.r * b.r * (1 - k * k))));
        }
    }
    printf("%.2lf\n", 2 * simpson(L, R));
}