#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
int n, m, q, a[MAXN], b[MAXN], sum[MAXN << 2], lans = 0;
std::vector<int> val[MAXN << 2];
void fuck(int n, int l, int r) {
	if (l == r) return sum[n] = 1, void();
	int mid = (l + r) >> 1;
	fuck(n << 1, l, mid);
	fuck(n << 1 | 1, mid + 1, r);
	sum[n] = sum[n << 1] + sum[n << 1 | 1];
}
void build(int n, int l, int r, int L, int R, int id) {
	if (l == L && r == R) {
		val[n].push_back(id);
		b[id]++;
		return;
	}
	int mid = (l + r) >> 1;
	if (R <= mid) return build(n << 1, l, mid, L, R, id);
	if (L > mid) return build(n << 1 | 1, mid + 1, r, L, R, id);
	build(n << 1, l, mid, L, mid, id);
	build(n << 1 | 1, mid + 1, r, mid + 1, R, id);
}
void update(int n, int l, int r, int p) {
	if (!--sum[n]) {
		for (int i = 0; i < (int)val[n].size(); i++) {
			if (!--b[val[n][i]]) lans++;
		}
	}
	if (l == r) return;
	int mid = (l + r) >> 1;
	p <= mid ? update(n << 1, l, mid, p) : update(n << 1 | 1, mid + 1, r, p);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1, l, r; i <= m; i++) {
		scanf("%d%d", &l, &r);
		build(1, 1, n, l, r, i);
	}
	fuck(1, 1, n);
	for (int x = scanf("%d", &q); q; q--) {
		scanf("%d", &x);
		x = (x + lans - 1) % n + 1;
		if (!--a[x]) {
			update(1, 1, n, x);
		}
		printf("%d\n", lans);
	}
	return 0;
}