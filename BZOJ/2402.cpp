#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 30010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], n, m, dfsclk, tot = 0;
int deep[MAXN], top[MAXN], size[MAXN], fa[MAXN], dfn[MAXN], pos[MAXN];
inline void $(int u, int v) {
	next[tot] = head[u], to[tot] = v, head[u] = tot++;
	next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
const double EPS = 1e-7;
struct point_t {
	double x, y;
	inline point_t(double x = 0, double y = 0) : x(x), y(y) {}
	inline int friend operator<(point_t a, point_t b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	}
	inline point_t friend operator-(point_t a, point_t b) {
		return point_t(a.x - b.x, a.y - b.y);
	}
	inline double friend operator*(point_t a, point_t b) {
		return a.x * b.y - a.y * b.x;
	}
} rx[MAXN], ry[MAXN], tmp[MAXN];
std::vector<point_t> px[MAXN << 2], py[MAXN << 2];
inline void insert(std::vector<point_t>& ret, point_t p) {
	while ((int)ret.size() >= 2) {
		if ((p - ret.back()) * (ret.back() - ret[ret.size() - 2]) < EPS) {
			ret.pop_back();
		} else {
			break;
		}
	}
	ret.push_back(p);
}
inline void merge(std::vector<point_t>& ret, const std::vector<point_t>& l, const std::vector<point_t>& r) {
	int L = (int)l.size(), R = (int)r.size();
	ret.clear();
	for (int i = 0, j = 0; i < L || j < R;) {
		if (i != L && (j == R || l[i] < r[j])) {
			insert(ret, l[i++]);
		} else {
			insert(ret, r[j++]);
		}
	}
}
void build(int n, int l, int r) {
	if (l == r) {
		px[n].push_back(rx[pos[l]]);
		py[n].push_back(ry[pos[l]]);
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	merge(px[n], px[n << 1], px[n << 1 | 1]);
	merge(py[n], py[n << 1], py[n << 1 | 1]);
}
inline double calc(point_t p, double k) {
	return p.y - k * p.x;
}
inline void update(const std::vector<point_t>& val, double k, double& ret) {
	ret = std::max(ret, calc(val[0], k));
	int l = 1, r = (int)val.size() - 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		double vl = calc(val[mid-1], k);
		double vr = calc(val[mid], k);
		ret = std::max(ret, vl);
		ret = std::max(ret, vr);
		if (vl < vr + EPS)
			l = mid + 1;
		else
			r = mid - 1;
	}
}
void query(int n, int l, int r, int L, int R, double k, double& ax, double& ay) {
	if (l == L && r == R) {
		update(px[n], k, ax);
		update(py[n], k, ay);
		return;
	}
	int mid = (l + r) >> 1;
	if (R <= mid) return query(n << 1, l, mid, L, R, k, ax, ay);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R, k, ax, ay);
	query(n << 1, l, mid, L, mid, k, ax, ay);
	query(n << 1 | 1, mid + 1, r, mid + 1, R, k, ax, ay);
}
void pre(int x) {
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x]) continue;
		fa[to[i]] = x;
		deep[to[i]] = deep[x] + 1;
		pre(to[i]);
		size[x] += size[to[i]];
	}
}
void split(int x) {
	pos[dfn[x] = ++dfsclk] = x;
	if (!top[x]) top[x] = x;
	int max = 0;
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && size[to[i]] > size[max]) max = to[i];
	if (max) top[max] = top[x], split(max);
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && to[i] != max) split(to[i]);
}
inline double check(int u, int v, double k) {
	double ansx = -1e10, ansy = -1e10;
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) std::swap(u, v);
		query(1, 1, n, dfn[top[u]], dfn[u], k, ansx, ansy);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) std::swap(u, v);
	query(1, 1, n, dfn[u], dfn[v], k, ansx, ansy);
	return ansx + ansy;
}
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lf", &rx[i].x);
	for (int i = 1; i <= n; i++) scanf("%lf", &rx[i].y);
	for (int i = 1; i <= n; i++) scanf("%lf", &ry[i].x);
	for (int i = 1; i <= n; i++) scanf("%lf", &ry[i].y);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		$(u, v);
	}
	pre(1);
	split(1);
    build(1, 1, n);
	for (int u, v = scanf("%d", &m); m; m--) {
		scanf("%d%d", &u, &v);
		double l = 0, r = 1e8;
		while (r - l > EPS) {
			double mid = (l + r) / 2;
			if (check(u, v, mid) > -EPS)
				l = mid;
			else
				r = mid;
		}
		printf("%.4f\n", (l + r) / 2);
	}
	return 0;
}