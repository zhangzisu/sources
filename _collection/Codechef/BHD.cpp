#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 25
const double EPS = 1e-6;
const double INF = 1000;
inline int fcmp(double a, double b) {
	double delta = b - a;
	if (delta >= EPS) return 1;
	if (delta <= -EPS) return -1;
	return 0;
}
struct x_t {
	double l, r;
	inline int friend operator<(const x_t &a, const x_t &b) {
		return b.l - a.l >= EPS;
	}
} x[MAXN << 2];
struct y_t {
	double x, y, r1, r2;
	double min_x, max_x, l_x, r_x;
	double fuck1, fuck2;
	inline void calc() {
		min_x = x - r1 - r2;
		max_x = x + r1 + r2;
		l_x = x - r1 + r2;
		r_x = x + r1 - r2;
		fuck1 = (r1 + r2) * (r1 + r2);
		fuck2 = (r1 - r2) * (r1 - r2);
	}
	inline int friend operator<(const y_t &a, const y_t &b) {
		return b.min_x - a.min_x >= EPS;
	}
} y[MAXN];
int yl, yr;
inline double f2(double p) {
	register int n = 0;
	for (int i = yl; i <= yr; i++) {
		const y_t &Y = y[i];
		if (fcmp(p, Y.min_x) >= 0 || fcmp(p, Y.max_x) <= 0) continue;
		double delta = fabs(Y.x - p);
		delta *= delta;
		if (fcmp(p, Y.l_x) == -1 && fcmp(p, Y.r_x) == 1) {
			if (fcmp(delta, Y.fuck1) != 1) continue;
			if (fcmp(delta, Y.fuck2) != 1) continue;
			double len1 = sqrt(Y.fuck1 - delta);
			double len2 = sqrt(Y.fuck2 - delta);
			x[++n] = (x_t){Y.y - len1, Y.y - len2};
			x[++n] = (x_t){Y.y + len2, Y.y + len1};
		} else {
			if (fcmp(delta, Y.fuck1) != 1) continue;
			double len = sqrt(Y.fuck1 - delta);
			x[++n] = (x_t){Y.y - len, Y.y + len};
		}
	}
	if (!n) return 0;
	std::sort(x + 1, x + n + 1);
	double l = x[1].l, r = x[1].r, ret = 0;
	for (int i = 2; i <= n; i++) {
		if (fcmp(x[i].l, r) >= 0) {
			r = std::max(r, x[i].r);
		} else {
			ret += r - l;
			l = x[i].l;
			r = x[i].r;
		}
	}
	ret += r - l;
	return ret;
}
inline double simpson2(double l, double r) {
	double mid = (l + r) / 2.0;
	return (f2(l) + 4.0 * f2(mid) + f2(r)) * (r - l) / 6.0;
}
double solve2(double L, double R, double ans) {
	double mid = (L + R) / 2, l = simpson2(L, mid), r = simpson2(mid, R);
	if (fabs(l + r - ans) <= EPS) return l + r;
	return solve2(L, mid, l) + solve2(mid, R, r);
}
struct z_t {
	double x, y, z, r1, r2;
	double min_height, max_height;
	double fuck1;
	inline void calc() {
		min_height = z - r2;
		max_height = z + r2;
		fuck1 = r2 * r2;
	}
	inline int friend operator<(const z_t &a, const z_t &b) {
		return b.min_height - a.min_height >= EPS;
	}
} z[MAXN];
int zl, zr;
inline double f3(double p) {
	register int n = 0;
	for (int i = zl; i <= zr; i++) {
		const z_t &Z = z[i];
		if (fcmp(p, Z.min_height) >= 0 || fcmp(p, Z.max_height) <= 0) continue;
		double delta = fabs(Z.z - p);
		delta *= delta;
		if (fcmp(delta, Z.fuck1) != 1) continue;
		++n;
		y[n].x = Z.x, y[n].y = Z.y;
		y[n].r1 = Z.r1;
		y[n].r2 = sqrt(Z.fuck1 - delta);
		y[n].calc();
	}
	std::sort(y + 1, y + n + 1);
	double l = y[1].min_x, r = y[1].max_x, ans = 0;
	yl = yr = 1;
	for (int i = 2; i <= n; i++) {
		if (fcmp(y[i].min_x, r) >= 0) {
			r = std::max(r, y[i].max_x);
			yr = i;
		} else {
			ans += solve2(l, r, simpson2(l, r));
			l = y[i].min_x, r = y[i].max_x;
			yl = yr = i;
		}
	}
	ans += solve2(l, r, simpson2(l, r));
	return ans;
}
inline double simpson3(double l, double r) {
	double mid = (l + r) / 2.0;
	return (f3(l) + 4.0 * f3(mid) + f3(r)) * (r - l) / 6.0;
}
double solve3(double L, double R, double ans) {
	double mid = (L + R) / 2, l = simpson3(L, mid), r = simpson3(mid, R);
	if (fabs(l + r - ans) <= EPS) return l + r;
	return solve3(L, mid, l) + solve3(mid, R, r);
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf%lf%lf%lf", &z[i].x, &z[i].y, &z[i].z, &z[i].r1, &z[i].r2);
		z[i].calc();
	}
	std::sort(z + 1, z + n + 1);
	double l = z[1].min_height, r = z[1].max_height, ans = 0;
	zl = zr = 1;
	for (int i = 2; i <= n; i++) {
		if (fcmp(z[i].min_height, r) >= 0) {
			r = std::max(r, z[i].max_height);
			zr = i;
		} else {
			ans += solve3(l, r, simpson3(l, r));
			l = z[i].min_height, r = z[i].max_height;
			zl = zr = i;
		}
	}
	ans += solve3(l, r, simpson3(l, r));
	printf("%f\n", ans);
	return 0;
}