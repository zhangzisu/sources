#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 400010
#define SQRT 640
int n, q, a[MAXN], belong[MAXN], left[SQRT], right[SQRT];
std::priority_queue<int> Q[SQRT], P[SQRT];
inline int _belong(int x) { return (x + SQRT - 1) / SQRT; }
inline void build(int x) {
	while (Q[x].size()) Q[x].pop();
	for (int i = left[x]; i <= right[x]; i++) Q[x].push(a[i]);
}
inline void gao(int x) {
	if (P[x].empty()) return;
	for (int i = left[x]; i <= right[x]; i++) {
		int min = -P[x].top();
		if (a[i] > min) {
			P[x].pop();
			P[x].push(-a[i]);
			a[i] = min;
		}
	}
	while (P[x].size()) P[x].pop();
	build(x);
}
inline void gaogao(int l, int r, int &v) {
	int L = belong[l];
	int R = belong[r];
	if (L == R) {
		gao(L);
		for (int i = l; i <= r; i++)
			if (a[i] > v) std::swap(a[i], v);
		build(L);
	} else {
		gao(L);
		gao(R);
		for (int i = l; i <= right[L]; i++)
			if (a[i] > v) std::swap(a[i], v);
		build(L);
		for (int i = L + 1; i < R; i++) {
			int x = Q[i].top();
			if (x > v) {
				Q[i].pop();
				Q[i].push(v);
				P[i].push(-v);
				v = x;
			}
		}
		for (int i = left[R]; i <= r; i++)
			if (a[i] > v) std::swap(a[i], v);
		build(R);
	}
}
int main() {
	scanf("%d%d", &n, &q);
	memset(left, 0x3F, sizeof(left));
	memset(right, 0, sizeof(right));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		Q[belong[i] = _belong(i)].push(a[i]);
		left[belong[i]] = std::min(i, left[belong[i]]);
		right[belong[i]] = std::max(i, right[belong[i]]);
	}
	fprintf(stderr, "PASS %d\n", __LINE__);
	for (int l, r, v; q; q--) {
		scanf("%d%d%d", &l, &r, &v);
		if (l <= r) {
			gaogao(l, r, v);
		} else {
			gaogao(l, n, v);
			gaogao(1, r, v);
		}
		printf("%d\n", v);
	}
	return 0;
}