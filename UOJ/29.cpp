#include <algorithm>
#include <cstdlib>
#include <cstring>
#include "holiday.h"
#define MAXN 250010
#define MAXM 5000010
typedef long long lnt;
int n, m, s, d, cnt = 0, _r[MAXN], *root = _r + 1, a[MAXN], v[MAXN], L[MAXM], R[MAXM], count[MAXM];
lnt sum[MAXM], f[MAXN], g[MAXN], F[MAXN], G[MAXN], ans;
void insert(int &n, int m, int l, int r, int p) {
	n = ++cnt;
	L[n] = L[m], R[n] = R[m];
	count[n] = count[m] + 1, sum[n] = sum[m] + v[p];
	if (l == r) return;
	int mid = (l + r) >> 1;
	p <= mid ? insert(L[n], L[m], l, mid, p) : insert(R[n], R[m], mid + 1, r, p);
}
lnt query(int n, int m, int l, int r, int c) {
	if (count[n] - count[m] <= c) return sum[n] - sum[m];
	if (l == r) return 1LL * v[l] * c;
	int mid = (l + r) >> 1;
	if (count[R[n]] - count[R[m]] >= c) return query(R[n], R[m], mid + 1, r, c);
	return query(L[n], L[m], l, mid, c - (count[R[n]] - count[R[m]])) + sum[R[n]] - sum[R[m]];
}
void solve0(int l, int r, int L, int R) {
	if (l > r || L > R) return;
	int mid = (l + r) >> 1, MID = f[mid] = 0;
	for (int i = L; i <= R && mid - i + s >= 0; i++) {
		lnt val = query(root[i], root[s], 0, m - 1, mid - (i - s));
		if (val >= f[mid]) {
			f[mid] = val;
			MID = i;
		}
	}
	if (l == r) return;
	solve0(l, mid - 1, L, MID);
	solve0(mid + 1, r, MID, R);
}
void solve1(int l, int r, int L, int R) {
	if (l > r || L > R) return;
	int mid = (l + r) >> 1, MID = g[mid] = 0;
	for (int i = R; i >= L && mid - s + i >= 0; i--) {
		lnt val = query(root[s - 1], root[i - 1], 0, m - 1, mid - (s - i));
		if (val >= g[mid]) {
			g[mid] = val;
			MID = i;
		}
	}
	if (l == r) return;
	solve1(l, mid - 1, MID, R);
	solve1(mid + 1, r, L, MID);
}
void solve2(int l, int r, int L, int R) {
	if (l > r || L > R) return;
	int mid = (l + r) >> 1, MID = F[mid] = 0;
	for (int i = L; i <= R && mid - 2 * (i - s) >= 0; i++) {
		lnt val = query(root[i], root[s], 0, m - 1, mid - 2 * (i - s));
		if (val >= F[mid]) {
			F[mid] = val;
			MID = i;
		}
	}
	if (l == r) return;
	solve2(l, mid - 1, L, MID);
	solve2(mid + 1, r, MID, R);
}
void solve3(int l, int r, int L, int R) {
	if (l > r || L > R) return;
	int mid = (l + r) >> 1, MID = G[mid] = 0;
	for (int i = R; i >= L && mid - 2 * (s - i) >= 0; i--) {
		lnt val = query(root[s - 1], root[i - 1], 0, m - 1, mid - 2 * (s - i));
		if (val >= G[mid]) {
			G[mid] = val;
			MID = i;
		}
	}
	if (l == r) return;
	solve3(l, mid - 1, MID, R);
	solve3(mid + 1, r, L, MID);
}
lnt solve() {
	root[-1] = 0;
	memcpy(v, a, sizeof(int) * n);
	std::sort(v, v + n);
	m = std::unique(v, v + n) - v;
	for (int i = 0; i < n; i++) {
		a[i] = std::lower_bound(v, v + m, a[i]) - v;
		insert(root[i], root[i - 1], 0, m - 1, a[i]);
	}
	solve0(0, d, s + 1, n - 1);
	solve1(0, d, 0, s - 1);
	solve2(0, d, s + 1, n - 1);
	solve3(0, d, 0, s - 1);
	for (int i = 0; i <= d; i++) ans = std::max(ans, std::max(f[i] + G[d - i], g[i] + F[d - i]));
	for (int i = 0; i < d; i++) ans = std::max(ans, std::max(f[i] + G[d - i - 1], g[i] + F[d - i - 1]) + v[a[s]]);
	return ans;
}
lnt findMaxAttraction(int n, int s, int d, int attr[]) {
	::n = n;
	::s = s;
	::d = d;
	memcpy(a, attr, sizeof(int) * n);
	return solve();
}

#ifdef DEBUG
#include <cstdio>
int main() {
    freopen("in", "r", stdin);
	int n, start, d;
	int attraction[100000];
	int i, n_s;
	n_s = scanf("%d %d %d", &n, &start, &d);
	for (i = 0; i < n; ++i) {
		n_s = scanf("%d", &attraction[i]);
	}
	printf("%lld\n", findMaxAttraction(n, start, d, attraction));
	return 0;
}
#endif