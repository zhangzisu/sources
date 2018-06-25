#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
typedef long long lnt;
int n;
std::pair<lnt, lnt> d[MAXN];
lnt val[MAXN], max[MAXN << 2], tag[MAXN << 2];
inline void pushDown(int n) {
	if (tag[n]) {
		tag[n << 1] += tag[n];
		tag[n << 1 | 1] += tag[n];
		max[n << 1] += tag[n];
		max[n << 1 | 1] += tag[n];
		tag[n] = 0;
	}
}
void build(int n, int l, int r) {
	if (l == r) {
		max[n] = val[l] - d[l].first;
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid);
	build(n << 1 | 1, mid + 1, r);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
lnt query(int n, int l, int r, int L, int R) {
	if (l == L && r == R) return max[n];
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid) return query(n << 1, l, mid, L, R);
	if (L > mid) return query(n << 1 | 1, mid + 1, r, L, R);
	return std::max(query(n << 1, l, mid, L, mid), query(n << 1 | 1, mid + 1, r, mid + 1, R));
}
void add(int n, int l, int r, int L, int R, lnt v) {
	if (l == L && r == R) {
		max[n] += v;
		tag[n] += v;
		return;
	}
	int mid = (l + r) >> 1;
	pushDown(n);
	if (R <= mid)
		add(n << 1, l, mid, L, R, v);
	else if (L > mid)
		add(n << 1 | 1, mid + 1, r, L, R, v);
	else
		add(n << 1, l, mid, L, mid, v), add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	max[n] = std::max(max[n << 1], max[n << 1 | 1]);
}
lnt ans = 0;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &d[i].first, &d[i].second);
	std::sort(d + 1, d + n + 1);
	for (int i = 1; i <= n; i++) val[i] = val[i - 1] + d[i].second;
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		ans = std::max(ans, d[i].first + query(1, 1, n, i, n));
		add(1, 1, n, i, n, -d[i].second);
	}
	printf("%lld\n", ans);
	return 0;
}