#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10010
typedef long long lnt;
struct tag {
	lnt k, b;
	inline tag(lnt k = 1, lnt b = 0) : k(k), b(b) {}
	inline void merge(tag x) {
		k *= x.k;
		b = b * x.k + x.b;
	}
	inline bool friend operator==(tag a, tag b) {
		return a.k == b.k && a.b == b.b;
	}
	inline bool friend operator!=(tag a, tag b) {
		return !(a == b);
	}
} tags[MAXN << 2], e;
lnt sum[MAXN << 2], sum2[MAXN << 2];
inline void update(lnt &sum, lnt &sum2, int len, tag t) {
	sum2 = t.k * t.k * sum2 + 2 * t.k * t.b * sum + t.b * t.b * len;
	sum = t.k * sum + t.b * len;
}
inline int pushDown(int n, int l, int r) {
	int mid = (l + r) >> 1;
	if (tags[n] != e) {
		tags[n << 1].merge(tags[n]);
		tags[n << 1 | 1].merge(tags[n]);
		update(sum[n << 1], sum2[n << 1], mid - l + 1, tags[n]);
		update(sum[n << 1 | 1], sum2[n << 1 | 1], r - mid, tags[n]);
		tags[n] = e;
	}
	return mid;
}
void add(int n, int l, int r, int L, int R, tag v) {
	if (l == L && r == R) {
		tags[n].merge(v);
		update(sum[n], sum2[n], r - l + 1, v);
		return;
	}
	int mid = pushDown(n, l, r);
	if (R <= mid)
		add(n << 1, l, mid, L, R, v);
	else if (L > mid)
		add(n << 1 | 1, mid + 1, r, L, R, v);
	else
		add(n << 1, l, mid, L, mid, v), add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
	sum2[n] = sum2[n << 1] + sum2[n << 1 | 1];
}
lnt query(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return sum[n];
	int mid = pushDown(n, l, r);
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
	return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
lnt query2(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return sum2[n];
	int mid = pushDown(n, l, r);
	if (R <= mid) return query2(n << 1, l, mid, L, R);
	if (L > mid) return query2(n << 1 | 1, mid + 1, r, L, R);
	return query2(n << 1, l, mid, L, mid) + query2(n << 1 | 1, mid + 1, r, mid + 1, R);
}
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		lnt x;
		scanf("%lld", &x);
		add(1, 1, n, i, i, tag(1, x));
	}
	for (int op, l, r, x; m; m--) {
		scanf("%d%d%d", &op, &l, &r);
		switch (op) {
			case 1:
				printf("%lld\n", query(1, 1, n, l, r));
				break;
			case 2:
				printf("%lld\n", query2(1, 1, n, l, r));
				break;
			case 3:
				scanf("%d", &x);
				add(1, 1, n, l, r, tag(x, 0));
				break;
			case 4:
				scanf("%d", &x);
				add(1, 1, n, l, r, tag(1, x));
				break;
		}
	}
	return 0;
}