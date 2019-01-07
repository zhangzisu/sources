#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
const int BIT_PREFIX = 100005, BIT_MAXN = BIT_PREFIX * 2;
const int INF = (~0U) >> 1;
int n, m, k, a[MAXN], b[MAXN], v[MAXN];
int bit[MAXN << 1];
inline int lowbit(int x) { return x & -x; }
inline void _set(int x, int v) {
	for (; x <= BIT_MAXN; x += lowbit(x)) bit[x] = std::min(bit[x], v);
}
inline int _get(int x) {
	int v = INF;
	for (; x; x -= lowbit(x)) v = std::min(v, bit[x]);
	return v;
}
inline void set(int x, int v) { _set(x + BIT_PREFIX, v); }
inline int get(int x) { return _get(x + BIT_PREFIX); }
inline bool judge(int mid) {
	for (int i = 1; i <= n; i++) b[i] = a[i] >= mid ? 1 : -1;
	for (int i = 1; i <= n; i++) b[i] += b[i - 1];
	memset(bit, 0x3F, sizeof(bit));
	set(0, 0);
	for (int i = 1; i <= n; i++) {
		if (get(b[i] - 1) <= i - k) return 1;
		set(b[i], i);
	}
	return 0;
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	memcpy(v, a, sizeof(v));
	std::sort(v + 1, v + n + 1);
	m = std::unique(v + 1, v + n + 1) - v - 1;
	int l = 1, r = m, ans = 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (judge(v[mid]))
			ans = mid, l = mid + 1;
		else
			r = mid - 1;
	}
	printf("%d\n", v[ans]);
	return 0;
}