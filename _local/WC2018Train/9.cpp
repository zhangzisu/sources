#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
const int INF = 0x3F3F3F3F;
int n, m, a[MAXN], v[MAXN], id[MAXN], ans;
int max[MAXN << 2], tag[MAXN << 2], L[MAXN << 2], R[MAXN << 2], cnt;
inline void ensure(int &n) {
	if (!n) {
		n = ++cnt;
		max[n] = -INF;
		L[n] = R[n] = tag[n] = 0;
	}
}
inline void pushDown(int n) {
	if (tag[n]) {
		ensure(L[n]);
		ensure(R[n]);
		max[L[n]] += tag[n];
		tag[L[n]] += tag[n];
		max[R[n]] += tag[n];
		tag[R[n]] += tag[n];
		tag[n] = 0;
	}
}
inline void pushUp(int n) {
	max[n] = -INF;
	if (L[n] && max[L[n]] > max[n]) max[n] = max[L[n]];
	if (R[n] && max[R[n]] > max[n]) max[n] = max[R[n]];
}
void set(int &n, int l, int r, int p, int v) {
	ensure(n);
	if (l == r) return max[n] = v, void();
	pushDown(n);
	int mid = (l + r) >> 1;
	p <= mid ? set(L[n], l, mid, p, v) : set(R[n], mid + 1, r, p, v);
	pushUp(n);
}
void add(int &n, int l, int r, int _l, int _r, int v) {
	if (_r < _l) return;
	ensure(n);
	if (l == _l && r == _r) return max[n] += v, tag[n] += v, void();
	int mid = (l + r) >> 1;
	pushDown(n);
	if (_r <= mid)
		add(L[n], l, mid, _l, _r, v);
	else if (_l > mid)
		add(R[n], mid + 1, r, _l, _r, v);
	else
		add(L[n], l, mid, _l, mid, v), add(R[n], mid + 1, r, mid + 1, _r, v);
	pushUp(n);
}
int bit[MAXN], tim[MAXN], bitclk;
inline void clear() {
	++bitclk;
}
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y) {
	for (; x <= n; x += lowbit(x)) bit[x] = tim[x] == bitclk ? bit[x] + y : y;
}
inline int qry(int x) {
	int y = 0;
	for (; x; x -= lowbit(x)) y += tim[x] == bitclk ? bit[x] : 0;
	return y;
}
lnt all;
int upper[MAXN], lower[MAXN], u, l;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	bool flag = 1;
	for (int i = 1; i <= n; i++) flag &= ((a[i] - a[1]) == i - 1);
	if (flag) return puts("1"), 0;
	memcpy(v + 1, a + 1, sizeof(int) * n);
	std::sort(v + 1, v + n + 1);
	m = std::unique(v + 1, v + n + 1) - v - 1;
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(v + 1, v + m + 1, a[i]) - v;
	for (int i = n; i >= 1; i--) all += qry(a[i]), add(a[i], 1);
	for (int i = 1; i <= n; i++) {
		if (a[i] > upper[u]) upper[++u] = i;
	}
	for (int i = n; i >= 1; i--) {
		if (a[i] < lower[l]) lower[++l] = i;
	}
	printf("%lld\n", all - ans);
	return 0;
}