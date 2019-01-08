#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 80
const int INF = (~0U) >> 1;
struct point_t {
	int x, y;
	inline point_t(int x = 0, int y = 0) : x(x), y(y) {}
	inline point_t friend operator-(point_t a, point_t b) {
		return point_t(a.x - b.x, a.y - b.y);
	}
};
inline int cross(point_t a, point_t b) {
	return a.x * b.y - a.y * b.x;
}
int n, t, a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN], ans;
int match[MAXN], lx[MAXN], ly[MAXN], vx[MAXN], vy[MAXN], rlx[MAXN];
bool dfs(int x) {
	vx[x] = 1;
	for (int y = 1; y <= n; y++) {
		if (vy[y]) continue;
		int tmp = lx[x] + ly[y] - c[x][y];
		if (!tmp) {
			vy[y] = 1;
			if (!match[y] || dfs(match[y])) {
				match[y] = x;
				return 1;
			}
		} else {
			rlx[y] = std::min(rlx[y], tmp);
		}
	}
	return 0;
}
inline void KM() {
	for (int x = 1; x <= n; x++) {
		for (int i = 1; i <= n; i++) rlx[i] = INF;
		for (;;) {
			memset(vx, 0, sizeof(vx));
			memset(vy, 0, sizeof(vy));
			if (dfs(x)) break;
			int delta = INF;
			for (int i = 1; i <= n; i++)
				if (!vy[i]) delta = std::min(delta, rlx[i]);
			for (int i = 1; i <= n; i++)
				if (vx[i]) lx[i] -= delta;
			for (int i = 1; i <= n; i++) {
				if (vy[i]) {
					ly[i] += delta;
				} else {
					rlx[i] -= delta;
				}
			}
		}
	}
}
inline point_t init() {
	memset(match, 0, sizeof(match));
	memset(ly, 0, sizeof(ly));
	for (int i = 1; i <= n; i++) {
		lx[i] = -INF;
		for (int j = 1; j <= n; j++) {
			lx[i] = std::max(lx[i], c[i][j]);
		}
	}
	KM();
	int rX = 0, rY = 0;
	for (int i = 1; i <= n; i++) {
		if (match[i]) {
			rX += a[match[i]][i];
			rY += b[match[i]][i];
		}
	}
	ans = std::min(ans, rX * rY);
	return point_t(rX, rY);
}
void solve(point_t A, point_t B) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			c[i][j] = -((B.x - A.x) * b[i][j] + (A.y - B.y) * a[i][j]);
		}
	}
	point_t C = init();
	if (cross(B - A, C - A) >= 0) return;
	solve(A, C);
	solve(C, B);
}
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%d", &n);
		ans = INF;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &a[i][j]);
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &b[i][j]);
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				c[i][j] = -a[i][j];
			}
		}
		point_t A = init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				c[i][j] = -b[i][j];
			}
		}
		point_t B = init();
		solve(A, B);
		printf("%d\n", ans);
	}
	return 0;
}