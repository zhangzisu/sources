#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
lnt min[MAXN << 2], max[MAXN << 2], sum[MAXN << 2], tag[MAXN << 2];
void build(int n, int l, int r) {
	if (l == r) {
		scanf("%lld", &sum[n]);
		max[n] = min[n] = sum[n];
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	min[n] = std::min(min[n << 1], min[n << 1 | 1]);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
inline int pushDown(int n, int l, int r) {
	int mid = (l + r) >> 1;
	if (tag[n]) {
		min[n << 1] += tag[n], max[n << 1] += tag[n], tag[n << 1] += tag[n], sum[n << 1] += tag[n] * (mid - l + 1);
		min[n << 1 | 1] += tag[n], max[n << 1 | 1] += tag[n], tag[n << 1 | 1] += tag[n], sum[n << 1 | 1] += tag[n] * (r - mid);
		tag[n] = 0;
	}
	return mid;
}
void add(int n, int l, int r, int L, int R, lnt v) {
	if (l == L && r == R) {
		min[n] += v, max[n] += v, tag[n] += v, sum[n] += (r - l + 1) * v;
		return;
	}
	int mid = pushDown(n, l, r);
	if (R <= mid) {
		add(n << 1, l, mid, L, R, v);
	} else if (L > mid) {
		add(n << 1 | 1, mid + 1, r, L, R, v);
	} else {
		add(n << 1, l, mid, L, mid, v);
		add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	}
	min[n] = std::min(min[n << 1], min[n << 1 | 1]);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
void div(int n, int l, int r, int L, int R, lnt v) {
	if (l == L && r == R && (min[n] == max[n] || (min[n] + 1 == max[n] && max[n] % v == 0))) {
		lnt d = (lnt)floor(1. * min[n] / v) - min[n];
		min[n] += d, max[n] += d, tag[n] += d, sum[n] += (r - l + 1) * d;
		return;
	}
	int mid = pushDown(n, l, r);
	if (R <= mid) {
		div(n << 1, l, mid, L, R, v);
	} else if (L > mid) {
		div(n << 1 | 1, mid + 1, r, L, R, v);
	} else {
		div(n << 1, l, mid, L, mid, v);
		div(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	}
	min[n] = std::min(min[n << 1], min[n << 1 | 1]);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
lnt qs(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return sum[n];
	int mid = pushDown(n, l, r);
	if (R <= mid) return qs(n << 1, l, mid, L, R);
	if (L > mid) return qs(n << 1 | 1, mid + 1, r, L, R);
	return qs(n << 1, l, mid, L, mid) + qs(n << 1 | 1, mid + 1, r, mid + 1, R);
}
lnt qm(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return min[n];
	int mid = pushDown(n, l, r);
	if (R <= mid) return qm(n << 1, l, mid, L, R);
	if (L > mid) return qm(n << 1 | 1, mid + 1, r, L, R);
	return std::min(qm(n << 1, l, mid, L, mid), qm(n << 1 | 1, mid + 1, r, mid + 1, R));
}
int n, q;
int main() {
	scanf("%d%d", &n, &q);
	build(1, 0, n - 1);
	lnt x;
	for (int op, l, r; q; q--) {
		scanf("%d%d%d", &op, &l, &r);
		switch (op) {
			case 1:
				scanf("%lld", &x);
				add(1, 0, n - 1, l, r, x);
				break;
			case 2:
				scanf("%lld", &x);
				div(1, 0, n - 1, l, r, x);
				break;
			case 3:
				printf("%lld\n", qm(1, 0, n - 1, l, r));
				break;
			case 4:
				printf("%lld\n", qs(1, 0, n - 1, l, r));
				break;
		}
	}
	return 0;
}