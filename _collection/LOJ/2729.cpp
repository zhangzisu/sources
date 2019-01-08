#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 500010
int n, m, k, ans[MAXN], bit[MAXN];
struct point_t {
	int x, y;
} p[MAXN];
struct query_t {
	int x, y, id;
} q[MAXN];
std::vector<int> v;
inline void up(int &x, int y) {
	if (y > x) x = y;
}
inline int lowbit(int x) { return x & -x; }
inline void gao(int x, int v) {
	for (; x; x -= lowbit(x)) up(bit[x], v);
}
inline int qry(int x) {
	int v = 0;
	for (; x <= k; x += lowbit(x)) up(v, bit[x]);
	return v;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y), v.push_back(p[i].x);
	for (int i = 1; i <= m; i++) scanf("%d%d", &q[i].x, &q[i].y), q[i].id = i, v.push_back(q[i].x);
	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());
	k = (int)v.size();
	for (int i = 1; i <= n; i++) p[i].x = std::lower_bound(v.begin(), v.end(), p[i].x) - v.begin() + 1;
	for (int i = 1; i <= m; i++) q[i].x = std::lower_bound(v.begin(), v.end(), q[i].x) - v.begin() + 1;
	std::sort(p + 1, p + n + 1, [](point_t a, point_t b) { return a.y == b.y ? a.x > b.x : a.y < b.y; });
	std::sort(q + 1, q + m + 1, [](query_t a, query_t b) { return a.y == b.y ? a.x > b.x : a.y < b.y; });
	for (int i = 1, j = 1; i <= m; i++) {
		for (; j <= n && p[j].y <= q[i].y; j++) gao(p[j].x, qry(p[j].x) + 1);
		ans[q[i].id] = qry(q[i].x);
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}