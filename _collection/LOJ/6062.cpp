#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 150010
int n, m, h, ans = 0;
int a[MAXN], b[MAXN], min[MAXN << 1], tag[MAXN << 1];
void build(int n, int l, int r) {
	if (l == r) {
		min[n] = l - ::m - 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	min[n] = std::min(min[n << 1], min[n << 1 | 1]);
}
inline void pushDown(int n) {
	if (tag[n]) {
		min[n << 1] += tag[n];
		min[n << 1 | 1] += tag[n];
		tag[n << 1] += tag[n];
		tag[n << 1 | 1] += tag[n];
		tag[n] = 0;
		return;
	}
}
void add(int n, int l, int r, int L, int R, int v) {
	if (l == L && r == R) return min[n] += v, tag[n] += v, void();
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid) {
		add(n << 1, l, mid, L, R, v);
	} else if (L > mid) {
		add(n << 1 | 1, mid + 1, r, L, R, v);
	} else {
		add(n << 1, l, mid, L, mid, v);
		add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	}
	min[n] = std::min(min[n << 1], min[n << 1 | 1]);
}
int main() {
	scanf("%d%d%d", &n, &m, &h);
	if (n < m) return puts("0"), 0;
	for (int i = 1; i <= m; i++) scanf("%d", b + i);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= m; i++) b[i] = h - b[i];
	std::sort(b + 1, b + m + 1);
	for (int i = 1; i <= n; i++) a[i] = std::upper_bound(b + 1, b + m + 1, a[i]) - b - 1;
	build(1, 1, m);
	for (int i = 1; i <= m; i++) {
		if (a[i]) add(1, 1, m, 1, a[i], 1);
	}
	ans += min[1] >= 0;
	for (int i = m + 1; i <= n; i++) {
		if (a[i - m]) add(1, 1, m, 1, a[i - m], -1);
		if (a[i]) add(1, 1, m, 1, a[i], 1);
		ans += min[1] >= 0;
	}
	printf("%d\n", ans);
	return 0;
}