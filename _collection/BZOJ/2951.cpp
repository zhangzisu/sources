#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 20000
#define MAXV 100000
#define OFFSET 50000
struct point_t {
	int x, y;
	inline int friend operator<(point_t a, point_t b) {
		return a.x < b.x;
	}
} p[MAXN];
int n, h, w, ans = 0, max[MAXV << 2], tag[MAXV << 2];
inline void pushDown(int n) {
	if (tag[n]) {
		max[n << 1] += tag[n], max[n << 1 | 1] += tag[n];
		tag[n << 1] += tag[n], tag[n << 1 | 1] += tag[n];
		tag[n] = 0;
	}
}
void add(int n, int l, int r, int L, int R, int v) {
	if (l == L && r == R) return max[n] += v, tag[n] += v, void();
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid)
		add(n << 1, l, mid, L, R, v);
	else if (L > mid)
		add(n << 1 | 1, mid + 1, r, L, R, v);
	else
		add(n << 1, l, mid, L, mid, v), add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
int main() {
	scanf("%d%d%d", &w, &h, &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
	std::sort(p + 1, p + n + 1);
	for (int i = 1, j = 1; i <= n; i++) {
		for (; j <= n && p[j].x <= p[i].x + w; j++) {
			add(1, 1, MAXV, p[j].y - h + OFFSET, p[j].y + OFFSET, 1);
		}
		ans = std::max(ans, max[1]);
		add(1, 1, MAXV, p[i].y - h + OFFSET, p[i].y + OFFSET, -1);
	}
	printf("%d\n", ans);
	return 0;
}