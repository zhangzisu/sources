#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 300010
typedef long long lnt;
int n, a[MAXN], s0, s1;
lnt ans = 0;
constexpr lnt mask = (1LL << 32) - 1;
int main() {
	scanf("%d", &n);
	for (int i = 1, p = 0; i <= n; i++) {
		lnt x;
		scanf("%lld", &x);
		a[i] = __builtin_popcount(x >> 32) + __builtin_popcount(x & mask);
		p += a[i];
		(p & 1 ? s1 : s0)++;
	}
	for (int i = 1; i <= n; i++) {
		ans += s0;
		(a[i] & 1 ? s1 : s0)--;
		if (a[i] & 1) std::swap(s1, s0);
		for (int j = i, sum = 0, max = 0; j <= n && j <= i + 64; j++) {
			max = std::max(max, a[j]);
			sum += a[j];
			if (!(sum & 1) && sum - max < max) ans--;
		}
	}
	printf("%lld\n", ans);
	return 0;
}