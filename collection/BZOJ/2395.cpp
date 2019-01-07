#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 210
#define MAXM 10010
typedef long long lnt;
int n, m, p[MAXN];
struct edge_t {
	int u, v, x, y, w;
	inline friend bool operator<(const edge_t &a, const edge_t &b) {
		return a.w < b.w;
	}
} es[MAXM];
struct point_t {
	int x, y;
	inline point_t(int x = 0, int y = 0) : x(x), y(y) {}
	inline point_t friend operator-(point_t a, point_t b) {
		return point_t(a.x - b.x, a.y - b.y);
	}
};
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
lnt ans = (~0ULL) >> 1;
int ansX, ansY;
inline point_t kruscal() {
	std::sort(es + 1, es + m + 1);
	for (int i = 0; i < n; i++) p[i] = i;
	int retX = 0, retY = 0;
	for (int i = 1; i <= m; i++) {
		int u = find(es[i].u), v = find(es[i].v);
		if (u == v) continue;
		p[u] = v;
		retX += es[i].x;
		retY += es[i].y;
	}
	lnt tmp = 1LL * retX * retY;
	if (tmp < ans || (tmp == ans && retX < ansX)) {
		ansX = retX;
		ansY = retY;
		ans = tmp;
	}
	return point_t(retX, retY);
}
inline lnt cross(point_t x, point_t y) {
	return 1LL * x.x * y.y - 1LL * x.y * y.x;
}
void solve(point_t A, point_t B) {
	for (int i = 1; i <= m; i++) es[i].w = (B.x - A.x) * es[i].y + (A.y - B.y) * es[i].x;
	point_t C = kruscal();
	if (cross(B - A, C - A) >= 0) return;
	solve(A, C);
	solve(C, B);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d%d", &es[i].u, &es[i].v, &es[i].x, &es[i].y);
	for (int i = 1; i <= m; i++) es[i].w = es[i].x;
	point_t A = kruscal();
	for (int i = 1; i <= m; i++) es[i].w = es[i].y;
	point_t B = kruscal();
	solve(A, B);
	printf("%d %d\n", ansX, ansY);
	return 0;
}