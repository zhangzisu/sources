#include <algorithm>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
int n, m, a[MAXN], vis[MAXN << 2];
std::complex<double> sum[MAXN << 2], tag[MAXN << 2];
inline void pushDown(int n) {
	if (vis[n]) {
		sum[n << 1] *= tag[n];
		sum[n << 1 | 1] *= tag[n];
		tag[n << 1] *= tag[n];
		tag[n << 1 | 1] *= tag[n];
		vis[n] = 0;
	}
}
inline void build(int n, int l, int r) {
	tag[n] = std::complex<double>(1, 0);
	if (l == r) {
		sum[n] = std::complex<double>(cos(1. * a[l]), sin(1. * a[l]));
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
inline void mul(int n, int l, int r, int L, int R, std::complex<double> v) {
	if (l == L && r == R) return sum[n] *= v, tag[n] *= v, void();
	int mid = (l + r) >> 1;
	if (R <= mid)
		mul(n << 1, l, mid, L, R, v);
	else if (L > mid)
		mul(n << 1 | 1, mid + 1, r, L, R, v);
	else
		mul(n << 1, l, mid, L, mid, v), mul(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
inline std::complex<double> query(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return sum[n];
	int mid = (l + r) >> 1;
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
	return query(n << 1, l, mid, L, mid) + query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	build(1, 1, n);
	scanf("%d", &m);
	for (int i = 1, l, r, op; i <= m; i++) {
		scanf("%d%d%d", &op, &l, &r);
		if (op == 1) {
			scanf("%d", &op);
			mul(1, 1, n, l, r, std::complex<double>(cos(1. * op), sin(1. * op)));
		} else {
			auto ret = query(1, 1, n, l, r);
			printf("%.1f\n", ret.imag());
		}
	}
	return 0;
}