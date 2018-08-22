#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define EPS 1e-8
struct point_t {
	int x, y;
	inline point_t(int x = 0, int y = 0) : x(x), y(y) {}
	inline bool friend operator<(point_t a, point_t b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	}
	inline point_t friend operator-(point_t a, point_t b) {
		return point_t(a.x - b.x, a.y - b.y);
	}
	inline double friend operator*(point_t a, point_t b) {
		return 1. * a.x * b.y - 1. * a.y * b.x;
	}
} p[MAXN];
struct line_t {
	double k;
	int x, y;
	inline bool friend operator<(line_t a, line_t b) {
		return a.k < b.k;
	}
} l[MAXN * MAXN];
int n, m, pos[MAXN], id[MAXN];
double ans = 1e100;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
	std::sort(p + 1, p + n + 1);
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			++m;
			l[m].x = i;
			l[m].y = j;
			l[m].k = p[i].x == p[j].x ? 1e100 : 1. * (p[i].y - p[j].y) / (p[i].x - p[j].x);
		}
	}
	std::sort(l + 1, l + m + 1);
	for (int i = 1; i <= n; i++) pos[i] = id[i] = i;
	for (int i = 1; i <= m; i++) {
		int x = l[i].x;
		int y = l[i].y;
		if (pos[x] > pos[y]) std::swap(x, y);
		if (pos[x] > 1) {
			ans = std::min(ans, fabs((p[id[pos[x] - 1]] - p[x]) * (p[y] - p[x])));
		}
		if (pos[y] < n) {
			ans = std::min(ans, fabs((p[id[pos[y] + 1]] - p[x]) * (p[y] - p[x])));
		}
		std::swap(pos[l[i].x], pos[l[i].y]);
		std::swap(id[pos[l[i].x]], id[pos[l[i].y]]);
	}
	printf("%.2f\n", ans / 2);
	return 0;
}