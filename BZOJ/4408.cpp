#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
#define MAXM 5000010
int n, m, q, a[MAXN], root[MAXN], sum[MAXM], L[MAXM], R[MAXM], cnt = 0;
inline void copy(int &n, int m) {
	n = ++cnt;
	sum[n] = sum[m], L[n] = L[m], R[n] = R[m];
}
void add(int &n, int m, int l, int r, int p) {
	copy(n, m);
	sum[n] += p;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (p <= mid) {
		add(L[n], L[m], l, mid, p);
	} else {
		add(R[n], R[m], mid + 1, r, p);
	}
}
int query(int n, int m, int l, int r, int _l, int _r) {
	if (l == _l && r == _r) return sum[n] - sum[m];
	int mid = (l + r) >> 1;
	if (_r <= mid) return query(L[n], L[m], l, mid, _l, _r);
	if (_l > mid) return query(R[n], R[m], mid + 1, r, _l, _r);
	return query(L[n], L[m], l, mid, _l, mid) + query(R[n], R[m], mid + 1, r, mid + 1, _r);
}
int main() {
	for (int i = scanf("%d", &n); i <= n; i++) scanf("%d", &a[i]), m = std::max(m, a[i]);
	for (int i = 1; i <= n; i++) add(root[i], root[i - 1], 1, m, a[i]);
	for (int l, r = scanf("%d", &q), ans, tmp; q; q -= (printf("%d\n", ans), 1)) {
		for (ans = (scanf("%d%d", &l, &r), 1);; ans = tmp + 1) {
			tmp = query(root[r], root[l - 1], 1, m, 1, std::min(ans, m));
			if (ans > tmp) break;
		}
	}
	return 0;
}