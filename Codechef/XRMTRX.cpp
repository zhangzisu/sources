#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
typedef long long lnt;
int t;
lnt l, r;
inline int test(lnt len) {
	if (r - l - (len >> 1) >= (r - (len >> 1)) % len) return 1;
	if (r - l - (len >> 1) >= (r + 1) % len) return 1;
	return 0;
}
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%lld%lld", &l, &r);
		lnt ans = 1;
		while (test(ans << 1)) ans <<= 1;
		ans--;
		if (ans) {
			lnt cnt = std::max((ans ^ l) - l + 1, 0LL) + std::max(r - (ans ^ r) + 1, 0LL);
			if ((l & ans) == 0) cnt += ans + 1;
			if ((r & ans) == ans) cnt += ans + 1;
			if ((r ^ ans) < (l ^ ans)) cnt -= 2 * (ans + 1);
			printf("%lld %lld\n", ans, (cnt % MOD) * (((ans + 1) / 2) % MOD) % MOD);
		} else {
			printf("%d %lld\n", 0, (r - l + 1) % MOD);
		}
	}
	return 0;
}