#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
const int INF = 0x3F3F3F3F;
int n, m, a[MAXN], v[MAXN], ans;
int max[MAXN << 2], tag[MAXN << 2];
inline void pushDown(int n) {
	if (tag[n]) {
		max[n << 1] += tag[n];
		tag[n << 1] += tag[n];
		max[n << 1 | 1] += tag[n];
		tag[n << 1 | 1] += tag[n];
		tag[n] = 0;
	}
}
inline void add(int n, int l, int r, int L, int R, int v) {
	if (L > R) return;
	if (l == L && r == R) return max[n] += v, tag[n] += v, void();
	pushDown(n);
	int mid = (l + r) >> 1;
	if (R <= mid) {
		add(n << 1, l, mid, L, R, v);
	} else if (L > mid) {
		add(n << 1 | 1, mid + 1, r, L, R, v);
	} else {
		add(n << 1, l, mid, L, mid, v);
		add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	}
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
inline void set(int n, int l, int r, int p, int v) {
	if (l == r) return max[n] = v, void();
	pushDown(n);
	int mid = (l + r) >> 1;
	p <= mid ? set(n << 1, l, mid, p, v) : set(n << 1 | 1, mid + 1, r, p, v);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
lnt all;
int upper[MAXN], lower[MAXN], mask[MAXN], cx[MAXN], cy[MAXN], u, l, c;
inline void add(int x, int v) {
	int left = std::upper_bound(upper + 1, upper + u + 1, x, [](int x, int y) { return a[x] < a[y]; }) - upper;
	int right = std::upper_bound(upper + 1, upper + u + 1, x) - upper - 1;
	// printf("ADD %d %d, left %d (%d), right %d (%d)\n", x, v, left, upper[left], right, upper[right]);
	add(1, 1, u, left, right, v);
}
namespace BIT {
int bit[MAXN];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y) {
	for (; x <= m; x += lowbit(x)) bit[x] += y;
}
inline int qry(int x) {
	int y = 0;
	for (; x; x -= lowbit(x)) y += bit[x];
	return y;
}
}  // namespace BIT
int main() {
	std::fill(max, max + sizeof(max) / sizeof(int), -INF);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	memcpy(v + 1, a + 1, sizeof(int) * n);
	std::sort(v + 1, v + n + 1);
	m = std::unique(v + 1, v + n + 1) - v - 1;
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(v + 1, v + m + 1, a[i]) - v;
	for (int i = n; i >= 1; i--) all += BIT::qry(a[i] - 1), BIT::add(a[i], 1);
	
	mask[upper[u = 1] = 1] = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i] > a[upper[u]]) mask[upper[++u] = i] = 1;
	}
	mask[lower[l = 1] = n] = 1;
	for (int i = n - 1; i >= 1; i--) {
		if (a[i] < a[lower[l]]) mask[lower[++l] = i] = 1;
	}
	std::reverse(lower + 1, lower + l + 1);
	for(int i = 1;i <= n;i++)if(!mask[i])cx[++c] = i;
	memcpy(cy+1,cx+1, sizeof(int)*c);
	std::sort(cy+1,cy+c+1, [](int x, int y){return a[x]<a[y]});
	for (int i = 1, x = 1, y = 1; i <= l; i++) {
		int dx=lower[i], dy=a[dx];
		for(;x<=c&&cx[x]<=dx;x++){
			int nx=cx[x], ny=a[nx];
			int left = std::lower_bound(upper+1, upper+u+1, nx, [](int i, int j){return a[i]<a[j];});
			int right = std::upper_bound(upper+1, upper+u+1, nx);
			
		}
		for (; t <= n && t < lower[i] - 1; t++) set(1, 1, u, t, 0);
		for (; s < t && a[upper[s]] <= a[lower[i]]; s++) set(1, 1, u, s, -INF);
		for (; j <= n && j < lower[i]; j++)
			if (!mask[j]) add(j, 1), used[j] = 1;
		ans = std::max(ans, max[1] * 2);
		for (; k <= n && a[id[k]] <= a[lower[i + 1]]; k++)
			if (used[id[k]]) add(id[k], -1);
	}
	printf("%lld\n", all - ans);
	return 0;
}