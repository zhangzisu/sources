#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 400010
int n, m, k, a[MAXN], b[MAXN], c[MAXN], v[MAXN], bit[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y) {
    // printf("ADD %d %d\n", x, y);
	for (; x <= k; x += lowbit(x)) bit[x] += y;
}
inline int qry(int x) {
	int y = 0;
	for (; x; x -= lowbit(x)) y += bit[x];
	return y;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		v[++k] = a[i];
	}
	for (int i = 1, op; i <= m; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &c[i]);
		} else {
			scanf("%d%d", &b[i], &c[i]);
		}
		v[++k] = c[i];
	}
	std::sort(v + 1, v + k + 1);
	k = std::unique(v + 1, v + k + 1) - v - 1;
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(v + 1, v + k + 1, a[i]) - v;
		if (a[i] > a[i - 1]) {
			add(a[i - 1] + 1, 1);
			add(a[i] + 1, -1);
		}
	}
	for (int i = 1; i <= m; i++) {
		c[i] = std::lower_bound(v + 1, v + k + 1, c[i]) - v;
		if (b[i]) {
			int x = std::min(a[b[i] - 1], a[b[i] + 1]);
			int y = std::max(a[b[i] - 1], a[b[i] + 1]);
			if (a[b[i]] > y) {
				add(y + 1, -1);
				add(a[b[i]] + 1, 1);
			}
			add(1, 1);
			add(std::min(a[b[i]], x) + 1, -1);
			a[b[i]] = c[i];
			add(1, -1);
			add(std::min(a[b[i]], x) + 1, 1);
			if (a[b[i]] > y) {
				add(y + 1, 1);
				add(a[b[i]] + 1, -1);
			}
		} else {
			printf("%d\n", qry(c[i]));
		}
	}
	return 0;
}