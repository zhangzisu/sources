#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 210
#define SQRT 15
#define MAXM 100010
int n, m, q, k, l, r, u, d, now, a[MAXN][MAXN], v[MAXN * MAXN], ans[MAXN];
struct query_t {
	int x1, y1, x2, y2, id;
	inline int friend operator<(const query_t &a, const query_t &b) {
		if (a.x1 / SQRT == b.x1 / SQRT) {
			if (a.y1 / SQRT == b.y1 / SQRT) {
				if (a.x2 / SQRT == b.x2 / SQRT) {
					return a.y2 < b.y2;
				} else
					return a.x2 < b.x2;
			} else
				return a.y1 < b.y1;
		} else
			return a.x1 < b.x1;
	}
} query[MAXN];
inline void fuckRow(int c, int t) {
	for (int i = l; i <= r; i++) {
		now -= v[a[c][i]] * v[a[c][i]];
		v[a[c][i]]++;
		now += v[a[c][i]] * v[a[c][i]];
	}
}
inline void fuckCol(int r, int t) {
	for (int i = u; i <= d; i++) {
		now -= v[a[i][r]] * v[a[i][r]];
		v[a[i][r]]++;
		now += v[a[i][r]] * v[a[i][r]];
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			v[++k] = a[i][j];
		}
	}
	std::sort(v + 1, v + k + 1);
	k = std::unique(v + 1, v + k + 1) - v - 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			a[i][j] = std::lower_bound(v + 1, v + k + 1, a[i][j]) - v;
		}
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d%d%d", &query[i].x1, &query[i].y1, &query[i].x2, &query[i].y2);
		if (query[i].x1 > query[i].x2) std::swap(query[i].x1, query[i].x2);
		if (query[i].y1 > query[i].y2) std::swap(query[i].y1, query[i].y2);
		query[i].id = i;
	}
	std::sort(query + 1, query + q + 1);
	memset(v, 0, sizeof(v));
	l = 1, r = 1, u = 1, d = 1, now = v[a[1][1]] = 1;
	for (int i = 1; i <= q; i++) {
		while (r < query[i].y2) fuckCol(++r, 1);
		while (d < query[i].x2) fuckRow(++d, 1);
		while (l > query[i].y1) fuckCol(--l, 1);
		while (u > query[i].x1) fuckRow(--u, 1);
		while (r > query[i].y2) fuckCol(r--, -1);
		while (d > query[i].x2) fuckRow(d--, -1);
		while (l < query[i].y1) fuckCol(l++, -1);
		while (u < query[i].x1) fuckRow(u++, -1);
		ans[query[i].id] = now;
	}
	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0;
}