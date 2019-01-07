#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
const double EPS = 1e-7;
int n, R, f[MAXN];
struct point_t {
	double x, y;
	inline point_t(double x = 0, double y = 0) : x(x), y(y) {}
	inline point_t friend operator*(point_t p, double k) {
		return point_t(p.x * k, p.y * k);
	}
} p[MAXN], q[MAXN];
double esm[MAXN];
inline int cmp(double x, double y) {
	double delta = x - y;
	if (delta < -EPS) return -1;  // x < y
	if (delta > EPS) return 1;	// x > y
	return 0;					  // x == y
}
inline int judge(double mid) {
	for (int i = 1; i <= n; i++) q[i] = p[i] * mid;
	int ret = n + 1;
	for (int i = 1, lst = 0; i <= n; i++) {
		f[i] = n + 1;
		while (lst < n && cmp(q[lst + 1].x, p[i].x) == -1) lst++;
		int cur = lst;
		double sl = 1e100;
		for (int j = i - 1; j >= 0; j--) {
			for (; cur >= 1 && cmp(q[cur].x, p[j].x) == 1; cur--) sl = std::min(sl, (p[i].y - q[cur].y) / (p[i].x - q[cur].x));
			if (cmp(sl, (p[i].y - p[j].y) / (p[i].x - p[j].x)) != -1) {
				f[i] = std::min(f[i], f[j] + 1);
			}
		}
		for (; cur >= 1; cur--) sl = std::min(sl, (p[i].y - q[cur].y) / (p[i].x - q[cur].x));
		if (cmp(sl, 0) != -1) f[i] = std::min(f[i], 1);
		if (cmp(q[n].x, p[i].x) != 1) ret = std::min(ret, f[i]);
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &R);
	for (int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
	std::sort(p + 1, p + n + 1, [](point_t a, point_t b) { return a.x < b.x; });
	double l = 0, r = 1;
	while (r - l > EPS) {
		auto mid = (l + r) / 2;
		if (judge(mid) <= R) {
			l = mid;
		} else {
			r = mid;
		}
	}
	printf("%lf\n", (l + r) / 2);
	return 0;
}