#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
typedef long long lnt;
const lnt INFLL = (~0ULL) >> 1;
int T, n, m, k, s[MAXN], t[MAXN], x[5][MAXN], y[5][MAXN];
int main() {
	for (scanf("%d", &T); T; T--) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &s[i]);
			for (int j = 0; j < k; j++) scanf("%d", &x[j][i]);
		}
		for (int i = 1; i <= m; i++) {
			scanf("%d", &t[i]);
			for (int j = 0; j < k; j++) scanf("%d", &y[j][i]);
		}
		lnt ans = 0;
		for (int d = 0; d < (1 << k); d++) {
			lnt maxA = -INFLL, maxB = -INFLL;
			for (int i = 1; i <= n; i++) {
				lnt val = s[i];
				for (int j = 0; j < k; j++) val += (d >> j) & 1 ? -x[j][i] : x[j][i];
				maxA = std::max(maxA, val);
			}
			for (int i = 1; i <= m; i++) {
				lnt val = t[i];
				for (int j = 0; j < k; j++) val += (d >> j) & 1 ? y[j][i] : -y[j][i];
				maxB = std::max(maxB, val);
			}
			ans = std::max(ans, maxA + maxB);
		}
		printf("%lld\n", ans);
	}
	return 0;
}