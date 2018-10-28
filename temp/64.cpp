#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
lnt n, m, l, r, a[MAXN], b[MAXN], c[MAXN];
inline lnt getValue(int k) {
	lnt l = 0, r = 2000000000LL, ans = -1;
	while (l <= r) {
		lnt mid = (l + r) >> 1;
		lnt cnt = 0;
		for (int i = 1; i <= n; i++) {
			cnt += (std::upper_bound(b + 1, b + n + 1, mid - a[i]) - b) - 1;
		}
		if (cnt >= k) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
    return ans;
}
int main() {
	scanf("%lld%lld%lld", &n, &l, &r);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (int i = 1; i <= n; i++) scanf("%lld", b + i);
	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + n + 1);
	lnt L = getValue(l);
	lnt R = getValue(r);
	for (int i = 1; i <= n; i++) {
		int s = std::lower_bound(b + 1, b + n + 1, L - a[i]) - b;
		int e = std::lower_bound(b + 1, b + n + 1, R - a[i]) - b;
		for (int j = s; j < e; j++) c[++m] = a[i] + b[j];
	}
	std::sort(c + 1, c + m + 1);
	for (int i = 1; i <= m; i++) printf("%lld ", c[i]);
	for (int i = m + 1; i <= r - l + 1; i++) printf("%lld ", R);
    puts("");
	return 0;
}