#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 1048576
char _1[BUF], *_3 = _1 + BUF;
inline char gc() {
	if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
	return *_3++;
}
inline int $() {
	register int x = 0;
	register char ch = gc();
	while (!isdigit(ch)) ch = gc();
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
#define MAXN 100010
#define MAXV 100000
#define MAXM 50000010
int n, f[MAXN], v[MAXN], ans[MAXN];
int root[MAXN], L[MAXM], R[MAXM], max[MAXM], cnt = 0;
void insert(int &n, int l, int r, int p) {
	if (!n) n = ++cnt;
	if (l == r) return void(max[n] = p);
	int mid = (l + r) >> 1;
	p <= mid ? insert(L[n], l, mid, p) : insert(R[n], mid + 1, r, p);
	max[n] = std::max(max[L[n]], max[R[n]]);
}
int merge(int n0, int n1, int l, int r, int &t) {
	if (!(n0 && n1)) return n0 + n1;
	if (max[n0] == max[n1]) t = std::max(t, max[n0]);
	int mid = (l + r) >> 1;
	if (L[n0] || L[n1]) L[n0] = merge(L[n0], L[n1], l, mid, t);
	if (R[n0] || R[n1]) R[n0] = merge(R[n0], R[n1], mid + 1, r, t);
	max[n0] = std::max(max[L[n0]], max[R[n0]]);
	return n0;
}
int main() {
	n = $();
	for (int i = 2; i <= n; i++) assert((f[i] = $()) < i);
	for (int i = 1; i <= n; i++) {
		v[i] = $();
		for (int j = 1; j * j <= v[i]; j++) {
			if (v[i] % j) continue;
			insert(root[i], 1, MAXV, j);
			insert(root[i], 1, MAXV, v[i] / j);
		}
	}
	memset(ans, -1, sizeof(ans));
	for (int i = n; i > 1; i--) root[f[i]] = merge(root[f[i]], root[i], 1, MAXV, ans[f[i]]);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
