#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
#define MAXM 500010
typedef long long lnt;
std::vector<int> V;
int n, q, a[MAXN], xl[MAXN], xr[MAXN], stk[MAXN], top;
int root[5][MAXN], all[5], L[5][MAXM], R[5][MAXM];
lnt sum[5][MAXM];
inline void insert(int &n, int m, int l, int r, int p, lnt v, int id) {
	n = ++all[id];
	sum[id][n] = sum[id][m] + v;
	L[id][n] = L[id][m];
	R[id][n] = R[id][m];
	if (l == r) return;
	int mid = (l + r) >> 1;
	p <= mid ? insert(L[id][n], L[id][m], l, mid, p, v, id) : insert(R[id][n], R[id][m], mid + 1, r, p, v, id);
}
inline lnt query(int n, int m, int l, int r, int _l, int _r, int id) {
	if (_l > _r) return 0;
	if (l == _l && r == _r) return sum[id][n] - sum[id][m];
	int mid = (l + r) >> 1;
	if (_r <= mid) return query(L[id][n], L[id][m], l, mid, _l, _r, id);
	if (_l > mid) return query(R[id][n], R[id][m], mid + 1, r, _l, _r, id);
	return query(L[id][n], L[id][m], l, mid, _l, mid, id) + query(R[id][n], R[id][m], mid + 1, r, mid + 1, _r, id);
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), V.push_back(a[i]);
	std::sort(V.begin(), V.end());
	V.erase(std::unique(V.begin(), V.end()), V.end());
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(V.begin(), V.end(), a[i]) - V.begin();
	a[stk[top = 0] = 0] = -1;
	for (int i = 1; i <= n; i++) {
		while (top && a[stk[top]] > a[i]) top--;
		xl[i] = stk[top] + 1;
		stk[++top] = i;
	}
	a[stk[top = 0] = n + 1] = -1;
	for (int i = n; i >= 1; i--) {
		while (top && a[stk[top]] > a[i]) top--;
		xr[i] = stk[top] - 1;
		stk[++top] = i;
	}
	for (int i = 1; i <= n; i++) printf("%d: %d - %d\n", i, xl[i], xr[i]);
	for (int i = 1; i <= n; i++) {
		int l = xl[i];
		int r = xr[i];
		int L = i - l + 1;
		int R = r - i + 1;
		insert(root[0][i], root[0][i - 1], 1, n, i, 1LL * L * R * V[a[i]], 0);
		insert(root[1][i], root[1][i - 1], 1, n, xl[i], 1LL * R * V[a[i]], 1);
		insert(root[2][i], root[2][i - 1], 1, n, xl[i], 1LL * l * R * V[a[i]], 2);
		insert(root[3][i], root[3][i - 1], 1, n, xr[i], 1LL * L * V[a[i]], 3);
		insert(root[4][i], root[4][i - 1], 1, n, xr[i], 1LL * r * L * V[a[i]], 4);
	}
	for (int l, r; q; q--) {
		scanf("%d%d", &l, &r);
		long long ans = query(root[0][r], root[0][l - 1], 1, n, l, r, 0);
		ans -= query(root[1][r], root[1][l - 1], 1, n, 1, l - 1, 1) * l;
		ans += query(root[2][r], root[2][l - 1], 1, n, 1, l - 1, 2);
		ans += query(root[3][r], root[3][l - 1], 1, n, r + 1, n, 3) * r;
		ans -= query(root[4][r], root[4][l - 1], 1, n, r + 1, n, 4);
		printf("%lld\n", ans);
	}
	return 0;
}