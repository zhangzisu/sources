#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 300010
using lnt = long long;
struct query_t {
	int l, r, id;
	inline query_t(int l, int r, int id) : l(l), r(r), id(id) {}
};
int n, m, a[MAXN], len[MAXN];
std::vector<query_t> q[MAXN];
int stk[MAXN], top = 0;
lnt sum[MAXN], ans[MAXN];
inline lnt getDis(int p) {
	int l = 1, r = top, ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (stk[mid] <= p) {
			ans = std::max(ans, mid);
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	assert(ans);
	return sum[top] - sum[ans] + 1LL * (stk[ans + 1] - p) * ans;
}
inline lnt gcd(lnt a, lnt b) { return b ? gcd(b, a % b) : a; }
int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		q[x].emplace_back(l, r, i);
		len[i] = r - l + 1;
	}
	for (int i = 2; i <= n; i++) {
		while (top && a[i] <= stk[top]) top--;
		sum[top] = sum[top - 1] + 1LL * (a[i] - stk[top]) * top;
		stk[++top] = a[i], stk[top + 1] = i;
		sum[top] = sum[top - 1] + 1LL * (stk[top + 1] - stk[top]) * top;
		for (const auto &query : q[i]) {
			lnt disl = 1LL * (top + 1) * (i - query.l) - getDis(query.l);
			lnt disr = 1LL * (top + 1) * (i - query.r - 1) - getDis(query.r + 1);
			ans[query.id] = disl - disr;
		}
	}
	for (int i = 1; i <= m; i++) {
		lnt g = gcd(ans[i], len[i]);
		printf("%lld/%lld\n", ans[i] / g, len[i] / g);
	}
	return 0;
}
