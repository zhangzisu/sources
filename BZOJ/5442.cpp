#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
#define MAXM 5000010
int n, m, x, a[MAXN], b[MAXN], v[MAXN], root[MAXN];
int L[MAXM], R[MAXM], max[MAXM], cnt, ans;
inline int insert(int n, int l, int r, int p, int v) {
	int m = ++cnt;
	L[m] = L[n], R[m] = R[n], max[m] = std::max(max[n], v);
	if (l == r) return m;
	int mid = (l + r) >> 1;
	p <= mid ? L[m] = insert(L[n], l, mid, p, v) : R[m] = insert(R[n], mid + 1, r, p, v);
	return m;
}
inline int query(int n, int l, int r, int _l, int _r) {
	if (!n || _l > _r) return 0;
	if (l == _l && r == _r) return max[n];
	int mid = (l + r) >> 1;
	if (_r <= mid) return query(L[n], l, mid, _l, _r);
	if (_l > mid) return query(R[n], mid + 1, r, _l, _r);
	return std::max(query(L[n], l, mid, _l, mid), query(R[n], mid + 1, r, mid + 1, _r));
}
int bit[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void upd(int x, int y) {
	for (; x <= m; x += lowbit(x)) bit[x] = std::max(bit[x], y);
}
inline int qry(int x) {
	int y = 0;
	for (; x; x -= lowbit(x)) y = std::max(y, bit[x]);
	return y;
}
int main() {
	scanf("%d%d", &n, &x);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), v[i] = a[i];
	std::sort(v + 1, v + n + 1);
	m = std::unique(v + 1, v + n + 1) - v - 1;
	for (int i = n; i >= 1; i--) {
		b[i] = std::lower_bound(v + 1, v + m + 1, a[i]) - v;
		int val = query(root[i + 1], 1, m, b[i] + 1, m) + 1;
		root[i] = insert(root[i + 1], 1, m, b[i], val);
	}
	ans = query(root[1], 1, m, 1, m);
	for (int i = 1; i <= n; i++) {
		int val = qry(b[i] - 1) + 1;
		int pos = std::lower_bound(v + 1, v + m + 1, a[i] - x + 1) - v;
		ans = std::max(ans, val + query(root[i + 1], 1, m, pos, m));
		upd(b[i], val);
	}
	printf("%d\n", ans);
	return 0;
}