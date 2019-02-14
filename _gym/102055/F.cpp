#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include<cassert>
const int MAXN = 1010;
const double EPS = 1e-6;
inline int fcmp(double a, double b) {
	double delta = b - a;
	if (delta >= EPS) return 1;
	if (delta <= -EPS) return -1;
	return 0;
}
inline double sqr(double x) { return x * x; }
struct cone_2d_t {
	double y, yl, yr, c;
	inline int friend operator<(cone_2d_t a, cone_2d_t b) {
		return b.yl - a.yl >= EPS;
	}
} cone_2d[MAXN];
int cone_2d_l, cone_2d_r;
inline double calc_2d(double y) {
	double ret = 0;
	for (int i = cone_2d_l; i <= cone_2d_r; i++) {
		const auto &cone = cone_2d[i];
		if (fcmp(y, cone.yl) != -1 || fcmp(y, cone.yr) != 1) continue;
		double z = 1 - sqrt(sqr(y - cone.y) + cone.c);
		ret = std::max(ret, z);
	}
	return ret;
}
inline double simpson_2d(double l, double r) {
	double mid = (l + r) / 2.0;
	return (calc_2d(l) + 4.0 * calc_2d(mid) + calc_2d(r)) * (r - l) / 6.0;
}
double solve_2d(double l, double r, double ans) {
	double mid = (l + r) / 2.0;
	double L = simpson_2d(l, mid);
	double R = simpson_2d(mid, r);
	if (fabs(L + R - ans) <= EPS) return L + R;
	return solve_2d(l, mid, L) + solve_2d(mid, r, R);
}
struct cone_3d_t {
	double x, xl, xr, y;
	inline int friend operator<(cone_3d_t a, cone_3d_t b) {
		return b.xl - a.xl >= EPS;
	}
} cone_3d[MAXN];
int cone_3d_l, cone_3d_r;
inline double calc_3d(double x) {
	int cone_2d_c = 0;
	for (int i = cone_3d_l; i <= cone_3d_r; i++) {
		const auto &cone = cone_3d[i];
		if (fcmp(x, cone.xl) != -1 || fcmp(x, cone.xr) != 1) continue;
		double c = sqr(x - cone.x);
		double r = sqrt(1 - c);
		cone_2d[++cone_2d_c] = {cone.y, cone.y - r, cone.y + r, c};
	}
	if (!cone_2d_c) return 0;
	std::sort(cone_2d + 1, cone_2d + cone_2d_c + 1);
	double l = cone_2d[1].yl, r = cone_2d[1].yr, ret = 0;
	cone_2d_l = cone_2d_r = 1;
	for (int i = 2; i <= cone_2d_c; i++) {
		if (fcmp(cone_2d[i].yl, r) >= 0) {
			r = std::max(r, cone_2d[i].yr);
			cone_2d_r = i;
		} else {
            assert(l==l);
            assert(r==r);
			ret += solve_2d(l, r, simpson_2d(l, r));
			l = cone_2d[i].yl, r = cone_2d[i].yr;
			cone_2d_l = cone_2d_r = i;
		}
	}
    assert(l==l);
    assert(r==r);
	ret += solve_2d(l, r, simpson_2d(l, r));
	return ret;
}
inline double simpson_3d(double l, double r) {
	double mid = (l + r) / 2.0;
	return (calc_3d(l) + 4.0 * calc_3d(mid) + calc_3d(r)) * (r - l) / 6.0;
}
double solve_3d(double l, double r, double ans) {
	double mid = (l + r) / 2.0;
	double L = simpson_3d(l, mid);
	double R = simpson_3d(mid, r);
	if (fabs(L + R - ans) <= EPS) return L + R;
	return solve_3d(l, mid, L) + solve_3d(mid, r, R);
}
int T, n;
double x[MAXN], y[MAXN];
int main() {
	scanf("%d", &T);
	for (int _t = 1; _t <= T; _t++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%lf%lf", x + i, y + i);
			cone_3d[i] = {x[i], x[i] - 1, x[i] + 1, y[i]};
		}
		std::sort(cone_3d + 1, cone_3d + n + 1);
		double l = cone_3d[1].xl, r = cone_3d[1].xr, ret = 0;
		cone_3d_l = cone_3d_r = 1;
		for (int i = 2; i <= n; i++) {
			if (fcmp(cone_3d[i].xl, r) >= 0) {
				r = std::max(r, cone_3d[i].xr);
				cone_3d_r = i;
			} else {
				ret += solve_3d(l, r, simpson_3d(l, r));
				l = cone_3d[i].xl, r = cone_3d[i].xr;
				cone_3d_l = cone_3d_r = i;
			}
		}
		ret += solve_3d(l, r, simpson_3d(l, r));
		printf("Case %d: %.9f\n", _t, ret);
	}
}