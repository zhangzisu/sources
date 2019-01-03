#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 110
const int INF = 0x3F3F3F3F;
struct point_t {
	double x, y;
	inline point_t(double x = 0, double y = 0) : x(x), y(y) {}
	inline point_t friend operator+(point_t a, point_t b) {
		return point_t(a.x + b.x, a.y + b.y);
	}
	inline point_t friend operator-(point_t a, point_t b) {
		return point_t(a.x - b.x, a.y - b.y);
	}
	inline double friend operator*(point_t a, point_t b) {
		return a.x * b.y - b.x * a.y;
	}
} point[MAXN], tmp[MAXN];
struct plane_t {
	double a, b, c;
	int w;
	inline point_t friend operator*(plane_t a, plane_t b) {
		return point_t((a.c * b.b - b.c * a.b) / (a.a * b.b - b.a * a.b), (a.c * b.a - b.c * a.a) / (a.b * b.a - a.a * b.b));
	}
} plane[MAXN];
inline bool in(plane_t plane, point_t point) {
	return plane.a * point.x + plane.b * point.y <= plane.c;
}
point_t base;
inline int cmp(point_t a, point_t b) { return (a - base) * (b - base) >= 0; }
int n, p, f[MAXN][MAXN], g[MAXN], ans = INF;
int main() {
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++) scanf("%lf%lf%lf%d", &plane[i].a, &plane[i].b, &plane[i].c, &plane[i].w);
	for (int i = 1; i <= p; i++) scanf("%lf%lf", &point[i].x, &point[i].y);
	for (int i = 1; i <= n; i++) {
		bool flag = true;
		for (int j = 1; j <= p; j++) {
			if (!in(plane[i], point[j])) {
				flag = false;
				break;
			}
		}
		if (flag) ans = std::min(ans, plane[i].w);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			int t = 0;
			for (int k = 1; k <= p; k++) {
				if (!in(plane[i], point[k]) && !in(plane[j], point[k])) {
					tmp[++t] = point[k];
				}
			}
			base = plane[i] * plane[j];
			std::sort(tmp + 1, tmp + t + 1, cmp);
			memset(f, 0x3F, sizeof(f));
			for (int k = 1; k <= n; k++) {
				if (k == i || k == j) continue;
				for (int l = 1; l <= t; l++) {
					if (in(plane[k], tmp[l])) {
						for (int r = l; r <= t; r++) {
							if (r == t || !in(plane[k], tmp[r + 1])) {
								f[l][r] = std::min(f[l][r], plane[k].w);
								l = r + 1;
								break;
							}
						}
					}
				}
			}
			for (int l = 1; l <= t; l++) {
				for (int r = t; r > l; r--) {
					f[l + 1][r] = std::min(f[l + 1][r], f[l][r]);
					f[l][r - 1] = std::min(f[l][r - 1], f[l][r]);
				}
			}
			memset(g, 0x3F, sizeof(g));
			g[0] = 0;
			for (int r = 1; r <= n; r++) {
				for (int l = 1; l <= r; l++) {
					g[r] = std::min(g[r], g[l - 1] + f[l][r]);
				}
			}
			ans = std::min(ans, plane[i].w + plane[j].w + g[t]);
		}
	}
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}