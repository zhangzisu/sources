#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, max[MAXN << 2], ans[MAXN << 2];
int query(int n, int l, int r, int p) {
	if (l == r) return max[n] > p;
	if (max[n] <= p) return 0;
	int mid = (l + r) >> 1;
	int ret = query(n << 1, l, mid, p);
	if (max[n << 1 | 1] > max[n << 1]) ret += query(n << 1 | 1, mid + 1, r, std::max(p, max[n << 1]));
	return ret;
}
void build(int n, int l, int r) {
	if (l == r) {
		scanf("%d", &max[n]);
		ans[n] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
	ans[n] = ans[n << 1];
	if (max[n << 1 | 1] > max[n << 1]) ans[n] += query(n << 1 | 1, mid + 1, r, max[n << 1]);
}
void modify(int n, int l, int r, int p, int v) {
	if (l == r) {
		max[n] = v;
		return;
	}
	int mid = (l + r) >> 1;
	p <= mid ? modify(n << 1, l, mid, p, v) : modify(n << 1 | 1, mid + 1, r, p, v);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
	ans[n] = ans[n << 1];
	if (max[n << 1 | 1] > max[n << 1]) ans[n] += query(n << 1 | 1, mid + 1, r, max[n << 1]);
}
char buf[5];
int main() {
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for (int x, y; m; m--) {
		scanf("%s", buf);
		if (buf[0] == 'Q') {
			printf("%d\n", ans[1]);
		} else {
			scanf("%d%d", &x, &y);
			modify(1, 1, n, x, y);
		}
	}
	return 0;
}