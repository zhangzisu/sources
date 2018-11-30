#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MOD 1000000007
inline void up(int &x, int y) {
	if ((x += y) >= MOD) x -= MOD;
}
inline int sum(int a, int b) { return (a + b) >= MOD ? a + b - MOD : a + b; }
struct node {
	int max, cnt1, cnt2;
	inline node(int max = 0, int cnt1 = 1, int cnt2 = 0) : max(max), cnt1(cnt1), cnt2(cnt2) {}
	inline node friend operator+(const node &a, const node &b) {
		if (a.max < b.max) {
			return node(b.max, b.cnt1, (a.max == b.max - 1) ? sum(a.cnt1, b.cnt2) : b.cnt2);
		} else if (a.max > b.max) {
			return node(a.max, a.cnt1, (b.max == a.max - 1) ? sum(b.cnt1, a.cnt2) : a.cnt2);
		} else {
			return node(a.max, sum(a.cnt1, b.cnt1), sum(a.cnt2, b.cnt2));
		}
	}
} val[MAXN << 2];
void build(int n, int l, int r) {
	if (l == r) return val[n] = node(0, 0, 0), void();
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	val[n] = val[n << 1] + val[n << 1 | 1];
}
void update(int n, int l, int r, int p, node v) {
	val[n] = val[n] + v;
	if (l == r) return;
	int mid = (l + r) >> 1;
	p <= mid ? update(n << 1, l, mid, p, v) : update(n << 1 | 1, mid + 1, r, p, v);
	val[n] = val[n << 1] + val[n << 1 | 1];
}
node query(int n, int l, int r, int L, int R) {
	if (L > R) return node();
	if (l == L && r == R) return val[n];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
	return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
int T, n, m, a[MAXN], v[MAXN];
int main() {
	for (scanf("%d", &T); T; T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		memcpy(v + 1, a + 1, sizeof(int) * n);
		std::sort(v + 1, v + n + 1);
		m = std::unique(v + 1, v + n + 1) - v - 1;
		build(1, 0, m);
		update(1, 0, m, 1, node(0, 1, 0));
		for (int i = 1; i <= n; i++) {
			a[i] = std::lower_bound(v + 1, v + m + 1, a[i]) - v;
			auto ret = query(1, 0, m, 1, a[i] - 1);
			// printf("{max: %d, cnt1: %d, cnt2: %d}\n", ret.max, ret.cnt1, ret.cnt2);
			ret.max++;
			update(1, 0, m, a[i], ret);
		}
		printf("%d\n", val[1].cnt2);
	}
	return 0;
}